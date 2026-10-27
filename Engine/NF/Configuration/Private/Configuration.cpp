// this file is AI-generated (Claude, claude-opus-5-5):
// Prompt: "Okay can you finish the configuration for me? with examples"

#include "Private/pch.hpp"

#include "Configuration/Configuration.hpp"

#include <Core/Diagnostics/Assert.hpp>
#include <Core/STL/Format.hpp>
#include <Core/STL/HashMap.hpp>

#include <algorithm>
#include <charconv>
#include <concepts>
#include <iterator>
#include <optional>
#include <utility>

namespace NF
{
    namespace
    {
        HashMap<HashType, SettingBase*> g_lookup;   // name hash -> setting
        Vector<SettingBase*>            g_settings; // registration order, stable output for Serialize / editor
        bool                            g_started{};

        [[nodiscard]] constexpr
        u8 Priority(SettingSource source) noexcept
        {
            switch (source)
            {
                case SettingSource::Default:     return 0;
                case SettingSource::ConfigFile:  return 1;
                case SettingSource::CommandLine: return 2;
                case SettingSource::Editor:      [[fallthrough]];
                case SettingSource::Runtime:     return 3; // live changes always win
            }

            return 0;
        }

        // calls fn with the setting cast to its real Setting<T>
        template<typename F>
        decltype(auto) Visit(SettingBase& setting, F&& fn)
        {
            switch (setting.GetType())
            {
                case SettingType::Bool:   return fn(static_cast<Setting<bool>&>(setting));
                case SettingType::Int:    return fn(static_cast<Setting<i64>&>(setting));
                case SettingType::Float:  return fn(static_cast<Setting<f64>&>(setting));
                case SettingType::String: return fn(static_cast<Setting<String>&>(setting));
            }

            ::std::unreachable();
        }

        [[nodiscard]] constexpr
        StringView Trim(StringView text) noexcept
        {
            constexpr StringView whitespace{ " \t\r\n" };

            const usize first{ text.find_first_not_of(whitespace) };

            if (first == StringView::npos)
            {
                return {};
            }

            const usize last{ text.find_last_not_of(whitespace) };

            return text.substr(first, last - first + 1);
        }

        [[nodiscard]] constexpr
        StringView Unquote(StringView text) noexcept
        {
            if (text.size() >= 2 && text.front() == '"' && text.back() == '"')
            {
                return text.substr(1, text.size() - 2);
            }

            return text;
        }

        // "renderer.vsync" -> "renderer"
        [[nodiscard]] constexpr
        StringView SectionOf(StringView name) noexcept
        {
            return name.substr(0, name.find('.'));
        }

        // "renderer.vsync" -> "vsync"
        [[nodiscard]] constexpr
        StringView KeyOf(StringView name) noexcept
        {
            const usize dot{ name.find('.') };

            return dot == StringView::npos ? name : name.substr(dot + 1);
        }

        template<typename T>
        [[nodiscard]]
        ::std::optional<T> ParseValue(StringView text) noexcept
        {
            if constexpr (::std::same_as<T, bool>)
            {
                if (text == "true" || text == "1" || text == "on")
                {
                    return true;
                }

                if (text == "false" || text == "0" || text == "off")
                {
                    return false;
                }

                return ::std::nullopt;
            }
            else
            {
                T out{};

                const char* const end{ text.data() + text.size() };
                const auto [ptr, ec]{ ::std::from_chars(text.data(), end, out) };

                if (ec != ::std::errc{} || ptr != end)
                {
                    return ::std::nullopt;
                }

                return out;
            }
        }

        // finds "section.key" without building the combined string
        [[nodiscard]]
        SettingBase* FindInSection(StringView section, StringView key) noexcept
        {
            if (section.empty())
            {
                return Configuration::Find(key); // key before any [section] is a full name
            }

            HashType hash{ CalculateHash(section) };
            hash = ContinueHash(hash, ".");
            hash = ContinueHash(hash, key);

            SettingBase* const setting{ Configuration::Find(hash) };

            if (!setting)
            {
                return nullptr;
            }

            // compare the name in parts, so a hash collision can't match
            const StringView name{ setting->GetName() };

            const bool matches{
                name.size() == section.size() + 1 + key.size() &&
                name.starts_with(section) &&
                name[section.size()] == '.' &&
                name.ends_with(key)
            };

            return matches ? setting : nullptr;
        }

        void AppendValue(String& out, SettingBase& setting)
        {
            Visit(setting, [&out]<typename T>(Setting<T>& typed)
            {
                if constexpr (::std::same_as<T, bool>)
                {
                    out += typed.Get() ? "true" : "false";
                }
                else if constexpr (::std::same_as<T, String>)
                {
                    out += '"';
                    out += typed.Get();
                    out += '"';
                }
                else
                {
                    ::NF::FormatTo(::std::back_inserter(out), "{}", typed.Get()); // shortest round-trip for f64
                }
            });
        }
    }

    void Configuration::Register(Span<SettingBase* const> settings)
    {
        g_settings.reserve(g_settings.size() + settings.size());

        for (SettingBase* const setting : settings)
        {
            // only used by the assert, unused in Release
            [[maybe_unused]] const StringView name{ setting->m_name };
            [[maybe_unused]] const usize      dot{ name.find('.') };

            NF_ASSERT(dot != StringView::npos && dot != 0 && dot != name.size() - 1,
                      "Setting name must be \"section.key\"");

            const bool inserted{ g_lookup.try_emplace(setting->m_hash, setting).second };

            NF_ASSERT(inserted, "Setting registered twice, or two names share a hash");

            if (inserted)
            {
                g_settings.push_back(setting);
            }
        }
    }

    SettingBase* Configuration::Find(StringView name) noexcept
    {
        SettingBase* const setting{ Find(CalculateHash(name)) };

        // compare the name too, so a hash collision with a typo can't match
        return (setting && setting->m_name == name) ? setting : nullptr;
    }

    SettingBase* Configuration::Find(HashType hash) noexcept
    {
        const auto it{ g_lookup.find(hash) };

        return it != g_lookup.end() ? it->second : nullptr;
    }

    Span<SettingBase* const> Configuration::GetAll() noexcept
    {
        return g_settings;
    }

    Configuration::Result Configuration::CanSet(const SettingBase& setting, SettingSource source) noexcept
    {
        if (HasFlag(setting.m_flags, SettingFlag::ReadOnly) && g_started)
        {
            return Result::NotAllowed;
        }

        if (Priority(source) < Priority(setting.m_source))
        {
            return Result::Ignored;
        }

        return Result::Ok;
    }

    Configuration::Result Configuration::SetFromText(SettingBase& setting, StringView text, SettingSource source)
    {
        return Visit(setting, [&text, &source]<typename T>(Setting<T>& typed) -> Result
        {
            if constexpr (::std::same_as<T, String>)
            {
                return Set(typed, Unquote(text), source);
            }
            else
            {
                const auto value{ ParseValue<T>(text) };

                if (!value)
                {
                    return Result::InvalidValue;
                }

                return Set(typed, *value, source);
            }
        });
    }

    void Configuration::ResetToDefault(SettingBase& setting)
    {
        Visit(setting, []<typename T>(Setting<T>& typed)
        {
            if (typed.m_value != typed.m_default)
            {
                typed.m_value = typed.m_default;
                ++typed.m_version;
            }

            typed.m_source = SettingSource::Default;
        });
    }

    Vector<Configuration::Error> Configuration::ParseArguments(Span<const StringView> args)
    {
        Vector<Error> errors;

        for (u32 index{}; index < args.size(); ++index)
        {
            const StringView arg{ args[index] };

            if (!arg.starts_with("--"))
            {
                continue;
            }

            const StringView body{ arg.substr(2) };
            const usize      equals{ body.find('=') };
            const StringView name{ body.substr(0, equals) };

            SettingBase* const setting{ Find(name) };

            if (!setting)
            {
                errors.push_back({ Result::UnknownSetting, index, String{ name } });
                continue;
            }

            StringView value{};

            if (equals != StringView::npos)
            {
                value = body.substr(equals + 1);
            }
            else if (setting->m_type == SettingType::Bool)
            {
                value = "true"; // "--renderer.vsync" alone
            }

            const Result result{ SetFromText(*setting, value, SettingSource::CommandLine) };

            if (result != Result::Ok && result != Result::Ignored)
            {
                errors.push_back({ result, index, String{ arg } });
            }
        }

        return errors;
    }

    Vector<Configuration::Error> Configuration::ParseText(StringView text, SettingSource source)
    {
        Vector<Error> errors;
        StringView    section{};
        u32           lineNumber{};

        while (!text.empty())
        {
            const usize newline{ text.find('\n') };
            StringView  line{ text.substr(0, newline) };

            text = (newline == StringView::npos) ? StringView{} : text.substr(newline + 1);
            ++lineNumber;

            line = Trim(line);

            if (line.empty() || line.front() == ';' || line.front() == '#')
            {
                continue;
            }

            if (line.front() == '[')
            {
                if (line.back() != ']' || line.size() < 3)
                {
                    errors.push_back({ Result::Malformed, lineNumber, String{ line } });
                    section = "?"; // matches nothing, so keys below report UnknownSetting
                    continue;
                }

                section = Trim(line.substr(1, line.size() - 2));
                continue;
            }

            const usize equals{ line.find('=') };

            if (equals == StringView::npos)
            {
                errors.push_back({ Result::Malformed, lineNumber, String{ line } });
                continue;
            }

            const StringView key{ Trim(line.substr(0, equals)) };
            const StringView value{ Trim(line.substr(equals + 1)) };

            SettingBase* const setting{ FindInSection(section, key) };

            if (!setting)
            {
                errors.push_back({ Result::UnknownSetting, lineNumber, String{ line } });
                continue;
            }

            const Result result{ SetFromText(*setting, value, source) };

            if (result != Result::Ok && result != Result::Ignored)
            {
                errors.push_back({ result, lineNumber, String{ line } });
            }
        }

        return errors;
    }

    String Configuration::Serialize()
    {
        Vector<SettingBase*> saved;
        saved.reserve(g_settings.size());

        for (SettingBase* const setting : g_settings)
        {
            const SettingSource source{ setting->m_source };

            // defaults and one-run command-line overrides aren't user choices
            if (HasFlag(setting->m_flags, SettingFlag::Saved) &&
                source != SettingSource::Default &&
                source != SettingSource::CommandLine)
            {
                saved.push_back(setting);
            }
        }

        // group by section, keep registration order inside a section
        ::std::stable_sort(saved.begin(), saved.end(), [](const SettingBase* a, const SettingBase* b)
        {
            return SectionOf(a->m_name) < SectionOf(b->m_name);
        });

        String     out;
        StringView currentSection{};

        for (SettingBase* const setting : saved)
        {
            const StringView section{ SectionOf(setting->m_name) };

            if (section != currentSection)
            {
                if (!out.empty())
                {
                    out += '\n';
                }

                out += '[';
                out += section;
                out += "]\n";

                currentSection = section;
            }

            out += KeyOf(setting->m_name);
            out += " = ";
            AppendValue(out, *setting);
            out += '\n';
        }

        return out;
    }

    void Configuration::Init()
    {
    }

    void Configuration::BeginFrame()
    {
        g_started = true; // ReadOnly settings are locked from the first frame on
    }

    void Configuration::PreUpdate()   {}
    void Configuration::FixedUpdate() {}
    void Configuration::Update()      {}
    void Configuration::PostUpdate()  {}
    void Configuration::Render()      {}
    void Configuration::EndFrame()    {}

    void Configuration::Shutdown()
    {
        g_lookup.clear();
        g_settings.clear();
        g_started = false;
    }
}

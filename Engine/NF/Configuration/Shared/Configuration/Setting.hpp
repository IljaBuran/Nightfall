// this file is AI-generated (Claude, claude-opus-5-5):
// Prompt: "Okay can you finish the configuration for me? with examples"

#pragma once

#include <Core/Types.hpp>
#include <Core/Utility/Helpers.hpp>
#include <Core/STL/String.hpp>

#include <concepts>
#include <type_traits>

namespace NF
{
    class Configuration;

    using HashType = u64;

    inline constexpr HashType HASH_SEED{ 14695981039346656037ull };

    // FNV-1a, can be continued: ContinueHash(CalculateHash("a"), "b") == CalculateHash("ab")
    [[nodiscard]] constexpr
    HashType ContinueHash(HashType hash, StringView text) noexcept
    {
        for (const char c : text)
        {
            hash ^= static_cast<u8>(c);
            hash *= 1099511628211ull;
        }

        return hash;
    }

    [[nodiscard]] constexpr
    HashType CalculateHash(StringView text) noexcept
    {
        return ContinueHash(HASH_SEED, text);
    }

    template<typename T>
    concept SettingValue =
        ::std::same_as<T, bool> ||
        ::std::same_as<T, i64>  ||
        ::std::same_as<T, f64>  ||
        ::std::same_as<T, String>;

    enum class SettingType : u8
    {
        Bool,
        Int,
        Float,
        String
    };

    enum class SettingFlag : u8
    {
        None        =      0,
        Saved       = 1 << 0, // written by Configuration::Serialize
        ReadOnly    = 1 << 1, // only settable before the first frame
        NeedRestart = 1 << 2, // for the editor: "restart required"
    };

    // ordered by priority, a lower source can't override a higher one
    enum class SettingSource : u8
    {
        Default,
        ConfigFile,
        CommandLine,
        Editor,
        Runtime
    };

    [[nodiscard]] constexpr
    SettingFlag operator|(SettingFlag a, SettingFlag b) noexcept
    {
        return static_cast<SettingFlag>(static_cast<u8>(a) | static_cast<u8>(b));
    }

    [[nodiscard]] constexpr
    bool HasFlag(SettingFlag flags, SettingFlag flag) noexcept
    {
        return (static_cast<u8>(flags) & static_cast<u8>(flag)) != 0;
    }

    template<SettingValue T>
    [[nodiscard]] consteval
    SettingType GetSettingType() noexcept
    {
        if constexpr (::std::same_as<T, bool>)
        {
            return SettingType::Bool;
        }
        else if constexpr (::std::same_as<T, i64>)
        {
            return SettingType::Int;
        }
        else if constexpr (::std::same_as<T, f64>)
        {
            return SettingType::Float;
        }
        else
        {
            return SettingType::String;
        }
    }

    // type-erased part, everything the registry, parsers and editor need
    class SettingBase
    {
        friend class ::NF::Configuration;

    public:

        NF_NOCOPY(SettingBase);
        NF_NOMOVE(SettingBase);

        [[nodiscard]] constexpr HashType      GetHash()        const noexcept { return m_hash; }
        [[nodiscard]] constexpr StringView    GetName()        const noexcept { return m_name; }
        [[nodiscard]] constexpr StringView    GetDescription() const noexcept { return m_description; }
        [[nodiscard]] constexpr SettingType   GetType()        const noexcept { return m_type; }
        [[nodiscard]] constexpr SettingFlag   GetFlags()       const noexcept { return m_flags; }
        [[nodiscard]] constexpr SettingSource GetSource()      const noexcept { return m_source; }

        // bumped on every change, compare against the last seen version instead of using callbacks
        [[nodiscard]] constexpr u32 GetVersion() const noexcept { return m_version; }

    protected:

        constexpr
        SettingBase(
            StringView  name,
            StringView  description,
            SettingType type,
            SettingFlag flags
        ) noexcept
            : m_hash{ CalculateHash(name) },
              m_name{ name },
              m_description{ description },
              m_type{ type },
              m_flags{ flags }
        {
        }

        constexpr ~SettingBase() = default;

    private:

        HashType      m_hash;
        StringView    m_name;        // "section.key", must point to static storage (a string literal)
        StringView    m_description;
        u32           m_version{};
        SettingType   m_type;
        SettingFlag   m_flags;
        SettingSource m_source{ SettingSource::Default };
    };

    template<SettingValue T>
    class Setting final : public SettingBase
    {
        friend class ::NF::Configuration;

    public:

        // string defaults are literals, so they're stored as a view
        using DefaultType = ::std::conditional_t<::std::same_as<T, String>, StringView, T>;

        // constexpr, not consteval: String settings allocate and can't be built at compile time.
        // bool/i64/f64 settings are still constant-initialized; add constinit to enforce it.
        constexpr
        Setting(
            StringView  name,
            StringView  description,
            DefaultType defaultValue,
            SettingFlag flags = SettingFlag::None
        )
            : SettingBase{ name, description, GetSettingType<T>(), flags },
              m_value{ defaultValue },
              m_default{ defaultValue }
        {
        }

        [[nodiscard]] constexpr const T&    Get()        const noexcept { return m_value; }
        [[nodiscard]] constexpr DefaultType GetDefault() const noexcept { return m_default; }

    private:

        T           m_value;
        DefaultType m_default;
    };
}

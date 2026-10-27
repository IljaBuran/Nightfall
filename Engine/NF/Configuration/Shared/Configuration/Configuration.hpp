// this file is AI-generated (Claude, claude-opus-5-5):
// Prompt: "Okay can you finish the configuration for me? with examples"

#pragma once

#include <Core/Module.hpp>
#include <Core/Types.hpp>
#include <Core/STL/Span.hpp>
#include <Core/STL/String.hpp>
#include <Core/STL/Vector.hpp>

#include "Configuration/Setting.hpp"

namespace NF
{
    // All functions are main-thread only, between frames.
    //
    // Names are "section.key". In INI text the section is written as a header:
    //
    //     [renderer]
    //     vsync = true        ; -> "renderer.vsync"
    //
    // The section is everything before the first '.', so "renderer.shadows.quality"
    // is written as "shadows.quality = ..." under [renderer].
    class Configuration
    {
        NF_MODULE(Configuration);

    public:

        enum class Result : u8
        {
            Ok,
            Ignored,        // a higher-priority source already set it (not an error)
            UnknownSetting,
            InvalidValue,
            NotAllowed,     // ReadOnly after startup
            Malformed       // line without '=' or a broken [section]
        };

        struct Error
        {
            Result result;
            u32    location; // line in text (from 1), or argument index (from 0)
            String text;     // offending name or line
        };

        // each module's compile-time table, call before parsing
        static void Register(Span<SettingBase* const> settings);

        [[nodiscard]] static SettingBase* Find(StringView name) noexcept;
        [[nodiscard]] static SettingBase* Find(HashType hash) noexcept;

        [[nodiscard]] static Span<SettingBase* const> GetAll() noexcept;

        // from code
        template<SettingValue T>
        static Result Set(Setting<T>& setting, typename Setting<T>::DefaultType value, SettingSource source = SettingSource::Runtime);

        // from text, converted by the setting's own type
        static Result SetFromText(SettingBase& setting, StringView text, SettingSource source);

        static void ResetToDefault(SettingBase& setting);

        // "--renderer.vsync=false", "--renderer.vsync" (bool only, means true); arguments without "--" are skipped
        [[nodiscard]] static Vector<Error> ParseArguments(Span<const StringView> args);

        // INI text: [section] headers, "key = value" lines, lines starting with ';' or '#' are comments
        [[nodiscard]] static Vector<Error> ParseText(StringView text, SettingSource source);

        // Saved settings the user chose (config file, editor, runtime), in ParseText format
        [[nodiscard]] static String Serialize();

    private:

        [[nodiscard]] static Result CanSet(const SettingBase& setting, SettingSource source) noexcept;
    };

    template<SettingValue T>
    Configuration::Result Configuration::Set(Setting<T>& setting, typename Setting<T>::DefaultType value, SettingSource source)
    {
        const Result result{ CanSet(setting, source) };

        if (result != Result::Ok)
        {
            return result;
        }

        if (setting.m_value != value)
        {
            setting.m_value = value;
            ++setting.m_version;
        }

        // source updates even if the value is the same: it decides saving and priority
        setting.m_source = source;

        return Result::Ok;
    }
}

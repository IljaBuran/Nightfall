#include "pch.hpp"

#include "Core/Log.hpp"
#include "Core/Logging/ISink.hpp"
#include "Logging/LogInternal.hpp"

#include "Core/Assert.hpp"

#include "Core/Containers/RingBuffer.hpp"
#include "Core/Containers/Vector.hpp"

// TODO(ilja): MULTITHREADING -> this will fail badly when threads will be introduced

namespace NF::Log
{
    namespace 
    {
        constexpr u32 logHistorySize{ 100u };
        struct State
        {
            RingBuffer<Record, logHistorySize> messageHistory;
            Vector<UniquePtr<ISink>> logSinks;
        };

        [[nodiscard]] constexpr
        StringView GetPrefixByLogLevel(Level level) noexcept
        {
            switch (level)
            {
                case Level::Info:    return "[INFO] ";
                case Level::Warning: return "[WARNING] ";
                case Level::Error:   return "[ERROR] ";
                case Level::Fatal:   return "[FATAL] ";
                case Level::Count:   break;
            }

            NF_ASSERT(false && "Invalid log level");
            return {};
        }
        
        
        [[nodiscard]] static 
        State& GetState() noexcept
        {
            static State state;
            return state;
        }

        void Distribute(const Record& entry)
        {
            auto& state{ GetState() };
            for (auto& sink : state.logSinks)
                sink->Write(entry);
        }
    }

    /* PUBLIC APIs IMPLEMENTATIONS */
    void Write(Level level, StringView message)
    {
        Record entry
        {
            .level{ level },
            .text{}
        };
        
        StringView prefix{ GetPrefixByLogLevel(level) };

        entry.text.reserve(prefix.size() + message.size());
        entry.text += prefix;
        entry.text += message;

        const auto& stored{ GetState().messageHistory.Add(std::move(entry)) };

        Distribute(stored);
    }

    void AddSink(UniquePtr<ISink> sink)
    {
        NF_ASSERT(sink);
        auto& state{ GetState() };
        state.logSinks.push_back(std::move(sink));
        auto& added{ state.logSinks.back()};
        for (u32 i{ 0 }; i < state.messageHistory.Size(); ++i)
        {
            added->Write(state.messageHistory[i]);
        }
    }
}

/* PRIVATE (INTERNAL) IMPLEMENTATIONS */
namespace NF::Log
{
    void Shutdown()
    {
        GetState().logSinks.clear(); // calls destructor on all sink uniqueptrs 
    }
}
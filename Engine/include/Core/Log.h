#pragma once

#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/pattern_formatter.h>

/**
 * Logging manager used as a wraper for spdlog.
 */
class Log
{
public:
    /// Initialization
    static void Init();
    /// Gets
    static std::shared_ptr<spdlog::logger> &GetCoreLogger();
    
private:
    /// Logger(s)
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

/**
 * Custum flag (log level symbols) used to format the log messages to its destination.
 */
class FlagLogSymbol : public spdlog::custom_flag_formatter
{
public:
    /// Format
    void format(const spdlog::details::log_msg &msg,
                const std::tm &, spdlog::memory_buf_t &dest) override;
    /// Copy/ Clone
    std::unique_ptr<spdlog::custom_flag_formatter> clone() const override;
    
private:
    /// Log level symbol equivalence
    const std::vector<std::string> m_Symbols = { "📓", "📘", "📗", "⚠️", "🛑", "⚡️", "" };
};

// --------------------------------------------
// Definition of the logging macros.
// --------------------------------------------
#define CORE_TRACE(...)     ::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...)     ::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define CORE_INFO(...)      ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)      ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)     ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...)  ::Log::GetCoreLogger()->critical(__VA_ARGS__)

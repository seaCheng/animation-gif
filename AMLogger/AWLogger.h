#pragma once
#include<iostream>
#include<memory>
#include"spdlog/spdlog.h"
#include"spdlog/sinks/basic_file_sink.h"
namespace AMLog
{
    class  AMLogger
    {
    public:
        ~AMLogger()
        {

        }
    private:
        friend class AWLoggerFactory;
        AMLogger(std::shared_ptr<spdlog::logger> logger)
        {
            m_logger = logger;
        }
    public:
        template<typename FormatString, typename... Args>
        void trace(const FormatString& fmt, Args &&...args)
        {
            if (m_logger) m_logger->log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void debug(const FormatString& fmt, Args &&...args)
        {
            if (m_logger)m_logger->log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void info(const FormatString& fmt, Args &&...args)
        {
            if (m_logger) m_logger->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void warn(const FormatString& fmt, Args &&...args)
        {
            if (m_logger) m_logger->log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void error(const FormatString& fmt, Args &&...args)
        {
            if (m_logger) m_logger->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
        }
        template<typename FormatString, typename... Args>
        void critical(const FormatString& fmt, Args &&...args)
        {
            if (m_logger) m_logger->log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
        }

        std::shared_ptr<spdlog::logger> logger() {
            return m_logger;
        }
    private:
        std::shared_ptr<spdlog::logger> m_logger = nullptr;
    };
   static void set_default_logger(std::shared_ptr<AMLog::AMLogger> logger)
    {
        spdlog::set_default_logger(logger->logger());
    }

    template<typename FormatString, typename... Args>
    void trace(const FormatString& fmt, Args &&...args)
    {
        spdlog::log(spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void debug(const FormatString& fmt, Args &&...args)
    {
        spdlog::log(spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void info(const FormatString& fmt, Args &&...args)
    {
        spdlog::log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void warn(const FormatString& fmt, Args &&...args)
    {
        spdlog::log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template<typename FormatString, typename... Args>
    void error(const FormatString& fmt, Args &&...args)
    {
        spdlog::log(spdlog::level::level_enum::err, fmt, std::forward<Args>(args)...);
    }
    template<typename FormatString, typename... Args>
    void critical(const FormatString& fmt, Args &&...args)
    {
        spdlog::log(spdlog::level::critical, fmt, std::forward<Args>(args)...);
    }


}

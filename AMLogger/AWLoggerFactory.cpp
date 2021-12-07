#include "AWLoggerFactory.h"
#include<string>
#include<memory>
#include<iostream>
#include"AWLogger.h"
#ifdef _MSC_VER
#include"spdlog/sinks/msvc_sink.h"
#endif //
#include"qt_sink.h"
namespace AMLog
{
    //AWLoggerFactory * AWLoggerFactory::m_instatce = nullptr;
    std::shared_ptr <AWLoggerFactory> AWLoggerFactory::m_awinstance = nullptr;
    std::shared_ptr <AWLoggerFactory>AWLoggerFactory::CreateFactory(const char* filename, bool toconsol)
    {
        try
        {
            std::shared_ptr <AWLoggerFactory> pLogger(new  AWLoggerFactory);
            if (toconsol)
            {
#ifdef _MSC_VER
                auto console_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
                pLogger->m_sinks.push_back(console_sink);
                console_sink->set_level(spdlog::level::info);//?????????????
#endif
            }

#ifdef __APPLE__
//            auto debug_sink = std::make_shared<spdlog::sinks::qt_sink_mt>();
//            pLogger->m_sinks.push_back(debug_sink);
//            debug_sink->set_level(spdlog::level::info);//?????????????
#elif defined(_WIN32)
            auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
            msvc_sink->set_level(spdlog::level::info);
            pLogger->m_sinks.push_back(msvc_sink);
#endif


            try
            {
                if (filename != nullptr)
                {
                    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename);
                    file_sink->set_level(spdlog::level::info);
                    pLogger->m_sinks.push_back(file_sink);
                }
            }
            catch (const spdlog::spdlog_ex& ex)
            {
                std::cout << "Log init failed: " << ex.what() << std::endl;
            }
            return pLogger;
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }
        return nullptr;
    }
    std::shared_ptr<AMLogger>AWLoggerFactory::CreateLogger(const std::string& logger_name)
    {
        try
        {

            auto logger = std::make_shared<spdlog::logger>(logger_name, m_sinks.begin(), m_sinks.end());
            logger->set_level(spdlog::level::info);
            logger->flush_on(spdlog::level::info);
            std::shared_ptr <AMLogger> pLogger = std::shared_ptr<AMLogger>(new AMLogger(logger));
            return pLogger;
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }
        return nullptr;
    }

    std::shared_ptr<spdlog::logger>AWLoggerFactory::CreateSpdlog(const std::string& logger_name)
    {
        try
        {

            auto logger = std::make_shared<spdlog::logger>(logger_name, m_sinks.begin(), m_sinks.end());
            logger->flush_on(spdlog::level::trace);
            return logger;
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }
        return nullptr;
    }
}

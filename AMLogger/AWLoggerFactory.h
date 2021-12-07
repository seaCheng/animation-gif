#pragma once
#include<memory>
#include"AWLogger.h"
#include"spdlog/spdlog.h"
#include"spdlog/sinks/basic_file_sink.h"

#include <QMutex>

namespace AMLog
{
    class  AWLoggerFactory
    {
    public:

        static std::shared_ptr <AWLoggerFactory> instace()
        {
            QMutex m_smutex;
            if(m_awinstance == nullptr)
            {
                m_smutex.lock();
                if(m_awinstance == nullptr)
                {
                    m_awinstance = CreateFactory("./Log/log.txt", false);
                }
                m_smutex.unlock();
            }

            return m_awinstance;
        }

        //创建一个日志工厂
        //filename 文件名字
        //toconsol 是否再控制台显示
        static std::shared_ptr <AWLoggerFactory>CreateFactory(const char* filename, bool toconsol);
        std::shared_ptr<AMLog::AMLogger>CreateLogger(const std::string& logger_name);
        std::shared_ptr<spdlog::logger>CreateSpdlog(const std::string& logger_name);
    private:
        AWLoggerFactory()
        {
        }
        std::vector<std::shared_ptr<spdlog::sinks::sink>> m_sinks;

        //static AWLoggerFactory * m_instatce;
        static std::shared_ptr <AWLoggerFactory> m_awinstance;
    };

}

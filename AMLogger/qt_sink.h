#ifndef QT_SINK_H
#define QT_SINK_H
// Copyright(c) 2016 Alexander Dalshov.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#include <spdlog/details/null_mutex.h>
#include <spdlog/sinks/base_sink.h>

#include <mutex>
#include <string> 

#include <QObject>
#include<qdebug.h>
// Avoid including windows.h (https://stackoverflow.com/a/30741042)
namespace spdlog {
namespace sinks {
/*
 * MSVC sink (logging using OutputDebugStringA)
 */
template<typename Mutex>
class qt_sink : public base_sink<Mutex>
{
public:
    qt_sink() = default;

protected:
    void sink_it_(const details::log_msg &msg) override
    {
        memory_buf_t formatted;
        base_sink<Mutex>::formatter_->format(msg, formatted);
        qDebug()<<fmt::to_string(formatted).c_str();
    }

    void flush_() override {}
};

using qt_sink_mt = qt_sink<std::mutex>;
using qt_sink_st = qt_sink<details::null_mutex>;

using qtdebug_sink_mt =qt_sink_mt;
using qtdebug_sink_st = qt_sink_st;

} // namespace sinks
} // namespace spdlog


#endif // QT_SINK_H

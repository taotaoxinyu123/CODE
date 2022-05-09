#ifndef COCC_TICK_TOCK_HPP
#define COCC_TICK_TOCK_HPP
namespace hticktock {
    class Clock {
    public:
        Clock()
        {
            latest_tick_tock_time_ = boost::posix_time::second_clock::local_time();  // 默认值先设置为程序启动时间
        }
    public:
        // 是否需要发起TickTock
        bool is_enable_start_tick_tock()
        {
            return is_enable_start(kTickTockDuration, latest_tick_tock_time_);
        }
    public:
        bool is_enable_start(int kDuration, boost::posix_time::ptime& latest)
        {
            bool ret = false;
            std::lock_guard<std::mutex> guard(mutex_);
            if (latest.is_not_a_date_time())
            {
                ret = true;
                latest = boost::posix_time::microsec_clock::local_time();
            }
            else
            {
                boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
                boost::posix_time::millisec_posix_time_system_config::time_duration_type duration = now - latest;
                if (kDuration < duration.total_milliseconds())
                {
                    ret = true;
                    latest = now;
                }
            }
            return ret;
        }
    public:
        std::mutex mutex_;  // 数据互斥锁
    private:
        boost::posix_time::ptime latest_tick_tock_time_;  // t=上次心跳时间
    private:
        static const int kTickTockDuration = 200000;  // 心跳间隔：2000ms
    };
    typedef boost::serialization::singleton<Clock> singleton_clock;  // 单例
}  // namespace hticktock


#endif

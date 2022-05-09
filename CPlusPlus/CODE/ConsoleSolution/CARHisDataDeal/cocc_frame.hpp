#ifndef COCC_FRAME_HPP
#define COCC_FRAME_HPP
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "cocc_his_enum.h"
namespace hframe 
{
    // client使用
    // 心跳
    class frame_tick_tock_t {
    public:
        frame_tick_tock_t() = default;
        frame_tick_tock_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& content) : time_(time), msg_id_(msg_id), version_(version), content_(content)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& content() { return content_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("content");
            w.String(content().c_str());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string content_;
    };
    // 报告请求
    class frame_report_ask_t {
    public:
        frame_report_ask_t() = default;
        frame_report_ask_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const hdata::statistics_report_type& msg_flag,
            const std::string spare) : time_(time), msg_id_(msg_id), version_(version), line_id_(line_id), report_id_(report_id), msg_flag_(msg_flag), spare_(spare)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& line_id() { return line_id_; }
        std::string& report_id() { return report_id_; }
        hdata::statistics_report_type& msg_flag() { return msg_flag_; }
        std::string& spare() { return spare_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("line_id");
            w.String(line_id().c_str());
            w.Key("report_id");
            w.String(report_id().c_str());
            w.Key("msg_flag");
            w.Int((int)msg_flag());
            w.Key("spare");
            w.String(spare().c_str());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string line_id_;
        std::string report_id_;
        hdata::statistics_report_type msg_flag_;
        std::string spare_;
    };
    // 事件及告警信息请求
    class frame_alarm_ask_t {
    public:
        frame_alarm_ask_t() = default;
        frame_alarm_ask_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const hdata::action_msg_type& msg_type,
            const std::string& start_time,
            const std::string& end_time) : time_(time), msg_id_(msg_id), version_(version), line_id_(line_id), report_id_(report_id), msg_type_(msg_type), start_time_(start_time), end_time_(end_time)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& line_id() { return line_id_; }
        std::string& report_id() { return report_id_; }
        hdata::action_msg_type& msg_type() { return msg_type_; }
        std::string& start_time() { return start_time_; }
        std::string& end_time() { return end_time_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("line_id");
            w.String(line_id().c_str());
            w.Key("report_id");
            w.String(report_id().c_str());
            w.Key("msg_type");
            w.Int((int)msg_type());
            w.Key("start_time");
            w.String(start_time().c_str());
            w.Key("end_time");
            w.String(end_time().c_str());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string line_id_;
        std::string report_id_;
        hdata::action_msg_type msg_type_;
        std::string start_time_;
        std::string end_time_;
    };
    // 运行图请求
    class frame_schedule_ask_t {
    public:
        frame_schedule_ask_t() = default;
        frame_schedule_ask_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const std::string& date,
            const hdata::tg_msg_type& tg_type) : time_(time), msg_id_(msg_id), version_(version), line_id_(line_id), report_id_(report_id), date_(date), tg_type_(tg_type)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& line_id() { return line_id_; }
        std::string& report_id() { return report_id_; }
        std::string& date() { return date_; }
        hdata::tg_msg_type& tg_type() { return tg_type_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("line_id");
            w.String(line_id().c_str());
            w.Key("report_id");
            w.String(report_id().c_str());
            w.Key("date");
            w.String(date().c_str());
            w.Key("tg_type");
            w.Int((int)tg_type());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string line_id_;
        std::string report_id_;
        std::string date_;
        hdata::tg_msg_type tg_type_;
    };

    // server使用
    // 基础
    class frame_basic_t {
    public:
        frame_basic_t() = default;
        frame_basic_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id) : time_(time), msg_id_(msg_id), version_(version), line_id_(line_id), report_id_(report_id)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& line_id() { return line_id_; }
        std::string& report_id() { return report_id_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("line_id");
            w.String(line_id().c_str());
            w.Key("report_id");
            w.String(report_id().c_str());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string line_id_;
        std::string report_id_;
    };
    // 基础-报告
    class frame_basic_report_t : public  frame_basic_t {
    public:
        frame_basic_report_t() = default;
        frame_basic_report_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count) : frame_basic_t(time, msg_id, version, line_id, report_id), total_message_(total_message), message_sequence_(message_sequence), count_(count)
        {

        }
    public:
        int& total_message() { return total_message_; }
        int& message_sequence() { return message_sequence_; }
        int& count() { return count_; }
    public:
        void pack_report(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            //rapidjson::StringBuffer s;
            //rapidjson::Writer<rapidjson::StringBuffer> w(s);
            this->pack_front(w);
            w.Key("total_message");
            w.Int((int)total_message());
            w.Key("message_sequence");
            w.Int((int)message_sequence());
            w.Key("count");
            w.Int((int)count());
        }
    private:
        int total_message_;
        int message_sequence_;
        int count_;
    };
    // 回复第三方：报告开始/结束
    class frame_report_start_end : public  frame_basic_t {
    public:
        frame_report_start_end() = default;
        frame_report_start_end(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const hdata::statistics_report_type& report_type) : frame_basic_t(time, msg_id, version, line_id, report_id), report_type_(report_type)
        {

        }
    public:
        hdata::statistics_report_type& report_type() { return report_type_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.Key("report_type");
            w.Int((int)report_type());
            w.EndObject();
            return s.GetString();
        }
    private:
        hdata::statistics_report_type report_type_;
    };
    // 回复第三方：车组运行里程报告数据
    class frame_running_group_report : public  frame_basic_report_t {
    public:
        frame_running_group_report() = default;
        frame_running_group_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::GroupRunningData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::GroupRunningData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("pvid");
                w.String(it_in->pvid.c_str());
                w.Key("total_running");
                w.String(it_in->total_running.c_str());
                w.Key("month_repair");
                w.String(it_in->month_repair.c_str());
                w.Key("self_repair");
                w.String(it_in->self_repair.c_str());
                w.Key("period_repair");
                w.String(it_in->period_repair.c_str());
                w.Key("factory_repair");
                w.String(it_in->factory_repair.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::GroupRunningData> report_data_;
    };
    // 回复第三方：司机驾驶里程报告数据
    class frame_driver_distance_report : public  frame_basic_report_t {
    public:
        frame_driver_distance_report() = default;
        frame_driver_distance_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::DriverDistanceData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::DriverDistanceData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("date");
                w.String(it_in->date.c_str());
                w.Key("driver_id");
                w.String(it_in->driver_id.c_str());
                w.Key("distance");
                w.String(it_in->distance.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::DriverDistanceData> report_data_;
    };
    // 回复第三方：调度日志报告数据
    class frame_dispatcher_report : public  frame_basic_report_t {
    public:
        frame_dispatcher_report() = default;
        frame_dispatcher_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::DisPatcherData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::DisPatcherData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("report_time");
                w.String(it_in->report_time.c_str());
                w.Key("user_name");
                w.String(it_in->user_name.c_str());
                w.Key("log_item");
                w.String(it_in->log_item.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::DisPatcherData> report_data_;
    };
    // 回复第三方：存备车报告数据
    class framegroup_bak_report : public  frame_basic_report_t {
    public:
        framegroup_bak_report() = default;
        framegroup_bak_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::GroupBakData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::GroupBakData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("pvid");
                w.String(it_in->pvid.c_str());
                w.Key("status");
                w.Int((int)it_in->status);
                w.Key("depot");
                w.Int((int)it_in->depot);
                w.Key("track_name");
                w.String(it_in->track_name.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::GroupBakData> report_data_;
    };
    // 回复第三方：列车整备状态报告数据
    class frame_group_status_report : public  frame_basic_report_t {
    public:
        frame_group_status_report() = default;
        frame_group_status_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::GroupStatusData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::GroupStatusData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("pvid");
                w.String(it_in->pvid.c_str());
                w.Key("status");
                w.String(it_in->status.c_str());
                w.Key("depot");
                w.Int((int)it_in->depot);
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::GroupStatusData> report_data_;
    };
    // 回复第三方： 操作命令消息数据
    class frame_action_report : public  frame_basic_report_t {
    public:
        frame_action_report() = default;
        frame_action_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::ActionData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::ActionData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("action_site");
                w.Int((int)it_in->action_site);
                w.Key("action_siteid");
                w.String(it_in->action_siteid.c_str());
                w.Key("action_name");
                w.String(it_in->action_name.c_str());
                w.Key("action_time");
                w.String(it_in->action_time.c_str());
                w.Key("action_user");
                w.String(it_in->action_user.c_str());
                w.Key("action_type");
                w.Int((int)it_in->action_type);
                w.Key("action_sub_type");
                w.String(it_in->action_sub_type.c_str());
                w.Key("action_len");
                w.String(it_in->action_len.c_str());
                w.Key("action_content");
                w.String(it_in->action_content.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::ActionData> report_data_;
    };
    // 回复第三方： 报警消息数据
    class frame_alarm_report : public  frame_basic_report_t {
    public:
        frame_alarm_report() = default;
        frame_alarm_report(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& report_id,
            const int& total_message,
            const int& message_sequence,
            const int& count,
            const std::list<hdata::AlarmData>& report_data) : frame_basic_report_t(time, msg_id, version, line_id, report_id, total_message, message_sequence, count), report_data_(report_data)
        {

        }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_report(w);

            w.Key("data");
            w.StartArray();
            for (std::list<hdata::AlarmData>::const_iterator it_in = report_data_.begin();
                it_in != report_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("alarm_site");
                w.Int((int)it_in->alarm_site);
                w.Key("alarm_siteid");
                w.String(it_in->alarm_siteid.c_str());
                w.Key("alarm_name");
                w.String(it_in->alarm_name.c_str());
                w.Key("alarm_time");
                w.String(it_in->alarm_time.c_str());
                w.Key("alarm_type");
                w.Int((int)it_in->alarm_type);
                w.Key("alarm_sub_type");
                w.String(it_in->alarm_sub_type.c_str());
                w.Key("alarm_len");
                w.String(it_in->alarm_len.c_str());
                w.Key("alarm_content");
                w.String(it_in->alarm_content.c_str());
                w.Key("alarm_ack_siteid");
                w.String(it_in->alarm_ack_siteid.c_str());
                w.Key("alarm_ack_site");
                w.String(it_in->alarm_ack_site.c_str());
                w.Key("alarm_ack_name");
                w.String(it_in->alarm_ack_name.c_str());
                w.Key("alarm_ack_time");
                w.String(it_in->alarm_ack_time.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::list<hdata::AlarmData> report_data_;
    };

    // 基础-运行图
    class frame_schedul_t {
    public:
        frame_schedul_t() = default;
        frame_schedul_t(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& date) : time_(time), msg_id_(msg_id), version_(version), line_id_(line_id), date_(date)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& line_id() { return line_id_; }
        std::string& date() { return date_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("line_id");
            w.String(line_id().c_str());
            w.Key("date");
            w.String(date().c_str());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string line_id_;
        std::string date_;
    };
    // 回复第三方：运行图开始/结束
    class frame_schedul_start_end : public  frame_schedul_t {
    public:
        frame_schedul_start_end() = default;
        frame_schedul_start_end(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& date,
            const hdata::tg_driver_type& tg_type) : frame_schedul_t(time, msg_id, version, line_id, date), tg_type_(tg_type)
        {

        }
    public:
        hdata::tg_driver_type& tg_type() { return tg_type_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.Key("tg_type");
            w.Int((int)tg_type());
            w.EndObject();
            return s.GetString();
        }
    private:
        hdata::tg_driver_type tg_type_;
    };
    // 回复第三方：计划运行图数据
    class frame_schedul_inused : public  frame_schedul_start_end {
    public:
        frame_schedul_inused() = default;
        frame_schedul_inused(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& date,
            const hdata::tg_driver_type& tg_type,
            const std::string& train_id,
            const std::string& trip_cnt,
            const std::list<hdata::InusedData>& inused_data) : frame_schedul_start_end(time, msg_id, version, line_id, date, tg_type), train_id_(train_id), trip_cnt_(trip_cnt), inused_data_(inused_data)
        {

        }
    public:
        std::string& train_id() { return train_id_; }
        std::string& trip_cnt() { return trip_cnt_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.Key("train_id");
            w.String(train_id().c_str());
            w.Key("trip_cnt");
            w.String(trip_cnt().c_str());

            w.Key("inused_data");
            w.StartArray();
            for (std::list<hdata::InusedData>::const_iterator it_in = inused_data_.begin();
                it_in != inused_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("trip_id");
                w.String(it_in->trip_id.c_str());
                w.Key("pvid");
                w.String(it_in->pvid.c_str());
                w.Key("destination_id");
                w.String(it_in->destination_id.c_str());
                w.Key("station_cnt");
                w.String(it_in->station_cnt.c_str());
                
                w.Key("stations");
                w.StartArray();
                for (std::list<hdata::InusedStation>::const_iterator it_in_in = it_in->stations.begin();
                    it_in_in != it_in->stations.end(); ++it_in_in)
                {
                    w.StartObject();
                    w.Key("station_id");
                    w.String(it_in_in->station_id.c_str());
                    w.Key("platform_id");
                    w.String(it_in_in->platform_id.c_str());
                    w.Key("a_time");
                    w.String(it_in_in->a_time.c_str());
                    w.Key("d_time");
                    w.String(it_in_in->d_time.c_str());
                    w.Key("flag");
                    w.Int((int)it_in_in->flag);
                    w.Key("spare");
                    w.String(it_in_in->spare.c_str());
                    w.EndObject();
                }
                w.EndArray();

                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::string train_id_;
        std::string trip_cnt_;
        std::list<hdata::InusedData> inused_data_;
    };
    // 回复第三方：实际运行图数据
    class frame_schedul_actual : public  frame_schedul_start_end {
    public:
        frame_schedul_actual() = default;
        frame_schedul_actual(const std::string& time,
            const hdata::his_data_type& msg_id,
            const std::string& version,
            const std::string& line_id,
            const std::string& date,
            const hdata::tg_driver_type& driver_type,
            const std::string& pvid,
            const std::string& station_cnt,
            const std::list <hdata::ActualdData>& actual_data) : frame_schedul_start_end(time, msg_id, version, line_id, date, driver_type), pvid_(pvid), station_cnt_(station_cnt), actual_data_(actual_data)
        {

        }
    public:
        std::string& pvid() { return pvid_; }
        std::string& station_cnt() { return station_cnt_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.Key("train_id");
            w.String(pvid().c_str());
            w.Key("station_cnt");
            w.String(station_cnt().c_str());

            w.Key("actual_data");
            w.StartArray();
            for (std::list<hdata::ActualdData>::const_iterator it_in = actual_data_.begin();
                it_in != actual_data_.end(); ++it_in)
            {
                w.StartObject();
                w.Key("station_id");
                w.String(it_in->station_id.c_str());
                w.Key("platform_id");
                w.String(it_in->platform_id.c_str());
                w.Key("a_time");
                w.String(it_in->a_time.c_str());
                w.Key("d_time");
                w.String(it_in->d_time.c_str());
                w.Key("flag");
                w.Int((int)it_in->flag);
                w.Key("train_id");
                w.String(it_in->train_id.c_str());
                w.Key("destination_id");
                w.String(it_in->destination_id.c_str());
                w.Key("type");
                w.Int((int)it_in->type);
                w.Key("spare");
                w.String(it_in->spare.c_str());
                w.EndObject();
            }
            w.EndArray();
            w.EndObject();
            return s.GetString();
        }
    private:
        std::string pvid_;
        std::string station_cnt_;
        std::list<hdata::ActualdData> actual_data_;
    };

    // common
    // 无结果查询
    class frame_false_t 
    {
    public:
        frame_false_t() = default;
        frame_false_t(const std::string & time,
            const hdata::his_data_type & msg_id,
            const std::string & version,
            const std::string & line_id,
            const std::string & report_id,
            const hdata::ask_nack& result,
            const std::string & content) : time_(time), msg_id_(msg_id), version_(version), line_id_(line_id), report_id_(report_id), result_(result), content_(content)
        {

        }
    public:
        std::string& time() { return time_; }
        hdata::his_data_type& msg_id() { return msg_id_; }
        std::string& version() { return version_; }
        std::string& line_id() { return line_id_; }
        std::string& report_id() { return report_id_; }
        hdata::ask_nack& result() { return result_; }
        std::string& content() { return content_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>&w)
        {
            w.Key("time");
            w.String(time().c_str());
            w.Key("msg_id");
            w.Int((int)msg_id());
            w.Key("version");
            w.String(version().c_str());
            w.Key("line_id");
            w.String(line_id().c_str());
            w.Key("report_id");
            w.String(report_id().c_str());
            w.Key("result");
            w.Int((int)result());
            w.Key("content");
            w.String(content().c_str());
        }
    private:
        std::string time_;
        hdata::his_data_type msg_id_;
        std::string version_;
        std::string line_id_;
        std::string report_id_;
        hdata::ask_nack result_;
        std::string content_;
    };
}

#endif

#include "cocc_his_impl.h"
#include "cocc_common_json.h"
#include "cocc_his_data.h"

static void Log(const std::string& message)
{
    hdata::singleton_cocchis_impl::get_mutable_instance().logger().Log(message);
}
namespace hcommon {
    // 获取Json对象: 暂时不使用了，因为想到里面的数据解析又组装，没啥用，中间也没用它。
    bool GetJsonInt(rapidjson::Document& document, const std::string& name, int& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        val = iter->value.GetInt();
        return true;
    }
    bool GetJsonString(rapidjson::Document& document, const std::string& name, std::string& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        val = iter->value.GetString();
        return true;
    }
    bool GetJsonGroupRunning(rapidjson::Document& document, const std::string& name, std::list<hdata::GroupRunningData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::GroupRunningData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.pvid = iter->value[i]["pvid"].GetString();
                data.total_running = iter->value[i]["total_running"].GetString();
                data.month_repair = iter->value[i]["month_repair"].GetString();
                data.self_repair = iter->value[i]["self_repair"].GetString();
                data.period_repair = iter->value[i]["period_repair"].GetString();
                data.factory_repair = iter->value[i]["factory_repair"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonDriverDistance(rapidjson::Document& document, const std::string& name, std::list<hdata::DriverDistanceData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::DriverDistanceData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.date = iter->value[i]["date"].GetString();
                data.driver_id = iter->value[i]["driver_id"].GetString();
                data.distance = iter->value[i]["distance"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonDisPatcher(rapidjson::Document& document, const std::string& name, std::list<hdata::DisPatcherData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::DisPatcherData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.report_time = iter->value[i]["report_time"].GetString();
                data.user_name = iter->value[i]["user_name"].GetString();
                data.log_item = iter->value[i]["log_item"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonGroupBak(rapidjson::Document& document, const std::string& name, std::list<hdata::GroupBakData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::GroupBakData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.pvid = iter->value[i]["pvid"].GetString();
                data.status = static_cast<hdata::driver_storge_status>(iter->value[i]["status"].GetInt());
                data.depot = static_cast<hdata::driver_location>(iter->value[i]["depot"].GetInt());
                data.track_name = iter->value[i]["track_name"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonGroupStatus(rapidjson::Document& document, const std::string& name, std::list<hdata::GroupStatusData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::GroupStatusData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.pvid = iter->value[i]["pvid"].GetString();
                data.status = iter->value[i]["status"].GetString();
                data.depot = static_cast<hdata::driver_ready_location>(iter->value[i]["depot"].GetInt());
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonAction(rapidjson::Document& document, const std::string& name, std::list<hdata::ActionData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::ActionData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.action_site = static_cast<hdata::order_location_type>(iter->value[i]["action_site"].GetInt());;
                data.action_siteid = iter->value[i]["action_siteid"].GetString();
                data.action_name = iter->value[i]["action_name"].GetString();
                data.action_time = iter->value[i]["action_time"].GetString();
                data.action_user = iter->value[i]["action_user"].GetString();
                data.action_type = static_cast<hdata::operation_type>(iter->value[i]["action_type"].GetInt());
                data.action_sub_type = iter->value[i]["action_sub_type"].GetString();
                data.action_len = iter->value[i]["action_len"].GetString();
                data.action_content = iter->value[i]["action_content"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonAlarm(rapidjson::Document& document, const std::string& name, std::list<hdata::AlarmData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::AlarmData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.alarm_site = static_cast<hdata::order_location_type>(iter->value[i]["alarm_site"].GetInt());;
                data.alarm_siteid = iter->value[i]["alarm_siteid"].GetString();
                data.alarm_name = iter->value[i]["alarm_name"].GetString();
                data.alarm_time = iter->value[i]["alarm_time"].GetString();
                data.alarm_type = static_cast<hdata::alarm_type>(iter->value[i]["alarm_type"].GetInt());
                data.alarm_sub_type = iter->value[i]["alarm_sub_type"].GetString();
                data.alarm_len = iter->value[i]["alarm_len"].GetString();
                data.alarm_content = iter->value[i]["alarm_content"].GetString();
                data.alarm_ack_siteid = iter->value[i]["alarm_ack_siteid"].GetString();
                data.alarm_ack_site = iter->value[i]["alarm_ack_site"].GetString();
                data.alarm_ack_name = iter->value[i]["alarm_ack_name"].GetString();
                data.alarm_ack_time = iter->value[i]["alarm_ack_time"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonScheduleInused(rapidjson::Document& document, const std::string& name, std::list<hdata::InusedData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::InusedData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.trip_id = iter->value[i]["trip_id"].GetString();
                data.pvid = iter->value[i]["pvid"].GetString();
                data.destination_id = iter->value[i]["destination_id"].GetString();
                data.station_cnt = iter->value[i]["station_cnt"].GetString();
                if (iter->value[i]["stations"].IsArray())
                {
                    hdata::InusedStation station_data;
                    for (int j = 0; j < iter->value[i]["stations"].Size(); j++)
                    {
                        station_data.station_id = iter->value[i]["stations"][j]["station_id"].GetString();
                        station_data.platform_id = iter->value[i]["stations"][j]["platform_id"].GetString();
                        station_data.a_time = iter->value[i]["stations"][j]["a_time"].GetString();
                        station_data.d_time = iter->value[i]["stations"][j]["d_time"].GetString();
                        station_data.flag = static_cast<hdata::tg_flag_type>(iter->value[i]["stations"][j]["flag"].GetInt());
                        station_data.spare = iter->value[i]["stations"][j]["spare"].GetString();
                        data.stations.push_back(station_data);
                    }
                }
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
    bool GetJsonSchedulActual(rapidjson::Document& document, const std::string& name, std::list<hdata::ActualdData>& val)
    {
        rapidjson::Value::ConstMemberIterator iter;
        iter = document.FindMember(name.c_str());
        if (iter == document.MemberEnd())
        {
            Log(name + ":error");
            return false;  // error
        }
        if (iter->value.IsArray())
        {
            hdata::ActualdData data;
            for (int i = 0; i < iter->value.Size(); i++)
            {
                data.station_id = iter->value[i]["station_id"].GetString();
                data.platform_id = iter->value[i]["platform_id"].GetString();
                data.a_time = iter->value[i]["a_time"].GetString();
                data.d_time = iter->value[i]["d_time"].GetString();
                data.flag = static_cast<hdata::tg_flag_type>(iter->value[i]["flag"].GetInt());
                data.train_id = static_cast<hdata::operation_type>(iter->value[i]["train_id"].GetInt());
                data.destination_id = iter->value[i]["destination_id"].GetString();
                data.type = static_cast<hdata::tg_plan_type>(iter->value[i]["type"].GetInt());
                data.spare = iter->value[i]["spare"].GetString();
                val.push_back(data);
            }
            return true;
        }
        return false;
    }
}  // namespace hcommon
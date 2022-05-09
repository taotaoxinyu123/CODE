#ifndef COCC_COMMON_JSON_H
#define COCC_COMMON_JSON_H

#include "rapidjson/document.h"
#include <boost/beast/core.hpp>
namespace hcommon {
	// 获取Json对象
	bool GetJsonInt(rapidjson::Document& document, const std::string& name, int& val);
	bool GetJsonString(rapidjson::Document& document, const std::string& name, std::string& val);
	bool GetJsonGroupRunning(rapidjson::Document& document, const std::string& name, std::list<hdata::GroupRunningData>& val);
	bool GetJsonDriverDistance(rapidjson::Document& document, const std::string& name, std::list<hdata::DriverDistanceData>& val);
	bool GetJsonDisPatcher(rapidjson::Document& document, const std::string& name, std::list<hdata::DisPatcherData>& val);
	bool GetJsonGroupBak(rapidjson::Document& document, const std::string& name, std::list<hdata::GroupBakData>& val);
	bool GetJsonGroupStatus(rapidjson::Document& document, const std::string& name, std::list<hdata::GroupStatusData>& val);
	bool GetJsonAction(rapidjson::Document& document, const std::string& name, std::list<hdata::ActionData>& val);
	bool GetJsonAlarm(rapidjson::Document& document, const std::string& name, std::list<hdata::AlarmData>& val);
	bool GetJsonScheduleInused(rapidjson::Document& document, const std::string& name, std::list<hdata::InusedData>& val);
	bool GetJsonSchedulActual(rapidjson::Document& document, const std::string& name, std::list<hdata::ActualdData>& val);
}	// namespace hcommon
#endif

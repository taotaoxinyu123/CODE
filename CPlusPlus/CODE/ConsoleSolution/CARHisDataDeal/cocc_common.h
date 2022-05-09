#ifndef COCC_COMMON_H
#define COCC_COMMON_H
#include <string>
#include "rapidjson/document.h"
#include <boost/beast/core.hpp>
#include <boost/crc.hpp>
// 业务处理
namespace hcommon
{
	// 打包
	void String2FlatBuffer(const std::string& str, boost::beast::flat_buffer& buf);
	// 获取当前时间字符串
	std::string SimpleTime();
} // namespace hserver

namespace hclient {
	// 响应心跳
	void TickTock(rapidjson::Document& document_read);
	// 响应消息推送开始
	void ReportBegin(rapidjson::Document& document_read);
	// 响应消息推送结束
	void ReportEnd(rapidjson::Document& document_read);
	// 响应车组运行里程报告
	void ReportGroupRunning(rapidjson::Document& document_read);
	// 响应司机驾驶里程报告
	void ReportDriverDistance(rapidjson::Document& document_read);
	// 响应调度日志报告
	void ReportDisPatcher(rapidjson::Document& document_read);
	// 响应存备车报告
	void ReportGroupBak(rapidjson::Document& document_read);
	// 响应列车整备状态报告
	void ReportGroupStatus(rapidjson::Document& document_read);
	// 响应操作命令消息
	void ReportAction(rapidjson::Document& document_read);
	// 列车信息、系统事件
	void ReportAlarm(rapidjson::Document& document_read);
	// 响应计划列车运行图消息
	void ScheduleInused(rapidjson::Document& document_read);
	// 响应实际列车运行图消息
	void SchedulActual(rapidjson::Document& document_read);
	// 响应运行图推送开始
	void ScheduleBegin(rapidjson::Document& document_read);
	// 响应运行图推送结束
	void ScheduleEnd(rapidjson::Document& document_read);
	// 判断crc是否相等
	bool Judge_CRC(hdata::his_data_type type);
	// crc的算法
	uint32_t GetCrc32(const std::string& my_string);
	// 响应查询无结果
	void ReportNoNack(rapidjson::Document& document_read);
}	// namespace hclient


namespace hserver {
	// 回复统计信息查询
	void ReportAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write);
	// 回复事件报警查询
	void AlarmAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write);
	// 回复运行图查询
	void ScheduleAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write);

	// 推送统计信息报告
	void SendReportData(const hdata::his_data_type type, hdata::statistics_report_type report_type, std::list<boost::beast::flat_buffer>& buffer_write);
	// 推送运行图信息报告
	void SendSchedulData(const hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write);

	// 处理统计信息数据
	void DealReportBlock(hdata::his_data_type type, hdata::statistics_report_type report_type, std::list<boost::beast::flat_buffer>& buffer_write);
	// 处理运行图信息数据
	void DealScheduleBlock(hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write);

	// 重复查询
	bool RepeatQuery(hdata::his_data_type type);
	// 是否正在做
	void judge_is_doing(hdata::his_data_type type);

}	// namespace hserver
#endif

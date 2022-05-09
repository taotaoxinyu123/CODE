#ifndef COCC_COMMON_H
#define COCC_COMMON_H
#include <string>
#include "rapidjson/document.h"
#include <boost/beast/core.hpp>
#include <boost/crc.hpp>
// ҵ����
namespace hcommon
{
	// ���
	void String2FlatBuffer(const std::string& str, boost::beast::flat_buffer& buf);
	// ��ȡ��ǰʱ���ַ���
	std::string SimpleTime();
} // namespace hserver

namespace hclient {
	// ��Ӧ����
	void TickTock(rapidjson::Document& document_read);
	// ��Ӧ��Ϣ���Ϳ�ʼ
	void ReportBegin(rapidjson::Document& document_read);
	// ��Ӧ��Ϣ���ͽ���
	void ReportEnd(rapidjson::Document& document_read);
	// ��Ӧ����������̱���
	void ReportGroupRunning(rapidjson::Document& document_read);
	// ��Ӧ˾����ʻ��̱���
	void ReportDriverDistance(rapidjson::Document& document_read);
	// ��Ӧ������־����
	void ReportDisPatcher(rapidjson::Document& document_read);
	// ��Ӧ�汸������
	void ReportGroupBak(rapidjson::Document& document_read);
	// ��Ӧ�г�����״̬����
	void ReportGroupStatus(rapidjson::Document& document_read);
	// ��Ӧ����������Ϣ
	void ReportAction(rapidjson::Document& document_read);
	// �г���Ϣ��ϵͳ�¼�
	void ReportAlarm(rapidjson::Document& document_read);
	// ��Ӧ�ƻ��г�����ͼ��Ϣ
	void ScheduleInused(rapidjson::Document& document_read);
	// ��Ӧʵ���г�����ͼ��Ϣ
	void SchedulActual(rapidjson::Document& document_read);
	// ��Ӧ����ͼ���Ϳ�ʼ
	void ScheduleBegin(rapidjson::Document& document_read);
	// ��Ӧ����ͼ���ͽ���
	void ScheduleEnd(rapidjson::Document& document_read);
	// �ж�crc�Ƿ����
	bool Judge_CRC(hdata::his_data_type type);
	// crc���㷨
	uint32_t GetCrc32(const std::string& my_string);
	// ��Ӧ��ѯ�޽��
	void ReportNoNack(rapidjson::Document& document_read);
}	// namespace hclient


namespace hserver {
	// �ظ�ͳ����Ϣ��ѯ
	void ReportAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write);
	// �ظ��¼�������ѯ
	void AlarmAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write);
	// �ظ�����ͼ��ѯ
	void ScheduleAsk(rapidjson::Document& document_read, std::list<boost::beast::flat_buffer>& buffer_write);

	// ����ͳ����Ϣ����
	void SendReportData(const hdata::his_data_type type, hdata::statistics_report_type report_type, std::list<boost::beast::flat_buffer>& buffer_write);
	// ��������ͼ��Ϣ����
	void SendSchedulData(const hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write);

	// ����ͳ����Ϣ����
	void DealReportBlock(hdata::his_data_type type, hdata::statistics_report_type report_type, std::list<boost::beast::flat_buffer>& buffer_write);
	// ��������ͼ��Ϣ����
	void DealScheduleBlock(hdata::his_data_type type, std::list<boost::beast::flat_buffer>& buffer_write);

	// �ظ���ѯ
	bool RepeatQuery(hdata::his_data_type type);
	// �Ƿ�������
	void judge_is_doing(hdata::his_data_type type);

}	// namespace hserver
#endif

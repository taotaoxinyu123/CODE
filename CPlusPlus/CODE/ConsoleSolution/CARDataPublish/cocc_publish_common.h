#ifndef COCC_PUBLISH_COMMON_H
#define COCC_PUBLISH_COMMON_H
#include <string>
#include "rapidjson/document.h"
#include <boost/beast/core.hpp>
#include "cocc_publish_data.h"
namespace pjson
{
	bool GetJsonInt(rapidjson::Document& document, const std::string& name, int& val);
	bool GetJsonString(rapidjson::Document& document, const std::string& name, std::string& val);
}

namespace pclient
{
	void TrainBlockInfo(int& type, std::vector<char>& data);
	void CbtcTrainIndicationInit(int& type, std::vector<char>& data);
}

namespace pbus 
{
	// ҵ���г�����
	void BusTrainBlockInfo(pubdata::post_train_block_info& trian_block_info);
	// ҵ���г�ȫ����Ϣ
	void BusCbtcTrainIndicationInit(pubdata::post_cbtc_train_indication_init& train_indication_init);
}
#endif

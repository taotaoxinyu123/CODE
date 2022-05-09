#ifndef COCC_CONFIG_MANAGER_HPP
#define COCC_CONFIG_MANAGER_HPP

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "boost/typeof/typeof.hpp"
#include "cocc_config_container.hpp"

namespace hconfig {
	std::string Load(Config& config)
	{
		std::string message;
		try
		{
			boost::property_tree::ptree pt;
			boost::property_tree::read_xml("CARHisDataDeal.xml", pt);
			{
				boost::property_tree::ptree child_local = pt.get_child("CARHisDataDeal.UpperRecv");
				config.cocc_upper_recv.ip = child_local.get<std::string>("<xmlattr>.ip");
				config.cocc_upper_recv.port = child_local.get<int>("<xmlattr>.port");
			}
			{
				boost::property_tree::ptree child_local = pt.get_child("CARHisDataDeal.UpperSend");
				config.cocc_upper_send.ip = child_local.get<std::string>("<xmlattr>.ip");
				config.cocc_upper_send.port = child_local.get<int>("<xmlattr>.port");
			}
			{
				boost::property_tree::ptree child_peer = pt.get_child("CARHisDataDeal.Lower");
				config.cocc_lower.ip = child_peer.get<std::string>("<xmlattr>.ip");
				config.cocc_lower.port = child_peer.get<int>("<xmlattr>.port");
			}
			{
				boost::property_tree::ptree child_peer = pt.get_child("CARHisDataDeal.Client");
				config.cocc_lower.client_max_num =  child_peer.get<int>("<xmlattr>.max_num");
			}
		}
		catch (const std::exception& ex)
		{
			message = ex.what();
		}
		return message;
	}
}

#endif


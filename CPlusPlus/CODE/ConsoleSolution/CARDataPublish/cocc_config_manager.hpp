#ifndef COCC_CONFIG_MANAGER_HPP
#define COCC_CONFIG_MANAGER_HPP

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "boost/typeof/typeof.hpp"
#include "cocc_config_container.hpp"

namespace pconfig {
	std::string Load(Config& config)
	{
		std::string message;
		try
		{
			boost::property_tree::ptree pt;
			boost::property_tree::read_xml("CARDataPublish.xml", pt);
			{
				boost::property_tree::ptree child_local = pt.get_child("CARDataPublish.Upper");
				config.machine.ip = child_local.get<std::string>("<xmlattr>.ip");
				config.machine.port = child_local.get<int>("<xmlattr>.port");
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


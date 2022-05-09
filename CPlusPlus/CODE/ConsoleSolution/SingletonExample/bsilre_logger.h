#ifndef BSILRE_LOGGER_H
#define BSILRE_LOGGER_H

#include <mutex>
#include <string>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "boost/typeof/typeof.hpp"

namespace bsilre_logger {

	class Logger {
	public:
		Logger(const std::string& file_name);
		void Log(const std::string& message);
		void ConfigEntity();
		void ConfigArbiter();
	private:
		std::mutex mutex_;  // ������
		bool enable_;  // �ܷ��¼��־
		std::string file_path;
		int log_size;
		int file_total_size;
	};
}  // namespace bsilre_logger

#endif

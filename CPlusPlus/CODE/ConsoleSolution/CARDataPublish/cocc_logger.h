#ifndef BSILRE_LOGGER_H
#define BSILRE_LOGGER_H

#include <mutex>
#include <string>
/*
	ͨ����־���
*/
namespace plogger {

	class Logger {
	public:
		Logger() {

		}
		~Logger(){
		}
	public:
		Logger(const std::string& file_name);
		void Log(const std::string& message);
	private:
		std::mutex mutex_;  // ������
	};
}  // namespace bsilre_logger

#endif

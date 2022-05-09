#ifndef BSILRE_LOGGER_H
#define BSILRE_LOGGER_H

#include <mutex>
#include <string>
/*
	通用日志输出
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
		std::mutex mutex_;  // 互斥锁
	};
}  // namespace bsilre_logger

#endif

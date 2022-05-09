#ifndef COCC_CONFIG_CONTAINER_HPP
#define COCC_CONFIG_CONTAINER_HPP

#include <mutex>
#include <string>
#include <list>

namespace pconfig {
	class Machine {
	public:
		Machine()
		{
			port = 0;
		}
	public:
		std::string ip;
		int port;
	};
	class Config {
	public:
		Machine machine; // Õ‚≤ø≈‰÷√
	};
	class ConfigContainer {
	public:
		void set(const Config& config)
		{
			std::lock_guard<std::mutex> guard(mutex_);
			config_ = config;
		}
		Config get()
		{
			std::lock_guard<std::mutex> guard(mutex_);
			return config_;
		}
	private:
		std::mutex mutex_;  // ª•≥‚À¯
		Config config_;  // XML≈‰÷√
	};
}

#endif


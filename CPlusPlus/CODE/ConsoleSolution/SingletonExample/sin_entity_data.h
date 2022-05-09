#pragma once
#include <string>
#include <list>
#include <vector>
namespace sin_entity {
	//Signal
	class SignalInfo {
	public:
		std::string name;
		int status_tagout;
		int mid_close;
		int mid_repeate_locking;
		int mid_locking;
		int mid_open_variable;
		int mid_opened_ever_variable;
		std::string mid_time_window;
	public:
		SignalInfo()
		{
			status_tagout = 0;
			mid_close = 0;
			mid_repeate_locking = 0;
			mid_locking = 0;
			mid_open_variable = 0;
			mid_opened_ever_variable = 0;
		}
	};
	// Turnout
	class TurnoutInfo {
	public:
		std::string name;
		int status_tagout;
		int mid_single_locking;
		std::string mid_time_window;
	public:
		TurnoutInfo()
		{
			status_tagout = 0;
			mid_single_locking = 0;
		}
	};
	// SumRunData
	class SumRunData {
	public:
		bool valid;
		std::string name;
	public:
		std::list<SignalInfo> list_signal_info;
		std::list< TurnoutInfo> list_turnout_info;
		std::string uuid;
	public:
		SumRunData()
		{
			this->clear();
		}
		void clear()
		{
			valid = false;
			list_signal_info.clear();
			list_turnout_info.clear();
			uuid.clear();
		}
	};

} // namespace bsilre_entity

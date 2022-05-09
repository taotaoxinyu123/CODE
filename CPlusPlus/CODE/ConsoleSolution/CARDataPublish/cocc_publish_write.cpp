#include <thread>
#include "cocc_publish_write.h"
#include "cocc_publish_impl.h"
//#include "bs_pub_api.h"
namespace pwrite 
{
	void do_start_publish_write()
	{
		pubdata::CoccPublishImpl& pi = pubdata::singleton_coccpublish_impl::get_mutable_instance();
		bool pub_iplat_switch = false;
		pi.get_pub_iplat_switch_imp(pub_iplat_switch);
		while (pub_iplat_switch)
		{
			std::map<std::string, pubdata::PublishIplat> src_pub_iplat;
			std::list<pubdata::PublishIplat> dst_pub_iplat;
			pi.get_pub_iplat_imp(src_pub_iplat);
			for (auto it : src_pub_iplat) 
			{
				dst_pub_iplat.push_back(it.second);
			}
			// TODOµ÷ÓÃAPI
			//BS_PUB_API_DataTranfer(dst_pub_iplat);
			// sleep 100ms
			std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(100));
		}
	}
}

void start_publish_write() 
{
	std::thread* write_thread = new std::thread(&pwrite::do_start_publish_write);
}
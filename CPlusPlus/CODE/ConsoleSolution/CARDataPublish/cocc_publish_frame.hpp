#ifndef COCC_PUBLISH_FRAME_HPP
#define COCC_PUBLISH_FRAME_HPP
#include <string>
#include <list>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "cocc_publish_enum.h"

namespace pframe 
{
    // ·¢ËÍtunnel
    class frame_client_id {
    public:
        frame_client_id() = default;
        frame_client_id(const std::string& name,
            const std::list<pubdata::real_data_type>& msg_id_arr) : name_(name), msg_id_arr_(msg_id_arr)
        {

        }
    public:
        std::string& name() { return name_; }
    public:
        std::string pack()
        {
            rapidjson::StringBuffer s;
            rapidjson::Writer<rapidjson::StringBuffer> w(s);
            w.StartObject();
            this->pack_front(w);
            w.EndObject();
            return s.GetString();
        }
        void pack_front(rapidjson::Writer<rapidjson::StringBuffer>& w)
        {
            w.Key("Name");
            w.String(name().c_str());
            w.Key("MsgIdArr");
            w.StartArray();
            for (std::list<pubdata::real_data_type>::const_iterator it_in = msg_id_arr_.begin();
                it_in != msg_id_arr_.end(); ++it_in)
            {
                w.Uint(int(*it_in));
            }
            w.EndArray();
        }
    private:
        std::string name_;
        std::list <pubdata::real_data_type> msg_id_arr_;
    };
}

#endif

// content from libs/log/example/rotating_file/main.cpp

#include <stdexcept>
#include <string>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>

#include "bsilre_logger.h"

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

namespace bsilre_logger {

    Logger::Logger(const std::string& file_name)
    {
        enable_ = true;
        if("bsilre_entity" == file_name)
        {
            ConfigEntity();
        }
        else if("bsilre_arbiter" == file_name)
        {
            ConfigArbiter();
        }
        else 
        {
            file_path = "logs";
            log_size = 10;
            file_total_size = 10;
        }
        try
        {
            // Create a text file sink
            typedef sinks::synchronous_sink< sinks::text_file_backend > file_sink;
            shared_ptr< file_sink > sink(new file_sink(
                keywords::file_name = "bsilre_log/" + file_name + "%Y%m%d_%H%M%S.log",                        // file name pattern
                //keywords::target_file_name = "%Y%m%d_%H%M%S_%5N.log",   // file name pattern
                keywords::rotation_size = log_size * 1024 * 1024                         // rotation size, in characters
            ));

            // Set up where the rotated files will be stored
            sink->locked_backend()->set_file_collector(sinks::file::make_collector(
                //keywords::target = "logs",                              // where to store rotated files
                keywords::target = file_path,                              // where to store rotated files
                //keywords::max_size = 200 * 1024 * 1024,                  // maximum total size of the stored files, in bytes
                keywords::max_size = file_total_size * 1024 * 1024,                  // maximum total size of the stored files, in bytes
                keywords::min_free_space = 1024 * 1024 * 1024,           // minimum free space on the drive, in bytes
                keywords::max_files = 512                               // maximum number of stored files
            ));

            // Upon restart, scan the target directory for files matching the file_name pattern
            sink->locked_backend()->scan_for_files();

            sink->set_formatter
            (
                expr::format("%1%:[%2%][%3%]%4%")
                % expr::attr< unsigned int >("RecordID")
                % expr::attr< boost::posix_time::ptime >("TimeStamp")
                % expr::attr<attrs::current_thread_id::value_type>("ThreadID")
                % expr::smessage
            );

            // Add it to the core
            logging::core::get()->add_sink(sink);
            logging::add_console_log(std::clog, keywords::format = "%TimeStamp%:[%ThreadID%]:%Message%");

            // Add some attributes too
            logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
            logging::core::get()->add_global_attribute("ThreadID", attrs::current_thread_id());
            logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());

            return;
        }
        catch (std::exception& e)
        {
            std::cout << "FAILURE: " << e.what() << std::endl;
            enable_ = false;
            return;
        }
    }

    void Logger::Log(const std::string& message)
    {

        if (!enable_)
        {
            std::cout << "Log not enable" << std::endl;
            return;
        }

        std::lock_guard<std::mutex> guard(mutex_);
        boost::log::sources::logger lg;
        BOOST_LOG(lg) << message;
        logging::core::get()->flush();
    }

    void Logger::ConfigEntity()
    {
        std::string message;
        try
        {
            boost::property_tree::ptree pt;
            boost::property_tree::read_xml("BSiLRe_EntityCfg.xml", pt);
            {
                boost::property_tree::ptree child_arbiter = pt.get_child("BSiLRe_EntityCfg.BsilReLog");
                file_path = child_arbiter.get<std::string>("<xmlattr>.path");
                log_size = child_arbiter.get<int>("<xmlattr>.log_size");
                file_total_size = child_arbiter.get<int>("<xmlattr>.file_total_size");
            }
        }
        catch (const std::exception& ex)
        {
            message = ex.what();
        }
    }

    void Logger::ConfigArbiter()
    {
        std::string message;
        try
        {
            boost::property_tree::ptree pt;
            boost::property_tree::read_xml("BSiLRe_ArbiterCfg.xml", pt);
            file_path = pt.get<std::string>("BSiLRe_ArbiterCfg.log_path");
            log_size = pt.get<int>("BSiLRe_ArbiterCfg.log_size");
            file_total_size = pt.get<int>("BSiLRe_ArbiterCfg.file_total_size");
        }
        catch (const std::exception& ex)
        {
            message = ex.what();
        }
    }


}

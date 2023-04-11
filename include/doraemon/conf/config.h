#ifndef DORAEMON_CONF_CONFIG_H
#define DORAEMON_CONF_CONFIG_H

#include <string>

#include "doraemon/json/json_util.h"

namespace doraemon {

struct Config final{
private:
    std::string conf_path = "./etc/conf";

private:
    static Config * config_ ;
    
    Config(){}
    Config(const std::string & conf_path) {
        this->conf_path = conf_path;
    }
public:
    static Config * get_config() {
        return config_;
    }
    static Config * init(const std::string & conf_path) {
        if (config_ == nullptr) {
            config_ = new Config(conf_path);
        }
        return config_;
    }

    template <typename T> T read_conf(const std::string & conf_file) {
        return JsonUtil::from_json_file<T>(this->conf_path + "/" + conf_file);
    }
};


};

#endif
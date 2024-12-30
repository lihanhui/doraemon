// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_CONF_CONFIG_H_
#define INCLUDE_DORAEMON_CONF_CONFIG_H_

#include <string>

#include "doraemon/export/export_def.h"
#include "doraemon/json/json_util.h"

namespace doraemon {

    struct D_CLASS_EXPORT Config final
    {
    private:
        std::string conf_path = "./etc/conf";

    private:
        static Config *config_;

        Config() {}
        explicit Config(const std::string &conf_path)
        {
            this->conf_path = conf_path;
        }

    public:
        static Config *get_config()
        {
            return config_;
        }
        static Config *init(const std::string &conf_path)
        {
            if (config_ == nullptr)
            {
                config_ = new Config(conf_path);
            }
            return config_;
        }

        template <typename T>
        T read_conf(const std::string &conf_file)
        {
            return JsonUtil::from_json_file<T>(this->conf_path + "/" + conf_file);
        }
    };

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_CONF_CONFIG_H_

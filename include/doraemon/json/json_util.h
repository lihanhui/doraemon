// Copyright (c) 2019 Hanhui LI
#ifndef INCLUDE_DORAEMON_JSON_JSON_UTIL_H_
#define INCLUDE_DORAEMON_JSON_JSON_UTIL_H_

#include <cassert>
#include <string>
#include <type_traits>

#include "doraemon/json/jsonable.h"

namespace doraemon{

struct JsonUtil {
    template <typename T>
    static typename std::enable_if<std::is_base_of<Jsonable, T>::value,
        std::string>::type to_json([[maybe_unused]] const T & t) {
        // t = t;
        return "";
    }
    template <typename T>
    static typename std::enable_if<std::is_base_of<Jsonable, T>::value, T>::type
        from_json([[maybe_unused]] const std::string & json) {
        // json.clear();
        return T();
    }
    template <typename T>
    static typename std::enable_if<std::is_base_of<Jsonable, T>::value, T>::type
        from_json_file([[maybe_unused]] const std::string & file) {
        // file.clear();
        return T();
    }
};

};  // namespace doraemon

#endif  // INCLUDE_DORAEMON_JSON_JSON_UTIL_H_

#ifndef DORAEMON_JSON_JSON_UTIL_H
#define DORAEMON_JSON_JSON_UTIL_H

#include <type_traits>

#include "doraemon/json/jsonable.h"

namespace doraemon{

struct json_util {
    template <typename T>
    static typename std::enable_if<std::is_base_of<jsonable, T>::value, std::string>::type to_json(const T & t){
        return "";
    }
    template <typename T> 
    static typename std::enable_if<std::is_base_of<jsonable, T>::value, T>::type from_json(const std::string & json){
        return T();
    }
    template <typename T> 
    static typename std::enable_if<std::is_base_of<jsonable, T>::value, T>::type from_json_file(const std::string & file){
        return T();
    }
};

};

#endif
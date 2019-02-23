#ifndef DORAEMON_JSON_JSONABLE_H
#define DORAEMON_JSON_JSONABLE_H

namespace doraemon {

struct jsonable{
    virtual std::string to_json() = 0;
    virtual void from_json(const std::string & json) = 0;
    //template<typename T> virtual typename std::enable_if<std::is_base_of<jsonable, T>::value, T>::type instance() = 0;
};

};

#endif
#include <iostream>
#include <memory>

#include "doraemon/doraemon.h"
#include "doraemon/conf/config.h"
#include "doraemon/json/jsonable.h"
#include "doraemon/md5/md5.h"
#include "doraemon/random/random_util.h"
#include "doraemon/base64/base64.h"

class MyJsonConf: public doraemon::jsonable{
    std::string to_json() override{
        return "";
    }
    void from_json(const std::string & json) override {
    
    }
};
int main(int argc, char * argv[]){
    for(int i = 0; i < 20; i++){
        std::cout<<doraemon::random_util::random(0, 10)<<std::endl;
    }
    doraemon::config::init("")->read_conf<MyJsonConf>("file");
    std::cout<<doraemon::md5::digest("grape")<<std::endl;

    const std::string s =
        "René Nyffenegger\n"
        "http://www.renenyffenegger.ch\n"
        "passion for data\n";

    std::string encoded = doraemon::base64::encode(reinterpret_cast<const unsigned char *>(s.c_str()), s.length());
    std::string decoded = doraemon::base64::decode(encoded);

    std::cout << "encoded: " << std::endl
              << encoded << std::endl
              << std::endl;
    std::cout << "decoded: " << std::endl
              << decoded << std::endl;

    return 0;
}

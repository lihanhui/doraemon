#include <iostream>
#include <memory>

#include "doraemon/doraemon.h"
#include "doraemon/conf/config.h"
#include "doraemon/json/jsonable.h"
#include "doraemon/md5/md5.h"
#include "doraemon/random/random_util.h"

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
    return 0;
}

// Copyright (c) 2019 Hanhui LI
#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "doraemon/doraemon.h"
#include "doraemon/conf/config.h"
#include "doraemon/json/jsonable.h"
#include "doraemon/md5/md5.h"
#include "doraemon/random/random_util.h"
#include "doraemon/base64/base64.h"
#include "doraemon/queue/queue_fifo.h"
#include "doraemon/lock/spin_lock.h"
#include "doraemon/lock/scoped_lock.h"
#include "doraemon/sys/system.h"
#include "doraemon/concurrency/abstract_task.h"
#include "doraemon/concurrency/thread_pool.h"
#include "doraemon/uuid/uuid.h"

using namespace doraemon;

class MyJsonConf: public doraemon::Jsonable{
    std::string to_json() override {
        return "";
    }
    void from_json([[maybe_unused]]const std::string & json) override {
    
    }
};
template<typename T> class MyTask: public doraemon::AbstractTask<T>{
private:
    T a_;
public:
    MyTask(T a): a_(a){
        std::cout<<"constructor"<<std::endl;
    } 
    void run() override {
        std::cout<<"run:"<<a_<<std::endl;
        this->get_promise()->success(a_);
    }
};
//template std::shared_ptr<doraemon::Future<int>> doraemon::Executor::submit<int>(std::shared_ptr<doraemon::Task<int>>);
int main2([[maybe_unused]]int argc, [[maybe_unused]]char * argv[]){
    doraemon::ThreadPool *tp = new doraemon::SimpleThreadPool(2);
    tp->start();

    std::shared_ptr<doraemon::Task<int>> t = std::make_shared<MyTask<int>>(1);
    tp->submit<int>(t);

    std::shared_ptr<doraemon::Task<double>> t2 = std::make_shared<MyTask<double>>(1.1);
    tp->submit<double>(t2);

    /*char s1 = doraemon::System::PathSeperator;
    doraemon::SpinLock spin_lck;
    {
        doraemon::ScopedLock lck(spin_lck);
    }
    spin_lck.lock();
    spin_lck.lock();

    doraemon::QueueFifo<char> queue;
    queue.push(nullptr);
    std::cout<<queue.count()<<std::endl;
    char * data = queue.pop();
    std::cout<<data<<std::endl;
  
    for(int i = 0; i < 20; i++){
        std::cout<<doraemon::RandomUtil::random(0, 10)<<std::endl;
    }
    doraemon::Config::init("")->read_conf<MyJsonConf>("file");
    std::cout<<doraemon::Md5::digest("grape")<<std::endl;
    //*/
    const std::string s =
        "René Nyffenegger\n"
        "http://www.renenyffenegger.ch\n"
        "passion for data\n";

    std::string encoded = doraemon::Base64::encode(reinterpret_cast<const unsigned char *>(s.c_str()), s.length());
    std::string decoded = doraemon::Base64::decode(encoded);

    std::cout << "encoded: " << std::endl
              << encoded << std::endl
              << std::endl;
    std::cout << "decoded: " << std::endl
              << decoded << std::endl;

    return 0;
}

int main(){
    std::cout << Uuid::uuid()
              << std::endl;
}

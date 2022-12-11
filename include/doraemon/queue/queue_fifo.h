#include <mutex>

namespace doraemon{
    namespace queue{
        template<typename T> struct queue_node{
            queue_node* _next;
            T* _data;
        public:
            queue_node(T* data = nullptr):_next(nullptr), _data(data){}    
        };

        template<typename T> class queue_fifo{
        public:
            queue_fifo():_head(nullptr), _tail(nullptr), _count(0){}
        public:
            void push(T* t){
                std::scoped_lock lock(_lock);
                queue_node<T> *node = new queue_node<T>(t);
                if(_tail){
                    _tail->_next = node;
                    _tail = node;
                }else{
                    _head = node;
                    _tail = node;
               }
               ++_count; 
            }
            T* pop(){
                std::scoped_lock lock(_lock);
                queue_node<T>* head = _head;
                T* data = nullptr;
                if(_head){
                    T* data = head->_data;
                    if(_head->_next){// more than one node
                       _head = _head->_next;
                    }else{ // only one node
                       _head = _tail = nullptr;
                    }
                    delete head;
                    --_count; 
                }
                return data;
            }
            int count(){
                std::scoped_lock lock(_lock);
                return _count;
            }
            void clear(){
                std::scoped_lock lock(_lock);
                queue_node<T>* head = _head;
                queue_node<T>* next = nullptr;
                while(head){
                    next = head->_next;
                    delete head;
                    head = next;
                }
                _head = _tail = nullptr;
                _count = 0; 
            }
        private:
            std::mutex _lock;
            queue_node<T>* _head;
            queue_node<T>* _tail;
            int _count;
            
        };
};
};

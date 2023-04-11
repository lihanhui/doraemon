#include <mutex>

namespace doraemon{
    
        template<typename T> struct QueueNode{
            QueueNode* _next;
            T* _data;
        public:
            QueueNode(T* data = nullptr):_next(nullptr), _data(data){}    
        };

        template<typename T> class QueueFifo{
        public:
            QueueFifo():_head(nullptr), _tail(nullptr), _count(0){}
        public:
            void push(T* t){
                std::scoped_lock lock(_lock);
                QueueNode<T> *node = new QueueNode<T>(t);
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
                QueueNode<T>* head = _head;
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
                QueueNode<T>* head = _head;
                QueueNode<T>* next = nullptr;
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
            QueueNode<T>* _head;
            QueueNode<T>* _tail;
            int _count;
            
        };

};

#ifndef STACK_HPP
#define STACK_HPP

#include <vector>
#include <algorithm>

namespace ly{

    template <typename T>
    class SmartStack{
        public: 
            SmartStack(){ m_buffInsert = m_buff.begin(); }

            ~SmartStack(){ for(T e: m_buff){ delete e; } }

            void pushFront(T t_element){
                m_buffInsert = m_buff.emplace(m_buffInsert, t_element);
            }

            void pushBack(T t_element){
                m_buff.emplace_back(t_element);
            }
            
            void popFront(T t_element){
                auto it = std::find(m_buff.begin(), m_buff.end(), t_element);
                if( it != m_buff.end() ){
                    m_buff.erase(it);
                    m_buffInsert--;
                }
            }
            
            void popBack(T t_element){
                auto it = std::find(m_buff.begin(), m_buff.end(), t_element);
                if( it != m_buff.end() ){ m_buff.erase(it); }
            }

            typename std::vector<T>::iterator begin(){ return m_buff.begin(); }
            typename std::vector<T>::iterator end(){ return m_buff.end(); }

        private:
            std::vector<T> m_buff;
            typename std::vector<T>::iterator m_buffInsert;
    };

}

#endif //STACK_HPP

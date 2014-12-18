#ifndef __LList_H_
#define __LList_H_

#include <list>
#include <initializer_list>
#include <functional>
#include "Optional.h"

namespace LCollection{

    template<typename T>
    class LList : public std::list<T> {
    public:

        LList(): std::list<T>(){}
        LList(const std::list<T>& l): std::list<T>(l){}
        LList(const std::list<T>&& l): std::list<T>(l){}
        LList(std::initializer_list<T> l): std::list<T>(l){}

        template<typename... P>
        LList(P&&... ps): std::list<T>({ps...}){};

        Optional<T> findFirst(std::function<bool(T&)> f){
            for(T& t : *this){
                if(f(t)){
                    return EngagedOptional<T>(t);
                }
            }
            return DisengagedOptional<T>();
        }
/*        T& findLast(function<bool(T&)>);
        LList<T> findAll(function<bool(T&)>);
        LList<T*> findAll_ptr(function<bool(T&)>);
        bool any(function<bool(T&)>);
        bool all(function<bool(T&)>);
        bool no(function<bool(T&)>);
        T& get(unsigned int index);
*/
    };

}

#endif //__LList_H_

#ifndef __LList_H_
#define __LList_H_

#include <list>
#include <initializer_list>
#include <functional>
#include "Optional.h"

namespace LCollection{

    template<typename Base>
    class List : public Base{
    public:
        typedef typename Base::value_type value_type;
        List(): Base(){}
        List(const Base& l): Base(l){}
        List(const Base&& l): Base(l){}
        List(std::initializer_list<value_type> l): Base(l){}

        template<typename... P>
        List(P&&... ps): Base({ps...}){};

        Optional<value_type> findFirst(std::function<bool(value_type&)> f){
            for(value_type& t : *this){
                if(f(t)){
                    return Optional<value_type>::engage(t);
                }
            }
            return Optional<value_type>();
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

    template<typename T>
    using LinkedList = List<std::list<T>>;
}

#endif //__LList_H_

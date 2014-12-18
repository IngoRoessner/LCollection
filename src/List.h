#ifndef __LList_H_
#define __LList_H_

#include <list>
#include <vector>
#include <initializer_list>
#include <functional>
#include "Optional.h"
#include <string>

namespace LCollection{

    using std::to_string;

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

        std::string toString(std::string delimiter = ", "){
            std::string str = "";
            bool first = true;
            for(value_type& t : *this){
                if(!first){
                    str += delimiter;
                }else{
                    first = false;
                }
                str += to_string(t);
            }
            return str;
        }

        Optional<value_type> findFirst(std::function<bool(value_type&)> f){
            for(value_type& t : *this){
                if(f(t)){
                    return Optional<value_type>::engage(t);
                }
            }
            return Optional<value_type>();
        }

        Optional<value_type> findLast(std::function<bool(value_type&)> f){
            Optional<value_type> optional;
            for(value_type& t : *this){
                if(f(t)){
                    optional = Optional<value_type>::engage(t);
                }
            }
            return optional;
        }

        Optional<value_type> get(unsigned int index){
            unsigned int counter = 0;
            for(value_type& t : *this){
                if(counter == index){
                    return Optional<value_type>::engage(t);
                }
                counter++;
            }
            return Optional<value_type>();
        }

/*        LList<T> findAll(function<bool(T&)>);
        LList<T*> findAll_ptr(function<bool(T&)>);
        bool any(function<bool(T&)>);
        bool all(function<bool(T&)>);
        bool no(function<bool(T&)>);
*/
    };

    template<typename T>
    using LinkedList = List<std::list<T>>;

    template<typename T>
    using ArrayList = List<std::vector<T>>;
}

#endif //__LList_H_

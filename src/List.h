#ifndef __LList_H_
#define __LList_H_

#include <list>
#include <vector>
#include <initializer_list>
#include <functional>
#include "Optional.h"
#include <string>

namespace LCollection{

    template<typename Base>
    class List;

    using std::to_string;

    template<typename ListType, typename ElementType>
    std::string ListToString(ListType* list , std::string delimiter = ", "){
        std::string str = "";
        bool first = true;
        for(ElementType& t : *list){
            if(!first){
                str += delimiter;
            }else{
                first = false;
            }
            str += to_string(t);
        }
        return str;
    }

    template<typename ListType, typename ElementType>
    Optional<ElementType> findFirstInList(ListType* list, std::function<bool(ElementType&)> f){
        for(ElementType& t : *list){
            if(f(t)){
                return Optional<ElementType>::engage(t);
            }
        }
        return Optional<ElementType>();
    }

    template<typename ListType, typename ElementType>
    Optional<ElementType> findLastInList(ListType* list, std::function<bool(ElementType&)> f){
        Optional<ElementType> optional;
        for(ElementType& t : *list){
            if(f(t)){
                optional = Optional<ElementType>::engage(t);
            }
        }
        return optional;
    }

    template<typename ListType, typename ElementType>
    List<std::list<ElementType*>> findAllInList(ListType* list, std::function<bool(ElementType&)> f){
        List<std::list<ElementType*>> result;
        for(ElementType& t : *list){
            if(f(t)){
                result.push_back(&t);
            }
        }
        return result;
    }

    template<typename ListType, typename ElementType>
    List<std::list<ElementType>> findAllCopyInList(ListType* list, std::function<bool(ElementType&)> f){
        List<std::list<ElementType>> result;
        for(ElementType& t : *list){
            if(f(t)){
                result.push_back(t);
            }
        }
        return result;
    }

    template<typename ListType, typename ElementType>
    Optional<ElementType> getInList(ListType* list, unsigned int index){
        unsigned int counter = 0;
        for(ElementType& t : *list){
            if(counter == index){
                return Optional<ElementType>::engage(t);
            }
            counter++;
        }
        return Optional<ElementType>();
    }

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
            return ListToString<Base, value_type>(this, delimiter);
        }

        Optional<value_type> findFirst(std::function<bool(value_type&)> f){
            return findFirstInList<Base, value_type>(this, f);
        }

        Optional<value_type> findLast(std::function<bool(value_type&)> f){
            return findLastInList<Base, value_type>(this, f);
        }

        List<std::list<value_type*>> findAll(std::function<bool(value_type&)> f){
            return findAllInList<Base, value_type>(this, f);
        }

        List<std::list<value_type>> findAllCopy(std::function<bool(value_type&)> f){
            return findAllCopyInList<Base, value_type>(this, f);
        }

        /**
        * use only for ordered Base
        */
        Optional<value_type> get(unsigned int index){
            return getInList<Base, value_type>(this, index);
        }

/*        
        bool any(function<bool(T&)>);
        bool all(function<bool(T&)>);
        bool no(function<bool(T&)>);
        List<P> map(function<P(T)>);
*/
    };

    template<typename T>
    using LinkedList = List<std::list<T>>;

    template<typename T>
    using ArrayList = List<std::vector<T>>;
}

#endif //__LList_H_

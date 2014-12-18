#ifndef __Optional_H_
#define __Optional_H_

#include <functional>
#include <stdexcept>
#include <memory>

namespace LCollection{

    template<typename T>
    class OptionalBase {
    public:
        virtual bool isEngaged() = 0;
        virtual T& value() = 0;
        virtual T& valueOr(T& other) = 0;
        virtual OptionalBase<T>& onEngaged(std::function<void(T&)> f) = 0;
        virtual OptionalBase<T>& onDisengaged(std::function<void()> f) = 0;
    };


    template<typename T>
    class EngagedOptional : public OptionalBase<T> {
        T& ref;
    public:
        EngagedOptional(EngagedOptional<T>& other):ref(other.ref){}
        EngagedOptional(EngagedOptional<T>&& other):ref(other.ref){}
        EngagedOptional(T& val): ref(val){}
        bool isEngaged(){return true;}
        T& value(){return ref;}
        T& valueOr(T& other){return ref;}
        OptionalBase<T>& onEngaged(std::function<void(T&)> f){f(this->ref); return *this;}
        OptionalBase<T>& onDisengaged(std::function<void()> f){return *this;}
    };


    template<typename T>
    class DisengagedOptional : public OptionalBase<T> {
    public:
        DisengagedOptional(){}
        bool isEngaged(){return false;}
        T& value(){throw std::logic_error("no value in disengaged optional");}
        T& valueOr(T& other){return other;}
        OptionalBase<T>& onEngaged(std::function<void(T&)> f){return *this;}
        OptionalBase<T>& onDisengaged(std::function<void()> f){f(); return *this;}
    };


    template<typename T>
    class Optional {
        std::shared_ptr<OptionalBase<T>> ptr;
    public:
        static Optional<T> engage(T& t){
            return Optional<T>(EngagedOptional<T>(t));
        }

        Optional(): ptr(new DisengagedOptional<T>()){}
        Optional(Optional<T>& orig): ptr(orig.ptr){}
        Optional(Optional<T>&& orig): ptr(orig.ptr){}
        Optional(EngagedOptional<T> orig): ptr(new EngagedOptional<T>(orig)){}
        Optional(DisengagedOptional<T> orig): ptr(new DisengagedOptional<T>(orig)){}
        bool isEngaged(){return this->ptr->isEngaged();}
        T& value(){return this->ptr->value();}
        T& valueOr(T& other){return this->ptr->valueOr(other);}
        OptionalBase<T>& onEngaged(std::function<void()> f){return this->ptr->onEngaged(f);}
        OptionalBase<T>& onDisengaged(std::function<void()> f){return this->ptr->onDisengaged(f);}
    };
}



#endif //__Optional_H_

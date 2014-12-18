#ifndef __OptionalTest_H_
#define __OptionalTest_H_

#include "../LTest/src/LTest.h"
#include "../src/Optional.h"
#include <vector>
#include <stdexcept>

using LCollection::Optional;
using LCollection::EngagedOptional;
using LCollection::DisengagedOptional;

TestSuite OptionalTest = {
        ltest().addTest("Optional::value", []() {
            std::vector<int> v = {1,2,3,4};
            auto get = [&](unsigned int index)->Optional<int>{
                if(v.size() <= index){
                    return Optional<int>();
                }else{
                    return Optional<int>::engage(v.at(index));
                }
            };

            LTAssert::True(get(0).value() == 1);
            LTAssert::True(get(1).value() == 2);
            LTAssert::True(get(2).value() == 3);
            LTAssert::True(get(3).value() == 4);
            LTAssert::ExpectException<std::logic_error>([&](){get(5).value();});

            get(0).value() = 8;
            LTAssert::True(get(0).value() == 8);
            LTAssert::True(v.at(0) == 8);
        }),

        ltest().addTest("Optional::valueOr", [](){
            int defaultVal = 20;
            std::vector<int> v = {1,2,3,4};
            auto get = [&](unsigned int index)->Optional<int>{
                if(v.size() <= index){
                    return Optional<int>();
                }else{
                    return Optional<int>::engage(v.at(index));
                }
            };

            LTAssert::True(get(0).valueOr(defaultVal) == 1);
            LTAssert::True(get(1).valueOr(defaultVal) == 2);
            LTAssert::True(get(2).valueOr(defaultVal) == 3);
            LTAssert::True(get(3).valueOr(defaultVal) == 4);
            LTAssert::True(get(5).valueOr(defaultVal) == defaultVal);

            get(0).valueOr(defaultVal) = 8;
            LTAssert::True(get(0).valueOr(defaultVal) == 8);
            LTAssert::True(v.at(0) == 8);

            get(6).valueOr(defaultVal) = 30;
            LTAssert::True(get(6).valueOr(defaultVal) == 30);
            LTAssert::True(defaultVal == 30);

        }),

        ltest().addTest("Optional::isEngaged", [](){
            std::vector<int> v = {1,2,3,4};
            auto get = [&](unsigned int index)->Optional<int>{
                if(v.size() <= index){
                    return Optional<int>();
                }else{
                    return Optional<int>::engage(v.at(index));
                }
            };

            LTAssert::True(get(0).isEngaged());
            LTAssert::True(get(1).isEngaged());
            LTAssert::True(get(2).isEngaged());
            LTAssert::True(get(3).isEngaged());
            LTAssert::False(get(4).isEngaged());

        }),

        ltest().addTest("Optional::on*()", [](std::vector<int>& v, unsigned int index, bool& engaged, bool& disengaged){
            auto get = [&](unsigned int index)->Optional<int>{
                if(v.size() <= index){
                    return Optional<int>();
                }else{
                    return Optional<int>::engage(v.at(index));
                }
            };
            engaged = false;
            disengaged = false;
            get(index).onEngaged([&](int& i){engaged = true;}).onDisengaged([&](){disengaged = true;});
        }, [](auto test){
            std::vector<int> v = {1,2,3,4};
            bool engaged, disengaged;
            test.with(v, 0, engaged, disengaged);
            LTAssert::True(engaged);
            LTAssert::False(disengaged);
            test.with(v, 1, engaged, disengaged);
            LTAssert::True(engaged);
            LTAssert::False(disengaged);
            test.with(v, 2, engaged, disengaged);
            LTAssert::True(engaged);
            LTAssert::False(disengaged);
            test.with(v, 3, engaged, disengaged);
            LTAssert::True(engaged);
            LTAssert::False(disengaged);
            test.with(v, 4, engaged, disengaged);
            LTAssert::False(engaged);
            LTAssert::True(disengaged);
            test.with(v, 5, engaged, disengaged);
            LTAssert::False(engaged);
            LTAssert::True(disengaged);
        })
};

#endif //__OptionalTest_H_

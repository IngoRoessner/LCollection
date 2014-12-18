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

        })
};

#endif //__OptionalTest_H_

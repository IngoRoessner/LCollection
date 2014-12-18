#ifndef __LListTest_H_
#define __LListTest_H_

#include "../LTest/src/LTest.h"
#include "../src/LList.h"

using LCollection::LList;
using LTAssert::True;

TestSuite LListTests = {
        ltest().addTest("LList::LList()", [](){
            LList<int> defaultConstructor;
            True(defaultConstructor.size() == 0);
            defaultConstructor.push_back(3);
            True(defaultConstructor.size() == 1);
            True(defaultConstructor.front() == 3);
        }),

        ltest().addTest("LList::LList(std::list&)", [](){
            std::list<int> l;
            l.push_back(5);
            LList<int> llist(l);
            True(l.size() == 1);
            True(l.front() == 5);
            l.push_back(3);
            True(l.size() == 2);
        }),

        ltest().addTest("LList::LList(initializer_list)", [](){
            LList<int> i = {1,2,3,4};
            LList<double> d{5,6,7,8};

            True(i.size() == 4);
            True(d.size() == 4);
            True(i.front() == 1);
            True(d.front() == 5);
        }),

        ltest().addTest("LList::LList(T...)", [](){
            LList<int> i(1,2,3,4);
            LList<double> d(5,6,7,8);

            True(i.size() == 4);
            True(d.size() == 4);
            True(i.front() == 1);
            True(d.front() == 5);
        }),

};


#endif //__LListTest_H_

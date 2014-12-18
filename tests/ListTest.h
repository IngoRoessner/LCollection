#ifndef __LListTest_H_
#define __LListTest_H_

#include "../LTest/src/LTest.h"
#include "../src/List.h"

using LCollection::LinkedList;
using LTAssert::True;

TestSuite LListTests = {
        ltest().addTest("LinkedList::LinkedList()", [](){
            LinkedList<int> defaultConstructor;
            True(defaultConstructor.size() == 0);
            defaultConstructor.push_back(3);
            True(defaultConstructor.size() == 1);
            True(defaultConstructor.front() == 3);
        }),

        ltest().addTest("LinkedList::LinkedList(std::list&)", [](){
            std::list<int> l;
            l.push_back(5);
            LinkedList<int> llist(l);
            True(l.size() == 1);
            True(l.front() == 5);
            l.push_back(3);
            True(l.size() == 2);
        }),

        ltest().addTest("LinkedList::LinkedList(initializer_list)", [](){
            LinkedList<int> i = {1,2,3,4};
            LinkedList<double> d{5,6,7,8};

            True(i.size() == 4);
            True(d.size() == 4);
            True(i.front() == 1);
            True(d.front() == 5);
        }),

        ltest().addTest("LinkedList::LinkedList(T...)", [](){
            LinkedList<int> i(1,2,3,4);
            LinkedList<double> d(5,6,7,8);

            True(i.size() == 4);
            True(d.size() == 4);
            True(i.front() == 1);
            True(d.front() == 5);
        }),

};


#endif //__LListTest_H_

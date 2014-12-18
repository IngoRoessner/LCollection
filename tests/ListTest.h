#ifndef __LListTest_H_
#define __LListTest_H_

#include "../LTest/src/LTest.h"
#include "../src/List.h"

using LCollection::LinkedList;
using LCollection::ArrayList;
using LTAssert::True;

TestSuite LinkedListTests = {
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

        ltest().addTest("LinkedList::findFirst()", [](){
            LinkedList<int> i(1,2,3,4);
            auto result1 = i.findFirst([](int& element){return element == 3;});
            True(result1.value() == 3, "1");

            auto result2 = i.findFirst([](int& element){return true;});
            True(result2.value() == 1, "2");

            auto result3 = i.findFirst([](int& element){return false;});
            LTAssert::False(result3.isEngaged(), "3 (shouldnt be engaged)");

            i.findFirst([](int& element){return true;}).value() = 20;
            True(i.front() == 20, "4 (value wasnt seted");
        })

};


TestSuite ArrayListTests = {
        ltest().addTest("ArrayList::ArrayList()", [](){
            ArrayList<int> defaultConstructor;
            True(defaultConstructor.size() == 0);
            defaultConstructor.push_back(3);
            True(defaultConstructor.size() == 1);
            True(defaultConstructor.front() == 3);
        }),

        ltest().addTest("ArrayList::ArrayList(std::list&)", [](){
            std::vector<int> l;
            l.push_back(5);
            ArrayList<int> llist(l);
            True(l.size() == 1);
            True(l.front() == 5);
            l.push_back(3);
            True(l.size() == 2);
        }),

        ltest().addTest("ArrayList::ArrayList(initializer_list)", [](){
            ArrayList<int> i = {1,2,3,4};
            ArrayList<double> d{5,6,7,8};

            True(i.size() == 4);
            True(d.size() == 4);
            True(i.front() == 1);
            True(d.front() == 5);
        }),

        ltest().addTest("ArrayList::ArrayList(T...)", [](){
            ArrayList<int> i(1,2,3,4);
            ArrayList<double> d(5,6,7,8);

            True(i.size() == 4);
            True(d.size() == 4);
            True(i.front() == 1);
            True(d.front() == 5);
        }),

        ltest().addTest("ArrayList::findFirst()", [](){
            ArrayList<int> i(1,2,3,4);
            auto result1 = i.findFirst([](int& element){return element == 3;});
            True(result1.value() == 3, "1");

            auto result2 = i.findFirst([](int& element){return true;});
            True(result2.value() == 1, "2");

            auto result3 = i.findFirst([](int& element){return false;});
            LTAssert::False(result3.isEngaged(), "3 (shouldnt be engaged)");

            i.findFirst([](int& element){return true;}).value() = 20;
            True(i.front() == 20, "4 (value wasnt seted");
        })

};


#endif //__LListTest_H_

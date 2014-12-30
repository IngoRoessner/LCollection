#ifndef __LListTest_H_
#define __LListTest_H_

#include "../LTest/src/LTest.h"
#include "../src/List.h"

using LCollection::LinkedList;
using LCollection::ArrayList;
using LTAssert::True;
using LTAssert::False;

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
            LinkedList<int> i(1,1,3,4);
            auto result1 = i.findFirst([](int& element){return element == 3;});
            True(result1.value() == 3, "1");

            auto result2 = i.findFirst([](int& element){return true;});
            True(result2.value() == 1, "2");

            auto result3 = i.findFirst([](int& element){return false;});
            LTAssert::False(result3.isEngaged(), "3 (shouldnt be engaged)");

            i.findFirst([](int& element){return true;}).value() = 20;
            True(i.front() == 20, "4 (value wasnt seted");

            i = LinkedList<int>(1,1,3,4);

            i.findFirst([](int& element){return element == 1;}).value() = 30;
            True(i.front() == 30, "5 (value wasnt seted)");
        }),

        ltest().addTest("LinkedList::findLast()", [](){
            LinkedList<int> i(1,1,3,4);
            auto result1 = i.findLast([](int& element){return element == 3;});
            True(result1.value() == 3, "1");

            auto result2 = i.findLast([](int& element){return true;});
            True(result2.value() == 4, "2");

            auto result3 = i.findLast([](int& element){return false;});
            LTAssert::False(result3.isEngaged(), "3 (shouldnt be engaged)");

            i.findLast([](int& element){return element == 1;}).value() = 20;
            LTAssert::False(i.front() == 20, "4 (value wasnt seted)");
            LTAssert::True(i.get(1).value() == 20, "5");

            i = LinkedList<int>(1,1,3,4);

            i.findLast([](int& element){return true;}).value() = 40;
            True(i.get(3).value() == 40);
        }),

        ltest().addTest("LinkedList::get()", [](){
            LinkedList<int> l(0,1,2,3,4);
            for(int i = 0; i<5; i++){
                LTAssert::True(l.get(i).value() == i, "simple get");
            }

            for(int i = 0; i<5; i++){
                l.get(i).value() = 2*i;
            }

            for(int i = 0; i<5; i++){
                LTAssert::True(l.get(i).value() == 2*i, "reference not setted");
            }

            LTAssert::ExpectException<std::logic_error>([&](){l.get(20).value();}, "missing error");
            LTAssert::ExpectException<std::logic_error>([&](){l.get(5).value();}, "missing error");
        }),

        ltest().addTest("LinkedList::findAllCopy()", [](){
            LinkedList<int> l(1,2,3,4,5,6);
            LinkedList<int> even = l.findAllCopy([](int& i){return i%2 == 0;});
            LinkedList<int> odd = l.findAllCopy([](int& i){return i%2 != 0;});
            LinkedList<int> all = l.findAllCopy([](int& i){return true;});
            LinkedList<int> none = l.findAllCopy([](int& i){return false;});
            True(even != odd && even != all && even != none && odd != all && odd != none);
            True(even == LinkedList<int>(2,4,6));
            True(odd == LinkedList<int>(1,3,5));
            True(all == LinkedList<int>(1,2,3,4,5,6));
            True(none == LinkedList<int>());
            even.get(0).value() = 5;
            LTAssert::False(l.get(2).value() == 5);
        }),

        ltest().addTest("LinkedList::findAll()", [](){
            LinkedList<int> l(1,2,3,4,5,6);
            LinkedList<int*> even = l.findAll([](int& i){return i%2 == 0;});
            LinkedList<int*> odd = l.findAll([](int& i){return i%2 != 0;});
            LinkedList<int*> all = l.findAll([](int& i){return true;});
            LinkedList<int*> none = l.findAll([](int& i){return false;});

            True(even != odd && even != all && even != none && odd != all && odd != none);

            True(even == LinkedList<int*>(&(l.get(1).value()), &(l.get(3).value()), &(l.get(5).value())), "1");
            True(odd == LinkedList<int*>(&(l.get(0).value()), &(l.get(2).value()), &(l.get(4).value())), "2");
            True(all == LinkedList<int*>(&(l.get(0).value()),&(l.get(1).value()),&(l.get(2).value()),&(l.get(3).value()),&(l.get(4).value()), &(l.get(5).value())), "3");
            True(none == LinkedList<int*>(), "4");

            *(even.get(0).value()) = 50;
            LTAssert::True(l.get(1).value() == 50, "5");
        }),

        ltest().addTest("LinkedList::any()", [](){
            LinkedList<int> l(1,2,3,4,5,6);

            True(l.any([](int& i){ return i == 3; }));
            True(l.any([](int& i){ return i >= 1 && i <= 6; }));
            False(l.any([](int& i){ return i == 8; }));
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
            ArrayList<int> i(1,1,3,4);
            auto result1 = i.findFirst([](int& element){return element == 3;});
            True(result1.value() == 3, "1");

            auto result2 = i.findFirst([](int& element){return true;});
            True(result2.value() == 1, "2");

            auto result3 = i.findFirst([](int& element){return false;});
            LTAssert::False(result3.isEngaged(), "3 (shouldnt be engaged)");

            i.findFirst([](int& element){return true;}).value() = 20;
            True(i.front() == 20, "4 (value wasnt seted");

            i = ArrayList<int>(1,1,3,4);

            i.findFirst([](int& element){return element == 1;}).value() = 30;
            True(i.front() == 30, "5 (value wasnt seted)");
        }),

        ltest().addTest("ArrayList::findLast()", [](){
            ArrayList<int> i(1,1,3,4);
            auto result1 = i.findLast([](int& element){return element == 3;});
            True(result1.value() == 3, "1");

            auto result2 = i.findLast([](int& element){return true;});
            True(result2.value() == 4, "2");

            auto result3 = i.findLast([](int& element){return false;});
            LTAssert::False(result3.isEngaged(), "3 (shouldnt be engaged)");

            i.findLast([](int& element){return element == 1;}).value() = 20;
            LTAssert::False(i.front() == 20, "4 (value wasnt seted)");
            LTAssert::True(i.get(1).value() == 20, "5");

            i = ArrayList<int>(1,1,3,4);

            i.findLast([](int& element){return true;}).value() = 40;
            True(i.get(3).value() == 40);
        }),

        ltest().addTest("ArrayList::get()", [](){
            ArrayList<int> l(0,1,2,3,4);
            for(int i = 0; i<5; i++){
                LTAssert::True(l.get(i).value() == i, "simple get");
            }

            for(int i = 0; i<5; i++){
                l.get(i).value() = 2*i;
            }

            for(int i = 0; i<5; i++){
                LTAssert::True(l.get(i).value() == 2*i, "reference not setted");
            }

            LTAssert::ExpectException<std::logic_error>([&](){l.get(20).value();}, "missing error");
            LTAssert::ExpectException<std::logic_error>([&](){l.get(5).value();}, "missing error");

        }),

        ltest().addTest("ArrayList::findAllCopy()", [](){
            ArrayList<int> l(1,2,3,4,5,6);
            LinkedList<int> even = l.findAllCopy([](int& i){return i%2 == 0;});
            LinkedList<int> odd = l.findAllCopy([](int& i){return i%2 != 0;});
            LinkedList<int> all = l.findAllCopy([](int& i){return true;});
            LinkedList<int> none = l.findAllCopy([](int& i){return false;});
            True(even != odd && even != all && even != none && odd != all && odd != none);
            True(even == LinkedList<int>(2,4,6));
            True(odd == LinkedList<int>(1,3,5));
            True(all == LinkedList<int>(1,2,3,4,5,6));
            True(none == LinkedList<int>());
            even.get(0).value() = 5;
            LTAssert::False(l.get(2).value() == 5);
        }),

        ltest().addTest("ArrayList::findAll()", [](){
            ArrayList<int> l(1,2,3,4,5,6);
            LinkedList<int*> even = l.findAll([](int& i){return i%2 == 0;});
            LinkedList<int*> odd = l.findAll([](int& i){return i%2 != 0;});
            LinkedList<int*> all = l.findAll([](int& i){return true;});
            LinkedList<int*> none = l.findAll([](int& i){return false;});

            True(even != odd && even != all && even != none && odd != all && odd != none);

            True(even == LinkedList<int*>(&(l.get(1).value()), &(l.get(3).value()), &(l.get(5).value())), "1");
            True(odd == LinkedList<int*>(&(l.get(0).value()), &(l.get(2).value()), &(l.get(4).value())), "2");
            True(all == LinkedList<int*>(&(l.get(0).value()),&(l.get(1).value()),&(l.get(2).value()),&(l.get(3).value()),&(l.get(4).value()), &(l.get(5).value())), "3");
            True(none == LinkedList<int*>(), "4");

            *(even.get(0).value()) = 50;
            LTAssert::True(l.get(1).value() == 50, "5");
        }),

        ltest().addTest("ArrayList::any()", [](){
            ArrayList<int> l(1,2,3,4,5,6);

            True(l.any([](int& i){ return i == 3; }));
            True(l.any([](int& i){ return i >= 1 && i <= 6; }));
            False(l.any([](int& i){ return i == 8; }));
        })

};


#endif //__LListTest_H_

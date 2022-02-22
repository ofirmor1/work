#include "mu_test.h"
#include <algorithm>
#include "ball.hpp"
#include "single_list.hpp"
#include "single_list.hxx"


using namespace cpp;

BEGIN_TEST(add_remove_items)
        LinkedList<int> l;
        ASSERT_THAT(l.isEmpty() == true);
        l.addFirst(1);
        l.addFirst(3);
        l.addFirst(5);
        l.printList();
        printf("LIST size: %ld\n\n" , l.size());
        ASSERT_EQUAL(l.size(),  3);
        ASSERT_THAT(l.isEmpty() == false);
        for(int i = l.size() - 1; i >= 0; i --)
        {
			l.remove();
			ASSERT_EQUAL((int)l.size(),  i);
        }
		ASSERT_THAT(l.isEmpty() == true);

END_TEST


BEGIN_TEST(test_copy)
        LinkedList<int> a;
        LinkedList<int> b;
        // LinkedList c;
        int i = 1;
        while(i < 3)
        {
            a.addFirst(i);
            i++;
        }
        ASSERT_EQUAL(a.size(), 2);
        b = a;
        ASSERT_EQUAL(b.size(), 2);
        ASSERT_EQUAL(b.first(), a.first());
        ASSERT_EQUAL(b.last(), a.last());
END_TEST


BEGIN_TEST(iterate_over_empty_list_test)
    LinkedList<int> list;
    ListItr<int> itr = list.begin();
    ListItr<int> end = list.end();
    ASSERT_THAT(itr.equal(end));
END_TEST


BEGIN_TEST(iterate_over_not_empty_list_test)
    LinkedList<int> list;
    int data;
    for(int i = 1; i < 10; i++)
    {
        list.addFirst(i);
    }
    int r = 9;
    for(ListItr<int> itr = list.begin(); itr.notEqual(list.end()); itr = itr.next())
    {

        data = itr.getData();
        printf(" data %d\n", data);
        ASSERT_EQUAL(data, r--);
    }
END_TEST


BEGIN_TEST(test_contains)
    LinkedList<int> list;
    for(int i = 1; i < 10; i++)
    {
        list.addFirst(i);
    }
    ASSERT_THAT(list.contains(1));
    ASSERT_THAT(list.contains(9));

END_TEST


BEGIN_TEST(iterator_operators_test)
    const size_t N = 1000;
    LinkedList<int> list;

    for(size_t i = 1; i < N; i++)
    {
        list.addLast(i);
    }



    ListItr<int> it = list.begin();
    ListItr<int> end = list.end();

    int e = *it;
    int i = e;
    while(it != end){
        ASSERT_EQUAL(*it++, i++);
    }

    it = list.begin();
    it++;
    ASSERT_EQUAL(*it, 2);

    int data = *it++;
    ASSERT_EQUAL(data, 2);
    ASSERT_EQUAL(*it, 3);

    data = *++it;
    ASSERT_EQUAL(data, 4);
    ASSERT_EQUAL(*it, 4);

END_TEST


struct BallFancyComp {
    BallFancyComp(int t) : threshold(t) {}
    bool operator()(Ball const& b) const{
        int r = b.getRadius();
        return r % 2 == 0 &&  r > threshold;
    }
private:
    int threshold;
};

BEGIN_TEST(find_if_test)
    const size_t N = 1000;
    LinkedList<Ball> list;

    for(size_t i = 0; i < N; i+=22)
    {
        list.addLast(Ball("red", i));
    }

    ListItr<Ball> it = list.begin();


    Ball b = *it;
    ASSERT_EQUAL(b.getRadius(), 0);

    //ASSERT_EQUAL((*it).getColor(), "red");
    const char* c = (*it).getColor();
    ASSERT_EQUAL_STR(c, "red");
    ++it;
    int r = it++->getRadius();
    ASSERT_EQUAL(r, 22);

    ListItr<Ball> end = list.end();
    it = std::find_if(list.begin(), list.end(), BallFancyComp(23));
    ASSERT_THAT(it != end);
    TRACE(*it);

    it = std::find_if(list.begin(), list.end(), BallFancyComp(51));
    ASSERT_THAT(it != end);
    TRACE(*it);

    it = std::find_if(list.begin(), list.end(), BallFancyComp(98978));
    ASSERT_THAT(it == end);


    ASSERT_PASS();
END_TEST


BEGIN_SUITE(single_linked_list_tests)
    TEST(add_remove_items)
    TEST(test_copy)
    TEST(iterate_over_empty_list_test)
    TEST(iterate_over_not_empty_list_test)
    TEST(test_contains)
    TEST(iterator_operators_test)
    TEST(find_if_test)
END_SUITE

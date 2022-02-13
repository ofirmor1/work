#include "mu_test.h"
#include "single_list.hpp"
#include "single_list.hxx"

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
//code review - check begin & end . works fine for(1..10) but fail on (0..10)

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


BEGIN_SUITE(single_linked_list_tests)
    TEST(add_remove_items)
    TEST(test_copy)
    TEST(iterate_over_empty_list_test)
    TEST(iterate_over_not_empty_list_test)
    TEST(test_contains)
END_SUITE
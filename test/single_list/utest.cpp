#include "mu_test.h"
#include "single_list.hpp"
#include "single_list.hxx"

BEGIN_TEST(test1)
        LinkedList l;
        ASSERT_THAT(l.isEmpty() == true);
        l.add(1);
        l.add(3);
        l.add(5);
        l.printList();
        printf("LIST size: %d\n\n" , l.size());
        ASSERT_EQUAL(l.size(),  3);
        ASSERT_THAT(l.isEmpty() == false);
        for(int i = l.size() - 1; i >= 0; i --)
        {
			l.remove();
			ASSERT_EQUAL(l.size(),  i);
        }
		ASSERT_THAT(l.isEmpty() == true);
        
END_TEST
//code review - check begin & end . works fine for(1..10) but fail on (0..10)

BEGIN_TEST(test_copy)
        LinkedList a;
        LinkedList b;
        // LinkedList c;
        for(int i = 1; i < 10; i++)
        {
            a.add(i);
        }
        ASSERT_THAT(a.size() == 9);
        b = a;
        ASSERT_THAT(b.size() == 9);
END_TEST

BEGIN_TEST(iterate_over_empty_list_test)
    LinkedList list;
    ListItr itr = list.begin();
    ListItr end = list.end();
    ASSERT_THAT(itr.equal(end));
END_TEST

BEGIN_TEST(iterate_over_not_empty_list_test)
    LinkedList list;
    int data;
    for(int i = 1; i < 10; i++)
    {
        list.add(i);
    }
    int r = 9;
    for(ListItr itr = list.begin(); itr.notEqual(list.end()); itr = itr.next())
    {
        
        data = itr.getData();
        printf(" data %d\n", data);
        ASSERT_EQUAL(data, r--);
    }
END_TEST



BEGIN_SUITE(single_linked_list_tests)
    TEST(test1)
    TEST(test_copy)
    // TEST(iterate_over_empty_list_test)
    // TEST(iterate_over_not_empty_list_test)
END_SUITE
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
BEGIN_TEST(test_itr)
        LinkedList list;
        int data;
        for(int i = 1; i < 10; i++)
        {
            list.add(i);
        }
        int r = 9;
        for(ListItr itr = list.begin(); !itr.equals(list.end()); itr = itr.next())
        {
            
            data = itr.get();
            printf(" data %d\n", data);
            ASSERT_EQUAL(data, r--);
        }
END_TEST

BEGIN_SUITE(single_linked_list_tests)
    TEST(test1)
    TEST(test_itr)

END_SUITE
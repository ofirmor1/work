#include "mu_test.h"
#include "single_list.hpp"
#include "single_list.hxx"

BEGIN_TEST(test1)
        LinkedList* l = new LinkedList();
        ASSERT_THAT(l->isEmpty() == true);
        l->add(1);
        l->add(3);
        l->add(5);
        l->printList();
        printf("LIST size: %d\n\n" , l->size());
        ASSERT_EQUAL(l->size(),  3);
        ASSERT_THAT(l->isEmpty() == false);
        for(int i = l->size() - 1; i >= 0; i --)
        {
			l->remove();
			ASSERT_EQUAL(l->size(),  i);
        }
		ASSERT_THAT(l->isEmpty() == true);


        delete[] l;
        
END_TEST


BEGIN_SUITE(single_linked_list_tests)
    TEST(test1)

END_SUITE
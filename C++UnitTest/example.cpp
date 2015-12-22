#define TEST_MAIN   // defined before include unittest.h
#include "unittest.h"

TEST_CASE(test)
{
    TEST_CHECK(1 == 1);
    TEST_CHECK(1 == 2, "Just test", 1, " == ", 2);
    TEST_CHECK(1 == 2, [](){
        std::cout << "Just test 1 == 2 for callable" << std::endl;
    });
    TEST_CHECK_STRING("str", "func");
    char str[] = "str";
    TEST_CHECK_STRING("str", str);
}
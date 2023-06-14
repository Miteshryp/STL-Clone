#include <criterion/criterion.h>
#include <criterion/logging.h>


#include "containers/stack.hpp"
// #include "./types/example.hpp"

using criterion::logging::info;
using criterion::logging::warn;
using criterion::logging::error;
using criterion::logging::log;


using test_type = int*;
pixel::stack<test_type> *s = NULL;




// Test functions

void suiteSetup() {
   s = new pixel::stack<test_type>();
}

void suiteCleanup() {
   delete s;
   // cr_assert(s == nullptr, "Deletion unsuccessful");
   // cr_fail(s != nullptr);
}

TestSuite(stacktests, .init=suiteSetup, .fini=suiteCleanup);

Test(stacktests, create) {
   bool valid = s != nullptr && s->size() == 0 && s->capacity() == PX_MIN_STACK_CAPACITY;
   cr_assert(valid == true, "stack creation unsuccessful");
   
   error << "Created\n" << std::endl;
   warn << "Warning\n" << std::endl;
   info << "Info\n" << std::endl;
}





// using namespace pixel;
// using namespace std;

// void test(stack<int> &s) {
//    cout << "Lvalue" << endl;
// }
// void test(stack<int> &&s) {
//    cout << "Rvalue" << endl;
// }

// int main() {
//    stack<int> s1;

//    s1.push(3);
//    s1.push(5);
//    s1.push(1);

//    test(s1);

   

//    stack<int> s2(s1);
//    cout << "TOP S1: " << s1.top() << endl;
//    cout << "TOP S2: " << s2.top() << endl;

//    cout << "------------\n";

//    cout << "POP S1: " << endl;
//    cout << s1.pop() << endl;
//    cout << s1.pop() << endl;

//    cout << "POP S2: " << endl;
//    cout << s2.pop() << endl;

//    cout << "------------\n";

//    cout << "S1 TOP: " << s1.top() << endl;
//    cout << "S2 TOP: " << s2.top() << endl;

//    cout << "End of Test\n";
// }
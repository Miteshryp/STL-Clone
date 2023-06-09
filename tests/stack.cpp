#include<iostream>
#include "containers/stack.hpp"

using namespace pixel;
using namespace std;

void test(stack<int> &s) {
   cout << "Lvalue" << endl;
}
void test(stack<int> &&s) {
   cout << "Rvalue" << endl;
}

int main() {
   stack<int> s1;

   s1.push(3);
   s1.push(5);
   s1.push(1);

   test(s1);

   

   stack<int> s2(s1);
   cout << "TOP S1: " << s1.top() << endl;
   cout << "TOP S2: " << s2.top() << endl;

   cout << "------------\n";

   cout << "POP S1: " << endl;
   cout << s1.pop() << endl;
   cout << s1.pop() << endl;

   cout << "POP S2: " << endl;
   cout << s2.pop() << endl;

   cout << "------------\n";

   cout << "S1 TOP: " << s1.top() << endl;
   cout << "S2 TOP: " << s2.top() << endl;

   cout << "End of Test\n";
}
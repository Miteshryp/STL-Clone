#include<iostream>
#include"./../containers/stack.hpp"

using namespace pixel;
using namespace std;

int main() {
   stack<int> s;

   s.push(3);
   s.push(5);
   s.push(1);

   cout << "TOP: " << s.top() << endl;

   cout << "POP: " << endl;
   cout << s.pop() << endl;
   cout << s.pop() << endl;

   cout << s.top() << endl;

   cout << "End of Test\n";
}
#pragma once 
#include <string>

class TestStructure {
   int m_a, m_b;
   float m_c;
   std::string m_s;
   

public:

   TestStructure(int a = 0, int b = 0, float c = 0.0f)
   //, std::string s = std::string(""))
      :
   m_a(a), m_b(b), m_c(c) //,m_s("")//, m_s(s)
   {
      // criterion::logging::info << "Constructor called" << std::endl;
      std::cout << "Created" << std::endl;
   }

   TestStructure(const TestStructure& test) 
      :
      m_a(test.m_a), m_b(test.m_b), m_c(test.m_c) {
      std::cout << "Lvalue constructor called\n";
   }

   TestStructure(TestStructure&& test)
      :
      m_a(test.m_a), m_b(test.m_b), m_c(test.m_c) 
   {
      std::cout << "Rvalue constructor called\n";
   }

   ~TestStructure() {
      // criterion::logging::info << "Test Structure destructor called: " << m_a << ", " << m_b << ", " << m_c << ", " << m_s << std::endl;
      std::cout << "destroyed" << std::endl;
   }



   void operator = (TestStructure&& test) {
      std::cout << "RVALUE operator called\n";

      m_a = test.m_a;
      m_b = test.m_b;
      m_c = test.m_c;
      m_s = test.m_s;

   }

   void operator = (const TestStructure& test) {
      std::cout << "LVALUE operator called\n";

      m_a = test.m_a;
      m_b = test.m_b;
      m_c = test.m_c;
      m_s = test.m_s;
   }


   int getA() const  { return m_a; }
   int getB() const  { return m_b; }
   float getC() const  { return m_c; }
   // std::string getS() const { return m_s; }
   
   
};
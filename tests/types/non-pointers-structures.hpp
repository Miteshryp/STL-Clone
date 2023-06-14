#pragma once 
#include <string>


using criterion::logging::warn;

class TestStructure {
   int m_a, m_b;
   float m_c;
   std::string m_s;

public:
   TestStructure() = delete;

   TestStructure(int a = 0, int b = 0, float c = 0.0f, std::string s = std::string(""))
      :
   m_a(a), m_b(b), m_c(c), m_s(s)
   {
      std::cout << "Constructor called" << std::endl;
   }

   ~TestStructure() {
      std::cout << "Test Structure destructor called: " << m_a << ", " << m_b << ", " << m_c << ", " << m_s << std::endl;
   }


   int getA() const  { return m_a; }
   int getB() const  { return m_b; }
   float getC() const  { return m_c; }
   std::string getS() const { return m_s; }
   
   
};
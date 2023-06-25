#include <iostream>
#include <criterion/criterion.h>

#include "./types/pointer-structures.hpp"
#include "./types/non-pointers-structures.hpp"
#include "containers/vector.hpp"


using criterion::logging::warn;
using criterion::logging::error;
using criterion::logging::info;

using namespace pixel::types;

class A {
public:
int k;

    A() {}

    virtual int sample() = 0;
    // {
    //     std::cout << "this is called\n";
    //     return k;
    // };
};

class B : public A {
public:

    B() = delete;// {}
    B(const int& k) {
        this->k = k;
        std::cout << "Deletion element pushed\n";
    }

    B(int&& k) {
        this->k = k;
        std::cout << "Rvalue element pushed\n";
    }

    int sample() {
        std::cout << "Called " << k << std::endl;
        return k;
    }

    bool operator == (const B& b) {
        std::cout << b.k << std::endl;
        return b.k == k;
    }
};


void suiteSetup() {
    info << "Setup complete\n";
}
void suiteCleanup() {
    info << "Cleanup complete\n";
}


TestSuite(vectorTestSuite, .init=suiteSetup, .fini=suiteCleanup);

Test(vectorTestSuite, memoryTest) {
    pixel::vector<A*> v;

    v.push(new B(3));
    v.push(new B(6));
    v.push(new B(7));

    // for(int i = 0; i < v.size(); i++) {
    //     v[i]->sample();
    //     std::cout << sizeof(*(v[i])) << std::endl;
    // }

    std::cout << sizeof(int*) << std::endl;
    std::cout << sizeof(A) << "\t" << sizeof(B) << std::endl;
    std::cout << sizeof(*(v[0])) << "\t" << sizeof(*(v[1])) << std::endl;
}


// pixel::vector<int> *int_vector = nullptr;
// pixel::vector<int *> *int_ptr_vector = nullptr;
// pixel::vector<TestStructure> *test_structure_vector = nullptr;
// pixel::vector<PointerStructure> *pointer_structure_vector = nullptr;


// void suiteSetup() {
//     int_vector = new pixel::vector<int>();
//     int_ptr_vector = new pixel::vector<int*>();
//     test_structure_vector = new pixel::vector<TestStructure>();
//     pointer_structure_vector = new pixel::vector<PointerStructure>();
// }

// void suiteCleanup() {
//     delete int_vector;
//     delete int_ptr_vector;
//     delete test_structure_vector;
//     delete pointer_structure_vector;
// }


// TestSuite(vectorTestSuite, .init=suiteSetup, .fini=suiteCleanup);


// Test(vectorTestSuite, create) {

//     cr_assert(int_vector != nullptr && int_vector->capacity() == 10,
//             "int_vector initialisation failed");
//     cr_assert(int_ptr_vector != nullptr && int_ptr_vector->capacity() == 10, 
//             "int_ptr_vector initialisation failed");
//     cr_assert(test_structure_vector != nullptr && test_structure_vector->capacity() == 10, 
//             "test_structure_vector initialisation failed");
//     cr_assert(pointer_structure_vector != nullptr && pointer_structure_vector->capacity() == 10, 
//             "pointer_structure_vector initialisation failed");

//     info << "Capacities:" 
//          << "\n int_vector: " << int_vector->capacity()
//          << "\n int_ptr_vector: " << int_ptr_vector->capacity()
//          << "\n test_structure_vector: " << test_structure_vector->capacity()
//          << "\n pointer_structure_vector: " << pointer_structure_vector->capacity() << std::endl;
// }


// Test(vectorTestSuite, pushnpopTest, .disabled=false) {
//     uint32 size = 15;

//     for(int i = 0; i < size; i++) {
//         pointer_structure_vector->push(PointerStructure(i, i+1));
//     }
//     cr_assert(pointer_structure_vector->size() == size, "Size does not match the pushed elements");
    
//     info << (*pointer_structure_vector)[2].getA() << (*pointer_structure_vector)[2].getB() << std::endl;
//     info << "vector capacity: " << pointer_structure_vector->capacity() << std::endl;
// }





// Test(vectorTestSuite, sizeCapacityTest) {
//     cr_expect(pointer_structure_vector->capacity() > pointer_structure_vector->size(), "Test failed to run as the pre-condition was not satisfied");

//     // Copying the vector state before the shrink operation
//     pixel::vector<PointerStructure> *copy_vector = new pixel::vector<PointerStructure>(*pointer_structure_vector);
//     cr_assert(copy_vector->size() == pointer_structure_vector->size() && copy_vector->capacity() == pointer_structure_vector->capacity(), "Copy operation failed");

//     // shriking the capacity of the original vector
//     pointer_structure_vector->shrink();

//     // checking if the shrink was statistically successful
//     cr_assert(pointer_structure_vector->size() == pointer_structure_vector->capacity(), "Shrink Failed");
//     cr_assert(copy_vector->size() < copy_vector->capacity(), "Copy_vector corrupted");

//     // Comparing value to check data integrity
//     for(uint32 i = 0; i < copy_vector->size(); i++) {
//         cr_assert((*copy_vector)[i].getA() == (*pointer_structure_vector)[i].getA(), "Value of %d is not the same", i);
//     }

//     info << "Shrink test successful" << std::endl;
// }




// Test(vectorTestSuite, initialiserList) {
//     // pixel::vector<int> v;
//     pixel::vector<TestStructure> v = {TestStructure(1,2), TestStructure(2,3)};
//     warn << "Creation Successful\n" << std::flush;
//     v.pop();

//     for(int i = 0; i < v.size(); i++)
//         info << v[i].getA() << " ";
    
//     info << std::endl;
// }

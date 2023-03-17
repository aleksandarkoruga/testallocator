// PluginTestAllocator.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "TestAllocator.hpp"
#include "SomeExternalClass.h"
#include <memory>

static InterfaceTable* ft;

namespace TestAllocator {
    
    //bInit is just a placeholder variable for the g_pWorld trick in double parenthesys call, so we initialize the externally referenced mWorld variable. 
    //m_vec is now allocated using the custom allocator which uses RTAlloc
TestAllocator::TestAllocator():bInit((memoryTranslation::g_pWorld=mWorld,true)), m_external(nullptr), m_vec(1000, 12.0f) {
    mCalcFunc = make_calc_function<TestAllocator, &TestAllocator::next>();
    

    //while the object itself is allocated using the custom allocator it's member vector uses the std::allocator. So external libraries' members are allocated using std
    auto a = memoryTranslation::RTAllocator<SomeExternalClass>();
    m_external = std::allocate_shared<SomeExternalClass>(a);
    std::shared_ptr<SomeExternalClass> otherInstance = std::allocate_shared<SomeExternalClass>(a);

}

void TestAllocator::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);
    //test local variable creation, destructor gets called when out of scope
    std::vector<float, memoryTranslation::RTAllocator<float>> vec(nSamples, 0.0f);
    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        vec[i] = input[i];
        outbuf[i] = input[i] * gain[i];
    }
    
}

} // namespace TestAllocator

PluginLoad(TestAllocatorUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<TestAllocator::TestAllocator>(ft, "TestAllocator", false);
}

// PluginTestAllocator.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "TestAllocator.hpp"

static InterfaceTable* ft;

namespace TestAllocator {

TestAllocator::TestAllocator() {
    mCalcFunc = make_calc_function<TestAllocator, &TestAllocator::next>();
    next(1);
}

void TestAllocator::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace TestAllocator

PluginLoad(TestAllocatorUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<TestAllocator::TestAllocator>(ft, "TestAllocator", false);
}

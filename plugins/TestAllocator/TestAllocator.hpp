// PluginTestAllocator.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace TestAllocator {

class TestAllocator : public SCUnit {
public:
    TestAllocator();

    // Destructor
    // ~TestAllocator();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace TestAllocator

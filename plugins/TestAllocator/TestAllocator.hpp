// PluginTestAllocator.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include <vector>
    
//externally referenced for RTAlloc in custom allocator
namespace memoryTranslation {

     World * g_pWorld; 
}

#include "AllocatorTranslation.h"
class SomeExternalClass;
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
    bool bInit;
    std::shared_ptr<SomeExternalClass> m_external;
    std::vector<float, memoryTranslation::RTAllocator<float>> m_vec;
};

} // namespace TestAllocator

#pragma once
#include <vector>

class SomeExternalClass
{
public:
	SomeExternalClass() :m_vec({0.0f,1.0f}),a(3) {};
	std::vector<float> m_vec;
	int a;
};
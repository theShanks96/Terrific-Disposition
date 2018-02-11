#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/SimpleBehaviour.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting{		
	TEST_CLASS(SimpleBehaviourTests)	{
	public:
		
		TEST_METHOD(BasicInitialisation)		{
			Behaviour* ptr_testedClassZero = new SimpleBehaviour();
			SimpleBehaviour m_testedClassOne = SimpleBehaviour();

			ptr_testedClassZero->c_nextPlotPoint = int2d(16, 32);
			m_testedClassOne.c_nextPlotPoint = int2d(16, 32);

			Assert::AreEqual(ptr_testedClassZero->c_nextPlotPoint.s_firstInt, m_testedClassOne.c_nextPlotPoint.s_firstInt, L"Different c_nextPlotPoint.s_firstInt");
			Assert::AreEqual(ptr_testedClassZero->c_nextPlotPoint.s_secondInt, m_testedClassOne.c_nextPlotPoint.s_secondInt, L"Different c_nextPlotPoint.s_secondInt");
		
		}

	};
}
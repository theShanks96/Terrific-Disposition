#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Terrific Disposition/ResourceManager.h"
#include "../Terrific Disposition/PythonManager.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TerrificTesting {
	TEST_CLASS(ResourceManagerTests) {
public:

	TEST_METHOD(ResourceManagerConstructor) {

		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");

		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_vulgarities.size(), L"Vulgarities not properly loaded");

		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_hostileAdjectives.size(), L"Hostile Adjective not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_hostileNouns.size(), L"Hostile Nouns not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_hostileVerbs.size(), L"Hostile Verbs not properly loaded");

		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_pleasantAdjectives.size(), L"Pleasant Adjectives not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_pleasantNouns.size(), L"Pleasant Nouns not properly loaded");
		Assert::AreNotEqual(0, (int)ptr_resourceManager->v_pleasantVerbs.size(), L"Pleasant Verbs not properly loaded");
	}

	};

	TEST_CLASS(PythonManagerTests) {
public:

	TEST_METHOD(PythonManagerConstructor) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");
		PythonManager* ptr_pythonManager = new PythonManager(ptr_resourceManager);

		Assert::AreEqual(16, ptr_pythonManager->c_vectorCapacityInt, L"PythonManager not correctly initialised");
		
	}

	TEST_METHOD(NLTKEntryProcessing) {
		ResourceManager* ptr_resourceManager = new ResourceManager("../../../Assets/AssetConfigurationTesting.json");
		PythonManager* ptr_pythonManager = new PythonManager(ptr_resourceManager);
		
		std::string m_stringTested = "Chocolate milk is delicious";
		commandProfile m_nltkTestResult = ptr_pythonManager->nltkEntryProcessing(m_stringTested);
		Assert::AreEqual(1, m_nltkTestResult.s_adjectivesInt, L"Incorrect adjective count");
		Assert::AreEqual(2, m_nltkTestResult.s_nounsInt, L"Incorrect noun count");
		Assert::AreEqual(1, m_nltkTestResult.s_verbsInt, L"Incorrect verb count");

		m_stringTested = "Spicy peppers give food a nice kick";
		m_nltkTestResult = ptr_pythonManager->nltkEntryProcessing(m_stringTested);
		Assert::AreEqual(1, m_nltkTestResult.s_adjectivesInt, L"Incorrect adjective count");
		Assert::AreEqual(4, m_nltkTestResult.s_nounsInt, L"Incorrect noun count");
		Assert::AreEqual(1, m_nltkTestResult.s_verbsInt, L"Incorrect verb count");
	}

	};

}
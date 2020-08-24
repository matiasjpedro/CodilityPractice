#pragma once
#include "UnitTesting/Testeable.h"

#pragma region ITesteable
#define EXTRA_TESTS_ENUM(DO) \
    DO(PalindromeString_Test) 

MAKE_LOGGABLE_ENUM(EXTRA_TESTS_ENUM, EExtraTests)
#pragma endregion

std::string PalindromeString(std::string& S) {

	const int Size = S.size();

	for (int i = 0; i < Size; i++)
	{
		const int OppositeSideIndex = (Size - 1) - i;

		char& ThisSideValue = S[i];
		const char& OppositeSideValue = S[OppositeSideIndex];

		if (ThisSideValue != '?' && OppositeSideValue != '?' && ThisSideValue != OppositeSideValue)
		{
			return "NO";
		}

		if (ThisSideValue == '?')
		{
			if (OppositeSideValue == '?')
			{
				S[i] = 'z';
				S[OppositeSideIndex] = 'z';
			}
			else
			{
				S[i] = S[OppositeSideIndex];
			}
		}
	}

	return S;
}

class TestExtra : public ITesteable<EExtraTests>
{
	bool RunTest(EExtraTests TestToRun) override
	{
		switch (TestToRun)
		{
		case EExtraTests::PalindromeString_Test:
		{
			std::string Test1 = "?ab??a";
			if (PalindromeString(Test1) != "aabbaa")
			{
				LastErrorStr = "Error with value: ?ab??a";
				return false;
			}

			std::string Test2 = "bab??a";
			if (PalindromeString(Test2) != "NO")
			{
				LastErrorStr = "Error with value: bab??a";
				return false;
			}

			std::string Test3 = "?a?";
			if (PalindromeString(Test3) != "zaz")
			{
				LastErrorStr = "Error with value: ?a?";
				return false;
			}

			return true;
		}
		default:
			break;
		}

		return true;
	}

};
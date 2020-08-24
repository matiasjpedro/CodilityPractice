#pragma once
#include "UnitTesting/Testeable.h"

#pragma region ITesteable
#define ITERATIONS_TESTS_ENUM(DO) \
    DO(BinaryGap_Test) 

MAKE_LOGGABLE_ENUM(ITERATIONS_TESTS_ENUM, EIterationTests)
#pragma endregion

int BinaryGap(int N)
{
	int StartGap = -1;
	int MaxGap = 0;
	for (int i = 0; i < 32; i++)
	{
		const int bitNumValue = (N >> i) & 1;
		if (bitNumValue == 1)
		{
			if (StartGap == -1)
			{
				StartGap = i;
			}
			//CloseGap
			else
			{
				if (i - (StartGap + 1) > MaxGap)
				{
					MaxGap = i - (StartGap + 1);
				}

				StartGap = i;
			}
		}
	}

	return MaxGap;
}

class TestIterations : public ITesteable<EIterationTests>
{
	bool RunTest(EIterationTests TestToRun) override
	{
		switch (TestToRun)
		{
		case EIterationTests::BinaryGap_Test:
		{
			if (BinaryGap(1041) != 5)
			{
				LastErrorStr = "Error with value: 1041";
				return false;
			}

			if (BinaryGap(32) != 0)
			{
				LastErrorStr = "Error with value: 32";
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
#pragma once
#include "UnitTesting/Testeable.h"
#include <vector>
#include <unordered_set>

#pragma region ITesteable
#define COUNTING_ELEMENTS_TESTS_ENUM(DO) \
    DO(FrogRiverOne_Test) \
	DO(MaxCounters_Test) \
	DO(MissingInteger_Test) \
	DO(PermCheck_Test) 

MAKE_LOGGABLE_ENUM(COUNTING_ELEMENTS_TESTS_ENUM, ECountingElementsTests)
#pragma endregion

int FrogRiverOne(int X, const std::vector<int>& A) {
	// write your code in C++14 (g++ 6.2.0)

	std::unordered_set<int> Steps = std::unordered_set<int>(X);
	int PossibleSteps = 0;

	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] <= X)
		{
			if (Steps.find(A[i]) == Steps.end())
			{
				Steps.insert(A[i]);
				PossibleSteps++;

				if (PossibleSteps == X)
				{
					return i;
				}
			}
		}

	}

	return -1;
}


std::vector<int> MaxCounters(int N, const std::vector<int>& A)
{
	std::vector<int> CountersVector = std::vector<int>(N);
	std::fill(CountersVector.begin(), CountersVector.end(), 0);
	int MaxCounter = 0;
	int MaxCounterSetted = 0;

	for (int i = 0; i < A.size(); i++)
	{
		const int Value = A[i];

		if (Value == N + 1)
		{
			MaxCounterSetted = MaxCounter;
		}
		else if (1 < Value < N)
		{
			int& Counter = CountersVector[Value - 1];

			if (Counter < MaxCounterSetted)
				Counter = MaxCounterSetted;

			Counter += 1;
			if (Counter > MaxCounter)
			{
				MaxCounter = Counter;
			}
		}
	}

	for (int i = 0; i < CountersVector.size(); i++)
	{
		int& Counter = CountersVector[i];
		if (Counter < MaxCounterSetted)
		{
			Counter = MaxCounterSetted;
		}
	}

	return CountersVector;
}

int MissingInteger(std::vector<int>& A)
{
	int LowerBound = std::numeric_limits<int>::max();
	int UpperBound = 0;

	//Get the bounds
	for (size_t i = 0; i < A.size(); i++)
	{
		const int Value = A[i];

		if (Value > 0)
		{
			if (Value > UpperBound)
			{
				UpperBound = Value;
			}

			if (Value < LowerBound)
			{
				LowerBound = Value;
			}
		}
	}

	if (LowerBound > 1)
		return 1;

	//Swap order it
	for (size_t i = 0; i < A.size(); i++)
	{
		const int Value = A[i];
		const int TargetIndex = Value - LowerBound;

		if (Value >= 0 && i != TargetIndex && TargetIndex < A.size())
		{
			if (A[i] == A[TargetIndex])
			{
				continue;
			}

			std::swap(A[i], A[TargetIndex]);

			// As we swap the value of A[i] we need to check again.
			i--;
		}
	}

	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] != LowerBound)
		{
			return A[i - 1] + 1;
		}
		else
		{
			LowerBound++;
		}
	}

	return UpperBound + 1;
}

int PermCheck(std::vector<int>& A)
{
	if (A.size() == 1)
		return A[0] == 1;

	int LowerBound = std::numeric_limits<int>::max();
	int UpperBound = 0;

	//Get the bounds
	for (size_t i = 0; i < A.size(); i++)
	{
		const int Value = A[i];

		if (Value > 0)
		{
			if (Value > UpperBound)
			{
				UpperBound = Value;
			}

			if (Value < LowerBound)
			{
				LowerBound = Value;
			}
		}
	}

	if (LowerBound > 1)
		return 0;

	//Swap order it
	for (size_t i = 0; i < A.size(); i++)
	{
		const int Value = A[i];
		const int TargetIndex = Value - LowerBound;

		if (Value >= 0 && i != TargetIndex && TargetIndex < A.size())
		{
			if (A[i] == A[TargetIndex])
			{
				continue;
			}

			std::swap(A[i], A[TargetIndex]);

			// As we swap the value of A[i] we need to check again.
			i--;
		}
	}

	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] != LowerBound)
		{
			return 0;
		}
		else
		{
			LowerBound++;
		}
	}

	return 1;
}

class TestCountingElements : public ITesteable<ECountingElementsTests>
{
	bool RunTest(ECountingElementsTests TestToRun) override
	{
		switch (TestToRun)
		{
		case ECountingElementsTests::FrogRiverOne_Test:
		{
			if (FrogRiverOne(5, {1,3,1,4,2,3,5,4}) != 6)
			{
				LastErrorStr = "Error with value: 5 | 1,3,1,4,2,3,5,4 ";
				return false;
			}

			return true;
		}
		case ECountingElementsTests::MaxCounters_Test:
		{
			if (MaxCounters(5, { 3,4,4,6,1,4,4 }) != std::vector({ 3, 2, 2, 4, 2 }))
			{
				LastErrorStr = "Error with value: 5 | 3,4,4,6,1,4,4 ";
				return false;
			}

			return true;
		}
		case ECountingElementsTests::MissingInteger_Test:
		{
			std::vector<int> Test1 = { 1, 3, 6, 4, 1, 2 };
			if (MissingInteger(Test1) != 5)
			{
				LastErrorStr = "Error with value: 1, 3, 6, 4, 1, 2 ";
				return false;
			}

			std::vector<int> Test2 = { 1,2,3 };
			if (MissingInteger(Test2) != 4)
			{
				LastErrorStr = "Error with value: 1,2,3 ";
				return false;
			}

			std::vector<int> Test3 = { -1, -3 };
			if (MissingInteger(Test3) != 1)
			{
				LastErrorStr = "Error with value: -1, -3 ";
				return false;
			}

			return true;
		}
		case ECountingElementsTests::PermCheck_Test:
		{
			std::vector<int> Test1 = { 4,1,3,2 };
			if (PermCheck(Test1) != 1)
			{
				LastErrorStr = "Error with value:  4,1,3,2  ";
				return false;
			}

			std::vector<int> Test2 = { 4,1,2 };
			if (PermCheck(Test2) != 0)
			{
				LastErrorStr = "Error with value:  4,1,3  ";
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

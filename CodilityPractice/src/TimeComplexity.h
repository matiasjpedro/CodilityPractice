#pragma once
#include "UnitTesting/Testeable.h"
#include <vector>
#include <unordered_set>

#pragma region ITesteable
#define TIME_COMPLEXITY_TESTS_ENUM(DO) \
    DO(FrogJmp_Test) \
	DO(PermMissingElem_Test) \
	DO(TapeEquilibrium_Test) 

MAKE_LOGGABLE_ENUM(TIME_COMPLEXITY_TESTS_ENUM, ETimeComplexityTests)
#pragma endregion

int FrogJmp(int X, int Y, int D) {

	// write your code in C++14 (g++ 6.2.0)
	const int Delta = Y - X;
	const double Steps = Delta / (double)D;

	return ceil(Steps);
}

int PermMissingElem(std::vector<int>& A) {
	// write your code in C++14 (g++ 6.2.0)

	int LowerBound = 1;
	int UpperBound = A.size();

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

int TapeEquilibrium(const std::vector<int>& A) {
	// write your code in C++14 (g++ 6.2.0)

	int Total = 0;

	for (size_t i = 0; i < A.size(); i++)
	{
		Total += A[i];
	}

	int MinorDifference = std::numeric_limits<int>::max();
	int Accumulated = 0;

	for (size_t i = 0; i < A.size() - 1; i++)
	{
		Accumulated += A[i];

		const int Delta = Total - Accumulated;

		const int Diff = std::abs(Accumulated - Delta);

		if (Diff < MinorDifference)
		{
			MinorDifference = Diff;
		}
	}

	return MinorDifference == std::numeric_limits<int>::max() ? 0 : MinorDifference;
}

class TestTimeComplexity : public ITesteable<ETimeComplexityTests>
{
	bool RunTest(ETimeComplexityTests TestToRun) override
	{
		switch (TestToRun)
		{
		case ETimeComplexityTests::FrogJmp_Test:
		{
			if (FrogJmp(10, 85, 30) != 3)
			{
				LastErrorStr = "Error with value: 10, 85, 30";
				return false;
			}

			return true;
		}
		case ETimeComplexityTests::PermMissingElem_Test:
		{

			std::vector<int> Test1 = { 2,3,1,5 };
			if (PermMissingElem(Test1) != 4)
			{
				LastErrorStr = "Error with value: 2,3,1,5";
				return false;
			}

			return true;
		}
		case ETimeComplexityTests::TapeEquilibrium_Test:
		{
			if (TapeEquilibrium({ 3,1,2,4,3 }) != 1)
			{
				LastErrorStr = "Error with value: 3,1,2,4,3";
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

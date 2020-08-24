#pragma once


#include "UnitTesting/Testeable.h"
#include <vector>
#include <unordered_set>

#pragma region ITesteable
#define ARRAYS_TESTS_ENUM(DO) \
    DO(CyclicRotation_Test) \
	DO(OddOccurrencesInArray_Test) \

MAKE_LOGGABLE_ENUM(ARRAYS_TESTS_ENUM, EArraysTests)
#pragma endregion

std::vector<int> CyclicRotation(std::vector<int>& A, int K)
{
	if (A.size() == 0)
	{
		return A;
	}

	for (int i = 0; i < K; i++)
	{
		const int LastValue = A.at(A.size() - 1);

		for (int j = A.size() - 1; j > 0; j--)
		{
			A.at(j) = A.at(j - 1);
		}

		A.at(0) = LastValue;
	}

	return A;
}

int OddOccurrencesInArray(const std::vector<int>& A) {

	std::unordered_set<int> MatchesMissing = std::unordered_set<int>((A.size() / 2) + 1);

	for (size_t i = 0; i < A.size(); i++)
	{
		if (MatchesMissing.find(A[i]) != MatchesMissing.end())
		{
			MatchesMissing.erase(A[i]);
		}
		else
		{
			MatchesMissing.insert(A[i]);
		}
	}

	return *MatchesMissing.begin();
}

class TestArrays : public ITesteable<EArraysTests>
{
	bool RunTest(EArraysTests TestToRun) override
	{
		switch (TestToRun)
		{
		case EArraysTests::CyclicRotation_Test:
		{
			std::vector<int> Test1 = { 3, 8, 9, 7, 6 };

			if (CyclicRotation(Test1, 3) != std::vector({ 9, 7, 6, 3, 8 }))
			{
				LastErrorStr = "Error with value: 3, 8, 9, 7, 6 | 3";
				return false;
			}

			std::vector<int> Test2 = { 0,0,0 };
			if (CyclicRotation(Test2, 1) != std::vector({ 0,0,0 }))
			{
				LastErrorStr = "Error with value: 0,0,0 | 1";
				return false;
			}

			std::vector<int> Test3 = { 1, 2, 3, 4 };
			if (CyclicRotation(Test3, 4) != std::vector({ 1, 2, 3, 4 }))
			{
				LastErrorStr = "Error with value: 1, 2, 3, 4 | 4";
				return false;
			}

			return true;
		}
		case EArraysTests::OddOccurrencesInArray_Test:
		{
			if (OddOccurrencesInArray({ 9,3,9,3,9,7,9 }) != 7)
			{
				LastErrorStr = "Error with value: 9,3,9,3,9,7,9";
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


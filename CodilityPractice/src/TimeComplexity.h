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

int PermMissingElem(const std::vector<int>& A) {
	// write your code in C++14 (g++ 6.2.0)

	if (A.size() == 0)
	{
		return 1;
	}

	const size_t VectorSize = A.size();

	if (VectorSize == 1)
	{
		const int FirstValue = A.at(0);
		return FirstValue > 1 ? FirstValue - 1 : FirstValue + 1;
	}

	std::unordered_set<int> Lookup;
	std::vector<int> Pendings;

	int MajorValue = 0;
	int MinorValue = std::numeric_limits<int>::max();

	for (const int& Element : A)
	{
		const int ValueToLookup = Element + 1;
		Lookup.insert(ValueToLookup);

		if (MajorValue < ValueToLookup)
		{
			MajorValue = ValueToLookup;
		}

		if (Element < MinorValue)
		{
			MinorValue = Element;
		}

		if (Lookup.find(Element) != Lookup.end())
		{
			Lookup.erase(Element);
		}
		else
		{
			Pendings.push_back(Element);
		}

	}

	// I'd like to not have the need to use this one
	for (const int& Element : Pendings)
	{
		if (Lookup.find(Element) != Lookup.end())
		{
			Lookup.erase(Element);
		}
	}

	//Maybe this is not needed
	if (Lookup.find(MajorValue) != Lookup.end())
	{
		Lookup.erase(MajorValue);
	}

	if (Lookup.size() > 0)
	{
		return *Lookup.begin();
	}

	return MinorValue > 1 ? MinorValue - 1 : MajorValue;
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

			if (PermMissingElem({2,3,1,5}) != 4)
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

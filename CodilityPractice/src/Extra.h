#pragma once
#include "UnitTesting/Testeable.h"

#pragma region ITesteable
#define EXTRA_TESTS_ENUM(DO) \
    DO(PalindromeString_Test) \
	DO(LargestSquareBranch_Test) \
	DO(MaxPointsWithoutDuplicates_Test)

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

int LargestSquareBranch(int A, int B)
{
	const int Sum = A + B;

	if (Sum < 4)
	{
		return 0;
	}
		
	const int MaxLargestBranchByB = B * 0.25;
	const int MaxLargestBranchByA = A * 0.25;

	if (MaxLargestBranchByB > A)
	{
		return MaxLargestBranchByB;
	}
	else if (MaxLargestBranchByA > B)
	{
		return MaxLargestBranchByA;
	}

	const int MaxLargestBranch = Sum * 0.25;
	const int AmountPossibleBranchesA = A / MaxLargestBranch;
	const int AmountPossibleBranchesB = B / MaxLargestBranch;
	const int bPossibleToFitLargestBranch = AmountPossibleBranchesA + AmountPossibleBranchesB  >= 4;

	if (bPossibleToFitLargestBranch)
		return MaxLargestBranch;

	if (A < B)
	{
		if (MaxLargestBranch > A || !bPossibleToFitLargestBranch)
		{
			int AmountOfBranchesNeeded = 4 - AmountPossibleBranchesB;
			float LargestABranch = A / AmountOfBranchesNeeded;

			return LargestABranch > MaxLargestBranchByB ? LargestABranch : MaxLargestBranchByB;
		}
	}
	else if (B < A)
	{
		if (MaxLargestBranch > B || !bPossibleToFitLargestBranch)
		{
			int AmountOfBranchesNeeded = 4 - AmountPossibleBranchesA;
			float LargestBBranch = B / AmountOfBranchesNeeded;

			return LargestBBranch > MaxLargestBranchByA ? LargestBBranch : MaxLargestBranchByA;
		}
	}

	return 0;
}

int GetRadioByIndex(const std::vector<int>& X, const std::vector<int>& Y, int Index)
{
	return std::max(std::abs(X[Index]), std::abs(Y[Index]));
}

int MaxPointsWithoutDuplicates(const std::string& S, const std::vector<int>& X, const std::vector<int>& Y)
{
	const int Size = S.size();

	int MaxRadio = 0;
	int ClampedMaxRadio = std::numeric_limits<int>::max();

	std::list<int> PointsOrderedByRadio;
	std::unordered_map<char, int> RadioByChar;

	for (int i = 0; i < Size; i++)
	{
		const char Tag = S[i];
		const int Radio = GetRadioByIndex(X, Y, i);

		auto Pair = RadioByChar.find(Tag);
		if (Pair != RadioByChar.end())
		{
			const int OtherRadio = Pair->second;
			const int MaxRadioBetweenMatch = std::max(Radio, OtherRadio);
			
			if (ClampedMaxRadio >= MaxRadioBetweenMatch)
			{
				ClampedMaxRadio = MaxRadioBetweenMatch;

				while (!PointsOrderedByRadio.empty() && GetRadioByIndex(X, Y, PointsOrderedByRadio.front()) >= ClampedMaxRadio)
				{
					PointsOrderedByRadio.pop_front();
				}

				MaxRadio = !PointsOrderedByRadio.empty() ? GetRadioByIndex(X, Y, PointsOrderedByRadio.front()) : 0;
			}
		}
		

		if (Radio >= ClampedMaxRadio)
			continue;

		if (Radio > MaxRadio)
		{
			MaxRadio = Radio;
			PointsOrderedByRadio.push_front(i);
			RadioByChar.emplace(Tag, Radio);
		}
		else
		{
			PointsOrderedByRadio.push_back(i);
			RadioByChar.emplace(Tag, Radio);
		}
	}


	return PointsOrderedByRadio.size();
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
		case EExtraTests::LargestSquareBranch_Test:
		{
			if (LargestSquareBranch(10, 21) != 7)
			{
				LastErrorStr = "Error with value: 10,21";
				return false;
			}

			if (LargestSquareBranch(13, 11) != 5)
			{
				LastErrorStr = "Error with value: 13, 11";
				return false;
			}

			if (LargestSquareBranch(2, 1) != 0)
			{
				LastErrorStr = "Error with value: 2, 1";
				return false;
			}

			if (LargestSquareBranch(1, 8) != 2)
			{
				LastErrorStr = "Error with value: 1, 8";
				return false;
			}

			return true;
		}

		case EExtraTests::MaxPointsWithoutDuplicates_Test:
		{
			if (MaxPointsWithoutDuplicates("ABDCA", { 2,-1,-4,-3,3 }, { 2,-2,4,1,-3 }) != 3)
			{
				LastErrorStr = "Error with value: ABDCA";
				return false;
			}

			if (MaxPointsWithoutDuplicates("ABB", { 1,-2,-2 }, { 1,-2, 2 }) != 1)
			{
				LastErrorStr = "Error with value: ABB";
				return false;
			}

			if (MaxPointsWithoutDuplicates("CCD", {1,-1,2 }, {1,-1,-2 }) != 0)
			{
				LastErrorStr = "Error with value: CCD";
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
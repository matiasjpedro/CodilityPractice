#pragma once
#include "UnitTesting/Testeable.h"
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>

#pragma region ITesteable
#define STACK_AND_QUEUE_TESTS_ENUM(DO) \
    DO(Brackets_Test) \
	DO(Fish_Test) \
	DO(Nesting_Test) \
	DO(StoneWall_Test) 

MAKE_LOGGABLE_ENUM(STACK_AND_QUEUE_TESTS_ENUM, EStackAndQueueTests)
#pragma endregion

int Brackets(const std::string& S)
{
	std::stack<char> Stack;
	std::unordered_map<char, char> BracketsMap = { {'(', ')'}, {'{', '}'},  {'[', ']'} };

	for (size_t i = 0; i < S.size(); i++)
	{
		const char Value = S[i];

		const auto FindResult = BracketsMap.find(Value);
		const bool bIsOpenBracket = FindResult != BracketsMap.end();
		if (bIsOpenBracket)
		{
			// Push the close bracket to know which bracket I'm waiting for.
			Stack.push(FindResult->second);
		}
		else
		{
			const bool bIsCloseBracketSpected = S[i] == Stack.top();
			if (bIsCloseBracketSpected)
			{
				Stack.pop();
			}
			else
			{
				for (const auto& Pair : BracketsMap)
				{
					// If we detect a closing brack which is not the one that we were specting then close it.
					if (Pair.second == S[i])
						return false;
				}
			}
		}
	}

	return Stack.size() == 0;
}

int Fish(const std::vector<int>& A, const std::vector<int>& B)
{
	std::queue<int> DownstreamQueue;
	int FishAlive = 0;

	for (size_t i = 0; i < B.size() && i < A.size(); i++)
	{
		// Going Down
		if (B[i] == 1)
		{
			FishAlive++;

			DownstreamQueue.push(A[i]);
		}
		//Going Up
		else
		{
			FishAlive++;

			bool bShouldCheckDownstreamFishes = DownstreamQueue.size() > 0;

			while (bShouldCheckDownstreamFishes)
			{
				const int FirstDownStreamFish = DownstreamQueue.front();
				if (FirstDownStreamFish < A[i])
				{
					FishAlive--;
					DownstreamQueue.pop();

					bShouldCheckDownstreamFishes = DownstreamQueue.size() > 0;
				}
				else
				{
					FishAlive--;
					bShouldCheckDownstreamFishes = false;
				}
			}
		}

	}

	return FishAlive;
}

int Nesting(const std::string& S)
{
	std::queue<char> Pendings;

	for (size_t i = 0; i < S.size(); i++)
	{
		if (S[i] == '(')
		{
			Pendings.push(')');
		}
		else if (S[i] == ')')
		{
			if (Pendings.size() == 0)
			{
				return 0;
			}
			else
			{
				Pendings.pop();
			}

		}
	}

	return Pendings.size() == 0;
}

int StoneWall(const std::vector<int>& H)
{
	std::stack<int> MyStack;
	int AmountBlocks = 0;

	for (size_t i = 0; i < H.size(); i++)
	{
		const int Value = H[i];

		if (MyStack.empty() || Value > MyStack.top())
		{
			AmountBlocks++;
			MyStack.push(Value);
			continue;
		}

		if (Value < MyStack.top())
		{
			i--;
			MyStack.pop();
		}
	}

	return AmountBlocks;
}

class TestStackAndQueue : public ITesteable<EStackAndQueueTests>
{
	bool RunTest(EStackAndQueueTests TestToRun) override
	{
		switch (TestToRun)
		{
		case EStackAndQueueTests::Brackets_Test:
		{
			if (Brackets("{[()()]}") != 1)
			{
				LastErrorStr = "Error with value: {[()()]}";
				return false;
			}

			if (Brackets("([)()]") != 0)
			{
				LastErrorStr = "Error with value: ([)()]";
				return false;
			}

			return true;
		}
		case EStackAndQueueTests::Fish_Test:
		{
			if (Fish({ 4,3,2,1,5 }, { 0,1,0,0,0 }) != 2)
			{
				LastErrorStr = "Error with value: 4,3,2,1,5 | 0,1,0,0,0";
				return false;
			}

			return true;
		}
		case EStackAndQueueTests::Nesting_Test:
		{
			if (Nesting("(()(())())") != 1)
			{
				LastErrorStr = "Error with value: (()(())())";
				return false;
			}

			if (Nesting("())") != 0)
			{
				LastErrorStr = "())";
				return false;
			}

			return true;
		}
		case EStackAndQueueTests::StoneWall_Test:
		{
			if (StoneWall({8,8,5,7,9,8,7,4,8}) != 7)
			{
				LastErrorStr = "Error with value: 8,8,5,7,9,8,7,4,8";
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

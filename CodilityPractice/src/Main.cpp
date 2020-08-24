#include "Iterations.h"
#include "Arrays.h"
#include "TimeComplexity.h"
#include "CountingElements.h"
#include "StackAndQueues.h"
#include "Extra.h"

int main()
{
	//TODO: Add to the result to the error msgs.

	TestIterations Iterations;
	Iterations.RunTests();

	TestArrays Arrays;
	Arrays.RunTests();

	TestTimeComplexity TimeComplexity;
	TimeComplexity.RunTests();

	TestCountingElements CountingElements;
	CountingElements.RunTests();

	TestExtra Extra;
	Extra.RunTests();

}

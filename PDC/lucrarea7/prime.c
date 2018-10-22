#include "stdio.h"
#include "stdlib.h"

int is_prime(unsigned long n)
{
	for (unsigned long i = 2; i < n; i++)
	{
		if (n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}



int main(int argc, char* argv[])
{
	unsigned long* numbers;
	unsigned long lStart, lEnd, failure, mult, len;

	if (argc != 3)
	{
		lStart = 1;
		lEnd = 100000;
	}
	else
	{
		lStart = atol(argv[1]);
		lEnd = atol(argv[2]);
	}

	if (lStart < 2) lStart = 2;
	if (lStart > lEnd) return 0;
	
	len = lEnd - lStart + 1;
	numbers = new unsigned long[len];

	unsigned int i;

	for (i = 0; i < len; i++)
	{
		numbers[i] = i + lStart;
	}

	for (i = 0; i < len; i++)
	{
		if (is_prime(numbers[i]) == 0)
		{
			numbers[i] = 0;
			mult = (i + lStart) * (i + lStart);
			while (mult - lStart <= len)
			{
				numbers[mult - lStart] = 0;
				mult += (i + lStart);
			}
		}
	}
	
	printf("Result:\n");
	for (i = 0; i < len; i++)
	{
		if (numbers[i] > 0)
		{
			printf("%d\n", i + lStart);
		}
	}
	delete[] numbers;
	failure = 0;
	return failure;
}
#include "Functions.h"

void max_area()	//n rows, m columns
{
	int M[MAX][MAX] = {
		{ 1, 0, 1, 1, 1 },
		{ 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 0 }
	};

	maxArea(M, 4, 5);
}

int maxArea(int M[MAX][MAX], int n, int m)	//n rows, m columns
{
	int area = maxHist(M[2],m);	//Row 0 area for initialisation (Area means Histogram Area)
	int max_area = area;

	for (int i = 1; i < n; i++)	//start from 1 since Row 0 area has already been stored in area for initialisation
	{
		for (int j = 0; j < m; j++)
		{
			if (M[i][j] == 1)
				M[i][j] += M[i - 1][j];
		}

		max_area = (max_area >= maxHist(M[i], m)) ? max_area : maxHist(M[i], m);
	}
	return max_area;
}

int maxHist(int M[], int m)	//m columns, also array length = m
{
	if (m < 1)
		return 0;
	
	int *stack = (int*)malloc(m*sizeof(int));
	if (!stack)
		return 0;

	memset(stack, -1, m*sizeof(int));	//memset with -1 as index can't be negative

	stack[0] = 0;	//will push index onto stack, not values i.e M[0] or so
	int top = 0;	//top = -1 means stack empty
	int area = M[stack[top]];	//if stack empty area = M[i]*i, else M[i]*(i-top-1)
	int max_area = area;

	int i = 1;
	while (i < m)
	{
		if (top < 0 || M[i] >= M[stack[top]])	//push index only, no need to check for area, update stack and update top
			stack[++top] = i++;

		else //means element is small i.e. histogram bar is lower than the previous one
		{
			//pop element and update area and check for max area till now, also do not increment 'i' as we need to pop till we get bar lower than current one or till stack gets empty
			int value = M[stack[top]];
			area = value * i;

			stack[top--] = -1;
			
			if (top >= 0)	//means stack is not empty
				area = value * (i - stack[top] - 1);

			max_area = max_area > area ? max_area : area;
			
		}
	}

	//now we need to empty whole stack as we have processed all elements of the array, and check if any other max area > max_area exists or not
	while (top >= 0)	//while stack does not gets empty, keep popping
	{
		int value = M[stack[top]];
		area = value * i;

		stack[top--] = -1;

		if (top >= 0)	//means stack is not empty
			area = value * (i - stack[top] - 1);

		max_area = max_area > area ? max_area : area;
	}

	return max_area;
}


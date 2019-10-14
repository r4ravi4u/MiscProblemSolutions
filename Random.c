#include "Functions.h"

void greycode()
{
	int N = 4;
	generateCode(N);
}

void generateCode(int N)
{
	//Logic : L1 : 0 & 1; L2 : 1 & 0 (reverse of L1), Prefix 0 in L1 and1 in L2 and union them as L1 and then L2
	
	if (N < 1)
		return;
	if (N == 1)
	{
		printf("0 1");
		return;
	}
		
	
	char **arr = (char**)malloc((pow(2, N))*sizeof(char *));	//no. of total elements in the final output will be 2^N
	if (!arr)
		return;

	for (int i = 0; i < pow(2, N); i++)	
	{
		arr[i] = (char *)malloc((N+1)*sizeof(char)); //each element will have N digits and +1 for last Null character

		if (!arr[i])
		{
			free(arr);
			return;
		}

		memset(&arr[i][N], 0, sizeof(char));
	}

	//initialising for N=1, as their will be only 2 elements and than it will start accumulating

	//L1
	arr[0][N-1] = '0';	//if N=4 from arr[0][0] to arr[0][3] i.e. 4 digits will come and arr[0][4] will contain Null termination
	arr[1][N-1] = '1';
	
	//L2
	arr[2][N - 1] = '1';
	arr[3][N - 1] = '0';

	for (int count = 1; count < N; count++)
	{
		int k = pow(2, count);
		for (int i = 0; i < k; i++)	//List L1
			arr[i][N - 1 - count] = '0';	//prefix 0
		
		for (int i = k; i < 2 * k; i++)	///List L2
			arr[i][N - 1 - count] = '1';	//prefix 1

		//for last iteration i.e. count = N-1, process finished, reverse not need to do
		if (count < N-1)	//then only reverse the list for next iteration
		{
			
			int l = 0;
			for (int i = (4 * k) - 1; i >= 2 * k; i--)
			{
				for (int j = 0; j < N; j++)
				{
					arr[i][j] = arr[l][j];
				}
				l++;
			}
		}
	}

	for (int i = 0; i < pow(2, N); i++)
	{
		printf("%s ", arr[i]);
	}

	//free the allocated memory, once all work done
	for (int i = 0; i < pow(2, N); i++)
	{
		if (arr[i])
			free(arr[i]);
	}

	if (arr)
		free(arr);
}

void permute(char *str, int start, int end)
{
	int i;
	if (start == end)
	{
		printf("%s\t\t", str);
		return;
	}
	for (i = start; i <= end; i++)
	{
		swap(str + start, str + i);
		permute(str, start + 1, end);
		swap(str + start, str + i);
	}

}

void swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void divby3()
{
	int pos, dec;
	pos = dec = 0; //position ; decimal equivalent
	char* s = "011010010110011201\0";
	char *s1, *ptr;
	ptr = s1 = s;
	while (*s)
	{
		if (*s != '0' && *s != '1')
		{
			printf("\n %c is Not a bin digit \n\n", *s);
			s++;
			continue;
		}

		if (*s == '0')
			dec = dec * 2;
		else
			dec = (dec * 2) + 1;

		s++;
		while (ptr != s)
		{
			if (*ptr == '0' || *ptr == '1')
				printf("%c", *ptr);
			ptr++;
		}

		if (dec % 3 == 0 && dec != 0)
			printf("\t\t%d\tBin no. divisible by 3\n", dec);
		else
			printf("\t\t%d\tNot divisible by 3\n", dec);

		ptr = s1;
	}
}
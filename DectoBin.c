#include "Functions.h"

#define maxsize 6

int DecToBin(int m, char *bin);
int geek()
{
	int t = 0;
	scanf_s("%d", &t);
	if (t < 1)
	{
		printf("Test Cases can't be less than 1\n");
		return 0;
	}


	for (int i = 0; i < t; i++)
	{
		int m = 0, k = 0, n = 0;
		scanf_s("%d%d%d", &m, &k, &n);

		if (m < 0 || k < 0 || n < 0)	//if k=0, kth digit does not exist
		{
			printf("m, n , k not proper\n");
			continue;
		}

		char bin[maxsize] = { -1, -1, -1, -1, -1, -1 };
		int digits = DecToBin(m, bin); //total no. of digits in binary equivalent;

		if (n == 0 && k > digits)
		{
			printf("k not proper\n");
			continue;
		}

		if (n == 0) // No iteration, and kth digit needs to be given from original bin only
		{
			printf("%c\n", bin[digits - (k+1)]);
			continue;
		}

		int max_digits = digits*pow(2, n);	//max digits that will be there after nth iteration

		if (k > max_digits)
		{
			printf("k not proper\n");
			continue;
		}

		int req_digits = (int)ceil((k+1) / pow(2, n));	//required digits to start with to get Kth digit after nth iteration. No need to process all the digits of the binary no.
		if (k == 0)
			req_digits = 1;

		char *s, *s1;	//s for odd iterations, s1 for even iterations

		s = (char *)malloc((k + 2)*sizeof(char));	//as we need kth digit only

		if (!s)
		{
			printf("Failed to allocate memory\n");
			continue;
		}

		s1 = (char *)malloc((k + 2)*sizeof(char));	//as we need kth digit only
		if (!s)
		{
			printf("Failed to allocate memory\n");
			if (s)
				free(s);
			continue;
		}

		memset(s, '\0', (k + 2)*sizeof(char));
		memset(s1, '\0', (k + 2)*sizeof(char));

		int index = 0, index1 = 0;
		for (int j = 0; j < req_digits && index <= k; j++)	//for first iteration as we need to take number from bin array and put it into s array
		{
			if (bin[digits-1] == 0)
			{
				s[index++] = '0';
				s[index++] = '1';
			}
			else
			{
				s[index++] = '1';
				s[index++] = '0';
			}
			digits--;
		}

		// Now s has the elements for next run i.e. 2nd iteration, s1 and s will be used alternatively for iterations

		for (int i = 2; i <= n; i++)
		{
			int count = 0;
			if (!(i % 2))	//for even iterations s1 filled from s
			{
				while (count < index && index1 <= k)
				{
					if (s[count++] == '0')
					{
						s1[index1++] = '0';
						s1[index1++] = '1';
					}
					else
					{
						s1[index1++] = '1';
						s1[index1++] = '0';
					}

				}
				index = 0;
			}
			else //for odd iterations s filled from s1
			{
				while (count < index1 && index <= k)
				{
					if (s1[count++] == '0')
					{
						s[index++] = '0';
						s[index++] = '1';
					}
					else
					{
						s[index++] = '1';
						s[index++] = '0';
					}

				}
				index1 = 0;
			}

		}
		if (n % 2)	//s kth index
			printf("%c\n", s[k]);
		else //s1 kth index
			printf("%c\n", s1[k]);

		if (s)
			free(s);
		if (s1)
			free(s1);

	}
	return 0;

}

int DecToBin(int m, char *bin)
{
	int rem = 0, i = 0;
	while (m)
	{
		bin[i++] = m % 2;
		m /= 2;
	}
	
	if (i == 0)
	{
		bin[0] = 0;
		return i + 1;
	}
	return i;	//from here bin no. starts ends at 0 index
}
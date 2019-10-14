/*
Given a fraction. Convert it into a decimal. So simple :P

eg.
10/2 = 5
3/5 = 0.6

(The Question Begins Now)  :D
If the decimals are repeating recursively, then enclose them inside  ().

eg.
8/3 = 2.(6)

as 8/3 = 2.66666666.......  infinitly.

1 ≤ T ≤ 100
1 ≤ N,D ≤ 2000

Logic : 
Rem = Rem*10;
if remainder at any point of time repeats, it means we have found our recurring sequence

Also special cases like 1/6 = 0.166666 .. Here sequence repeating from 2nd decimal point i.e. after 1, we need to take care

Also special case like 11/2 = 5.5 : No recurring sequence

*/
#include "Functions.h"

#include <math.h>
#define MAX 2001

void SimpleFractionUtil(int num, int den)
{
	char str[MAX];
	memset(str, 0, sizeof(str));

	int quot = num / den;
	int i = 3;	//since max it can be in terms of 10^3
	int index = 0;
	while (quot)
	{
		int x = quot / (pow(10, i));
		if (x)
		{
			str[index++] = x + '0';
			quot -= (x*pow(10, i));
		}
		i--;
	}

	if (!index)	//means its 0. Something
		str[index++] = '0';
	
	//Till here we got quotient part in str array, now time to check for remainder part
	
	str[index++] = '.';	//Decimal comes up as quotient is over

	int rem = num % den;

	int arr[MAX];	//to store index of decimal point to check if it already came or not ; 0 is useless
	memset(arr, 0, sizeof(arr));
	
	while (rem)
	{
		arr[rem] = index;
		rem *= 10;
		str[index++] = (rem / den) + '0';
		rem %= den;
		if (arr[rem])
			break;	//we found our rec. sequence
	}

	if (rem)
	{
		str[index + 1] = ')';
		while (index != arr[rem])
		{
			str[index] = str[index - 1];
			index--;
		}
		str[index] = '(';
	}

	printf("%s\n", str);
}

void SimpleFraction()
{
	FILE *fp = fopen("Test.txt", "r");
	int T;
	fscanf(fp, "%d", &T);
	while (T--)
	{
		int num, den;
		fscanf(fp, "%d %d", &num, &den);

		if (num % den == 0)
		{
			printf("%d\n", num / den);
			continue;
		}

		SimpleFractionUtil(num, den);

	}
	

	fclose(fp);
}
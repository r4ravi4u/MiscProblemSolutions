#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	//char c[256] = "000010101000101011111000011111000";
	char* s;
	char* c;
	int n = 0, i = 0, dec = 0;
	int* a; c = (char*)malloc(sizeof(char));
	a = (int*)malloc(sizeof(int));
	c = (char*)malloc(sizeof(char));
	s = (char*)malloc(sizeof(char));
	//("size of s : %d", sizeof(s));
	gets(c);
	printf("Enter Binary String : \n");
	c = (char*)realloc(c, strlen(c)*sizeof(char));
	s = c;
	while (*s != '\0')
	{
		if (*s == '1')
		{
			a[i] = n;
			i++;
			a = (int *)realloc(a, sizeof(int)*(i + 1));
		}
		s++;
		n++;
	}
	n--;
	i--;
	while (i >= 0)
	{
		dec += pow(2, n - a[i]);
		i--;
	}
	printf("Equivalent Decimal : %d\n", dec);
	free(a);
	free(c);
	//free (s);
}

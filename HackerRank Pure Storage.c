/*

*/

#include "Functions.h"

#define LEN 512000

int counting(char* s)
{
	int len = strlen(s);

	int res = 0;
	int last = 0;	
	int curr = 1;

	for (int i = 0; i < len-1; i++)
	{
		if (s[i] != s[i+1])
		{
			res += ((last < curr) ? last : curr);
			last = curr;
			curr = 1;
		}
		else 
			curr++;
	}
	return res + ((last < curr) ? last : curr);
}

void HackerRank()
{
	FILE *fp = fopen("test.txt", "r");

	int T;
	fscanf(fp, "%d", &T);
	char* s = (char *)malloc(LEN * sizeof(char));
	if (!s)
		return;

	while (T--)
	{
		fscanf(fp, "%s", s);

		int n = counting(s);

		printf("%d\n", n);

	}

	if (s)
	{
		free(s);
		s = NULL;
	}
	fclose(fp);
}
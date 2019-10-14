/*
All Pair Shortest Path.

1<=T<=20
1<=V<=20
-1000<=graph[][]<=1000


*/

#include "Functions.h"

void FloydWarshallUtil(int** G, int** T, int V)
{
	for (int k = 0; k < V; k++)
	{
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				if (G[i][j] > G[i][k] + G[k][j])
				{
					G[i][j] = G[i][k] + G[k][j];
					T[i][j] = T[k][j];
				}
			}
		}
	}

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			printf("%d ", G[i][j]);

		printf("\n");
}

void FloydWarshall()
{
	FILE *fp = fopen("Test.txt", "r");

	int N;
	fscanf(fp, "%d", &N);
	while (N--)
	{
		int V;	//V Vertex
		fscanf(fp, "%d", &V);

		if (V == 1)
		{
			int e;
			fscanf(fp, "%d", &e);
			printf("%d\n", e);
			continue;
		}

		//Build 2D Adjacency Matrix, rather than Adjacency List here, as ques is like that only
		int** G = (int **)malloc(sizeof(int*)*V);
		if (!G)
			return;

		for (int i = 0; i < V; i++)
		{
			G[i] = (int *)malloc(sizeof(int)*V);
			if (!G[i])
				return;

			memset(G[i], 0, sizeof(int)*V);
		}

		//Path Matrix T to fill column vertex comes from row vertex, however its like path[i][j] = path[k][j]
		int** T = (int **)malloc(sizeof(int*)*V);
		if (!T)
			return;

		for (int i = 0; i < V; i++)
		{
			T[i] = (int *)malloc(sizeof(int)*V);
			if (!T[i])
				return;

			memset(T[i], 0, sizeof(int)*V);
		}

		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				fscanf(fp, "%d", &G[i][j]);

				if (G[i][j] == 0)
					T[i][j] = -1;	//means NULL i.e not reachable from this particular vertex
				else
					T[i][j] = i;
			}
		}

		FloydWarshallUtil(G, T, V);

		//Free mem after usage

		if (T)
		{
			for (int i = 0; i < V; i++)
			{
				if (T[i])
				{
					free(T[i]);
					T[i] = NULL;
				}
			}
			free(T);
			T = NULL;
		}

		if (G)
		{
			for (int i = 0; i < V; i++)
			{
				if (G[i])
				{
					free(G[i]);
					G[i] = NULL;
				}
			}
			free(G);
			G = NULL;
		}
	}

	fclose(fp);
}
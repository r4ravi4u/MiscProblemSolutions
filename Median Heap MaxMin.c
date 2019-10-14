/*
Given an input stream of n integers the task is to insert integers to stream and print the median of the new stream formed by each insertion of x to the stream.

Example

Flow in stream : 5, 15, 1, 3
5 goes to stream --> median 5 (5)
15 goes to stream --> median 10 (5, 15)
1 goes to stream --> median 5 (5, 15, 1)
3 goes to stream --> median 4 (5, 15, 1, 3)

1<=N<=10^5+7
1<=x<=10^5+7

MaxHeap : mx = for lower half
MinHeap : mn = for upper half

if N is odd, then median = extract_max(mx)
if N is even, then median = extract_min(mn)
*/

#include "Functions.h"

//flag1 = 0 Insert ; 1 = Delete 
void heapify(int* arr, int start, int size, int flag, int flag1)	//flag = 1 means max heap, 0 means min heap
{
	if (flag1)	//Delete means Top to down
	{
		if (start > (size - 1) / 2)
			return;
	}
	else //Insert means bottom to up
	{
		if (start <= 0)
			return;
	}
	
	if (flag) //Max heap : Parent is greater than both its child
	{
		if (flag1) //means Delete top down
		{
			int left = 2 * start + 1 <= size ? 2 * start + 1 : 0;
			int right = 2 * start + 2 <= size ? 2 * start + 2 : 0;

			if (left && right)
			{
				if (arr[start] > arr[left] && arr[start] > arr[right])
					return;	//already heapified
				else
				{
					int temp = arr[start];
					if (arr[left] > arr[right])
					{
						//swap left & start & heapify
						arr[start] = arr[left];
						arr[left] = temp;
						heapify(arr, left, size, flag, flag1);
					}
					else
					{
						//swap right & start & heapify
						arr[start] = arr[right];
						arr[right] = temp;
						heapify(arr, right, size, flag, flag1);
					}
				}
			}
			else if (left) //this condition true means, its last node to be checked and right also does not exist
			{
				if (arr[start] > arr[left])
					return;
				else
				{
					int temp = arr[start];
					arr[start] = arr[left];
					arr[left] = temp;
					return;
				}
			}
		}
		else //means insert bottom up
		{
			int parent = (start - 1) / 2;

			if (parent < 0)
				return;

			if (arr[start] < arr[parent])
				return;	//already heapified
			else
			{
				//swap child & parent & heapify
				int temp = arr[start];
				arr[start] = arr[parent];
				arr[parent] = temp;
				heapify(arr, parent, size, flag, flag1);
			}
		}
	}
	else //Min Heap
	{
		if (flag1) //means Delete top down
		{
			int left = 2 * start + 1 <= size ? 2 * start + 1 : 0;
			int right = 2 * start + 2 <= size ? 2 * start + 2 : 0;

			if (left && right)
			{
				if (arr[start] < arr[left] && arr[start] < arr[right])
					return;	//already heapified
				else
				{
					int temp = arr[start];
					if (arr[left] < arr[right])
					{
						//swap left & start & heapify
						arr[start] = arr[left];
						arr[left] = temp;
						heapify(arr, left, size, flag, flag1);
					}
					else
					{
						//swap right & start & heapify
						arr[start] = arr[right];
						arr[right] = temp;
						heapify(arr, right, size, flag, flag1);
					}
				}
			}
			else if (left) //this condition true means, its last node to be checked and right also does not exist
			{
				if (arr[start] < arr[left])
					return;
				else
				{
					int temp = arr[start];
					arr[start] = arr[left];
					arr[left] = temp;
					return;
				}
			}
		}
		else //means insert bottom up
		{
			int parent = (start - 1) / 2;

			if (parent < 0)
				return;

			if (arr[start] > arr[parent])
				return;	//already heapified
			else
			{
				//swap child & parent & heapify
				int temp = arr[start];
				arr[start] = arr[parent];
				arr[parent] = temp;
				heapify(arr, parent, size, flag, flag1);
			}
		}
	}
}

int extract_Max(int* arr, int size)
{
	int temp = arr[0];
	arr[0] = arr[size];
	heapify(arr, 0, size-1, 1, 1);
	return temp;
}

int extract_Min(int* arr, int size)
{
	int temp = arr[0];
	arr[0] = arr[size];
	heapify(arr, 0, size-1, 0, 1);
	return temp;
}

void MedianStream()
{
	FILE *fp = fopen("Test.txt", "r");

	int N;
	fscanf(fp, "%d", &N);
	
	int* mx = (int*)malloc(sizeof(int)*((N / 2)+1));
	if (!mx)
		return;
	memset(mx, 0, sizeof(int)*((N / 2) + 1));

	int* mn = (int*)malloc(sizeof(int)*((N / 2) + 1));
	if (!mn)
		return;
	memset(mn, 0, sizeof(int)*((N / 2) + 1));

	int size_mx = -1;
	int size_mn = -1;

	//Index 0 will contain max and min elements of heap respectively
	
	for (int i = 1; i <= N;i++)
	{
		int x;
		fscanf(fp, "%d", &x);

		if (size_mx < 0)	//1st element into Max Heap
		{
			//insert into Max Heap : Lower Half
			mx[++size_mx] = x;
			printf("%d\n", mx[0]);
			continue;
		}
		
		else if (size_mn < 0)	//2nd element into Min Heap
		{
			//insert into Min Heap : Upper Half
			mn[++size_mn] = x;
			printf("%d\n", (mx[0] + mn[0])/2);

			//We need to check if mn[0] < mx[0], then it means that heaps shall be swapped
			if (mn[0] < mx[0])
			{
				//swap them
				int temp = mn[0];
				mn[0] = mx[0];
				mx[0] = temp;
			}

			continue;
		}

		else  //means here i >= 3
		{
			if (x <= mx[0])	//means it need to go in Max Heap for sure
			{
				if (size_mx > size_mn)	//at max difference will be 1 between them
				{
					//means we need to first extract_max from mx, push it to top of mn and then check for x
					mn[++size_mn] = extract_Max(mx, size_mx);	//in extract max we need to return mx[0] and then delete it from mx and then heapify it
					heapify(mn, size_mn, size_mn, 0, 0);
					size_mx--;					
				}
				mx[++size_mx] = x;
				heapify(mx, size_mx, size_mx, 1, 0);
			}
			
			else if (x >= mn[0])	//means it need to go in Max Heap for sure
			{
				if (size_mn > size_mx)	//at max difference will be 1 between them
				{
					//means we need to first extract_min from mn, push it to top of mx and then check for x
					mx[++size_mx] = extract_Min(mn, size_mn);	//in extract max we need to return mx[0] and then delete it from mx and then heapify it
					heapify(mx, size_mx, size_mx, 1, 0);
					size_mn--;
				}
				mn[++size_mn] = x;
				heapify(mn, size_mn, size_mn, 0, 0);
			}
			else //means x > mx[0] && x < mn[0], it shall be top of either heap
			{
				//it need to go into that heap whose size is smaller till now
				if (size_mx <= size_mn)
				{
					mx[++size_mx] = x;
					heapify(mx, size_mx, size_mx, 1, 0);
				}
				else
				{
					mn[++size_mn] = x;
					heapify(mn, size_mn, size_mn, 0, 0);
				}

			}
			

		}

		if (i % 2) //odd, hence mid element, either of size must be greater than other
		{
			if (size_mx > size_mn)
				printf("%d\n", mx[0]);
			else
				printf("%d\n", mn[0]);
		}

		else //average of min & max
			printf("%d\n", (mx[0] + mn[0]) / 2);

	}

	if (mx)
	{
		free(mx);
		mx = NULL;
	}

	if (mn)
	{
		free(mn);
		mn = NULL;
	}

	fclose(fp);
}
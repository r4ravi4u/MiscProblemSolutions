#include "Functions.h"

void points_line()
{
	int X[] = { 38, 26, 36, 16, 26, 41, 27, 28, 22, 9, 26, 15, 49, 4, 23 };
	int Y[] = { 17, 8, 32, 38, 8, 37, 26, 30, 44, 39, 1, 22, 42, 42, 44 };

	int N = sizeof(X) / sizeof(X[0]);

	printf("%d", maxPoints(X, Y, N));
}

int maxPoints(int X[], int Y[], int N)
{
	if (N < 2)
		return N;

	//make a line segment from 2 points and check every other point orientation w.r.t. to line segment
	int max = 0;
	for (int i = 0; i < N; i++)
	{
		point p, q;
		p.x = X[i];
		p.y = Y[i];

		for (int k = i+1; k < N; k++)
		{
			q.x = X[k];
			q.y = Y[k];

			int equal_count = 0;
			if (p.x == q.x && p.y == q.y)	//co-ordinates are equal
			{
				equal_count++;
				continue;
			}
				

			int count = 2;	//since 2 points will always be collinear
			for (int j = 0; j < N; j++)
			{
				if (j == i || j == k)
					continue;

				point r;
				r.x = X[j];
				r.y = Y[j];

				if ((p.x == r.x && p.y == r.y) || (q.x == r.x && q.y == r.y))	//co-ordinates are equal
				{
					equal_count++;
					continue;
				}

				if (!(orientation(p, q, r)))
					count++;
			}
			if (count == N)
				return count;
			max = (count + equal_count) > max ? (count + equal_count) : max;
		}
	}
	return max;
}

int orientation(point p, point q, point r)
{
	int dir = (q.y - p.y)*(r.x - q.x) - (r.y - q.y)*(q.x - p.x);	//dir for direction, collinear or clockwise or anticlockwise

	//0 for collinear, >0 clockwise, <0 anticlockwise

	if (dir == 0)
		return 0;

	return (dir > 0) ? 1 : 2;
}

void convex_hull()
{
	point points[] = { { 0, 3 }, { -2, 2 }, { -1, 1 }, { 2, 1 }, { 3, 0 }, { 0, 10 }, { 3, 3 } };

	point hull[sizeof(points) / sizeof(points[0])];
	
	int size = sizeof(points) / sizeof(points[0]);
	
	if (size < 3)
	{
		printf("Less than 3 points in the plane. Convex Hull not possible");
		return;
	}

	int start = 0, i;	//start for initial point for starting
	

	for (i = 1; i < size; i++)	//to get lowest 'x' co-ordinate in the points array
	{
		if (points[i].x < points[start].x)
			start = i;
	}

	int p = start, q;	//p for start, q for next best point
	int index = 0;

	do //atleast shud run 1 time
	{
		hull[index++] = points[p];
		q = (p+1)%size;	//modulus done to avoid boundary conditions i.e. q<0 or q>size
		for (i = 0; i < size; i++)
		{
			if (q != p && q != i && p!=i)
				if ((orientation(points[p], points[i], points[q]) == 2))	//capture anticlockwise
					q = i;
		}
		p = q;

	} while (p!= start);

	printf("Hull Contents : \n");
	for (i = 0; i < index ; i++)
		//if (hull[i].x > -100)
			printf("{ %d, %d }\n", hull[i].x, hull[i].y);
}

void intersect()
{
	point p1 = { 10, 0 }, q1 = { 0, 10 };
	point p2 = { 0, 0 }, q2 = { 10, 10 };

	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	//0 for collinear, >0 clockwise, <0 anticlockwise

	if (o1 != o2 && o3 != o4)	//general case
		printf("\nYES Line Segment Intersects\n");

	else if (o1 == 0 && onSegment(p1, p2, q1))	//p2 lies on p1q1
		printf("\nYES Line Segment Intersects\n");

	else if (o2 == 0 && onSegment(p1, q2, q1))	//q2 lies on p1q1
		printf("\nYES Line Segment Intersects\n");

	else if (o3 == 0 && onSegment(p2, p1, q2))	//p1 lies on p2q2
		printf("\nYES Line Segment Intersects\n");

	else if (o4 == 0 && onSegment(p2, q1, q2))	//q1 lies on p2q2
		printf("\nYES Line Segment Intersects\n");

	else
		printf("\nNO Line Segment does not intersect\n");

	
}

bool onSegment(point p, point q, point r)
{
	return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) ? true : false;
}
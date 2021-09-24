#include <iostream>
#include <random>
#include <queue>
using namespace std;

//#define DEBUG

#include "utils2d.h"


#ifdef DEBUG
int total = 0;
void* operator new(size_t n)
{
	total += n;
	cout << n << " bytes allocated\n";
	return malloc(n);
}
#endif // DEBUG


void fillArr2d(char** arr, int n, int m) 
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{ arr[i][j] = '*'; }
}

void randomFillArr2d(char** arr, int n, int m)
{
	random_device rd; mt19937 gen(rd());
	uniform_int_distribution<int> rand(0, 9);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			// approximately 40% chance
			if (rand(gen) >= 6) arr[i][j] = '*';
			else arr[i][j] = ' ';
		}
}

void coutArr2d(char** arr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{ cout << arr[i][j] << " "; }

		cout << "\n";
	}
}

void simpleFloodFill(char** arr, int n, int m, int x, int y)
{
	if (arr[x][y] == '*') return;
	else
	{
		arr[x][y] = '*';
		if (y < m - 1) simpleFloodFill(arr, n, m, x, y + 1);
		if (x < n - 1) simpleFloodFill(arr, n, m, x + 1, y);
		if (y > 0) simpleFloodFill(arr, n, m, x, y - 1);
		if (x > 0) simpleFloodFill(arr, n, m, x - 1, y);
	}
}

void simpleFloodFill2(char** arr, int n, int m, int x, int y)
{
	queue<int> q1, q2;
	q1.push(x); q2.push(y);
	while (!q1.empty() && !q2.empty())
	{
		int tx = q1.front(), ty = q2.front(); q1.pop(); q2.pop();
		if (arr[tx][ty] == '*') continue;
		else {
			arr[tx][ty] = '*';
			if (tx < n - 1) { q1.push(tx + 1); q2.push(ty); }
			if (ty < m - 1) { q1.push(tx); q2.push(ty + 1); }
			if (tx > 0) { q1.push(tx - 1); q2.push(ty); }
			if (ty > 0) { q1.push(tx); q2.push(ty - 1); }
		}
	}
}

char** getArr2d(int n, int m) 
{
	char** arr = new char* [n];
	for (int i = 0; i < n; i++)
	{ arr[i] = new char[m]; }

	return arr;
}

void cleanUp2d(char** arr, int n) 
{
	for (int i = 0; i < n; i++)
	{ delete[] arr[i]; }
	delete[] arr;
}

int main()
{
	int n, m;
	cout << "Enter two integer: quantity of rows and cols ";
	cin >> n >> m;
	
	char** arr = getArr2d(n, m);
	randomFillArr2d(arr, n, m);
	coutArr2d(arr, n, m);

	int x, y;
	cout << "Enter two coords (x and y) that implements of starting point for FloodFill: ";
	cin >> x >> y;
	simpleFloodFill2(arr, n, m, x, y);
	coutArr2d(arr, n, m);

	cleanUp2d(arr, n);
	return 0;
}
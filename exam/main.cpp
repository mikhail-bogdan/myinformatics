#include <iostream>
#include <stack>

int ** new_table(int N)
{
	int ** table = new int*[N];
	for (int i = 0; i < N; i++)
	{
		table[i] = new int[N];
		for (int j = 0; j < N; j++)
			table[i][j] = 0;
	}
	return table;
}

void delete_table(int * table, int N)
{
	delete[] table;
}

int is_free(int ** table, int i, int j)
{
	return table[i][j] == 0;
}

void set_queen(int ** table, int N, int i, int j)
{
	for (int a = 0; a < N; a++)
	{
		table[i][a] += 1;
		table[a][j] += 1;
	}
	
}

void queens(int * table, int N, int a)
{

	if (a >= N) return;
}

int main()
{
	int N = 8;
	int * table = new int[N];
	int * queens = new int[N];
	for (int i = 0; i < N; i++)
		queens[i] = 0;
	int i = 0, j = 0;
	delete_table(table, N);
}
#include<iostream>
#include<fstream>
#include<list>
#include<vector>

const int size = 4;

void find_joint(int graph[size][size])
{
	std::vector<int> path;
	int curr = 0, taken = 0;
	int visited[size];
	for (int i = 0; i < size; i++)
		visited[i] = 0;
	for (int i = 0; i < size; i++)
	{
		for (; curr != taken;)
		{
			path.push_back(curr);
			int found = -1;
			for(int j = 0; j < size; j++)
				if (i != j && graph[i][j] && !visited[j])
				{
					found = j;
				}

			if (found == -1)
			{
				curr = *path.end();
				path.pop_back();
			}

		}
	}
}

int main()
{
	int graph[size][size] =
	{
		0, 1, 0, 0,
		1, 0, 0, 1,
		0, 0, 0, 1,
		0, 1, 1, 0,
	};

	return 0;
}
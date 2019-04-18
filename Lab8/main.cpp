#include <iostream>
#include <vector>
#include "my_lab.h"

using namespace std;

int main()
{
	int sizeX, sizeY;
	cout << "Enter size X and size Y" << endl;
	cin >> sizeX;
	cin >> sizeY;
	Matrix matrix(sizeX, sizeY);

	cout << "Enter matrix " << sizeX << "x" << sizeY << endl;
	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
			cin >> matrix[i][j];

	vector<Point*> points;
	saddle_elements(matrix, &points);
	
	if (points.size() == 0) cout << "Not saddle elements" << endl;
	else
	{
		cout << "Result" << endl;
		int size = points.size();
		for(int i = 0; i < size; i++)
		{
			cout << "(" << points[i]->x + 1 << ", " << points[i]->y + 1 << ")" << endl;
		}
	}
	std::getchar();
	std::getchar();
	return 0;
}

/*
5 4 4 5 6
-2 1 3 7 7
8 2 -2 6 8
-2 3 3 7 7
8 4 4 6 8
*/
#include "my_lab.h"

void saddle_elements(Matrix &matrix, std::vector<Point*> * points)
{
	double min = 0, max = 0;
	char pos = 0, ip = 0;
	for (char i = 0; i < matrix.sizeX(); i++)
	{
		min = matrix[i][0];
		for (char j = 1; j < matrix.sizeY(); j++)
		{
			if (matrix[i][j] < min)
			{
				min = matrix[i][j];
			}
		}
		for (char j = 0; j < matrix.sizeY(); j++) {
			if (matrix[i][j] == min) {
				max = matrix[0][j];
				for (char k = 1; k < matrix.sizeX(); k++) {
					if (matrix[k][j] > max)
					{
						max = matrix[k][j];
					}
				}
				if (max == min) {
					points->push_back(new Point(i, j));
				}
			}
		}
	}
}

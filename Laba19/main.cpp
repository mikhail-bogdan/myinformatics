#include <iostream>
#include <list>

bool in_list(std::list<int>& list, int value)
{
	for(auto iter = list.begin(); iter != list.end(); iter++)
		if(*(iter))
			return false;
}

void recursive(int n, std::list<int>& list)
{
	if (n <= 0) return;
	for (int i = 0; i < n; i++)
	{
		if (in_list(list, i)) continue;
		std::cout << i;
		list.push_back(i);
		list

	}
}

int main()
{

	return 0;
}
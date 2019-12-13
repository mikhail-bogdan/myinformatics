#pragma once
#include<iostream>
#include<fstream>
#include<vector>


class Graph {
	std::vector<std::vector<int>> graph;
	std::vector<bool> was;

public:
	void fileRead(std::string filename);
	void filePrint(std::string filename);
	void search(int cur);
	void findAllVertex();
};
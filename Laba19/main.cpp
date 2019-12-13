#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include "graph.h"

int main()
{
	Graph graph;
	
	graph.fileRead("input.txt");
	graph.findAllVertex();
	graph.filePrint("graf1.txt");
	return 0;
}
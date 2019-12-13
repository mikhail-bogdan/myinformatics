#include "graph.h"
#include<string>
#include<sstream>

void Graph::fileRead(std::string filename) {
	std::ifstream fin(filename);
	std::vector<int> v_tmp;
	int tmp = 0;
	while (!fin.eof()) {
		std::string s;
		getline(fin, s);
		if (!s.empty()){
			std::istringstream iss(s);
			for (; iss.good();){
				iss >> tmp;
				v_tmp.push_back(tmp);
			}
		}
		graph.push_back(v_tmp);
		v_tmp.clear();
	}
	fin.close();
}

void Graph::search(int cur) {
	//if (cur == graph.size()) return;
	was[cur] = true;
	for (int i = 0; i < graph[cur].size(); ++i) {
		if (!was[graph[cur][i] - 1]) {     // if (!was[i]) {
			std::cout << graph[cur][i];
			search(graph[cur][i] - 1);     // search(graph[cur][i]);
			//return;
		}
	}
	//was[cur] = false;
	return;
}

void Graph::findAllVertex() {
	std::vector<bool> was_(graph.size(), false);
	for (int i = 0; i < graph.size(); ++i) {
		was = was_;
		std::cout << i+1 << " - ";
		search(i);
		std::cout << '\n';
	}
}

void Graph::filePrint(std::string filename) {
	std::ofstream fout(filename);
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			fout << graph[i][j] << ' ';
		}
		fout << '\n';
	}
	fout.close();
}
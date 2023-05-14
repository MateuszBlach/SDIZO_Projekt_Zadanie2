#pragma once
#include "ListEl.h"
#include<string>

using namespace std;

class Mst {
	int numberOfEdges;
	int numberOfVertices;
	int** matrix;
	ListEl** list;
	

public:
	Mst();
	~Mst();

	int manageMstMenu();
	void loadFromFile(string filePath);
	void generateRandom(int numberOfV, float density);

	void prim();
	void display();
};
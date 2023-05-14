#pragma once


using namespace std;

class ListEl {
public:
	int weight;
	int nextV;
	ListEl* next;
	ListEl(int weight);
};
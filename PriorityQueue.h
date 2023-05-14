#pragma once
#include<string>
#include "Edge.h"
using namespace std;

class PriorityQueue
{
	Edge* heapTab;
	int hpos;
public:

    PriorityQueue(int n);
    ~PriorityQueue();
    Edge front();
    void push(Edge e);
    void pop();

};
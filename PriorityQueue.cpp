#include "PriorityQueue.h"
#include <iostream>
#include <ctime>
#include "Random.h"


using namespace std;


PriorityQueue::PriorityQueue(int n) {
	heapTab = new Edge[n];         // Tworzymy tablicê
	hpos = 0;                      // Pozycja w kopcu
}

PriorityQueue::~PriorityQueue() {
	delete[] heapTab;
}

Edge PriorityQueue::front()
{
	return heapTab[0];
}

void PriorityQueue::push(Edge e)
{
	int i, j;

	i = hpos++;                    // i ustawiamy na koniec kopca
	j = (i - 1) >> 1;            // Obliczamy pozycjê rodzica

	// Szukamy miejsca w kopcu dla e

	while (i && (heapTab[j].weight > e.weight))
	{
		heapTab[i] = heapTab[j];
		i = j;
		j = (i - 1) >> 1;
	}

	heapTab[i] = e;                // KrawêdŸ e wstawiamy do kopca
}


void PriorityQueue::pop()
{
	int i, j;
	Edge e;

	if (hpos)
	{
		e = heapTab[--hpos];

		i = 0;
		j = 1;

		while (j < hpos)
		{
			if ((j + 1 < hpos) && (heapTab[j + 1].weight < heapTab[j].weight)) j++;
			if (e.weight <= heapTab[j].weight) break;
			heapTab[i] = heapTab[j];
			i = j;
			j = (j << 1) + 1;
		}

		heapTab[i] = e;
	}
}
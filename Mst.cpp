#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <ctime>
#include "Mst.h"
#include "ListEl.h"
#include "Random.h"
#include "PriorityQueue.h"

using namespace std;
using namespace std::chrono;

Mst::Mst() {
	numberOfVertices = 0;
}

Mst::~Mst() {
	if (numberOfVertices != 0) {
		for (int i = 0; i < numberOfVertices; i++) delete[] matrix[i];
		delete[] matrix;
		for (int i = 0; i < numberOfVertices; i++)
		{
			ListEl* p = list[i];
			while (p)
			{
				ListEl* r = p;
				p = p->next;
				delete r;
			}
		}
		delete[] list;
		numberOfVertices = 0;
	}
}

int Mst::manageMstMenu() {
	int choice, numberOfV;
	float density;
	string filePath;
	cin >> choice;
	switch (choice) {
		case 1:
			cout << "Podaj sciezke do pliku: ";
			cin >> filePath;
			loadFromFile(filePath);
			display();
			break;
		case 2:
			cout << "Podaj ilosc wierzcholkow: ";
			cin >> numberOfV;
			cout << "Podaj gestosc grafu: ";
			cin >> density;
			srand(time(NULL));
			generateRandom(numberOfV,density);
			display();
			break;
		case 3:
			display();
			break;
		case 4:
			prim();
			break;
		case 5:
			break;
		default:
			Mst::~Mst();
			break;
	}
	return choice;

}

void Mst::loadFromFile(string filePath) {
	ifstream  myFile(filePath);
	if (myFile.fail()) {
		cout << "Podano bledna sciezke do pliku!" << endl;
	}
	else {
		Mst::~Mst();
		myFile >> numberOfEdges >> numberOfVertices;

		matrix = new int* [numberOfVertices];  // Tworzymy tablicê wskaŸników
		for (int i = 0; i < numberOfVertices; i++) matrix[i] = new int[numberOfVertices]; // Tworzymy wiersz
		// Macierz wype³niamy zerami
		for (int i = 0; i < numberOfVertices; i++)
			for (int j = 0; j < numberOfVertices; j++) matrix[i][j] = 0;

		list = new ListEl * [numberOfVertices];
		for (int i = 0; i < numberOfVertices; i++) list[i] = NULL;


		for (int i = 0; i < numberOfEdges; i++) {
			int v1, v2, w;
			myFile >> v1 >> v2 >> w;
			matrix[v1][v2] = w;
			matrix[v2][v1] = w;

			// Dodaj element dla pierwszego wierzcho³ka
			ListEl* newEl1 = new ListEl(w);
			newEl1->next = list[v1];
			newEl1->nextV = v2;
			 [v1] = newEl1;

			// Dodaj element dla drugiego wierzcho³ka
			ListEl* newEl2 = new ListEl(w);
			newEl2->next = list[v2];
			newEl2->nextV = v1;
			list[v2] = newEl2;

		}
		myFile.close();
	}
}

void Mst::display() {
	cout << "   ";
	for (int i = 0; i < numberOfVertices; i++) cout << setw(3) << i;
	cout << endl;
	for (int i = 0; i < numberOfVertices; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < numberOfVertices; j++) cout << setw(3) << matrix[i][j];
		cout << endl;
	}

	for (int i = 0; i < numberOfVertices; i++)
	{
		cout << "list [ " << i << " ] =";
		ListEl * p = list[i];
		while (p)
		{
			cout << right << setw(2) << p->nextV << "|w:" << left << setw(2) << p->weight;
			p = p->next;
		}
		cout << endl;
	}

}

void Mst::generateRandom(int numberOfV, float density) {
	Mst::~Mst();

	float maxV = (numberOfV * (numberOfV - 1))/2;
	int noe;
	noe = floor((density / 100.0)* maxV);
	cout << "Number of edges " << noe << endl;

	numberOfVertices = numberOfV;
	numberOfEdges = noe;

	matrix = new int* [numberOfVertices];  // Tworzymy tablicê wskaŸników
	for (int i = 0; i < numberOfVertices; i++) matrix[i] = new int[numberOfVertices]; // Tworzymy wiersz
	// Macierz wype³niamy zerami
	for (int i = 0; i < numberOfVertices; i++)
		for (int j = 0; j < numberOfVertices; j++) matrix[i][j] = 0;

	list = new ListEl * [numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++) list[i] = NULL;

	int value;
	//utworzenie drzewa rozpinaj¹cego
	for (int i = 0; i < numberOfVertices - 1; i++) {
		value = generateRandomNumber(1, 40);
		matrix[i][i + 1] = value;
		matrix[i+1][i] = value;

		// Dodaj element dla pierwszego wierzcho³ka
		ListEl* newEl1 = new ListEl(value);
		newEl1->next = list[i];
		newEl1->nextV = i+1;
		list[i] = newEl1;

		// Dodaj element dla drugiego wierzcho³ka
		ListEl* newEl2 = new ListEl(value);
		newEl2->next = list[i+1];
		newEl2->nextV = i;
		list[i+1] = newEl2;
	}

	int v1, v2;
	//dodanie pozosta³ych krawêdzi
	for (int i = 0; i < numberOfEdges - (numberOfVertices - 1); i++) {
		//zabezpieczenie przed nadpisywaniem istniej¹cych juz krawedzi
		do {
			v1 = generateRandomNumber(0, numberOfVertices - 1);
			v2 = generateRandomNumber(0, numberOfVertices - 1);
		} while (matrix[v1][v2] != 0  || v1 == v2);

		value = generateRandomNumber(1, 40);
		matrix[v1][v2] = value;
		matrix[v2][v1] = value;

		// Dodaj element dla pierwszego wierzcho³ka
		ListEl* newEl1 = new ListEl(value);
		newEl1->next = list[v1];
		newEl1->nextV = v2;
		list[v1] = newEl1;

		// Dodaj element dla drugiego wierzcho³ka
		ListEl* newEl2 = new ListEl(value);
		newEl2->next = list[v2];
		newEl2->nextV = v1;
		list[v2] = newEl2;
	}
}

void Mst::prim() {
	//----ALGORYTM DLA MACIERZY S¥SIEDZTWA----
	//PriorityQueue pq = PriorityQueue();

	//przyjmujemy ze zaczynamy od wierzcholka o indeksie 0
	int* distances = new int[numberOfVertices];
	distances[0] = 0;
	for (int i = 1; i < numberOfVertices; i++) {
		distances[i] = 100;
	}

	bool* mstVertexes = new bool[numberOfVertices];
	//mstVertexes[0] = true;
	for (int i = 0; i < numberOfVertices; i++) {
		mstVertexes[i] = false;
	}

	int* mstParents = new int[numberOfVertices];
	mstParents[0] = -1;
	

	for (int i = 0; i < numberOfVertices - 1; i++) {
		//wybór najlepszego wierzcho³ka
		int minimum = 100;
		int vertex;
		for (int j = 0; j < numberOfVertices; j++) {
			if (mstVertexes[i] == false && distances[i] < minimum) {
				vertex = i;
				minimum = distances[i];
			}
		}
		mstVertexes[vertex] = true;

		//relaksacja wierzcho³ków
		for (int j = 0; j < numberOfVertices; j++) {
			if (matrix[vertex][j] != 0 && mstVertexes[j] == false && matrix[vertex][j] < distances[j]) {
				distances[j] = matrix[vertex][j];
				mstParents[j] = vertex;
			}
		}
	};

	//wyswietlenie mst
	int mstValue = 0;
	for (int i = 1; i < numberOfVertices; ++i) {
		cout << "U -> V: " << mstParents[i] << "->" << i << "  wt = " << matrix[mstParents[i]][i] << "\n";
		mstValue += matrix[mstParents[i]][i];
	}
	cout << "Wartoœæ mst: " << mstValue << endl;




	//pq.~PriorityQueue();
	//----ALGORYTM DLA LISTY S¥SIEDZTWA----
	//pq = PriorityQueue();

	//pq.~PriorityQueue();
}
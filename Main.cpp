#include <iostream>
#include "Mst.h"

using namespace std;

int mainMenuChoice;
int problemMenuChoice;

Mst mst;

void displayMainMenu();
void manageMainMenu();
void displayProblemMenu();

int main()
{
	do{
		displayMainMenu();
		manageMainMenu();
	} while (mainMenuChoice != 0);
	
}

void displayMainMenu() {
	cout << "Wybierz problem:" << endl;
	cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)" << endl;
	cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
	cout << "0. Zakoncz dzialanie programu" << endl;
	cout << "Wybor: ";
}

void manageMainMenu() {
	cin >> mainMenuChoice;
	switch (mainMenuChoice) {
		case 1:
			mst = Mst();
			do {
				displayProblemMenu();
				problemMenuChoice = mst.manageMstMenu();
			} while (problemMenuChoice != 0);
			mst.~Mst();
			break;
		case 2:
			do {
				displayProblemMenu();
			} while (problemMenuChoice != 0);
			break;
		default:
			break;
	}
}

void displayProblemMenu() {
	cout << "Wybierz dzia³anie:" << endl;
	cout << "1. Wczytaj z pliku" << endl;
	cout << "2. Wygeneruj losowo" << endl;
	cout << "3. Wyœwietl" << endl;
	cout << "4. Algorytm 1" << endl;
	cout << "5. Algorytm 2" << endl;
	cout << "0. Powrot do menu glownego" << endl;
	cout << "Wybor: ";
}






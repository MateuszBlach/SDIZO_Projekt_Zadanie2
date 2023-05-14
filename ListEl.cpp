#include "ListEl.h"
#include <stdio.h>

using namespace std;

ListEl::ListEl(int weight) {
	next = NULL;
	ListEl::weight = weight;
}
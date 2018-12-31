#include <iostream>
#include "abrsc.hpp"
#include <iostream>
#include <ctime>
#include <stdlib.h>


using namespace std;

void debug_1();

int main()
{
	srand(time(NULL));
	debug_1();
	return 0;
}


void debug_1()
{
	Tree<int> a;
	int val = 0;
	a.insert(5);
	a.insert(3);
	a.insert(4);

}






#include <iostream>
#include "tree.hpp"
#include <iostream>
#include <ctime>
#include <stdlib.h>


using namespace std;

void debug_ins_it();
void debug_1();

int main()
{
	srand(time(NULL));
	debug_1();
	return 0;
}


void debug_ins_it()
{

}


void debug_1()
{
	Tree<int> a;
	int val = 0;
	cout<<"Inserer une valeur: ";
	cin>>val;
	a.insert_it(val);
	a.print_infix();
	a.insert_it(98);
	a.insert_it(-23);
	a.insert_it(-23);
	a.print_infix();
	a.erase();
	a.print_infix();
	cout<<"Combien de valeur: ";
	cin>>val;
	for(int i=0; i<val; i++)
		a.insert_it(rand()%100);
	a.print_infix();
}






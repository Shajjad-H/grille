#include <iostream>
#include "avl.hpp"
#include <iostream>
#include <ctime>
#include <stdlib.h>


using namespace std;

void rotation_test();
void test_insertion();
void random_insert_test(const int val);



int main()
{
	srand(time(NULL));
	//rotation_test();
	//test_insertion();
	random_insert_test(50);


	return 0;
}

void random_insert_test(const int val)
{
	Avl<int> abr;
	for(int i=0; i<val; i++)
		abr.insert(rand()%(2*val));
	abr.print();
}

void test_insertion()
{
	Avl<int> abr;

	abr.insert(4);
	abr.insert(3);
	abr.print();
	cout<<"insert 1"<<endl<<"rotation right"<<endl;
	abr.insert(1);
	abr.print();

	cout<<"insert 6"<<endl;
	abr.insert(6);
	abr.print();
	cout<<"insert 7"<<endl<<"rotation left (4)"<<endl;
	abr.insert(7);
	abr.print();

	cout<<"insert 5"<<endl<<"double rotation left (3)"<<endl;
	abr.insert(5);
	abr.print();

	cout<<"insert 2"<<endl;
	abr.insert(2);
	abr.print();
	cout<<"insert 2"<<endl<<"double rotation right (3)"<<endl;
	abr.print();


}


void rotation_test()
{
	cout<<"start rotation_test"<<endl;
	Avl<int> abr;
	
	abr.insert(50);
	abr.insert(52);
	abr.insert(40);
	abr.insert(39);
	abr.insert(42);
	abr.insert(35);

	abr.print();
	cout<<"Right rotation"<<endl;
	abr.rotate_right();
	abr.print();

	/*abr.erase();
	abr.insert(50);
	abr.insert(40);
	abr.insert(60);
	abr.insert(55);
	abr.insert(70);
	abr.insert(66);
	abr.insert(76);

	abr.print();*/
	cout<<"Left rotation"<<endl;
	abr.rotate_left();
	abr.print();


	cout<<"end rotation_test"<<endl<<endl;
}
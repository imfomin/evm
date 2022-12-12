#include <iostream>
#include <fstream>
#include "list.hpp"

using namespace std;

int main() {
	ifstream in("list.txt");

	List list;
	in >> list;
	cout << list << endl;

	SortedList list1;
	List& _list = list1;
	in >> list1;
	cout << list1 << endl;

	return 0;
}
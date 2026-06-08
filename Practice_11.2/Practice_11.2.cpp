#include <iostream>
#include <string>
#include <functional>
#include "RBTree.h"
using namespace std;
int main() {
	int entryData[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
	11, 12, 13, 14, 15, 16 };
	int num_data = sizeof(entryData) / sizeof(int);
	int data;
	RBTree<int> intRBT;
	for (int i = 0; i < num_data; i++) {
		data = entryData[i];
		cout << "inserting " << data << " into intRBT" << endl;
		intRBT.insert(data);
		intRBT.printRBT();
	}
	cout << "intRBT inorder : ";
	intRBT.inorderPrint();
	cout << "\n===========================\n";
	cout << "Testing erases of RBT .....\n";
	for (int i = 0; i < num_data; i++) {
		data = entryData[i];
		intRBT.erase(data);
		cout << "After erase (" << data << ")\n";
		intRBT.printRBT();
		cout << endl;
	}
	return 0;
}
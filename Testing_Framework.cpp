#include "BST.h"
#include <iostream>

void main() {

	//BST* A = new BST(); // Construct BST so that object is stored in heap-allocated memory
	//A->loadFile();
	//
	//BST* B = BST(A);

	/*BST A;
	A.loadFile();
	BST B = BST(A);
	B.printEntries();*/

	BST A;
	A.loadFile();

	cout << A;

	getchar();
}
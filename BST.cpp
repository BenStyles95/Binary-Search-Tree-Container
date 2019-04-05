#include "BST.h"		// Include BST header
#include <fstream>		// Standard library
#include <iostream>		// Standard library
#include <sstream>		// Standard library
#include <string>		// Standard library
#include <vector>		// Standard library
#include <cassert>		// Standard library (Assertions)
using namespace std;	// Standard namespace

struct BST::Node {
	Key key;						// Node variable
	Item item;						// Node variable
	Node* leftChild = nullptr;		// Node variable
	Node* rightChild = nullptr;		// Node variable
	Node(Key, Item);				// Node constructor
};

BST::Node::Node(Key K, Item I) {	// Node constructor
	key = K;						// Initialise variable
	item = I;						// Initialise variable
}

void BST::insert(Key K, Item I) {
	insertWorker(K, I, root);
}

void BST::insertWorker(Key K, Item I, Node*& N) {
	if (N == nullptr) {
		N = new Node(K, I);
	}
	else if (N != nullptr) {
		if (K < N->key) {
			insertWorker(K, I, N->leftChild);
		}
		else if (K > N->key) {
			insertWorker(K, I, N->rightChild);
		}
		else if (K == N->key) {
			N->item = I;
		}
	}
}

BST::Item* BST::lookup(Key K) {
	Item* I = lookupWorker(K, root);
	return I;
}

BST::Item* BST::lookupWorker(Key K, Node* N) {
	if (N == nullptr) {
		return nullptr;
	}
	else if (N != nullptr) {
		if (K == N->key) {
			return &N->item;
		}
		else if (K < N->key) {
			lookupWorker(K, N->leftChild);
		}
		else if (K > N->key) {
			lookupWorker(K, N->rightChild);
		}
	}
}

void BST::loadFile() {
	loadFileWorker(root);	// Call loadFileWorker functiion
}

void BST::loadFileWorker(Node*& N) {
	ifstream file("Example.txt");			// Create file stream

	string current;							// Holds current line																	
	int lineCount = 0;						// Counter for amount of lines in file																		
	while (getline(file, current)) {		// While loop																							
		lineCount++;						// Increment counter																						
	}
	file.clear();							// Reset EOF flag for file stream																		
	file.seekg(0, ios::beg);				// Find the first line for file stream

	Key K = 0;								// Initialise variable to hold key 
	Item I = "";							// Initialise variable to hold item

	for (int i = 0; i < lineCount; i++) {	// Loop for inserting new nodes 
		getline(file, current, ' ');		// Get current line in buffer and stop at next space
		stringstream s(current);			// Convert string into int
		s >> K;								// Input int into K

		getline(file, current);				// Get other half of current line
		I = current;						// Make I equal to other half of current line
		insert(K, I);						// Call Insert function to insert new node
	}
}

void BST::printItem(Key K) {
	Item* I = lookup(K);

	assert(I != nullptr);

	if (I != nullptr) {
		cout << K << " " << *I << endl;
	}
}

void BST::printEntries() {

	vector<Node*> entries;
	printEntriesWorker(root, entries);

	// Print Entries
	for (int i = 0; i < entries.size(); i++) {
		printItem(entries[i]->key);
	}
}

vector<BST::Node*> BST::printEntriesWorker(Node* N, vector<Node*>& V) {
	if (N != nullptr)
	{
		printEntriesWorker(N->leftChild, V);
		V.push_back(N);
		printEntriesWorker(N->rightChild, V);
	}
	return V;
}

vector<string> BST::outputStreamWorker(Node* N, vector<string>& V, int I) {
	if (N == nullptr) {
		string temp;
		for (int i = 0; i < I; i++) {
			temp = temp + "\t";
		}
		temp = temp + "Leaf Node";
		V.push_back(temp);
	}
	else if (N != nullptr) {

		string temp;
		for (int i = 0; i < I; i++) {
			temp = temp + "\t";
		}

		temp = temp + "Level ";
		temp = temp + to_string(I);
		temp = temp + " Node: ";
		temp = temp + N->item;
		temp = temp + " - ";
		temp = temp + to_string(N->key);
		V.push_back(temp);
		I++;
		outputStreamWorker(N->leftChild, V, I);
		outputStreamWorker(N->rightChild, V, I);
	}
	return V;
}

std::ostream& operator << (std::ostream& os, const BST& bst) {

	vector<string> entries;

	BST::outputStreamWorker(bst.root, entries, 0);

	for (int i = 0; i < entries.size(); i++) {
		cout << entries[i] << endl;
	}

	return os;
}

void BST::remove(Key K) {
	removeWorker(K, root);
}

void BST::removeWorker(Key K, Node*& N) {
	if (N == nullptr) {

	}
	else if (N != nullptr) {
		if (K == N->key) {
			if (N->leftChild == nullptr && N->rightChild == nullptr) {			// Node being deleted has no child nodes
				delete N;
				N = nullptr;
			}
			else if (N->leftChild != nullptr && N->rightChild == nullptr) {		// Node being deleted has one child node on the left
				Node* tempN;
				tempN = N;
				N = N->leftChild;
				delete tempN;
			}
			else if (N->leftChild == nullptr && N->rightChild != nullptr) {		// Node being deleted has one child node on the right
				Node* tempN;
				tempN = N;
				N = N->rightChild;
				delete tempN;
			}
			else if (N->leftChild != nullptr && N->rightChild != nullptr) {		// Node being deleted has two child nodes
				Node* minNode = detachMinimumNode(N->rightChild);
				minNode->leftChild = N->leftChild;
				minNode->rightChild = N->rightChild;
				delete N;
				N = minNode;
			}
		}
		else if (K < N->key) {
			removeWorker(K, N->leftChild);
		}
		else if (K > N->key) {
			removeWorker(K, N->rightChild);
		}
	}
}

BST::Node* BST::detachMinimumNode(Node*& N) {

	assert(N != nullptr);

	if (N->leftChild == nullptr) {
		Node* minNode = N;
		N = N->rightChild;
		return minNode;
	}
	else {
		return detachMinimumNode(N->leftChild);
	}
}

BST::~BST()
{
	deepDelete(root);
}

void BST::deepDelete(Node* N)
{
	if (N != nullptr) {
		deepDelete(N->leftChild);
		deepDelete(N->rightChild);
		delete N;
		N = nullptr;
	}
}

BST::BST(const BST& original)
{
	this->root = deepCopy(original.root);
}

BST::Node* BST::deepCopy(Node* original)
{
	Node* newNode = new Node(original->key, original->item);

	if (original->leftChild != nullptr)
	{
		if (original->rightChild == nullptr)
		{
			newNode->rightChild = nullptr;
		}
		newNode->leftChild = deepCopy(original->leftChild);
	}

	if (original->rightChild != nullptr)
	{
		if (original->leftChild == nullptr)
		{
			newNode->leftChild = nullptr;
		}
		newNode->rightChild = deepCopy(original->rightChild);
	}

	if (original->leftChild == nullptr && original->rightChild == nullptr)
	{
		newNode->leftChild = nullptr;
		newNode->rightChild = nullptr;
	}

	return newNode;
}
#include <string>
#include <vector>
using namespace std;

class BST {
public:
	using Key = int;		// Type alias
	using Item = string;	// Type alias

	void insert(Key, Item);	// Function
	Item* lookup(Key);		// Function
	void loadFile();		// Function
	void printItem(Key);	// Function
	void printEntries();	// Function
	void remove(Key);		// Function

	BST() = default;	// Default constructor
	~BST();				// Destructor
	BST(const BST&);	// Copy constructor

	friend std::ostream& operator << (std::ostream&, const BST&);	// Friend function

private:
	struct Node;			// Node structure
	Node* root = nullptr;	// Root node	

	void insertWorker(Key, Item, Node*&);									// Worker function
	static Item* lookupWorker(Key, Node*);									// Worker function
	void loadFileWorker(Node*&);											// Worker function
	static vector<Node*> printEntriesWorker(Node*, vector<Node*>&);			// Worker function
	void removeWorker(Key, Node*&);											// Worker function
	static Node* detachMinimumNode(Node*&);									// Worker function
	static vector<string> outputStreamWorker(Node*, vector<string>&, int);	// Worker function
	static void deepDelete(Node*);											// Worker for delete constructor
	static Node* deepCopy(Node*);
};

std::ostream& operator << (std::ostream&, const BST&);	// Overloaded operator
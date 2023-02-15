//============================================================================
// Name        : CombinedAuction.cpp
// Author      : Christopher Cammel
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Auction and Bid with Vector Sorting, Linked List
//				 Hash Tables, and a Binary Search Tree, Ansi-style
//============================================================================
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> 
#include <time.h>

#include "CSVparser.hpp"
#include <parser.h>
#include <vector>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================
const unsigned int DEFAULT_SIZE = 179;

// Forward declarations
double strToDouble(string str, char ch);
struct Bid { // define a structure to hold bid information
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

// Internal structure for tree node
struct Node {
	Bid bid;
	Node* right;
	Node* left;
	Node() {
		right = left = nullptr;
	}
	Node(Bid bid) : Node() {
		this->bid = bid;
	}
};
//============================================================================
// Hash Table class definition
//============================================================================
//Define a class containing data members and methods to implement a hash table with chaining.
class HashTable {
private:
	struct Node { // Define structures to hold bids
		Bid bid;
		unsigned key;
		Node* nextNodePtr;
		Node() { //Builds the node
			key = UNIT_MAX;
			nextNodePtr = nullptr;
		}
		Node(Bid myBid) : Node() { //Initializes the node with a bid
			bid = myBid;
		}
		Node(Bid myBid, unsigned myKey) : Node(myBid) {
			key = myKey;
		}
	};
	vector<Node> nodes;
	unsigned tableSize = DEFAULT_SIZE;
	unsigned int hash(int key);

public:
	HashTable();
	HashTable(unsigned size);
	virtual ~HashTable();
	void Insert(Bid bid);
	void PrintAll();
	void Remove(string bidId);
	Bid Search(string bidId);
};

// Default constructor
HashTable::HashTable() {
	nodes.resize(tableSize); // Initializes the structures used to hold bids
}

HashTable::HashTable(unsigned size) {
	this->tableSize = size;
	nodes.resize(tableSize);
}

// Destructor
HashTable::~HashTable() {
	nodes.erase(nodes.begin()); // Implement logic to free storage when class is destroyed
}

/** Calculate the hash value of a given key. Note that key is specifically defined as
 * unsigned int to prevent undefined results of a negative list index.
 * @param key The key to hash
 * @return The calculated hash */
unsigned int HashTable::hash(int key) {
	// Implement logic to calculate a hash value
	return key % tableSize;
}

/** Insert a bid, @param bid The bid to insert */
void HashTable::Insert(Bid bid) {
	// Implement logic to insert a bid
	unsigned key = hash(atoi(bid.bidId.c_str()));
	Node* prevNode = &(nodes.at(key)); // Key value node search
	if (prevNode == nullptr) {
		Node* nextNode = new Node(bid, key);
		nodes.insert(nodes.begin() + key, (*nextNode));
	}
	else {
		if (prevNode->key == UNIT_MAX) { // If the key value node is found
			prevNode->key = key;
			prevNode->bid = bid;
			prevNode->nextNodePtr = nullptr;
		}
		else { // If the key value node is not found, this searches for the next available node
			while (prevNode->nextNodePtr != nullptr) {
				prevNode = prevNode->nextNodePtr;
			}
		}
	}
}

void HashTable::PrintAll() { // Print all bids   
	for (unsigned int i = 0; i < nodes.size(); ++i) {  // Implement logic to print all bids
		displayBid(nodes[i].bid);
	}
}

/** Remove a bid, @param bidId The bid id to search for */
void HashTable::Remove(string bidId) {
	unsigned key = hash(atoi(bidId.c_str())); // Implement logic to remove a bid
	nodes.erase(nodes.begin() + key);
}

/** Search for a specific bidID, @param bidId The bid id to search for */
Bid HashTable::Search(string bidId) {
	Bid bid;
	unsigned key = hash(atoi(bidId.c_str())); // Implement logic to search for and return a bid
	Node* node = &(nodes.at()); // Key value node search
	if (node != nullptr && node->key != UNIT_MAX && node->bid.bidId.compare(bidId) == 0) { // If node search completes with given key value
		return node->bid;
	}
	if (node == nullptr || node->key == UNIT_MAX) { // If no node is found with given key value
		return bid;
	}
	while (node != nullptr) { // Search list for a match
		if (node->key != UNIT_MAX && node->bid.bidId.compare(bidId) == 0) {
			return node->bid;
		}
		node = node->nextNodePtr;
	}
	return bid;
}

//============================================================================
// Linked-List class definition
//============================================================================
// Define a class containing data members and methods to implement a linked-list.
class LinkedList {
private: // Internal structure for list entries, housekeeping variables
	struct node {
		Bid data;
		node* nextNode;
	};
	node* head;
	node* tail;
	int size;

public:
	LinkedList();
	virtual ~LinkedList();
	void Append(Bid bid);
	void Prepend(Bid bid);
	void PrintList();
	void Remove(string bidId);
	Bid Search(string bidId);
	int Size();
};

// Default constructor
LinkedList::LinkedList() {
	// Initialize housekeeping variables
	head = nullptr;
	tail = nullptr;
	size = 0;
}
// Destructor
LinkedList::~LinkedList() {
}

void LinkedList::Append(Bid bid) { // Append a new bid to the end of the list
	// Implement append logic
	node* newNode = new node;
	newNode->data = bid;
	newNode->nextNode = nullptr;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		++size;
	}
	else {
		tail->nextNode = newNode;
		tail = newNode;
		++size;
	}
}

void LinkedList::Prepend(Bid bid) { // Prepend a new bid to the start of the list 
	node* newNode = new node; // Implements prepend logic
	newNode->data = bid;
	newNode->nextNode = nullptr;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		++size;
	}
	else {
		newNode->nextNode = head;
		head = newNode;
		++size;
	}
}

void LinkedList::PrintList() { // Simple output of all bids in the list   
	node* temp = head; // Implements print logic
	while (temp != nullptr) {
		cout << temp->data.title << "!";
		cout << temp->data.amount << "!";
		cout << temp->data.fund << endl;
		temp = temp->nextNode;
	}
}
/** Remove a specified bid, @param bidId The bid id to remove from the list */
void LinkedList::Remove(string bidId) {
	// Implement remove logic
	node* temp = head;
	node* prevNode;
	if (temp == nullptr) {
		return;
	}
	else if (head->data.bidId == bidId && head->nextNode == nullptr) {
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		while (temp->data.bidId != bidId) {
			prevNode = temp;
			temp = temp->nextNode;
		}
		prevNode->nextNode = temp->nextNode;
		delete temp;
	}
}

/** Search for the specified bidId, @param bidId The bid id to search for */
Bid LinkedList::Search(string bidId) {
	// Implement search logic
	node* temp = head;
	node* holder = new node;
	holder->data.bidId = "";
	while (temp != nullptr) {
		cout << temp->data.bidId << endl;
		if (temp->data.bidId == bidId) {
			return temp->data;
		}
		cout << "test";
		temp = temp->nextNode;
	}
}

// Returns the current size (number of elements) in the list
int LinkedList::Size() {
	return size;
}

//============================================================================
// Binary Search Tree class definition
//============================================================================
// Define a class containing data members and methods to implement a binary search tree
class BinarySearchTree {
private:
	Node* root;
	void addNode(Node* node, Bid bid);
	void inOrder(Node* node);
	Node* removeNode(Node* node, string bidId);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Bid bid);
	void Remove(string bidId);
	Bid Search(string bidId);
}

// Default constructor
BinarySearchTree::BinarySearchTree() {
	// initialize housekeeping variables
	root = nullptr;
}

// Destructor
BinarySearchTree::~BinarySearchTree() {
	// recurse from root deleting every node
}

// Traverse the tree in order
void BinarySearchTree::InOrder() {
	this->inOrder(root);
}

// Inserts a bid
void BinarySearchTree::Insert(Bid bid) {
	// Implements inserting a bid into the tree
	if (root == nullptr) {
		root = new Node(bid);
	}
	else {
		this->addNode(root, bid);
	}
}

// Remove a bid
void BinarySearchTree::Remove(string bidId) {
	// Implements removing a bid from the tree
	this->removeNode(root, bidId);
}

// Search for a bid
Bid BinarySearchTree::Search(string bidId) { // Implements searching the tree for a bid
	Node* current = root; // Starting a search from the root
	while (current != nullptr) {
		if (current->bid.bidId.compare(bid.bidId) == 0) {
			return current->bid;
		}
		if (bidId.compare(current->bid.bidId) < 0) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	Bid bid;
	return bid;
}

/** Add a bid to some node (recursive)
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) { // Implements inserting a bid into the tree   
	if (node->bid.bidId.compare(bid.bidId) > 0) {
		if (node->left == nullptr) {
			node->left = new Node(bid);
		}
		else {
			this->addNode(node->left, bid);
		}
	}
	else {
		if (node->right == nullptr) {
			node->right = new Node(bid);
		}
		else {
			this->addNode(node->right, bid);
		}
	}
}
void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left);
		inOrder(node->right);
	}
}

Node* BinarySearchTree::removeNode(Node* node, string bidId)
{
	return nullptr;
}

//============================================================================
// Static methods used for testing
//============================================================================

/** Display the bid information to the console (std::out)
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
	return;
}

/** Load a CSV file containing bids into a container
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
	cout << "Loading CSV file " << csvPath << endl;
	file = csv::Parser(csvPath); // initialize the CSV Parser using the given path   
	vector<string> header = file.getHeader(); // read and display header row - optional
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;
	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {
			// Create a data structure and add to the collection of bids           
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');
			cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;
			bst->Insert(bid); // push this bid to the end
		}
	}
	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
	}
}

/** Simple C function to convert a string to a double
 * after stripping out unwanted char
 * credit: http://stackoverflow.com/a/24875936
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

// The one and only main() method
int main(int argc, char* argv[]) {
	string csvPath, bidKey; // process command line arguments
	switch (argc) {
	case 2:
		csvPath = argv[1];
		bidKey = "98109";
		break;
	case 3:
		csvPath = argv[1];
		bidKey = argv[2];
		break;
	default:
		csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
		bidKey = "98109";
	}
	clock_t ticks; // Define a timer variable
	BinarySearchTree* bst; // Define a binary search tree to hold all bids
	Bid bid;
	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  4. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			bst = new BinarySearchTree();
			ticks = clock(); // Initializes a timer variable before loading bids           
			loadBids(csvPath, bst); // Complete the method call to load the bids and print out number of bids read
			cout << bst->Size() << " bids read" << endl;
			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;
		case 2:
			bst->InOrder();
			break;
		case 3:
			ticks = clock();
			bid = bst->Search(bidKey);
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			if (!bid.bidId.empty()) {
				displayBid(bid);
			}
			else {
				cout << "Bid Id " << bidKey << " not found." << endl;
			}
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;
		case 4:
			bst->Remove(bidKey);
			break;
		}
	}
	cout << "Good bye." << endl;
	return 0;
}
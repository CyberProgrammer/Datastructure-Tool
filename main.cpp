#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

void driver();

class Node {
public:
	int data;
	Node* next;

	// Default constructor
	Node()
	{
		data = 0;
		next = NULL;
	}

	Node(int data)
	{
		this->data = data;
		this->next = NULL;
	}
};

class linkedList {
	Node* head = NULL;
public:
	string filepath;

	void push(int new_data);
	void search(int x);
	void printList();
	void deleteNode(int value);
	void pushFromFile();
	void readFile(string file);
	void deleteNthNode(int);
	void listDriver();
	linkedList();
};

class vectorClass {
	public:
		vector<int> vec;
};

vectorClass myVector;

// Read file into vector for linear and binary search
void readFile() {
	string line;
	string filepath;
	int value;

	cout << "What is the name of the text file?" << endl;
	cin >> filepath;
	cout << endl;

	ifstream file(filepath);

	// Reset buffer
	cin.clear();
	cin.ignore(10000, '\n');

	if (file.is_open()) {
		while (getline(file, line))
		{
			// Convert input to int
			stringstream ss(line);

			// If input is valid
			if (ss >> value) {
				ss >> value;
				// Add value to vector
				myVector.vec.push_back(value);
			}
			else
				continue;
		}

		driver();
	}
	else {
		cout << "File could not be opened or file path does not exist." << endl << endl;
		driver();
	}
}

void viewData() {

	if (myVector.vec.size() == 0) {
		cout << "Vector is empty, please add data using a text file to proceed." << endl << endl;
		driver();
	}
	else {
		cout << endl << "Data in vector" << endl;
		cout << "---------------" << endl;
		for (int i = 0; i < myVector.vec.size(); i++) {
			cout << myVector.vec[i] << endl;
		}
		cout << "---------------" << endl << endl;

		driver();
	}
}

/*
	Linear Search
	-----------
	Pros: fast searches for small and medium lists, does not need to be sorted, does not need to be shifted during insertions or deletions

	Cons: slow for large sets of data
*/

void linearSearch() {
	
	// If no data is stored restart program
	if (myVector.vec.size() == 0) {
		cout << "Vector is empty, please add data using a text file to proceed." << endl << endl;
		driver();
	}

	// User input
	string input = "";
	cout << "Enter a value: ";
	cin >> input;

	// Convert input to int
	int intInput;
	stringstream ss(input);
	ss >> intInput;

	// Linear Search O(n)
	bool isFound = false;
	for (int i = 0; i != myVector.vec.size(); i++)
	{
		if (myVector.vec[i] == intInput) {
			cout << "Value found at index " << i << "." << endl << endl;
			isFound = true;
		}
	}

	if (isFound == false) {
		cout << "Could not find value." << endl << endl;
	}

	// Clear buffer
	cin.clear();
	cin.ignore(10000, '\n');

	// Rerun main loop
	driver();
}

/*
	Binary Search
	-----------
	Pros: continously eliminates half the list to reduce the number of searches, better than linear for large lists but slower for smaller lists

	Cons: prone to errors when determining the boundary, overflows is also a concern
*/

void binarySearch() {
	// If no data is stored restart program
	if (myVector.vec.size() == 0) {
		cout << "Vector is empty, please add data using a text file to proceed." << endl << endl;
		driver();
	}

	// User input
	string input = "";
	cout << "Enter a value: ";
	cin >> input;

	// Convert input to int
	int target;
	stringstream ss(input);

	// Input validation
	if (ss >> target) {
		ss >> target;
	}
	else {
		cout << "Integers only. Try again" << endl << endl;
		binarySearch();
	}

	// Sort the array O(n log n) , keeps original the same and only performs sort on copy
	vector<int> tempSorted = myVector.vec;
	sort(tempSorted.begin(), tempSorted.end());

	int min = 0;
	int max = tempSorted.size() - 1;

	while (min <= max) {
		int half = min + (max - min) / 2;

		if (tempSorted[half] == target) {
			cout << "Found the value " << target << " at index " << half << "." << endl << endl;
			driver();
		}
		else if (tempSorted[half] < target) {
			min = half + 1;
		}
		else {
			max = half - 1;
		}

		if (target == tempSorted[min]) {
			cout << "Found the value " << target << " at index " << min << "." << endl << endl;
			driver();
		}
		if (target == tempSorted[max]) {
			cout << "Found the value " << target << " at index " << max << "." << endl << endl;
			driver();
		}
	}


		

	cout << "Could not find the value " << target << "." << endl << endl;

	// Clear buffer
	cin.clear();
	cin.ignore(10000, '\n');

	// Rerun main loop
	driver();

}

/*
	Linked List
	-----------
	Pros: dynamic structure, no memory waste, stacks and queues can be implemented, no need to shift elements with insertion and deletions

	Cons: more time consuming to traverse through a large list, random access memory is not possible
*/

// Deletes a node that contains the value given
void linkedList::deleteNode(int value) {

	// Head node
	Node* temp = head;
	Node* prev = NULL;

	// If head holds the value
	if (temp->data == value && temp != NULL) {
		head = temp->next;
	}
	else {
		// Traverse until data is found
		while (temp != NULL && temp->data != value) {
			prev = temp;
			temp = temp->next;
		}

		// If value is not found
		if (temp == NULL)
			return;

		// Change node link
		prev->next = temp->next;

		// Delete node
		delete temp;
	}
}

// Deletes a node at a specific position
void linkedList::deleteNthNode(int pos) {
	int counter = 0;

	// Head node
	Node* temp = head;
	Node* prev = NULL;

	while (counter != pos)
	{
		prev = temp;
		temp = temp->next;
		counter++;
	}

	// Reassign pointer
	prev->next = temp->next;

	// Delete node
	delete temp;

}

// Adds a node to the end of the list
void linkedList::push(int data)
{
	// Create the new Node.
	Node* newNode = new Node(data);

	// Assign to head
	if (head == NULL) {
		head = newNode;
		return;
	}

	// Traverse till end of list
	Node* temp = head;
	while (temp->next != NULL) {

		// Update temp
		temp = temp->next;
	}

	// Insert at the last.
	temp->next = newNode;
}

// Searches for a node with the given target value
void linkedList::search(int target)
{
	// If no data is stored restart program
	if (head == NULL) {
		cout << endl << "Linked list is null, please add data using a text file to proceed." << endl << endl;
		listDriver();
	}



	Node* current = head; // Initialize current
	while (current != NULL) {
		if (current->data == target) {
			cout << target << " was found!" << endl;
			return;
		}

		current = current->next;
	}

	cout << target << " was NOT found!" << endl;
	return;
}

// Prints the list
void linkedList::printList()
{
	Node* temp = head;

	// Check for empty list.
	if (head == NULL) {
		cout << "List is empty." << endl << endl;
		return;
	}

	// Traverse the list.
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
		cout << endl;
	}
}

// Adds to the list using a text file ( 1 value per line)
void linkedList::pushFromFile() {
	cout << "What is the name of the text file?" << endl;
	cin >> filepath;

	readFile(filepath);
}

// Reads a file by line and adds the value to the list
void linkedList::readFile(string filepath) {
	string line;
	int value;

	ifstream file(filepath);

	if (file.is_open()) {
		while (getline(file, line))
		{
			// Convert input to int
			stringstream ss(line);

			// Input validation
			if (ss >> value) {
				ss >> value;
				push(value);
			}
		}
	}
	else {
		cout << "File could not be opened." << endl;
		exit(98);
	}
}

void linkedList::listDriver() {
	string choice;
	int intChoice; // Converted string to int
	bool inputValid = false; // Loop condition

	cout << "Linked List" << endl;
	cout << "---------------" << endl;
	cout << "1. Add to list" << endl;
	cout << "2. Add to list with a file" << endl;
	cout << "3. Delete from list" << endl;
	cout << "4. Delete at Nth node" << endl;
	cout << "5. Search List" << endl;
	cout << "6. Print List" << endl;
	cout << "7. Back to menu" << endl << endl;

	cin >> choice;
	cout << endl;

	// Input validation
	while (!inputValid)
	{
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7") {
			// Convert input to int
			stringstream ss(choice);
			ss >> intChoice;

			inputValid = true;
		}
		else {
			cout << "Invalid input. Try again." << endl << endl;
			listDriver();
		}
	}

	// Decision
	int value;

	switch (intChoice) {
	case 1:
		cout << "What is the value to be added?" << endl;
		cin >> value;
		// Input validation
		if (cin >> value)
			push(value);
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Integers only. Please try again." << endl << endl;
		}
		break;
	case 2:
		pushFromFile();
		break;
	case 3:
		cout << "What is the value to be deleted?" << endl;
		cin >> value;
		// Input validation
		if (cin >> value)
			deleteNode(value);
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Integers only. Please try again." << endl << endl;
		}
		break;
	case 4:
		cout << "What is the position to be deleted?" << endl;
		cin >> value;
		// Input validation
		if (cin >> value)
			deleteNthNode(value);
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Integers only. Please try again." << endl << endl;
		}
		break;
	case 5:
		cout << "What is the value to be found?" << endl;
		cin >> value;
		// Input validation
		if (cin >> value)
			search(value);
		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Integers only. Please try again." << endl << endl;
		}
		break;
	case 6:
		printList();
		break;
	case 7:
		driver();
		break;
	}

	// Clear buffer
	cin.clear();
	cin.ignore(10000, '\n');

	listDriver();
}

// Menu for linked list options
linkedList::linkedList() {
	Node* head = NULL;
}

// Main exectution driver
void driver() {
	linkedList list;

	string choice;
	int intChoice; // Converted string to int
	bool inputValid = false; // Loop condition

	cout << "Data Structures" << endl;
	cout << "---------------" << endl;
	cout << "1. Linear Search" << endl;
	cout << "2. Binary Search" << endl;
	cout << "3. Linked List" << endl;
	cout << "4. Add data using text file" << endl;
	cout << "5. View data" << endl;
	cout << "6. Exit" << endl << endl;

	cin >> choice;
	cout << endl;

	// Input validation
	while (!inputValid)
	{
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6") {
			// Convert input to int
			stringstream ss(choice);
			ss >> intChoice;

			inputValid = true;
		}
		else {
			cout << "Invalid input. Try again." << endl << endl;
			driver();
		}
	}
	
	// Decision
	switch (intChoice) {
		case 1:
			linearSearch();
			break;
		case 2:
			binarySearch();
			break;
		case 3:
			list.listDriver();
			break;
		case 4:
			readFile();
			break;
		case 5:
			viewData();
			break;
		case 6:
			exit(99);
	}

}

int main() {
	vectorClass vecClass;

	// Main loop
	driver();
}


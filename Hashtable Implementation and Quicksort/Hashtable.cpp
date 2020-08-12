/*
* Program or Lab #: HashTables and Quicksort.
* Programmer : Shaantanu Sharma
*
* Due Date : Monday, 16 April 2018, 11: 59 PM
* 
*
* Description : The following code is the implementation of a HashTable and a Quicksort algorithm. The project is based
around reading in a text file and counting how often each word occurs
*
*/
#include <iostream>
#include "Hashtable.h"
#include <string>




using namespace std;

/*Function : Hashtable(int sz)
--------------------
Constuctor, that initializes the Hashtable, creates the table of user input size.
Returns : none
*/
Hashtable::Hashtable(int sz)
{
	size = sz;  //sz is the size of the hash table the user wants to create
	table.resize(size); // set the size of the table according to user input.
}

/*Function : put(string key, int frequency)
--------------------
Add a new pair(key, frequency) to the table if key isn't already in the table, or update the frequency if it's 
already there.
Returns : none
*/
void Hashtable::put(string key)
{
	// using push_back so your output matches mine.
	int HashRes = 0;
	HashRes = hash(key);
	for (pair<string, int> & p : table[HashRes]) // iterate over the list with a reference variable
	{
		if (p.first == key) { // look for a specific word...
			p.second++; // ...and change its frequency
			return;
		}
	}
	pair<string, int> Ltadd(key, 1); // if not found, creates a new pair and adds it at the end of the table.
	table[HashRes].push_back(Ltadd);
}
/*Function : get(string key)
--------------------
A function that returns the frequency(no of times seen in the file) of the word in the table.
Returns : return the associated frequency, or -1 if not found.
*/
int Hashtable::get(string key)
{
	// fill in --- 
	int HashRes = 0;
	HashRes = hash(key);
	//cout << key << " " << HashRes << endl;
	for (pair<string, int> & p : table[HashRes]) // iterate over the list with a reference variable
	{
		if (p.first == key) // look for a specific word...
			return p.second;// ...and return its frequency
	}
	return 0;

}
/*Function : print()
A function that prints out all the data in the table.
Returns : None.
*/
void Hashtable::print()
{
	
	list<pair<string, int>> MyList;
	for (int i = 0; i < table.size(); i++)
	{
		int comma = 0; //to see if comma is needed
		MyList = table[i];
		if (MyList.size() == 0)
			continue;
		cout << "Table Index " << i << "(" << MyList.size() << "): ";
		for (pair<string, int> & p : table[i])
		{
			if (comma != table[i].size() - 1) {
				cout << p.first << ' ' << p.second << ", ";
			}
			else {
				cout << p.first << ' ' << p.second;
			}
			comma++;
		}
		cout << endl;
	}

}
/*Function : hash(s)
--------------------
A simple hash function that calculates the position in the table to store a value.
Returns : An integer representing a slot in the Hashtable, where new entries can be stored.
*/
int Hashtable::hash(string s)
{
	int sum = 0;
	for (int i = 0; i < s.size(); i++)
	{
		sum += s[i]; //add up ASCII codes of each char in s, and return this value % size.
	}
	cout << s << " " << sum << " " << sum % table.size() << endl;
	return sum % table.size();
}


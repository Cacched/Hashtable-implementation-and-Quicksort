/*
* Program or Lab #: HashTables and Quicksort.
* Programmer : Shaantanu Sharma
*
* Date : Monday, 16 April 2018, 11: 59 PM
*
*
* Description : The following code is the implementation of a HashTable and a Quicksort algorithm. The project is based
around reading in a text file and counting how often each word occurs

*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>


using namespace std;


class Hashtable
{
public:
    Hashtable(int sz);	// Constructor

    void put(string key); // adds pair,or updates the frequency if the world already exists.
    int get(string key); // Function to get the frequency of a word in the table.

    void print(); // Function to print the Hashtable.

private:
    int size;                               // number of slots in the table
    vector<list<pair<string, int>>> table;  // the table itself

    int hash(string s);                     // the hash function
};


#endif

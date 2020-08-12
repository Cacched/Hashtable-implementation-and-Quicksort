/*
* Program or Lab #: HashTables and Quicksort.
* Programmer : Shaantanu Sharma
*
* Due Date : Monday, 16 April 2018, 11: 59 PM
*
* COMP241, Spring 2018
*
* Pledge : I have neither given nor received unauthorized aid
*         on this program.
*
* Description : The following code is the implementation of a HashTable and a Quicksort algorithm. The project is based
around reading in a text file and counting how often each word occurs
(similar to the movie reviews project).
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

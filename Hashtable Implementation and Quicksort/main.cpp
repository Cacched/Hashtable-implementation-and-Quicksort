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
#include <iostream>
#include <fstream>
#include <sstream>
#include "Hashtable.h"

using namespace std;
// Function declarations for Split,Quicksort and Binary search
vector<string> split(const string &s, char delim); 
int DivAux(vector<pair<string, int>> &unst, int top, int bot);
void Quicksort(vector<pair<string, int>>& inpt, int fst, int lst);
int binarySearch(vector<pair<string, int>>& inpt, int l, int r, string x);

/*Function : main()
--------------------
Main part of the code, calls all the other function.Initializes the Hashtable and processes command from input file.Initializes Hashtable object
for different functions to be implemented.
Returns : none
*/
int main()
{
	cout << "How big should the hashtable be? ";
	int htsize;
	cin >> htsize;

	Hashtable freqHt(htsize);
	vector<pair<string, int>> freqVec;
	vector<string> words;

	string filename, line;
	cout << "What filename do you want to read? ";
	cin >> filename;
	ifstream infile(filename);
	if (infile.fail())
	{
		cout << "Could not open file." << endl;
		exit(0);
	}

	while (getline(infile, line))
	{
		int ctr = 0;
		words = split(line, ' ');
		for (int x = 0; x < words.size(); x++)
		{
			string word = words[x];
			freqHt.put(word);
			{
				bool state = false;
				for (pair<string, int>& p : freqVec)
				{

					if (p.first == word)
					{
						p.second++;
						state = true;
					}

				}
				if (!state)
				{
					pair<string, int> AddPair(word, 1);
					freqVec.push_back(AddPair);
				}

			}
		}
		

	}
	infile.close();

	cout << "\nHash table:";
	freqHt.print();

	cout << endl << "\nUnsorted vector: " << endl;
	int cnt = 0;
	for (pair<string, int> p : freqVec)
	{
		cout << "Vector index:" <<' ' <<cnt<<' ';
		cout << p.first << ' ' << p.second << endl;
		cnt++;
	} 

	Quicksort(freqVec, 0,freqVec.size()-1);
	cout << endl << "Sorted vector: " << endl;
	int cre=0;
	for (pair<string, int> p : freqVec)
	{
		cout << "Vector index: "<<' '<< cre<<' ';
		cout << p.first << ' ' << p.second << endl;
		cre++;
	} 

	string word;
	while (true)
	{
		cout << "\nEnter a word to search for: ";
		cin >> word;
		if (word == "quit") break;

		int freq = freqHt.get(word);
		int freq2 = -1; 
		freq2 = binarySearch(freqVec, 1, freqVec.size() - 1, word);// BINARY SEARCH THE VECTOR
		cout << "Hashtable frequency = " << freq << endl;
		
		cout << "Vector frequency = " << freq2 << endl;
	}
	return 0;
}
/*Function : binarySearch(vector<pair<string, int>>& inpt, int l, int r, string x)
--------------------
binary search function to search for a word in the Hashtable and vector and returns th number of times the word has 
appeared in the Hashtable or Vector.
Returns : An integer that represents the frequency of a certain word in a vector or Hashtable. or -1 when not
		 found.
*/
int binarySearch(vector<pair<string, int>>& inpt, int l, int r, string x)
{
	while (l <= r)
	{
		int m = l + (r - l) / 2;

		// Check if word is present at mid
		if (inpt[m].first == x)
			return inpt[m].second;

		// If word greater, ignore left half
		if (inpt[m].first < x)
			l = m + 1;

		// If word is smaller, ignore right half
		else
			r = m - 1;
	}

	// if we reach here, then element was
	// not present
	return -1;
}
/*Function :DivAux(vector<pair<string, int>>&unst, int top, int bot)
--------------------
Gets the Pivot, and divides the vector into greater than or less than value of Pivot.
Returns : An integer that represents the position after each step of Quicksort.
*/
int DivAux(vector<pair<string, int>>&unst, int top, int bot)
{
	pair <string, int> pivot = unst[top];
	int lft = top;
	int rht = bot;
	while (lft < rht)
	{
		while (pivot < unst[rht])
		{
			rht--;
		}
		while (lft < rht && (unst[lft] < pivot || unst[lft] == pivot))
		{
			lft++;
		}
		if (lft < rht)
		{
			swap(unst[lft], unst[rht]);
		}
	}
	int pos = rht;
	unst[top] = unst[pos];
	unst[pos] = pivot;
	return pos;
}
/*Function :DivAux(vector<pair<string, int>>&unst, int top, int bot)
--------------------
Quicksorts the vector of unsorted elements, or strings.
Returns : None.
*/
void Quicksort(vector<pair<string, int>> &inpt, int fst, int lst)
{
	//int fst = 1;
	//int lst = inpt.size();
	int pos;
	if (fst < lst)
	{
		pos = DivAux(inpt, fst, lst);
		Quicksort(inpt, fst, pos - 1);
		Quicksort(inpt, pos + 1, lst);
	}
}
/* Function : split(const string &s, char delim)
--------------------
splits the vector of strings called words into individual characters so that main() can read specific characters as commands
from the text file.
Return : Vector of chars.
*/
vector<string> split(const string &s, char delim)
{
    stringstream ss(s);  // this requires #include <sstream>
    string item;
    vector<string> elems;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
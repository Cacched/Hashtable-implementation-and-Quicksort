/*
* Program or Lab #: HashTables and Quicksort.
* Programmer : Shaantanu Sharma
*
* Due Date : Monday, 16 April 2018, 11: 59 PM
*
*
* Description : The following code is the implementation of a HashTable and a Quicksort algorithm. The project is based
*  around reading in a text file and counting how often each word occurs 
*				 
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "Hashtable.h"

using namespace std;

// Function declarations for Split,Quicksort,Reading file input and Binary search
vector<string> split(const string &s, char delim); 
int DivAux(vector<pair<string, int>> &unst, int top, int bot);
void Quicksort(vector<pair<string, int>>& inpt, int fst, int lst);
int binarySearch(vector<pair<string, int>>& inpt, int l, int r, string x);
void readFile(vector<pair<string,int>>&dstVec,Hashtable&dstHt);
/*Function : main()
--------------------
Main part of the code, calls all the other function.Initializes the Hashtable and the Hashtable object
for different functions to be implemented.
Returns : none
*/
int main()
{
	cout << "How big should the hashtable be? ";
	int htsize;
	cin >> htsize;

	Hashtable freqHt(htsize); // Hashtable object
	vector<pair<string, int>> freqVec; 
	vector<string> words; // Vector to store all the words read in from the file.
  	bool readAnother = true;
  	readFile(freqVec,freqHt);
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
   		 cout << "\nType 'quit' to end the search or 'another' to read in another file!";
		cout << "\nEnter a word to search for: ";
		cin >> word;
		if (word == "quit") break;
    		else if (word == "another")
    		{
      		  readFile(freqVec,freqHt);
    		}

		int freq = freqHt.get(word);
		int freq2 = -1; 
		freq2 = binarySearch(freqVec, 1, freqVec.size() - 1, word);// BINARY SEARCH THE VECTOR
		cout << "Hashtable frequency = " << freq << endl;
		
		cout << "Vector frequency = " << freq2 << endl;
	}
	return 0;
}


/*Function : readFile(vector<pair<string,int>>&dstVec,Hashtable&dstHt)
--------------------
Reads in the input file and stores the words along with its frequency in the Hashtable and Vector.
Takes in a Vector and Hashtable object as parameters.
Returns : none
*/
void readFile(vector<pair<string,int>>&dstVec,Hashtable&dstHt)
{

	vector<string> words; // Vector to store all the words read in from the file.

	string filename, line;
  	cout << "\nType 'quit' to end the search"<<endl;
	cout << "What filename do you want to read? ";
	cin >> filename;
	ifstream infile(filename);
  	if(filename == "quit") 
  	{
   	  exit(0);
  	}
  	else if (infile.fail())
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
			dstHt.put(word);
			{
				bool state = false;
				for (pair<string, int>& p : dstVec)
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
					dstVec.push_back(AddPair);
				}

			}
		}
		

	}
	infile.close();

} 

/*Function : binarySearch(vector<pair<string, int>>& inpt, int l, int r, string x)
----------------------------------------------------------------------------------
Binary search function to search for a word in the Hashtable and vector.
Returns : An integer that represents the frequency of a certain word in a vector or Hashtable. or -1 when not
found.
*/
int binarySearch(vector<pair<string, int>>& inpt, int l, int r, string x)
{
	while (l <= r)
	{
		int m = l + (r - l) / 2; // finds the middle index of the vector

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

	// if we reach here, then element was not present
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
/*Function :Quicksort(vector<pair<string, int>>&inpt, int fst, int lst)
--------------------
Uses a recursive divide and conquer stratergy to split the vector to sub vectors from the pivot element and sort the sub vectors of unsorted elements.
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

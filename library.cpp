// Author: Alejandro Cuevas

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

//Function prototype for al lthe glorius function decomposition

void addToLibrary(vector<vector<string>> &library, string book, string id);
void checkOutStatus(const vector<vector<string>> &library);
bool containsCommas(const string book);
void displayLibrary(const vector<vector<string>> &library);
bool isValidISBN(const string &isbn);
int loadFile(const string &fileName, vector<vector<string> > &library);
void outputLibrary(const vector<vector<string> > &library, string fileName);
void printInvalidEntries(const vector<vector<string> > &library);
void printMenu();
void removeEntry(vector<vector<string> > &library, const string &searchBook, const int choice);
void searchBook(const vector<vector<string> > &library, const string &search, const int choice);


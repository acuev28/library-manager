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

int main(){
    
    string command;
    vector<vector<string> > library;

    cout << "Welcome to the library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

}

//Adds book information the user library vector
void addToLibrary(vector<vector<string> > &library, string book, string ID){
    if (book.find(",") != string::npos){
        cout << "The book title cannot contain commas." << endl;
        return;
    }
    
    vector<string> bookDetails;
    bookDetails.push_back(book);
    bookDetails.push_back(ID);
    bookDetails.push_back("0");
    library.push_back(bookDetails);

    cout << "The Following Entry Was Added\n";
    cout << "-----------------------------\n";
    cout << book << " --- " << ID << " --- " << "In Library\n";
}

// Prints out the library books check out status
void checkOutStatus(const vector<vector<string> > &library){
    int inLibrary = 0;
    int checkedOut = 0;
    int onLoan = 0;
    int unknown = 0;
    int other = 0;

    for (size_t i = 0; i < library.size(); i++){
        string status = library[i][2];

        switch(stoi(status)){
            case 0:
                inLibrary += 1;
                break;
            case 1:
                checkedOut += 1;
                break;
            case 2:
                onLoan += 1;
                break;
            case 3:
                unknown += 1;
                break;
            default:
                other += 1;
        }
    }
    cout << "Your Current Library's Stats" << endl;
    cout << "----------------------------" << endl;
    cout << "Total Books: " << library.size() << endl;
    cout << "   In Library: " << inLibrary << endl;
    cout << "   Checked Out: " << checkedOut << endl;
    cout << "   On Loan: " << onLoan << endl;
    cout << "   Unknown: " << unknown << endl;
    cout << "   Other: " << other << endl;
}

// Check if book title contains a comma
bool containsCommas(const string book){
    if (book.find(",") != string::npos){
        return true;
    }
    return false;
}
// Author: Alejandro Cuevas

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

// Display the whole library (bookTitle, ISBN number, checkout status)
void displayLibrary(const vector<vector<string> > &library){
    cout << "Your Current Library" << endl;
    cout << "--------------------" << endl;

    for (size_t i = 0; i < library.size(); i++){
        string bookTitle = library[i][0];
        string bookID = library[i][1];
        int bookStatus = stoi(library[i][2]); // Convert bookStatus to integer
        string status;

        switch (bookStatus) {
            case 0:
                status = "In Library";
                break;
            case 1:
                status = "Check Out";
                break;
            case 2:
                status = "On Loan";
                break;
            case 3:
                status = "Unknown State";
                break;
            default:
                status = "Invalid State";
        }

        cout << bookTitle << " ---" << bookID << " --- " << status << endl;
    }
}

// Checks if the ISBN is valid
bool isValidISBN(const string &isbn){
    if (isbn.size() != 13){
        return false;
    }

    int weightedSum = 0;

    for (size_t i = 0; i < 12; i++){
        int digit = isbn[i] - '0';
        weightedSum += (i % 2 == 0) ? digit : digit * 3;
    }

    int remainder = weightedSum % 10;
    int checkDigit = (remainder == 0) ? 0 : (10 - remainder);
    int lastDigit = isbn[12] - '0';

    return (checkDigit == lastDigit);
}

// Reads in file and stores the information to the library
int loadFile(const string &fileName, vector<vector<string> > &library){
    int numOfLines = 0;
    string bookTitle;
    string bookID;
    string bookStatus;

    ifstream readFile(fileName);

    if (!readFile.is_open()){
        cout << "Could not find the database file." << endl;
        return 0; // Return 0 to indicate that no lines were read.
    }

    string line;
    while (getline(readFile, line)){
        // Set the bookTitle as the entire line by default
        bookTitle = line;

        // Finding the comma (,)
        size_t comma = line.find(',');
        if (comma != string::npos){
            bookTitle = line.substr(0, comma);
            line = line.substr(comma + 1);
            comma = line.find(',');

            if (comma != string::npos){
                bookID = line.substr(0, comma);
                line = line.substr(comma + 1);

                // Set the book status to the remaining part of the line
                bookStatus = line;
            } else {
                bookID = line;
                // Sets default checkout status to "0" (In Library) if the book does not contain any status
                bookStatus = "0";
            }   
        } else {
            // Default ISBN when there is no ISBN in the line
            bookID = "000-0-00-000000-0";
            // Default checkout status to "0" (In Library) if missing
            bookStatus = "0";
        }

        vector<string> bookInformation;
        bookInformation.push_back(bookTitle);
        bookInformation.push_back(bookID);
        bookInformation.push_back(bookStatus);
        library.push_back(bookInformation);
        numOfLines++;
    }
    readFile.close();
    return numOfLines;
}

// Creates file and write the books information
void outputLibrary(const vector<vector<string> > &library, string fileName){
    ofstream fLibrary(fileName);

    for (size_t i = 0; i < library.size(); i++){
        string book = library[i][0];
        string bookISBN = library[i][1];
        string bookStatus = library[i][2];
        int status = stoi(bookStatus); //Convert bookStatus to integer

        fLibrary << book << ", " << bookISBN << ", " << status << endl; 
    }
    fLibrary.close();
}

// Checks the book information (ISBN and Check Out Status)
void printInvalidEntries(const vector<vector<string> > &library){
    cout << "The Following Library Entries Have Invalid Data" << endl;
    cout << "-----------------------------------------------" << endl;

    if (library.empty()){
        cout << "The library has no books." << endl;
        return;
    }

    bool notValid = false;
    bool hasInvalidEntries = false;

    for (size_t i = 0; i < library.size(); i++){
        string bookTitle = library[i][0];
        string bookID = library[i][1];
        string bookStatus = library[i][2];

        // Checking ISBN Validity
        if (!isValidISBN(bookID)){
            notValid = true;
        }

        // Checking status
        int status = stoi(bookStatus);

        if (status < 0 || status > 3){
            cout << bookTitle << " --- " << bookID << " --- Invalid Status" << endl;
            notValid = true;
        }

        if (notValid){
            hasInvalidEntries = true;
        }
    }
    if (hasInvalidEntries){
        cout << "The library has no invalid entries." << endl;
    }
}
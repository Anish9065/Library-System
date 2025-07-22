#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// Function to check if book already exists
bool bookExists(string bookName) {
    ifstream file("library.txt");
    string line;
    
    while (getline(file, line)) {
        size_t pos = line.find(" | ");
        string existingBook = line.substr(0, pos);
        if (existingBook == bookName) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void addBook() {
    ofstream file("library.txt", ios::app);
    string bookName, authorName;
    int copies;

    cout << "Enter Book Name: ";
    getline(cin >> ws, bookName);
    
    // Check if book already exists
    if (bookExists(bookName)) {
        cout << "Error: Book with name '" << bookName << "' already exists!\n";
        file.close();
        return;
    }

    cout << "Enter Author Name: ";
    getline(cin, authorName);
    cout << "Enter Number of Copies: ";
    
    // Arithmetic validation for copies
    while (true) {
        if (cin >> copies && copies > 0) {
            break; // Valid input, exit loop
        } else {
            cout << "Invalid input. Please enter a positive number of copies: ";
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        }
    }

    file << bookName << " | " << authorName << " | " << copies << endl;
    file.close();
    cout << "Book added successfully!\n";
}

void viewBooks() {
    ifstream file("library.txt");
    string line;

    cout << "\nAvailable Books:\n";
    cout << "----------------------------------------------------\n";
    cout << "Book Name\t\tAuthor\t\tCopies\n";
    cout << "----------------------------------------------------\n";

    while (getline(file, line)) {
        size_t pos1 = line.find(" | ");
        size_t pos2 = line.find(" | ", pos1 + 3);
        string bookName = line.substr(0, pos1);
        string authorName = line.substr(pos1 + 3, pos2 - (pos1 + 3));
        int copies = stoi(line.substr(pos2 + 3));

        cout << bookName << "\t\t" << authorName << "\t\t" << copies << endl;
    }

    file.close();
}

void searchBook() {
    ifstream file("library.txt");
    string line, searchName;
    bool found = false;

    cout << "Enter the Book Name to search: ";
    getline(cin >> ws, searchName);

    while (getline(file, line)) {
        if (line.find(searchName) != string::npos) {
            cout << "Book found: " << line << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }

    file.close();
}

void deleteBook() {
    ifstream file("library.txt");
    ofstream temp("temp.txt");
    string line, deleteName;
    bool found = false;

    cout << "Enter the Book Name to delete: ";
    getline(cin >> ws, deleteName);

    while (getline(file, line)) {
        if (line.find(deleteName) != string::npos) {
            cout << "Deleted: " << line << endl;
            found = true;
            continue; // Skip writing this line
        }
        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found) {
        cout << "Book not found.\n";
    } else {
        cout << "Book deleted successfully.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n==== Mini Library System ====\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Search Book by Name\n";
        cout << "4. Delete Book by Name\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>  
using namespace std;

void design(){
    cout << "----------------------------------------------------------" << endl;
}

void clear(){
    system("cls");
}

class temp {
    string id, name, author, search;
    fstream file;
public:
    void addBook();
    void showAll();
    void extractBook();
    void deleteBook();
} obj;

int main() {
    clear();
    cout << "" << endl;
    cout << "" << endl;
    design();
    cout << "             LIBRARY MANAGEMENT SYSTEM" << endl;
    design();
    char choice;
    while (true) { 
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "What do you want to do..." << endl;
        cout << "           1. Show All Books" << endl;
        cout << "           2. Extract Book" << endl;
        cout << "           3. Add books (ADMIN)" << endl;
        cout << "           4. Delete Book" << endl;
        cout << "           5. Exit" << endl;
        design();
        cout << "" << endl;
        cout << "" << endl;
        cout << "Enter Your Choice :: ";
        cin >> choice;
        clear();
        switch (choice) {
        case '1':
            cin.ignore();
            obj.showAll();
            break;
        case '2':
            cin.ignore();
            obj.extractBook();
            break;
        case '3':
            cin.ignore();
            obj.addBook();
            break;
        case '4':
            cin.ignore();
            obj.deleteBook();
            break;
        case '5':
            return 0;
        default:
            cout << "Invalid Choice...!" << endl;
        }
    }
    return 0;
}

void temp::addBook() {
    clear();
    string adminUsername, adminPassword;
    string correctUsername = "admin";  
    string correctPassword = "admin123"; 
    cout << "Enter Admin Username: ";
    getline(cin, adminUsername);
    cout << "Enter Admin Password: ";
    getline(cin, adminPassword);
    if (adminUsername == correctUsername && adminPassword == correctPassword) {
        bool idExists;
        do {
            idExists = false;
            cout << "\nEnter Book ID :: ";
            getline(cin, id);
            file.open("bookData.txt", ios::in);
            while (getline(file, search, '*')) {
                getline(file, name, '*');
                getline(file, author, '\n');
                if (search == id) {
                    cout << "Book ID already exists! Please enter a unique ID." << endl;
                    idExists = true;
                    break;
                }
            }
            file.close();
        } while (idExists);

        cout << "Enter Book Name :: ";
        getline(cin, name);
        cout << "Enter Book's Author name :: ";
        getline(cin, author);
        file.open("bookData.txt", ios::out | ios::app);
        file << id << "" << name << "" << author << endl;
        file.close();

        cout << "Book added successfully!" << endl;
    } else {
        cout << "Invalid username or password. Access denied!" << endl;
    }
}

void temp::showAll() {
    ifstream file("bookData.txt");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
    }

    string id, name, author;

    cout << "\n----------------------------------------------------------" << endl;
    cout << "  Book ID      |      Book Name      |      Author Name" << endl;
    cout << "----------------------------------------------------------" << endl;

    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');
        cout << left << setw(10) << id 
             << setw(30) << name 
             << setw(30) << author << endl;
    }

    file.close();
}

void temp::extractBook() {
    clear();
    showAll();  

    cout << "Enter Book Id to Extract :: ";
    getline(cin, search);
    fstream tempFile;
    bool found = false;

    file.open("bookData.txt", ios::in);
    tempFile.open("tempData.txt", ios::out);  

    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');

        if (search == id) {
            cout << "\n\t\t " << id << " \t\t " << name << " \t\t " << author << endl;
            cout << "Book Extracted Successfully...!" << endl;
            found = true;
        } else {
            tempFile << id << "" << name << "" << author << endl;
        }
    }

    if (!found) {
        cout << "Book Not Found!" << endl;
    }

    file.close();
    tempFile.close();
    remove("bookData.txt");
    rename("tempData.txt", "bookData.txt");
}

void temp::deleteBook() {
    clear();
    showAll();
    cout << "Enter Book Id to Delete :: ";
    getline(cin, search);

    fstream tempFile;
    bool found = false;

    file.open("bookData.txt", ios::in);
    tempFile.open("tempData.txt", ios::out);

    while (getline(file, id, '*')) {
        getline(file, name, '*');
        getline(file, author, '\n');

        if (search == id) {
            cout << "\nBook Found:\n";
            cout << "\t\t " << id << " \t\t\t " << name << " \t\t\t " << author << endl;
            cout << "Are you sure you want to delete this book? (y/n): ";
            char confirm;
            cin >> confirm;
            cin.ignore();
            if (confirm == 'y' || confirm == 'Y') {
                found = true;
                cout << "Book Deleted Successfully...!" << endl;
            } else {
                tempFile << id << "" << name << "" << author << endl;
            }
        } else {
            tempFile << id << "" << name << "" << author << endl;
        }
    }

    if (!found) {
        cout << "Book Not Found!" << endl;
    }

    file.close();
    tempFile.close();
    remove("bookData.txt");
    rename("tempData.txt", "bookData.txt");
}
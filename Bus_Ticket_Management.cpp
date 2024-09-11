#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Passenger {
    string passenger_name;
    string passenger_contact;
    int seatNumber;
    string source;
    string destination;
    double price;
};

void drawLine() {
    cout << "-------------------------------------------------------------------------------" << endl;
}

void displayMenu() {
    cout << "What do you want to do?" << endl;
    cout << "            1. Book ticket" << endl;
    cout << "            2. Ticket modification" << endl;
    cout << "            3. Print ticket" << endl;
    cout << "            4. Quit" << endl;
    drawLine();
}

bool isSeatBooked(int seatNumber) {
    ifstream inFile("tickets.txt");
    string line;
    string seatNumStr = "Seat Number: " + to_string(seatNumber);

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find(seatNumStr) != string::npos) {
                inFile.close();
                return true; 
            }
            for (int i = 0; i < 5; ++i) {
                getline(inFile, line);
            }
        }
        inFile.close();
    } else {
        cout << "Error opening file!" << endl;
    }
    return false; 
}

void bookTicket() {
    Passenger passenger;
    ofstream outFile("tickets.txt", ios::app);
   do {
        cout << "Enter seat number (1-35): ";
        cin >> passenger.seatNumber;
        if (passenger.seatNumber < 1 || passenger.seatNumber > 35) {
            cout << "Invalid seat number........" << endl;
            continue; 
        }
        if (isSeatBooked(passenger.seatNumber)) {
            cout << "Sorry, seat number " << passenger.seatNumber << " is already booked." << endl;
        } else {
            break;  
        }
    } while (true);

    cout << "Enter your name: ";
    cin.ignore(); 
    getline(cin, passenger.passenger_name);   
    cout << "Enter your contact number: ";
    cin >> passenger.passenger_contact;
    cout << "Enter source station: ";
    cin.ignore(); 
    getline(cin, passenger.source);
    cout << "Enter destination station: ";
    getline(cin, passenger.destination);
    cout << "Enter Price: ";
    cin >> passenger.price;

    if (outFile.is_open()) {
        outFile << "Seat Number: " << passenger.seatNumber << endl;
        outFile << "Passenger Name: " << passenger.passenger_name << endl;
        outFile << "Contact: " << passenger.passenger_contact << endl;
        outFile << "Source: " << passenger.source << endl;
        outFile << "Destination: " << passenger.destination << endl;
         outFile << "Price: " << passenger.price << endl;
        outFile << "-------------------------------------------------" << endl;
        outFile.close();
        cout << "Ticket booked successfully!" << endl;
    } else {
        cout << "Error opening file!" << endl;
    }
}

void printTicket() {
    ifstream inFile("tickets.txt");
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}

void deleteTicket() {
    ifstream inFile("tickets.txt");
    ofstream tempFile("temp.txt");
    string line;
    int seatNum;
    bool found = false;

    cout << "Enter seat number to delete: ";
    cin >> seatNum;
    string seatNumStr = "Seat Number: " + to_string(seatNum);

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find(seatNumStr) != string::npos) {
                found = true;
                for (int i = 0; i < 5; ++i) {
                    getline(inFile, line); 
                }
            } else {
                tempFile << line << endl; 
            }
        }
        inFile.close();
        tempFile.close();
        
        if (found) {
            remove("tickets.txt"); 
            rename("temp.txt", "tickets.txt"); 
            cout << "" << endl;
            cout << "" << endl;
            cout << "Ticket for seat number " << seatNum << " deleted!" << endl;
        } else {
            remove("temp.txt"); 
            cout << "Seat number not found!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }
}

void editTicket() {
    ifstream inFile("tickets.txt");
    ofstream tempFile("temp.txt");
    string line;
    int seatNum;
    bool found = false;

    cout << "Enter seat number to modify: ";
    cin >> seatNum;
    string seatNumStr = "Seat Number: " + to_string(seatNum);

    if (inFile.is_open() && tempFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find(seatNumStr) != string::npos) {
                found = true;
                Passenger passenger;
                for (int i = 0; i < 5; ++i) {
                    getline(inFile, line);
                }

                cout << "Enter new name: ";
                cin.ignore(); 
                getline(cin, passenger.passenger_name);
                cout << "Enter new contact number: ";
                cin >> passenger.passenger_contact;
                cout << "Enter new source station: ";
                cin.ignore(); 
                getline(cin, passenger.source);
                cout << "Enter new destination station: ";
                getline(cin, passenger.destination);
                cout << "Enter new price: ";
                cin >> passenger.price;

                tempFile << "Seat Number: " << seatNum << endl;
                tempFile << "Passenger Name: " << passenger.passenger_name << endl;
                tempFile << "Contact: " << passenger.passenger_contact << endl;
                tempFile << "Source: " << passenger.source << endl;
                tempFile << "Destination: " << passenger.destination << endl;
                tempFile << "Price: " << passenger.price << endl;
                drawLine();


                cout << "Ticket modified successfully!" << endl;

            } else {
                tempFile << line << endl;
            }
        }

        inFile.close();
        tempFile.close();

        if (found) {
            remove("tickets.txt");
            rename("temp.txt", "tickets.txt");
        } else {
            remove("temp.txt");
            cout << "Seat number not found!" << endl;
        }
    } else {
        cout << "Error opening file!" << endl;
    }
}

void ticketModification() {
    int modificationChoice;

    cout << "What would you like to do?" << endl;
    cout << "                1. Modify Ticket" << endl;
    cout << "                2. Delete Ticket" << endl;
    cout << "                3. Cancel" << endl;
    drawLine();
    cout << "Enter your choice: ";
    cin >> modificationChoice;

    switch (modificationChoice) {
        case 1:
            editTicket();
            break;
        case 2:
            deleteTicket();
            break;
        case 3:
            cout << "Modification cancelled." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}

int main() {
    drawLine();
    cout << "                       Welcome to the bus reservation system" << endl;
    drawLine();
    int choice;
    do {
        cout << "" << endl;
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "" << endl;
        cout << "" << endl;

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                ticketModification();
                break;
            case 3:
                printTicket();
                break;
            case 4:
                cout << "Exiting the system..." << endl;
                break;
            default:
                cout << "Invalid Choice." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
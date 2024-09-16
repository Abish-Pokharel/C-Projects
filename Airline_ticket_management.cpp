#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Flight {
    string flightNumber;
    string route;
    int availableSeats;
    double price;
};

struct Ticket {
    string name;
    string phoneNumber;
    int age;
    string flightNumber;
    string route;
    int seatNumber;
    double price;
};

Ticket lastBookedTicket;
bool isTicketBooked = false;

void displayFlights(Flight flights[], int size) {
    cout << "\nAvailable Flights:\n";
    for (int i = 0; i < size; i++) {
        cout << "Flight Number: " << flights[i].flightNumber
             << "\tRoute: " << flights[i].route
             << "\tAvailable Seats: " << flights[i].availableSeats
             << "\tPrice: Rs." << flights[i].price << endl;
    }
}

void bookTicket(Flight flights[], int size) {
    string flightNumber;
    cout << "\nEnter Flight Number to book: ";
    cin >> flightNumber;
    cin.ignore();  // Clear input buffer before taking string inputs

    bool flightFound = false;
    for (int i = 0; i < size; i++) {
        if (flights[i].flightNumber == flightNumber) {
            flightFound = true;
            if (flights[i].availableSeats > 0) {
                Ticket ticket;
                cout << "Enter your phone number: ";
                getline(cin, ticket.phoneNumber);  // Take phone number as string
                cout << "Enter your name: ";
                getline(cin, ticket.name);  // Take name as string
                cout << "Enter your age: ";
                cin >> ticket.age;
                cout << "Choose a seat number (1 to " << flights[i].availableSeats << "): ";
                cin >> ticket.seatNumber;
                
                if (ticket.seatNumber < 1 || ticket.seatNumber > flights[i].availableSeats) {
                    cout << "Invalid seat number. Please choose between 1 and " << flights[i].availableSeats << ".\n";
                    return;
                }

                ticket.flightNumber = flights[i].flightNumber;
                ticket.route = flights[i].route;
                ticket.price = flights[i].price;

                flights[i].availableSeats--;  // Decrease available seats

                ofstream ticketFile("bastola.txt", ios::app);
                if (ticketFile.is_open()) {
                    ticketFile << "Phone Number: " << ticket.phoneNumber << "\n";
                    ticketFile << "Name: " << ticket.name << "\n";
                    ticketFile << "Age: " << ticket.age << "\n";
                    ticketFile << "Flight Number: " << ticket.flightNumber << "\n";
                    ticketFile << "Route: " << ticket.route << "\n";
                    ticketFile << "Seat Number: " << ticket.seatNumber << "\n";
                    ticketFile << "Price: Rs." << ticket.price << "\n";
                    ticketFile << "-------------------------\n";
                    ticketFile.close();
                    cout << "Ticket booked successfully!\n";

                    lastBookedTicket = ticket;
                    isTicketBooked = true;
                } else {
                    cout << "Error opening the tickets file.\n";
                }
            } else {
                cout << "No available seats on this flight.\n";
            }
            break;
        }
    }

    if (!flightFound) {
        cout << "Flight not found. Please try again.\n";
    }
}

void printTicketByPhoneNumber() {
    string phoneNumber;
    cout << "Enter your phone number to retrieve your ticket: ";
    cin.ignore();  // Clear input buffer
    getline(cin, phoneNumber);

    ifstream ticketFile("bastola.txt");
    if (!ticketFile.is_open()) {
        cout << "Error opening the tickets file.\n";
        return;
    }

    string line;
    bool ticketFound = false;
    while (getline(ticketFile, line)) {
        if (line.find("Phone Number: " + phoneNumber) != string::npos) {
            ticketFound = true;
            cout << "\n**** Ticket Details ****\n";
            cout << line << endl;  // Print phone number line
            while (getline(ticketFile, line) && line != "-------------------------") {
                cout << line << endl;  // Print until delimiter is reached
            }
            cout << "-------------------------\n";
            break;
        }
    }

    if (!ticketFound) {
        cout << "Ticket not found for phone number: " << phoneNumber << endl;
    }

    ticketFile.close();
}

void printAllTickets() {
    ifstream ticketFile("bastola.txt");

    if (!ticketFile.is_open()) {
        cout << "Error opening the tickets file.\n";
        return;
    }

    cout << "\n**** All Booked Tickets ****\n";
    string line;
    while (getline(ticketFile, line)) {
        cout << line << endl;
    }

    ticketFile.close();
}

void adminPanel(Flight flights[], int& size) {
    const string adminUsername = "admin@gmail.com";
    const string adminPassword = "admin123";
    string password, userName;
    
    cout << "\nEnter Admin Username: ";
    cin >> userName;
    cout << "\nEnter Admin Password: ";
    cin >> password;

    if (adminUsername != userName || adminPassword != password) {
        cout << "Invalid username or password! Access denied.\n";
        return;
    }

    int choice;
    do {
        cout << "\n**** Admin Panel ****\n";
        cout << "1. View All Flights\n";
        cout << "2. Add a New Flight\n";
        cout << "3. Print All Tickets\n";
        cout << "4. Exit Admin Panel\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayFlights(flights, size);
        } else if (choice == 2) {
            if (size < 10) {
                Flight newFlight;
                cout << "Enter Flight Number: ";
                cin >> newFlight.flightNumber;
                cout << "Enter Route: ";
                cin.ignore();
                getline(cin, newFlight.route);
                cout << "Enter Available Seats: ";
                cin >> newFlight.availableSeats;
                cout << "Enter Price: ";
                cin >> newFlight.price;

                flights[size] = newFlight;
                size++;
                cout << "New flight added successfully!\n";
            } else {
                cout << "Cannot add more flights. Maximum limit reached.\n";
            }
        } else if (choice == 3) {
            printAllTickets();
        } else if (choice == 4) {
            cout << "Exiting Admin Panel...\n";
        } else {
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 4);
}

int main() {
    Flight flights[10] = {
        {"AI101", "Kathmandu to Bhairawa", 50, 5000},
        {"BA202", "Kathmandu to Lukla", 35, 6000},
        {"DL303", "Kathmandu to Nepalgunj", 20, 4000},
        {"AI404", "Kathmandu to Pokhara", 50, 5000},
        {"BA505", "Kathmandu to Biratnagar", 35, 6000},
        {"DL605", "Bhairawa to Kathmandu", 20, 4000}
    };

    int size = 6;
    int choice;
    do {
        cout << "\n**** Flight Booking System ****\n";
        cout << "1. View Available Flights\n";
        cout << "2. Book a Ticket\n";
        cout << "3. Admin Panel\n";
        cout << "4. Print Ticket\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            displayFlights(flights, size);
        } else if (choice == 2) {
            bookTicket(flights, size);
        } else if (choice == 3) {
            adminPanel(flights, size);
        } else if (choice == 4) {
            printTicketByPhoneNumber();
        } else if (choice == 5) {
            cout << "Thank you for using the Flight Booking System!\n";
        } else {
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
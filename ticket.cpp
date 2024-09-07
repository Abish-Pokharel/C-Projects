#include<iostream>
#include<fstream>
using namespace std;

const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string RESET = "\033[0m"; 


struct Passenger{
    string passenger_name;
    int passenger_age;
    string passenger_contact;
    int seatNumber;
    string source;
    string destination;
};


void drawLine(){
    cout << "-------------------------------------------------------------------------------"<< endl;
}


void displayMenu() {
    drawLine();
    cout << GREEN << "                       Welcome to the bus reservation system" << RESET << endl;
    drawLine();
    cout <<"" << endl;
    cout <<"" << endl;
    cout << BLUE <<"What do you want to do ?"<< RESET << endl;
    cout << MAGENTA << "            1. Seat availability " << RESET << endl;
    cout << MAGENTA << "            2. Book ticket" << RESET << endl;
    cout << MAGENTA << "            3. Ticket modification" << RESET << endl;
    cout << MAGENTA << "            4. Print ticket" << RESET << endl;
    cout << RED << "            5. Quit" << RESET << endl;
    drawLine();
}


void bookTicket(){
    Passenger passenger;
    ofstream outFile;
    

}
void ticketModification(){}
void printTicket(){}

void seatAvailability(){
    cout << CYAN << "Under construction.........." << RESET << endl;
}


int main()
{
    displayMenu();
    int choice;
    cin >> choice ;
    switch (choice)
    {
    case 1:
        seatAvailability();
        break;
    
    case 2:
        bookTicket();
        break;

     case 3:
        ticketModification();
        break;
    
     case 4:
        printTicket();
        break;

    case 5: 
        cout << RED << "Exiting the system..." << RESET << endl;
        return 0;
        break;

    default:
        cout << RED << "Invalid Choice." << RESET << endl;
        break;
    }

    return 0;
}
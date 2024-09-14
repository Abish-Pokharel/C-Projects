#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Customer {
public:
    string name;
    string password;
    double walletUSD = 100000;
    double walletNPR = 0;
    double expensesUSD = 0;
    double expensesNPR = 0;
    vector<string> bookedRestaurants;
    vector<string> bookedHotels;

    void registerCustomer() {
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> password;
        saveCustomerData();
        cout << "Registration complete!" << endl;
    }

    bool login() {
        ifstream inFile(name + ".txt");
        if (!inFile) {
            cout << "No such customer found! Please register first." << endl;
            return false;
        }

        string inputName, inputPassword;
        while (true) {
            cout << "Enter your name: ";
            cin >> inputName;
            cout << "Enter your password: ";
            cin >> inputPassword;

            if (inputName == name && inputPassword == password) {
                cout << "Welcome, " << name << "!" << endl;
                return true;
            } else {
                cout << "Incorrect name or password! Try again." << endl;
            }
        }
    }

    void loadCustomerData() {
        ifstream inFile(name + ".txt");
        if (!inFile) return;

        getline(inFile, name);
        getline(inFile, password);
        inFile >> walletUSD >> walletNPR >> expensesUSD >> expensesNPR;
        inFile.ignore();

        string booking;
        while (getline(inFile, booking)) {
            if (booking.find("Restaurant:") != string::npos) {
                bookedRestaurants.push_back(booking);
            } else if (booking.find("Hotel:") != string::npos) {
                bookedHotels.push_back(booking);
            }
        }

        inFile.close();
    }

    void saveCustomerData() {
        ofstream outFile(name + ".txt");
        outFile << name << "\n" << password << "\n" << walletUSD << "\n" << walletNPR << "\n" << expensesUSD << "\n" << expensesNPR << "\n";
        for (const auto& booking : bookedRestaurants) {
            outFile << booking << endl;
        }
        for (const auto& booking : bookedHotels) {
            outFile << booking << endl;
        }
        outFile.close();
    }

    void walletSection() {
        cout << "Wallet: " << endl;
        cout << "USD: $" << walletUSD << endl;
        cout << "NPR: Rs " << walletNPR << endl;
        cout << "Expenses USD: $" << expensesUSD << endl;
        cout << "Expenses NPR: Rs " << expensesNPR << endl;
    }

    void currencyExchange() {
        char option;
        double amount;
        cout << "A. Hello Exchange Center (1 USD = 130 NPR)\nB. Bye Exchange Center (1 USD = 132 NPR)" << endl;
        cout << "Select option: ";
        cin >> option;
        cout << "Enter amount to exchange in USD: ";
        cin >> amount;

        if (option == 'A' || option == 'a') {
            walletUSD -= amount;
            walletNPR += amount * 130;
        } else if (option == 'B' || option == 'b') {
            walletUSD -= amount;
            walletNPR += amount * 132;
        } else {
            cout << "Invalid option!" << endl;
            return;
        }

        expensesUSD += amount;
        saveCustomerData();
        cout << "Exchange complete!" << endl;
    }

    void viewRestaurants() {
        ifstream restaurantFile("restaurants.txt");
        string name, about;
        double price;

        cout << "Available Restaurants:" << endl;
        while (getline(restaurantFile, name)) {
            getline(restaurantFile, about);
            restaurantFile >> price;
            restaurantFile.ignore();
            cout << name << endl;
            cout << "   About: " << about << endl;
            cout << "   Price: NPR " << price << " per day" << endl;
        }
        restaurantFile.close();
    }

    void viewHotels() {
        ifstream hotelFile("hotels.txt");
        string name, about;
        double price;

        cout << "Available Hotels:" << endl;
        while (getline(hotelFile, name)) {
            getline(hotelFile, about);
            hotelFile >> price;
            hotelFile.ignore();
            cout << name << endl;
            cout << "   About: " << about << endl;
            cout << "   Price: NPR " << price << " per day" << endl;
        }
        hotelFile.close();
    }

    void book() {
        char choice;
        cout << "Choose an option to book:\nA. Restaurant\nB. Hotel\n0. Exit" << endl;
        cin >> choice;

        if (choice == 'A' || choice == 'a') {
            viewRestaurants();
            cout << "Enter restaurant name to book: ";
            string restaurant;
            cin.ignore();
            getline(cin, restaurant);
            double price = 0;
            ifstream restaurantFile("restaurants.txt");
            string name, about;
            while (getline(restaurantFile, name)) {
                getline(restaurantFile, about);
                restaurantFile >> price;
                restaurantFile.ignore();
                if (name == restaurant) {
                    break;
                }
            }
            restaurantFile.close();

            if (find(bookedRestaurants.begin(), bookedRestaurants.end(), "Restaurant:" + restaurant) != bookedRestaurants.end()) {
                cout << "Already booked!" << endl;
                return;
            }
            if (walletNPR >= price) {
                walletNPR -= price;
                expensesNPR += price;
                bookedRestaurants.push_back("Restaurant:" + restaurant);
                saveCustomerData();
                cout << "Booking successful!" << endl;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        } else if (choice == 'B' || choice == 'b') {
            viewHotels();
            cout << "Enter hotel name to book: ";
            string hotel;
            cin.ignore();
            getline(cin, hotel);
            double priceNPR = 0;
            ifstream hotelFile("hotels.txt");
            string name, about;
            while (getline(hotelFile, name)) {
                getline(hotelFile, about);
                hotelFile >> priceNPR;
                hotelFile.ignore();
                if (name == hotel) {
                    break;
                }
            }
            hotelFile.close();

            if (find(bookedHotels.begin(), bookedHotels.end(), "Hotel:" + hotel) != bookedHotels.end()) {
                cout << "Already booked!" << endl;
                return;
            }
            if (walletNPR >= priceNPR) {
                walletNPR -= priceNPR;
                expensesNPR += priceNPR;
                bookedHotels.push_back("Hotel:" + hotel);
                saveCustomerData();
                cout << "Booking successful!" << endl;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        } else if (choice == '0') {
            cout << "Exiting booking menu." << endl;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
};

class Admin {
public:
    string username = "Biplob";
    string password = "333";
    map<string, pair<string, double>> restaurants;
    map<string, pair<string, double>> hotels;

    Admin() {
        loadAdminData();
    }

    bool login() {
        string inputUsername, inputPassword;
        while (true) {
            cout << "Enter admin username: ";
            cin >> inputUsername;
            cout << "Enter admin password: ";
            cin >> inputPassword;

            if (inputUsername == username && inputPassword == password) {
                cout << "Admin login successful!" << endl;
                return true;
            } else {
                cout << "Incorrect username or password! Try again." << endl;
            }
        }
    }

    void addHotel() {
        string hotelName, about;
        double pricePerDay;
        cout << "Enter hotel name: ";
        cin.ignore();
        getline(cin, hotelName);
        cout << "Enter about the hotel: ";
        getline(cin, about);
        cout << "Enter price per day (in NPR): ";
        cin >> pricePerDay;
        hotels[hotelName] = {about, pricePerDay};
        saveAdminData();
        cout << "Hotel added successfully!" << endl;
    }

    void addRestaurant() {
        string restaurantName, about;
        double pricePerDay;
        cout << "Enter restaurant name: ";
        cin.ignore();
        getline(cin, restaurantName);
        cout << "Enter about the restaurant: ";
        getline(cin, about);
        cout << "Enter price per day (in NPR): ";
        cin >> pricePerDay;

        restaurants[restaurantName] = {about, pricePerDay};
        saveAdminData();
        cout << "Restaurant added successfully!" << endl;
    }

    void viewHotels() {
        cout << "Available Hotels:" << endl;
        for (const auto& [name, details] : hotels) {
            cout << name << endl;
            cout << "   About: " << details.first << endl;
            cout << "   Price: NPR " << details.second << " per day" << endl;
        }
    }

       void viewRestaurants() {
        cout << "Available Restaurants:" << endl;
        for (const auto& [name, details] : restaurants) {
            cout << name << endl;
            cout << "   About: " << details.first << endl;
            cout << "   Price: NPR " << details.second << " per day" << endl;
        }
    }

    void saveAdminData() {
        ofstream restaurantFile("restaurants.txt");
        for (const auto& [name, details] : restaurants) {
            restaurantFile << name << endl;
            restaurantFile << details.first << endl;
            restaurantFile << details.second << endl;
        }
        restaurantFile.close();

        ofstream hotelFile("hotels.txt");
        for (const auto& [name, details] : hotels) {
            hotelFile << name << endl;
            hotelFile << details.first << endl;
            hotelFile << details.second << endl;
        }
        hotelFile.close();
    }

    void loadAdminData() {
        ifstream restaurantFile("restaurants.txt");
        string name, about;
        double price;

        while (getline(restaurantFile, name)) {
            getline(restaurantFile, about);
            restaurantFile >> price;
            restaurantFile.ignore();
            restaurants[name] = {about, price};
        }
        restaurantFile.close();

        ifstream hotelFile("hotels.txt");
        while (getline(hotelFile, name)) {
            getline(hotelFile, about);
            hotelFile >> price;
            hotelFile.ignore();
            hotels[name] = {about, price};
        }
        hotelFile.close();
    }
};

void displayCustomerMenu(Customer& customer) {
    int option;
    do {
        cout << "1. Wallet\n2. Currency Exchange\n3. View Hotels\n4. View Restaurants\n5. Book\n0. Exit\n";
        cout << "Select an option: ";
        cin >> option;
        switch (option) {
            case 1:
                customer.walletSection();
                break;
            case 2:
                customer.currencyExchange();
                break;
            case 3:
                customer.viewHotels();
                break;
            case 4:
                customer.viewRestaurants();
                break;
            case 5:
                customer.book();
                break;
        }
    } while (option != 0);
}

void displayAdminMenu(Admin& admin) {
    int option;
    do {
        cout << "1. Add Hotel\n2. Add Restaurant\n3. View Hotels\n4. View Restaurants\n0. Exit\n";
        cout << "Select an option: ";
        cin >> option;
        switch (option) {
            case 1:
                admin.addHotel();
                break;
            case 2:
                admin.addRestaurant();
                break;
            case 3:
                admin.viewHotels();
                break;
            case 4:
                admin.viewRestaurants();
                break;
        }
    } while (option != 0);
}

int main() {
    int mainOption;
    Customer customer;
    Admin admin;

    cout << "************* Smart Visit *************" << endl;
    cout << "1. Admin\n2. Customer\nSelect an option: ";
    cin >> mainOption;

    switch (mainOption) {
        case 1:
            if (admin.login()) {
                displayAdminMenu(admin);
            }
            break;
        case 2:
            cout << "1. Register\n2. Log in\n";
            int customerOption;
            cin >> customerOption;
            if (customerOption == 1) {
                customer.registerCustomer();
            }
            cout << "Enter customer name: ";
            cin >> customer.name;
            customer.loadCustomerData();
            if (customer.login()) {
                displayCustomerMenu(customer);
            }
            break;
        default:
            cout << "Invalid option!" << endl;
    }

    return 0;
}
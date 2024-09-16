#include <iostream>
#include <windows.h>
using namespace std;

bool GAMEOVER = false;

bool isDraw(char place[9]) {
    for (int i = 0; i < 9; i++) {
        if (place[i] != 'X' && place[i] != 'O') {
            return false; 
        }
    }
    return true; 
}

void gameOver(char place[9], string winner) {
    if ((place[0] == place[1] && place[0] == place[2]) ||
        (place[3] == place[4] && place[3] == place[5]) ||
        (place[6] == place[7] && place[7] == place[8]) ||
        (place[0] == place[3] && place[3] == place[6]) ||
        (place[1] == place[4] && place[4] == place[7]) ||
        (place[2] == place[5] && place[5] == place[8]) ||
        (place[0] == place[4] && place[0] == place[8]) ||
        (place[2] == place[4] && place[4] == place[6])) {
        system("Color 0A");
        cout << "Congrats! " << winner << " has won the match!" << endl;
        GAMEOVER = true;
    }
    else if (isDraw(place)) {
        system("Color 0C");
        cout << "The game is a draw!" << endl;
        GAMEOVER = true;
    }
}

int main() {
    char place[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    string name1, name2;
    int turn = 1, position;

    cout << "Enter name of player1 and player2: ";
    cin >> name1 >> name2;

    while (!GAMEOVER) {
        cout << place[0] << " | " << place[1] << " | " << place[2] << endl;
        cout << place[3] << " | " << place[4] << " | " << place[5] << endl;
        cout << place[6] << " | " << place[7] << " | " << place[8] << endl;

        if (turn == 1) {
            cout << "Choose your position " << name1 << ": ";
            cin >> position;
            if (position < 1 || position > 9 || place[position - 1] == 'X' || place[position - 1] == 'O') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }
            place[position - 1] = 'X';
            turn = 2;
        }
        else {
            cout << "Choose your position " << name2 << ": ";
            cin >> position;
            if (position < 1 || position > 9 || place[position - 1] == 'X' || place[position - 1] == 'O') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }
            place[position - 1] = 'O';
            turn = 1;
        }

        gameOver(place, turn == 1 ? name2 : name1);
    }

    return 0;
}
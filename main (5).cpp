#include <iostream>
#include <cstdlib>

using namespace std;

char board[9] = {'1','2','3','4','5','6','7','8','9'};
char newBoard[9] = {'1','2','3','4','5','6','7','8','9'};
char newX[9], newY[9];
char playerX[9], playerY[9];
int scoreX = 0, scoreY = 0, choice;
int result = -1;
char option;

#define RESET "\x1b[0m"
#define GOLDEN "\x1b[38;5;214m"

void mainScreen();
void points();
void gameBoard();
int gameStatus();
void mainMenu();
void userMoves();

void mainMenu() {
    system("clear");
    cout << "TIC - TAC - TOE !!!" << endl << "----------------------------------" << endl << endl;
    cout << "PLAYER 1 (X)   " << "VS" << "\tPLAYER 2 (O) : " << endl << endl << "**********************************" << endl << endl;
    
    cout << "Menu : \n" << endl;
    cout << "1. Play Game." << endl;
    cout << "2. View scoreboard." << endl;
    cout << "3. Exit." << endl;
    
    cout << "Choose your option (1/2/3): ";
    cin >> choice;
    cout << endl << endl << "**********************************" << endl << endl;
    
    if(choice == 1) {
        for(int i = 0; i < 9; ++i) {
            board[i] = newBoard[i];
        }
        gameBoard();
        cout << endl << endl << endl;
        userMoves();
    }
    else if(choice == 2) {
        points();
    }
    else if(choice == 3) {
        cout << "Thank you !" << endl;
        exit(0);
    }
    else {
        cout << "Invalid option chosen." << endl << endl << "**********************************" << endl << endl;
        mainMenu();
    }
}

void points() {
    cout << "Player 1 (X) Points: " << scoreX << endl;
    cout << "Player 2 (O) Points: " << scoreY << endl;
    cout << "-------------------------" << endl;
    cout << "Return to Main Menu? (y/n): ";
    cin >> option;
    if(option == 'y') {
        cout << endl;
        mainMenu();
    } else if(option == 'n') {
        cout << "Thanks for playing." << endl;
        exit(0);
    } else {
        cout << "Invalid option entered." << endl;
        points();
    }
}

void gameBoard() {
    cout << "-------------------" << endl;
    for(int i = 0; i < 9; i += 3) {
        cout << "| ";
        for(int j = i; j < i + 3; j++) {
            if (board[j] == 'X' || board[j] == 'O') {
                cout << ((board[j] == 'X') ? GOLDEN : GOLDEN) << board[j] << RESET;
            } else {
                cout << board[j];
            }
            cout << " | ";
        }
        cout << endl;
        cout << "|-----------|" << endl;
    }
}

void mainScreen() {
    cout << "Return to Main Menu? (y/n): ";
    cin >> option;
    system("clear");
    if(option == 'y') {
        for(int i = 0; i < 9; i++) {
            if(board[i] == 'X' || board[i] == 'O') {
                board[i] = newBoard[i];
                playerX[i] = newX[i];
                playerY[i] = newY[i];
            }
        }
        cout << endl << endl << "**********************************" << endl << endl;
        mainScreen();
    }
    else if(option == 'n') {
        cout << "Thanks for playing." << endl;
        exit(0);
    }
    else {
        cout << "Invalid option entered." << endl;
        mainMenu();
    }
} 

void userMoves() {
    do {
        system("clear");
        gameBoard();

        cout << "Enter move for Player X: ";
        int move;
        while (!(cin >> move) || move < 1 || move > 9 || (board[move - 1] == 'X' || board[move - 1] == 'O')) {
            cout << "Invalid input or cell already taken. Please enter a number between 1 and 9: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        board[move - 1] = 'X';

        result = gameStatus();
        if (result == 1) {
            system("clear");
            gameBoard();
            cout << "Player X wins!" << endl;
            scoreX++;
            points();
            break;
        } else if (result == 0) {
            system("clear");
            gameBoard();
            cout << "It's a draw!" << endl;
            points();
            break;
        }

        system("clear");
        gameBoard();

        cout << "Enter move for Player O: ";
        while (!(cin >> move) || move < 1 || move > 9 || (board[move - 1] == 'X' || board[move - 1] == 'O')) {
            cout << "Invalid input or cell already taken. Please enter a number between 1 and 9: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        board[move - 1] = 'O';

        result = gameStatus();
        if (result == 1) {
            system("clear");
            gameBoard();
            cout << "Player O wins!" << endl;
            scoreY++;
            points();
            break;
        } else if (result == 0) {
            system("clear");
            gameBoard();
            cout << "It's a draw!" << endl;
            points();
            break;
        }
    } while (result == -1);
}

int gameStatus() {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
            return 1;
    }

    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6])
            return 1;
    }

    if ((board[0] == board[4] && board[4] == board[8]) ||
        (board[2] == board[4] && board[4] == board[6]))
        return 1;

    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O')
            return -1;
    }

    return 0;
}

int main() {
    mainMenu();
    return 0;
}

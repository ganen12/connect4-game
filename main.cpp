#include <iostream>
#include <array> 
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

const char PLAYER1 = 'x';
const char PLAYER2 = 'o';
const int ROW = 6;
const int COLUMN = 7;

char board[6][7];

void displayMainMenu();
void resetBoard();
void displayBoard();
void player1Turn();
void player2Turn();
int checkFreeSpaces();
char checkWinner();
void printWinner(char);


int main() {
	char winner = ' ';
	char playAgain = ' ';

	do {
		resetBoard();

		while (winner == ' ' && checkFreeSpaces() != 0) {
			displayBoard();

			player1Turn();
			if (checkWinner() != ' ' || checkFreeSpaces() == 0) {
				break;
			}

			player2Turn();
			if (checkWinner() != ' ' || checkFreeSpaces() == 0) {
				break;
			}

		}
		
	} while (playAgain == 'Y' || playAgain == 'y');
	
	
	return 0;
}

void displayMainMenu() {
}

void resetBoard() {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7; ++j) {
			board[i][j] = ' ';
		}
	}
}

void displayBoard() {
	cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " | " << board[0][3] << " | " << board[0][4] << " | " << board[0][5] << " | " << board[0][6] << " ";
	cout << "\n---|---|---|---|---|---|---\n";
	cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " | " << board[1][3] << " | " << board[1][4] << " | " << board[1][5] << " | " << board[1][6] << " ";
	cout << "\n---|---|---|---|---|---|---\n";
	cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " | " << board[2][3] << " | " << board[2][4] << " | " << board[2][5] << " | " << board[2][6] << " ";
	cout << "\n---|---|---|---|---|---|---\n";
	cout << " " << board[3][0] << " | " << board[3][1] << " | " << board[3][2] << " | " << board[3][3] << " | " << board[3][4] << " | " << board[3][5] << " | " << board[3][6] << " ";
	cout << "\n---|---|---|---|---|---|---\n";
	cout << " " << board[4][0] << " | " << board[4][1] << " | " << board[4][2] << " | " << board[4][3] << " | " << board[4][4] << " | " << board[4][5] << " | " << board[4][6] << " ";
	cout << "\n---|---|---|---|---|---|---\n";
	cout << " " << board[5][0] << " | " << board[5][1] << " | " << board[5][2] << " | " << board[5][3] << " | " << board[5][4] << " | " << board[5][5] << " | " << board[5][6] << " ";
	cout << "\n";

}

int checkFreeSpaces() {
	int freeSpaces = 42;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (board[i][j] != ' ') {
				freeSpaces--;
			}
		}
	}

	return freeSpaces;
}

// nantinya player turn akan menjadi satu fungsi
void player1Turn() {
	
	int colPlacement;
	int rowPlacement = 5;

	do {
		
		cout << "Pilih kolom (1-7):";
		cin >> colPlacement;

		// mungkin tidak digunakan, karena setiap playerTurn() dipanggil, rowPlacement = 5.
		// tanpa memerhatikan jika ada placement di bawah input colPlacement, rowPlacement akan selalu dikurangi 1 sampai ada tempat kosong 
		for (int i = 0; i < 6; i++) {
			if (board[5][colPlacement - 1] == ' ') {
				rowPlacement = 5;
				break;
			}
		}

		while (rowPlacement >= 0) {
			if (board[rowPlacement][colPlacement - 1] != ' ') {
				rowPlacement--;
			}
			else if (board[rowPlacement][colPlacement - 1] == ' ') {
				board[rowPlacement][colPlacement - 1] = PLAYER1;
				break;
			} 
		}

		if (rowPlacement < 0) {
			cout << "No more space available, try another column!"<<endl;
		}
		else if (board[rowPlacement][colPlacement - 1] == PLAYER1) {
			break;
		}

	} while (true);

}

void player2Turn() {

	int colPlacement;
	int rowPlacement = 5;
	do {

		cout << "Pilih kolom (1-7):";
		cin >> colPlacement;

		for (int i = 0; i < 6; i++) {
			if (board[5][colPlacement - 1] == ' ') {
				rowPlacement = 5;
				break;
			}
		}

		while (rowPlacement >= 0) {
			if (board[rowPlacement][colPlacement - 1] != ' ') {
				rowPlacement--;
			}
			else if (board[rowPlacement][colPlacement - 1] == ' ') {
				board[rowPlacement][colPlacement - 1] = PLAYER2;
				break;
			}
		}

		if (rowPlacement < 0) {
			cout << "No more space available, try again" << endl;
		}
		else if (board[rowPlacement][colPlacement - 1] == PLAYER2) {
			break;
		}

	} while (true);

}

char checkWinner() {

}
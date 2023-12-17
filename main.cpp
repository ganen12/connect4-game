#include <iostream>
#include <array> 
#include <cctype>
#include <cstdlib>


using namespace std;

const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

char board[6][7];

void displayMainMenu();
void resetBoard();
void displayBoard();
int checkFreeSpaces();
char checkWinner();
void printWinner(char);
void placeChecker(char player);
void aiMove();


int main() {
	char winner;
	char playAgain = ' ';
	char menuOption;

	do {
		winner = ' ';

		resetBoard();
		displayMainMenu();

		cout << "\nPilih:\n-> ";
		cin >> menuOption;

		switch (menuOption) {
			case '1': // Player vs Player
				while (winner == ' ' && checkFreeSpaces() != 0) {

					system("cls");
					displayBoard();

					placeChecker(PLAYER1);
					if (checkWinner() != ' ' || checkFreeSpaces() == 0) {
						winner = PLAYER1;
						break;
					}

					system("cls");
					displayBoard();

					placeChecker(PLAYER2);
					if (checkWinner() != ' ' || checkFreeSpaces() == 0) {
						winner = PLAYER2;
						break;
					}
				}
				break;

			case '2': // Player vs Bot

				break;

			case '3': // Keluar

				return 0;
		}
		
		system("cls");
		displayBoard();
		printWinner(winner);

		cout << "\n\tPlay again? (y/n):";
		cin >> playAgain;

		system("cls");
		
	} while (playAgain == 'Y' || playAgain == 'y');
	
	cout << "\nTerima kasih sudah bermain Connect 4!\n";

	return 0;
}

void displayMainMenu() {
	cout << "  _____                            _     ______               \n";
	cout << " / ____|                          | |   |  ____|              \n";
	cout << "| |     ___  _ __  _ __   ___  ___| |_  | |__ ___  _   _ _ __ \n";
	cout << "| |    / _ \\| '_ \\| '_ \\ / _ \\/ __| __| |  __/ _ \\| | | | '__|\n";
	cout << "| |___| (_) | | | | | | |  __/ (__| |_  | | | (_) | |_| | |   \n";
	cout << " \\_____\\___/|_| |_|_| |_|\\___|\\___|\\__| |_|  \\___/ \\__,_|_|   \n";
	cout << "                                                               \n";
	cout << "                                                              \n";

	cout << "1. Player VS Player \n";
	cout << "\n2. Player VS Bot\n";
	cout << "\n3. Keluar\n";
}

void resetBoard() {
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 7; ++j) {
			board[i][j] = ' ';
		}
	}
}

void displayBoard() {

	// keren bet jirr
	cout << "  _____                            _     ______               \n";
	cout << " / ____|                          | |   |  ____|              \n";
	cout << "| |     ___  _ __  _ __   ___  ___| |_  | |__ ___  _   _ _ __ \n";
	cout << "| |    / _ \\| '_ \\| '_ \\ / _ \\/ __| __| |  __/ _ \\| | | | '__|\n";
	cout << "| |___| (_) | | | | | | |  __/ (__| |_  | | | (_) | |_| | |   \n";
	cout << " \\_____\\___/|_| |_|_| |_|\\___|\\___|\\__| |_|  \\___/ \\__,_|_|   \n";
	cout << "                                                               \n";
	cout << "                                                              \n";

	cout << "\t      " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " | " << board[0][3] << " | " << board[0][4] << " | " << board[0][5] << " | " << board[0][6] << " ";
	cout << "\n\t     ---|---|---|---|---|---|---\n";
	cout << "\t      " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " | " << board[1][3] << " | " << board[1][4] << " | " << board[1][5] << " | " << board[1][6] << " ";
	cout << "\n\t     ---|---|---|---|---|---|---\n";
	cout << "\t      " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " | " << board[2][3] << " | " << board[2][4] << " | " << board[2][5] << " | " << board[2][6] << " ";
	cout << "\n\t     ---|---|---|---|---|---|---\n";
	cout << "\t      " << board[3][0] << " | " << board[3][1] << " | " << board[3][2] << " | " << board[3][3] << " | " << board[3][4] << " | " << board[3][5] << " | " << board[3][6] << " ";
	cout << "\n\t     ---|---|---|---|---|---|---\n";
	cout << "\t      " << board[4][0] << " | " << board[4][1] << " | " << board[4][2] << " | " << board[4][3] << " | " << board[4][4] << " | " << board[4][5] << " | " << board[4][6] << " ";
	cout << "\n\t     ---|---|---|---|---|---|---\n";
	cout << "\t      " << board[5][0] << " | " << board[5][1] << " | " << board[5][2] << " | " << board[5][3] << " | " << board[5][4] << " | " << board[5][5] << " | " << board[5][6] << " ";
	cout << "\n\t      1   2   3   4   5   6   7 \n";
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

void placeChecker(char player) {

	int colPlacement;

	switch (player) {
		case 'X':
			cout << "\n    --> PLAYER 1'S TURN (X) <--        PLAYER 2\n\n";
			break;
		case 'O':
			cout << "\n        PLAYER 1                   --> PLAYER 2'S TURN (O) <--\n\n";
			break;
	}

	do {
		int rowPlacement = 5;

		// Validasi input
		while (true) {
			cout << "\tPilih kolom (1-7):\n\t-> ";
			cin >> colPlacement;
			if (colPlacement >= 1 && colPlacement <= 7) {
				break; // Valid input, exit loop
			}
			else {
				cout << "\n\tInvalid input. Masukkan angka 1-7.\n";
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			}
		}

		while (rowPlacement >= 0) {
			if (board[rowPlacement][colPlacement - 1] != ' ') {
				rowPlacement--;
			}
			else if (board[rowPlacement][colPlacement - 1] == ' ') {
				board[rowPlacement][colPlacement - 1] = player;
				break;
			}
		}

		if (board[rowPlacement][colPlacement - 1] == player) {
			break;
		}

		cout << "\n\tTidak ada lagi ruang yang tersedia, coba kolom lain!" << endl;

	} while (true);

}

void aiMove() {

	
}

char checkWinner() {

	// Check secara horizontal
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (board[i][j] == board[i][j + 1] &&
				board[i][j] == board[i][j + 2] &&
				board[i][j] == board[i][j + 3] &&
				board[i][j] != ' ') {
				return board[i][j];
			}
		}
	}

	// Check secara vertikal
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (board[i][j] == board[i + 1][j] &&
				board[i][j] == board[i + 2][j] &&
				board[i][j] == board[i + 3][j] &&
				board[i][j] != ' ') {
				return board[i][j];
			}
		}
	}

	// Check secara diagonal (dari kiri atas ke kanan bawah)
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (board[i][j] == board[i + 1][j + 1] &&
				board[i][j] == board[i + 2][j + 2] &&
				board[i][j] == board[i + 3][j + 3] &&
				board[i][j] != ' ') {
				return board[i][j];
			}
		}
	}

	// Check secara diagonal (dari kanan atas ke kiri bawah)
	for (int i = 0; i < 3; ++i) {
		for (int j = 3; j < 7; ++j) {
			if (board[i][j] == board[i + 1][j - 1] &&
				board[i][j] == board[i + 2][j - 2] &&
				board[i][j] == board[i + 3][j - 3] &&
				board[i][j] != ' ') {
				return board[i][j];
			}
		}
	}

	return ' '; // jika belum ada checker yang 4 kali berurutan, return char kosong
}

void printWinner(char winner) {
	if (winner == PLAYER1) {
		cout << "\tPlayer 1 (X) wins!" << endl;
	}
	else if (winner == PLAYER2) {
		cout << "\tPlayer 2 (O) wins!" << endl;
	}
	else {
		cout << "\tIt's a draw!" << endl;
	}
}

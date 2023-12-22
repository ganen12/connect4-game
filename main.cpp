#include <iostream>
#include <array> 
#include <cctype>
#include <ctime>
#include <Windows.h>

using namespace std;

const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
const char AI = 'O';
char board[6][7];

void displayMainMenu();
void resetBoard();
void displayBoard();
int checkFreeSpaces();
char checkWinner();
void printWinner(char);
void placeChecker(char player);
void aiMove();
int minimax(int depth, bool isMaximizing);
bool isValidMove(int col);
int dropPiece(int col);
void undoMove(int col);
int evaluateBoard();
void placeCheckerAI(char player, int col);
void computerMove();



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
			while (winner == ' ' && checkFreeSpaces() != 0) { // winner == ' ' mungkin akan dihapus, supaya hasil permainan seri bisa ditampilkan

				system("cls");
				displayBoard();

				placeChecker(PLAYER1);
				if (checkWinner() != ' ') {
					winner = PLAYER1;
					break;
				}

				system("cls");
				displayBoard();

				placeChecker(PLAYER2);
				if (checkWinner() != ' ') {
					winner = PLAYER2;
					break;
				}
			}
			break;

		case '2': // Player vs Bot
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

				Sleep(100);
				computerMove();
				if (checkWinner() != ' ' || checkFreeSpaces() == 0) {
					winner = PLAYER2;
					break;
				}
			}

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

	int col;
	int row;

	switch (player) {
		case 'X':
			cout << "\n    --> PLAYER 1'S TURN (X) <--         \n\n";
			break;
		case 'O':
			cout << "\n                             --> PLAYER 2'S TURN (O) <--\n\n";
			break;
	}

	do {

		// Validasi input
		while (true) {
			cout << "\tPilih kolom (1-7):\n\t-> ";
			cin >> col;
			if (col >= 1 && col <= 7) {
				break; // Valid input, exit loop
			}
			else {
				cout << "\n\tInvalid input. Masukkan angka 1-7.\n";
				cin.clear(); // Clear error flag
				cin.ignore();
				// cin.ignore(numeric_limits<streamsize>::max(), '\n');  Clear input buffer
			}
		}

		// Meletakkan checker
		row = 5;

		while (row >= 0) {
			if (board[row][col - 1] != ' ') {
				row--;
			}
			else if (board[row][col - 1] == ' ') {
				board[row][col - 1] = player;
				return;
			}
		}

		cout << "\n\tTidak ada lagi ruang yang tersedia, coba kolom lain!" << endl;

	} while (true);

}

// move AI demgam menggunakan algoritma simple
void computerMove() {
	srand(static_cast<unsigned int>(time(0)));

	int randomCol;
	int row;

	// Cek jika ada move yang bisa memenangkan AI, jika ada maka letakkan checker di kotak yang terpilih
	// Bisa dibilang, AI akan mengecek jika ada 'O' yang sudah 3x berurutan
	for (int col = 0; col < 7; ++col) {

		row = 5;

		while (row >= 0) {
			if (board[row][col] == ' ') {
				board[row][col] = AI;
				if (checkWinner() == AI) {
					return;  // AI menang, tidak perlu lanjut
				}
				board[row][col] = ' ';  // Move akan di-undo jika move tersebut tidak memenangkan AI
				break;
			}
			else if (board[row][col] != ' ') {
				row--;
			}
		}
	}
	// Cek jika ada move untuk bisa mem-blok lawan agar lawan tidak menang
	// Bisa dibilang, AI akan mengecek jika ada 'X' yang sudah 3x berurutan
	for (int col = 0; col < 7; ++col) {

		row = 5;

		while (row >= 0) {
			if (board[row][col] == ' ') {
				board[row][col] = PLAYER1;  // Anggap bahwa kotak yang ini diisi lawan
				if (checkWinner() == PLAYER1) {
					board[row][col] = AI;  // Mem-blok move yang memenangkan lawan
					return;
				}
				board[row][col] = ' ';  // Move akan di-undo jika tidak memblok lawan
				break;
			}
			else if (board[row][col] != ' ') {
				row--;
			}
		}
	}
	// Jika tidak ada dari kedua move di atas yang ditemukan, maka buat random move dari kolom 1-7
	do {
		randomCol = rand() % 7 + 1;
		row = 5;

		while (row >= 0) {
			if (board[row][randomCol - 1] == ' ') {
				board[row][randomCol - 1] = AI;
				return;
			}
			row--;
		}
	} while (true);
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

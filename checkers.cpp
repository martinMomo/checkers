// (c) copyright by Earl Martin Momongan
// C++ Checkers Game

#include<iostream>
#include<string>
#include<ctime>
#include<cmath>
#include<Windows.h>

using namespace std;

void initPieces(char m[][8]); // initializes game pieces
void setupBoard(char m[][8]); // prints out the board
void jumping(char m[][8], int x, int y);

int main() {
	// set up the console window resolution
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 600, 800, TRUE);

	char matrix[8][8];
	int posx, posy, roll;
	int comx, comy;
	bool running = true, error = true, getmove = true;
	string input;

	initPieces(matrix);

	while (running) {
		cout << "(c) copyright by Earl Martin Momongan" << endl;
		cout << "C++ Checkers Game" << endl << endl;

		setupBoard(matrix);

		// ask player which piece to move
		while (error) {
			cout << "Player: x | Computer: o" << endl;
			cout << "Please pick a piece to move" << endl;
			cout << "Coordinate X: ";
			cin >> posx;
			cout << "Coordinate Y: ";
			cin >> posy;
			cout << endl;

			if (matrix[posx][posy] != 'x') {
				cout << "ERROR! INVALID INPUT! TRY AGAIN!" << endl << endl;
			}
			else
				error = false;
		}
		error = true;

		// ask player where to move
		jumping(matrix, posx, posy);

		cout << endl << "Please wait for computer move..." << endl;

		// enemy turn
		// simple random move generator
		while (getmove) {
			srand(time(NULL));
			comx = rand() % 7;
			comy = rand() % 7;		
			while (matrix[comx][comy] != 'o') {
				comx = (rand() % 7);
				comy = (rand() % 7);
			}
			roll = rand() % 10;

			if (roll > 5) {
				if (matrix[comx - 1][comy + 1] == ' ') {
					matrix[comx - 1][comy + 1] = 'o';
					matrix[comx][comy] = ' ';
					getmove = false;
				}
				else if (matrix[comx + 1][comy + 1] == ' ') {
					matrix[comx + 1][comy + 1] = 'o';
					matrix[comx][comy] = ' ';
					getmove = false;
				}
				else if (matrix[comx - 1][comy + 1] == 'x' && matrix[comx - 2][comy + 2] == ' ') {
					matrix[comx - 2][comy + 2] = 'o';
					matrix[comx][comy] = ' ';
					matrix[comx - 1][comy + 1] = ' ';
					getmove = false;
				}
				else if (matrix[comx + 1][comy + 1] == 'x' && matrix[comx - 2][comy + 2] == ' ') {
					matrix[comx - 2][comy + 2] = 'o';
					matrix[comx][comy] = ' ';
					matrix[comx + 1][comy + 1] = ' ';
					getmove = false;
				}
				else
					getmove = true;
			}
			else {
				if (matrix[comx + 1][comy + 1] == ' ') {
					matrix[comx + 1][comy + 1] = 'o';
					matrix[comx][comy] = ' ';
					getmove = false;
				}
				else if (matrix[comx - 1][comy + 1] == ' ') {
					matrix[comx - 1][comy + 1] = 'o';
					matrix[comx][comy] = ' ';
					getmove = false;
				}
				else if (matrix[comx + 1][comy + 1] == 'x' && matrix[comx - 2][comy + 2] == ' ') {
					matrix[comx - 2][comy + 2] = 'o';
					matrix[comx][comy] = ' ';
					matrix[comx + 1][comy + 1] = ' ';
					getmove = false;
				}
				else if (matrix[comx - 1][comy + 1] == 'x' && matrix[comx - 2][comy + 2] == ' ') {
					matrix[comx - 2][comy + 2] = 'o';
					matrix[comx][comy] = ' ';
					matrix[comx - 1][comy + 1] = ' ';
					getmove = false;
				}
				else
					getmove = true;
			}
		}
		getmove = true;
		system("CLS");
	}

	return 0;
}

void initPieces(char m[][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (((i % 2) == 0 && (j % 2) == 0) ||
				(i % 2) != 0 && (j % 2) != 0)
				m[i][j] = '-';
			else
				m[i][j] = ' ';
		}
	}

	// setup o pieces
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if ((j % 2) == 0 && (i % 2) != 0)
				m[i][j] = 'o';
			else if ((j % 2) != 0 && (i % 2) == 0)
				m[i][j] = 'o';
		}
	}
	// setup x pieces
	for (int i = 0; i < 8; i++) {
		for (int j = 5; j < 8; j++) {
			if ((j % 2) == 0 && (i % 2) != 0)
				m[i][j] = 'x';
			else if ((j % 2) != 0 && (i % 2) == 0)
				m[i][j] = 'x';
		}
	}
}

void setupBoard(char m[][8]) {
	cout << "  ";
	for (int i = 0; i < 8; i++) {
		cout << "  " << i << " ";
	}
	cout << endl;
	for (int j = 0; j < 8; j++) {
		cout << "  ";
		for (int i = 0; i < 8; i++) {
			cout << "----";
		}
		cout << "-\n";
		cout << j << " ";
		for (int i = 0; i < 9; i++) {
			if (i != 8)
				cout << "| " << m[i][j] << " ";
			else
				cout << "| " << "  ";
		}
		cout << endl;
	}
	cout << "  ";
	for (int i = 0; i < 8; i++) {
		cout << "----";
	}
	cout << "-" << endl << endl;
}

void jumping(char m[][8], int x, int y) {
	bool error = true;
	int movx, movy;
	while (error) {
		cout << "Please pick a coordinate you'd like to move to" << endl;
		cout << "Enter 0 and 0 to quit jumping" << endl;
		cout << "Coordinate X: ";
		cin >> movx;
		cout << "Coordinate Y: ";
		cin >> movy;

		// check to see if invalid move was made
		if (movx == 0 && movy == 0) // quit jumping
			break;
		else if (m[movx][movy] == '-' || m[movx][movy] == 'o' || m[movx][movy] == 'x') {
			cout << "ERROR! INVALID INPUT! TRY AGAIN!" << endl << endl;
		}
		else if (abs(movx - x) > 2 && (movy + y > 2 || movy + y < 1))
			cout << "ERROR! INVALID INPUT! TRY AGAIN!" << endl << endl;
		else {
			m[movx][movy] = 'x';
			m[x][y] = ' ';
			if ((movx - x) == 2 && (movy - y) == -2 && m[movx - 1][movy + 1] == 'o') {
				m[movx - 1][movy + 1] = ' ';
				jumping(m, x, y);
			}
			if ((movx - x) == -2 && (movy - y) == -2 && m[movx + 1][movy + 1] == 'o') {
				m[movx + 1][movy + 1] = ' ';
				jumping(m, x, y);
			}
			cout << m[1][4];
			error = false;
		}
	}
	error = true;
}
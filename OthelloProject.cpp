/*
 * Othello1.cpp
 *
 *  Created on: Jun 14, 2022
 *      Author: Bryce DiMedio and Conor McCloskey
 */


#include <iostream>
#include <string>
using namespace std;


class Player {
    public:

    //Variables
    string name;
    char piece;

    //Constructor1
    Player() {
        name = "Computer";
        piece = 'O';
    }

    //Constructor2
    Player(string name1, char piece1) {
    	name = name1;
    	piece = piece1;
    }
};

class Othello {
	public:

	//Variables
	char board[8][8];
	int board_size = 8;
	Player player1;
	Player player2;
	int numplayers;

	//Constructors
	Othello() {
		player1.name = "Computer 1";
		player1.piece = 'B';
		player2.name = "Computer 2";
		player2.piece = 'O';
		numplayers = 0;
	}
	Othello(string st1, char c) {
		player1.name = st1;
		player1.piece = c;
		numplayers = 1; //And player2 is "Computer" and 'O' by default (due to the Player constructor).
	}
	Othello(string st1, char c, string st2, char c2) {
		player1.name = st1;
		player1.piece = c;
		player2.name = st2;
		player2.piece = c2;
		numplayers = 2;
	}

	//Functions
	void makemat() {
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
				board[i][j] = '_';
			}
		}
		board[3][3] = player1.piece;
		board[3][4] = player2.piece;
		board[4][3] = player2.piece;
		board[4][4] = player1.piece;
	}

	void printmat() {
		//prints index values on top (x)
		for (int i=0; i<8; i++) {
			cout << '\t' << i;
		}
		cout << endl;
		for (int i=0; i<8; i++) {
			cout << i << '\t'; //prints the index values on the side (y)
			for (int j=0; j<8; j++) {
				cout << board[i][j] << '\t'; //Printing the board
		    }
		    cout << endl;
		}
		cout << endl;
	}

	void placepiece(string player, char color) {
		int x;
		int y;
		cout << "Enter the x coordinate on the board: " << endl;
		cin >> x;
		cout << "Enter the y coordinate on the board: " << endl;
		cin >> y;
		while ( (x<0 || x>7) || (y<0 || y>7) || (board[y][x] == player1.piece) || (board[y][x] == player2.piece) ) {
			cout << "Invalid coordinate" << endl;
			cout << "Enter another x coordinate on the board: ";
			cin >> x;
			cout << "Enter another y coordinate on the board: ";
			cin >> y;
		}
		board[y][x] = color; // y is the row, x is the column
		cout << endl; //Space for visual purposes
		countandflippieces(x,y,color,true); //Calling the flip count function
	}

	int countandflippieces(int x, int y, char color, bool flipping) {
		char opp_color;

		if (color == player1.piece) {
			opp_color = player2.piece;
		}
		if (color == player2.piece) {
			opp_color = player1.piece;
		}

		int left_flips = 0;
		int right_flips = 0;
		int down_flips = 0;
		int up_flips = 0;
		int upleft_flips = 0;
		int upright_flips = 0;
		int downleft_flips = 0;
		int downright_flips = 0;
		int total_flips = 0;

		//Down Scan
		for (int i=1; i<20; i++) { //Seeing how many O's follow the B placement in that direction, checking for an arbitrary length away.
			if (board[y+i][x] == opp_color) { //Flips if there's an O, for now, but checked later.
				down_flips += 1; //Counts how many to flip in that direction.
			}
			if (board[y+i][x] == color) { //Break the loop when we reach the opponent's piece.
				break;
			}
			if (y+i < 0 || y+i > 7 || board[y+i][x] != opp_color) { //If the iteration goes off the board or reaches a blank, meaning we don't reach an end piece, none are flipped.
				down_flips = 0;
				break;
			}
		}
		//Down Flip
		if (flipping == 1) { //Only do flipping if the boolean is True. If false, this function only counts the flips.
			for (int i=0; i<down_flips+1; i++) {
				board[y+i][x] = color; //Actually flipping the pieces
			}
		}


		//Up Scan
		for (int i=1; i<20; i++) {
			if (board[y-i][x] == opp_color) {
				up_flips += 1;
			}
			if (board[y-i][x] == color) {
				break;
			}
			if (y-i < 0 || y-i > 7  || board[y-i][x] != opp_color) {
				up_flips = 0;
				break;
			}
		}
		//Up Flip
		if (flipping == 1) {
			for (int i=0; i<up_flips+1; i++) {
				board[y-i][x] = color;
			}
		}

		//Right Scan
		for (int i=1; i<20; i++) {
			if (board[y][x+i] == opp_color) {
				right_flips += 1;
			}
			if (board[y][x+i] == color) {
				break;
			}
			if (x+i < 0 || x+i >7 || board[y][x+i] != opp_color) {
				right_flips = 0;
				break;
			}
		}
		//Right Flip
		if (flipping == 1) {
			for (int i=0; i<right_flips+1; i++) {
				board[y][x+i] = color;
			}
		}

		//Left Scan
		for (int i=1; i<20; i++) {
			if (board[y][x-i] == opp_color) {
				left_flips += 1;
			}
			if (board[y][x-i] == color) {
				break;
			}
			if (x-i < 0 || x-i > 7  || board[y][x-i] != opp_color) {
				left_flips = 0;
				break;
			}
		}
		//Left Flip
		if (flipping == 1) {
			for (int i=0; i<left_flips+1; i++) {
				board[y][x-i] = color;
			}
		}


		//Up Left Diagonal Scan
		for (int i=1; i<20; i++) {
			if (board[y-i][x-i] == opp_color) {
				upleft_flips += 1;
			}
			if (board[y-i][x-i] == color) {
				break;
			}
			if (y-i<0 || y-i>7 || x-i<0 || x-i>7) {
				upleft_flips = 0;
				break;
			}

		}
		//Up Left Diagonal Flip
		if (flipping == 1) {
			for (int i=0; i<upleft_flips+1; i++) {
				board[y-i][x-i] = color;
			}
		}


		//Up Right Diagonal Scan
		for (int i=1; i<20; i++) {
			if (board[y-i][x+i] == opp_color) {
				upright_flips += 1;
			}
			if (board[y-i][x+i] == color) {
				break;
			}
			if (y-i<0 || y-i>7 || x+i<0 || x+i>7 || board[y-i][x+i] != opp_color) {
				upright_flips = 0;
				break;
			}
		}
		//Up Right Diagonal Flip
		if (flipping == 1) {
			for (int i=0; i<upright_flips+1; i++) {
				board[y-i][x+i] = color;
			}
		}


		//Down Left Diagonal Scan
		for (int i=1; i<20; i++) {
			if (board[y+i][x-i] == opp_color) {
				downleft_flips += 1;
			}
			if (board[y+i][x-i] == color) {
				break;
			}
			if (y+i<0 || y+i>7 || x-i<0 || x-i>7 || board[y+i][x-i] != opp_color) {
				downleft_flips = 0;
				break;
			}
		}
		//Down Left Diagonal Flip
		if (flipping == 1) {
			for (int i=0; i<downleft_flips+1; i++) {
				board[y+i][x-i] = color;
			}
		}


		//Down Right Diagonal Scan
		for (int i=1; i<20; i++) {
			if (board[y+i][x+i] == opp_color) {
				downright_flips += 1;
			}
			if (board[y+i][x+i] == color) {
				break;
			}
			if (y+i<0 || y+i>7 || x+i<0 || x+i>7 || board[y+i][x+i] != opp_color) {
				downright_flips = 0;
				break;
			}
		}
		//Down Right Diagonal Flip
		if (flipping == 1) {
			for (int i=0; i<downright_flips+1; i++) {
				board[y+i][x+i] = color;
			}
		}


		//Displaying number of flips and printing the updated board.
		total_flips = down_flips + up_flips + left_flips + right_flips + upleft_flips + upright_flips +
				downleft_flips + downright_flips;
		if (flipping == 1) {
			if (total_flips == 0) {
				cout << "Player forfeits turn." << endl << endl;
				board[y][x] = '_'; //Un-places the piece since the player forfeits their turn, due to no flips.
			}
			else {
				//cout << "Pieces flipped: " << total_flips << endl << endl;
				printmat();
			}
		}
		return total_flips;
	}


	void ckwin() {
		//Iterate through the entire board and count the scores.
		int b_score = 0;
		int o_score = 0;
		for (int i=0; i<8; i++) {
			for (int j=0; j<8; j++) {
				if (board[i][j] == 'B') {
					b_score++;
				}
				if (board[i][j] == 'O') {
					o_score++;
				}
			}
		}
		if (b_score > o_score) {
			cout << player1.name << " won with: " << b_score << " versus " << o_score << endl;
		}
		if (o_score > b_score) {
			cout << "Computer won with: " << o_score << " versus " << b_score << endl;
		}
		if (b_score == o_score) {
			cout << "Tie: " << b_score << " versus " << o_score << endl;
		}
	}

	void compplacepiece(char comp_piece) {
		int max_flips = 0;
		int best_placements[64][2]; //Holds the list of coordinates that yield maximum flips.
		int row_n = 0; //Used as both the index for placement and an indicator of how long the list is.
		//Iterates through the board and finds the maximum number of pieces that can be flipped with a placement.
		for (int x=0; x<8; x++) {
			for (int y=0; y<8; y++) {
				if (countandflippieces(x, y, comp_piece, false) > max_flips && board[y][x]!='B' && board[y][x]!='O') {
					max_flips = countandflippieces(x, y, comp_piece, false);
				}
			}
		}
		//Now makes note of all the coordinates that yield maximum flips.
		for (int x=0; x<8; x++) {
			for (int y=0; y<8; y++) {
				if (countandflippieces(x, y, comp_piece, false) == max_flips && board[y][x]!='B' && board[y][x]!='O') {
					//Adds to the list of optimal placements.
					best_placements[row_n][0] = x;
					best_placements[row_n][1] = y;
					row_n++;
				}
			}
		}
		//Now the array contains the list of best coordinates to place the piece, which will be chosen randomly later.
		//Makes computer choose a random coordinate from the list;
		srand(time(NULL));
		int random_index = rand()%row_n;
		//Now it's actually getting placed, along with flipping other pieces.
		countandflippieces(best_placements[random_index][0], best_placements[random_index][1], comp_piece, true);
		cout << "x: " << best_placements[random_index][0] << endl;
		cout << "y: " << best_placements[random_index][1] << endl;
		cout << endl << endl;
	}


	void playGame() {
		makemat();
		printmat();
		int fullsqrs = 4;
		int random_n = rand()%2;
		if (random_n == 0) { // Player 1 goes first
			while (fullsqrs < 64) {
				cout << player1.name << ' ' << '(' << player1.piece << ") choose your square: ";
				cout << endl;
				placepiece(player1.name,player1.piece);
				fullsqrs++;
				if (player2.name == "Computer") { //If Player 2 is a computer
					cout << player2.name << ' ' << '(' << player2.piece << ") choose your square: ";
					cout << endl;
					compplacepiece(player2.piece);
					fullsqrs++;
				}
				else { //If Player 2 is another person
					cout << player2.name << ' ' << '(' << player1.piece << ") choose your square: ";
					cout << endl;
					placepiece(player2.name,player2.piece);
					fullsqrs++;
				}
			}
		}
		if (random_n == 1) { //Player 2 goes first
			while (fullsqrs < 64) {
				if (player2.name == "Computer") { //If Player 2 is a computer
					cout << player2.name << ' ' << '(' << player2.piece << ") choose your square: ";
					cout << endl;
					compplacepiece(player2.piece);
					fullsqrs++;
				}
				else { //If Player 2 is another person
					cout << player2.name << ' ' << '(' << player1.piece << ") choose your square: ";
					cout << endl;
					placepiece(player2.name,player2.piece);
					fullsqrs++;
				}
				cout << player1.name << ' ' << '(' << player1.piece << ") choose your square: ";
				cout << endl;
				placepiece(player1.name,player1.piece);
				fullsqrs++;
			}
		}
		ckwin();
	}

};


int main() {
	srand(time(NULL));
	Othello game("Player 1",'B',"Player 2",'O');
	Othello game2("Bryce",'B');
	Othello game3;
	game2.playGame();
    return 0;
}









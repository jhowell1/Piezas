#include "Piezas.h"
#include <iostream>
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
	// Fill board with Blank
	for(int i = 0; i < BOARD_ROWS; ++i)
	{
		std::vector<Piece> newRow(BOARD_COLS, Blank);
		board.push_back(newRow);
	}
	// Set turn to X
	turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
	// Set each to Blank
	for(int i = 0; i < BOARD_ROWS; ++i)
		for(int j = 0; j < BOARD_COLS; ++j)
			board.at(i).at(j) = Blank;
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
	if(column < 0 || column >= BOARD_COLS)
	{
		// Toggle Turn
		if(turn == X)
			turn = O;
		else
			turn = X;
		return Invalid;
	}
	
	int lastRow = BOARD_ROWS;
	int currentRow = BOARD_ROWS - 1;
	Piece current = pieceAt(currentRow, column);
	while(current == Blank) // Drop as low as possible
	{
		--lastRow;
		current = pieceAt(--currentRow, column);
	}
	
	if(lastRow >= BOARD_ROWS) // Column full, return Blank
	{
		// Toggle Turn
		if(turn == X)
			turn = O;
		else
			turn = X;
		return Blank;
	}
	else
	{
		// Place piece
		board.at(lastRow).at(column) = turn;
		// Toggle Turn
		if(turn == X)
			turn = O;
		else
			turn = X;
		// Return piece
		return pieceAt(lastRow, column);
	}
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
	if(row < 0 || row >= BOARD_ROWS || column < 0 || column >= BOARD_COLS)
		return Invalid;
    return board.at(row).at(column);
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{	
	int sumX = 0;
	int sumO = 0;
	
	// Check horizontal
	for(int i = 0; i < BOARD_ROWS; ++i)
	{
		Piece current = board.at(i).at(0);
		int currentSum = 1;
		for(int j = 1; j < BOARD_COLS; ++j)
		{
			if(board.at(i).at(j) == Blank) // Game not over
				return Invalid;
			
			if(board.at(i).at(j) != current) // end of adjacency
			{
				// Check if currentSum is new record
				if(current == X)
				{
					if(currentSum > sumX)
						sumX = currentSum;
					// set current to other Piece, reset currentSum
					current = O;
					currentSum = 1;
				}
				else
				{
					if(currentSum > sumO)
						sumO = currentSum;
					// set current to other Piece, reset currentSum
					current = X;
					currentSum = 1;
				}
			}
			else // adjacency continues
				++currentSum;
		}
		// Check if currentSum is new record, case when adjacency continues to end of line
		if(current == X)
		{
			if(currentSum > sumX)
				sumX = currentSum;
		}
		else
		{
			if(currentSum > sumO)
				sumO = currentSum;
		}
	}
	
	// Check Vertical
	for(int j = 0; j < BOARD_COLS; ++j)
	{
		Piece current = board.at(0).at(j);
		int currentSum = 1;
		for(int i = 1; i < BOARD_ROWS; ++i)
		{
			if(board.at(i).at(j) == Blank) // Game not over
				return Invalid;
			
			if(board.at(i).at(j) != current) // end of adjacency
			{
				// Check if currentSum is new record
				if(current == X)
				{
					if(currentSum > sumX)
						sumX = currentSum;
					// set current to other Piece, reset currentSum
					current = O;
					currentSum = 1;
				}
				else
				{
					if(currentSum > sumO)
						sumO = currentSum;
					// set current to other Piece, reset currentSum
					current = X;
					currentSum = 1;
				}
			}
			else // adjacency continues
				++currentSum;
		}
		// Check if currentSum is new record, case when adjacency continues to end of line
		if(current == X)
		{
			if(currentSum > sumX)
				sumX = currentSum;
		}
		else
		{
			if(currentSum > sumO)
				sumO = currentSum;
		}
	}
	
	if(sumX > sumO)
		return X;
	else if(sumX < sumO)
		return O;
	
	// game tied, return Blank
	return Blank;
}
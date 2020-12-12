/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

/* CONSTRUCTOR ----------------------------------------------------------------------*/

// Test that the constructor works in setting the board empty
TEST(PiezasTest, constructorFillWithBlank)
{
	Piezas obj;
	bool isEmpty = true;
	for(int i = 0; i < BOARD_ROWS; ++i)
	{
		for(int j = 0; j < BOARD_COLS; ++j)
			if(obj.pieceAt(i, j) != Blank)
				isEmpty = false;
	}
	ASSERT_TRUE(isEmpty);
}

/* DROP PIECE ------------------------------------------------------------------------*/

// Tests that test dropPiece() returns Invalid for Out of Bounds column
TEST(PiezasTest, dropPieceInvalidLow)
{
	Piezas obj;
	ASSERT_TRUE(obj.dropPiece(-1) == Invalid);
}

TEST(PiezasTest, dropPieceInvalidHigh)
{
	Piezas obj;
	ASSERT_TRUE(obj.dropPiece(BOARD_COLS) == Invalid);
}

// Test that dropPiece() properly places a Piece onto the board
TEST(PiezasTest, dropPieceSimple)
{
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_TRUE(obj.pieceAt(0,0) == X);
}

// Test that dropPiece() toggles turn when a Piece is placed
TEST(PiezasTest, dropPieceSimpleNextTurn)
{
	Piezas obj;
	Piece p1 = obj.dropPiece(0);
	Piece p2 = obj.dropPiece(0);
	ASSERT_TRUE(p1 != p2);
}

// Test that dropPiece() returns Blank if column is already full
TEST(PiezasTest, dropPieceBlank)
{
	Piezas obj;
	for(int i = 0; i < BOARD_ROWS; ++i)
		obj.dropPiece(0);
	ASSERT_TRUE(obj.dropPiece(0) == Blank);
}

// Test that dropPiece() toggles turn when a column is full
TEST(PiezasTest, dropPieceBlankNextTurn)
{
	Piezas obj;
	for(int i = 0; i < BOARD_ROWS; ++i)
		obj.dropPiece(0);
	Piece lastTurn = obj.pieceAt(BOARD_ROWS-1, 0);
	obj.dropPiece(1);
	ASSERT_TRUE(obj.pieceAt(0, 1) != lastTurn);
}

/* RESET ----------------------------------------------------------------------------*/

// Test that reset() sets all Pieces to blank, with simple test of only one Piece dropped
TEST(PiezasTest, resetSimple)
{
	Piezas obj;
	obj.dropPiece(0);
	obj.reset();
	bool isEmpty = true;
	for(int i = 0; i < BOARD_ROWS; ++i)
	{
		for(int j = 0; j < BOARD_COLS; ++j)
			if(obj.pieceAt(i, j) != Blank)
				isEmpty = false;
	}
	ASSERT_TRUE(isEmpty);
}

// Test that reset() sets all Pieces to blank, with moderate test of all Pieces dropped
TEST(PiezasTest, resetModerate)
{
	Piezas obj;
	for(int i = 0; i < BOARD_ROWS; ++i)
		for(int j = 0; j < BOARD_COLS; ++j)
			obj.dropPiece(j);
	obj.reset();
	bool isEmpty = true;
	for(int i = 0; i < BOARD_ROWS; ++i)
	{
		for(int j = 0; j < BOARD_COLS; ++j)
			if(obj.pieceAt(i, j) != Blank)
				isEmpty = false;
	}
	ASSERT_TRUE(isEmpty);
}

/* PIECE AT --------------------------------------------------------------------------*/

// Tests that test peiceAt() returns Invalid if location is out of bounds
TEST(PiezasTest, pieceAtXLow) // Row is less than 0
{
	Piezas obj;
	Piece outOfBoundsPiece = obj.pieceAt(-1,0);
	ASSERT_TRUE(outOfBoundsPiece == Invalid);
}

TEST(PiezasTest, pieceAtXHigh) // Row is greater than BOARD_ROWS
{
	Piezas obj;
	Piece outOfBoundsPiece = obj.pieceAt(3,0);
	ASSERT_TRUE(outOfBoundsPiece == Invalid);
}

TEST(PiezasTest, pieceAtYLow) // Column is less than 0
{
	Piezas obj;
	Piece outOfBoundsPiece = obj.pieceAt(0,-1);
	ASSERT_TRUE(outOfBoundsPiece == Invalid);
}

TEST(PiezasTest, pieceAtYHigh) // Column is greater than BOARD_COLS
{
	Piezas obj;
	Piece outOfBoundsPiece = obj.pieceAt(0,4);
	ASSERT_TRUE(outOfBoundsPiece == Invalid);
}

// Test that pieceAt() returns a Blank Piece from location not dropped in yet
TEST(PiezasTest, pieceAtIsBlank)
{
	Piezas obj;
	Piece blankPiece = obj.pieceAt(0,1);
	ASSERT_TRUE(blankPiece == Blank);
}

//Test that pieceAt() returns a Piece
TEST(PiezasTest, pieceAtSimple)
{
	Piezas obj;
	obj.dropPiece(0);
	Piece validPiece = obj.pieceAt(0,0);
	ASSERT_TRUE(validPiece == X || validPiece == O);
}

/* GAME STATE -------------------------------------------------------------------------*/

// Test that game is over and return winning Piece from Horizontal line
TEST(PiezasTest, gameStateWinnerHorizontal)
{
	Piezas obj;
	for(int i = 0; i < 2; ++i)
	{
		obj.dropPiece(0); //X
		obj.dropPiece(0); //O
		obj.dropPiece(1); //X
		obj.dropPiece(1); //O
		obj.dropPiece(2); //X
		obj.dropPiece(3); //O
	}
	obj.dropPiece(3);
	obj.dropPiece(2);
	
	ASSERT_TRUE(obj.gameState() == X);
}

// Test that game is over and return winning Piece from Vertical line
TEST(PiezasTest, gameStateWinnerVertical)
{
	Piezas obj;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
			obj.dropPiece(i);
	}
	obj.dropPiece(3); //O
	obj.dropPiece(4); //X, invalid
	obj.dropPiece(3); //O
	obj.dropPiece(4); //X, invalid
	obj.dropPiece(3); //O
	
	ASSERT_TRUE(obj.gameState() == O);
}

// Test that game is not over and returns Invalid
TEST(PiezasTest, gameStateInvalid)
{
	Piezas obj;
	ASSERT_TRUE(obj.gameState() == Invalid);
}

// Test that game is a tie and returns Blank
TEST(PiezasTest, gameStateTie)
{
	Piezas obj;
	for(int i = 0; i < BOARD_ROWS; ++i)
	{
		for(int j = 0; j < BOARD_COLS; ++j)
		{
			obj.dropPiece(j);
		}
	}
	ASSERT_TRUE(obj.gameState() == Blank);
}

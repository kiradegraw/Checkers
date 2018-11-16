#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

// check if a certain position on the board is occupied by a red or black piece
string checkPos(int x, int y, int red[][6], int black[][6])
{
    string str = "";
    if(red[x][y] != 0)
        if(red[x][y] == 1)
            str = "r1";
        else
            str = "r2";
    else if(black[x][y] != 0)
        if(black[x][y] == 1)
            str = "b1";
        else
            str = "b2";
    else
        str = "  ";

    return str;
}

//print board according to red and black arrays indicating positions on the board
void printBoard(int red[][6], int black[][6])
{
    cout << "\n";
    cout << "   ____ ____ ____ ____ ____ ____ " << endl;
    cout << "  |    |    |    |    |    |    |" << endl;
    cout << "5 | " << checkPos(0, 5, red, black) << " |    | " << checkPos(2, 5, red, black) << " |    | " << checkPos(4, 5, red, black) << " |    |" << endl;
    cout << "  |____|____|____|____|____|____|" << endl;
    cout << "  |    |    |    |    |    |    |" << endl;
    cout << "4 |    | " << checkPos(1, 4, red, black) << " |    | " << checkPos(3, 4, red, black) << " |    | " << checkPos(5, 4, red, black) << " |" << endl;
    cout << "  |____|____|____|____|____|____|" << endl;
    cout << "  |    |    |    |    |    |    |" << endl;
    cout << "3 | " << checkPos(0, 3, red, black) << " |    | " << checkPos(2, 3, red, black) << " |    | " << checkPos(4, 3, red, black) << " |    |" << endl;
    cout << "  |____|____|____|____|____|____|" << endl;
    cout << "  |    |    |    |    |    |    |" << endl;
    cout << "2 |    | " << checkPos(1, 2, red, black) << " |    | " << checkPos(3, 2, red, black) << " |    | " << checkPos(5, 2, red, black) << " |" << endl;
    cout << "  |____|____|____|____|____|____|" << endl;
    cout << "  |    |    |    |    |    |    |" << endl;
    cout << "1 | " << checkPos(0, 1, red, black) << " |    | " << checkPos(2, 1, red, black) << " |    | " << checkPos(4, 1, red, black) << " |    |" << endl;
    cout << "  |____|____|____|____|____|____|" << endl;
    cout << "  |    |    |    |    |    |    |" << endl;
    cout << "0 |    | " << checkPos(1, 0, red, black) << " |    | " << checkPos(3, 0, red, black) << " |    | " << checkPos(5, 0, red, black) << " |" << endl;
    cout << "  |____|____|____|____|____|____|" << endl;
    cout << "    0    1    2    3    4    5   \n" << endl;
}

void initializePieces(int red[][6], int black[][6])
{
    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 6; j++)
        {
            red[i][j] = 0;
            black[i][j] = 0;
        }
    red[0][1] = 1;
    red[1][0] = 2;
    red[2][1] = 1;
    red[3][0] = 2;
    red[4][1] = 1;
    red[5][0] = 2;

    black[0][5] = 2;
    black[1][4] = 1;
    black[2][5] = 2;
    black[3][4] = 1;
    black[4][5] = 2;
    black[5][4] = 1;

}

bool isValidPiece(int x, int y, int red[][6], int black[][6], string playerColor)
{
    // if player color is the same as color from checkPos
    string pieceColor = checkPos(x, y, red, black).substr(0,1);
    if (pieceColor == playerColor)
    {
        return true;
    }
    cout << "Please enter a valid piece." << endl;
    return false;
}

void determineJumpCoordinates(int startX, int startY, int endX, int endY, int& jumpX, int& jumpY)
{
    // gets the value in between the old and new coordinates
    if (startX > endX)
        {
            jumpX = startX - 1;
        }
    else if (endX > startX)
        {
            jumpX = endX - 1;
        }

    if (startY > endY)
        {
            jumpY = startY - 1;
        }
    else if (endY > startY)
        {
            jumpY = endY - 1;
        }
}

bool isMoveValid(int startX, int startY, int endX, int endY, int& jumpX, int& jumpY,int red[][6], int black[][6], string playerColor)
{
    string startPiece = checkPos(startX, startY, red, black);
    string endPiece = checkPos(endX, endY, red, black);
    // player has passed their turn
    if (endX == -1 && endY == -1)
    {
        return true;
    }
    // player wants to move one space diagonally and the space is empty
    else if ((abs(startX - endX) == 1) && (abs(startY - endY) == 1) && (endPiece.substr(0, 1) == " "))
    {
        return true;
    }
    // player wants to move 2 spaces and the space they want is empty
    else if ((abs(startX - endX) == 2) && (abs(startY - endY) == 2) && (endPiece.substr(0, 1) == " "))
    {
        // get coordinates in the middle
        determineJumpCoordinates(startX, startY, endX, endY, jumpX, jumpY);
        if (playerColor == "r")
        {
            // if jumped piece is not the opposite color
            if (checkPos(jumpX, jumpY, red, black).substr(0,1) != "b")
            {
                jumpX = 999;
                jumpY = 999;
                cout << "Jumped piece must be the opposite color." << endl;
                return false;
            }
        }
        else if (playerColor == "b")
        {
            // if jumped piece is not the opposite color
            if (checkPos(jumpX, jumpY, red, black).substr(0,1) != "r")
            {
                jumpX = 999;
                jumpY = 999;
                cout << "Jumped piece must be the opposite color." << endl;
                return false;
            }
        }
        // if jumped piece and current piece have the same number
        if (startPiece.substr(1,1) == checkPos(jumpX, jumpY, red, black).substr(1,1))
            return true;
        else
        {
            {
                cout << "The jumped piece must be the opposite color, but the same number." << endl;
                jumpX = 999;
                jumpY = 999;
                return false;
            }
        }
    }
    else
        cout << "Please select a valid move." << endl;
        return false;
}

void movePiece(int startX, int startY, int endX, int endY, int red[][6], int black[][6], string playerColor)
{
    // sets starting array pos to 0, new pos to its correct number from checkPos
    int pieceNumber = atoi((checkPos(startX, startY, red, black).substr(1, 1)).c_str());
    if (playerColor == "r")
    {
        red[startX][startY] = 0;
        red[endX][endY] = pieceNumber;
    }
    else if (playerColor == "b")
    {
        black[startX][startY] = 0;
        black[endX][endY] = pieceNumber;
    }
}

// sets the jumped piece array to a 0 value and adds a point
void addPoint(int jumpX, int jumpY, int red[][6], int black[][6], int &redPoints, int &blackPoints, string playerColor)
{
    if (playerColor == "r")
    {
        black[jumpX][jumpY] = 0;
        ++ redPoints;
    }
    else if (playerColor == "b")
    {
        red[jumpX][jumpY] = 0;
        ++ blackPoints;
    }
}

void printPoints(int redPoints, int blackPoints)
{
    cout << "Red Points: " << redPoints << endl;
    cout << "Black Points: " << blackPoints << endl;
}

void playGame(int red[][6], int black[][6], int &redPoints, int &blackPoints)
{
    //declare variables, set default player to red
    int startX, startY;
    int endX, endY;
    int jumpX, jumpY;
    string playerColor = "r";
    do
    {
        //reset all values
        startX = 999;
        startY = 999;
        endX = 999;
        endY = 999;
        jumpX = 999;
        jumpY = 999;
    do
    {
        if (playerColor == "r")
        {
            cout << "Red Player, select the piece you would like to move (x y): ";
        }
        else if (playerColor == "b")
        {
            cout << "Black Player, select the piece you would like to move (x y): ";
        }
        cin >> startX >> startY;
    }
    while (!isValidPiece(startX, startY, red, black, playerColor));

    do
    {
        if (playerColor == "r")
        {
            cout << "Red Player, select the place to move your piece (x y)(-1 -1 to pass): ";
        }
        else if (playerColor == "b")
        {
            cout << "Black Player, select the place to move your piece (x y)(-1 -1 to pass): ";
        }
        cin >> endX >> endY;
    }
    while (!isMoveValid(startX, startY, endX, endY, jumpX, jumpY, red, black, playerColor));

    // player skipped their turn
    if (endX == -1 && endY == -1)
    {
        if (playerColor == "r")
        {
            cout << "Red Player, you have passed your turn." << endl;
        }
        else if (playerColor == "b")
        {
            cout << "Black Player, you have passed your turn." << endl;
        }
    }
    else
    {
        movePiece(startX, startY, endX, endY, red, black, playerColor);
        if (jumpX != 999)
        { // if a piece was actually jumped
            addPoint(jumpX, jumpY, red, black, redPoints, blackPoints, playerColor);
        }
    }
    // display board
    printBoard(red, black);
    // display points
    printPoints(redPoints, blackPoints);
    // change current player before restarting the do while loop
    if (playerColor == "r")
    {
        playerColor = "b";
    }
    else if (playerColor == "b")
    {
        playerColor = "r";
    }
    } // stop once a player has reached 3 points
    while ((redPoints < 3) && (blackPoints < 3));

    // tell the winner, end the game
    if (blackPoints == 3)
    {
        cout << "Black Player, you are the winner!!" << endl;
    }
    else if (redPoints == 3)
    {
       cout << "Red Player, you are the winner!!" << endl;
    }
}

int main()
{
    int red[6][6];
    int black[6][6];
    int redPoints = 0;
    int blackPoints = 0;
    initializePieces(red, black);
    printBoard(red, black);
    playGame(red, black, redPoints, blackPoints);
    return 0;
}

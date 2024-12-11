#ifndef FUNCTIONS
#define FUNCTIONS

#define DASHES_IN_FRAME 8
#define NUMBER_OF_TOTAL_SPACES 6
#define SPACES_BEFORE_NUM 5
#define NUMBER_OF_OPTIONS 6
#define MAX_CHARS 81
#define FIRST_NUMBER 2
#define FIRST_NUMBER_PERCENT 70
#define SECOND_NUMBER 4
#define NEW_GAME_DASHES 11

void printBoard(const int* board, int rows, int cols);

void printBoardFrame(int cols);

void printChar(int amount, char ch);

void printMenu();

void doNothing();

char handleInput();

void playGame(int* board, int size, int scoreToWin);

int canMove();

int generateNumber();

void addNumberToRandomCell(int* board,  int boardSize, int* freeCells, int* score);

int generateCellIndex(const int* board,  int boardSize, int freeCells);

void printStartGame(int scoreToWin);

void startGame(int* isGameStarted, int* board, int size, int* freeCells, int* score);

void resetGame(int* board, int size);

void sumTwoNumbers(int* mat, int index1, int index2, int* freeCells, int* score);

void sumAllTwoSameNumbersUp(int* mat, int size, int* freeCells, int* score);

void sumAllTwoSameNumbersDown(int* mat, int size, int* freeCells, int* score);

void sumAllTwoSameNumbersRight(int* mat, int size, int* freeCells, int* score);

void sumAllTwoSameNumbersLeft(int* mat, int size, int* freeCells, int* score);

void moveAllNumbersLeft(int* mat, int size);   

void moveAllNumbersRight(int* mat, int size); 

void moveAllNumbersUp(int* mat, int size);     

void moveAllNumbersDown(int* mat, int size);

void moveNumbers(int* mat, int size, int direction);

void moveDown(int* board, int size, int* freeCells, int* score);

void moveUp(int* board, int size, int* freeCells, int* score);

void moveRight(int* board, int size, int* freeCells, int* score);

void moveLeft(int* board, int size, int* freeCells, int* score);

int checkCanMoveRight(int* mat, int size);

int checkCanMoveLeft(int* mat, int size);

int checkCanMoveUp(int* mat, int size);

int checkCanMoveDown(int* mat, int size);

#endif
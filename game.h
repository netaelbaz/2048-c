#ifndef GAME
#define GAME

#define FIRST_NUMBER 2
#define FIRST_NUMBER_PERCENT 70
#define SECOND_NUMBER 4

char handleInput();

void playGame(int* board, int size, int scoreToWin);

int canMove(int* board, int size);

int generateNumber();

void addNumberToRandomCell(int* board, int boardSize, int* freeCells);

int generateCellIndex(const int* board, int boardSize, int freeCells);

void startGame(int* isGameStarted, int* board, int size, int* freeCells);

void resetGame(int* board, int size);

void sumTwoNumbers(int* board, int index1, int index2, int* freeCells, int* score);

void sumAllTwoSameNumbersUp(int* board, int size, int* freeCells, int* score);

void sumAllTwoSameNumbersDown(int* board, int size, int* freeCells, int* score);

void sumAllTwoSameNumbersRight(int* board, int size, int* freeCells, int* score);

void sumAllTwoSameNumbersLeft(int* board, int size, int* freeCells, int* score);

void moveNumbersrightLeft(int* board, int size, int start, int end, int step);

void moveNumbersUpDown(int* board, int size, int start, int end, int step);

int checkCanMoveRight(int* mat, int size);

int checkCanMoveLeft(int* mat, int size);

int checkCanMoveUp(int* mat, int size);

int checkCanMoveDown(int* mat, int size);

// int checkCanMoveRightLeft(int* board, int size, int start, int end, int step);

// int checkCanMoveDownUp(int* board, int size, int start, int end, int step);

void moveDown(int* board, int size, int* freeCells, int* score);

void moveUp(int* board, int size, int* freeCells, int* score);

void moveRight(int* board, int size, int* freeCells, int* score);

void moveLeft(int* board, int size, int* freeCells, int* score);

#endif
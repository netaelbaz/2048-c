#ifndef GUI
#define GUI

#define DASHES_IN_FRAME 8
#define NUMBER_OF_TOTAL_SPACES 6
#define SPACES_BEFORE_NUM 5
#define NUMBER_OF_OPTIONS 6
#define MAX_CHARS 81
#define NEW_GAME_DASHES 11

void printBoard(const int* board, int rows, int cols);

void printBoardFrame(int cols);

void printChar(int amount, char ch);

void printMenu();

void printStartGame(int scoreToWin);

#endif

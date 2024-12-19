
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "game.h"
#include "gui.h"

char handleInput() {
	char input;
	do {
		scanf("%c", &input);
	} while (isspace(input));
	return tolower(input);
}

int canMove(int* board, int size) {
	return checkCanMoveDown(board, size) || checkCanMoveRight(board, size) || checkCanMoveUp(board, size) || checkCanMoveLeft(board, size);
}

void playGame(int* board, int size, int scoreToWin) {
	printBoard((int*)board, size, size);
	int currentScore = 0;
	int bestScore = 0;
	int freeCells = size * size;
	int isGameStarted = 0;
	char userInput = '\0';
	while (userInput != 'e' && currentScore < scoreToWin && (freeCells != 0 || canMove(board, size))) {
		printMenu();
		userInput = handleInput();
		switch (userInput) {
		case 'n':
			printStartGame(scoreToWin);
			currentScore = 0;
			startGame(&isGameStarted, board, size, &freeCells);
			break;
		case 'r':
			if (isGameStarted == 0)
				printf("Need to start game first\n");
			else
				moveRight(board, size, &freeCells, &currentScore);
			break;
		case 'l':
			if (isGameStarted == 0)
				printf("Need to start game first\n");
			else
				moveLeft(board, size, &freeCells, &currentScore);
			break;
		case 'u':
			if (isGameStarted == 0)
				printf("Need to start game first\n");
			else
				moveUp(board, size, &freeCells, &currentScore);
			break;
		case 'd':
			if (isGameStarted == 0)
				printf("Need to start game first\n");
			else
				moveDown(board, size, &freeCells, &currentScore);
			break;
		case 'e':
			printf("Ending previous game - your score %d best score %d\n\nBye bye\n", currentScore, bestScore);
			break;
		default:
			printf("Wrong Option, re-enter\n");
		}
		if (currentScore > bestScore)
			bestScore = currentScore;
		if (userInput != 'e') {
			printf("Score %d Best %d\n", currentScore, bestScore);
			printBoard(board, size, size);
		}
	}
	resetGame(board, size);
	if (currentScore >= scoreToWin) {
		printf("You won %d! - Ending Game\n", scoreToWin);
	}
	else if (!canMove(board, size)) {
		printf("Game over your score is %d\n", currentScore);
	}
}

int generateNumber() {
	int num = rand() % 100;
	if (num < FIRST_NUMBER_PERCENT) {
		return FIRST_NUMBER;
	}
	return SECOND_NUMBER;
}

int generateCellIndex(const int* board, int boardSize, int freeCells) {
	int randomIndex = rand() % freeCells;
	int currentIndex = 0;
	for (int i = 0; i < boardSize * boardSize; i++) {
		if (*board == 0) {
			if (currentIndex == randomIndex) {
				return i;
			}
			currentIndex++;
		}
		board++;
	}
	return -1;
}

void addNumberToRandomCell(int* board, int boardSize, int* freeCells) {
	int generatedIndex = generateCellIndex(board, boardSize, *freeCells);
	int num = generateNumber();
	*(board + generatedIndex) = num;
	(*freeCells)--;
}

void startGame(int* isGameStarted, int* board, int size, int* freeCells) {
	if (*isGameStarted == 1)
		resetGame(board, size);
	*freeCells = size * size;
	*isGameStarted = 1;
	for (int i = 0; i < 2; i++)
		addNumberToRandomCell(board, size, freeCells);
}

void resetGame(int* board, int size) {
	for (int i = 0; i < size * size; i++) {
		if (*board != 0) {
			*board = 0;
		}
		board++;
	}
}


void sumTwoNumbers(int* board, int index1, int index2, int* freeCells, int* score)
{
	*(board + index1) += *(board + index2);
	*(board + index2) = 0;
	int sum = *(board + index1);
	*score += sum;
	(*freeCells)++;
}

void sumAllTwoSameNumbersUp(int* board, int size, int* freeCells, int* score)
{
	for (int col = 0; col < size; col++) {
		for (int row = 0; row < size - 1; row++) {
			int currentIndex = size * row + col;
			int nextIndex = size * (row + 1) + col;
			if (*(board + currentIndex) == *(board + nextIndex) && *(board + currentIndex) != 0) {
				sumTwoNumbers((int*)board, currentIndex, nextIndex, freeCells, score);
				break;
			}
		}
	}
}

void sumAllTwoSameNumbersDown(int* board, int size, int* freeCells, int* score)
{
	for (int col = size - 1; col >= 0; col--) {
		for (int row = size - 1; row > 0; row--) {
			int currentIndex = size * row + col;
			int prevIndex = size * (row - 1) + col;
			if (*(board + currentIndex) == *(board + prevIndex) && *(board + currentIndex) != 0) {
				sumTwoNumbers(board, currentIndex, prevIndex, freeCells, score);
				break;
			}
		}
	}
}

void sumAllTwoSameNumbersLeft(int* board, int size, int* freeCells, int* score)
{
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size - 1; col++) {
			int currentIndex = size * row + col;
			int nextIndex = (col + 1) + size * row;
			if (*(board + currentIndex) == *(board + nextIndex) && *(board + currentIndex) != 0) {
				sumTwoNumbers(board, currentIndex, nextIndex, freeCells, score);
				break;
			}
		}
	}
}

void sumAllTwoSameNumbersRight(int* board, int size, int* freeCells, int* score)
{
	for (int row = size - 1; row >= 0; row--) {
		for (int col = size - 1; col > 0; col--) {
			int currentIndex = size * row + col;
			int prevIndex = (col - 1) + size * row;
			if (*(board + currentIndex) == *(board + prevIndex) && *(board + currentIndex) != 0) {
				sumTwoNumbers(board, currentIndex, prevIndex, freeCells, score);
				break;
			}
		}
	}
}


int checkCanMoveRight(int* mat, int size) {
	int isNumber = 1;
	for( int row=0 ; row < size ; row ++) {
		for( int col=size-1 ; col >= 0 ; col--) {
			int currentIndex = size*row + col;
			if (*(mat+currentIndex) != 0 && isNumber == 0) {
				return 1;
			}
			else if (*(mat+currentIndex) == 0)
				isNumber = 0;
			else if (col > 0 && (*(mat+currentIndex) == *(mat+currentIndex-1)))
				return 1;
		}
		isNumber = 1;
	}
	return 0;
}

int checkCanMoveLeft(int* mat, int size) {
	int isNumber = 1;
	for( int row=0 ; row < size ; row++) {
		for( int col=0 ; col < size ; col++) {
			int currentIndex = size*row +col;
			if (*(mat+currentIndex) != 0 && isNumber == 0) {
				return 1;
			}
			else if (*(mat+currentIndex) == 0)
				isNumber = 0;
			else if (col < size-1 && (*(mat+currentIndex) == *(mat+currentIndex+1)))
				return 1;
		}
		isNumber = 1;
	}
	return 0;
}


int checkCanMoveUp(int* mat, int size) {
	int isNumber = 1;
	for( int col=0 ; col < size ; col++) {
		for( int row=0 ; row < size ; row++) {
			int currentIndex = size*row+col;
			if (*(mat+currentIndex) != 0 && isNumber == 0) {
				return 1;
			}
			else if (*(mat+currentIndex) == 0)
				isNumber = 0;
			else if (row < size-1 && (*(mat+currentIndex) == *(mat+size*(row+1)+col)))
				return 1;
		}
		isNumber = 1;
	}
	return 0;
}


int checkCanMoveDown(int* mat, int size) {
	int isNumber = 1;
	for( int col=size-1 ; col >= 0 ; col--) {
		for( int row=size-1 ; row >= 0 ; row--) {
			int currentIndex = size*row+col;
			if (*(mat+currentIndex) != 0 && isNumber == 0) {
				return 1;
			}
			else if (*(mat+currentIndex) == 0)
				isNumber = 0;
			else if (row > 0 && (*(mat+currentIndex) == *(mat+size*(row-1)+col)))
				return 1;
		}
		isNumber = 1;
	}
	return 0;
}

// int checkCanMoveRightLeft(int* board, int size, int start, int end, int step)
// {
// 	int isNumber = 1;
// 	for (int row = start; row != end; row += step) {
// 		for (int col = start; col != end; col += step) {
// 			int currentIndex = size * row + col;
// 			if (*(board + currentIndex) != 0 && isNumber == 0) {
// 				return 1;
// 			}
// 			else if (*(board + currentIndex) == 0)
// 				isNumber = 0;
// 			else if (col != end && (*(board + currentIndex) == *(board + currentIndex + step)))
// 				return 1;
// 		}
// 		isNumber = 1;
// 	}
// 	return 0;
// }

// int checkCanMoveDownUp(int* board, int size, int start, int end, int step)
// {
// 	int isNumber = 1;

// 	for (int col = start; col != end; col += step) {
// 		for (int row = start; row != end; row += step) {
// 			int currentIndex = size * row + col;
// 			if (*(board + currentIndex) != 0 && isNumber == 0) {
// 				return 1;
// 			}
// 			else if (*(board + currentIndex) == 0)
// 				isNumber = 0;
// 			else if (row != end && (*(board + currentIndex) == *(board + size * (row + step) + col)))
// 				return 1;
// 		}
// 		isNumber = 1;
// 	}
// 	return 0;
// }

void moveNumbersrightLeft(int* board, int size, int start, int end, int step)
{
	int countZero = 0;

	for (int row = start; row != end; row += step) {
		for (int col = start; col != end; col += step) {
			if (*(board + size * row + col) == 0)
				countZero++;
			else if (countZero > 0) {
				*(board + (size * row + (col - step * countZero))) = *(board + size * row + col);
				*(board + size * row + col) = 0;
			}
		}
		countZero = 0;
	}
}

void moveNumbersUpDown(int* board, int size, int start, int end, int step)
{
	int countZero = 0;
	
	for (int col = start; col != end; col += step) {
		for (int row = start; row != end; row += step) {
			if (*(board + size * row + col) == 0)
				countZero++;
			else if (countZero > 0) {
				*(board + (size * (row - (step * countZero))) + col) = *(board + size * row + col);
				*(board + size * row + col) = 0;
			}
		}
		countZero = 0;
	}
}

void moveLeft(int* board, int size, int* freeCells, int* score)
{
	if (checkCanMoveLeft(board, size) == 0)
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveNumbersrightLeft(board, size, 0, size, 1);
		sumAllTwoSameNumbersLeft(board, size, freeCells, score);
		moveNumbersrightLeft(board, size, 0, size, 1);
		addNumberToRandomCell(board, size, freeCells);
	}
}

void moveRight(int* board, int size, int* freeCells, int* score)
{
	if (checkCanMoveRight(board, size) == 0)
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveNumbersrightLeft(board, size, size - 1, -1, -1);
		sumAllTwoSameNumbersRight(board, size, freeCells, score);
		moveNumbersrightLeft(board, size, size - 1, -1, -1);
		addNumberToRandomCell(board, size, freeCells);
	}
}

void moveUp(int* board, int size, int* freeCells, int* score)
{
	if (checkCanMoveUp(board, size) == 0)
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveNumbersUpDown(board, size, 0, size, 1);
		sumAllTwoSameNumbersUp(board, size, freeCells, score);
		moveNumbersUpDown(board, size, 0, size, 1);
		addNumberToRandomCell(board, size, freeCells);
	}
}

void moveDown(int* board, int size, int* freeCells, int* score)
{
	if (checkCanMoveDown(board, size) == 0)
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveNumbersUpDown(board, size, size - 1, -1, -1);
		sumAllTwoSameNumbersDown(board, size, freeCells, score);
		moveNumbersUpDown(board, size, size - 1, -1, -1);
		addNumberToRandomCell(board, size, freeCells);
	}
}

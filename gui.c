
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "gui.h"

void printBoard(const int* board, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		printBoardFrame(cols);
		for (int j = 0; j < cols; j++) {
			printf("|");
			if (*board == 0) {
				printChar(NUMBER_OF_TOTAL_SPACES, ' ');
			}
			else {
				printf("%*d ", SPACES_BEFORE_NUM, *board);
			}
			board++;
		}
		printf("|\n");
	}
	printBoardFrame(cols);
}

void printBoardFrame(int cols) {
	int numberToPrint = DASHES_IN_FRAME * cols - (cols - 1);
	printChar(numberToPrint, '-');
	printf("\n");
}

void printChar(int amount, char ch) {
	for (int i = 0; i < amount; i++) {
		printf("%c", ch);
	}
}

void printMenu() {
	char* options[MAX_CHARS] = {
		"N/n - New Game",
		"R/r - Move Right",
		"L/l - Move left",
		"U/u - Move Up",
		"D/d - Move Down",
		"E/e - Exit"
	};
	char** ptr_options = options;
	printf("Please choose one of the following options:\n");
	for (int i = 0; i < NUMBER_OF_OPTIONS; i++) {
		printf("%s\n", *ptr_options);
		ptr_options++;
	}
}

void printStartGame(int scoreToWin) {
	printf("-----------  STARTING A GAME  ----------- \n");
	printf("%*s%s %d%*s\n", NEW_GAME_DASHES, " ", "Score for a win", scoreToWin, NEW_GAME_DASHES, " ");
	printf("-----------------------------------------\n\n");
}

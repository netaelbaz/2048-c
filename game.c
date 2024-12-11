#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 4

#include "game.h"

void printBoard(const int* board, int rows, int cols) {
    for (int i=0; i<rows; i++) {
        printBoardFrame(cols);
        for (int j=0; j<cols; j++) {
            printf("|");
            if (*board == 0) {
                printChar(NUMBER_OF_TOTAL_SPACES, ' ');
            }
            else {
                printf("%*d ",SPACES_BEFORE_NUM, *board);
            }
            board++;
        }
        printf("|\n");
    }
    printBoardFrame(cols);
}

void printBoardFrame(int cols) {
    int numberToPrint = DASHES_IN_FRAME * cols - (cols -1);
    printChar(numberToPrint, '-');
    printf("\n");
}

void printChar(int amount, char ch) {
    for (int i=0; i<amount; i++) {
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
    for (int i=0; i<NUMBER_OF_OPTIONS; i++) {
        printf("%s\n", *ptr_options);
        ptr_options++;
    }
}

void doNothing() {
    printf("you chose this\n");
}


char handleInput() {
    char input;
    do {
        scanf("%c", &input);
    } while (isspace(input));
    return tolower(input);
}

int canMove(int* board, int size) {
    return checkCanMoveDown(board, size) || checkCanMoveLeft(board, size) || checkCanMoveRight(board, size) || checkCanMoveUp(board, size);
}

void playGame(int* board, int size, int scoreToWin) {
    printBoard((int*) board, size, size);
    int currentScore = 0;
    int bestScore = 0;
    int freeCells = size*size;
    int isGameStarted = 0;
    char userInput;
    while (userInput !='e' && currentScore < scoreToWin && (freeCells != 0 || canMove(board, size))) {
        printMenu();
        userInput = handleInput();
        switch (userInput) {
            case 'n':
                printStartGame(scoreToWin);
                startGame(&isGameStarted, board, size, &freeCells, &currentScore);
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
                isGameStarted = 0;
                resetGame(board, size);
                printf("Ending previous game - your score %d best score %d\n\nBye bye\n", currentScore, bestScore);
                break;
            default:
                printf("Wrong Option, re-enter\n");
        }
		if (currentScore > bestScore)
			bestScore = currentScore;
        if (userInput!= 'e') {
            printf("Score %d Best %d\n", currentScore, bestScore);
            printBoard(board, size, size);
        }
    }
	if (currentScore == scoreToWin) {
		printf("You won %d! - Ending Game\n", scoreToWin);
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
    for (int i=0; i<boardSize*boardSize; i++) {
        if (*board == 0) {
            if (currentIndex == randomIndex) {
                return i;
            }
            currentIndex ++;
        }
        board++;
    }
    return -1;
}

void addNumberToRandomCell(int* board, int boardSize, int* freeCells, int* score) {
    int generatedIndex = generateCellIndex(board, boardSize, *freeCells);
    int num = generateNumber();
	if (num > *score) 
		*score = num;
    *(board+generatedIndex) = num;
    (*freeCells)--;
}


void printStartGame(int scoreToWin) {
    int numberOfSpaces = 2;
    printChar(NEW_GAME_DASHES,  '-');
    printf("%*s%s%*s", numberOfSpaces, " ", "STARTING A GAME", numberOfSpaces, " ");
    printChar(NEW_GAME_DASHES, '-');
    printf("\n");
    printf("%*s%s %d%*s\n",11," ", "Score for a win", scoreToWin ,11, " ");
    printChar(41, '-');
    printf("\n\n");
}

void startGame(int* isGameStarted, int* board, int size, int* freeCells, int* score) {
    if (*isGameStarted == 1)
        resetGame(board, size);
		*freeCells = size*size;
    *isGameStarted = 1;
    for (int i=0; i<2; i++) 
        addNumberToRandomCell(board, size, freeCells, score);
}

void resetGame(int* board, int size) {
    for (int i=0; i<size*size; i++) {
        if (*board != 0) {
            *board = 0;
        }
        board++;
    }
}


void sumTwoNumbers(int* mat, int index1, int index2, int* freeCells, int* score)
{
	*(mat+index1) += *(mat+index2);
	*(mat+index2) = 0;
	int sum = *(mat+index1);
	if (*score < sum)
		*score = sum;
	(*freeCells)++;
}	

void sumAllTwoSameNumbersUp(int* mat, int size, int* freeCells, int* score)
{	
	for( int i=0 ; i < size ; i++){
		for( int j=0 ; j < size-1 ; j++){	
			if( *(mat+size*j+i) == *(mat+size*(j+1)+i) && *(mat+size*j+i) != 0 ) {
				sumTwoNumbers((int*) mat, size*j+i, size*(j+1)+i, freeCells, score);
				break;
			}
		}
	}
}

void sumAllTwoSameNumbersDown(int* mat, int size, int* freeCells, int* score)
{	
	for( int i=size-1 ; i >= 0 ; i--){
		for( int j=size-1 ; j > 0 ; j--){
			if( *(mat+size*j+i) == *(mat+size*(j-1)+i) && *(mat+size*j+i) != 0 ){
				sumTwoNumbers(mat, size*j+i, size*(j-1)+i, freeCells, score);
				break;
			}
		}
	}
}

void sumAllTwoSameNumbersLeft(int* mat, int size, int* freeCells, int* score)
{
	for( int i=0 ; i < size ; i++){
		for( int j=0 ; j < size-1 ; j++){	
			if( *(mat+size*i+j) == *(mat+(j+1)+size*i) && *(mat+size*i+j) != 0 ){
				sumTwoNumbers(mat, size*i+j, (j+1)+size*i, freeCells, score);
				break;
			}
		}
	}
}

void sumAllTwoSameNumbersRight(int* mat, int size, int* freeCells, int* score)
{for( int i=size-1 ; i >= 0 ; i--){
		for( int j=size-1 ; j > 0 ; j--){
			if( *(mat+size*i+j) == *(mat+(j-1)+size*i) && *(mat+size*i+j) != 0 ){
				sumTwoNumbers(mat, size*i+j, (j-1)+size*i, freeCells, score);
				break;
			}
		}
	}
}

void moveAllNumbersLeft(int* mat, int size)
{	
	int countZero = 0;
	for( int i=0 ; i < size ; i++){
		for( int j=0 ; j < size ; j++)
		{
			if(*(mat+j+size*i) == 0) {
				countZero++;
			}
			else if (countZero > 0)
			{
				*(mat+size*i+j-countZero) = *(mat+j+size*i);
				*(mat+j+size*i) = 0;
			}
		}
		countZero = 0;
	}
}

void moveAllNumbersRight(int* mat, int size)
{
	int countZero = 0;
	for( int i=size-1 ; i >= 0 ; i--){
		for( int j=size-1 ; j >= 0 ; j--){
			if(*(mat+j+size*i) == 0){
				countZero++;
			}
			else if (countZero > 0){
				*(mat+j+size*i+countZero) = *(mat+j+size*i);
				*(mat+j+size*i) = 0;
			}
		}
		countZero = 0;
	}
}

void moveAllNumbersUp(int* mat, int size)
{
	int countZero = 0;
	for( int i=0 ; i < size ; i++){
		for( int j=0 ; j < size ; j++){	
			if (*(mat+size*j+i) == 0)
				countZero++;
			else if (countZero > 0) {
				*(mat+(size*(j-countZero))+i) = *(mat+size*j+i);
				*(mat+size*j+i) = 0;
			}
		}
		countZero = 0;
	}
}

void moveAllNumbersDown(int* mat, int size)
{
	int countZero = 0;
	for( int i=size-1 ; i >= 0 ; i--){
		for( int j=size-1 ; j >= 0 ; j--){
			if (*(mat+size*j+i) == 0)
				countZero++;
			else if (countZero > 0) {
				*(mat+(size*(j+countZero))+i) = *(mat+size*j+i);
				*(mat+size*j+i) = 0;
			}
		}
		countZero = 0;
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
			else if (col < size-1 && (*(mat+currentIndex) == *(mat+size*(row+1)+col)))
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

void moveNumbers(int* mat, int size, int direction)
{
	int countZero = 0;
	int start =  size - 1;
    	int end = -1;
    	int step = -1;
    	if (direction == 1){
    		start = 0;
    		end = size;
    		step = -1;
    	}
    	
	for( int i = 0 ; i < size ; i ++){
		for( int j = start ; j != end ; j += step){
			if (*(mat+size*j+i) == 0)
				countZero++;
			else if (countZero > 0) {
				*(mat+size*(j-step*countZero)+i) = *(mat+size*j+i);
				*(mat+size*j+i) = 0;
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
		moveAllNumbersLeft(board, size);
		sumAllTwoSameNumbersLeft(board, size, freeCells, score);
		moveAllNumbersLeft(board, size);
		addNumberToRandomCell(board, size, freeCells, score);
	}
}

void moveRight(int* board, int size, int* freeCells, int* score)
{
	if (checkCanMoveRight(board, size) == 0) 
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveAllNumbersRight(board, size);
		sumAllTwoSameNumbersRight(board, size, freeCells, score);
		moveAllNumbersRight(board, size);
		addNumberToRandomCell(board, size, freeCells, score);
	}

}

void moveUp(int* board, int size, int* freeCells, int* score)
{	
	if (checkCanMoveUp(board, size) == 0) 
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveAllNumbersUp(board, size);
		sumAllTwoSameNumbersUp(board, size, freeCells, score);
		moveAllNumbersUp(board, size);
		addNumberToRandomCell(board, size, freeCells, score);
	}
}

void moveDown(int* board, int size, int* freeCells, int* score)
{
	if (checkCanMoveDown(board, size) == 0) 
		printf("Nothing to move in this direction, choose another option\n");
	else {
		moveAllNumbersDown(board, size);
		sumAllTwoSameNumbersDown(board, size, freeCells, score);
		moveAllNumbersDown(board, size);
		addNumberToRandomCell(board, size, freeCells, score);
	}
}

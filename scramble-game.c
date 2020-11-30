#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Pre-set up for program */
// Data Structure:  Singly-Linked List
typedef struct node_s {
	char word[15];
	int point; //points assigned for each word
	struct node_s* next;
} wordnode;

// Function Prototypes
wordnode* loadWordSet();
char* returnWord(wordnode* node);
char* returnWord(wordnode* node, int index);
void printNode(wordnode* node);
char* scrambleHand(char array[15]);
void printHand(char array[15]);

// Global Variables
FILE* input = NULL;

/* Linked List Functions */
// Add node to tail
wordnode* addNode() {
	wordnode* head = NULL, * temp = NULL, * tail = NULL;
	temp = (wordnode*)malloc(sizeof(wordnode));
	// fscanf values into temp node
	if (head == NULL) {
		head = temp; // create head and set values
	}
	else {
		tail->next = temp; //set values
	}
	tail = temp;  //next pointer setup
	tail->next = NULL;
	temp = (wordnode*)malloc(sizeof(wordnode));

	return head;
}

wordnode* removeNode(wordnode* current, char word[15]) {
	wordnode* temp = NULL;
	temp = (wordnode*)malloc(sizeof(wordnode));
	while (strcmp(current->word, word) != 0) {
		current = current->next;
	}
	temp = current;
	current = temp->next;
	free(temp);
}

// Returns node->word by index location
//char* returnWord(wordnode* current) {
//	return current->word;
//}

char* returnWord(wordnode* current, int index) {
	int count = 0;
	char selection[15];
	while (count != index) {
		current = current->next;
		count++;
	}
	strcpy(selection, current->word);
	return selection;
}

// Returns node->point by index location
//int returnPoint(wordnode* current) {
//	return current->point;
//}

int returnPoint(wordnode* current, int index) {
	int count = 0;
	while (count != index) {
		current = current->next;
		count++;
	}
	return current->point;
}

// Returns 0 or 1 whether word exists in Linked List
wordnode* findNode(wordnode* current, char word[15]) {
	int value = 1;
	while (current != NULL) {
		if (strcmp(word, current->word) == 0) {
			return 0;
			break;
		}
		current = current->next;
	}

	return current;
}

// Returns length of word
int strLength(char word[15]) {
	int length = 0;
	for (int i = 0; word[i] != '\0'; i++) {
		length++;
	}

	return length;
}

// Print individual node data
void printNode(wordnode* current) {
	printf("%s %d\n", current->word, current->point);
}

// Print entire linked list
void printWordSet(wordnode* current) {
	char word[15];
	int point;
	while (current != NULL) {
//		strcpy(word, returnWord(current));
//		point = returnPoint(current);
		printNode(current);
		current = current->next;
	}
}

// Functions used to set up game dictionary
int chooseWordSet() {
	int valid = 0;
	int setValue = 0;

	srand(time(0));
	switch (rand() % 10) {
	case 0: input = fopen("WordSet0.txt", "r"); break;
	case 1: input = fopen("WordSet0.txt", "r"); break;
	case 2: input = fopen("WordSet0.txt", "r"); break;
	case 3: input = fopen("WordSet0.txt", "r"); break;
	case 4: input = fopen("WordSet0.txt", "r"); break;
	case 5: input = fopen("WordSet0.txt", "r"); break;
	case 6: input = fopen("WordSet0.txt", "r"); break;
	case 7: input = fopen("WordSet0.txt", "r"); break;
	case 8: input = fopen("WordSet0.txt", "r"); break;
	case 9: input = fopen("WordSet0.txt", "r"); break;
	}

	if (input != NULL) {
		return 0;
	}
	else {
		printf("File does not exist.  Please check that the file was placed in the correct directory.\n");
		return -1;
	}
}

// Load Linked List based on input file from chooseWordSet
wordnode* loadWordSet() {
	wordnode* head = NULL, * temp = NULL, * tail = NULL;
	temp = (wordnode*)malloc(sizeof(wordnode));
	while ((fscanf(input, "%s %d%*c", temp->word, &temp->point)) != EOF) {
		// fscanf values into temp node
		if (head == NULL) {
			head = temp; // create head and set values
		}
		else {
			tail->next = temp; //set values
		}
		tail = temp;  //next pointer setup
		tail->next = NULL;
		temp = (wordnode*)malloc(sizeof(wordnode));
	}

	return head;
}


int availableWords(wordnode* current) {
	int count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

void clueOutput(wordnode* current, int available) {
	int clueLoop = 0;
	if (available >= 5) {
		printf("5 clues to help you guess.\n");
		clueLoop = 5;
	}
	else {
		printf("%d clues to help you guess.\n", available);
		clueLoop = available;
	}

	int count = 0;  // Used to traverse specific index location of Linked List
	char clueWord[15];
	while (clueLoop != 0) { // Controller for dynamic clue word availability
		if ((count == 0) || (count == 1) ||
			(count == available - 3) || (count == available - 2) ||
			(count == available - 1)) {
			strcpy(clueWord, returnWord(current, count));
			int control = 0;
			for (int i = 0; clueWord[i] != '\0'; i++) {
				if (clueWord[i] == 'a') {
					printf("%c", 'a');
				} else if (clueWord[i] == 'e') {
					printf("%c", 'e');
				} else if (clueWord[i] == 'i') {
					printf("%c", 'i');
				} else if (clueWord[i] == 'o') {
					printf("%c", 'o');
				} else if (clueWord[i] == 'u') {
					printf("%c", 'u');
				} else {
					printf("-");
				}
			}
			printf("\n");
			clueLoop--;
		}
		count++;
	}

}

char* playerChoice(char hand[15]) {
	int count = 0,  valid = 1, length = strLength(hand);
	char playerGuess[15];

	while (valid != 0) {
		printf("Type your guess (between 4 and %d letters): ", length);
		fgets(playerGuess, 15, stdin);
		printf("\n");
		for (int i = 0; i < 15; i++) {
			if (playerGuess[i] == '\n') {
				playerGuess[i] = '\0';
			}
		}
		if (strLength(playerGuess) > 9) {
			printf("Entry was too long.\n");
			valid = 1;
		} else {
			valid = 0;
		}
	}
	
	return playerGuess;
}

int roundResults(wordnode* current, wordnode* correct, wordnode* wrong, char word[15]) {
	int found = 1, wordScore = 0;
	while (current != NULL) {
		found = strcmp(current->word, word);
		if (found = 0) {
			wordScore = current->point;
			break;
		}
		else {
			current = current->next;
		}

	}

	return wordScore;
}

int roundFormat(wordnode* current, char hand[15], int score) {
	wordnode *correct = NULL, *wrong = NULL;
	int roundScore = 0;
	int roundAvail = availableWords(current);
	char playerGuess[15];

	printf("Current Points: %d\n", score);
	
	printHand(hand);

	printf("There are %d words that you can guess.\n", roundAvail);
	clueOutput(current, roundAvail);
	strcpy(playerGuess, playerChoice(hand));
	roundScore = roundResults(current, correct, wrong, playerGuess);

	return score + roundScore;
}

/* Functions used to manage player hand */
// Output hand
void printHand(char hand[15]) {
	int control = 0;
	
	control = strLength(hand);
	for (int i = 0; i < control; i++) {
		printf("--- ");
	}
	printf("\n");

	for (int i = 0; hand[i] != '\0'; i++) {
		printf("%c ", hand[i]);
	}
	printf("\n");

	for (int i = 0; i < control; i++) {
		printf("--- ");
	}
	printf("\n");

}

// Scrambles letters for player hand
char* scrambleHand(char hand[15]) {
	int init = 0, end = 0, count= 0, control = 0;
	char temp;
	
	control = strLength(hand);

	for (int i = 0; i < 15; i++) { // random amount of time to shuffle
		while (end == init) {  // select a first and second char to swap
			init = rand() % control - 1;
			end = (rand() % control);
			if ((hand[init] < (char)0) || (hand[end] < (char)0)) {
				init = 0;
				end = 0;
			}
		}
		temp = hand[init];
		hand[init] = hand[end];
		hand[end] = temp;
		init = 0;
		end = 0;
	}
	return hand;
}

// Creates player hand based on longest word (head)
char* createHand(char word[15]) {
	char hand[15], currWord[15];
	strcpy(currWord, word);
	strcpy(hand, scrambleHand(currWord));
	return hand;
}

/* Game Driving Functions */
void endGame(wordnode* current, int score) {
	// did they win
	// display remaining words left
	int remainingCount = availableWords(current);
	printf("%d Words that were not guessed:\n", remainingCount);
	while (current != NULL) {
		printf("%s\t", current->word);
		current = current->next;
	}
	printf("\n");
}

void initGame() {
	int gameOver = 1, gameScore = 0;	
	char keyInput;
	wordnode* gameNode = NULL, * correct = NULL, * wrong = NULL;

	gameNode = loadWordSet();
	char playerHand[15];
	strcpy(playerHand, createHand(gameNode->word));

	while (gameOver != 0) {
		gameScore = roundFormat(gameNode, playerHand, gameScore);

		printf("Continue playing (Q/q to Quit)? ");
		scanf(" %c%*c", &keyInput);
		printf("\n");
		if ( (keyInput == 'Q') || (keyInput == 'q') ) {
			gameOver = 0;
		}
		else {
			printf("Would you like to scramble your hand (Y/y for Yes)? ");
			scanf(" %c%*c", &keyInput);
			printf("\n");
			if ((keyInput == 'Y') || (keyInput == 'y')) {
				scrambleHand(playerHand);
			}
		}
	}
	endGame(gameNode, gameScore);
	free(gameNode);
	free(correct);
	free(wrong);
}

// Main control starting driver
void main() {
		char rePlay = 'y';
		while (rePlay != 'q') {
			if (chooseWordSet() == 0) {
				printf("Let's play Word Scramble\n");
				initGame();
			}
			printf("Would you like to replay? (q to quit)\n");
			scanf(" %c%*c", &rePlay);
		}
	
	fclose(input);
	printf("Goodbye.");
}

/*
 * Author: Grant Pausanos
 * Date:             11/25/2019 1:33:54 PM
 * Lab: 8, Simon Game
 *
 * Purpose: A randomly generated sequence containing the channel of the buttons is created and the user has to copy the sequence
			of the pattern in order to win the game.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <Windows.h>
#include <time.h>

//Button Channels
#define GREEN_BUTTON 0
#define RED_BUTTON 1
#define YELLOW_BUTTON 2
#define BLUE_BUTTON 3

//LED Channels
#define GREEN_LED 0
#define RED_LED 1
#define YELLOW_LED 2
#define BLUE_LED 3

//Helpful Constants
#define TRUE 1
#define FALSE 0

#define ON 1
#define OFF 0

#define USER 0
#define COMPUTER 1

//Max Length is 5 as described by the procedure
#define MAX_LENGTH 5

//Function Prototypes
void runSimon(void);
void generateSequence(int length, int data[]);
void turnOnLED(int LED_NUM, int who);
void tripleBlink(int LED_CHANNEL);
int compareSequence(int computer[], int user[], int length);
int randInt(void);

int main(void)
{
	int setupNum;

	printf("Enter 0 to use DAQ module or 6 for simulator (Simon Game): ");
	scanf("%d", &setupNum);

	if (setupDAQ(setupNum) != TRUE) {
		printf("Error. Cannot initialise");
	}
	else {
		runSimon();
	}

	system("PAUSE");
	return 0;
}

/*
* runSimon Function
* Purpose: Contains the main operation to play the Simon game
* Paramters: None
* Return: None
*/
void runSimon(void) {

	//Variables to assign the status of the buttons
	int readGreen;
	int readRed;
	int readYellow;
	int readBlue;

	int roundSequence[5]; //Randomly generated sequence stored in this array
	int userSequence[5]; //User sequence stored in this array

	//Useful counter variables
	int counterRounds = 0;
	int counterLED = 0;
	int counterClicks = 0;

	int numOfClicks; //Stores the number of clicks the user has left
	int roundNumber = 1; //Stores the round the user is currently in
	int initialDelay = 0;

	int nextRound; //Necessary variable that tells whether the user can go to the next round
	int GAMEOVER = FALSE; //This variable becomes true if the user wants to quit the game




	printf("Welcome to the Simon Game.");

	while (continueSuperLoop() == TRUE) {

		//This if statement sleeps only when the game starts so the user has time to see the first light
		if (initialDelay == 0) {
			Sleep(1000);
			initialDelay = 1;
		}

		//Game starts
		if (GAMEOVER == FALSE) {

			//Generates a random sequence every game
			generateSequence(MAX_LENGTH, roundSequence);

			//The block of code in this for loop occurs every round of the game
			for (counterRounds = 0; counterRounds < roundNumber; counterRounds++) {

				numOfClicks = roundNumber;
				printf("Round %d \n", roundNumber);
				
				//Turns on the LED one at a time 
				for (counterLED = 0; counterLED < roundNumber; counterLED++) {
					turnOnLED(roundSequence[counterLED], COMPUTER);
				}

				printf("Now it's your turn. Copy the pattern. \n");
				printf("You have %d clicks left. \n", numOfClicks);

				//This while loop conitnues if the user still has more than 0 clicks
				while (numOfClicks > 0) {

					//Reads the button the is pressed by the user
					readGreen = digitalRead(GREEN_BUTTON);
					readRed = digitalRead(RED_BUTTON);
					readYellow = digitalRead(YELLOW_BUTTON);
					readBlue = digitalRead(BLUE_BUTTON);
					
					//When a button is pressed, it turns on the designated LED light,
					//decrements the number of clicks by 1 and adds the channel of the
					//button to the user sequence in order
					if (readGreen == ON) {
						userSequence[counterClicks] = GREEN_LED;
						turnOnLED(GREEN_LED, USER);
						numOfClicks--;
						counterClicks++;
						printf("You have %d clicks left. \n", numOfClicks);
					}
					else if (readRed == ON) {
						userSequence[counterClicks] = RED_LED;
						turnOnLED(RED_LED, USER);
						numOfClicks--;
						counterClicks++;
						printf("You have %d clicks left. \n", numOfClicks);
					}
					else if (readYellow == ON) {
						userSequence[counterClicks] = YELLOW_LED;
						turnOnLED(YELLOW_LED, USER);
						numOfClicks--;
						counterClicks++;
						printf("You have %d clicks left. \n", numOfClicks);
					}
					else if (readBlue == ON){
						userSequence[counterClicks] = BLUE_LED;
						turnOnLED(BLUE_LED, USER);
						numOfClicks--;
						counterClicks++;
						printf("You have %d clicks left. \n", numOfClicks);
					}
				}

				//Checks whether the user had the same pattern as the randomly generated sequence
				nextRound = compareSequence(roundSequence, userSequence, roundNumber);

				//The user goes to the next round if the sequence is the same as the randomly generated sequence
				if (nextRound == TRUE) {
					roundNumber++;
					counterClicks = 0;
				}
				else {
					printf("GAME OVER \n");
					tripleBlink(RED_LED);
					counterRounds = roundNumber + 1;
					GAMEOVER = TRUE;
				}
				printf("\n");

				//If the user surpasses 5 rounds, the user wins the game
				if (roundNumber > MAX_LENGTH) {
					printf("YOU WIN! \n");
					tripleBlink(GREEN_LED);
					counterRounds = roundNumber + 1;
					GAMEOVER = TRUE;
				}
			}
		}
		else {
			//Gives the user the option to play again or to quit
			printf("Type 0 to play again or close the window to exit: ");
			scanf("%d", &GAMEOVER);
			roundNumber = 1;
			counterClicks = 0;
			initialDelay = 0;
		}
	}
}

/*
* randInt Function
* Purpose: To generate a randum integer between 0 and 3, which are the possible LED channels
* Paramters: None
* Return: lightNum - The channel number of the LED
*/
int randInt(void) {
	int lightNum;

	lightNum = (rand() % 4);
	return lightNum;
}

/*
* generateSequence Function
* Purpose: Appends the randomly generated integers inside the randomSequence array
* Paramters: Max Length of the sequence --> 5
			 data[] --> The array for the randomly generated sequence
* Return: None
*/
void generateSequence(int length, int data[]) {
	int counter;
	srand(time(NULL));

	for (counter = 0; counter < length; counter++) {
		data[counter] = randInt();
	}

}
/*
* turnOnLED Function
* Purpose: Blinks the specific LED light once
* Paramters: LED_NUM --> Store the LED channel
			 who --> stores who wants the LED to be turned on; the computer or the user
* Return: None
*/
void turnOnLED(int LED_NUM, int who) {
	digitalWrite(LED_NUM, ON);
	Sleep(500);
	digitalWrite(LED_NUM, OFF);

	//If it is the user's turn, remove the 0.5s delay so it is more optimized and efficient for the user
	if (who == COMPUTER)
		Sleep(500);
}

/*
* compareSequence Function
* Purpose: compares the array of the randomly generated sequence and the sequence of the user
* Paramters: computer[] --> the array of the randomly generated sequence
*			 user[] --> the array of the sequence inputted by the user
*			 length --> the current round number
* Return: proceed --> 0 if the integer of each index in the array are not equivalent or
*					  1 if the integer of each index in the array are equivalent
*/
int compareSequence(int computer[], int user[], int length) {
	int temp;
	int score = 0;
	int proceed;

	//comparing the integer of each index of the arrays in order
	for (temp = 0; temp < length; temp++) {
		if (user[temp] == computer[temp]) {
			score++;
		}
	}

	if (score == length) {
		printf("You got the correct pattern! \n");
		Sleep(500);
		proceed = 1;
	}
	else
		proceed = 0;
	return proceed;
}

/*
* tripleBlink Function
* Purpose: Blinks the given LED channel 3 times
* Paramters: LED_CHANNEL --> the LED channel
* Return: None
*/
void tripleBlink(LED_CHANNEL) {
	int counter;

	for (counter = 0; counter < 3; counter++) {
		digitalWrite(LED_CHANNEL, ON);
		Sleep(250);
		digitalWrite(LED_CHANNEL, OFF);
		Sleep(250);
	}
}
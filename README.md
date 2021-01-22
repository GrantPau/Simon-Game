# Simon Game

## Purpose
A game where a randomly-generated sequence is created and the user attempts to copy the sequence of the pattern in order to win the game. This program uses the DAQ library in APSC 160.


## Features
The program is required to do as follows:
- Generate a random LED sequence for each round, for a total of 5 rounds
- When a push button is pressed, turn on its corresponding LED light
- User copies the sequence by pressing the LED's corresponsing button to progress
- If the user gets the correct pattern, let the green LED blink 3 times and increase the round by 1.
- If the user gets the incorrect pattern, let the red LED blink 3 times and reset the game
- If the user gets the correct patter for all 5 rounds, let the green LED blink 5 times instead of 3
- Each round adds an extra sequence to increase level of difficulty (ie. round 1 starts with 1 random LED )
- The console helps keep track of the number of clicks left for the user

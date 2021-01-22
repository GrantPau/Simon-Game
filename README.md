# Simon Game

## Purpose
A game where a randomly-generated sequence is created and the user attempts to copy the sequence of the pattern in order to win the game. This program uses the DAQ library in APSC 160.


## Features
The program is required to do the following:
- Generate a random LED sequence for each round, for a total of 5 rounds
- When a push button is pressed, turn on its corresponding LED light
- User copies the sequence by pressing the LED's corresponsing button to progress
- If the user gets the correct pattern, increase the round by 1
- If the user gets the incorrect pattern, let the red LED blink 3 times and reset the game
- If the user gets the correct patter for all 5 rounds, let the green LED blink 5
- Each round adds an extra sequence to increase level of difficulty (ie. round 1 has 1 blinking LED, round 3 has 3 blinking LEDs)
- As the round progresses, the program must remember the previous sequence and add one random sequence to increase difficulty (ie. round 2 is red --> green, round 3 is red --> green --> green)
- The console helps keep track of the number of clicks left

## Clip of Winning a Game
Winning a game only occurs after completing Round 5, as shown below.
<br/>
![](https://github.com/GrantPau/Simon-Game/blob/main/Clips/winning-a-game.gif)

## Clip of Losing a Game
In this example, the user pushes the wrong button during Round 2 and the 3 consecutive blinking lights indicates that it is game over.
<br/>
![](https://github.com/GrantPau/Simon-Game/blob/main/Clips/losing-a-round.gif)

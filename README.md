# Craps-Game
Programming Principles II Final Project

In this game, a player rolls two dice. Each die has six faces.
Each face contains 1, 2, 3, 4, 5 and 6 spots. After the dice have come to rest, the sum of
the spots on the two top faces is calculated. If the sum is 7 or 11 on the first throw the
player wins. If the sum is 2, 3, or 12 on the first throw, the player loses. If the sum is 4, 5,
6, 8, 9 or 10 on the first throw, that sum becomes the player’s “point.” To win, a player
must continue rolling the dice until the player rolls the point value. The player loses by
rolling a 7 before rolling the point.
If a player wins one game, s/he will earn $10. Otherwise, s/he will lose $1. A player can
keep playing the game until s/he chooses to quit or his/her balance becomes 0 or less. 

There are totally 10 players that can play the game. All players’ information (name,
balance, gain so far) is stored in the file players.txt. When your program is started, the balance and gain of each player should be
retrieved from this file. Before a player quit your program, your program should make
sure the file players.txt contains the latest balance and gain for each player. 

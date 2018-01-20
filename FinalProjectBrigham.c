#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "players.txt"
#define MAX_PLAYERS 10

/*Structure that outlines the informations of each player*/
typedef struct {
  char name[20];
  int balance;
  int winnings;
} Player;
/*function declarations*/
void LoadPlayers(Player *p, int *total);
void menu(void);
void TopBalance(void);
void Game(void);
void PrintTopFive(int type);
void Sort(int type);
int GetPlayerIndex(void);
void Writetofile(void);
/*creation of file pointer, array of players, and ints that count number of total players, as well as control loop*/
FILE *fp;
Player players[10];
int totalPlayers, forever=1;


int main(void)
{
    /*reads in players*/
    LoadPlayers(players, &totalPlayers);
    /*displays menu*/
    menu();
    return 0;
}

/*function that reads in player data*/
void LoadPlayers(Player *p, int *total) {
    /*opens file*/
  fp = fopen(FILE_NAME, "r");
  int i =0;
  /*checks to make sure player has a name, balance, and winnings in file*/
  while(fscanf(fp, "%s\t%d\t%d", p[i].name, &p[i].balance, &p[i].winnings) == 3)
  {
       if (feof(fp)) {
        fclose(fp);
        break;
      }
    i++;
    }
     *total = i;
  fclose(fp);
  }

  /*function that displays menu of the game*/
void menu(void) {
  while(forever==1){
    printf("--------------- Craps Game Menu ---------------\n"
    "0) Top up your balance\n"
    "1) Play Game\n"
    "2) Top 5 Players by Balance\n"
    "3) Top 5 Winners By What They Won\n"
    "4) Exit\n"
    "-----------------------------------------------\n"
    "Please type a number from 0 to 4 to select menu item:\n");
    char user;
    user = getchar();
    getchar();
    /*if user enters a choice that is not on the menu*/
   if ( user < '0' || user > '4' ) {
      printf("Enter a valid choice.\n");
      continue;
    } else {
      switch(user) {
        case '0': {
          TopBalance();
          break;
        }
        case '1':
          Game();
          break;
        case '2':
          PrintTopFive(0);
          break;
        case '3':
          PrintTopFive(1);
          break;
        case '4':
         Writetofile();
         /*breaks the loop, ending the game*/
         forever=0;
          break;

      }
    }
  }
}

/*function that checks to see if the player's name is in file*/
int GetPlayerIndex() {
  char playerName[20];
  int knownPlayer,playerIndex;
  printf("Enter your name: ");
  scanf("%s", playerName);
  /*scans through file*/
  for (playerIndex = 0; playerIndex < totalPlayers; playerIndex++) {
    if (strcmp(playerName, players[playerIndex].name) == 0)
      return playerIndex;
  }
  printf("That name was not found, please enter a name from the list below.\n");
  /*prints out names of players in file if user enters a name that is not in file*/
  for (knownPlayer = 0; knownPlayer < totalPlayers; knownPlayer++)
    printf("%s, ", players[knownPlayer].name);
  printf("\n");
  return -1;
}

/*function that allows the player to set their balance to a number*/
void TopBalance(void) {
  int bal, playerIndex;
  /*checks if name is in file*/
  for (;;) {
    playerIndex = GetPlayerIndex();
    if (playerIndex != -1) break;
  }
  printf("Enter the balance you would like: ");
  scanf("%d", &bal); getchar();
  /*assigns entered balance to players balance*/
  players[playerIndex].balance = bal;
}


/*this is the craps game function*/
void Game(void) {
  char name[20];
int playerIndex;
/*checks if players name is in file*/
  for (;;) {
    playerIndex = GetPlayerIndex();
    if (playerIndex != -1)
     break;
  }
  getchar();
  srand(time(NULL));
  printf("Your starting balance is: %d", players[playerIndex].balance);
  for (;;) {
    printf("\nPress ENTER to roll the dice.\n");
    getchar();
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    int dicetotal = dice1 + dice2;
    printf("You rolled a %d and a %d for a total of %d.\n", dice1, dice2, dicetotal);
    switch(dicetotal) {
        /*if player wins on first rol*/
      case 7:
      case 11:
        players[playerIndex].balance += 10;
        players[playerIndex].winnings += 10;
        printf("You win! Your current balance is %d.\n", players[playerIndex].balance);
        break;
        /*if player loses on first roll*/
      case 2:
      case 3:
      case 12:
        players[playerIndex].balance -= 1;
        players[playerIndex].winnings -= 1;
        printf("The house wins. "
             "Your current balance is %d.\n", players[playerIndex].balance);
        break;
        /*if player needs to roll again*/
      case 4:
      case 5:
      case 6:
      case 8:
      case 9:
      case 10: {
          /*creates players point value*/
        int point = dicetotal;
        for (;;) {
          printf("Press ENTER to roll the dice.\n");
          getchar();
          dice1 = rand() % 6 + 1;
          dice2 = rand() % 6 + 1;
          dicetotal = dice1 + dice2;
          printf("You rolled %d and %d for a total of %d.\n", dice1, dice2, dicetotal);
          if (dicetotal == 7) {
                /*if player loses on second roll*/
            players[playerIndex].balance -= 1;
            players[playerIndex].winnings -= 1;
            printf("The house wins. "
                   "Your current balance is %d.\n", players[playerIndex].balance);
            break;
          /*if player wins on second roll*/
          } else if (dicetotal == point) {
            players[playerIndex].balance += 10;
            players[playerIndex].winnings += 10;
            printf("You win! Your current balance is %d.\n", players[playerIndex].balance);
            break;
          }

        }
        break;
      }
    }
    /*checks if player wants to play again*/
    printf("Would you like to play again (y/n)? ");
    char again = getchar();
    getchar();
    if (again == 'y')
      continue;
    else
    {
        printf("\n%s's ending balance is: %d\n", players[playerIndex].name, players[playerIndex].balance);
        break;
    }
  }
  menu();
}

/*function prints top 5 by balance or by winnings depending on value of type*/
void PrintTopFive(int type) {
  Sort(type);
  int i,j;
  if (type == 0) {
    printf("-------------- Top 5 By Balance ---------------\n");
    for (i = MAX_PLAYERS - 1; i > MAX_PLAYERS - 6; i--) {
      printf("%s\t%d\n", players[i].name, players[i].balance);
    }
  } else {
    printf("--------------- Top 5 By Winnings -----------------\n");
    for (j = MAX_PLAYERS - 1; j > MAX_PLAYERS - 6; j--) {
      printf("%s\t%d\n", players[j].name, players[j].winnings);
    }
  }
  printf("-----------------------------------------------\n");
}


/*function that sorts to find top 5 players*/
void Sort(int type){
  int min, indexA, indexB;
  for( indexA = 0; indexA < MAX_PLAYERS; indexA++){
    min = indexA;

    for(indexB = indexA+1; indexB < MAX_PLAYERS; indexB++){
      if (type == 0) {
        if(players[indexB].balance < players[min].balance)
          min = indexB;
      }
      else {
        if(players[indexB].winnings < players[min].winnings)
          min = indexB;
      }
    }
    /*swaps players so top 5 are printed*/
    Player temp = players[indexA];
    players[indexA] = players[min];
    players[min] = temp;
  }
}

/*function that writes to file*/
void Writetofile() {
    /*opens file*/
  fp = fopen(FILE_NAME, "w+b");
  int i;
  /*writes all new information to file*/
  for (i = 0; i < totalPlayers; i++) {
    fprintf(fp, "%s\t%d\t%d\r\n", players[i].name, players[i].balance, players[i].winnings);
  }
  fclose(fp);
}

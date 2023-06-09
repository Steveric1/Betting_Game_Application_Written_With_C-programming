#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <unistd.h> 

/* *Simple Betting Game"
  "Jack", "Queen", "King" - computer shuffles this cards.
  Player has to guess the position of queen.
  if he/she wins, he/she will take 2*bet.
  if he/she looses, he/she looses the bet money.
  player has 100$ initial deposity.
*/

//Global variable
int virtualCash = 100;
int abortFlag = 0;

//shuffing function
void shuffing()
{
    const char* frames[] = {
        "shuffing   ",
        "shuffing.  ",
        "shuffing.. ",
        "shuffing..."
    };
    int numFrames = sizeof(frames) / sizeof(frames[0]);

    for (int i = 0; i < 10; i++) {
        printf("%s\r", frames[i % numFrames]);
        fflush(stdout);
        usleep(500000);  // Sleep for 0.5 seconds
    }

    printf("\n");
}

//play main function
void play(int bet)
{
    char c[3] = {'J', 'Q', 'K'};
    shuffing();
    srand(time(NULL)); //seeding random number generator
    int i;

    for (i = 0; i < 5; i++)
    {
        int x = rand() % 3;
        int y = rand() % 3;
        int temp = c[x];
        c[x] = c[y];
        c[y] = temp;

    }

    int playersGuess;
    printf("what is the position of queen - 1, 2 or 3?: ");
    scanf("%d", &playersGuess);

    if (c[playersGuess - 1] == 'Q')
    {
        virtualCash += 2*bet;
        printf("You Win! Result = %c %c %c Total Cash = %d\n", c[0],c[1],c[2], virtualCash);
    }
    else
    {
        virtualCash -= bet;
        printf("You Loose! Result = %c %c %c Total Cash = %d\n", c[0],c[1],c[2], virtualCash);
    }
}

//Game loop function
void gameLoop()
{
    int bet;
    while (virtualCash != 0)
    {
        printf("\nPlace your bet $: ");
        scanf("%d", &bet);
        if (bet == 0 || bet > virtualCash) break;
        play(bet);
        printf("******************************************************\n");
    }
}

//processing function
void processing()
{
    const char* frames[] = {
        "processing   ",
        "processing.  ",
        "processing.. ",
        "processing..."
    };
    int numFrames = sizeof(frames) / sizeof(frames[0]);

    for (int i = 0; i < 10; i++) {
        printf("%s\r", frames[i % numFrames]);
        fflush(stdout);
        usleep(500000);  // Sleep for 0.5 seconds
    }

    printf("\n");
}

//Withdraw function
void withdrawCash(int signum)
{
    printf("\nDo you want to withdraw the earned money before existing? (y/n): ");
    fflush(stdout); //flush output buffer

    //List of supported bank
    char Bank1[20] = "GTBank";
    char Bank2[20] = "Access Bank";
    char Bank3[20] = "PalmPay";
    char Bank4[20] = "Opay";

    //get user input
    char response;
    scanf(" %c", &response);
    if (response == 'Y' || response == 'y')
    {
        int bank, acctNum;
        printf("\nSelect your bank from the list of supported banks\n1.%s\n2.%s\n3.%s\n4.%s\n", Bank1, Bank2, Bank3, Bank4);
        scanf("%d", &bank);
        printf("please input your account number: ");
        scanf("%d", &acctNum);
        processing();
        printf("Total cash of %d$ withdraw successfully!\n", virtualCash);
        exit(1);
    }
    else 
    {
        printf("Gracefully existing...\n");
        abortFlag = 1;
    }
}

int main()
{
    printf("**Welcome to Betting Casino**\n");
    printf("Total cash %d\n", virtualCash);

    signal(SIGINT, withdrawCash);
    gameLoop();

    while(1)
    {
       if (virtualCash == 0)
       {
            char playGame;
            printf("\nDo you want to continue playing? (y/Y): ");
            scanf(" %c", &playGame);
            if (playGame == 'y' || playGame == 'Y')
            {
                printf("Make a deposit to continue playing\n");
                scanf("%d", &virtualCash);
                gameLoop(virtualCash);
            }
            else
            {
                printf("\n**Thanks for playing**\n");
                break;
            }
        }
    }
    return 0;
}


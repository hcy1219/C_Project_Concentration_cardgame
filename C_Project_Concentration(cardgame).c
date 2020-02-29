/**
* ENGG1110 Problem Solving by Programming
*
* Course Project
*
* I declare that the project here submitted is original
* except for source material explicitly acknowledged,
* and that the same or closely related material has not been
* previously submitted for another course.
* I also acknowledge that I am aware of University policy and
* regulations on honesty in academic work, and of the disciplinary
* guidelines and procedures applicable to breaches of such
* policy and regulations, as contained in the website.
*
* University Guideline on Academic Honesty:
* https://www.cuhk.edu.hk/policy/academichonesty/
*
* Student Name : Hsu Chia Yuan
* Student ID : 1155124446
* Class/Section : ENGG1110-LL01
* Date : 2019/4/15
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card {
    char suit;   // 'S'pade / 'H'eart / 'C'lub / 'D'iamond
    int  rank;   // A (1) / 2 - 10 / J (11) / Q (12) / K (13);
    int  status; // covered (0) or flipped (1) or chosen (-1), etc.
    int  order; //card's order
} TypeCard;

void printCard(TypeCard aCard){
    if (aCard.status == 0){
        printf("XXX");
    }else if(aCard.status == 1){
        /* display suit of a card */
        switch (aCard.suit) {
            case 'S':
            case 'H':
            case 'C':
            case 'D':
                printf("%c", aCard.suit);
                break;
        }
        printf(" ");
        /* display rank of a card */
        switch (aCard.rank){
            case 1:
                printf("A");
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                printf("%d", aCard.rank);
                break;
            case 11:
                printf("J");
                break;
            case 12:
                printf("Q");
                break;
            case 13:
                printf("K");
                break;
        }
    }
    return;
}

void showDesktop(TypeCard desktop[4][13]){
    /*show the desktop*/
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            if(desktop[i][j].status == 0){
                printf("XXX");
                printf("\t");
            }else{
                printf("%c", desktop[i][j].suit);
                if(desktop[i][j].rank == 1){
                    printf(" A");
                }else if(desktop[i][j].rank == 11){
                    printf(" J");
                }else if(desktop[i][j].rank == 12){
                    printf(" Q");
                }else if(desktop[i][j].rank == 13){
                    printf(" K");
                }else{
                    if(desktop[i][j].rank == 10){
                        printf("%d", desktop[i][j].rank);
                    }else{
                        printf(" %d", desktop[i][j].rank);
                    }
                }
                printf("\t");
            }
        }
        printf("\n");
    }
}

void shuffleCard (TypeCard desktop[4][13]){
    int i = 0, j = 0, k = 0;
    int tmp[52];
    srand(time(0));
    for(i = 0; i < 52; i ++){
        tmp[i] = i+1;
    }
    for(i = 0; i < 52; i++){
        j = rand()%(52-i)+i;
        k = tmp[i];
        tmp[i] = tmp[j];
        tmp[j] = k;
    }
    k = 0;
    for(i = 0; i < 4; i ++){
        for(j = 0; j < 13; j ++){
            desktop[i][j].order = tmp[k];

            if(desktop[i][j].order >= 1 && desktop[i][j].order <= 13){
                desktop[i][j].suit = 'S';
            }else if(desktop[i][j].order >= 14 && desktop[i][j].order <= 26){
                desktop[i][j].suit = 'H';
            }else if(desktop[i][j].order >= 27 && desktop[i][j].order <= 39){
                desktop[i][j].suit = 'C';
            }else if(desktop[i][j].order >= 40 && desktop[i][j].order <= 52){
                desktop[i][j].suit = 'D';
            }

            if(desktop[i][j].order % 13 == 0){
                desktop[i][j].rank = 13;
            }else{
                desktop[i][j].rank = desktop[i][j].order %13;
            }
            k ++;
        }
    }

}

void closeCard(TypeCard desktop[4][13]){
    for(int row = 0; row < 4; row ++){
        for(int col = 0; col < 13; col ++){
            desktop[row][col].status = 0;
        }
    }
}

void playGame_HumCom(TypeCard desktop[4][13]){
    int Hum_row1 = 0, Hum_col1 = 0;
    int Hum_row2 = 0, Hum_col2 = 0;
    int Com_row1 = 0, Com_col1 = 0;
    int Com_row2 = 0, Com_col2 = 0;
    int i = 0, j = 0;
    int flippedCard = 0, Hum_flipped = 0, Com_flipped = 0;
    int turns = 0;

    while(flippedCard <= 52){
        i = 0;
        j = 0;

        printf("Please input 1st card:\n");
        while(i == 0){
            scanf("%d%d", &Hum_row1, &Hum_col1);
            Hum_col1 = Hum_col1 -1;
            if(!(Hum_row1 >= 0 && Hum_row1 <= 3 && Hum_col1+1 >= 1 && Hum_col1+1 <= 13)){
                printf("Row and column must be within 0 - 3 and 1 - 13\n");
                printf("Please input 1st card:");
            }else if(desktop[Hum_row1][Hum_col1].status == 1){
                printf("The card must not be flipped already\n");
                printf("Please input 1st card:");
            }else{
                printf("You chose 1st card (%d, %d) and it is ", Hum_row1, Hum_col1+1);
                desktop[Hum_row1][Hum_col1].status = 1;
                printCard(desktop[Hum_row1][Hum_col1]);
                printf("\n");
                i = 1;
                turns ++;
            }
        }
        printf("Please input 2nd card:\n");
        while(j == 0){
            scanf("%d%d", &Hum_row2, &Hum_col2);
            Hum_col2 = Hum_col2 -1;
            if(!(Hum_row2 >= 0 && Hum_row2 <= 3 && Hum_col2+1 >= 1 && Hum_col2+1 <= 13)){
                printf("Row and column must be within 0 - 3 and 1 - 13\n");
                printf("Please input 2nd card:");
            }else if(Hum_row1 == Hum_row2 && Hum_col1 == Hum_col2){
                printf("The second card cannot be the same as first\n");
                printf("Please input 2nd card:");
            }else if(desktop[Hum_row2][Hum_col2].status == 1){
                printf("The card must not be flipped already\n");
                printf("Please input 2nd card:");
            }else{
                printf("You chose 2nd card (%d, %d) and it is ", Hum_row2, Hum_col2+1);
                desktop[Hum_row2][Hum_col2].status = 1;
                printCard(desktop[Hum_row2][Hum_col2]);
                printf("\n");
                j = 1;
                turns ++;
            }
        }
        if(desktop[Hum_row1][Hum_col1].rank == desktop[Hum_row2][Hum_col2].rank){
            printf("You got a matched pair!\n\n");
            desktop[Hum_row1][Hum_col1].status = 1;
            desktop[Hum_row2][Hum_col2].status = 1;
            flippedCard = flippedCard + 2;
            Hum_flipped = Hum_flipped + 2;
            showDesktop(desktop);
            printf("Flipped cards: %d; You: %d; Computer: %d;\n", flippedCard, Hum_flipped, Com_flipped);
            if(flippedCard == 52){
                printf("*** End of Game ***\n");
                printf("%d turns played\n", turns);
                if(Hum_flipped > Com_flipped){
                    printf("You win!\n");
                }else if(Hum_flipped < Com_flipped){
                    printf("Computer wins!\n");
                }else{
                    printf("A tie!\n");
                }
                flippedCard ++;
                }
        }else{
            desktop[Hum_row1][Hum_col1].status = 0;
            desktop[Hum_row2][Hum_col2].status = 0;
            showDesktop(desktop);
            printf("Flipped cards: %d; You: %d; Computer: %d;\n", flippedCard, Hum_flipped, Com_flipped);
        }

        printf("\n");

        i = 0;
        j = 0;

        while(i == 0){
            Com_row1 = rand()%(4);
            Com_col1 = 1 + rand()%13;
            if(desktop[Com_row1][Com_col1-1].status == 0){
                printf("Computer chose 1st card (%d, %d) and it is ", Com_row1, Com_col1);
                Com_col1 = Com_col1 -1;
                desktop[Com_row1][Com_col1].status = 1;
                printCard(desktop[Com_row1][Com_col1]);
                i = 1;
                turns ++;
            }
        }
        printf("\n");

        while(j == 0){
            Com_row2 = rand()%(4);
            Com_col2 = 1 + rand()%13;
            if(desktop[Com_row2][Com_col2-1].status == 0 && Com_row2 != Com_row1 && Com_col2-1 != Com_col1){
                printf("Computer chose 2nd card (%d, %d) and it is ", Com_row2, Com_col2);
                Com_col2 = Com_col2 -1;
                desktop[Com_row2][Com_col2].status = 1;
                printCard(desktop[Com_row2][Com_col2]);
                j = 1;
                turns ++;
            }
        }
        printf("\n");

        if(desktop[Com_row1][Com_col1].rank == desktop[Com_row2][Com_col2].rank){
            printf("Computer got a matched pair!\n");
            desktop[Com_row1][Com_col1].status = 1;
            desktop[Com_row2][Com_col2].status = 1;
            flippedCard = flippedCard + 2;
            Com_flipped = Com_flipped + 2;
            showDesktop(desktop);
            printf("Flipped cards: %d; You: %d; Computer: %d;\n", flippedCard, Hum_flipped, Com_flipped);
            if(flippedCard == 52){
                printf("*** End of Game ***\n");
                printf("%d turns played\n", turns);
                if(Hum_flipped > Com_flipped){
                    printf("You win!\n");
                }else if(Hum_flipped < Com_flipped){
                    printf("Computer wins!\n");
                }else{
                    printf("A tie!\n");
                }
                flippedCard ++;
                }
        }else{
            desktop[Com_row1][Com_col1].status = 0;
            desktop[Com_row2][Com_col2].status = 0;
            showDesktop(desktop);
            printf("Flipped cards: %d; You: %d; Computer: %d;\n", flippedCard, Hum_flipped, Com_flipped);
        }
    }
    }

void playGame_ComCom(TypeCard desktop[4][13]){
    int flippedCard = 0, Com1_flipped = 0, Com2_flipped = 0;
    int Com1_row1 = 0, Com1_col1 = 0;
    int Com1_row2 = 0, Com1_col2 = 0;
    int Com2_row1 = 0, Com2_col1 = 0;
    int Com2_row2 = 0, Com2_col2 = 0;
    int i = 0, j = 0;
    int m = 0, n = 0;
    int turns = 0;

    showDesktop(desktop);
    printf("\n");

    while(flippedCard <= 52){
        i = 0, j = 0, m = 0, n = 0;

        while(i == 0){
            Com1_row1 = rand()%(4);
            Com1_col1 = 1 + rand()%13;
            if(desktop[Com1_row1][Com1_col1-1].status == 0){
                printf("Computer 1 chose 1st card (%d, %d) and it is ", Com1_row1, Com1_col1);
                Com1_col1 = Com1_col1 -1;
                desktop[Com1_row1][Com1_col1].status = 1;
                printCard(desktop[Com1_row1][Com1_col1]);
                printf("\n");
                i = 1;
                turns ++;
                }
            }

        while(j == 0){
            Com1_row2 = rand()%(4);
            Com1_col2 = 1 + rand()%13;
            if(desktop[Com1_row2][Com1_col2-1].status == 0){
                printf("Computer 1 chose 2nd card (%d, %d) and it is ", Com1_row2, Com1_col2);
                Com1_col2 = Com1_col2 -1;
                desktop[Com1_row2][Com1_col2].status = 1;
                printCard(desktop[Com1_row2][Com1_col2]);
                printf("\n");
                j = 1;
                turns ++;
                }
            }
        if(desktop[Com1_row1][Com1_col1].rank == desktop[Com1_row2][Com1_col2].rank){
            printf("Computer 1 got a matched pair!\n");
            flippedCard = flippedCard + 2;
            Com1_flipped = Com1_flipped + 2;
            if(flippedCard == 52){
                printf("\n");
                showDesktop(desktop);
                printf("\n");
            }
            printf("Flipped cards: %d; Computer 1: %d; Computer 2: %d;\n", flippedCard, Com1_flipped, Com2_flipped);
            if(flippedCard == 52){
                printf("\n*** End of Game ***\n");
                printf("%d turns played\n", turns);
                if(Com1_flipped > Com2_flipped){
                    printf("Computer 1 wins!\n");
                }else if(Com1_flipped < Com2_flipped){
                    printf("Computer 2 wins!\n");
                }else{
                    printf("A tie!\n");
                }
                printf("\n");
                flippedCard ++;
                }
        }else{
            desktop[Com1_row1][Com1_col1].status = 0;
            desktop[Com1_row2][Com1_col2].status = 0;
            printf("Flipped cards: %d; Computer 1: %d; Computer 2: %d;\n", flippedCard, Com1_flipped, Com2_flipped);
        }

        printf("\n");

        while(m == 0){
            Com2_row1 = rand()%(4);
            Com2_col1 = 1 + rand()%13;
            if(desktop[Com2_row1][Com2_col1-1].status == 0){
                printf("Computer 2 chose 1st card (%d, %d) and it is ", Com2_row1, Com2_col1);
                Com2_col1 = Com2_col1 -1;
                desktop[Com2_row1][Com2_col1].status = 1;
                printCard(desktop[Com2_row1][Com2_col1]);
                printf("\n");
                m = 1;
                turns ++;
                }
            }

        while(n == 0){
            Com2_row2 = rand()%(4);
            Com2_col2 = 1 + rand()%13;
            if(desktop[Com2_row2][Com2_col2-1].status == 0){
                printf("Computer 2 chose 2nd card (%d, %d) and it is ", Com2_row2, Com2_col2);
                Com2_col2 = Com2_col2 -1;
                desktop[Com2_row2][Com2_col2].status = 1;
                printCard(desktop[Com2_row2][Com2_col2]);
                printf("\n");
                n = 1;
                turns ++;
                }
            }
        if(desktop[Com2_row1][Com2_col1].rank == desktop[Com2_row2][Com2_col2].rank){
            printf("Computer 2 got a matched pair!\n");
            flippedCard = flippedCard + 2;
            Com2_flipped = Com2_flipped + 2;
            if(flippedCard == 52){
                printf("\n");
                showDesktop(desktop);
                printf("\n");
            }
            printf("Flipped cards: %d; Computer 1: %d; Computer 2: %d;\n", flippedCard, Com1_flipped, Com2_flipped);
            if(flippedCard == 52){
                printf("\n*** End of Game ***\n");
                printf("%d turns played\n", turns);
                if(Com1_flipped > Com2_flipped){
                    printf("Computer 1 wins!\n");
                }else if(Com1_flipped < Com2_flipped){
                    printf("Computer 2 wins!\n");
                }else{
                    printf("A tie!\n");
                }
                printf("\n");
                flippedCard ++;
            }

        }else{
            desktop[Com2_row1][Com2_col1].status = 0;
            desktop[Com2_row2][Com2_col2].status = 0;
            printf("Flipped cards: %d; Computer 1: %d; Computer 2: %d;\n", flippedCard, Com1_flipped, Com2_flipped);
        }
        printf("\n");
    }
}

void startGame(TypeCard desktop[4][13]){
    int userChoice = 0, i = 0;
    while(i == 0){
        printf("Please choose a mode of the game:\n");
        printf("1. Human vs. Computer\n");
        printf("2. Computer vs. Computer\n");
        printf("0. Quit\n");
        printf("Your choice:\n");
        scanf("%d", &userChoice);
        if(userChoice >= 0 && userChoice <= 2){
            if(userChoice == 1){
                shuffleCard(desktop);
                closeCard(desktop);
                printf("\n");
                showDesktop(desktop);
                printf("\n");
                playGame_HumCom(desktop);
            }else if(userChoice == 1){
                shuffleCard(desktop);
                closeCard(desktop);
                printf("\n");
                showDesktop(desktop);
                printf("\n");
                playGame_HumCom(desktop);
            }else if(userChoice == 0){
                i = 1;
                exit(0);
            }
        }else{
            return startGame(desktop);
        }
}


int main(void)
{
    printf("*****************************\n");
    printf("* Welcome to Concentration! *\n");
    printf("*****************************\n");

    TypeCard desktop[4][13];

    startGame(desktop);





    return 0;
}


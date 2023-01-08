#include <stdio.h>
#include <stdlib.h>   //l'system(cls)//
#include <time.h>    // l'Clock() // 
#include <windows.h> //  l'SetCursorPosition()  //
#include <conio.h>  // l'GetCh() w gotoxy() // 
void gotoxy(int x, int y)
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p); //// 
}

void boundary()       // Map Borders //
{
    printf("%c", 218);
    for (int i = 1; i < 119; i++)
    {
        printf("%c", 196);      //      -     // 
    }
    printf("%c", 191);         //      +     // 
    for (int i = 1; i < 29; i++)
    {
        gotoxy(119, i);
        printf("%c", 179); //      |     // 
        gotoxy(0, i);
        printf("%c", 179);
    }
    printf("\n%c", 192); //       -    // 
    for (int i = 1; i < 119; i++)
    {
        printf("%c", 196); //      -     // 
    }
    printf("%c", 217); //      +     // 
    gotoxy(0, 0);
}

void move(int *x, int *y, char *l, char c, int len)
{
    gotoxy(x[len - 1], y[len - 1]);
    printf(" "); // To remove the Traces //
    for (int i = len; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    *l = c;
    if (len > 1)
    {
        gotoxy(x[1], y[1]);
        printf("o");
    }
}

int check(int px, int py, int *x, int *y, int len)      // verify snake took the bate or not // 
{
    for (int i = 0; i < len; i++)
    {
        if (px == x[i] && py == y[i])
        {
            return 1;
        }
    }
    return 0;
}

void over(int x, int y, int len)            // end game screen // 
{
	system("cls");
    gotoxy(x, y);
    printf("%c", 254);
    gotoxy(1, 1);
    printf("Hak 5sert Ya3tik sa7a !!!\n");
    printf("%cTry Harder next Time Ya Noob \n",179);
    printf("%c Hak 7asalet  : %d   ", 179, len - 1);
    while (getch() != 13)              //Enter Ascii Number : 13 //
        ;
    exit(0);
}

int main()
{
    boundary();
    gotoxy(1, 1);

    printf("- Z --- Z --- Z --- Z --- Z --- Z --- Z --- Z --- Z --- 7nech  --- Z --- Z --- Z --- Z --- Z --- Z --- Z --- Z --- Z -\n");
    printf("%cMade By Ghassen Lahdiri\n",179);
    printf("%cUse Arrows to move \n", 179);
    printf("%cYou can't Move Backward  \n", 179);
    printf("%cPress Enter to pause the game \n", 179);
    printf("%cDon't Change window size \n", 179);
    printf("%cIf you're ready press Enter ", 179);

    getch();
    system("cls");
    boundary();

    srand(time(NULL));
    int *x, *y, px = ((rand() % 58) * 2) + 3, py = (rand() % 28) + 1, len = 1;
    char c, l;
    clock_t t;

    x = (int *)malloc(sizeof(int) * (len + 1));
    y = (int *)malloc(sizeof(int) * (len + 1));
    x[0] = 25;
    y[0] = 20;

    gotoxy(px, py);
    printf("%c", 15); //          o       //

    gotoxy(x[0], y[0]);
    printf("X");

    while (1)
    {
        do //While bait not eatten yet //
        {
            t = clock();
            while (clock() < t + 250 && !kbhit())  //verify if key pressed //  //clock() count time since execution  // 
                ;
            if (clock() < t + 250)
            {                           // Choose  move when  2 keys pressed at the same time //
                c = getch();
                if (c == 75 && l == 77)  // left + right = right //
                    c = 77;
                else if (c == 77 && l == 75) // right + left = left //
                    c = 75;
                else if (c == 80 && l == 72) // down + up = up //
                    c = 72;
                else if (c == 72 && l == 80) // up + down = down // 
                    c = 80;
            }

            switch (c)
            {
            case 0:
                break;

            case 224:
                break;

            case 80:                            // down arrow // 
                move(x, y, &l, c, len);
                gotoxy(x[0], ++y[0]);
                printf("%c", 31);

                if (y[0] == 29)                //  border limits bottom  //
                    over(x[0], y[0], len);   
                break;

            case 72:                        // Up arrow // 
                move(x, y, &l, c, len);
                gotoxy(x[0], --y[0]);
                printf("%c", 30);

                if (y[0] == 0)
                    over(x[0], y[0], len);
                break;

            case 75:                    // left arrow // 
                move(x, y, &l, c, len);
                gotoxy(x[0] = x[0] - 2, y[0]);
                printf("%c", 17);

                if (x[0] == 1)
                    over(x[0], y[0], len);
                break;

            case 77:                   // right arrow // 
                move(x, y, &l, c, len);
                gotoxy(x[0] = x[0] + 2, y[0]);
                printf("%c", 16);

                if (x[0] == 119)
                    over(x[0], y[0], len);
                break;

            default:
                break;
            }
            for (int i = 4; i < len; i++)
            {
                if (x[0] == x[i] && y[0] == y[i])
                    over(x[0], y[0], len);
            }
        } while (x[0] != px || y[0] != py);

        gotoxy(x[len], y[len]);
        printf("o");
        len++;

        x = (int *)realloc(x, sizeof(int) * (len + 1));
        y = (int *)realloc(y, sizeof(int) * (len + 1));

        do          // Spawn random baits // 
        {
            py = (rand() % 28) + 1;
            px = ((rand() % 58) * 2) + 3;
        } while (check(px, py, x, y, len));

        gotoxy(px, py);
        printf("%c", 15);
    }
    return 0;
}

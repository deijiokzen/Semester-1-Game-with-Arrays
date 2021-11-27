#include<stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include<bits.h>
#include<conio.h>

//char CASTER[20];
int CAVAREA;
//int moldren=10;
struct reportcard{
	char name[20];
	int points;
};

void textcolor (int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

int game11(int pos_x, int pos_y);
int game22(int pos_x, int pos_y);
int game33(int pos_x, int pos_y);
int game44(int pos_x, int pos_y);
int game55(int pos_x, int pos_y);
int game66(int pos_x, int pos_y);
int game77(int pos_x, int pos_y);
int game88(int pos_x, int pos_y);
int game99(int pos_x, int pos_y);
int game102(int pos_x, int pos_y);
void visual(int wrong, int choice);
int gameboardbasic(int pos_x, int pos_y);
void Door();
void ending ()
{
system("cls");
	printf("After a long and arduous journey you finally find a glimpse of purple light in the distance...");
	getch();
	printf("Is this it...have you finally made it out!?");
	getch();
	Door();
}
int k; // global variable for number of turns of computer in a round
void print_comp(char board[9])
{
	system("cls");
	printf("\n %c | %c | %c \n___|___|___\n %c | %c | %c \n___|___|___\n %c | %c | %c \n   |   |", board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);
	k++;
	return;
}

void tictactoe_point(int *points, int win, int lose, int tie)
{
	if(win+lose+tie==3)
	{
		if(win==1) //if only one round is won
		{
			printf("\nYou barely unlocked the door in time...");
			*points += 100;
			return;
		}
		if(win==2) //if two rounds are won
		{
			printf("\nYou unlocked the door but after some struggle...");
			*points += 200;
			return;
		}
		if(win==3) //if all three rounds are won
		{
			printf("\nYou unlocked the door with ease!");
			*points += 300;
			return;
		}
		//game over case
		if(win==0)
		{
			printf("Game Over"); // REPLACE THIS WITH GAME OVER FUNCTION PLEASE!!!
			return;
		}
	}
}

void computer(char board[9], char comp, char player, int pos, int level);
void TicTacToe(int *points, int level)
{
	int win=0, lose=0, tie=0, noSpace=0, i, j;
	char player, comp;
	
	//character selection
	do{
	printf("Please select 'x' or 'o' [x/o]: ");
	scanf("%c", &player);
	fflush(stdin);
	if(player!='x' && player!='o')
		{
			printf("Error! ");
		}
	}while(player != 'x' && player != 'o');
	if(player == 'x')
		comp = 'o';
	else
		comp = 'x';
	
	printf("   |   |   \n___|___|___\n   |   |   \n___|___|___\n   |   |   \n   |   |");
	
	char board[9]; //setting the playing board
	next_round:
	level++; //if three rounds are NOT complete
	for(i=0;i<9;i++)
	{
		board[i] = ' ';  // positions in the 3x3 matrix, elements are empty(spaces) at the beginning
	}
	k=0; //this is to record the number of turns by the computer
	while(win+tie+lose<3) //the whole working is in this loop
	{
		int pos=0;
		
		//asking player for a move
		printf("\nChoose a number from 1-9 to place your sign on the board: ");
		scanf("%d", &pos);
		getchar();
		if(pos > 9 || pos < 1)
		{
			printf("\nError! ");
			continue;
		}
		if(board[pos-1]!=' ')
		{
			printf("\nError! Position already filled.\n");
			continue;
		}
		board[pos-1]=player;
		
		//printing the move
		system("cls");
		printf(" %c | %c | %c \n___|___|___\n %c | %c | %c \n___|___|___\n %c | %c | %c \n   |   |", board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);
		
		//now checking if player won
		for(i=0;i<3;i++) //checking horizontal
		{
			if(board[i]==player && board[i+3]==player && board[i+6]==player)
			{
				win++;
				printf("\nYou win this round.\n");
				if((win+lose+tie)!=3)
				goto next_round; // going to next_round resets the board
				else
				tictactoe_point(points, win, lose, tie);
				return;
			}
		}
		for(i=0;i<7;i+=3) //checking vertical
		{
			if(board[i]==player && board[i+1]==player && board[i+2]==player)
			{
				win++;
				printf("\nYou win this round.\n");
				if(win+lose+tie<3)
				goto next_round;
				else
				tictactoe_point(points, win, lose, tie);
			return;
			}
		}
		if((board[0]==player && board[4]==player && board[8]==player) || (board[2]==player && board[4]==player && board[6]==player)) //checking diagonal
		{
			win++;
			printf("\nYou win this round.\n");
			if(win+lose+tie<3)
			goto next_round;
			else
			tictactoe_point(points, win, lose, tie);
			return;
		}
	
		//checking if it's a tie
		for(i=0;i<9;i++)
		{
			if(board[i]==' ')
			{
				noSpace++;
			}
		}
		if(noSpace==0)
		{
			tie++;
			printf("\nThis round is a Tie\n");
			*points += 50;
			if(win+lose+tie<3)
			goto next_round;
			else
			tictactoe_point(points, win, lose, tie);
			return;
		}
		else
			noSpace=0;
	
		//computer's move (calling function)	
		computer(board, comp, player, pos, level);
	
		//now checking if computer won
		for(i=0;i<3;i++) //checking horizontal
		{
			if(board[i]==comp && board[i+3]==comp && board[i+6]==comp)
			{
				lose++;
				printf("\nYou lose this round.\n");
				if(win+lose+tie<3)
				goto next_round;
				else
				tictactoe_point(points, win, lose, tie);
			return;
			}
		}
		for(i=0;i<7;i+=3) //checking vertical
		{
			if(board[i]==comp && board[i+1]==comp && board[i+2]==comp)
			{
				lose++;
				printf("\nYou lose this round.\n");
				if(win+lose+tie<3)
				goto next_round;
				else
				tictactoe_point(points, win, lose, tie);
			return;
			}
		}
		if((board[0]==comp && board[4]==comp && board[8]==comp) || (board[2]==comp && board[4]==comp && board[6]==comp)) //checking diagonal
		{
			lose++;
			printf("\nYou lose this round.\n");
			if(win+lose+tie<3)
			goto next_round;
			else
			tictactoe_point(points, win, lose, tie);
			return;
		}
	}
}

void computer(char board[9], char comp, char player, int pos, int level)
{
	int i,j, arr[4] = {0, 2, 6, 8};
		// Computer will now do it's move
		if(level == 1)
		{
			do{ //if player doesn't have any two consecutive slots filled, computer will randomely select a slot
				srand(time(0));
				pos = rand()%9+1;
				if(board[pos-1]==' ')
				{
					board[pos-1]=comp;
					print_comp(board);
					return;
				}
			}while(board[pos-1]!=' ');
		}
		if(level == 5)
		{
			if(board[4]==' ') //first move will always be in the centre slot
			{
				if(k==0)
				{
					board[4] = comp;
					print_comp(board);
					return;
				}
			}
		}
		if(level ==6)
		{
			if(k==0) //first move will always be in the centre slot if it's empty
			{
				if(board[4]==' ')
				{
					board[4] = comp;
					print_comp(board);
					return;
				}
				if(board[4] != ' ') //otherwise it will be a random corner slot
				{
					srand(time(0));
					i = rand()%4;
					board[arr[i]] = comp;
					print_comp(board);
					return;
				}
			}
		}
		if(level >=4)
		{
			for(i=0,j=0;i<7;i+=3,j++) //checking if there's a chance to win in vertical and horizontal direction
			{
				if(board[i]==comp && board[i+1]==comp && board[i+2]==' ')
				{
					board[i+2] = comp;
					print_comp(board);
					return;
				}
				else if(board[i+2]==comp && board[i+1]==comp && board[i]==' ')
				{
					board[i] = comp;
					print_comp(board);
					return;
				}
				if(board[i]==comp && board[i+2]==comp && board[i+1]==' ')
				{
					board[i+1] = comp;
					print_comp(board);
					return;
				}
				else if(board[j]==comp && board[j+3]==comp && board[j+6]==' ')
				{
					board[j+6] = comp;
					print_comp(board);
					return;
				}
				else if(board[j+6]==comp && board[j+3]==comp && board[j]==' ')
				{
					board[j] = comp;
					print_comp(board);
					return;
				}
				else if(board[j]==comp && board[j+6]==comp && board[j+3]==' ')
				{
					board[j+3] = comp;
					print_comp(board);
					return;
				}
			}
			i=0	; j=0;
			while(i<9) //checking for a chance to win diagonally
			{
				if(board[i]==comp && board[4]==comp && board[8-i]==' ')
				{
					board[8-i] = comp;
					print_comp(board);
					return;
				}
				if(board[i]==comp && board[8-i]==comp && board[4]==' ')
				{
					board[4] = comp;
					print_comp(board);
					return;
				}
				if(j==0)
				{
					i+=2;
					j++;
				}
				else if(j==1)
				{
					i+=4;
					j--;
				}
			}
		}
		// if there isn't a way for computer to win it will try and stop the player from winning
		for(i=0,j=0;i<7;i+=3,j++) //stopping player from winning if they have filled two consecutive slots on the board except diagonal
		{
			if(board[i]==player && board[i+1]==player && board[i+2]==' ')
			{
				board[i+2] = comp;
				print_comp(board);
				return;
			}
			if(board[i+2]==player && board[i+1]==player && board[i]==' ')
			{
				board[i] = comp;
				print_comp(board);
				return;
			}
			if(level >=3)
			{
				if(board[i]==player && board[i+2]==player && board[i+1]==' ')
				{
					board[i+1] = comp;
					print_comp(board);
					return;
				}
			}
			if(board[j]==player && board[j+3]==player && board[j+6]==' ')
			{
				board[j+6] = comp;
				print_comp(board);
				return;
			}
			if(board[j+6]==player && board[j+3]==player && board[j]==' ')
			{
				board[j] = comp;
				print_comp(board);
				return;
			}
			if(level >=3)
			{
				if(board[j]==player && board[j+6]==player && board[j+3]==' ')
				{
					board[j+3] = comp;
					print_comp(board);
					return;
				}
			}
		}
		i=0; j=0;
		while(i<9) //stopping player from winning if they filled two consecutive slots on the board DIAGONALLY
		{
			if(board[i]==player && board[4]==player && board[8-i]==' ')
			{
				board[8-i] = comp;
				print_comp(board);
				return;
			}
			if(board[i]==player && board[8-i]==player && board[4]==' ')
			{
				board[4] = comp;
				print_comp(board);
				return;
			}
			if(j==0)
			{
				i+=2;
				j++;
			}
			else if(j==1)
			{
				i+=4;
				j--;
			}
		}
		do{ //if player isn't winning any of the above ways, computer will randomely select a slot
			srand(time(0));
			pos = rand()%9+1;
			if(board[pos-1]==' ')
			{
				board[pos-1]=comp;
				print_comp(board);
				return;
			}
		}while(board[pos-1]!=' ');
}



int check12(char *ch,char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	*ch='.';
	*x=*pos_x;
	*y=*pos_y;
if(m=='p')
{

if((*y>51))
	{
		game102(25,28);
	}
	if((*x>=0 && *x<12) && (*y>=28 && *y<43))
	{
		game102(54,35);
	}
	if((*x>=48 && *x<60) && (*y>=28 && *y<43))
	{
	game102(6,35);

	}
	if((*x>=23 && *x<31) && (*y>=23 && *y<=31))
		game102(57,54);
	}
	

if (m=='r')
game102(57,54);
if(m=='l')
{
	game102(*x,*y);
}
if(*COUNT==10)
game102(*pos_x,*pos_y);

else{
	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' '&& a[*pos_x][59]!='X') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			else if( a[*pos_x][*pos_y-1]=='O'   ){
			*ch=' ';
			*pos_y=*pos_y-1;
			
			return 1;}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T'  ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' '&& a[0][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		if( a[*pos_x+1][*pos_y]=='O')
			{*ch=' ';
				*pos_x=*pos_x+1;
			return 1;
			}
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ' && a[59][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		if( a[*pos_x-1][*pos_y]=='O')
			{*ch=' ';
			*pos_x=*pos_x-1;
			return 1;
			}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		if(a[*pos_x][*pos_y+1]=='O')
		{
			*ch=' ';
			*pos_y=*pos_y+1;
			return 1;
		}
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' && a[*pos_x][0]!='X' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game12(char ch, char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==1 && pos_y==0)//FINAL DESTINATION OF THE PLAYER A.K.A T'S POSITION
return 1;
textcolor(14);
system("cls");
printf("Remember!Press 'l' to randomize the 'Os'.\nPress 'p' to teleport.\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{textcolor(8);
 		if((j>51)||((i>=23 && i<31) && (j>=23 && j<=31)))
 		textcolor(13);
 		if(((i>=0 && i<12) && (j>=28 && j<43))||((i>=48 && i<60) && (j>=28 && j<43)))
 		textcolor(9);
 		if(a[i][j]=='P' ||a[i][j]=='O' )
 	    textcolor(12);
 	    if(a[i][j]=='T')
 	    textcolor(10);

 printf("%c ", a[i][j]);
	 }
printf("\n");
}



m=getch();
if (check12(&ch,m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	a[x][y]=ch;//MAKING NEW POSITION 'P' AND REPLACING THE PREVIOUS POSITION WITH THE CHARACTER '.' SO IT LOOKS LIKE IT'S MOVING
	game12(ch,a, pos_x, pos_y, x, y, COUNT);
}
else {

	game12(ch,a, pos_x, pos_y, x, y, COUNT);}
}
game102(int pos_x, int pos_y){
	/*stupid bs extra variables declared*/
 int COUNT=0, k=0,i,s,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char ch,a[60][60];
for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
 for (i=0; i<60;i++)
 {
 	for (j=i;j<60;j++)
 	{
    a[i][j]=' ';
	 }
 }
  for (i=0; i<60;i++)
{
	for(j=12;j<50;j++)
	{
		 a[i][j]=' ';
	}
}
 for (i=23; i<35;i++)
 {
 	for (j=i;j<31;j++)
 	{
    a[i][j]='.';
	 }
 }
  for (i=0; i<23;i++)
 {
 	for (j=25;j<35;j++)
 	{
s=((rand() % 7 ) + 1);
      if(s>5)
        a[i][j]= ' '; 
	else 
	a[i][j]='O';
	 }
 }
 for (i=0; i<12;i++)
 {
 	for (j=28;j<43;j++)
 	{
    a[i][j]='.';
	 }
 }
 for (i=48; i<60;i++)
 {
 	for (j=28;j<43;j++)
 	{
    a[i][j]='.';
	 }
 }
  for (i=58; i<60;i++)
 {
 	for (j=0;j<28;j++)
 	{
    a[i][j]='.';
	 }
 }
 	a[1][0]='T';
a[pos_x][pos_y]='P';
 
 if(game12(ch,a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
 	ending();
 }
}
void hangerman2()
{	int p;
char inp[10];
char org[10];
char x;
	srand(time(NULL));
	int choice = ((rand() % 4 ) + 1);
	if (choice==1)
	{
	p=7;
	org[0] = 'b';		//Word stored in org
	org[1] = 'r';
	org[2] = 'i';
	org[3] = 'd';
	org[4] = 'g';
	org[5] = 'e';
	org[6] = 's';
	}
	if (choice==2)
	{
	p=5;
	org[0] = 'f';		//Word stored in org
	org[1] = 'o';
	org[2] = 'r';
	org[3] = 'c';
	org[4] = 'e';
}
if (choice==3)
	{
	p=4;
    org[0] = 'h';		//Word stored in org
	org[1] = 'e';
	org[2] = 'l';
	org[3] = 'l';
}
if (choice==4)
	{
	p=6;
	org[0] = 'g';		//Word stored in org
	org[1] = 'o';
	org[2] = 'v';
	org[3] = 'e';
	org[4] = 'r';
	org[5] = 'n';
}
	int i, right, wrong=5, win=0, inc=0;
	
	visual(wrong, choice);		//Will show initial visual

	
	for(i=0 ; i<p ; i++)
	{
		inp[i] = '_';
		printf("%c ", inp[i]);		//Transforming no of letters in from of _
	}
	
	while(wrong!=0)		//For 5 tries only
	{
		right=0;
		printf("\nEnter a alphabet\n");
		fflush(stdin);
		scanf("%c", &x);
		for(i=0 ; i<p ; i++)		//To check if guessed word is in the org array
		{
			if(org[i]==x)
			{
				inp[i]=x;
				right=1;
			}
			else
			{
				continue;		//If alphabet is more than one places
			}
		}
		system("cls");
		visual(wrong, choice);
		for(i=0 ; i<p ; i++)
		{
			printf("%c ", inp[i]);		//Will show you the array with right guessed alphabet
		}
		if(right==0)
		{
			wrong--;
			visual(wrong, choice);
			printf("\nWrong Guess\nRemaining tries are %d\nPress any key to start guessing again", wrong);
			getch();
			system("cls");
			visual(wrong, choice);
		for(i=0 ; i<p ; i++)
		{
			printf("%c ", inp[i]);
		}
		}
		else
		{
			for(i=inc ; i<p ; i++)
			{
				if(inp[i]==org[i])
				{
					win++;
				}
			}
			inc=win;		//OK this is a interesting part cuz, first I was incrementing the loop by adding 1 in inc but if the alph. has
			if(win==p)		//more than one similiar alphabet, so it was not incrementing thats why, had to equate this with win
			{
				printf("\nWinner Winner Chicken Dinner");
				system("cls");
				game99(0,0);
				break;
			}
		}
	}
	if (wrong <=0)		//For Losers only
	{
	
		getch();
	    main();
	}
}


int check9(char *ch,char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	*ch='.';
	*x=*pos_x;
	*y=*pos_y;
if(m=='p')
{
	if((*x>=23 && *x<35) && (*y>=12 && *y<31))
	{
		game99(6,35);
	}
	if((*x>=0 && *x<12) && (*y>=28 && *y<43))
	{
		game99(29,21);
	}
	if((*x>=48 && *x<60) && (*y>=28 && *y<43))
	{
		game99(5,54);
	}
	if((*x>=0 && *x<17) && (*y>=49 && *y<=59))
	{
		game99(54,35);
	}
	
}
if(m=='r')
{
	game99(*x,*y);
}
if(*COUNT==10)
game99(*pos_x,*pos_y);

else{
	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' '&& a[*pos_x][59]!='X') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			else if( a[*pos_x][*pos_y-1]=='O'   ){
			*ch=' ';
			*pos_y=*pos_y-1;
			
			return 1;}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T'  ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' '&& a[0][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		if( a[*pos_x+1][*pos_y]=='O')
			{*ch=' ';
				*pos_x=*pos_x+1;
			return 1;
			}
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ' && a[59][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		if( a[*pos_x-1][*pos_y]=='O')
			{*ch=' ';
			*pos_x=*pos_x-1;
			return 1;
			}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		if(a[*pos_x][*pos_y+1]=='O')
		{
			*ch=' ';
			*pos_y=*pos_y+1;
			return 1;
		}
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' && a[*pos_x][0]!='X' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game9(char ch, char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==35 && pos_y==54)//FINAL DESTINATION OF THE PLAYER A.K.A T'S POSITION
return 1;

system("cls");
textcolor(15);
printf("Remember!If the platforms are of the same color, press 'p' to teleport between them.\nHowever you may not teleport if the ground is dark grey.\n");
//printf("'O' IS WATER THAT'S SHALLOW, TAKE A LITTLE DIP WON'TCHA?\nDon't go peddling in the 'X' though, that has some gnarly waves, you'd be swept away!\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{textcolor(8);
 		if(((i>=23 && i<35) && (j>=12 && j<31))||((i>=0 && i<12) && (j>=28 && j<43)))
 		textcolor(13);
 		if(((i>=48 && i<60) && (j>=28 && j<43)) ||((i>=0 && i<13) && (j>=49 && j<=59)) )
 		textcolor(12);
 		if(a[i][j]=='P')
 		textcolor(12);
 		if(a[i][j]=='T')
 		textcolor(10);


 printf("%c ", a[i][j]);
	 }
printf("\n");
}

m=getch();
if (check9(&ch,m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	a[x][y]=ch;//MAKING NEW POSITION 'P' AND REPLACING THE PREVIOUS POSITION WITH THE CHARACTER '.' SO IT LOOKS LIKE IT'S MOVING
	game9(ch,a, pos_x, pos_y, x, y, COUNT);
}
else {

	game9(ch,a, pos_x, pos_y, x, y, COUNT);}
}
game99(int pos_x, int pos_y){
	/*stupid bs extra variables declared*/
 int COUNT=0, k=0,i,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char ch,a[60][60];
for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		
 		
    a[i][j]='.';
	 }
 }
 for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
  for (i=0; i<60;i++)
{
	for(j=12;j<50;j++)
	{
		 a[i][j]=' ';
	}
}
 for (i=23; i<35;i++)
 {
 	for (j=12;j<31;j++)
 	{
    a[i][j]='.';
	 }
 }
 for (i=0; i<12;i++)
 {
 	for (j=28;j<43;j++)
 	{
    a[i][j]='.';
	 }
 }
 for (i=48; i<60;i++)
 {
 	for (j=28;j<43;j++)
 	{
    a[i][j]='.';
	 }
 }

 	a[35][54]='T';
a[pos_x][pos_y]='P';
 
 if(game9(ch,a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	game102(57,54);
 	
 }
}


int checkbasic(char m, char a[30][30], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	
		
*x=*pos_x;
	*y=*pos_y;	
if(m=='p')
{

if((*y<=5))
	{
		gameboardbasic(10,28);
	}
	if(*y>20)
	{
	gameboardbasic(10,3);
	}
}
if(m=='r')
{
	gameboardbasic(0,0);
}
//if(*COUNT==30)
//gameboard(*pos_x,*pos_y);
//
else
{

	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][29]!=' ') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=29;
				return 1;
			}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T' || a[*pos_x][*pos_y-1]=='O'   ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>29 && a[0][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[29][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=29;
			return 1;
		}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>29 && a[*pos_x][0]!=' ' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}

void skeleton()
{
FILE *fp=fopen("Skeleton 2.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
textcolor(12);	printf("%c", ch);
	
}
}
getch();
system("cls");
hangerman2();
}
int gamebasic(char a[30][30], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==29 && pos_y==28)
return 1;

system("cls");
textcolor(14);
printf("The trick is really easy to grasp, if the platforms are of the same color, press 'p' to teleport between them.\nHowever you may not teleport if the ground is dark grey.\n");
//printf("Wall teleportation hallway, you can't sift through the holes on the floor,\nTry using the walls to make your trip to the T shorter.\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;
textcolor(3);
for (i=0; i<30;i++)
 {
 	for (j=0;j<30;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		if(a[i][j]=='T')
 		textcolor(10);
 printf("%c ", a[i][j]);
	 }
printf("\n");
}

m=getch();
if (checkbasic (m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{ a[0][0]='.';
	a[pos_x][pos_y]='P';
	
	
	a[x][y]='.';
	gamebasic(a, pos_x, pos_y, x, y, COUNT);
}
else {

	gamebasic(a, pos_x, pos_y, x, y, COUNT);}
}
gameboardbasic(int pos_x, int pos_y){
 int COUNT=0,i,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char a[30][30];
for (i=0; i<30;i++)
 {
 	for (j=0;j<30;j++)
 	{
    a[i][j]='.';
	 }
 }
 
 for (i=0;i<30;i++)
 {
 	for (j=5;j<20;j++)
 	{
 		a[i][j]=' ';
	 }
 }

 	a[29][28]='T';

a[pos_x][pos_y]='P';
 
 if(gamebasic(a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
skeleton();
getch();

}
}




void girl33()
{
	FILE *fp=fopen("Young child 3.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
textcolor(13);	printf("%c", ch);
	
}
}
getch();
system("cls");
int points = 0;
TicTacToe(&points, 3);
CAVAREA+=points;
system("cls");
printf("%d points received\n", points);
textcolor(12);
printf("Hmm hmm, would you look at that. She vanished, but she left her doll behind...I'll keep it with me...in case we ever meet again...");
getch();
system("cls");
if(CAVAREA>300)
{

printf("The girl, grateful for entertaining her thus far, decides to teach you one of her many tricks.");
system("cls");
gameboardbasic(0,0);
}

else
{
	printf("To this day you wander the halls of the bridges castle, desperate to find your way out, but you struggle and end up just wear you came from.\nSlowly but surely you lose your mind.\n");
	getch();
	printf("If only you had a friend to help you....");
	getch();
	system("cls");
	printf("Player received Ending:Despair, with points %d.\nPress any key to proceed.", CAVAREA);
	system("cls");
	main();
}
}



void girl3()
{textcolor(14);

	system("cls");
	printf("Wait....what's this!?'");
	getch();
	system("cls");
	girl33();
	
}

int check8(char *ch,char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	*ch='.';
	*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game88(0,0);
}
if(m=='l')
{
	game88(*x,*y);
}
if(*COUNT==10)
game88(*pos_x,*pos_y);

else{
	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' '&& a[*pos_x][59]!='X') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			else if( a[*pos_x][*pos_y-1]=='O'   ){
			*ch=' ';
			*pos_y=*pos_y-1;
			
			return 1;}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T'  ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' '&& a[0][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		if( a[*pos_x+1][*pos_y]=='O')
			{*ch=' ';
				*pos_x=*pos_x+1;
			return 1;
			}
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ' && a[59][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		if( a[*pos_x-1][*pos_y]=='O')
			{*ch=' ';
			*pos_x=*pos_x-1;
			return 1;
			}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		if(a[*pos_x][*pos_y+1]=='O')
		{
			*ch=' ';
			*pos_y=*pos_y+1;
			return 1;
		}
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' && a[*pos_x][0]!='X' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game8(char ch, char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
if (pos_x==35 && pos_y==54)//FINAL DESTINATION OF THE PLAYER A.K.A T'S POSITION
return 1;
textcolor(14);
 
system("cls");
printf("Use 'l' yet again to randomize the 'O's so you can open up your path to T.\n");
char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(14);

 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='O')
     	textcolor(12);
     	
     	if(a[i][j]=='.')
textcolor(9);     	
 printf("%c ", a[i][j]);
 if(a[i][j]!='P')
 textcolor(10);
	 }
printf("\n");
}

m=getch();
if (check8(&ch,m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	a[x][y]=ch;
	game8(ch,a, pos_x, pos_y, x, y, COUNT);
}
else {

	game8(ch,a, pos_x, pos_y, x, y, COUNT);}
}
game88(int pos_x, int pos_y){
 int COUNT=0, k=0,i,j, x, y;
 char ch,a[60][60];
 
 
 srand(time(NULL));

 

 
 
 for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
int radius=25, dist;
for ( i = 0; i <= 2 * radius; i++) { 
  
    for ( j = 0; j <= 2 * radius; j++) { 
      dist = sqrt((i - radius) * (i - radius) +  
                  (j - radius) * (j - radius)); 
  
      if (dist > radius - 2.5 && dist < radius + 2.5)  
a[i][j]= '.';
      else 
        a[i][j]= 'O';     
    } 
  
  }
  int s;
   radius=20;
for ( i = 0; i <= 2 * radius; i++) { 
  
    for ( j = 0; j <= 2 * radius; j++) { 
      dist = sqrt((i - radius) * (i - radius) +  
                  (j - radius) * (j - radius)); 
  
      if (dist > radius - 0.25 && dist < radius + 0.25)  
a[i][j]= '.';
      else 
      {
	  s=((rand() % 7 ) + 1);
      if(s==7)
        a[i][j]= ' '; 
	else 
	a[i][j]='O';
}
    } 
  
  } 
for (i=3; i<53;i++)
 {
 	for (j=3;j<35;j++)
 	{
    a[i][j]=' ';
	 }
 }
 for (i=25; i<35;i++)
 {
 	for (j=35;j<60;j++)
 	{
    a[i][j]='X';
	 }
 }
 
 for (i=0; i<34;i++)
 {
 	for (j=58;j<60;j++)
 	{
    a[i][j]='X';
	 }
 }
 for (i=56; i<60;i++)
 {
 	for (j=0;j<20;j++)
 	{
    a[i][j]='X';
	 }
 }
  for (i=37; i<60;i++)
 {
 	for (j=35;j<60;j++)
 	{
    a[i][j]=' ';
	 }
 }
 for (i=4; i<20;i++)
 {
 	for (j=0;j<5;j++)
 	{
    a[i][j]=' ';
	 }
 }
  


 
 /*INITIAL POSITIONS OF 'T' AND 'P'.*/
 	a[35][54]='T';
a[pos_x][pos_y]='P';
 
 if(game8(ch,a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
 	girl3();
 }
}


void init7()
{system("cls");
textcolor(14);
 
	printf("Time to merge some concepts, let's see if you've been keeping up.");
	getch();
	game88(0,0);
	
}

int check7(char *ch,char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	*ch='.';
	*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game77(0,0);
}
//if(*COUNT==30)
//gameboard(*pos_x,*pos_y);

else{
//	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' ') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			else if( a[*pos_x][*pos_y-1]=='O'   ){
			*ch=' ';
			*pos_y=*pos_y-1;
			
			return 1;}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T'  ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		if( a[*pos_x+1][*pos_y]=='O')
			{*ch=' ';
				*pos_x=*pos_x+1;
			return 1;
			}
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		if( a[*pos_x-1][*pos_y]=='O')
			{*ch=' ';
			*pos_x=*pos_x-1;
			return 1;
			}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		if(a[*pos_x][*pos_y+1]=='O')
		{
			*ch=' ';
			*pos_y=*pos_y+1;
			return 1;
		}
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game7(char ch, char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
if (pos_x==35 && pos_y==54)//FINAL DESTINATION OF THE PLAYER A.K.A T'S POSITION
return 1;

system("cls");

char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='O')
     	textcolor(12);
     	
     	if(a[i][j]=='.')
     	textcolor(12);
     	
 printf("%c ", a[i][j]);
 if(a[i][j]!='P')
 textcolor(10);
	 }
printf("\n");
}

m=getch();
if (check7(&ch,m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	a[x][y]=ch;//MAKING NEW POSITION 'P' AND REPLACING THE PREVIOUS POSITION WITH THE CHARACTER '.' SO IT LOOKS LIKE IT'S MOVING
	game7(ch,a, pos_x, pos_y, x, y, COUNT);
}
else {

	game7(ch,a, pos_x, pos_y, x, y, COUNT);}
}
game77(int pos_x, int pos_y){
	/*stupid bs extra variables declared*/
 int COUNT=0, k=0,i,j, x, y;
 char ch,a[60][60];
 for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
 for(i=5;i<60;i++)
	{
		for(j=5;j!=i;j++)
		{
			a[i][j]='O';
		}
	}
	
	 for(i=7;i<45;i++)
	{
		for(j=0;j!=i+6;j++)
		{
			a[j][i]='X';
		}
	}
	
for(i=25; i<50; i++)
    {
        
        for(j=25; j<=(50-i); j++)
        {
            printf(" ");
        }

        
        for(j=i; j<=50; j++)
        {
            a[i][j]=' ';
        }

    }

   
    for(i=0; i<=50; i++)
    {
        
        for(j=1; j<i; j++)
        {
            a[i][j]=' ';
        }

      
        for(j=1; j<=i; j++)
        {
            a[i][j]=' ';
        }
    }
    for (i=2; i<55;i++)
 {
 	for (j=0;j<1;j++)
 	{
    a[i][j]=' ';
	 }
 }
    for (i=0; i<60;i++)
 {
 	for (j=58;j<59;j++)
 	{
    a[i][j]='X';
	 }
 }

  /*INITIAL POSITIONS OF 'T' AND 'P'.*/
 	a[35][54]='T';
a[pos_x][pos_y]='P';
 
 if(game7(ch,a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
 	init7();
 }
}

void init6()
{
	textcolor(14);
 
	printf("M-Moving on.........god you're good at this, huh.\nLet's try to make it a little challenging now.");
	getch();
	game77(0,0);
	
	
}

void Hang1()
{textcolor(15);
		FILE *fp=fopen("Hangman 1.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{

	printf("%c", ch);
	
}
}

}

void Hang2()
{
		FILE *fp=fopen("Hangman 2.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
	printf("%c", ch);
	
}
}
}
void Hang3()
{
		FILE *fp=fopen("Hangman 3.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{

	printf("%c", ch);
	
}
}
}
void Hang4()
{
		FILE *fp=fopen("Hangman 4.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{

	printf("%c", ch);
	
}
}
}
void Hang5()
{
		FILE *fp=fopen("Hangman 5.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{

	printf("%c", ch);
	
}
}
}
void Hang6()
{
		FILE *fp=fopen("Hangman 6.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
	textcolor(12);

	printf("%c", ch);
	
}
}
}
int check6(char *ch,char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	*ch='.';
	*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game66(0,0);
}
//if(*COUNT==30)
//gameboard(*pos_x,*pos_y);

else{
//	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' '&& a[*pos_x][59]!='X') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			else if( a[*pos_x][*pos_y-1]=='O'   ){
			*ch=' ';
			*pos_y=*pos_y-1;
			
			return 1;}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T'  ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' '&& a[0][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		if( a[*pos_x+1][*pos_y]=='O')
			{*ch=' ';
				*pos_x=*pos_x+1;
			return 1;
			}
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ' && a[59][*pos_y]!='X')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		if( a[*pos_x-1][*pos_y]=='O')
			{*ch=' ';
			*pos_x=*pos_x-1;
			return 1;
			}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		if(a[*pos_x][*pos_y+1]=='O')
		{
			*ch=' ';
			*pos_y=*pos_y+1;
			return 1;
		}
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' && a[*pos_x][0]!='X' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game6(char ch, char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==35 && pos_y==54)//FINAL DESTINATION OF THE PLAYER A.K.A T'S POSITION
return 1;

system("cls");
textcolor(14);

printf("'O' IS WATER THAT'S SHALLOW, TAKE A LITTLE DIP WON'TCHA?\nDon't go peddling in the 'X' though, that has some gnarly waves, you'd be swept away!\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='O')
     	textcolor(12);
     	
     	if(a[i][j]=='.')
     	textcolor(12);
     	
 printf("%c ", a[i][j]);
 if(a[i][j]!='P')
 textcolor(10);
	 }
printf("\n");
}

m=getch();
if (check6(&ch,m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	a[x][y]=ch;//MAKING NEW POSITION 'P' AND REPLACING THE PREVIOUS POSITION WITH THE CHARACTER '.' SO IT LOOKS LIKE IT'S MOVING
	game6(ch,a, pos_x, pos_y, x, y, COUNT);
}
else {

	game6(ch,a, pos_x, pos_y, x, y, COUNT);}
}
game66(int pos_x, int pos_y){
	/*stupid bs extra variables declared*/
 int COUNT=0, k=0,i,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char ch,a[60][60];
 
for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
 for(i=5;i<60;i++)
	{
		for(j=5;j!=i;j++)
		{
			a[i][j]='O';
		}
	}
	
	 for(i=7;i<45;i++)
	{
		for(j=0;j!=i+6;j++)
		{
			a[j][i]='X';
		}
	}

 
 /*INITIAL POSITIONS OF 'T' AND 'P'.*/
 	a[35][54]='T';
a[pos_x][pos_y]='P';
 
 if(game6(ch,a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
	system("cls");
 	init6();
return 0; }
}
void init5()
{
	system("cls");
	printf("More concepts, ughh...I know, but hey, it keeps everything interesting, don'tcha think?\nJust remember, can't step on 'X', but you can step on 'O',\n but it get's interesting when you actually try it.");
	getch();
	system("cls");
	game66(0,0);
}

void girl22()
{
	FILE *fp=fopen("Young child 2.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
textcolor(13);	printf("%c", ch);
	
}
}
getch();
system("cls");
int points = 0;
TicTacToe(&points, 2);
CAVAREA+=points;
system("cls");
printf("%d points received\n", points);
textcolor(14);
printf("The child witch took her dolls and ran away yet again....what the hell....");
getch();
system("cls");
init5();
}


void girl2()
{textcolor(14);

	system("cls");
	printf("Wait....what's this!?'");
	getch();
	system("cls");
	girl22();
}







int check5(char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
if(m=='r')
{
	game55(0,0);
}	
	
	*x=*pos_x;
	*y=*pos_y;
if(m=='l')
{
	game55(*x,*y);
}
if(*COUNT==30)
game55(*pos_x,*pos_y);

else{
	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' ') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T'  ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		 if(a[*pos_x-1][*pos_y]=='.')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game5(char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==25 && pos_y==25)//FINAL DESTINATION OF THE PLAYER A.K.A T'S POSITION
return 1;

system("cls");
textcolor(14);

printf("Use the 'l' character to make the floor holes change, opening up your path to the 'T'!\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='.')
textcolor(11);     	
 printf("%c ", a[i][j]);
	 }
printf("\n");
}


m=getch();
if (check5(m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	a[x][y]='.';//MAKING NEW POSITION 'P' AND REPLACING THE PREVIOUS POSITION WITH THE CHARACTER '.' SO IT LOOKS LIKE IT'S MOVING
	game5(a, pos_x, pos_y, x, y, COUNT);
}
else {

	game5(a, pos_x, pos_y, x, y, COUNT);}
}
game55(int pos_x, int pos_y){
	/*stupid bs extra variables declared*/
 int COUNT=0,i,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char a[60][60];
 
 
 
 

 
 
 for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
 
 srand(time(NULL));
 for(i=0;i<=1000;i++){
 
do
  {
 	array_value15= ((rand() % 50 ) + 1);
 	array_value16= ((rand() % 50) + 1);
 	if (a[array_value16][array_value15]!=' ')
 	break;
 	}while(1);
 	a[array_value16][array_value15]=' ';
 }
 
 /*INITIAL POSITIONS OF 'T' AND 'P'.*/
  for (i=22; i<29;i++)
 {
 	for (j=22;j<29;j++)
 	{
    a[i][j]='.';
	 }
 }
 	a[25][25]='T';
a[pos_x][pos_y]='P';
 
 if(game5(a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
 girl2();
 }
}



void init4()
{textcolor(14);

	printf("Ah, you sneaked away from Uncle Death!\nGood job making it this far yo! Venture forth, but here's a few heads ups,\n You're being introduced to the concept of randomization....");
	getch();
	system("cls");
	game55(0,0);
	
}
void visual(int wrong, int choice)
{
	switch(wrong)
	{
		case 0 :
			
			system("cls");
			Hang6();
			if (choice==1)
	printf("\nThe word has 7 letters, \nHint:It's structures carrying a road. \n");
	if (choice==2)
	printf("\nThe word has 5 letters, \nHint:Strength or energy as an attribute of physical action or movement. \n");
	if (choice==3)
	printf("\nThe word has 4 letters, \nHint:a place regarded in various religions as a spiritual realm of evil and suffering, \nOften traditionally depicted as a place of perpetual fire beneath the earth where the wicked are punished after death. \n");
	if (choice==4)
	printf("\nThe word has 5 letters, \nHint:Rule. \n");
			break;
		case 1 :
		   system("cls"); Hang5();
		   if (choice==1)
	printf("\nThe word has 7 letters, \nHint:It's structures carrying a road. \n");
	if (choice==2)
	printf("\nThe word has 5 letters, \nHint:Strength or energy as an attribute of physical action or movement. \n");
	if (choice==3)
	printf("\nThe word has 4 letters, \nHint:a place regarded in various religions as a spiritual realm of evil and suffering, \nOften traditionally depicted as a place of perpetual fire beneath the earth where the wicked are punished after death. \n");
	if (choice==4)
	printf("\nThe word has 5 letters, \nHint:Rule. \n");
			break;
		case 2 :
			system("cls");Hang4();
			if (choice==1)
	printf("\nThe word has 7 letters, \nHint:It's structures carrying a road. \n");
	if (choice==2)
	printf("\nThe word has 5 letters, \nHint:Strength or energy as an attribute of physical action or movement. \n");
	if (choice==3)
	printf("\nThe word has 4 letters, \nHint:a place regarded in various religions as a spiritual realm of evil and suffering, \nOften traditionally depicted as a place of perpetual fire beneath the earth where the wicked are punished after death. \n");
	if (choice==4)
	printf("\nThe word has 5 letters, \nHint:Rule. \n");
			break;
		case 3 :
			system("cls");
			Hang3();
			if (choice==1)
	printf("\nThe word has 7 letters, \nHint:It's structures carrying a road. \n");
	if (choice==2)
	printf("\nThe word has 5 letters, \nHint:Strength or energy as an attribute of physical action or movement. \n");
	if (choice==3)
	printf("\nThe word has 4 letters, \nHint:a place regarded in various religions as a spiritual realm of evil and suffering, \nOften traditionally depicted as a place of perpetual fire beneath the earth where the wicked are punished after death. \n");
	if (choice==4)
	printf("\nThe word has 5 letters, \nHint:Rule. \n");
			break;
		case 4 :
			system("cls");
			Hang2();
			if (choice==1)
	printf("\nThe word has 7 letters, \nHint:It's structures carrying a road. \n");
	if (choice==2)
	printf("\nThe word has 5 letters, \nHint:Strength or energy as an attribute of physical action or movement. \n");
	if (choice==3)
	printf("\nThe word has 4 letters, \nHint:a place regarded in various religions as a spiritual realm of evil and suffering, \nOften traditionally depicted as a place of perpetual fire beneath the earth where the wicked are punished after death. \n");
	if (choice==4)
	printf("\nThe word has 5 letters, \nHint:Rule. \n");
			break;
		case 5 :
			Hang1();
			if (choice==1)
	printf("\nThe word has 7 letters, \nHint:It's structures carrying a road. \n");
	if (choice==2)
	printf("\nThe word has 5 letters, \nHint:Strength or energy as an attribute of physical action or movement. \n");
	if (choice==3)
	printf("\nThe word has 4 letters, \nHint:a place regarded in various religions as a spiritual realm of evil and suffering, \nOften traditionally depicted as a place of perpetual fire beneath the earth where the wicked are punished after death. \n");
	if (choice==4)
	printf("\nThe word has 5 letters, \nHint:Rule. \n");
			break;
	}
	
}

void hangerman()
{	int p;
char inp[10];
char org[10];
char x;
	srand(time(NULL));
	int choice = ((rand() % 4 ) + 1);
	if (choice==1)
	{
	p=7;
	org[0] = 'b';		//Word stored in org
	org[1] = 'r';
	org[2] = 'i';
	org[3] = 'd';
	org[4] = 'g';
	org[5] = 'e';
	org[6] = 's';
	}
	if (choice==2)
	{
	p=5;
	org[0] = 'f';		//Word stored in org
	org[1] = 'o';
	org[2] = 'r';
	org[3] = 'c';
	org[4] = 'e';
}
if (choice==3)
	{
	p=4;
    org[0] = 'h';		//Word stored in org
	org[1] = 'e';
	org[2] = 'l';
	org[3] = 'l';
}
if (choice==4)
	{
	p=6;
	org[0] = 'g';		//Word stored in org
	org[1] = 'o';
	org[2] = 'v';
	org[3] = 'e';
	org[4] = 'r';
	org[5] = 'n';
}
	int i, right, wrong=5, win=0, inc=0;
	
	visual(wrong, choice);		//Will show initial visual

	
	for(i=0 ; i<p ; i++)
	{
		inp[i] = '_';
		printf("%c ", inp[i]);		//Transforming no of letters in from of _
	}
	
	while(wrong!=0)		//For 5 tries only
	{
		right=0;
		printf("\nEnter a alphabet\n");
		fflush(stdin);
		scanf("%c", &x);
		for(i=0 ; i<p ; i++)		//To check if guessed word is in the org array
		{
			if(org[i]==x)
			{
				inp[i]=x;
				right=1;
			}
			else
			{
				continue;		//If alphabet is more than one places
			}
		}
		system("cls");
		visual(wrong, choice);
		for(i=0 ; i<p ; i++)
		{
			printf("%c ", inp[i]);		//Will show you the array with right guessed alphabet
		}
		if(right==0)
		{
			wrong--;
			visual(wrong, choice);
			printf("\nWrong Guess\nRemaining tries are %d\nPress any key to start guessing again", wrong);
			getch();
			system("cls");
			visual(wrong, choice);
		for(i=0 ; i<p ; i++)
		{
			printf("%c ", inp[i]);
		}
		}
		else
		{
			for(i=inc ; i<p ; i++)
			{
				if(inp[i]==org[i])
				{
					win++;
				}
			}
			inc=win;		//OK this is a interesting part cuz, first I was incrementing the loop by adding 1 in inc but if the alph. has
			if(win==p)		//more than one similiar alphabet, so it was not incrementing thats why, had to equate this with win
			{
				printf("\nWinner Winner Chicken Dinner");
				system("cls");
				init4();
				break;
			}
		}
	}
	if (wrong <=0)		//For Losers only
	{
	
		getch();
	    main();
	}
}

void Skeleton1()
{
	FILE *fp=fopen("Skeleton1.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
textcolor(12);
	printf("%c", ch);
	
}
}
getch();
system("cls");
hangerman();
}




int check4(char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	
	*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game44(0,0);
}
//if(*COUNT==30)
//game44(*pos_x,*pos_y);

else{
//	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' ')
			{
				*pos_y=59;
				return 1;
			}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T' ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' ')
	{
		*pos_x=0;
		return 1;
	}
		
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ')
		{
			*pos_x=59;
			return 1;
		}
		 if(a[*pos_x-1][*pos_y]=='.' || a[*pos_x-1][*pos_y]=='T')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' )
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game4(char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==35 && pos_y==54)
return 1;

system("cls");
textcolor(14);

printf("Wall teleportation hallway, you can't sift through the holes on the floor,\nTry using the walls to make your trip to the T shorter.Press 'r' if game behaves inadequately.\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the game55, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;

for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='.')
     	textcolor(13);
     	
 printf("%c ", a[i][j]);
	 }
printf("\n");
}

m=getch();
if (check4(m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{
	a[pos_x][pos_y]='P';
	
	
	a[x][y]='.';
	game4(a, pos_x, pos_y, x, y, COUNT);
}
else {

	game4(a, pos_x, pos_y, x, y, COUNT);}
}
game44(int pos_x, int pos_y){
 int COUNT=0,i,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char a[60][60];
 
 fflush(stdin);
 


 
 
 for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
  
for (i=(59-25);i<(59-23);i++)
 {
 	for (j=55;j<60;j++)
 	{
 		a[i][j]=' ';
	 }
 }
 for (i=58; i<60;i++)
 {
 	for (j=0;j<30;j++)
 	{
    a[i][j]=' ';
	 }
 }
 
 
 for (i=3;i<29;i++)
 {
 	for (j=0;j<25;j++)
 	{
 		a[i][j]=' ';
	 }
 }
 
 
 for (i=0;i<4;i++)
 {
 	for (j=5;j<6;j++)
 	{
 		a[i][j]=' ';
	 }
 }

for (i=0;i<4;i++)
 {
 	for (j=40;j<45;j++)
 	{
 		a[i][j]=' ';
	 }
 }
  for (i=11;i<13;i++)
 {
 	for (j=20;j<60;j++)
 	{
 		a[i][j]=' ';
	 }
 }
   for (i=29;i<60;i++)
 {
 	for (j=35;j<53;j++)
 	{
 		a[i][j]=' ';
	 }
 }
   for (i=29;i<50;i++)
 {
 	for (j=0;j<25;j++)
 	{
 		a[i][j]=' ';
	 }
 }
 for (i=36;i<40;i++)
 {
 	for (j=10;j<60;j++)
 	{
 		a[i][j]=' ';
	 }
 }
 for(i=30;i<45;i++)
 {
 	for(j=0;j<9;j++)
 	{
 		a[i][j]='.';
	 }
 }
 	a[35][54]='T';
a[pos_x][pos_y]='P';
 
 if(game4(a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	
 	getch();
 	Skeleton1();
 }
}
void init3()
{   system("cls");
textcolor(14);

	printf("Now let's all of the skills you've used, to the test!"); getch();
	game44(0,0);
}

int check3(char m, char a[60][60], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	
	*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game33(0,0);
}
if(*COUNT==11)
game33(0,0);

else{
	*COUNT=*COUNT+1;
	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][59]!=' ') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=59;
				return 1;
			}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T' || a[*pos_x][*pos_y-1]=='O'   ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>59 && a[0][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[59][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=59;
			return 1;
		}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>59 && a[*pos_x][0]!=' ' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game3(char a[60][60], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==57 && pos_y==57)
return 1;

system("cls");
//printf("Wall teleportation hallway, you can't sift through the holes on the floor,\nTry using the walls to make your trip to the T shorter.\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;
textcolor(14);

printf("Number of moves left %d\n", 12-COUNT);
for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='.')
textcolor(13);     	
 printf("%c ", a[i][j]);
	 }
printf("\n");
}

m=getch();
if (check3 (m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{a[0][0]='.';
	a[pos_x][pos_y]='P';
	
	
	a[x][y]='.';
	game3(a, pos_x, pos_y, x, y, COUNT);
}
else {

	game3(a, pos_x, pos_y, x, y, COUNT);}
}
int game33(int pos_x, int pos_y){
 int COUNT=0,i,j, x=0, y=0;
 char a[60][60];
 fflush(stdin);
 for (i=0; i<60;i++)
 {
 	for (j=0;j<60;j++)
 	{
    a[i][j]='.';
	 }
 }
 
 for (i=0;i<13;i++)
 {
 	for (j=7;j<25;j++)
 	{
 		a[i][j]=' ';
	 }
 }

  for (i=11;i<13;i++)
 {
 	for (j=35;j<60;j++)
 	{
 		a[i][j]=' ';
	 }
 }
   for (i=29;i<59;i++)
 {
 	for (j=35;j<53;j++)
 	{
 		a[i][j]=' ';
	 }
 }
   for (i=29;i<50;i++)
 {
 	for (j=0;j<25;j++)
 	{
 		a[i][j]=' ';
	 }
 }
 	a[57][57]='T';
a[pos_x][pos_y]='P';
 
 if(game3(a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	init3();
 	;
 }
}

void init2()
{   system("cls");
textcolor(14);

	printf("Time to make things way tougher!\nComplete the next room in just 12 moves, or you'll be sent to the start!"); getch();
	game33(0,0);
}






void girl1()
{
	FILE *fp=fopen("Young child.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
textcolor(13);	printf("%c", ch);
	
}
}
getch();
system("cls");
int points = 0;
TicTacToe(&points, 1);
CAVAREA+=points;
system("cls");
printf("%d points received\n", points);
textcolor(14);
printf("The child scurried away in a hurry....she seemed happy...");
getch();
system("cls");
init2();
}


void girl()
{textcolor(14);

	system("cls");
	printf("Ah!? What's this, a child blocks your path....");
	getch();
	system("cls");
	girl1();
}

int check2(char m, char a[30][30], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	
		
*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game11(0,0);
}
//if(*COUNT==30)
//gameboard(*pos_x,*pos_y);
//
else
{

	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][29]!=' ') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=29;
				return 1;
			}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T' || a[*pos_x][*pos_y-1]=='O'   ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>29 && a[0][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[29][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=29;
			return 1;
		}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>29 && a[*pos_x][0]!=' ' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game2(char a[30][30], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==29 && pos_y==28)
return 1;

system("cls");
//printf("Wall teleportation hallway, you can't sift through the holes on the floor,\nTry using the walls to make your trip to the T shorter.\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;
for (i=0; i<30;i++)
 {
 	for (j=0;j<30;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='.')
textcolor(3);     	
 printf("%c ", a[i][j]);
	 }
printf("\n");
}

m=getch();
if (check2 (m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{ a[0][0]='.';
	a[pos_x][pos_y]='P';
	
	
	a[x][y]='.';
	game2(a, pos_x, pos_y, x, y, COUNT);
}
else {

	game2(a, pos_x, pos_y, x, y, COUNT);}
}
game22(int pos_x, int pos_y){
 int COUNT=0,i,j,array_value1, array_value2,array_value3,array_value4,array_value5,array_value6,array_value7,array_value8,array_value9,array_value10,array_value11,array_value12,array_value13,array_value14,array_value15,array_value16, x, y;
 char a[30][30];
for (i=0; i<30;i++)
 {
 	for (j=0;j<30;j++)
 	{
    a[i][j]='.';
	 }
 }
 
 for (i=0;i<30;i++)
 {
 	for (j=5;j<28;j++)
 	{
 		a[i][j]=' ';
	 }
 }
//
//  for (i=11;i<13;i++)
// {
// 	for (j=35;j<60;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }
//   for (i=29;i<59;i++)
// {
// 	for (j=35;j<53;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }
//   for (i=29;i<50;i++)
// {
// 	for (j=0;j<25;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }

 	a[29][28]='T';

a[pos_x][pos_y]='P';
 
 if(game2(a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
girl();
}
}


void init1()
{   system("cls");
textcolor(14);


	printf("Well that seemed kinda easy!?\nHmm, how about we spice it up a little, now, whenever you see a hole in the ground,\nYou CANNOT go past it, try using the walls to make it to 'T'!"); getch();
	game22(0,0);
}


int check1(char m, char a[30][30], int *pos_x, int *pos_y, int *x, int *y,int *COUNT){
	
	
		
*x=*pos_x;
	*y=*pos_y;
if(m=='r')
{
	game11(0,0);
}
//if(*COUNT==30)
//gameboard(*pos_x,*pos_y);
//
else
{

	if (m=='a')
	{
		if (/**pos_x<10 && *pos_x>0 &&*/ /**pos_y-1>=0*/ /*&&*/  a[*pos_x][*pos_y-1]!=' ')//COMPARING WITH EMPTY SPACE SO IT CAN'T TRAVERSE IT 
		
			if(*pos_y-1<0 && a[*pos_x][29]!=' ') //TELEPORTATION POSSIBILITY EVALUATION
			{
				*pos_y=29;
				return 1;
			}
			
			else if(a[*pos_x][*pos_y-1]=='.' || a[*pos_x][*pos_y-1]=='T' || a[*pos_x][*pos_y-1]=='O'   ){
			
			*pos_y=*pos_y-1;
			
			return 1;}
	
		else
		return 0;
	}
	
	if (m=='s')
	{
	if (  a[*pos_x+1][*pos_y]!=' ')
	{
		
	if(*pos_x+1>29 && a[0][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
	{
		*pos_x=0;
		return 1;
	}
		
		if(a[*pos_x+1][*pos_y]=='.'|| a[*pos_x+1][*pos_y]=='T' || a[*pos_x+1][*pos_y]=='O')
			{	*pos_x=*pos_x+1;
			return 1;
			}
     }
		else
		return 0;
	}
		
		
		
	
	if (m=='w')
	{
		if (/**pos_x<10 &&*/  /*&& *pos_y>=0 && */   a[*pos_x-1][*pos_y]!=' ')
		{
		
		if(*pos_x-1<0 && a[29][*pos_y]!=' ')//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_x=29;
			return 1;
		}
		 if(a[*pos_x-1][*pos_y]=='.'|| a[*pos_x-1][*pos_y]=='T' || a[*pos_x-1][*pos_y]=='O')
			{*pos_x=*pos_x-1;
			return 1;
			}
		
			
}
		else
		return 0;
	}
	if (m=='d')
	{
		
		if( a[*pos_x][*pos_y+1]!=' ' )
			{
		if 	( a[*pos_x][*pos_y+1]=='.' || a[*pos_x][*pos_y+1]=='T' || a[*pos_x][*pos_y+1]=='O' )
		{
		*pos_y=*pos_y+1;
		if( *pos_y+1>29 && a[*pos_x][0]!=' ' )//TELEPORTATION POSSIBILITY EVALUATION
		{
			*pos_y=0;
		
				}	
		
		
		return 1;}		
		
			
			
			
		}
			else
		return 0;
	}
}
}


int game1(char a[30][30], int pos_x, int pos_y, int x, int y, int COUNT)
{
/*Position tester :printf("%d %d", pos_x, pos_y);
getch();*/
if (pos_x==28 && pos_y==28)
return 1;

system("cls");
//printf("Wall teleportation hallway, you can't sift through the holes on the floor,\nTry using the walls to make your trip to the T shorter.\n");
//printf("Press 'w' for moving P upwards, 's' for downwards, 'd' for rightwards, and 'a' for leftwards,\nTo move multiple spaces at once, you may type 'aaaa', or even 'wasdssdw', etc.\nThe points marked 'D' send you back to the start while the points marked 'K' do not let you move.\nPoints marked '*' kill you instantly, also, the board shuffles every 30 moves.\nTo reset the gameboard, enter 'r'.\nYour objective is to get to 'T', good luck.\n");
char m, i, j;
for (i=0; i<30;i++)
 {
 	for (j=0;j<30;j++)
 	{
 		if(a[i][j]=='P')
 		textcolor(12);
 		
 		if(a[i][j]=='T')
     	textcolor(10);
     	
     	if(a[i][j]=='.')
textcolor(3);     	
 printf("%c ", a[i][j]);
	 }
printf("\n");
}

m=getch();
if (check1 (m, a,&pos_x, &pos_y,&x,&y, &COUNT)==1)
{ a[0][0]='.';
	a[pos_x][pos_y]='P';
	
	
	a[x][y]='.';
	game1(a, pos_x, pos_y, x, y, COUNT);
}
else {

	game1(a, pos_x, pos_y, x, y, COUNT);}
}
game11(int pos_x, int pos_y){
 int COUNT=0,i,j,x, y;
 char a[30][30];
for (i=0; i<30;i++)
 {
 	for (j=0;j<30;j++)
 	{
    a[i][j]='.';
	 }
 }
 
// for (i=0;i<13;i++)
// {
// 	for (j=7;j<25;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }
//
//  for (i=11;i<13;i++)
// {
// 	for (j=35;j<60;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }
//   for (i=29;i<59;i++)
// {
// 	for (j=35;j<53;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }
//   for (i=29;i<50;i++)
// {
// 	for (j=0;j<25;j++)
// 	{
// 		a[i][j]=' ';
//	 }
// }

 	a[28][28]='T';

a[pos_x][pos_y]='P';
 
 if(game1(a, pos_x, pos_y, x, y, COUNT)==1)
 {
 	system("cls");
 	printf("UNLOCKED");
 	getch();
init1();
}
}


void delay(int k)
{
	int c, d;
   
   for (c = 1; c <= 15000 *k; c++)
for (d = 1; d <= 15000*k; d++)
   {}  
}


void rules()
{
	textcolor(14);

	printf("\t\t\t**INSTRUCTIONS** \t\t\t\n");
	printf("-This game is very in line with a very early 90s hallway simulator.\n");
	printf("-Even with it's simplistic features, this game can still put your brain to the test!\n");
	printf("-Try the first hallway to get the feel of the game, get to the point marked 'T'.");
	getch();
	system("cls");
	game11(0,0);
	
}
void skeleton3()
{
	FILE *fp=fopen("Skeleton3.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
//	printf("\033[1;35m");
textcolor(12);

	printf("%c", ch);
	
}
}
}
void ending2()
{
	system("cls");
	textcolor(12);
	printf("Realizing the true despair of the bridges castle, you decide to forfeit any thought of escape....bon voyage...\n");
	getch();
	skeleton3();
	getch();
	printf("You decide to go with along with him....\n");
	getch();
	system("cls");
	printf("The end.");
	getch();
//	struct reportcard e[1];
//FILE *ptr= fopen("highscore.txt", "a");
//e[0].points=CAVAREA;
//moldren++;
//fprintf(ptr,"%s %d",CASTER,e[0].points);
	main();
}

void Door()
{int a;system("cls");
textcolor(13);
printf("Do you dare to traverse the menacing halls of the Bridges Castle?(1=YES/2=NO)");



	FILE *fp=fopen("Door.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
//	printf("\033[1;35m");
textcolor(13);

	printf("%c", ch);
	
}

}
scanf("%d", &a);
if (a==1)
{
	system("cls");
	rules();
}
else if(a==2)
{
	ending2();
}
}
void CL3()
{
	FILE *fp=fopen("Clock Cycle 3.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
	textcolor(14);

	printf("%c", ch);
	
}
}
}

void CL2()
{
FILE *fp=fopen("Clock Cycle 2.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
	textcolor(14);

	printf("%c", ch);
	
}
}
	
}

void CL1()
{
	FILE *fp=fopen("Clock Cycle 1.txt", "r");char ch;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
	textcolor(14);

	printf("%c", ch);
	
}
}
}


void CLockAnimation()
{

	 CL1();
	delay(1);
	system("cls");
	 CL2();
	delay(1);
	system("cls");
	 CL3();
	 getch();
	 getch();
	system("cls");
	
}


void Waker()
{
	FILE *fp=fopen("Waking up.txt", "r");char ch;	FILE *tb=fopen("Waking up2.txt", "r");char sh;
while(1)
{
	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
//	textcolor(12);
textcolor(12);
	printf("%c", ch);

	
}
}
while(1)
{
	sh=fgetc(tb);
	if (sh==EOF)
	break;
	else
	{
//	printf("\033[1;34m");
textcolor(9);
	printf("%c", sh);
	
}
}
}
void title()
{
	FILE *fp=fopen("Title Screen.txt", "r");char ch;
while(1)
{

	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
//	printf("\033[1;36m");
	textcolor(11);
	printf("%c", ch);
	
}
}
printf("\n");
}
void controls()
{
	FILE *fp=fopen("Controls.txt", "r");char ch;
while(1)
{

	ch=fgetc(fp);
	if (ch==EOF)
	break;
	else
	{
//	printf("\033[1;36m");
	textcolor(12);
	printf("%c", ch);
	
}
}
}

void viewreport(struct reportcard *e)
{int i;
system("cls");
for(i=0;i<10;i++)
{
	printf("%s %d\n", e->name, e->points);
	e++;
}
getch();

main();
}
int main()
{CAVAREA=0;
int a;
system("mode 650");
textcolor(14);
//printf("Enter your name.\n");
//scanf("%s", CASTER);
system("cls");
printf("Please enter your choice.\n1.View Report Card.\n2.Start game.\n");
scanf("%d", &a);

if(a==1)
{

//{FILE *fp= fopen ( "highscore.txt", "rb" ) ;
//struct reportcard e;
//fread ( &e, sizeof (e), 1, fp ); 
//fclose ( fp ) ;
//viewreport(&e);
struct reportcard e[10];
FILE *ptr= fopen("highscore.txt", "rb");
fread(&e, 1, sizeof(e), ptr);

viewreport(e);
}

else if (a==2)
{
system("cls");
title();
getch();
controls();
getch();
Waker();
getch();
system("cls");
CLockAnimation();
Door();}


}

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void visual(int wrong)
{
	switch(wrong)
	{
		case 0 :
			system("cls");
			printf("||=======\n");
			printf("||      |\n");
			printf("||      O\n");
			printf("||     /|%c \n", '\\');
			printf("||     / %c \n", '\\');
			break;
		case 1 :
			system("cls");
			printf("||=======\n");
			printf("||      |\n");
			printf("||      O\n");
			printf("||     /|%c \n", '\\');		//Well it looks weird but the thing is if I directly put / , it is not shouwing it , so had to make it a character.
			printf("||     /  \n");
			break;
		case 2 :
			system("cls");
			printf("||=======\n");
			printf("||      |\n");
			printf("||      O\n");
			printf("||     /|%c \n", '\\');
			printf("||\n");
			break;
		case 3 :
			system("cls");
			printf("||=======\n");
			printf("||      |\n");
			printf("||      O\n");
			printf("||     /|  \n");
			printf("||\n");
			break;
		case 4 :
			system("cls");
			printf("||=======\n");
			printf("||      |\n");
			printf("||      O\n");
			printf("||     /  \n");
			printf("||\n");
			break;
		case 5 :
			printf("||=======\n");
			printf("||      |\n");
			printf("||      O\n");
			printf("||\n");
			printf("||\n");
			break;
	}
	
}
int main()
{
	char org[7] = {'b', 'r', 'i', 'd','g','e','s'};		//Word stored in org
	char inp[7], x;
	int i, right, wrong=5, win=0, inc=0;
	
	visual(wrong);		//Will show initial visual
	
	printf("The letter has 7 words\n");
	for(i=0 ; i<7 ; i++)
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
		for(i=0 ; i<7 ; i++)		//To check if guessed word is in the org array
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
		visual(wrong);
		for(i=0 ; i<7 ; i++)
		{
			printf("%c ", inp[i]);		//Will show you the array with right guessed alphabet
		}
		if(right==0)
		{
			wrong--;
			visual(wrong);
			printf("\nWrong Guess\nRemaining tries are %d\nPress any key to start guessing again", wrong);
			getch();
			system("cls");
			visual(wrong);
		for(i=0 ; i<7 ; i++)
		{
			printf("%c ", inp[i]);
		}
		}
		else
		{
			for(i=inc ; i<7 ; i++)
			{
				if(inp[i]==org[i])
				{
					win++;
				}
			}
			inc=win;		//OK this is a interesting part cuz, first I was incrementing the loop by adding 1 in inc but if the alph. has
			if(win==7)		//more than one similiar alphabet, so it was not incrementing thats why, had to equate this with win
			{
				printf("\nWinner Winner Chicken Dinner");
				break;
			}
		}
	}
	if (wrong <=0)		//For Losers only
	{
		printf("\n");
		printf("\nLoser\nBetter Luck NeXt Time");
	}
}

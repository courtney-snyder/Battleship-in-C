#include <stdio.h>
#include <stdlib.h>
#include "Battleship.h"
#define _CRT_SECURE_NO_WARNINGS
#define ROWS 10
#define COLS 10

void welcome_screen(int choice)
{
	do
	{
	printf("Welcome to Battleship!\n1.	Rules\n2.	Play Battleship\n3.	Exit\n");
	scanf("%d", &choice);
	
	if (choice == 1)
	{
		print_rules();
	}
	if (choice == 3)
	{
		printf("See you later!\n");
		return 0;
	}
	}
	while (choice != 2); //If choice == 2, we break out of the do while loop and begin the game
}

void print_rules()
{
	printf("On your turn, pick a target on the computer's board using (row, column) notation. When you call a shot, the computer will tell you if the shot is a hit or miss.\n");
}

void create_game_board(char board[ROWS][COLS], int rows, int cols)
{
	int row_ind = 0, col_ind = 0;
	for (; row_ind < rows; row_ind++)
	{
		for (col_ind = 0; col_ind < cols; col_ind++)
		{
			board[row_ind][col_ind] = '~';
		}
	}
}

void print_game_board(char board[ROWS][COLS], int rows, int cols)
{
	int row_index = 0, col_index = 0;
	printf("  0  1  2  3  4  5  6  7  8  9\n"); //Displays the column numbers above the columns. Outside of the for loop so it is only displayed once.
	for (; row_index < rows; row_index++)
	{
		printf("%d", row_index); //Displays the row numbers to the left of the 0th index of each row. Inside the for loop because only one number is displayed per row, and that number is the row index
		for (col_index = 0; col_index < cols; col_index++)
		{
			printf(" %c ", board[row_index][col_index]); //The row_index stays the same until columns [0]-[9] are filled, then the next row is filled in until the end of row [9].		
		}
		printf("\n");
	}
}

int starting_player()
{
	int num = 0;
	num = rand() % 2;
	if (num == 0)
	{
		printf("Computer goes first.\n");
		return num;
	}
	else
	{
		printf("Player goes first.\n");
		return num;
	}
}

void manually_place_ships(int car_direction, int bs_direction, int sub_direction, int cru_direction, int des_direction, int*car_dir_ptr, int*bs_dir_ptr, int*sub_dir_ptr, int*cru_dir_ptr, int*des_dir_ptr)
{
	int index = 0;
	for (; index < 5; index++)
	{
		printf("To place ships horizontally, enter 0. To place ships vertically, enter 1.\n");
//When index = 0, they decide which direction to place their carrier, index = 1 is battleship, index = 2 is sub, until index = 5, then we break out of the for loop
		if (index == 0)
		{
			printf("Enter which direction you would like your carrier, 5 spaces, to go.\n");
			scanf("%d", &car_direction);
			*car_dir_ptr = car_direction;
		}
		else if (index == 1)
		{
			printf("Enter which direction you would like your battleship, 4 spaces, to go.\n");
			scanf("%d", &bs_direction);
			*bs_dir_ptr = bs_direction;
		}
		else if (index == 2)
		{
			printf("Enter which direction you would like your submarine, 3 spaces, to go.\n");
			scanf("%d", &sub_direction);
			*sub_dir_ptr = sub_direction;
		}
		else if (index == 3)
		{
			printf("Enter which direction you would like your crusier, 3 spaces, to go.\n");
			scanf("%d", &cru_direction);
			*cru_dir_ptr = cru_direction;
		}
		else if (index == 4)
		{
			printf("Enter which direction you would like your destroyer, 2 spaces, to go.\n");
			scanf("%d", &des_direction);
			*des_dir_ptr = des_direction;
		}
	}
}

void randomly_place_ships(int car_direction, int bs_direction, int sub_direction, int cru_direction, int des_direction, int*car_dir_ptr, int*bs_dir_ptr, int*sub_dir_ptr, int*cru_dir_ptr, int*des_dir_ptr)
{
	int index = 0;
for (; index < 5; index++)
{
//When index = 0, they decide which direction to place their carrier, index = 1 is battleship, index = 2 is sub, until index = 5, then we break out of the for loop
	if (index == 0)
	{
		car_direction = rand() % 2;
		*car_dir_ptr = car_direction;
	}
	else if (index == 1)
	{
		bs_direction = rand() % 2;
		*bs_dir_ptr = bs_direction;
	}
	else if (index == 2)
	{
		sub_direction = rand() % 2;
		*sub_dir_ptr = sub_direction;
	}
	else if (index == 3)
	{
		cru_direction = rand() % 2;
		*cru_dir_ptr = cru_direction;
	}
	else if (index == 4)
	{
		des_direction = rand() % 2;
		*des_dir_ptr = des_direction;
	}
}
}

void random_starting_point(Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr)
{
	int index = 0;
	for (; index < 5; index++)
	{
//Essentially the same loop as the manually_place_ships loop. When index = 0, they decide where to place their carrier, index = 1 is battleship, index = 2 is sub, until index = 5, then we break out of the for loop
		if (index == 0)
		{
			if (car.direction == 0)
			{
			*car_row_ptr = rand() % 10;
			*car_col_ptr = rand() % (10 - car.size - 1);
			//Sets the starting row, col coordinate equal to the corresponding pointers so the program can return a column and direction for every ship (10 returns)
			car.row[0] = *car_row_ptr;
			car.col[0] = *car_col_ptr;
			}
			else //Carrier is vertical
			{
			*car_row_ptr = rand() % (10 - car.size - 1);
			*car_col_ptr = rand() % 10;
			car.row[0] = *car_row_ptr; //Sets the pointers equal to the corresponding coordinates so the program can return a column and direction for every ship (10 returns)
			car.col[0] = *car_col_ptr;
			}
		}
		else if (index == 1)
		{
			do //The do while loop makes sure that none of the ships start in the same place
			{
			if (bs.direction == 0) //Battleship is horizontal
			{
			*bs_row_ptr = rand() % 10;
			*bs_col_ptr = rand() % (10 - bs.size - 1);
			bs.row[0] = *bs_row_ptr;
			bs.col[0] = *bs_col_ptr;
			}
			else //Battleship is vertical
			{
			*bs_row_ptr = rand() % (10 - bs.size - 1);
			*bs_col_ptr = rand() % 10;
			bs.row[0] = *bs_row_ptr;
			bs.col[0] = *bs_col_ptr;
			}
			}
			while(*bs_row_ptr == *car_row_ptr && *bs_col_ptr == *car_col_ptr);
		}
		else if (index == 2)
		{
			do
			{
			if (sub.direction == 0) //Sub is horizontal
			{
			*sub_row_ptr = rand() % 10;
			*sub_col_ptr = rand() % (10 - sub.size - 1);
			sub.row[0] = *sub_row_ptr;
			sub.col[0] = *sub_col_ptr;
			}
			else //Sub is vertical
			{
			*sub_row_ptr = rand() % (10 - sub.size - 1);
			*sub_col_ptr = rand() % 10;
			sub.row[0] = *sub_row_ptr;
			sub.col[0] = *sub_col_ptr;
			}
			}
			while ((*sub_row_ptr == *bs_row_ptr || *sub_row_ptr == *car_row_ptr) && (*sub_col_ptr == *bs_col_ptr || *sub_col_ptr == *car_col_ptr));
		}
		else if (index == 3)
		{
			do
			{
			if (cru.direction == 0) //Cruiser is horizontal
			{
			*cru_row_ptr = rand() % 10;
			*cru_col_ptr = rand() % (10 - cru.size - 1);
			cru.row[0] = *cru_row_ptr;
			cru.col[0] = *cru_col_ptr;
			}
			else
			{//Cruiser is vertical
			*cru_row_ptr = rand() % (10 - cru.size - 1);
			*cru_col_ptr = rand() % 10;
			cru.row[0] = *cru_row_ptr;
			cru.col[0] = *cru_col_ptr;
			}
			}
			while((*cru_row_ptr == *sub_row_ptr || *cru_row_ptr == *bs_row_ptr || *cru_row_ptr == *car_row_ptr) && (*cru_col_ptr == *sub_col_ptr || *cru_col_ptr == *bs_col_ptr || *cru_col_ptr == *car_col_ptr));
		}
		else if (index == 4)
		{
			do
			{
			if (des.direction == 0) //Destroyer is horizontal
			{
			*des_row_ptr = rand() % 10;
			*des_col_ptr = rand() % (10 - des.size - 1);
			des.row[0] = *des_row_ptr;
			des.col[0] = *des_col_ptr;
			}
			else //Destroyer is vertical
			{
			*des_row_ptr = rand() % (10 - des.size - 1);
			*des_col_ptr = rand() % 10;
			des.row[0] = *des_row_ptr;
			des.col[0] = *des_col_ptr;
			}
			}
			while((*des_row_ptr == *cru_row_ptr || *des_row_ptr == *sub_row_ptr || *des_row_ptr == *bs_row_ptr || *des_row_ptr == *car_row_ptr) && (*des_col_ptr == *cru_col_ptr || *des_col_ptr == *sub_col_ptr || *des_col_ptr == *bs_col_ptr || *des_col_ptr == *car_col_ptr));
		}
}
}

void manual_starting_point(Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr)
{
	int index = 0, car_row = 0, car_col = 0, bs_row = 0, bs_col = 0, sub_row = 0, sub_col = 0, cru_row = 0, cru_col = 0, des_row = 0, des_col = 0;
	for (; index < 5; index++)
	{
//Essentially the same loop as the manually_place_ships loop. When index = 0, they decide where to place their carrier, index = 1 is battleship, index = 2 is sub, until index = 5, then we break out of the for loop
		if (index == 0)
		{
			printf("Enter where you would like your carrier, 5 spaces, to go in the format row, column. Do not include the comma, but separate the coordinates with a space.\n");
			scanf("%d%d", &car_row, &car_col); //Scans the row and column coordinates
			*car_row_ptr = car_row; //Sets the pointers equal to the corresponding coordinates so the program can return a column and direction for every ship (10 returns)
			*car_col_ptr = car_col;
		}
		else if (index == 1)
		{
			do //The same do while loop as the one in random_starting_point; makes sure the ships don't start on the same coordinate
			{
			printf("Enter which row you would like your battleship, 4 spaces, to go in the format row, column. Do not include the comma, but separate the coordinates with a space.\n");
			scanf("%d%d", &bs_row, &bs_col);
			*bs_row_ptr = bs_row;
			*bs_col_ptr = bs_col;
			}
			while(*bs_row_ptr == *car_row_ptr && *bs_col_ptr == *car_col_ptr);
		}
		else if (index == 2)
		{
			do
			{
			printf("Enter which row you would like your submarine, 3 spaces, to go in the format row, column. Do not include the comma, but separate the coordinates with a space.\n");
			scanf("%d%d", &sub_row, &sub_col);
			*sub_row_ptr = sub_row;
			*sub_col_ptr = sub_col;
			}
			while ((*sub_row_ptr == *bs_row_ptr || *sub_row_ptr == *car_row_ptr) && (*sub_col_ptr == *bs_col_ptr || *sub_col_ptr == *car_col_ptr));
		}
		else if (index == 3)
		{
			do
			{
			printf("Enter which row you would like your crusier, 3 spaces, to go in the format row, column. Do not include the comma, but separate the coordinates with a space.\n");
			scanf("%d%d", &cru_row, &cru_col);
			*cru_row_ptr = cru_row;
			*cru_col_ptr = cru_col;
			}
			while((*cru_row_ptr == *sub_row_ptr || *cru_row_ptr == *bs_row_ptr || *cru_row_ptr == *car_row_ptr) && (*cru_col_ptr == *sub_col_ptr || *cru_col_ptr == *bs_col_ptr || *cru_col_ptr == *car_col_ptr));
		}
		else if (index == 4)
		{
			do
			{
			printf("Enter which row you would like your crusier, 3 spaces, to go in the format row, column. Do not include the comma, but separate the coordinates with a space.\n");
			scanf("%d%d", &des_row, &des_col);
			*des_row_ptr = des_row;
			*des_col_ptr = des_col;
			}
			while((*des_row_ptr == *cru_row_ptr || *des_row_ptr == *sub_row_ptr || *des_row_ptr == *bs_row_ptr || *des_row_ptr == *car_row_ptr) && (*des_col_ptr == *cru_col_ptr || *des_col_ptr == *sub_col_ptr || *des_col_ptr == *bs_col_ptr || *des_col_ptr == *car_col_ptr));
		}
	}
}

void total_place_function(int choice, Ship car, Ship bs, Ship sub, Ship cru, Ship des, int *car_dir_ptr, int *car_row_ptr, int *car_col_ptr, int *bs_dir_ptr, int *bs_row_ptr, int *bs_col_ptr, int *sub_dir_ptr, int *sub_row_ptr, int *sub_col_ptr, int *cru_dir_ptr, int *cru_row_ptr, int *cru_col_ptr, int *des_dir_ptr, int *des_row_ptr, int *des_col_ptr)
{
	if (choice == 1)
	{
		manually_place_ships(car.direction, bs.direction, sub.direction, cru.direction, des.direction, car_dir_ptr, bs_dir_ptr, sub_dir_ptr, cru_dir_ptr, des_dir_ptr);
		car.direction = *car_dir_ptr;
		bs.direction = *bs_dir_ptr;
		sub.direction = *sub_dir_ptr;
		cru.direction = *cru_dir_ptr;
		des.direction = *des_dir_ptr;
		printf("Carrier: %d\nBattleship: %d\nSubmarine: %d\nCruiser: %d\nDestroyer: %d\n", car.direction, bs.direction, sub.direction, cru.direction, des.direction);
		manual_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
		car.col[0] = *car_col_ptr;
		car.row[0] = *car_row_ptr;
		bs.col[0] = *bs_col_ptr;
		bs.row[0] = *bs_row_ptr;
		sub.col[0] = *sub_col_ptr;
		sub.row[0] = *sub_row_ptr;
		cru.col[0] = *cru_col_ptr;
		cru.row[0] = *cru_row_ptr;
		des.col[0] = *des_col_ptr;
		des.row[0] = *des_row_ptr;
		printf("Player's Starting Coordinates:\nRow, Col: \nCarrier: %d, %d\nBattleship: %d, %d\nSubmarine: %d, %d\nCruiser: %d, %d\nDestroyer: %d, %d\n", car.row[0], car.col[0], bs.row[0], bs.col[0], sub.row[0], sub.col[0], cru.row[0], cru.col[0], des.row[0], des.col[0]);
		system("pause");
		system("cls");
	}
	else
	{
		randomly_place_ships(car.direction, bs.direction, sub.direction, cru.direction, des.direction, car_dir_ptr, bs_dir_ptr, sub_dir_ptr, cru_dir_ptr, des_dir_ptr);
		car.direction = *car_dir_ptr;
		bs.direction = *bs_dir_ptr;
		sub.direction = *sub_dir_ptr;
		cru.direction = *cru_dir_ptr;
		des.direction = *des_dir_ptr;
		printf("Carrier: %d\nBattleship: %d\nSubmarine: %d\nCruiser: %d\nDestroyer: %d\n", car.direction, bs.direction, sub.direction, cru.direction, des.direction);
		random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
		car.col[0] = *car_col_ptr;
		car.row[0] = *car_row_ptr;
		bs.col[0] = *bs_col_ptr;
		bs.row[0] = *bs_row_ptr;
		sub.col[0] = *sub_col_ptr;
		sub.row[0] = *sub_row_ptr;
		cru.col[0] = *cru_col_ptr;
		cru.row[0] = *cru_row_ptr;
		des.col[0] = *des_col_ptr;
		des.row[0] = *des_row_ptr;
		printf("Player's Starting Coordinates:\nRow, Col: \nCarrier: %d, %d\nBattleship: %d, %d\nSubmarine: %d, %d\nCruiser: %d, %d\nDestroyer: %d, %d\n", car.row[0], car.col[0], bs.row[0], bs.col[0], sub.row[0], sub.col[0], cru.row[0], cru.col[0], des.row[0], des.col[0]);
		system("pause");
		system("cls");
	}
}

//This function records every coordinate of the ships without placing them on the board. This is so I don't have to create two arrays.
void write_ships_down(FILE *write, Ship car, Ship bs, Ship sub, Ship cru, Ship des) //int car_length, int car_direction, int player_car_row, int player_car_col, int bs_length, int bs_direction, int player_bs_row, int player_bs_col, int sub_length, int sub_direction, int player_sub_row, int player_sub_col, int cru_length, int cru_direction, int player_cru_row, int player_cru_col, int des_length, int des_direction, int player_des_row, int player_des_col)
{
	int i = 0, j = 0;
	for (; i < 1; i++)
	{
		if (i == 0) //Prints the Carrier's coordinates row and col[0], row and col[1], row and col[2], row and col[3], row and col[4]
		{
				for(j = 0; j < car.size - 1; j++)
				{
					fprintf(write, "%d %d\n", car.row[j], car.col[j]);
				}
		}
		else if (i == 1)
		{
				for(j = 0; j < bs.size - 1; j++)
				{
					fprintf(write, "%d %d\n", bs.row[j], bs.col[j]);
				}
		}
		else if (i == 2)
		{
				for(j = 0; j < sub.size - 1; j++)
				{
					fprintf(write, "%d %d\n", sub.row[j], sub.col[j]);
				}
		}
		else if (i == 3)
		{
				for(j = 0; j < cru.size - 1; j++)
				{
					fprintf(write, "%d %d\n", cru.row[j], cru.col[j]);
				}
		}
		else if (i == 4)
		{
				for (j = 0; j < des.size - 1; j++);
				{
					fprintf(write, "%d %d\n", des.row[j], des.col[j]);
				}
		}
	}
}

int hit_or_miss(char opponents_board[ROWS][COLS], Ship opponents_car, Ship opponents_bs, Ship opponents_sub, Ship opponents_cru, Ship opponents_des, int*car_hits, int*bs_hits, int*sub_hits, int*cru_hits, int*des_hits, int row, int col)
{
	if ((row == opponents_car.row[0] && col == opponents_car.col[0]) || (row == opponents_car.row[1] && col == opponents_car.col[1]) || (row == opponents_car.row[2] && col == opponents_car.col[2]) || (row == opponents_car.row[3] && col == opponents_car.col[3]) || (row == opponents_car.row[4] && col == opponents_car.col[4]))
	//The shot hits somewhere on the opponent's carrier, so it can hit one of five spots. The carrier starts at car.row, car.col
		//The opponents carrier is horizontal, so the columns increase from the starting column, car.col. If the guess is in the right row, then if it's a hit, it hit (row,col) (row,col+1) (row,col+2) (row,col+3) or (row,col+4)
		//The guess was a hit and the carrier is horizontal
		{	
			printf("Hit!\n");
			opponents_board[row][col] = 'x';
			(*car_hits)++;
			return 1;
		}
	//The shot hits somewhere on the opponent's battleship, so it can hit one of four spots. The carrier starts at bs.row, bs.col
	else if ((row == opponents_bs.row[0] && col == opponents_bs.col[0]) || (row == opponents_bs.row[1] && col == opponents_bs.col[1]) || (row == opponents_bs.row[2] && col == opponents_bs.col[2]) || (row == opponents_bs.row[3] && col == opponents_bs.col[3]))
		{
			printf("Hit!\n");
			opponents_board[row][col] = 'x';
			(*bs_hits)++;
			return 1;
		}

	else if ((row == opponents_sub.row[0] && col == opponents_sub.col[0]) || (row == opponents_sub.row[1] && col == opponents_sub.col[1]) || (row == opponents_sub.row[2] && col == opponents_sub.col[2]))
		{
			printf("Hit!\n");
			opponents_board[row][col] = 'x';
			(*sub_hits)++;
			return 1;
		}
	else if ((row == opponents_cru.row[0] && col == opponents_cru.col[0]) || (row == opponents_cru.row[1] && col == opponents_cru.col[1]) || (row == opponents_cru.row[2] && col == opponents_cru.col[2]))
		{
			printf("Hit!\n");
			opponents_board[row][col] = 'x';
			(*cru_hits)++;
			return 1;
		}
	else if ((row == opponents_des.row[0] && col == opponents_des.col[0]) || (row == opponents_des.row[1] && col == opponents_des.col[1]))
		{
			printf("Hit!\n");
			opponents_board[row][col] = 'x';
			(*des_hits)++;
			return 1;
		}
	else
		{
			printf("Miss!\n");
			opponents_board[row][col] = 'M';
			return 0;
		}
}

void computer_guess(int hit_or_miss, int *previous_row_guess, int *previous_col_guess, int*row_guess, int*col_guess)
{
	int row = 0, col = 0, random = 0;
	if (hit_or_miss == 0)
	{ //Miss, so any guess is valid
	row = rand() % 10;
	col = rand() % 10;
	*row_guess = row;
	*col_guess = col;
	}
	else
	{
	random = rand() % 2; //Once you get a hit, you know the ship is either in the same row or same column. This randomly picks a direction to go and guesses the next coordinate based on the previous guess, which was a hit
		switch(random)
		{
		//Make a guess to the right of the hit, guessing that the ship is horizontal
		case 0: 
			*row_guess = *previous_row_guess;
			*col_guess = *previous_col_guess++;
			break;
		//Make a guess immediately below the hit, guessing that the ship is vertical
		case 1: 
			*row_guess = *previous_row_guess++;
			*col_guess = *previous_col_guess;
			break;
		}
	}
	//The shot hits somewhere on the opponent's battleship, so it can hit one of four spots. The carrier starts at bs.row, bs.col
}

void update_stat(int hit_or_miss, int*hits, int*misses, int computer_or_player, FILE*write)
{
	switch(computer_or_player)
	{
		//Computer
		case 1: computer_or_player == 0;
	if (hit_or_miss == 1)
	{//Hit
		(*hits)++; //Increments computer.hits
		fprintf(write, "Computer has %d hits\n", *hits);
	}
	else
	{//Miss
		(*misses)++; //Increments computer.misses
		fprintf(write, "Computer has %d misses\n", *misses);
	}
	break;
		//Player
		default:
	if (hit_or_miss == 1)
	{//Hit
		(*hits)++;
		fprintf(write, "Player has %d hits\n", *hits);
	}
	else
	{//Miss
		(*misses)++;
		fprintf(write, "Player has %d misses\n", *misses);
	}
	break;
	}
}

//This determines if the ship has been sunk, if all of it's coordinates have been guessed
void is_sunk(Ship opponents_car, Ship opponents_bs, Ship opponents_sub, Ship opponents_cru, Ship opponents_des)
{ //I used all if statements to 1) remind the player which ships they have already sunk every turn, rather than just printing it when they sink it, and 2) because multiple ships can but sunk at once
	if (opponents_car.hits == 5)
	{
		printf("Carrier is sunk!\n");
	}
	if (opponents_bs.hits == 4)
	{
		printf("Battleship is sunk!\n");
	}
	if (opponents_sub.hits == 3)
	{
		printf("Submairne is sunk!\n");
	}
	if (opponents_cru.hits == 3)
	{
		printf("Cruiser is sunk!\n");
	}
	if (opponents_des.hits == 2)
	{
		printf("Destroyer is sunk!\n");
	}
}
//This makes sure that the ships don't share any coordinates or overlap
void check_for_overlap (Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr, int*new_car_row_ptr, int*new_car_col_ptr, int*new_bs_row_ptr, int*new_bs_col_ptr, int*new_sub_row_ptr, int*new_sub_col_ptr, int*new_cru_row_ptr, int*new_cru_col_ptr, int*new_des_row_ptr, int*new_des_col_ptr)
{
	int k = 0;
	*new_bs_row_ptr = *bs_row_ptr;
	*new_bs_col_ptr = *bs_col_ptr;
	*new_sub_row_ptr = *sub_row_ptr;
	*new_sub_col_ptr = *sub_col_ptr;
	*new_cru_row_ptr = *cru_row_ptr;
	*new_cru_col_ptr = *cru_col_ptr;
	*new_des_row_ptr = *des_row_ptr;
	*new_des_col_ptr = *des_col_ptr; //I set these all equal to each other so that when I call the *new pointers in main, I get the right value. If cru_col_ptr doesn't change, then new_cru_col_ptr will just be the original value of cru_col_ptr, but if it does change then new_cru_col_ptr will be important in making sure that there is not overlap
	for (k = 0; k < car.size; k++)
	{ //I used all if statements because it's possible for multiple ships to share coordinates (eg the destroyer and battleship can have the same starting coordinates and the battleship and cruiser could intersect at some point
		if (car.row[k] && car.col[k] == bs.row[k] && bs.col[k])
		{//If the carrier and battleship share any coordinates, move the battleship
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_bs_row_ptr = *bs_row_ptr;
			*new_bs_col_ptr = *bs_col_ptr;
		}
		if (car.row[k] && car.col[k] == sub.row[k] && sub.col[k])
		{//If the carrier and sub share any coordinates, move the sub
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_sub_row_ptr = *sub_row_ptr;
			*new_sub_col_ptr = *sub_col_ptr;
		}
		if (car.row[k] && car.col[k] == cru.row[k] && cru.col[k])
		{//If the carrier and cruiser share any coordinates, move the cruiser
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_cru_row_ptr = *cru_row_ptr;
			*new_cru_col_ptr = *cru_col_ptr;
		}
		if (car.row[k] && car.col[k] == des.row[k] && des.col[k])
		{//If the carrier and destroyer share any coordinates, move the destroyer
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_des_row_ptr = *des_row_ptr;
			*new_des_col_ptr = *des_col_ptr;
		}
		if (bs.row[k] && bs.col[k] == sub.row[k] && sub.col[k])
		{//If the battleship and sub share any coordinate, move the sub
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_sub_row_ptr = *sub_row_ptr;
			*new_sub_col_ptr = *sub_col_ptr;
		}
		if (bs.row[k] && bs.col[k] == cru.row[k] && cru.col[k])
		{//If the battleship and cruiser share any coordinates, move the cruiser
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_cru_row_ptr = *cru_row_ptr;
			*new_cru_col_ptr = *cru_col_ptr;
		}
		if (bs.row[k] && bs.col[k] == des.row[k] && des.col[k])
		{//If the battleship and destroyer share any coordinates, move the destroyer
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_des_row_ptr = *des_row_ptr;
			*new_des_col_ptr = *des_col_ptr;
		}
		if (sub.row[k] && sub.col[k] == cru.row[k] && cru.col[k])
		{//If the sub and the cruiser share any coordinates, move the cruiser
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_cru_row_ptr = *cru_row_ptr;
			*new_cru_col_ptr = *cru_col_ptr;
		}
		if (sub.row[k] && sub.col[k] == cru.row[k] && cru.col[k])
		{//If the sub and the destroyer share any coordinates, move the destroyer
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_des_row_ptr = *des_row_ptr;
			*new_des_col_ptr = *des_col_ptr;
		}
		if (cru.row[k] && cru.col[k] == des.row[k] && des.col[k])
		{//If the cruiser and destroyer share any coordinates, move the destroyer
			random_starting_point(car, bs, sub, cru, des, car_row_ptr, car_col_ptr, bs_row_ptr, bs_col_ptr, sub_row_ptr, sub_col_ptr, cru_row_ptr, cru_col_ptr, des_row_ptr, des_col_ptr);
			*new_des_row_ptr = *des_row_ptr;
			*new_des_col_ptr = *des_col_ptr;
		}
	}
}

//void populate_coordinates(Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr)
//{ int inc_car = 0, inc_bs = 0, inc_sub = 0, inc_cru = 0, inc_des = 0;
//	int k = 0;
//	if (car.direction == 0)
//	{
//		car.row[0] = *car_row_ptr;
//		car.col[0] = *car_col_ptr;
//		for (k = 1; k < car.size - 1; k++)
//		{
//			car.row[k] = *car_row_ptr; //As the index gets larger, the row coordinate stays the same
//			car.col[k] = (*car_col_ptr)++; //As the index gets larger, the column increments by one
//		}
//	}
//	else if (car.direction == 1)
//	{
//		car.row[0] = *car_row_ptr;
//		car.col[0] = *car_col_ptr;
//		for (k = 1; k < car.size - 1; k++)
//		{
//			car.row[k] = (*car_row_ptr)++; //As the index gets larger, the row coordinate increments by one
//			car.col[k] = *car_col_ptr; //As the index gets larger, the column stays the same
//		}
//	}
//	if (bs.direction == 0)
//	{ // battleship is horizontal, so the columns increase from the starting column, bs.col
//		bs.row[0] = *bs_row_ptr;
//		bs.col[0] = *bs_col_ptr;
//		for (k = 1; k < bs.size - 1; k++)
//		{
//			bs.row[k] = *bs_row_ptr;
//			bs.col[k] = (*bs_col_ptr)++;
//		}
//	}
//	else if (bs.direction == 1)
//	{ //The battleship is vertical, so the rows increase from the starting row, bs.row
//		bs.row[0] = *bs_row_ptr;
//		bs.col[0] = *bs_col_ptr;
//		for (k = 1; k < bs.size - 1; k++)
//		{
//			bs.row[k] = (*bs_row_ptr)++;
//			bs.col[k] = *bs_col_ptr;
//		}
//	}
//	if (sub.direction == 0)
//	{ //The sub is horizontal
//		sub.row[0] = *sub_row_ptr;
//		sub.col[0] = *sub_col_ptr;
//		for (k = 1; k < sub.size - 1; k++)
//		{
//			sub.row[k] = *sub_row_ptr;
//			sub.col[k] = (*sub_col_ptr)++;
//		}
//	}
//	else if (sub.direction == 1)
//	{ //The sub is vertical
//		sub.row[0] = *sub_row_ptr;
//		sub.col[0] = *sub_col_ptr;
//		for (k = 1; k < bs.size - 1; k++)
//		{
//			sub.row[k] = (*sub_row_ptr)++;
//			sub.col[k] = *sub_col_ptr;
//		}
//	}
//	if (cru.direction == 0)
//	{ //The cruiser is horizontal
//		cru.row[0] = *cru_row_ptr;
//		cru.col[0] = *cru_col_ptr;
//		for (k = 1; k < cru.size - 1; k++)
//		{
//			cru.row[k] = *cru_row_ptr;
//			cru.col[k] = (*cru_col_ptr)++;
//		}
//	}
//	else if (cru.direction == 1)
//	{ //The cruiser is vertical
//		cru.row[0] = *cru_row_ptr;
//		cru.col[0] = *cru_col_ptr;
//		for (k = 1; k < cru.size - 1; k++)
//		{
//			cru.row[k] = (*cru_row_ptr)++;
//			cru.col[k] = *cru_col_ptr;
//		}
//	}
//	if (des.direction == 0)
//	{ //The cruiser is horizontal
//		des.row[0] = *des_row_ptr;
//		des.col[0] = *des_col_ptr;
//		des.row[1] = *des_row_ptr;
//		des.col[1] = *des_col_ptr++;
//	}
//	else if (des.direction == 1)
//	{ //The cruiser is vertical
//		des.row[0] = *des_row_ptr;
//		des.col[0] = *des_col_ptr;
//		des.row[1] = *des_row_ptr++;
//		des.col[1] = *des_col_ptr;
//	}
//}
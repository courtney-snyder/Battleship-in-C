/*
Programmer: Courtney Snyder
Class: Computer Science 121, Lab Section 11, PA 6
Last Updated: 11/20/2015
Description: A game of Battleship with one player against the computer. The goal is to sink all of the other player's ships before they
sink all of yours. The game is over when one player sinks all of the other player's ships.
Ships:
'd' || 'D'= Destroyer = 2 cells
'r' || 'R' = Cruiser = 3 cells
's' || 'S' = Submarine = 3 cells
'b' || 'B' = Battleship = 4 cells
'c' || 'C' = Carrier = 5 cells
Credits:
Rules from http://www.hasbro.com/common/instruct/battleship.pdf with a bit of my own wording
create_game_board, print_game_board, random_start_direction written in class
*/

//CONCERNS: Something new_battleship.log says it's being used by another process?

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Battleship.h"
#define _CRT_SECURE_NO_WARNINGS
#define ROWS 10 //So the amount of rows can be changed whenever without hard coding
#define COLS 10 //So the amount of coulmns can be changed whenever without hard coding

int main (void)
{
	int choice = 0, starter = 0, i = 0, k = 0, player_row = 0, player_col = 0, comp_row = 0, comp_col = 0, prev_row = 0, prev_col = 0, comp_guess = 0, player_guess = 0, status = 0;
	char player_board[ROWS][COLS] = {"\0"}, computer_board[ROWS][COLS] = {"\0"};
	char placement = '\0';
	Ship des = {0, 2, 0, 0}, cru = {0, 3, 0, 0}, sub = {0, 3, 0, 0}, bs = {0, 4, 0, 0}, car = {0, 5, 0, 0}, comp_des = {0, 2, 0, 0}, comp_cru = {0, 3, 0, 0}, comp_sub = {0, 3, 0, 0}, comp_bs = {0, 4, 0, 0}, comp_car = {0, 5, 0, 0}; //Ships
	Stat player = {0, 0, 0.0, 0, 0}, computer = {0, 0, 0.0, 0, 0};
	FILE*write = NULL; //To write the information onto new_battleship.log
	FILE*read = NULL; //To read information from new_battleship.log
	int des_dir_ptr = 0, cru_dir_ptr = 0, sub_dir_ptr = 0, bs_dir_ptr = 0, car_dir_ptr = 0; //Direction pointers
	int car_row_ptr = 0, car_col_ptr = 0, bs_row_ptr = 0, bs_col_ptr = 0, sub_row_ptr = 0, sub_col_ptr = 0, cru_row_ptr = 0, cru_col_ptr = 0, des_row_ptr = 0, des_col_ptr = 0; //Row and Column pointers
	int comp_row_ptr = 0, comp_col_ptr = 0, prev_row_ptr = 0, prev_col_ptr = 0, comp_hits_ptr = 0, comp_misses_ptr = 0, player_hits_ptr = 0, player_misses_ptr = 0;
	int p_car_hits = 0, p_bs_hits = 0, p_sub_hits = 0, p_cru_hits = 0, p_des_hits = 0, c_car_hits = 0, c_bs_hits = 0, c_sub_hits = 0, c_cru_hits = 0, c_des_hits = 0;
	int *new_car_row_ptr = 0, *new_car_col_ptr = 0, *new_bs_row_ptr = 0, *new_bs_col_ptr = 0, *new_sub_row_ptr = 0, *new_sub_col_ptr = 0, *new_cru_row_ptr = 0, *new_cru_col_ptr = 0, *new_des_row_ptr = 0, *new_des_col_ptr = 0;

	srand((unsigned int)time(NULL));
	//I had to name the .log file "new_battleship.log" because my "battleship.log" started acting up and I couldn't save with it in the program; the error list said it was already being used by another process and nothing but VS was open
	write = fopen("new_battleship.log", "w");
	read = fopen("new_battleship.log", "r");

	welcome_screen(choice);
	create_game_board(player_board, ROWS, COLS);
	create_game_board(computer_board, ROWS, COLS);
	printf("PLAYER BOARD\n");
	printf("\n");
	print_game_board(player_board, ROWS, COLS);
	printf("COMPUTER BOARD\n");
	printf("\n");
	print_game_board(computer_board, ROWS, COLS);
	printf("How would you like to place your ships?\n1. Manually\n2. Randomly\n");
	scanf("%d", &choice);
	//I wrote total_place_function to save some space in main, but also so the program can easily be changed to a two human player game instead of player VS computer. For some reason total_place_function didn't work for the computer's board so I had to manually code the computer's randomized ship placement
	total_place_function(choice, car, bs, sub, cru, des, &car_dir_ptr, &car_row_ptr, &car_col_ptr, &bs_dir_ptr, &bs_row_ptr, &bs_col_ptr, &sub_dir_ptr, &sub_row_ptr, &sub_col_ptr, &cru_dir_ptr, &cru_row_ptr, &cru_col_ptr, &des_dir_ptr, &des_row_ptr, &des_col_ptr);
	randomly_place_ships(comp_car.direction, comp_bs.direction, comp_sub.direction, comp_cru.direction, comp_des.direction, &car_dir_ptr, &bs_dir_ptr, &sub_dir_ptr, &cru_dir_ptr, &des_dir_ptr);
	comp_car.direction = car_dir_ptr;
	comp_bs.direction = bs_dir_ptr;
	comp_sub.direction = sub_dir_ptr;
	comp_cru.direction = cru_dir_ptr;
	comp_des.direction = des_dir_ptr;
	//A starting point is randomly generated
	random_starting_point(comp_car, comp_bs, comp_sub, comp_cru, comp_des, &car_row_ptr, &car_col_ptr, &bs_row_ptr, &bs_col_ptr, &sub_row_ptr, &sub_col_ptr, &cru_row_ptr, &cru_col_ptr, &des_row_ptr, &des_col_ptr); //I used car_row_ptr and car_col_ptr because even though it was designated for the carrier row and column starting coordinates, since the coordinates are randomized every iteration, it works as a multifunctional pointer
	//These are the coordinates of the ships
		if (car.direction == 0)
		{ //The carrier is horizontal so the columns increase from the starting column, car.col: (row,col) (row,col+1) (row,col+2) (row,col+3) (row,col+4)
			for (k = 0; k < car.size; k++)
			{ //The ship has 5 indeces for each row and column array. row[0],[1],[2],[3],[4], and col[0],[1],[2],[3],[4]. Since the index starts from 1, k must be one less than the size of the ship
			car.col[k] = car_col_ptr++;
			car.row[k] = car_row_ptr;
			player_board[car.row[k]][car.col[k]] = 'c';
			}
		}
		else if (car.direction == 1)
		{ //The carrier is vertical, so the rows increase from the starting row, car.row: (row, col) (row + 1, col) (row + 2, col) (row + 3, col) (row + 4, col)
			for (k = 0; k < car.size; k++)
			{
			car.col[k] = car_col_ptr;
			car.row[k] = car_row_ptr++;
			player_board[car.row[k]][car.col[k]] = 'c';
			}
		}
		if (bs.direction == 0)
		{//Battleship is horizontal
			for (k = 0; k < bs.size; k++)
			{
			bs.col[k] = bs_col_ptr++;
			bs.row[k] = bs_row_ptr;
			player_board[bs.row[k]][bs.col[k]] = 'b';
			}
		}
		else if (bs.direction == 1)
		{//Battleship is vertical
			for (k = 0; k < bs.size; k++)
			{
			bs.col[k] = bs_col_ptr;
			bs.row[k] = bs_row_ptr++;
			player_board[bs.row[k]][bs.col[k]] = 'b';
			}
		}
		if (sub.direction == 0)
		{//Submarine is horizontal
			for (k = 0; k < sub.size; k++)
			{
			sub.col[k] = sub_col_ptr++;
			sub.row[k] = sub_row_ptr;
			player_board[sub.row[k]][sub.col[k]] = 's';
			}
		}
		else if (sub.direction == 1)
		{//Submarine is vertical
			for (k = 0; k < sub.size; k++)
			{
			sub.col[k] = sub_col_ptr;
			sub.row[k] = sub_row_ptr++;
			player_board[sub.row[k]][sub.col[k]] = 's';
			}
		}
		if (cru.direction == 0)
		{//Cruiser is horizontal
			for (k = 0; k < cru.size; k++)
			{
			cru.col[k] = cru_col_ptr++;
			cru.row[k] = cru_row_ptr;
			player_board[cru.row[k]][cru.col[k]] = 'r';
			}
		}
		else if (cru.direction == 1)
		{//Cruiser is vertical
			for (k = 0; k < cru.size; k++)
			{
			cru.col[k] = cru_col_ptr;
			cru.row[k] = cru_row_ptr++;
			player_board[cru.row[k]][cru.col[k]] = 'r';
			}
		}
		if (des.direction == 0)
		{//Destroyer is horizontal
			for (k = 0; k < des.size; k++)
			{
			des.col[k] = des_col_ptr++;
			des.row[k] = des_row_ptr;
			player_board[des.row[k]][des.col[k]] = 'd';
			}
		}
		else if (des.direction == 1)
		{//Destroyer is vertical
			for (k = 0; k < des.size; k++)
			{
			des.col[k] = des_col_ptr;
			des.row[k] = des_row_ptr++;
			player_board[des.row[k]][des.col[k]] = 'd';
			}
		}
	//The coordinates of the ships are written into new_battleship.log
	fprintf(write, "Player's Placement Coordinates\n");
	write_ships_down(write, car, bs, sub, cru, des);
	fprintf(write, "Computer's Placement Coordinates\n");
	write_ships_down(write, comp_car, comp_bs, comp_sub, comp_cru, comp_des);
	//The player who goes first is decided
	starter = starting_player();
	system("pause");
	system("cls");
	while (player.hits != 17 || computer.hits != 17)
	{
		switch(starter)
		{
			case 0: //Computer goes first
				printf("PLAYER BOARD\n");
				print_game_board(player_board, ROWS, COLS);
				computer_guess(comp_guess, &prev_row_ptr, &prev_col_ptr, &comp_row_ptr, &comp_col_ptr);
				comp_row = comp_row_ptr;
				comp_col = comp_col_ptr;
				prev_row = prev_row_ptr;
				prev_col = prev_col_ptr;
				printf("Computer guessed %d, %d\n", comp_row, comp_col);
				fprintf(write, "Computer Guess: %d %d. ", comp_row, comp_col);
				status = hit_or_miss(player_board, car, bs, sub, cru, des, &p_car_hits, &p_bs_hits, &p_sub_hits, &p_cru_hits, &p_des_hits, comp_row, comp_col);
				car.hits = p_car_hits;
				bs.hits = p_bs_hits;
				sub.hits = p_sub_hits;
				cru.hits = p_cru_hits;
				des.hits = p_des_hits;
				is_sunk(car, bs, sub, cru, des);
				if (status == 1)
				{
					fprintf(write, "Guess was a hit.\n");
				}
				else
				{
					fprintf(write, "Guess was a miss.\n");
				}
				update_stat(status, &comp_hits_ptr, &comp_misses_ptr, 1, write); //Updates computer's hit/miss ratio
				computer.hits = comp_hits_ptr;
				computer.misses = comp_misses_ptr;
				printf("PLAYER BOARD\n");
				print_game_board(player_board, ROWS, COLS);
				printf("%d Hits\n%d Misses\n", computer.hits, computer.misses);
				system("pause");
				system("cls");
				printf("COMPUTER BOARD\n");
				print_game_board(computer_board, ROWS, COLS);
				printf("Enter your guess in the format row, column (not including the comma): ");
				scanf("%d%d", &player_row, &player_col);
				fprintf(write, "Player Guess: %d %d. ", player_row, player_col);
				status = hit_or_miss(computer_board, comp_car, comp_bs, comp_sub, comp_cru, comp_des, &c_car_hits, &c_bs_hits, &c_sub_hits, &c_cru_hits, &c_des_hits, player_row, player_col);
				comp_car.hits = c_car_hits;
				comp_bs.hits = c_bs_hits;
				comp_sub.hits = c_sub_hits;
				comp_cru.hits = c_cru_hits;
				comp_des.hits = c_des_hits;
				is_sunk(comp_car, comp_bs, comp_sub, comp_cru, comp_des);
				if (status == 1)
				{
					fprintf(write, "Guess was a hit.\n");
				}
				else
				{
					fprintf(write, "Guess was a miss.\n");
				}
				update_stat(status, &player_hits_ptr, &player_misses_ptr, 2, write); //Updates player's hit/miss ratio
				player.hits = player_hits_ptr;
				player.misses = player_misses_ptr;
				printf("COMPUTER BOARD\n");
				print_game_board(computer_board, ROWS, COLS);
				printf("%d Hits\n%d Misses\n", player.hits, player.misses);
				system("pause");
				system("cls");
				break;

			default:
				//Player goes first
				printf("COMPUTER BOARD\n");
				print_game_board(computer_board, ROWS, COLS);
				printf("Enter your guess in the format row, column (not including the comma): ");
				scanf("%d%d", &player_row, &player_col);
				fprintf(write, "Player Guess: %d %d. ", player_row, player_col);
				status = hit_or_miss(computer_board, comp_car, comp_bs, comp_sub, comp_cru, comp_des, &c_car_hits, &c_bs_hits, &c_sub_hits, &c_cru_hits, &c_des_hits, player_row, player_col);
				comp_car.hits = c_car_hits;
				comp_bs.hits = c_bs_hits;
				comp_sub.hits = c_sub_hits;
				comp_cru.hits = c_cru_hits;
				comp_des.hits = c_des_hits;
				is_sunk(comp_car, comp_bs, comp_sub, comp_cru, comp_des);
				if (status == 1)
				{
					fprintf(write, "Guess was a hit.\n");
				}
				else
				{
					fprintf(write, "Guess was a miss.\n");
				}
				update_stat(status, &player_hits_ptr, &player_misses_ptr, 2, write); //Updates player's hits/miss ratio
				player.hits = player_hits_ptr;
				player.misses = player_misses_ptr;
				printf("COMPUTER BOARD\n");
				print_game_board(computer_board, ROWS, COLS);
				system("pause");
				system("cls");
				printf("%d Hits\n%d Misses\n", player.hits, player.misses);
				printf("PLAYER BOARD\n");
				print_game_board(player_board, ROWS, COLS);
				//The computer generates a guess based on the previous guess. If the previous guess was a hit, it guesses the same row, col + 1 or row +1, col. If that's a miss, it guesses the same row, col - 2 or row - 2, col
				computer_guess(comp_guess, &prev_row_ptr, &prev_col_ptr, &comp_row_ptr, &comp_col_ptr);
				comp_row = comp_row_ptr;
				comp_col = comp_col_ptr;
				prev_row = prev_row_ptr;
				prev_col = prev_col_ptr;
				printf("Computer guessed %d, %d\n", comp_row, comp_col);
				fprintf(write, "Computer Guess: %d %d. ", comp_row, comp_col);
				status = hit_or_miss(player_board, car, bs, sub, cru, des, &p_car_hits, &p_bs_hits, &p_sub_hits, &p_cru_hits, &p_des_hits, comp_row, comp_col);
				car.hits = p_car_hits;
				bs.hits = p_bs_hits;
				sub.hits = p_sub_hits;
				cru.hits = p_cru_hits;
				des.hits = p_des_hits;
				is_sunk(car, bs, sub, cru, des);
				if (status == 1)
				{
					fprintf(write, "Guess was a hit.\n");
				}
				else
				{
					fprintf(write, "Guess was a miss.\n");
				}
				update_stat(status, &comp_hits_ptr, &comp_misses_ptr, 1, write); //Updates computer's hits/miss ratio
				computer.hits = comp_hits_ptr;
				computer.misses = comp_misses_ptr;
				printf("PLAYER BOARD\n");
				print_game_board(player_board, ROWS, COLS);
				printf("%d Hits\n%d Misses\n", computer.hits, computer.misses);
				system("pause");
				system("cls");
				break;
			}
	}
	//When the computer or the player gets 17 hits, they won and the game ends
	if (player.hits == 17)
	{
		printf("Player wins!\n");
		player.wins++;
		computer.losses++;
	}
	else if (computer.hits == 17)
	{
		printf("Computer wins!\n");
		computer.wins++;
		player.losses++;
	}
	player.hit_miss_ratio = (double)player.hits/player.misses;
	computer.hit_miss_ratio = (double)computer.hits/computer.misses;
	fprintf(write, "Player has %d wins and %d losses with %lf hit/miss ratio\nComputer has %d wins and %d losses with %lf hit/miss ratio\n", player.wins, player.losses, player.hit_miss_ratio, computer.wins, computer.losses, computer.hit_miss_ratio);
	return 0;
}
 
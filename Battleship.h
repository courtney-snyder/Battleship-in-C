#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ROWS 10
#define COLS 10

typedef struct ship
{
	int direction;
	int size;
	int row[5];
	int col[5]; //Coordinates are entered in as row, col. Max size is 10 because the largest ship is the carrier, which is 5 spaces or 10 coordinates
	int hits;
	int sunk;
} Ship;

typedef struct stat
{
	int hits;
	int misses;
	double hit_miss_ratio;
	int wins;
	int losses;
} Stat;

void welcome_screen(int choice);
void print_rules();
void create_game_board(char board[ROWS][COLS], int rows, int cols);
void print_game_board(char board[ROWS][COLS], int rows, int cols);
int starting_player();
void who_starts(int player_guess);
void total_place_function(int choice, Ship car, Ship bs, Ship sub, Ship cru, Ship des, int *car_dir_ptr, int *car_row_ptr, int *car_col_ptr, int *bs_dir_ptr, int *bs_row_ptr, int *bs_col_ptr, int *sub_dir_ptr, int *sub_row_ptr, int *sub_col_ptr, int *cru_dir_ptr, int *cru_row_ptr, int *cru_col_ptr, int *des_dir_ptr, int *des_row_ptr, int *des_col_ptr);
void manually_place_ships(int car_direction, int bs_direction, int sub_direction, int cru_direction, int des_direction, int*car_dir_ptr, int*bs_dir_ptr, int*sub_dir_ptr, int*cru_dir_ptr, int*des_dir_ptr);
void randomly_place_ships(int car_direction, int bs_direction, int sub_direction, int cru_direction, int des_direction, int*car_dir_ptr, int*bs_dir_ptr, int*sub_dir_ptr, int*cru_dir_ptr, int*des_dir_ptr);
void random_starting_point(Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr);
void manual_starting_point(Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr);
void write_ships_down(FILE *write, Ship car, Ship bs, Ship sub, Ship cru, Ship des);
void read_coords(FILE*read, int*row, int*col);
int hit_or_miss(char opponents_board[ROWS][COLS], Ship opponents_car, Ship opponents_bs, Ship opponents_sub, Ship opponents_cru, Ship opponents_des, int*car_hits, int*bs_hits, int*sub_hits, int*cru_hits, int*des_hits, int row, int col);
void computer_guess(int hit_or_miss, int *previous_row_guess, int *previous_col_guess, int*row_guess, int*col_guess);
void update_stat(int hit_or_miss, int*hits, int*misses, int computer_or_player, FILE*write);
void is_sunk(Ship opponents_car, Ship opponents_bs, Ship opponents_sub, Ship opponents_cru, Ship opponents_des);
void populate_coordinates(Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr);
void check_for_overlap (Ship car, Ship bs, Ship sub, Ship cru, Ship des, int*car_row_ptr, int*car_col_ptr, int*bs_row_ptr, int*bs_col_ptr, int*sub_row_ptr, int*sub_col_ptr, int*cru_row_ptr, int*cru_col_ptr, int*des_row_ptr, int*des_col_ptr, int*new_car_row_ptr, int*new_car_col_ptr, int*new_bs_row_ptr, int*new_bs_col_ptr, int*new_sub_row_ptr, int*new_sub_col_ptr, int*new_cru_row_ptr, int*new_cru_col_ptr, int*new_des_row_ptr, int*new_des_col_ptr);

#endif
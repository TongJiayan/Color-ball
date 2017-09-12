/*童佳燕 计算机科学与技术1班*/
#pragma once
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<iomanip>
#include<conio.h>

void print_menu();
void print(int(*p)[10], int rows, int cols, int(*rout)[2], int leap = 0, int leap_2 = 0);//打印内部数组函数//默认参数值leap, leap_2
void end();//打印结束语
void check_rows_cols(int *rc);
void init(int *rows, int *cols, int(*p)[10], int n);
void next_balls(int *next_balls);
void input_position(int(*p)[10], int rows, int cols, char *begin, char *final);
int search(int(*p)[10], int(*rout)[2], int x1, int y1, int x2, int y2, int rows, int cols, int *num_pace);
void print_console1(int rows, int cols, int(*p)[10]);
void print_console2(const int rows, const int cols, int(*p)[10]);
void print_console3(const int rows, const int cols, int next[], int leap);
void print_rout(int rows, int cols, int(*rout)[2], int(*p)[10]);
void judge(int(*p)[10], char final[2], const int rows, const int cols, int *score, int *eve_score);
void bgn_fnl_mouse(char begin[2], char final[2], int rows, int cols, int Y, int p[][10]);
void move_img(int p[][10], int rout[][2], char begin[2], char final[2], int rows, int cols, int Y);
int game_over(int(*p)[10], const int *row_ptr, const int *col_ptr,int Y);
void update_array(int(*p)[10], int next[], const int *col_ptr, const int *row_ptr, int move_img);
void reset_array(int(*p)[10], const int *col_ptr, const int *row_ptr);
void show_rout(int rout[][2], int begin_value);
void one(int(*p)[10]);
void two(int(*p)[10]);
void three(int(*p)[10]);
void four(int(*p)[10]);
void five(int(*p)[10]);
void six(int(*p)[10]);
void seven(int(*p)[10]);
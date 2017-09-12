#pragma once
#include <Windows.h>

/* 定义颜色（用宏定义取代数字，方便记忆） */
#define COLOR_BLACK		0	//黑
#define COLOR_BLUE		1	//蓝
#define COLOR_GREEN		2	//绿
#define COLOR_CYAN		3	//青
#define COLOR_RED		4	//红
#define COLOR_PINK		5	//粉
#define COLOR_YELLOW	6	//黄
#define COLOR_WHITE		7	//白
#define COLOR_HBLACK	8	//亮黑
#define COLOR_HBLUE		9	//亮蓝
#define COLOR_HGREEN	10	//亮绿
#define COLOR_HCYAN		11	//亮青
#define COLOR_HRED		12	//亮红
#define COLOR_HPINK		13	//亮粉
#define COLOR_HYELLOW	14	//亮黄
#define COLOR_HWHITE	15	//亮白

/* 定义鼠标的操作 */
#define MOUSE_NO_ACTION						0	//无鼠标操作
#define MOUSE_LEFT_BUTTON_CLICK				1	//按下左键
#define MOUSE_LEFT_BUTTON_DOUBLE_CLICK		2	//双击左键
#define MOUSE_RIGHT_BUTTON_CLICK			3	//按下右键
#define MOUSE_RIGHT_BUTTON_DOUBLE_CLICK	4	//双击右键
#define MOUSE_LEFTRIGHT_BUTTON_CLICK		5	//同时按下左右键
#define MOUSE_ONLY_MOVED					6	//鼠标移动

/* 定义光标的形态 */
#define CURSOR_VISIBLE_FULL			0	//光标显示，全高色块
#define CURSOR_VISIBLE_HALF			1	//光标显示，半高色块
#define CURSOR_VISIBLE_NORMAL		2	//光标显示，横线（缺省为此方式）
#define CURSOR_INVISIBLE			3	//光标不显示

/* cmd_console_tools下的函数声明 */
void setcolor(const HANDLE hout, const int bg_color, const int fg_color);
void getcolor(const HANDLE hout, int &bg_color, int &fg_color);
void gotoxy(const HANDLE hout, const int X, const int Y);
void getxy(const HANDLE hout, int &x, int &y);
void setcursor(const HANDLE hout, const int options);
void showch(const HANDLE hout, const int X, const int Y, const char ch, const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE, const int n = 1);
void showstr(const HANDLE hout, const int X, const int Y, const char *str, const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE);
void setconsoleborder(const HANDLE hout, const int cols, const int lines, const int buffer_lines = -1);
void getconsoleborder(const HANDLE hout, int &cols, int &lines, int &buffer_coles, int &buffer_lines);
void setfontsize(const HANDLE hout, const wchar_t *fontname, const int fontsize);
void enable_mouse(const HANDLE hin);
int  read_mouse(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved = 1);
#pragma once
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
函数名称：
功    能：设置指定的颜色
输入参数：const HANDLE hout  ：cmd窗口句柄
const int bg_color ：背景色（0-15）
const int fg_color ：前景色（0-15）
返 回 值：
说    明：颜色的取值由背景色+前景色组成，各16种
fg_color：0-7    黑   蓝   绿   青   红   粉   黄   白
8-15 亮黑 亮蓝 亮绿 亮青 亮红 亮粉 亮黄 亮白
bg_color：0-7    黑   蓝   绿   青   红   粉   黄   白
8-15 亮黑 亮蓝 亮绿 亮青 亮红 亮粉 亮黄 亮白
最终的颜色为 背景色*16+前景色
***************************************************************************/
void setcolor(const HANDLE hout, const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}

/***************************************************************************
函数名称：
功    能：取当前设置的前景色和背景色
输入参数：const HANDLE hout  ：cmd窗口句柄
int &bg_color      ：返回的背景色（0-15）
int &fg_color      ：返回的前景色（0-15）
返 回 值：
说    明：返回最后一次setcolor的前景色和背景色
***************************************************************************/
void getcolor(const HANDLE hout, int &bg_color, int &fg_color)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	bg_color = binfo.wAttributes / 16;
	fg_color = binfo.wAttributes % 16;
}

/***************************************************************************
函数名称：
功    能：将光标移动到指定位置
输入参数：const HANDLE hout ：cmd窗口句柄
const int X       ：X轴坐标（列）
const int Y       ：Y轴坐标（行）
返 回 值：
说    明：屏幕左上角坐标为(0,0)，在cmd窗口的大小未被调整的情况下，缺省为：
横向x轴，对应列(0-79)
纵向y轴，对应行(0-24)
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
函数名称：
功    能：取当前光标所在位置的坐标值
输入参数：const HANDLE hout ：cmd窗口句柄
int &x            ：取得的X轴坐标（列）
int &y            ：取得的Y轴坐标（行）
返 回 值：
说    明：形参中的&表示引用，第六章会讲到，引用形参的值可以返回给实参
***************************************************************************/
void getxy(const HANDLE hout, int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	x = binfo.dwCursorPosition.X;
	y = binfo.dwCursorPosition.Y;

	return;
}

/***************************************************************************
函数名称：
功    能：设置光标状态（显示/不显示/全高/半高/横线等）
输入参数：const HANDLE hout ：cmd窗口句柄
const int X       ：X轴坐标（列）
const int Y       ：Y轴坐标（行）
const char ch     ：要输出的字符值
返 回 值：
说    明：X、Y的范围参见gotoxy函数的说明
***************************************************************************/
void setcursor(const HANDLE hout, const int options)
{
	CONSOLE_CURSOR_INFO cursor_info;

	switch (options) {
	case CURSOR_VISIBLE_FULL:
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 100;
		break;
	case CURSOR_VISIBLE_HALF:
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 50;
		break;
	case CURSOR_INVISIBLE:
		cursor_info.bVisible = 0;
		cursor_info.dwSize = 1;
		break;
	case CURSOR_VISIBLE_NORMAL:
	default: //缺省显示光标，横线
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 25;
		break;
	}
	SetConsoleCursorInfo(hout, &cursor_info);
}

/***************************************************************************
函数名称：
功    能：在指定位置，用指定颜色，显示一个字符若干次
输入参数：const HANDLE hout ：cmd窗口句柄
const int X       ：X轴坐标（列）
const int Y       ：Y轴坐标（行）
const char ch     ：要输出的字符值
返 回 值：
说    明：X、Y的范围参见gotoxy函数的说明
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch, const int bg_color, const int fg_color, const int n)
{
	int i;
	gotoxy(hout, X, Y);
	setcolor(hout, bg_color, fg_color);

	/* 循环n次，打印字符ch */
	for (i = 0; i<n; i++)
		putchar(ch);
}

/***************************************************************************
函数名称：
功    能：在指定位置，用指定颜色，显示一个字符串
输入参数：
返 回 值：
说    明：
***************************************************************************/
void showstr(const HANDLE hout, const int X, const int Y, const char *str, const int bg_color, const int fg_color)
{
	const char *p;
	gotoxy(hout, X, Y);
	setcolor(hout, bg_color, fg_color);
	for (p = str; *p; p++)
		putchar(*p);
}

/***************************************************************************
函数名称：
功    能：改变cmd窗口的大小
输入参数：const HANDLE hout ：cmd窗口句柄
const int cols    : 新的列数
const int lines   ：新的行数
返 回 值：
说    明：
***************************************************************************/
void setconsoleborder(const HANDLE hout, const int cols, const int lines, const int buffer_lines)
{
	char cmd[80];

	/* 恢复为背景色0、前景色白（cmd窗口的缺省值）*/
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	system("cls");	//清屏

	sprintf(cmd, "mode con cols=%d lines=%d", cols, lines);
	system(cmd); //设置新的大小

				 /* 设置屏幕缓冲区的大小（缺省则与屏幕高度一致，不用设置）*/
	if (buffer_lines >= lines) {
		COORD cr;
		cr.X = cols;
		cr.Y = buffer_lines;
		SetConsoleScreenBufferSize(hout, cr); //设置cmd窗口的屏幕缓冲区的大小
	}

	return;
}

/***************************************************************************
函数名称：
功    能：取当前cmd窗口的大小设置
输入参数：const HANDLE hout ：cmd窗口句柄
int &cols         ：当前窗口的列数-返回值
int &lines        ：当前窗口的行数-返回值
int &buffer_cols  ：当前缓冲区的列数-返回值
int &buffer_lines ：当前缓冲区的行数-返回值
返 回 值：
说    明：
***************************************************************************/
void getconsoleborder(const HANDLE hout, int &cols, int &lines, int &buffer_cols, int &buffer_lines)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	cols = binfo.dwMaximumWindowSize.X;	//可见窗口的列数
	lines = binfo.dwMaximumWindowSize.Y;   //可见窗口的行数
	buffer_cols = binfo.dwSize.X;         //缓冲区的列数
	buffer_lines = binfo.dwSize.Y;			//缓冲区的行数
}

/***************************************************************************
函数名称：
功    能：改变输出窗口的字体
输入参数：
返 回 值：
说    明：
***************************************************************************/
void setfontsize(const HANDLE hout, const wchar_t *fontname, const int fontsize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = fontsize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, fontname);	//字体
	SetCurrentConsoleFontEx(hout, NULL, &info);
}

/***************************************************************************
函数名称：
功    能：允许使用鼠标
输入参数：const HANDLE hin ：cmd窗口输入句柄
返 回 值：
说    明：某些cmd窗口控制语句执行后，可能会取消鼠标支持，则调用本函数回再次加入
***************************************************************************/
void enable_mouse(const HANDLE hin)
{
	DWORD Mode;

	GetConsoleMode(hin, &Mode);	/* 取得控制台原来的模式 */
	SetConsoleMode(hin, Mode | ENABLE_MOUSE_INPUT);	//加入鼠标支持（可能原先已支持鼠标，再加也没错）
}

/***************************************************************************
函数名称：
功    能：读鼠标按键
输入参数：const HANDLE hout ：cmd窗口句柄
返 回 值：
说    明：下列说明来自鼠标定义文件
01.typedef struct _MOUSE_EVENT_RECORD      //鼠标事件结构体
02.{
03.    COORD dwMousePosition;      //当前鼠标在控制台窗口缓冲区的位置
04.    DWORD dwButtonState;        //鼠标按键的状态
05.    DWORD dwControlKeyState;    //控制键状态
06.    DWORD dwEventFlags;         //鼠标事件类型
07.} MOUSE_EVENT_RECORD;
08.
09.其中鼠标按键状态dwButtonState可能的值有
10.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
11.FROM_LEFT_1ST_BUTTON_PRESSED        最左边的鼠标键被按下      一般来说就是鼠标左键
12.FROM_LEFT_2ND_BUTTON_PRESSED        左起第二个鼠标键被按下    一般来说是鼠标中键，就是滚轮键
13.FROM_LEFT_3RD_BUTTON_PRESSED        左起第三个鼠标键被按下
14.FROM_LEFT_4TH_BUTTON_PRESSED        左起第四个鼠标键被按下
15.RIGHTMOST_BUTTON_PRESSED            最右边的鼠标键被按下      一般来说是鼠标右键
16.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
17.控制键状态dwControlKeyState与键盘事件的一样
18.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
19.ENHANCED_KEY        扩展键被按下
20.LEFT_ALT_PRESSED    左Alt键被按下
21.LEFT_CTRL_PRESSED   左Ctrl键被按下
22.RIGHT_ALT_PRESSED   右Alt键被按下
23.RIGHT_CTRL_PRESSED  右Ctrl键被按下
24.NUMLOCK_ON          数字锁定被打开
25.SCROLLLOCK_ON       滚动锁定被打开
26.CAPSLOCK_ON         大写锁定被打开
27.SHIFT_PRESSED       Shift键被按下
28.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
29.鼠标事件类型dwEventFlags有以下几种
30.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
31.DOUBLE_CLICK            双击，第一击只作为普通按键事件，第二击才作为双击事件
32.MOUSE_HWHEELED          水平鼠标滚轮移动
33.MOUSE_MOVED             鼠标移动
34.MOUSE_WHEELED           垂直鼠标滚轮移动
35.0                       当鼠标有键被按下或者释放
***************************************************************************/
int read_mouse(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos;

	while (1) {
		/* 从hin中读输入状态（包括鼠标、键盘等） */
		ReadConsoleInput(hin, &mouseRec, 1, &res);
		/* 忽略所有非鼠标事件，包括键盘 */
		if (mouseRec.EventType != MOUSE_EVENT)
			continue;

		/* 从返回中读鼠标指针当前的坐标 */
		crPos = mouseRec.Event.MouseEvent.dwMousePosition;
		X = crPos.X;
		Y = crPos.Y;

		if (enable_read_mouse_moved && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			return MOUSE_ONLY_MOVED;

		if (mouseRec.Event.MouseEvent.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)) { //同时按下左右键
			return MOUSE_LEFTRIGHT_BUTTON_CLICK;
		}
		else if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //按下左键
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_LEFT_BUTTON_CLICK;
		}
		else if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { //按下右键
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_RIGHT_BUTTON_CLICK;
		}
		else //忽略其它按键操作（如果需要滚轮，则判断 FROM_LEFT_2ND_BUTTON_PRESSED）
			;
	} //end of while(1)

	return MOUSE_NO_ACTION; //此句应该执行不到，为避免某些编译器报不完全分支错误，加
}
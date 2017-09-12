/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b2.h"
#include"cmd_console_tools.h"
using namespace std;
void four(int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int rows, cols;
	int rout[81][2];
	init(&rows, &cols, p, 5);
	const int *const row_ptr = &rows;
	const int *const col_ptr = &cols;
	print(p, *row_ptr, *col_ptr, rout);
	cout << endl;
	cout << "按回车键显示图形...";
	while (_getch() != '\r')
		;
	system("cls");
	print_console1(*row_ptr, *col_ptr, p);

}
void five(int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int rows, cols;
	int rout[81][2];
	init(&rows, &cols, p, 5);
	const int *const row_ptr = &rows;
	const int *const col_ptr = &cols;
	print(p, *row_ptr, *col_ptr, rout);
	cout << endl;
	cout << "按回车键显示图形...";
	while (_getch() != '\r')
		;
	system("cls");
	print_console2(*row_ptr, *col_ptr, p);
	end();
}

void six(int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
	int rows, cols;
	int rout[81][2];
	char begin[2], final[2];
	init(&rows, &cols, p, 100);//初始化 100代表生成百分之六十的球
	const int *const row_ptr = &rows;
	const int *const col_ptr = &cols;
	print_console2(*row_ptr, *col_ptr, p);//打印有分割线的棋盘
	int X = 0, Y = 0;
	getxy(hout, X, Y);
	setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
	move_img(p, rout, begin, final, *row_ptr, *col_ptr, Y);
	setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
	gotoxy(hout, 0, Y + 1);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
	end();
}

void seven(int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	int rows, cols, X, Y;//X,Y用于存放打印完棋盘后的光标坐标，方便打印结束语
	char begin[2], final[2];//存放鼠标输入的起点坐标和终点坐标
	int next[3], rout[81][2];//next用于存放下一轮将会出现的球的信息；rout用于存放寻到的路上的点坐标
	init(&rows, &cols, p, 5);//初始化内部数组+随机产生5个球
	const int *row_ptr = &rows;//防止不小心对cols rows篡改
	const int *col_ptr = &cols;
	int score = 0, eve_score = 0;//总得分，每次得分
	int leap = 0;
	print_console2(rows, cols, p);//打印棋盘
	getxy(hout, X, Y);
	print_console3(rows, cols, next, 0);//打印得分，预示等
	for (int i = 0; i < 3; i++)
		next[i] = rand() % 7;
	print_console3(rows, cols, next, 4);
	while (1)
	{
		int num_pace = 0;
		bgn_fnl_mouse(begin, final, rows, cols, Y, p);//输入起点和终点的坐标
		int begin_value = p[begin[0] - 'A'][begin[1] - '1'];//将起点值先存起来，寻完路后再赋给终点，防止寻路过程中值被“破坏
		if (search(p, rout, begin[1] - '1', begin[0] - 'A', final[1] - '1', final[0] - 'A', *row_ptr, *col_ptr, &num_pace))
		{//search返回1代表寻到路，否则没寻到路！但不论是否寻到路，这个函数中的操作已经执行，也就是路径上的点的值已被改变
			reset_array(p, col_ptr, row_ptr);//search是吧探索过的店全都变成了-1要变回来，包括起始点
			p[final[0] - 'A'][final[1] - '1'] = begin_value;
			show_rout(rout, begin_value);//把存在rout里的路径上的点坐标按顺序（加延时）显示，即移动路径
			for (int i = 0; i < 81; i++)
				for (int j = 0; j < 2; j++)
					rout[i][j] = -1;//清空存储的路径记录
			judge(p, final, *row_ptr, *col_ptr, &score, &eve_score);//判断能否得分，若得分，设置为0，更新内部数组
			if (eve_score == 0)
			{
				update_array(p, next, col_ptr, row_ptr, 1);//将next中存的值随机赋给"棋盘"中空白的位置，也就是给内部数组p
				for (int i = 0; i < 3; i++)
					next[i] = rand() % 7+1;////
				print_console3(rows, cols, next, 4);//4用于控制打印位置
			}
			else
			{/*遍历棋盘，把刚消去球的位置打印空格*/
				for (int i = 0; i < rows; i++)
					for (int j = 0; j < cols; j++)
						if (p[i][j] == 0)
							showstr(hout, 2 + j * 4, (i + 1) * 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
				setcolor(hout, COLOR_HWHITE, COLOR_BLACK);
				gotoxy(hout, 4 * cols + 12, 2);
				cout << score;
			}
		}
		else//如果没有找到路
		{
			p[begin[0] - 'A'][begin[1] - '1']=begin_value;
			showstr(hout, 2 +(begin[1] - '1') * 4, (begin[0] - 'A' + 1) * 2, "○", begin_value + 1, COLOR_HWHITE);
			reset_array(p, col_ptr, row_ptr);
			continue;
		}
		if (game_over(p, row_ptr, col_ptr,Y-1))
			break;
	}
	end();
}
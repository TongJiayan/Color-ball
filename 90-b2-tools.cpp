/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b2.h"
#include"cmd_console_tools.h"
using namespace std;

/*打印菜单*/
void print_menu()
{
	cout << "-------------------------------------" << endl;
	cout << "1.内部数组，随机生成初始5个球" << endl;
	cout << "2.内部数组，随机生成60%的球，寻找移动路径" << endl;
	cout << "3.内部数组，完整版" << endl;
	cout << "4.画出n*n的框架（无分割线），随机显示5个球" << endl;
	cout << "5.画出n*n的框架（有分割线），随机显示5个球" << endl;
	cout << "6.9*9的框架，50个球，完成一次移动" << endl;
	cout << "7.cmd图形界面完整版" << endl;
	cout << "0.退出" << endl;
	cout << "--------------------------------------" << endl;
}

/*初始化数组，包括行数，列数，以及内部的值*/
void init(int *rows, int *cols, int(*p)[10], int n)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	cout << "请输入行数（7-9）";
	cin >> *rows;
	check_rows_cols(rows);//对rows进行判断，如果不合适，重新要求输入，同时更新行数和列数

	cout << "请输入列数（7-9）";
	cin >> *cols;
	check_rows_cols(cols);

	cout << "\n初始数组:" << endl;

	/*先全部初始化为0*/
	int(*q)[10];
	int *w;
	for (q = p; q < p + *rows; q++)
		for (w = *q; w < *q + *cols; w++)
			*w = 0;

	/*随机生成小球，随机分布*/
	for (int i = 0; i < n && i<(*rows)*(*cols)*0.6;)//n用来控制打印5个还是60%个球
	{
		int x = rand() % *cols;
		int y = rand() % *rows;
		if (*(*(p + y) + x) == 0)
		{
			*(*(p + y) + x) = rand() % 7 + 1;
			i++;
		}
	}
}

/*打印内部数组*/
void print(int(*p)[10], int rows, int cols, int(*rout)[2], int leap, int leap_2)//打印内部数组
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "  |";
	for (int i = 1; i <= cols; i++)
		cout << setw(3) << i;
	cout << endl;
	cout << "----";
	for (int i = 1; i <= cols; i++)
		cout << "---";
	cout << endl;
	int(*q)[10];
	int *w;
	char c = 65;
	for (q = p; q < p + rows; q++)
	{
		cout << c << setw(2) << "|";
		for (w = *q; w < *q + cols; w++)
		{
			cout << "  ";
			if (leap == 0)//leap=0---对应不输出*的内部数组，以色块来显示对应小球
			{
				if (*w != 0)
					setcolor(hout, 7, *w + 7);
				cout << *w;
			}
			else
			{
				int judge = 0;
				for (int num_pace = 0; num_pace < 81; num_pace++)
					if (q - p == rout[num_pace][0] && w - *q == rout[num_pace][1])
					{
						judge = 1;
						if (leap_2 == 0)//leap_2==0对应打印不带颜色的路径，即用*代表路径  leap_2!=0对应用带颜色的色块代表路径
							cout << '*';
						else
						{
							setcolor(hout, COLOR_HYELLOW, COLOR_HBLUE);
							cout << *w;
						}
						break;
					}
				if (judge == 0)
				{
					setcolor(hout, 0, 7);
					if (leap_2 == 0)
						cout << 0;
					else
						cout << *w;
				}
			}
			setcolor(hout, 0, 7);
		}
		c++;
		cout << endl;
	}
}

/*打印结束语，输入End进行判断*/
void end()
{
	int a, b;
	int &x = a, &y = b;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	cout << "\n本小题结束，请输入End继续...";
	char End[4];//存放输入的字符
	for (int i = 0; i < 3; i++)
		cin >> End[i];
	End[3] = '\0';//加入尾零来控制字符串的输出
	if (strcmp("End", End))//比较字符串
	{
		cout << "输入错误，请重新输入";
		while (1)
		{
			getxy(hout, x, y);
			gotoxy(hout, 28, y - 1);
			cout << "        ";
			gotoxy(hout, 28, y - 1);
			for (int i = 0; i < 3; i++)
				cin >> End[i];
			End[3] = '\0';
			if (!(strcmp("End", End)))
				break;
		}
	}
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
	setconsoleborder(hout, 80, 21, 21);
	setfontsize(hout, L"新宋体", 15);
}

//对输入行列进行检查  rc是指向
void check_rows_cols(int *rc)
{
	int a, b;
	int &x = a;
	int &y = b;
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (*rc < 7 || *rc>9)
	{
		cout << "输入错误，请重新输入.";
		getxy(hout, x, y);
		gotoxy(hout, 17, y - 1);
		cout << "  ";
		gotoxy(hout, 17, y - 1);
		cin >> *rc;
	}
	cout << endl;
}

/*随机生成三个小球，存在指针next_balls指向的地址，打印提示*/
void next_balls(int *next_balls)
{
	cout << "\n下三个彩球的颜色分别是： ";
	for (int i = 0; i < 3; i++)
	{
		next_balls[i] = rand() % 7 + 1;
		cout << next_balls[i] << "　";
	}
}

/*输入起点和终点的坐标信息 A-I,1-9 以字符数组形式输入，同时进行判断合法性*/
void input_position(int(*p)[10], int rows, int cols, char *begin, char *final)
{
	int n = 0;//用于控制输入为起点数据还是终点数据
	char po[2];
	while (n<2)
	{
		if (!n)
			cout << "\n请以字母+数字形式[例：c2]输入要移动球的矩阵目标： ";
		else
			cout << "\n请以字母+数字形式[例：c2]输入要移动球的目的目标： ";
		for (int i = 0; i < 2; i++)
			cin >> *(po + i);
		if (*po >= 'a'&&*po <= 'z')
			*po -= 32;
		if (*po >= 'A'&&*po <= 'A' + rows - 1 && *(po + 1) >= '1'&&*(po + 1) <= cols + '0')
		{
			if (*(*(p + *po - 'A') + *(po + 1) - '1') == 0 && n == 0)
				cout << "起始位置为空，请重新输入：";
			else if (*(*(p + *po - 'A') + *(po + 1) - '1') != 0 && n == 1)
				cout << "目标位置为非空，请重新输入：";
			else
			{
				cout << "输入为" << *po << "行" << *(po + 1) << "列";
				if (!n)
					for (int i = 0; i < 2; i++)
						*(begin + i) = *(po + i);
				else
					for (int i = 0; i < 2; i++)
						*(final + i) = *(po + i);
				n++;
			}
		}
		else
			cout << "输入错误，请重新输入";
	}
}

/*寻路，把走过的点全都放进rout数组，返回值为int型，返回为0则找路不成功，1则找路成功*/
int search(int(*p)[10], int(*rout)[2], int x1, int y1, int x2, int y2, int rows, int cols, int *num_pace)
{
	if (x1 >= 0 && x1 < cols&&y1 >= 0 && y1 < rows)
	{
		if (x1 == x2&&y1 == y2)
		{
			rout[*num_pace][0] = y1;
			rout[*num_pace][1] = x1;
			(*num_pace)++;
			return 1;
		}
		else
			p[y1][x1] = -1;

		if (p[y1][x1 + 1] == 0)
		{
			search(p, rout, x1 + 1, y1, x2, y2, rows, cols, num_pace);
			if (*num_pace)
			{
				rout[*num_pace][0] = y1;
				rout[*num_pace][1] = x1;
				(*num_pace)++;
				return 1;
			}
		}
		if (p[y1 - 1][x1] == 0)
		{
			search(p, rout, x1, y1 - 1, x2, y2, rows, cols, num_pace);
			if (*num_pace)
			{
				rout[*num_pace][0] = y1;
				rout[*num_pace][1] = x1;
				(*num_pace)++;
				return 1;
			}
		}
		if (p[y1][x1 - 1] == 0)
		{
			search(p, rout, x1 - 1, y1, x2, y2, rows, cols, num_pace);
			if (*num_pace)
			{
				rout[*num_pace][0] = y1;
				rout[*num_pace][1] = x1;
				(*num_pace)++;
				return 1;
			}
		}
		if (p[y1 + 1][x1] == 0)
		{
			search(p, rout, x1, y1 + 1, x2, y2, rows, cols, num_pace);
			if (*num_pace)
			{
				rout[*num_pace][0] = y1;
				rout[*num_pace][1] = x1;
				(*num_pace)++;
				return 1;
			}
		}
		return 0;
	}
	else
		return 0;
}

/*判断是否满足游戏结束的条件*/
int game_over(int(*p)[10], const int *row_ptr, const int *col_ptr,int Y)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j, n = 0;
	for (i = 0; i < *row_ptr; i++)
	{
		for (j = 0; j < *col_ptr; j++)
			if (p[i][j] == 0)
			{
				n++;
				if (n >= 3)
					return 0;//0代表没有game over
			}
	}
	gotoxy(hout, 0, Y - 1);
	cout << "game over!";
	return 1;
}

/*如果没有得分，随机位置赋值上一轮预告的小球种类*/
void update_array(int(*p)[10], int next[], const int *col_ptr, const int *row_ptr, int move_img)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i <3;)
	{
		int x = rand() % *col_ptr;
		int y = rand() % *row_ptr;
		if (p[y][x] == 0)
		{
			p[y][x] = next[i];
			if (move_img == 1)
				showstr(hout, 2 + x * 4, y * 2 + 2, "○", p[y][x] + 1, COLOR_HWHITE);
			i++;
		}
	}
}

/*寻路过程中，对所有探索过的点都赋值为-1，寻路结束后，恢复为0*/
void reset_array(int(*p)[10], const int *col_ptr, const int *row_ptr)
{
	for (int i = 0; i < *row_ptr; i++)
		for (int j = 0; j < *col_ptr; j++)
			if (p[i][j]<0)
				p[i][j] = 0;
}

/*简单的组合print函数两种情况（0+*   数值+色块）下的输出*/
void print_rout(int rows, int cols, int(*rout)[2], int(*p)[10])
{
	cout << endl;
	cout << "移动路径（路径*表示）：\n";
	print(p, rows, cols, rout, 1);
	cout << endl << endl;
	cout << "移动路径（路径颜色标记）：\n";
	print(p, rows, cols, rout, 1, 1);
}

/*判断能否得分，记录每次得分，积累得分，如果能消除，数组内部进行消除*/
void judge(int(*p)[10], char final[2], const int rows, const int cols, int *score, int *eve_score)
{
	int new_chess = p[final[0] - 'A'][final[1] - '1'];
	int x = final[1] - '1', y = final[0] - 'A';
	int i1 = 1, i2 = 1, i3 = 1, i4 = 1, j1 = 1, j2 = 1, j3 = 1, j4 = 1, sum = 0;

	if (x >= 1 && new_chess == p[y][x - 1] || x<cols - 1 && new_chess == p[y][x + 1])
	{
		while (x - i1 >= 0 && p[y][x - i1] == new_chess)
			i1++;
		while (x + j1<cols&&p[y][x + j1] == new_chess)
			j1++;
	}
	if (y >= 1 && p[y - 1][x] == new_chess || y < rows - 1 && p[y + 1][x] == new_chess)
	{
		while (p[y - i2][x] == new_chess && y - i2 >= 0)
			i2++;
		while (p[y + j2][x] == new_chess && y + j2<rows)
			j2++;
	}
	if (x >= 1 && y >= 1 && p[y - 1][x - 1] == new_chess || x < cols - 1 && y < rows - 1 && new_chess == p[y + 1][x + 1])
	{
		while (p[y + i3][x + i3] == new_chess && y + i3<rows && x + i3<cols)
			i3++;
		while (p[y - j3][x - j3] == new_chess &&y - j3 >= 0 && x - j3 >= 0)
			j3++;
	}
	if (x<cols - 1 && y >= 1 && p[y - 1][x + 1] == new_chess || x >= 1 && y < rows - 1 && new_chess == p[y + 1][x - 1])
	{
		while (p[y - i4][x + i4] == new_chess && y - i4 >= 0 && x + i4<cols)
			i4++;
		while (p[y + j4][x - j4] == new_chess && x - j4 >= 0 && y + j4<rows)
			j4++;
	}
	if (i1 + j1 >= 6)
	{
		sum += (i1 + j1 - 1);
		for (int i = x + 1 - i1; i < x + j1; i++)
			p[y][i] = 0;
	}
	if (i2 + j2 >= 6)
	{
		sum += (i2 + j2 - 1);
		for (int i = y - i2 + 1; i < y + j2; i++)
			p[i][x] = 0;
	}
	if (i3 + j3 >= 6)
	{
		sum += (i3 + j3 - 1);
		for (int i = 1 - j3; i < i3; i++)
			p[y + i][x + i] = 0;
	}
	if (i4 + j4 >= 6)
	{
		sum += (i4 + j4 - 1);
		for (int i = 1 - i4; i<j4; i++)
			p[y + i][x - i] = 0;
	}

	if (sum)
	{
		*eve_score = (sum - 1)*(sum - 2);
		*score += (sum - 1)*(sum - 2);
	}
	else
		*eve_score = 0;
}

/*画没有分割线的棋盘*/
void print_console1(const int rows, const int cols, int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const int r = rows + 6;
	setconsoleborder(hout, 35, r, 35);
	setfontsize(hout, L"新宋体", 20);
	cout << "屏幕：" << rows + 6 << "行" << 35 << "列" << endl;
	setcursor(hout, CURSOR_VISIBLE_FULL);
	for (int i = 0; i < cols + 2; i++)
	{
		if (i == 0)
			showstr(hout, 2 * i, 1, "┍", COLOR_HWHITE, COLOR_BLACK);
		else if (i == cols + 1)
			showstr(hout, 2 * i, 1, "┑", COLOR_HWHITE, COLOR_BLACK);
		else
			showstr(hout, 2 * i, 1, "─", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i <cols + 2; i++)
	{
		if (i == 0)
			showstr(hout, 2 * i, rows + 2, "┕", COLOR_HWHITE, COLOR_BLACK);
		else if (i == cols + 1)
			showstr(hout, 2 * i, rows + 2, "┙", COLOR_HWHITE, COLOR_BLACK);
		else
			showstr(hout, 2 * i, rows + 2, "─", COLOR_HWHITE, COLOR_BLACK);
	}

	for (int j = 0; j < rows; j++)
	{
		showstr(hout, 0, 2 + j, "┃", COLOR_HWHITE, COLOR_BLACK);
		showstr(hout, 2 * (cols + 1), 2 + j, "┃", COLOR_HWHITE, COLOR_BLACK);
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (p[i][j] != 0)
				showstr(hout, 2 * (j + 1), i + 2, "○", p[i][j] + 1, COLOR_HWHITE);
			else
				showstr(hout, 2 * (j + 1), i + 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
		}
	cout << endl << endl;
	end();
}

/*画有分割线的棋盘*/
void print_console2(const int rows, const int cols, int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int r = rows * 2 + 5;
	int c = cols * 2 + 21;
	int bf_c, bf_r;
	getconsoleborder(hout, c, r, bf_c, bf_r);
	int x, y;
	setconsoleborder(hout, c, r, c);
	setfontsize(hout, L"新宋体", 20);
	cout << "屏幕：" << r << "行" << c << "列" << endl;
	setcursor(hout, CURSOR_VISIBLE_FULL);
	for (int i = 0; i < 2 * rows + 1; i++)
		for (int j = 0; j < 2 * cols + 1; j++)
		{
			if (i == 0)
			{
				if (j == 0)
					showstr(hout, 0, 1, "┍", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * cols)
					showstr(hout, j * 2, 1, "┑", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * cols - 1)
					showstr(hout, j * 2, 1, "─", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						showstr(hout, 2 * j, 1, "─", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, 1, "┯", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else if (i == 2 * rows)
			{
				if (j == 0)
					showstr(hout, 0, i + 1, "┕", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * cols)
					showstr(hout, j * 2, i + 1, "┙", COLOR_HWHITE, COLOR_BLACK);
				else if (j == 2 * cols - 1)
					showstr(hout, j * 2, i + 1, "─", COLOR_HWHITE, COLOR_BLACK);
				else
				{
					if (j % 2 == 1)
						showstr(hout, 2 * j, i + 1, "─", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "┷", COLOR_HWHITE, COLOR_BLACK);
				}
			}
			else
			{
				if (j == 0)
					if (i % 2 == 1)
						showstr(hout, 2 * j, i + 1, "┃", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "┝", COLOR_HWHITE, COLOR_BLACK);
				else if (j == cols * 2)
					if (i % 2 == 1)
						showstr(hout, 2 * j, i + 1, "┃", COLOR_HWHITE, COLOR_BLACK);
					else
						showstr(hout, 2 * j, i + 1, "┥", COLOR_HWHITE, COLOR_BLACK);
				else
					if (i % 2 == 1)
					{
						if (j % 2 == 1)
							showstr(hout, 2 * j, i + 1, "  ", COLOR_HWHITE, COLOR_BLACK);
						else
							showstr(hout, 2 * j, i + 1, "│", COLOR_HWHITE, COLOR_BLACK);
					}
					else
					{
						if (j % 2 == 1)
							showstr(hout, 2 * j, i + 1, "─", COLOR_HWHITE, COLOR_BLACK);
						else if (j != 0 && j != cols * 2)
							showstr(hout, 2 * j, i + 1, "┿", COLOR_HWHITE, COLOR_BLACK);
					}
			}
			getxy(hout, x, y);
		}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (p[i][j] != 0)
				showstr(hout, 2 + j * 4, (i + 1) * 2, "○", p[i][j] + 1, COLOR_HWHITE);
	gotoxy(hout, 0, y + 1);
	setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
}

/*画得分区域+彩球预告*/
void print_console3(const int rows, const int cols, int next[], int leap)//leap=4如果要打印球//leap=8打印统计结果
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	showstr(hout, 4 * cols + 4, 1 + leap, "┍", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * cols + 3; i<2 * cols + 8; i++)
		showstr(hout, 2 * i, 1 + leap, "─", COLOR_HWHITE, COLOR_BLACK);
	showstr(hout, 4 * cols + 16, 1 + leap, "┑", COLOR_HWHITE, COLOR_BLACK);
	showstr(hout, 4 * cols + 4, 2 + leap, "┃", COLOR_HWHITE, COLOR_BLACK);
	if (leap == 0)
	{
		showstr(hout, 4 * cols + 6, 2, "得分：", COLOR_HWHITE, COLOR_BLACK);
		showstr(hout, 4 * cols + 12, 2, "0   ", COLOR_HWHITE, COLOR_HWHITE);
	}
	else if(leap=4)
	{
		for (int i = 0; i < 3; i++)
		{
			showstr(hout, 2 * (2 * cols + 3 + 2 * i),6, "○", next[i] + 1, COLOR_HWHITE);
			showstr(hout, 2 * (2 * cols + 3 + 2 * i) + 2, 6, "┃", COLOR_HWHITE, COLOR_BLACK);
		}
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			showstr(hout, 4 * cols + 6, 10 + i, "○", 1, COLOR_HWHITE);
		}
	}

	showstr(hout, 4 * cols + 16, 2 + leap, "┃", COLOR_HWHITE, COLOR_BLACK);
	showstr(hout, 4 * cols + 4, 3 + leap, "┕", COLOR_HWHITE, COLOR_BLACK);
	for (int i = 2 * cols + 3; i<2 * cols + 8; i++)
		showstr(hout, 2 * i, 3 + leap, "─", COLOR_HWHITE, COLOR_BLACK);
	showstr(hout, 4 * cols + 16, 3 + leap, "┙", COLOR_HWHITE, COLOR_BLACK);
}

/*读取起点终点，并放入数组begin final  */
void bgn_fnl_mouse(char begin[2], char final[2], int rows, int cols, int Y, int p[][10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	int loop = 1;
	int click_begin = 0;
	enable_mouse(hin);
	int action, x, y;
	setcursor(hout, CURSOR_INVISIBLE);
	while (loop)
	{
		action = read_mouse(hin, x, y);//读取鼠标的动作和位置
		gotoxy(hout, 0, Y);
		setcolor(hout, COLOR_BLACK, COLOR_HWHITE);
		int y_i = (y - 1) / 2;//0-rows-1
		int x_j = x / 4;//0-cols-1
		if ((y - 1) / 2 + 1 > 0 && (y - 1) / 2 + 1 <= rows && (x / 4 + 1) > 0 && (x / 4 + 1) <= cols)
		{
			cout << "[当前坐标]" << char(y_i + 'A') << "行" << x_j + 1 << "列";
			switch (action)
			{
			case MOUSE_RIGHT_BUTTON_CLICK:
				end();
				break;
			case MOUSE_LEFT_BUTTON_CLICK:
				if (click_begin != -1 && p[y_i][x_j] != 0)
				{
					if (click_begin)
						showstr(hout, 2 + (begin[1] - '1') * 4, (begin[0] - 'A') * 2 + 2, "○", p[begin[0] - 'A'][begin[1] - '1'] + 1, COLOR_HWHITE);
					begin[0] = char(y_i + 'A');
					begin[1] = char(x_j + '1');
					showstr(hout, 2 + x_j * 4, y_i * 2 + 2, "◎", p[y_i][x_j] + 1, COLOR_HWHITE);
					click_begin++;
					break;
				}
				else if (click_begin >0 && p[y_i][x_j] == 0)//
				{
					final[0] = char(y_i + 'A');
					final[1] = char(x_j + '1');
					loop = 0;
					break;
				}
			
			}
		}
	}
}

/*已知起点和终点，利用search函数判断能不能找到路，如果找到路，进行小球的移动，不能则打印提示，并继续接受输入*/
void move_img(int p[][10], int rout[][2], char begin[2], char final[2], int rows, int cols, int Y)///如果不需要对rows,cols进行修改，用整型就可以了，不需要用指针
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int begin_value = p[begin[0] - 'A'][begin[1] - '1'];
	int num_pace;
	while (1)
	{
		num_pace = 0;
		for (int i = 0; i < 81; i++)
			for (int j = 0; j < 2; j++)
				rout[i][j] = -1;
		bgn_fnl_mouse(begin, final, rows, cols, Y, p);//给起点和终点赋值1-cols,A-ROWS
		int begin_value = p[begin[0] - 'A'][begin[1] - '1'];
		if (search(p, rout, begin[1] - '1', begin[0] - 'A', final[1] - '1', final[0] - 'A', rows, cols, &num_pace))
		{
			reset_array(p, &cols, &rows);
			show_rout(rout, begin_value);
			break;
		}
		else
		{
			reset_array(p, &cols, &rows);
			cout << "错误，无法从" << begin[0] << begin[1] << "转移到" << final[0] << final[1];
			continue;
		}
	}
}

void show_rout(int rout[][2], int begin_value)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int i = 81;
	for (; i > 0; i--)
		if (rout[i][0] >= 0)//??为什么用!=-1做条件行不通！！误打误撞
			break;
	for (int k = i - 1; k >= 0; k--)//rout[][0]是i 0-(rows-1)!  rout[][1]是j 0-(cols-1)
	{
		if (k != 0)
			showstr(hout, 2 + rout[k][1] * 4, (rout[k][0] + 1) * 2, "◎", begin_value + 1, COLOR_HWHITE);
		else
			showstr(hout, 2 + rout[k][1] * 4, (rout[k][0] + 1) * 2, "○", begin_value + 1, COLOR_HWHITE);
		showstr(hout, 2 + rout[k + 1][1] * 4, (rout[k + 1][0] + 1) * 2, "  ", COLOR_HWHITE, COLOR_HWHITE);
		Sleep(100);
	}
}


/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b2.h"
#include"cmd_console_tools.h"
using namespace std;
void one(int(*p)[10])//打印五个球
{
	int rows, cols;
	int rout[81][2];
	init(&rows, &cols, p, 5);
	print(p, rows, cols, rout);
	end();
}

void two(int(*p)[10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int rows, cols;
	int balls;//炮灰
	char begin[2];//存放起点 begin[0]  A-I  begin[1] 1-9
	char final[2];//存放终点 
	int *next = &balls;
	int rout[81][2];//存放路径
	int num_pace = 0;
	init(&rows, &cols, p, 100);//初始化+随机产生球
	print(p, rows, cols, rout);//打印初始数组（有球，有颜色）
	next_balls(next);//*next存放即将出现的球的值，但没有确定分布位置
	input_position(p, rows, cols, begin, final);//要求输入起始和终止位置，同时把坐标分别存入begin，final两个数组
	int begin_value = p[begin[0] - 'A'][begin[1] - '1'];//把起点的值事先存下来，因为在search中会发生改变。
	if (search(p, rout, begin[1] - '1', begin[0] - 'A', final[1] - '1', final[0] - 'A', rows, cols, &num_pace))
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (p[i][j] == -1)
					p[i][j] = 0;//search是吧探索过的店全都变成了-1要变回来，包括起始点
		p[begin[0] - 'A'][begin[1] - '1'] = begin_value;
		print_rout(rows, cols, rout, p);
	}
	else
		cout << "\nno way";
	end();
}

void three(int p[][10])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(hout, 60, 60, 200);//设置窗口大小
	int rows, cols, score = 0, eve_score = 0, num_pace;
	char begin[2], final[2];
	int next[3], rout[81][2];
	init(&rows, &cols, p, 5);//初始化+随机产生球
	const int * const row_ptr = &rows;
	const int * const col_ptr = &cols;
	print(p, *row_ptr, *col_ptr, rout);
	next_balls(next);
	int x, y;
	while (1)
	{
		for (int i = 0; i < 81; i++)
			for (int j = 0; j < 2; j++)
				rout[i][j] = -1;//每次寻路都把原先存放路径上点的数组清空

		num_pace = 0;//每次都需要重置
		input_position(p, *row_ptr, *col_ptr, begin, final);
		int begin_value = p[begin[0] - 'A'][begin[1] - '1'];
		if (search(p, rout, begin[1] - '1', begin[0] - 'A', final[1] - '1', final[0] - 'A', *row_ptr, *col_ptr, &num_pace))
		{
			reset_array(p, col_ptr, row_ptr);//search是吧探索过的店全都变成了-1要变回来，包括起始点
			p[final[0] - 'A'][final[1] - '1'] = begin_value;
		}
		else
		{
			cout << "\n本次得分：" << 0 << " 总共得分：" << score << endl;
			reset_array(p, col_ptr, row_ptr);
			print(p, *row_ptr, *col_ptr, rout);
			cout << "\n下三个彩球的颜色分别是： " << next[0] << "  " << next[1] << "  " << next[2];
			continue;
		}
		judge(p, final, *row_ptr, *col_ptr, &score, &eve_score);
		if (!eve_score)
			update_array(p, next, col_ptr, row_ptr, 0);
		cout << "\n本次得分：" << eve_score << " 总共得分：" << score << endl;
		print(p, *row_ptr, *col_ptr, rout);
		if (eve_score)
			cout << "\n下三个彩球的颜色分别是： " << next[0] << "  " << next[1] << "  " << next[2];
		else
			next_balls(next);
		getxy(hout, x, y);
		if (game_over(p, row_ptr, col_ptr,y-1))
			break;
	}
	end();
}
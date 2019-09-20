#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//4996是为了提醒fopen、fclose、fscanf函数不安全的
#pragma warning(disable:4996)
using namespace std;
int write(int x, int y);
int inside(int x, int y);
int outside(int x, int y);
//记录棋盘上的标记点 
bool sign[10][10][10];
//记录标记点的可能性剩余个数 
int sign_count[10][10];
//记录棋盘 
int checkerboard[10][10];
//记录类型
int type;


//重置棋盘和标记 
void reset()
{
	for (int i = 1; i < type + 1; i++)
	{
		for (int j = 1; j < type + 1; j++)
		{
			//假设每个位置都有type种可能 
			sign_count[i][j] = type;
			//每个位置都是空 
			checkerboard[i][j] = 0;
			//每个位置未曾填写 
			sign[i][j][0] = false;
			//假设每个位置的type种可能都是可实现的
			for (int k = 1; k < type + 1; k++)
			{
				sign[i][j][k] = true;
			}
		}
	}
	return;
}

//填入确定值 
int write(int x, int y)
{
	//这个位置标记为存在数字 
	sign[x][y][0] = true;
	sign_count[x][y] = 0;
	//填入数字 
	for (int i = 1; i < type + 1; i++)
	{
		if (sign[x][y][i])
		{
			checkerboard[x][y] = i;
			break;
		}
	}
	/*//输出改变的位置和新棋盘
	cout<<x<<' '<<y<<'\n';
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			cout<<checkerboard[i][j]<<' ';
		}
		cout<<'\n';
	}
	//输出每个位置的可能性
	cout<<'\n'<<"可能性：\n";
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			cout<<sign_count[i][j]<<' ';
		}
		cout<<'\n';
	}
	cout<<'\n';*/
	outside(x, y);
	return 0;
}

//查出所有空缺的可能性（位置上还没有数字） 
//此时是扣除所在位置的可能性 
int inside(int x, int y)
{
	//排除横纵向可能性
	int remove;
	for (int i = 1; i < type + 1; i++)
	{
		//如果检测位置存在数 
		if (sign[x][i][0])
		{
			remove = checkerboard[x][i];
			//则这个空位不能出现相同数字
			//防止sign_count被误减去，前面先判断是不是已经变否了，未变否才变否 
			if (sign[x][y][remove])
			{
				sign[x][y][remove] = false;
				//可能性-1
				sign_count[x][y]--;
			}
			if (sign_count[x][y] == 1 && !sign[x][y][0])
			{
				write(x, y);
				return 0;
			}
		}
	}
	for (int i = 1; i < type + 1; i++)
	{
		if (sign[i][y][0])
		{
			remove = checkerboard[i][y];
			if (sign[x][y][remove])
			{
				sign[x][y][remove] = false;
				sign_count[x][y]--;
			}
			if (sign_count[x][y] == 1 && !sign[x][y][0])
			{
				write(x, y);
				return 0;
			}
		}
	}
	//宫格判断 
	if (type == 4 || type == 6 || type == 8 || type == 9)
	{
		int beginx, beginy;
		int xplus, yplus;
		switch (type)
		{
		case 4:
			xplus = 2;
			yplus = 2;
			break;
		case 6:
			xplus = 2;
			yplus = 3;
			break;
		case 8:
			xplus = 4;
			yplus = 2;
			break;
		case 9:
			xplus = 3;
			yplus = 3;
			break;
		}
		beginx = ((x - 1) / xplus)*xplus + 1;
		beginy = ((y - 1) / yplus)*yplus + 1;
		for (int i = beginx; i < beginx + xplus; i++)
		{
			for (int j = beginy; j < beginy + yplus; j++)
			{
				if (sign[i][j][0])
				{
					if (sign[x][y][(checkerboard[i][j])])
					{
						sign[x][y][(checkerboard[i][j])] = false;
						sign_count[x][y]--;
					}
					if (sign_count[x][y] == 1 && !sign[x][y][0])
					{
						write(x, y);
						return 0;
					}
				}
			}
		}
	}
	//经过上面的判断，如果该位置只剩下一种可能性，那么执行write()
	return 0;
}


//去除所填位置的横纵九宫格所有同数可能性（位置上刚填入数字） 
//此时是扣除所填位置的横纵九宫格的其他位置可能性 
int outside(int x, int y)
{
	//remove是当前位置填入的数字 
	int remove = checkerboard[x][y];
	for (int i = 1; i < type + 1; i++)
	{
		if (!sign[x][i][0] && sign[x][i][remove])
		{
			sign[x][i][remove] = false;
			sign_count[x][i]--;
			if (sign_count[x][i] == 1 && !sign[x][i][0])
			{
				write(x, i);
			}
		}
	}
	for (int i = 1; i < type + 1; i++)
	{
		if (!sign[i][y][0] && sign[i][y][remove])
		{
			sign[i][y][remove] = false;
			sign_count[i][y]--;
			if (sign_count[i][y] == 1 && !sign[i][y][0])
			{
				write(i, y);
			}
		}
	}
	//宫格判断 
	if (type == 4 || type == 6 || type == 8 || type == 9)
	{
		int beginx, beginy;
		int xplus, yplus;
		switch (type)
		{
		case 4:
			xplus = 2;
			yplus = 2;
			break;
		case 6:
			xplus = 2;
			yplus = 3;
			break;
		case 8:
			xplus = 4;
			yplus = 2;
			break;
		case 9:
			xplus = 3;
			yplus = 3;
			break;
		}
		beginx = ((x - 1) / xplus)*xplus + 1;
		beginy = ((y - 1) / yplus)*yplus + 1;
		for (int i = beginx; i < beginx + xplus; i++)
		{
			for (int j = beginy; j < beginy + yplus; j++)
			{
				if (!sign[i][j][0] && sign[i][j][remove])
				{
					sign[i][j][remove] = false;
					sign_count[i][j]--;
					if (sign_count[i][j] == 1 && !sign[i][j][0])
					{
						write(i, j);
					}
				}
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int n;
	FILE* fp1;
	FILE* fp2;
	type = atoi(argv[2]);
	n = atoi(argv[4]);
	//cin >> type >> n;
	//cout << type << n;
	//以只读方式打开文件
	fp1 = fopen("input.txt", "r");
	if (fp1 == NULL) //
		return -1;
	//打开output.txt，并立即关闭，意义为清空文本内容
	fp2 = fopen("output.txt", "w");
	if (fp2 == NULL) //
		return -1;
	fclose(fp2);
	while (n > 0)
	{
		//重置棋盘 
		reset();
		//输入棋盘 
		for (int i = 1; i < type + 1; i++)
		{
			for (int j = 1; j < type + 1; j++)
			{
				fscanf(fp1, "%d", &checkerboard[i][j]);
				if (checkerboard[i][j] != 0)
				{
					sign[i][j][0] = true;
					sign_count[i][j] = 0;
				}
			}
		}
		//关闭input文件
		//以只写方式打开文件
		fp2 = fopen("output.txt", "a");
		if (fp2 == NULL)
			return -1;
		//找出空缺位置
		for (int k = 0; k < 2; k++)
		{
			for (int i = 1; i < type + 1; i++)
			{
				for (int j = 1; j < type + 1; j++)
				{
					if (!sign[i][j][0])
					{
						inside(i, j);
					}
				}
			}
		}
		bool sign_complete = true;
		for (int i = 1; i < type + 1; i++)
		{
			for (int j = 1; j < type + 1; j++)
			{
				fprintf(fp2, "%d", checkerboard[i][j]);
				if (checkerboard[i][j] == 0)
				{
					sign_complete = false;
				}
				if (j != type)
				{
					fprintf(fp2, " ");
				}
				//cout << checkerboard[i][j] << ' ';//
			}
			if( n != 1 && i==type && sign_complete){ fprintf(fp2, "\n\n"); }
			else if (n != 1 && i == type && !sign_complete) { fprintf(fp2, "\n这道题有多个解存在，无法再填入任何一格\n因此棋盘中有空位\n\n"); }
			else if ( n == 1 && i == type && sign_complete){}
			else if (n == 1 && i == type && !sign_complete) { fprintf(fp2, "\n这道题有多个解存在，无法再填入任何一格\n因此棋盘中有空位"); }
			else { fprintf(fp2, "\n");  }
			//cout << '\n';//
		}
		//cout << '\n';//
		//fprintf(fp2, "\n");
		n--;
		fclose(fp2);
	}
	fclose(fp1);
}

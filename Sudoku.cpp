#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//4996��Ϊ������fopen��fclose��fscanf��������ȫ��
#pragma warning(disable:4996)
using namespace std;
int write(int x, int y);
int inside(int x, int y);
int outside(int x, int y);
void check();
//��¼�����ϵı�ǵ� 
bool sign[10][10][10];
//��¼��ǵ�Ŀ�����ʣ����� 
int sign_count[10][10];
//��¼���� 
int checkerboard[10][10];
//��¼����
int type;
int small_sign[10];


//�������̺ͱ�� 
void reset()
{
	for (int i = 1; i < type + 1; i++)
	{
		for (int j = 1; j < type + 1; j++)
		{
			//����ÿ��λ�ö���type�ֿ��� 
			sign_count[i][j] = type;
			//ÿ��λ�ö��ǿ� 
			checkerboard[i][j] = 0;
			//ÿ��λ��δ����д 
			sign[i][j][0] = false;
			//����ÿ��λ�õ�type�ֿ��ܶ��ǿ�ʵ�ֵ�
			for (int k = 1; k < type + 1; k++)
			{
				sign[i][j][k] = true;
			}
		}
	}
	return;
}

//����ȷ��ֵ 
int write(int x, int y)
{
	//���λ�ñ��Ϊ�������� 
	sign[x][y][0] = true;
	sign_count[x][y] = 0;
	//�������� 
	for (int i = 1; i < type + 1; i++)
	{
		if (sign[x][y][i])
		{
			checkerboard[x][y] = i;
			break;
		}
	}
	/*//����ı��λ�ú�������
	cout<<x<<' '<<y<<'\n';
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			cout<<checkerboard[i][j]<<' ';
		}
		cout<<'\n';
	}
	//���ÿ��λ�õĿ�����
	cout<<'\n'<<"�����ԣ�\n";
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

//������п�ȱ�Ŀ����ԣ�λ���ϻ�û�����֣� 
//��ʱ�ǿ۳�����λ�õĿ����� 
int inside(int x, int y)
{
	//�ų������������
	int remove;
	for (int i = 1; i < type + 1; i++)
	{
		//������λ�ô����� 
		if (sign[x][i][0])
		{
			remove = checkerboard[x][i];
			//�������λ���ܳ�����ͬ����
			//��ֹsign_count�����ȥ��ǰ�����ж��ǲ����Ѿ�����ˣ�δ���ű�� 
			if (sign[x][y][remove])
			{
				sign[x][y][remove] = false;
				//������-1
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
	//�����ж� 
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
	//����������жϣ������λ��ֻʣ��һ�ֿ����ԣ���ôִ��write()
	return 0;
}


//ȥ������λ�õĺ��ݾŹ�������ͬ�������ԣ�λ���ϸ��������֣� 
//��ʱ�ǿ۳�����λ�õĺ��ݾŹ��������λ�ÿ����� 
int outside(int x, int y)
{
	//remove�ǵ�ǰλ����������� 
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
	//�����ж� 
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

void check()
{
	//���ÿһ��
	for (int i = 1; i < type + 1; i++)
	{
		for (int j = 1; j < type + 1; j++)
		{
			small_sign[j] = 0;
		}
		for (int j = 1; j < type + 1; j++)
		{
			if (!sign[i][j][0])
			{
				for (int k = 1; k < type + 1; k++)
				{
					if (sign[i][j][k])
					{
						small_sign[k]++;
					}
				}
			}
		}
		for (int k = 1; k < type + 1; k++)
		{
			if (small_sign[k] == 1)
			{
				for (int j = 1; j < type + 1; j++)
				{
					if (sign[i][j][k] && !sign[i][j][0])
					{
						//���λ�ñ��Ϊ�������� 
						sign[i][j][0] = true;
						sign_count[i][j] = 0;
						checkerboard[i][j] = k;
						outside(i, j);
					}
				}
			}
		}
	}
	//���ÿһ��
	for (int j = 1; j < type + 1; j++)
	{
		for (int i = 1; i < type + 1; i++)
		{
			small_sign[i] = 0;
		}
		for (int i = 1; i < type + 1; i++)
		{
			if (!sign[i][j][0])
			{
				for (int k = 1; k < type + 1; k++)
				{
					if (sign[i][j][k])
					{
						small_sign[k]++;
					}
				}
			}
		}
		for (int k = 1; k < type + 1; k++)
		{
			if (small_sign[k] == 1)
			{
				for (int i = 1; i < type + 1; i++)
				{
					if (sign[i][j][k] && !sign[i][j][0])
					{
						//���λ�ñ��Ϊ�������� 
						sign[i][j][0] = true;
						sign_count[i][j] = 0;
						checkerboard[i][j] = k;
						outside(i, j);
					}
				}
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int n;
	FILE* fp1;
	FILE* fp2;
	type = atoi(argv[2]);
	n = atoi(argv[4]);
	char* InputName = argv[6];
	char* OutputName = argv[8];
	//��ֻ����ʽ���ļ�
	fp1 = fopen(InputName, "r");
	if (fp1 == NULL) //
		return -1;
	//fscanf(fp1, "%d%d", &type,&n);
	//��output.txt���������رգ�����Ϊ����ı�����
	fp2 = fopen(OutputName, "w");
	if (fp2 == NULL) //
		return -1;
	fclose(fp2);
	while (n > 0)
	{
		//�������� 
		reset();
		//�������� 
		for (int i = 1; i < type + 1; i++)
		{
			for (int j = 1; j < type + 1; j++)
			{
				//cin >> checkerboard[i][j];
				fscanf(fp1, "%d", &checkerboard[i][j]);
				if (checkerboard[i][j] != 0)
				{
					sign[i][j][0] = true;
					sign_count[i][j] = 0;
				}
			}
		}
		//�ر�input�ļ�
		//��ֻд��ʽ���ļ�
		fp2 = fopen(OutputName, "a");
		if (fp2 == NULL)
			return -1;
		//�ҳ���ȱλ��
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
		check();
		for (int i = 1; i < type + 1; i++)
		{
			for (int j = 1; j < type + 1; j++)
			{
				//cout << checkerboard[i][j];
				fprintf(fp2, "%d", checkerboard[i][j]);
				if (checkerboard[i][j] == 0)
				{
					sign_complete = false;
				}
				if (j != type)
				{
					fprintf(fp2, " ");
					//cout << ' ';
				}
			}
			if (n != 1 && i == type && sign_complete)
			{
				//cout << "\n\n";  
				fprintf(fp2, "\n\n");
			}
			else if (n != 1 && i == type && !sign_complete)
			{
				//cout << "\n�޷���ȷ���������κ�һ��\n����������п�λ\n\n";
				fprintf(fp2, "\n�޷���ȷ���������κ�һ��\n����������п�λ\n\n");
			}
			else if (n == 1 && i == type && sign_complete) {}
			else if (n == 1 && i == type && !sign_complete)
			{
				//cout << "\n�޷���ȷ���������κ�һ��\n����������п�λ";
				fprintf(fp2, "\n�޷���ȷ���������κ�һ��\n����������п�λ");
			}
			else
			{
				//cout << "\n";
				fprintf(fp2, "\n");
			}
		}
		//cout << '\n';//
		//fprintf(fp2, "\n");
		n--;
		fclose(fp2);
	}
	fclose(fp1);
}
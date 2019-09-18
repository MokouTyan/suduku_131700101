#include <iostream>
#include <cstdio>
using namespace std;
int write(int x,int y);
int inside(int x, int y);
int outside(int x,int y);
//记录棋盘上的标记点 
bool sign[10][10][10];
//记录标记点的剩余个数 
int sign_count[10][10]; 
//记录棋盘 
int checkerboard[10][10];
//记录类型
int type; 


//重置棋盘和标记 
void reset()
{
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			//假设每个位置都有九种可能 
			sign_count[i][j]=type;
			checkerboard[i][j]=0;
			sign[i][j][0]=false;
			for ( int k=1 ; k<type+1 ; k++ )
			{
				//假设每个位置的九种可能都是可实现的 
				sign[i][j][k]=true;
			}
		}
	}
	return;
}

//填入确定值 
int write(int x,int y)
{
	//这个位置标记为存在数字 
	sign[x][y][0]=true;
	sign_count[x][y]=0;
	//填入数字 
	for ( int i=1 ; i<type+1 ; i++ )
	{
		if ( sign[x][y][i] )
		{
			checkerboard[x][y]=i;
			break;
		}
	}
	cout<<x<<' '<<y<<'\n'; 
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			cout<<checkerboard[i][j]<<' ';
		}
		cout<<'\n';
	}
	cout<<'\n'<<"sign_count\n";
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			cout<<sign_count[i][j]<<' ';
		}
		cout<<'\n';
	}
	outside(x,y); 
	return 0;
} 

//第二步，查出所有空缺的可能性（位置上还没有数字） 
//此时是扣除所在位置的可能性 
int inside(int x, int y)
{
	//排除横纵向可能性
	int remove;
	for( int i=1 ; i<type+1 ; i++ )
	{
		//如果检测位置存在数 
		if ( sign[x][i][0] )
		{
			remove=checkerboard[x][i];
			//则这个空位不能出现相同数字
			//防止sign_count被误减去，前面先判断是不是已经变否了，未变否才变否 
			if ( sign[x][y][remove] )
			{
				sign[x][y][remove]= false;
				//可能性-1
				sign_count[x][y]--; 
			}
			if ( sign_count[x][y] == 1 && !sign[x][y][0] )
			{
				write(x,y);
				return 0;
			}
		}
	}
	for ( int i=1 ; i<type+1 ; i++ )
	{
		if ( sign[i][y][0] )
		{
			remove=checkerboard[i][y];
			if (sign[x][y][remove] )
			{
				sign[x][y][remove]= false;
				sign_count[x][y]--;
			}
			if ( sign_count[x][y] == 1 && !sign[x][y][0])
			{
				write(x,y);
				return 0;
			}
		}
	}
	int beginx, beginy;
	if ( type==9 )
	{
		beginx=((x-1)/3)*3+1;
		beginy=((y-1)/3)*3+1;
		for ( int i=beginx ; i<beginx+3 ; i++ )
		{
			for ( int j=beginy ; j<beginy+3 ; j++ )
			{
				if ( sign[i][j][0] )
				{
					if ( sign[x][y][ (checkerboard[i][j]) ])
					{
						sign[x][y][ (checkerboard[i][j]) ] = false;
						sign_count[x][y]--;
					}
					if ( sign_count[x][y] == 1 && !sign[x][y][0])
					{
						write(x,y);
						return 0;
					}
				}
			}
		}
	}
	else if( type==4 )
	{
		beginx=((x-1)/2)*2+1;
		beginy=((y-1)/2)*2+1;
		for ( int i=beginx ; i<beginx+2 ; i++ )
		{
			for ( int j=beginy ; j<beginy+2 ; j++ )
			{
				if ( sign[i][j][0] )
				{
					if ( sign[x][y][ (checkerboard[i][j]) ])
					{
						sign[x][y][ (checkerboard[i][j]) ] = false;
						sign_count[x][y]--;
					}
					if ( sign_count[x][y] == 1 && !sign[x][y][0])
					{
						write(x,y);
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
int outside(int x,int y) 
{
	//remove是当前位置填入的数字 
	int remove=checkerboard[x][y];
	for( int i=1 ; i<type+1 ; i++ )
	{
		if ( !sign[x][i][0] && sign[x][i][remove] )
		{
			sign[x][i][remove] = false;
			sign_count[x][i]--;
			if ( sign_count[x][i]==1 && !sign[x][i][0])
			{
				write(x,i);
			}
		}
	}
	for ( int i=1 ; i<type+1 ; i++ )
	{
		if ( !sign[i][y][0] && sign[i][y][remove] )
		{
			sign[i][y][remove] = false;
			sign_count[i][y]--;
			if ( sign_count[i][y]==1 && !sign[i][y][0])
			{
				write(i,y);
			}
		}
	}
	int beginx, beginy;
	if ( type==9 )
	{
		beginx=((x-1)/3)*3+1;
		beginy=((y-1)/3)*3+1;
		for ( int i=beginx ; i<beginx+3 ; i++ )
		{
			for ( int j=beginy ; j<beginy+3 ; j++ )
			{
				if ( !sign[i][j][0] && sign[i][j][remove] )
				{
					sign[i][j][remove]  = false;
					sign_count[i][j]--;
					if ( sign_count[i][j]==1 && !sign[i][j][0])
					{
						write(i,j);
					}
				}
			}
		}
	}
	else if( type==4 )
	{
		beginx=((x-1)/2)*2+1;
		beginy=((y-1)/2)*2+1;
		for ( int i=beginx ; i<beginx+2 ; i++ )
		{
			for ( int j=beginy ; j<beginy+2 ; j++ )
			{
				if ( !sign[i][j][0] && sign[i][j][remove] )
				{
					sign[i][j][remove]  = false;
					sign_count[i][j]--;
					if ( sign_count[i][j]==1 && !sign[i][j][0])
					{
						write(i,j);
					}
				}
			}
		}
	}
	return 0;
}

int main(void)
{
	int n;
	cin>>type>>n;
	while( n>0 )
	{
		//重置棋盘 
		reset();
		//输入棋盘 
		for ( int i=1 ; i<type+1 ; i++ )
		{
			for ( int j=1 ; j<type+1 ; j++ )
			{
				cin>>checkerboard[i][j];
				if ( checkerboard[i][j]!=0 )
				{
					sign[i][j][0]=true;	
					sign_count[i][j]=0;
				}
			}
		}
		cout<<'\n';
		//找出空缺位置
		for ( int i=1 ; i<type+1 ; i++ )
		{
			for ( int j=1 ; j<type+1 ; j++ )
			{
				if ( !sign[i][j][0] )
				{
					inside(i,j);
				}
			}
		}
		for ( int i=1 ; i<type+1 ; i++ )
		{
			for ( int j=1 ; j<type+1 ; j++ )
			{
				cout<<checkerboard[i][j]<<' ';
			}
			cout<<'\n';
		}
		n--;
	}
}

#include <iostream>
#include <cstdio>
using namespace std;
int write(int x,int y);
int inside(int x, int y);
int outside(int x,int y);
//��¼�����ϵı�ǵ� 
bool sign[10][10][10];
//��¼��ǵ��ʣ����� 
int sign_count[10][10]; 
//��¼���� 
int checkerboard[10][10];
//��¼����
int type; 


//�������̺ͱ�� 
void reset()
{
	for ( int i=1 ; i<type+1 ; i++ )
	{
		for ( int j=1 ; j<type+1 ; j++ )
		{
			//����ÿ��λ�ö��о��ֿ��� 
			sign_count[i][j]=type;
			checkerboard[i][j]=0;
			sign[i][j][0]=false;
			for ( int k=1 ; k<type+1 ; k++ )
			{
				//����ÿ��λ�õľ��ֿ��ܶ��ǿ�ʵ�ֵ� 
				sign[i][j][k]=true;
			}
		}
	}
	return;
}

//����ȷ��ֵ 
int write(int x,int y)
{
	//���λ�ñ��Ϊ�������� 
	sign[x][y][0]=true;
	sign_count[x][y]=0;
	//�������� 
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

//�ڶ�����������п�ȱ�Ŀ����ԣ�λ���ϻ�û�����֣� 
//��ʱ�ǿ۳�����λ�õĿ����� 
int inside(int x, int y)
{
	//�ų������������
	int remove;
	for( int i=1 ; i<type+1 ; i++ )
	{
		//������λ�ô����� 
		if ( sign[x][i][0] )
		{
			remove=checkerboard[x][i];
			//�������λ���ܳ�����ͬ����
			//��ֹsign_count�����ȥ��ǰ�����ж��ǲ����Ѿ�����ˣ�δ���ű�� 
			if ( sign[x][y][remove] )
			{
				sign[x][y][remove]= false;
				//������-1
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
	//����������жϣ������λ��ֻʣ��һ�ֿ����ԣ���ôִ��write()
	return 0;
}


//ȥ������λ�õĺ��ݾŹ�������ͬ�������ԣ�λ���ϸ��������֣� 
//��ʱ�ǿ۳�����λ�õĺ��ݾŹ��������λ�ÿ����� 
int outside(int x,int y) 
{
	//remove�ǵ�ǰλ����������� 
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
		//�������� 
		reset();
		//�������� 
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
		//�ҳ���ȱλ��
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

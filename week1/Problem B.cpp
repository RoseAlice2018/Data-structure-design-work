#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

/********************************************************************************/
/********************************将学生的代码添加到下面******************************/
int countbomb(int x,int y,int map[][30])
{
    int countbomb=0;
    if(map[x-1][y-1]==-2)
        countbomb++; 
    if(map[x-1][y]==-2)
        countbomb++;
    if(map[x-1][y+1]==-2)
        countbomb++;
    if(map[x+1][y-1]==-2)
        countbomb++;
    if(map[x+1][y]==-2) 
        countbomb++;
    if(map[x+1][y+1]==-2)
        countbomb++;
    if(map[x][y-1]==-2)
        countbomb++;
    if(map[x][y+1]==-2)
        countbomb++;
    return countbomb;  
}
int countblank(int map[][30],int x,int y)
{
    int countbomb=0;
    if(map[x-1][y-1]==-1)
        countbomb++; 
    if(map[x-1][y]==-1)
        countbomb++;
    if(map[x-1][y+1]==-1)
        countbomb++;
    if(map[x+1][y-1]==-1)
        countbomb++;
    if(map[x+1][y]==-1) 
        countbomb++;
    if(map[x+1][y+1]==-1)
        countbomb++;
    if(map[x][y-1]==-1)
        countbomb++;
    if(map[x][y+1]==-1)
        countbomb++;
    return countbomb; 
}
void tag(int map[][30],int x,int y)
{
    if(map[x-1][y-1]==-1)
        map[x-1][y-1]=-2; 
    if(map[x-1][y]==-1)
        map[x-1][y]=-2;
    if(map[x-1][y+1]==-1)
        map[x-1][y+1]=-2;
    if(map[x+1][y-1]==-1)
        map[x+1][y-1]=-2;
    if(map[x+1][y]==-1) 
        map[x+1][y]=-2;
    if(map[x+1][y+1]==-1)
        map[x+1][y+1]=-2;
    if(map[x][y-1]==-1)
        map[x][y-1]=-2;
    if(map[x][y+1]==-1)
        map[x][y+1]=-2;
}
void changexy(int map[][30],int i,int j,int& x,int& y)
{

                    if(map[i-1][j-1]==-1)
                    {
                        x=i-1;
                        y=j-1;
                        return ;
                    }
                    if(map[i-1][j]==-1)
                    {
                        x=i-1;
                        y=j;
                        return ;
                    }
                    if(map[i-1][j+1]==-1)
                    {
                        x=i-1;
                        y=j+1;
                        return ;
                    }
                    if(map[i+1][j-1]==-1)
                      {
                          x=i+1;
                          y=j-1;
                          return ;
                      }
                    if(map[i+1][j]==-1) 
                    {
                        x=i+1;
                        y=j;
                        return ;
                    }
                    if(map[i+1][j+1]==-1)
                    {
                        x=i+1;
                        y=j+1;
                        return ;
                    }
                    if(map[i][j-1]==-1)
                    {
                        x=i;
                        y=j-1;
                        return ;
                    }
                    if(map[i][j+1]==-1)
                    {
                        x=i;
                        y=j+1;
                        return ;
                        ///注意 xy返回的时候要--
                    }
}
int setbomb(int map[][30],int n,int m,int& x,int& y)
{
    int tagg=0;
    //a)如果格子周围未确定的格子个数加上被标记的雷的个数等于中央数字，则剩余格子都是雷
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(map[i][j]>0&&(map[i][j]==countblank(map,i,j)+countbomb(i,j,map)))
            {
                //将剩余的格子标记为雷
                tag(map,i,j);
                // tagg=1;
            }
        }
    }
    //b)如果周围的格子被标记的个数已经达到了中央数字，则其他格子不是雷
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(map[i][j]==countbomb(i,j,map))
            {
                if(countblank(map,i,j)>0)
                {
                    tagg=1;
                    changexy(map,i,j,x,y);
                    x--;
                    y--;
                    return tagg;
                }
            }
        }
    }
    return tagg;
}
void machine(int GamePanel[30][30],int n,int m,int&x,int& y)
{
    int x1=x;
    int y1=y;
    int map[30][30];
    //copy
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            map[i+1][j+1]=GamePanel[i][j];
    }
    for(int i=0;i<=n+1;i++)
    {
        map[i][0]=-3;
        map[i][m+1]=-3;
    }
    for(int i=0;i<=m+1;i++)
    {
        map[0][i]=-3;
        map[n+1][i]=-3;
    }
    //对该数组进行操作
    //step1： 对雷进行标记，同时进行最简单的寻路操作
    int t=1;
   
        t=setbomb(map,n,m,x,y);
        //此时已经决策出了下一个点
        if((x!=x1)||(y!=y1))
        {
            return;
        }
    
    //step2: 当以上两种方法不能再翻开格子或者标记雷时，挑选任意一个周围仍然有未确定格子的数字，穷举周围格子的可能分布
    x=rand()%20;
    y=rand()%20;
    return;  
}
/*
一、穷举每个格子，
a) 如果格子的周围被标记的雷数已经到达了中央数字，则其他格子不是雷；
b) 如果格子周围未确定格子数加上被标记的雷数等于中央数字，则所有剩余格子都是雷。
翻开格子或标记后重复第一步。
二、当以上两种方法不能再次翻开格子或者标记雷时，挑选任意一个周围仍然有未确定格子的数字，
穷举周围格子可能的雷的分布，
然后在这个假设条件下按a和b的规则判断其他格子是不是雷，
直到：c)出现矛盾的情况，将这种穷举的结果排除；
d)无矛盾，将所有应该翻开和应该标记的格子记下来。
三、如果对这个格子所有的未被排除的结果，都标记了某个格子，或者将某个格子翻开，
则这个格子应当被标记或者应当翻开。标记或翻开这个格子后重新回到第一步。
四、如果对所有的格子执行二后都无法再翻开或者标记，随机选择一个未标记的格子翻开。
*/

// int secondchose(int map[][30],int n,int m,int& x,int& y)
// {
//     //挑选一个周围仍然有未确定格子的数字，穷举周围格子的可能分布
//     for(int i=1;i<=n;i++)
//     {
//         for(int j=1;j<=m;j++)
//         {
//             if(countblank(map,i,j)>0&&map[i][j]>0)
//             {
//                // 穷举周围格子可能的雷的分布，然后在这个假设条件下按a和b的规则判断其他格子是不是雷
//                return 1;
//             }
//         }
//     }
// }
// int copy(int map[][30],int cover[][30])
// {
//     for(int i=0;i<30;i++)
//     {
//         for(int j=0;j<30;j++)
//         {
//             cover[i][j]=map[i][j];
//         }
//     }
// }

void open(int x,int y,int show[][30],int mapp[][30])
{
    if(mapp[x][y]==-3)
    {
        return;
    }
    else if(countbomb(x,y,mapp)>0&&mapp[x][y]!=-2)
    {
        mapp[x][y]=countbomb(x,y,mapp);
        show[x-1][y-1]=mapp[x][y];
        return;
    }
    else
    {
        if(mapp[x][y]==-2)
        {
            return;
        }
        //open
        if(mapp[x][y]==0)
        {
            // already open
            return ;
        }
        mapp[x][y]=0;
        show[x-1][y-1]=0;
       open(x-1,y-1,show,mapp);
       open(x-1,y,show,mapp);
       open(x-1,y+1,show,mapp);
       open(x,y-1,show,mapp);
       open(x,y+1,show,mapp);
       open(x+1,y-1,show,mapp);
       open(x+1,y,show,mapp);
       open(x+1,y+1,show,mapp);
       
    }
  return;      
}
//set函数重新设置一下数组
void sett(int show[][30],int min[][30],int n,int m,int mapp[][30])
{
    //initialize
     for(int i=0;i<30;i++)
     {
         for(int j=0;j<30;j++)
         {
             mapp[i][j]=-1;
         }
     }
     for(int i=0;i<=m+1;i++)
     {
         mapp[0][i]=-3;
         mapp[n+1][i]=-3;
     }
     for(int i=0;i<=n+1;i++)
     {
         mapp[i][0]=-3;
         mapp[i][m+1]=-3;
     }
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            mapp[i+1][j+1]=show[i][j];
            if(min[i][j]==1)
            {
                mapp[i+1][j+1]=-2;
            }
        }
    }
     return;
}
void click(int x,int y,int show[][30],int n,int m,int mapp[][30])
{
   open(x,y,show,mapp);    
}
int RefreshGamePanel(int GamePanel[30][30],int x,int y,int mine[30][30],int n, int m,int k)
{
    if(mine[x][y]==1)
        return -1;
    int mapp[30][30];
    sett(GamePanel,mine,n,m,mapp);
    click(x+1,y+1,GamePanel,n,m,mapp);
    int num=0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
         {
                if (GamePanel[i][j] == -1)
                 num++;        //计算未打开点的个数
        }
    }
    if (num == k) 
    {   //最后成功
        return 1;
    }
    return 0;
}
/********************************将学生的代码添加到上面******************************/
/********************************************************************************/



int main()
{
	int GamePanel[30][30];
	int temp[30][30];
	int mine[30][30];
	int iii, ii, n, m, k, i, j, minenum, x, y, win = 0;
	int bonus;
	double score;
	double  maxscore = -999, minscore = 999, sumscore=0;
	int gamenum = 1000;
	int zerocnt = 0;
	int winnum = 0;
	n = 20;
	m = 20;
	minenum = 50;
	srand(int(time(0)));
	printf("正在评测中，请稍等，我们将进行1000局游戏，取平均分*1.3作为最终成绩......\n");
	
	for (iii = 0; iii<gamenum; iii++)
	{
		
		for (i = 0; i<n; i++)
			for (j = 0; j<m; j++)
			{
				GamePanel[i][j] = -1;
				mine[i][j] = 0;
			}

		int cnt = 0;

		for (ii = 0; ii<400; ii++)
		{	
			for (i = 0; i < 20; i++)
				for (j = 0; j < 20; j++)
					temp[i][j] = GamePanel[i][j];
			machine(temp, n, m, x, y);
			if (ii == 0)
			{
				for ( k = 0; k < minenum; k++)
				{
					i = rand() % 20;
					j = rand() % 20;
					while ((i == x && j == y) || mine[i][j] != 0)
					{
						i = rand() % 20;
						j = rand() % 20;
					}
					mine[i][j] = 1;
				}
			}
			if (GamePanel[x][y] == -1)
			{
				cnt++;
				win = RefreshGamePanel(GamePanel, x, y, mine, n, m, minenum);
				if (win == 1)
				{
					if (cnt < 80) bonus = 10;
					else if (cnt < 90) bonus = 9;
					else if (cnt < 100) bonus = 8;
					else if (cnt < 120) bonus = 7;
					else if (cnt < 150) bonus = 5;
					else if (cnt < 200) bonus = 3;
					else if (cnt < 250) bonus = 1;
					else bonus = 0;
					score = 50.0 + bonus;
					if(iii==0 || (iii+1)%10==0) printf("第 %d 局,赢了,得 %d 分.\n", iii+1,(int)score);
					winnum++;

					break;
				}
				else if (win == -1)
				{
					score = 0;
					for (i = 0; i<n; i++)
						for (j = 0; j<m; j++)
						{
							if (GamePanel[i][j] != -1)
								score=score+1;
						}
					score = score/10;
									
					if (iii == 0 || (iii + 1) % 10 == 0)printf("第 %d 局,输了,得 %.2lf 分.\n", iii + 1, score);
		
					break;
				}
			}

		}
		if (win == 0)
		{
			score = 0;
			for (i = 0; i<n; i++)
				for (j = 0; j<m; j++)
				{
					if (GamePanel[i][j] != -1)
						score=score+1;
				}
			score = score / 10;
			if (iii == 0 || (iii + 1) % 10 == 0)printf("第 %d 局,输了,得 %.2lf 分.\n", iii + 1, score);

		}
		if (score>maxscore) maxscore = score;
		if (score<minscore) minscore = score;
		sumscore = sumscore+score;
		
	}
	
	int orignscore,finalscore;

	orignscore= ceil(1.3*ceil(sumscore/gamenum));

	if (orignscore > 60) finalscore = 60;
	else finalscore = orignscore;
	//printf("该学生原始分数为 %d.\n\n", orignscore);
	
	
	printf("该学生最终分数为 %d.\n\n", finalscore);
	printf("该学生胜率为 %.1lf%%\n\n", winnum/10.0);
	
	system("pause");
	return 0;
}

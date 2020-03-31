#include "snake.h"
using namespace std;


bool check30(point snake[5][100], int len[5], int t, GamePanel gp, int direction ) 
{
	//将你的check函数体放在此处，并删去下面示例代�?
	// if (snake[t][1].y == gp.m && direction == 1) return false;
	// if (snake[t][1].y == 2 && direction == 2) return false;
	//第一种情况，不考虑斜方向走
	if(direction==1)// 向右�?
	{
		
		point next;
		next.x=snake[t][1].x;
		next.y=snake[t][1].y+2;
		// 如果右边是障碍物
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//如果右边是墙�?
		if(next.y==gp.m+2)
			return false;
		//如果右边是其他�?
		/*
		注意 这里默认了我们操纵的�?号�?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}

	}
	if(direction==0)//如果向下�?
	{
		point next;
		next.x=snake[t][1].x+1;
		next.y=snake[t][1].y;
		// 如果下边是障碍物
		for(int i=0;i<gp.wallnum;i++)
		{
			if(gp.wall[i].x==next.x&&gp.wall[i].y==next.y)
				return false;
		}
		//如果下边是墙�?
		if(next.x==gp.n+1)
			return false;
		//如果右边是其他�?
		/*
		注意 这里默认了我们操纵的�?号�?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
	}
	if(direction==2)//如果向左�?
	{
		point next;
		next.x=snake[t][1].x;
		next.y=snake[t][1].y-2;
		// 如果左边是障碍物
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		if(next.y==0)
			return false;
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
	}
	if(direction==3)//如果向上�?
	{
		point next;
		next.x=snake[t][1].x-1;
		next.y=snake[t][1].y;
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		if(next.x==0)
			return false;
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
	}
	if(direction==4)//右下�?
	{
		point next;
		next.x=snake[t][1].x+1;
		next.y=snake[t][1].y+2;
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		if(next.x==0)
			return false;
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//如果右下两边都是墙壁
		if((gp.panel[next.x-1][next.y]==2)&&(gp.panel[next.x][next.y-2]==2))
			return false;
	}
	if(direction==5)//右上�?
	{
		point next;
		next.x=snake[t][1].x-1;
		next.y=snake[t][1].y+2;
		// 如果右上边是障碍�?
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//如果右上边是墙壁
		if(next.x==0)
			return false;
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//如果右上两边都是墙壁
		if((gp.panel[next.x][next.y-2]==2)&&(gp.panel[next.x+1][next.y]==2))
			return false;
	}
	if(direction==6)//左上
	{
		point next;
		next.x=snake[t][1].x-1;
		next.y=snake[t][1].y-2;
		// 如果左上边是障碍�?
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//如果左上边是墙壁
		if(next.x==0)
			return false;
		//如果右边是其他�?
		/*
		注意 这里默认了我们操纵的�?号�?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//如果左上两边都是墙壁
		if((gp.panel[next.x+1][next.y]==2)&&(gp.panel[next.x][next.y+2]==2))
			return false;
	}
	if(direction==7)//左下
	{
		point next;
		next.x=snake[t][1].x+1;
		next.y=snake[t][1].y-2;
		// 如果右下边是障碍�?
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//如果右下边是墙壁
		if(next.x==0)
			return false;
		//如果右边是其他�?
		/*
		注意 这里默认了我们操纵的�?号�?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//如果右边是自�?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//如果右下两边都是墙壁
		if((gp.panel[next.x-1][next.y]==2)&&(gp.panel[next.x][next.y+2]==2))
			return false;
	}
	return true;
}

int machine_move30(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)	
{
	//将你的machine_move函数体放在此处，并删去下面示例代�?
	//最简单的方法 找到最近的一个可以吃掉的食物并吃掉它
	int left=gp.totalfoodnum;
	int distant[left];
	point head;
	head.x=snake[t][1].x;head.y=snake[t][1].y;
	//用曼哈顿距离计算
	int mindis=2000;
	int minlocation=0;
	for(int i=0;i<left;i++)
	{
		if(gp.panel[gp.food[i].x][gp.food[i].y]==1)
		{
			int dis=fabs(head.x-gp.food[i].x)+fabs(head.y-gp.food[i].y);
			distant[i]=dis;
			if(dis<mindis)
			{
			mindis=dis;
			minlocation=i;
			}
		}		
	}
    point location;location.x=gp.food[minlocation].x;location.y=gp.food[minlocation].y;
    if(gp.obliquenum>=1)
    {
        for(int i=0;i<2;i++)
        {
            if(gp.panel[gp.obliqueprops[i].x][gp.obliqueprops[i].y]==4)
            {
                location.x=gp.obliqueprops[i].x;
                location.y=gp.obliqueprops[i].y;
            }
        }
    }
    if(gp.speednum>0)
    {
        if(gp.panel[gp.speedprops.x][gp.speedprops.y]==3)
        {
            location.x==gp.speedprops.x;
            location.y=gp.speedprops.y;
        }
    }
	if(location.x>head.x)
	{
		if(location.y>head.y)
		{
            if(gp.obliqueowner[t]==1)
            {
                if(check30(snake,len,t,gp,4))
                    return 4;
            }
			if(check30(snake,len,t,gp,1))
				return 1;
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,3))
				return 3;
		}
		else if(location.y<head.y)
		{
            if(gp.obliqueowner[t]==1)
            {
                if(check30(snake,len,t,gp,7))
                    return 7;
            }
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,1))
				return 1;
			if(check30(snake,len,t,gp,3))
				return 3;
		}
		else
		{
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,1))
				return 1;
			if(check30(snake,len,t,gp,3))
				return 3;
		}
	}
	else if(location.x<head.x)
	{
		if(location.y>head.y)
		{
            if(gp.obliqueowner[t]==1)
            {
                if(check30(snake,len,t,gp,5))
                    return 5;
            }
			if(check30(snake,len,t,gp,1))
				return 1;
			if(check30(snake,len,t,gp,3))
				return 3;
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,2))
				return 2;
		}
		else if(location.y<head.y)
		{
            if(gp.obliqueowner[t]==1)
            {
                if(check30(snake,len,t,gp,6))
                    return 6;
            }
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,3))
				return 3;
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,1))
				return 1;
		}
		else
		{
			if(check30(snake,len,t,gp,3))
				return 3;
			if(check30(snake,len,t,gp,1))
				return 1;
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,0))
				return 0;
		}
	}
	else 
	{
		if(location.y>head.y)
		{
			if(check30(snake,len,t,gp,1))
				return 1;
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,3))
				return 3;
		}
		else
		{
			if(check30(snake,len,t,gp,2))
				return 2;
			if(check30(snake,len,t,gp,3))
				return 3;
			if(check30(snake,len,t,gp,0))
				return 0;
			if(check30(snake,len,t,gp,1))
				return 1;
		}
			
	}
	return 3;

}

#include "snake.h"
using namespace std;
struct queue30
{
	int f,r;
	point *data;
	int size;
	queue30(int x=10000)
	{
		f=r=0;
		size=x;
		data=new point[x];
	}
	int next(int x) {return (x+1)%size;}
	int pre(int x) {return (size+x-1)%size;}
	bool push(point x)
	{
		if(next(r)==pre(f))
		{
			return false;
		}
		data[r]=x;
		r=next(r);
		return true;
	}
	point front()
	{
		if(f==r) ;
		return data[f];
	}
	void pop()
	{
		if(f==r) ;
		else f=next(f);
	}
	bool empty(){return f==r;}
};

bool checkSnkBody30(point snake[5][100],GamePanel gp,point tt,int len[5],int t)
{
	for(int i=1;i<len[t];i++)
	{
		if(snake[t][i].x==tt.x&&snake[t][i].y==tt.y)
			return false;
	}
	if(snake[t][len[t]].x==tt.x&&snake[t][len[t]].y==tt.y)
		return true;
	for(int i=1;i<=len[!t];i++)
	{
		if(snake[!t][i].x==tt.x&&snake[!t][i].y==tt.y)
			return false;
	}
	if(gp.panel[tt.x][tt.y]==2)
		return false;
	if(tt.x==0||tt.x==gp.n+1||tt.y==0||tt.y==gp.m+2)
		return false;
	return true;
}
bool findthepathtoend30(point snake[5][100],int len[5],int direct[5],int t,GamePanel gp)
{
	queue30 path;
	int panel[50][100]={-1};// -1表示还未访问过
	point first; first.x=snake[t][1].x;first.y=snake[t][1].y;
	point tail;  tail.x=snake[t][len[t]].x;tail.y=snake[t][len[t]].y;
	path.push(first);
	panel[first.x][first.y]=1;//1 表示已经访问过
	while(!path.empty())
	{
		point tt=path.front();
		if(tt.x==tail.x&&tt.y==tail.y)
		{
			return true;
		}
		path.pop();
		point ttup;ttup.x=tt.x-1;ttup.y=tt.y;
		point ttdown;ttdown.x=tt.x+1;ttdown.y=tt.y;
		point ttleft;ttleft.x=tt.x;ttleft.y=tt.y-2;
		point ttright;ttright.x=tt.x;ttright.y=tt.y+2;
		if((panel[ttup.x][ttup.y]==-1)&&checkSnkBody30(snake,gp,ttup,len,t))
			{
				path.push(ttup);
				panel[ttup.x][ttup.y]=1;//visit
				// parent[ttup.x][ttup.y]=tt;//记录父亲结点;
			}
				
			if((panel[ttdown.x][ttdown.y]==-1)&&checkSnkBody30(snake,gp,ttdown,len,t))
			{
				{
				path.push(ttdown);
				panel[ttdown.x][tt.y]=1;//visit
				// parent[ttdown.x][ttdown.y]=tt;//记录父亲结点;
			}
			}
			if((panel[ttleft.x][ttleft.y]==-1)&&checkSnkBody30(snake,gp,ttleft,len,t))
			{
				{
				path.push(ttleft);
				panel[ttleft.x][ttleft.y]=1;//visit
				// parent[ttleft.x][ttleft.y]=tt;//记录父亲结点;
				}
			}
			if((panel[ttright.x][ttright.y]==-1)&&checkSnkBody30(snake,gp,ttright,len,t))
			{
				{
				path.push(ttright);
				panel[ttright.x][ttright.y]=1;//visit
				// parent[ttright.x][ttright.y]=tt;//记录父亲结点;
				}
			}
	}
	return false;
}
void findpathtofood30(point snake[5][100],int len[5],int direct[5],int t,GamePanel gp,int minlocation,int panel[50][100],point parent[50][100])
{
	point tt,next;
	queue30 path;
	 panel[50][100]={-1};// -1表示还未访问过
	point first; first.x=snake[t][1].x;first.y=snake[t][1].y;
	point tail;  tail.x=gp.food[minlocation].x;tail.y=gp.food[minlocation].y;
	path.push(first);
	parent[first.x][first.y].x=-1;
	parent[first.x][first.y].y=-1;
	panel[first.x][first.y]=1;//1 表示已经访问过
	while(!path.empty())
	{
		int size=path.r-path.f;
		while(size--)
		{
			tt=path.front();
			path.pop();
			if(tt.x==tail.x&&tt.y==tail.y)
			{
                //find it
				return;
			}
			point ttup;ttup.x=tt.x-1;ttup.y=tt.y;
			point ttdown;ttdown.x=tt.x+1;ttdown.y=tt.y;
			point ttleft;ttleft.x=tt.x;ttleft.y=tt.y-2;
			point ttright;ttright.x=tt.x;ttright.y=tt.y+2;
			if((panel[ttup.x][ttup.y]==-1)&&checkSnkBody30(snake,gp,ttup,len,t))
			{
				path.push(ttup);
				panel[ttup.x][ttup.y]=1;//visit
				parent[ttup.x][ttup.y]=tt;//记录父亲结点;
			}
				
			if((panel[ttdown.x][ttdown.y]==-1)&&checkSnkBody30(snake,gp,ttdown,len,t))
			{
				{
				path.push(ttdown);
				panel[ttdown.x][tt.y]=1;//visit
				parent[ttdown.x][ttdown.y]=tt;//记录父亲结点;
			}
			}
			if((panel[ttleft.x][ttleft.y]==-1)&&checkSnkBody30(snake,gp,ttleft,len,t))
			{
				{
				path.push(ttleft);
				panel[ttleft.x][ttleft.y]=1;//visit
				parent[ttleft.x][ttleft.y]=tt;//记录父亲结点;
				}
			}
			if((panel[ttright.x][ttright.y]==-1)&&checkSnkBody30(snake,gp,ttright,len,t))
			{
				{
				path.push(ttright);
				panel[ttright.x][ttright.y]=1;//visit
				parent[ttright.x][ttright.y]=tt;//记录父亲结点;
				}
			}
			
		}
	}
	return ;


}
bool check30(point snake[5][100], int len[5], int t, GamePanel gp, int direction ) 
{
	//灏嗕綘鐨刢heck鍑芥暟浣撴斁鍦ㄦ澶勶紝骞跺垹鍘讳笅闈㈢ず渚嬩唬鐮?
	// if (snake[t][1].y == gp.m && direction == 1) return false;
	// if (snake[t][1].y == 2 && direction == 2) return false;
	//绗竴绉嶆儏鍐碉紝涓嶈€冭檻鏂滄柟鍚戣蛋
	if(direction==1)// 鍚戝彸璧?
	{
		
		point next;
		next.x=snake[t][1].x;
		next.y=snake[t][1].y+2;
		// 濡傛灉鍙宠竟鏄殰纰嶇墿
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//濡傛灉鍙宠竟鏄澹?
		if(next.y==gp.m+2)
			return false;
		//濡傛灉鍙宠竟鏄叾浠栶煇?
		/*
		娉ㄦ剰 杩欓噷榛樿浜嗘垜浠搷绾电殑鏄?鍙佛煇?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}

	}
	if(direction==0)//濡傛灉鍚戜笅璧?
	{
		point next;
		next.x=snake[t][1].x+1;
		next.y=snake[t][1].y;
		// 濡傛灉涓嬭竟鏄殰纰嶇墿
		for(int i=0;i<gp.wallnum;i++)
		{
			if(gp.wall[i].x==next.x&&gp.wall[i].y==next.y)
				return false;
		}
		//濡傛灉涓嬭竟鏄澹?
		if(next.x==gp.n+1)
			return false;
		//濡傛灉鍙宠竟鏄叾浠栶煇?
		/*
		娉ㄦ剰 杩欓噷榛樿浜嗘垜浠搷绾电殑鏄?鍙佛煇?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
	}
	if(direction==2)//濡傛灉鍚戝乏璧?
	{
		point next;
		next.x=snake[t][1].x;
		next.y=snake[t][1].y-2;
		// 濡傛灉宸﹁竟鏄殰纰嶇墿
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
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
	}
	if(direction==3)//濡傛灉鍚戜笂璧?
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
	if(direction==4)//鍙充笅鏂?
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
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		if((gp.panel[next.x-1][next.y]==2)&&(gp.panel[next.x][next.y-2]==2))
			return false;
	}
	if(direction==5)//鍙充笂鏂?
	{
		point next;
		next.x=snake[t][1].x-1;
		next.y=snake[t][1].y+2;
		// 濡傛灉鍙充笂杈规槸闅滅鐗?
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//濡傛灉鍙充笂杈规槸澧欏
		if(next.x==0||next.y==gp.m+2)
			return false;
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//濡傛灉鍙充笂涓よ竟閮芥槸澧欏
		if((gp.panel[next.x][next.y-2]==2)&&(gp.panel[next.x+1][next.y]==2))
			return false;
	}
	if(direction==6)//宸︿笂
	{
		point next;
		next.x=snake[t][1].x-1;
		next.y=snake[t][1].y-2;
		// 濡傛灉宸︿笂杈规槸闅滅鐗?
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//濡傛灉宸︿笂杈规槸澧欏
		if(next.x==0)
			return false;
		//濡傛灉鍙宠竟鏄叾浠栶煇?
		/*
		娉ㄦ剰 杩欓噷榛樿浜嗘垜浠搷绾电殑鏄?鍙佛煇?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//濡傛灉宸︿笂涓よ竟閮芥槸澧欏
		if((gp.panel[next.x+1][next.y]==2)&&(gp.panel[next.x][next.y+2]==2))
			return false;
	}
	if(direction==7)//宸︿笅
	{
		point next;
		next.x=snake[t][1].x+1;
		next.y=snake[t][1].y-2;
		// 濡傛灉鍙充笅杈规槸闅滅鐗?
		for(int i=0;i<gp.wallnum;i++)
		{
			if((gp.wall[i].x==next.x)&&(gp.wall[i].y==next.y))
				return false;
		}
		//濡傛灉鍙充笅杈规槸澧欏
		if(next.x==0)
			return false;
		//濡傛灉鍙宠竟鏄叾浠栶煇?
		/*
		娉ㄦ剰 杩欓噷榛樿浜嗘垜浠搷绾电殑鏄?鍙佛煇?
		*/
		for(int i=1;i<=len[1];i++)
		{
			if((snake[1][i].x==next.x)&&(snake[1][i].y==next.y))
				return false;
		}
		//濡傛灉鍙宠竟鏄嚜宸?
		for(int i=1;i<=len[0];i++)
		{
			if(snake[0][i].x==next.x&&snake[0][i].y==next.y)
				return false;
		}
		//濡傛灉鍙充笅涓よ竟閮芥槸澧欏
		if((gp.panel[next.x-1][next.y]==2)&&(gp.panel[next.x][next.y+2]==2))
			return false;
	}
	return true;
}

int machine_move30(point snake[5][100], int len[5], int direct[5], int t, GamePanel gp)	
{
	//灏嗕綘鐨刴achine_move鍑芥暟浣撴斁鍦ㄦ澶勶紝骞跺垹鍘讳笅闈㈢ず渚嬩唬鐮?
	//鏈€绠€鍗曠殑鏂规硶 鎵惧埌鏈€杩戠殑涓€涓彲浠ュ悆鎺夌殑椋熺墿骞跺悆鎺夊畠
	int left=gp.totalfoodnum;
	int distant[left];
	point head;
	head.x=snake[t][1].x;head.y=snake[t][1].y;
	//鐢ㄦ浖鍝堥】璺濈璁＄畻
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
    // int panel[50][100]={-1};
    // point z;z.x=-1;z.y=-1;
    // point parent[50][100]={z};
    // findpathtofood30(snake,len,direct,t,gp,minlocation,panel,parent);
    
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
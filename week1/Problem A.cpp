#include<iostream>
using namespace std;
#define limit 25
int map[limit][limit];
int show[limit][limit];
int n,m,k,l;
 //n: 行数 m:列数 K：雷的数量 l：点击次数
 void cover(int n,int m)
 {
    
     //initialize
     for(int i=0;i<limit;i++)
     {
         for(int j=0;j<limit;j++)
         {
             map[i][j]=-1;
             show[i][j]=-1;
         }
     }
     for(int i=0;i<=m+1;i++)
     {
         map[0][i]=-3;
         map[n+1][i]=-3;
     }
     for(int i=0;i<=n+1;i++)
     {
         map[i][0]=-3;
         map[i][m+1]=-3;
     }
     return;
 }
int countbomb(int x,int y)
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
void open(int x,int y)
{
    if(map[x][y]==-3)
    {
        return;
    }
    else if(countbomb(x,y))
    {
        map[x][y]=countbomb(x,y);
        show[x][y]=countbomb(x,y);
        return;
    }
    else
    {
        if(map[x][y]==-2)
        {
            return;
        }
        //open
        if(map[x][y]==0)
        {
            // already open
            return ;
        }
        map[x][y]=0;
        show[x][y]=0;
       open(x-1,y-1);
       open(x-1,y);
       open(x-1,y+1);
       open(x,y-1);
       open(x,y+1);
       open(x+1,y-1);
       open(x+1,y);
       open(x+1,y+1);
    }
    return;    
}
int tag=0;
int ch=0;// check if have been open  
void click(int x,int y)
{
    if(map[x][y]==-2)
    {
        cout<<"You lose";
        tag=1;
        return;
    }
    else
    {
        // situation1 : already open
        if(map[x][y]!=-1)
        {
            ch=1;
            return;
        }
        //situation2: new 
        open(x,y);
    }
    return;    
}
void pp()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<m;j++)
        {
            cout<<show[i][j]<<" ";
        }
        cout<<show[i][m]<<endl;
    }
}
int tag0=0;
void check()
{
    for(int i=1;i<=n;i++)
    {
        if(tag0==1)
        {
            break;
        }

        //
        for(int j=1;j<=m;j++)
        {
            if(show[i][j]==-1)
            {
                if(map[i][j]==-2)
                    ;
                else
                    tag0=1;                
            }
        }
    }
    return;
}
int main()
{
    cin>>n>>m>>k>>l;
    //k行雷的坐标
    cover(n,m);
    for(int i=0;i<k;i++)
    {
        int x,y;
        cin>>x>>y;
        map[x+1][y+1]=-2;
        //-2 means that there is a bomb
    }
    for(int i=0;i<l;i++)
    {
        //用户点击
        int x,y;
        cin>>x>>y;
        click(x+1,y+1);
        if(tag==1)
        {
            break;
        }
        if(!ch)
        {
            pp();   
        }
        check();
        if(tag0==0)
        {
            cout<<"You win";
            break;
        }
        tag0=0; 
		if(!ch)
		{
		cout<<endl;        	
		 } 
		ch=0;
    }
    return 0;
}
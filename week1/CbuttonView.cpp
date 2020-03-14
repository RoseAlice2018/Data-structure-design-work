

#include "stdafx.h"
#include "Cbutton.h"
#include "CbuttonDoc.h"
#include "CbuttonView.h"
#include <time.h>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDB_ZLH 0

IMPLEMENT_DYNCREATE(CCbuttonView, CView)

BEGIN_MESSAGE_MAP(CCbuttonView, CView)
	//{{AFX_MSG_MAP(CCbuttonView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_MENU_CAPTION, OnMenuCaption)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_OUT, OnMenuOut)
	ON_COMMAND(ID_MACHINE, OnMachine)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()



/******************************************************************************************************************/
/************************************************需要添加的两个函数如下********************************************/
int countbomb(int x, int y, int map[][30])
{
	int countbomb = 0;
	if (map[x - 1][y - 1] == -2)
		countbomb++;
	if (map[x - 1][y] == -2)
		countbomb++;
	if (map[x - 1][y + 1] == -2)
		countbomb++;
	if (map[x + 1][y - 1] == -2)
		countbomb++;
	if (map[x + 1][y] == -2)
		countbomb++;
	if (map[x + 1][y + 1] == -2)
		countbomb++;
	if (map[x][y - 1] == -2)
		countbomb++;
	if (map[x][y + 1] == -2)
		countbomb++;
	return countbomb;
}
int countblank(int map[][30], int x, int y)
{
	int countbomb = 0;
	if (map[x - 1][y - 1] == -1)
		countbomb++;
	if (map[x - 1][y] == -1)
		countbomb++;
	if (map[x - 1][y + 1] == -1)
		countbomb++;
	if (map[x + 1][y - 1] == -1)
		countbomb++;
	if (map[x + 1][y] == -1)
		countbomb++;
	if (map[x + 1][y + 1] == -1)
		countbomb++;
	if (map[x][y - 1] == -1)
		countbomb++;
	if (map[x][y + 1] == -1)
		countbomb++;
	return countbomb;
}
void tag(int map[][30], int x, int y)
{
	if (map[x - 1][y - 1] == -1)
		map[x - 1][y - 1] = -2;
	if (map[x - 1][y] == -1)
		map[x - 1][y] = -2;
	if (map[x - 1][y + 1] == -1)
		map[x - 1][y + 1] = -2;
	if (map[x + 1][y - 1] == -1)
		map[x + 1][y - 1] = -2;
	if (map[x + 1][y] == -1)
		map[x + 1][y] = -2;
	if (map[x + 1][y + 1] == -1)
		map[x + 1][y + 1] = -2;
	if (map[x][y - 1] == -1)
		map[x][y - 1] = -2;
	if (map[x][y + 1] == -1)
		map[x][y + 1] = -2;
}
void changexy(int map[][30], int i, int j, int& x, int& y)
{

	if (map[i - 1][j - 1] == -1)
	{
		x = i - 1;
		y = j - 1;
		return;
	}
	if (map[i - 1][j] == -1)
	{
		x = i - 1;
		y = j;
		return;
	}
	if (map[i - 1][j + 1] == -1)
	{
		x = i - 1;
		y = j + 1;
		return;
	}
	if (map[i + 1][j - 1] == -1)
	{
		x = i + 1;
		y = j - 1;
		return;
	}
	if (map[i + 1][j] == -1)
	{
		x = i + 1;
		y = j;
		return;
	}
	if (map[i + 1][j + 1] == -1)
	{
		x = i + 1;
		y = j + 1;
		return;
	}
	if (map[i][j - 1] == -1)
	{
		x = i;
		y = j - 1;
		return;
	}
	if (map[i][j + 1] == -1)
	{
		x = i;
		y = j + 1;
		return;
		///注意 xy返回的时候要--
	}
}
int setbomb(int map[][30], int n, int m, int& x, int& y)
{
	int tagg = 0;
	//a)如果格子周围未确定的格子个数加上被标记的雷的个数等于中央数字，则剩余格子都是雷
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] > 0 && (map[i][j] == countblank(map, i, j) + countbomb(i, j, map)))
			{
				//将剩余的格子标记为雷
				tag(map, i, j);
				// tagg=1;
			}
		}
	}
	//b)如果周围的格子被标记的个数已经达到了中央数字，则其他格子不是雷
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j] == countbomb(i, j, map))
			{
				if (countblank(map, i, j) > 0)
				{
					tagg = 1;
					changexy(map, i, j, x, y);
					x--;
					y--;
					return tagg;
				}
			}
		}
	}
	return tagg;
}
void open(int x, int y, int show[][30], int mapp[][30])
{
	if (mapp[x][y] == -3)
	{
		return;
	}
	else if (countbomb(x, y, mapp) > 0 && mapp[x][y] != -2)
	{
		mapp[x][y] = countbomb(x, y, mapp);
		show[x - 1][y - 1] = mapp[x][y];
		return;
	}
	else
	{
		if (mapp[x][y] == -2)
		{
			return;
		}
		//open
		if (mapp[x][y] == 0)
		{
			// already open
			return;
		}
		mapp[x][y] = 0;
		show[x - 1][y - 1] = 0;
		open(x - 1, y - 1, show, mapp);
		open(x - 1, y, show, mapp);
		open(x - 1, y + 1, show, mapp);
		open(x, y - 1, show, mapp);
		open(x, y + 1, show, mapp);
		open(x + 1, y - 1, show, mapp);
		open(x + 1, y, show, mapp);
		open(x + 1, y + 1, show, mapp);

	}
	return;
}
//set函数重新设置一下数组
void sett(int show[][30], int min[][30], int n, int m, int mapp[][30])
{
	//initialize
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			mapp[i][j] = -1;
		}
	}
	for (int i = 0; i <= m + 1; i++)
	{
		mapp[0][i] = -3;
		mapp[n + 1][i] = -3;
	}
	for (int i = 0; i <= n + 1; i++)
	{
		mapp[i][0] = -3;
		mapp[i][m + 1] = -3;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			mapp[i + 1][j + 1] = show[i][j];
			if (min[i][j] == 1)
			{
				mapp[i + 1][j + 1] = -2;
			}
		}
	}
	return;
}
void click(int x, int y, int show[][30], int n, int m, int mapp[][30])
{
	open(x, y, show, mapp);
}
int CCbuttonView::RefreshGamePanel(int GamePanel[30][30], int x, int y, int mine[30][30], int n, int m, int k)
{
	//请将你封装的RefreshGamePanel函数体添加到此处，并去掉下行的return 0
	if (mine[x][y] == 1)
		return -1;
	int mapp[30][30];
	sett(GamePanel, mine, n, m, mapp);
	click(x + 1, y + 1, GamePanel, n, m, mapp);
	int num = 0;
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


void CCbuttonView::machine(int GamePanel[30][30], int n, int m, int &x, int &y)
{
	int x1 = x;
	int y1 = y;
	int map[30][30];
	//copy
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			map[i + 1][j + 1] = GamePanel[i][j];
	}
	for (int i = 0; i <= n + 1; i++)
	{
		map[i][0] = -3;
		map[i][m + 1] = -3;
	}
	for (int i = 0; i <= m + 1; i++)
	{
		map[0][i] = -3;
		map[n + 1][i] = -3;
	}
	//对该数组进行操作
	//step1： 对雷进行标记，同时进行最简单的寻路操作
	int t = 1;

	t = setbomb(map, n, m, x, y);
	//此时已经决策出了下一个点
	if ((x != x1) || (y != y1))
	{
		return;
	}

	//step2: 当以上两种方法不能再翻开格子或者标记雷时，挑选任意一个周围仍然有未确定格子的数字，穷举周围格子的可能分布
	x = rand() % 20;
	y = rand() % 20;
	return;
}
/************************************************需要添加的两个函数如上********************************************/
/******************************************************************************************************************/
















/*************************************以下代码不用管********************************************/
CCbuttonView::CCbuttonView()
{

	// TODO: add construction code here
	srand(int(time(0)));
	minenum=50;
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
		{	
			mine[i][j]=0;
			GamePanel[i][j]=-1;
		}

	for(int k=0;k<minenum;k++)
	{
		i=rand()%20;
		j=rand()%20;
		while(mine[i][j]!=0)
		{
			i=rand()%20;
			j=rand()%20;
		}
		mine[i][j]=1;
	}
	x=0;y=0;
	id=0;
	i=0;j=0;
	showmine=-1;
	win=0;
	current_j=-1;
	current_i=-1;
}

CCbuttonView::~CCbuttonView()
{
}


void CCbuttonView::OnMenuNew() 
{
	// TODO: Add your command handler code here
	for(i=0;i<20;i++)
		for(j=0;j<20;j++)
		{	
			mine[i][j]=0;
			GamePanel[i][j]=-1;
			::ShowWindow(cbutton[i][j],SW_SHOW);
		}
		
		for(int k=0;k<minenum;k++)
		{
			i=rand()%20;
			j=rand()%20;
			while(mine[i][j]!=0)
			{
				i=rand()%20;
				j=rand()%20;
			}
			mine[i][j]=1;
		}
		x=0;y=0;
		id=0;
		i=0;j=0;
		win=0;
		showmine=-1;
		current_i=-1;
		current_j=-1;
		CRect rect1;
		GetClientRect(&rect1);
		InvalidateRect(rect1);

}
void CCbuttonView::OnMenuOut() 
{
	// TODO: Add your command handler code here
	 
	//PostQuitMessage(0);
	exit(0) ;
}


BOOL CCbuttonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView drawing

void CCbuttonView::OnDraw(CDC* pDC)
{
	CCbuttonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView printing

BOOL CCbuttonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCbuttonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCbuttonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView diagnostics

#ifdef _DEBUG
void CCbuttonView::AssertValid() const
{
	CView::AssertValid();
}

void CCbuttonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCbuttonDoc* CCbuttonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCbuttonDoc)));
	return (CCbuttonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCbuttonView message handlers

int CCbuttonView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	id = 0;
	x=0;y=0;
	int realid;
	for(i=0;i<20;i++)
	 {
		 for(j=0;j<20;j++)
		 {
			 if (id == 0) realid = 1;
			 else realid = id;
			  cbutton[i][j].Create("",WS_CHILD | WS_VISIBLE,CRect(x,y,x+20,y+20),this,realid);
			  x+=20;
			  id+=20;
		 }
		 x=0;
		 y+=20;
	 }
     return 0;
}

void CCbuttonView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	
	CView::OnLButtonDown(nFlags, point);
}


void CCbuttonView::OnRButtonDown(UINT nFlags, CPoint point)			 
{
	// TODO: Add your message handler code here and/or call default
	/*for(int k=0;k<20;k++)
	{
	  ::ShowWindow(cbutton[i_lei[k]][j_lei[k]],SW_HIDE);
	}*/
	showmine*=-1;
		CClientDC dc(this);
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP_LEI);
	if(showmine==1)
	{
	
		CBrush brush(&bitmap);
		//cbutton[0][0].SetBitmap();
		//dc.FillRect(CRect(point.x,point.y,point.x+20,point.y+20),&brush);
		
		for(i=0;i<20;i++)
		{
			 for(j=0;j<20;j++)
			 {
				 if(mine[i][j]==1)
				 {
					 dc.FillRect(CRect(j*20,i*20,j*20+20,i*20+20),&brush);
				 }
			 }
		}
	}
	else{
	
		CRect rect1;
		GetClientRect(&rect1);
		InvalidateRect(rect1);
	}
	//cbutton[0][0].SetBitmap(bitmap);

	CView::OnRButtonDown(nFlags, point);
}

void CCbuttonView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
    CBrush brush(RGB(255,255,255));
	dc.SelectObject(&brush);
	dc.FillRect(CRect(0,0,800,600),&brush);

	CPen pen(PS_SOLID,1,RGB(180,180,180));
 
	for( i=0;i<420;i+=20)
	{
		dc.SelectObject(&pen);
		dc.MoveTo(i,0);
		dc.LineTo(i,440);
		dc.MoveTo(0,i);
		dc.LineTo(400,i);
	}
				
    COLORREF col=dc.SetBkColor(RGB(255,255,255));
	dc.SetTextColor(RGB(0,0,255));

	if(win==0)
	{

		for(i=0;i<20;i++)
            for(j=0;j<20;j++)
			{
				if(GamePanel[i][j]==0)
					::ShowWindow(cbutton[i][j],SW_HIDE);
				else if(GamePanel[i][j]>0 && GamePanel[i][j]<9)
				{
					::ShowWindow(cbutton[i][j],SW_HIDE);
					str.Format("%d",GamePanel[i][j]);
					dc.SetTextColor(RGB(0,0,255));
					dc.DrawText(str,CRect(j*20,i*20,j*20+20,i*20+20),DT_CENTER);
				}
			}
	}
	else if(win==-1 || win==1)
	{
		
		for(i=0;i<20;i++)
            for(j=0;j<20;j++)
			{
				if(GamePanel[i][j]==0)
					::ShowWindow(cbutton[i][j],SW_HIDE);
				else if(GamePanel[i][j]>0 && GamePanel[i][j]<9)
				{
					::ShowWindow(cbutton[i][j],SW_HIDE);
					str.Format("%d",GamePanel[i][j]);
					dc.SetTextColor(RGB(0,0,255));
					dc.DrawText(str,CRect(j*20,i*20,j*20+20,i*20+20),DT_CENTER);
				}
				CBitmap bitmap,bitmap1;
				bitmap.LoadBitmap(IDB_BITMAP_LEI);
				CBrush brush(&bitmap);
		
				if(mine[i][j]==1)
				{
					::ShowWindow(cbutton[i][j],SW_HIDE);
					
					if(win==-1 && current_i==i && current_j==j)
					{
						bitmap1.LoadBitmap(IDB_REDMINE_BITMAP);
						CBrush brush1(&bitmap1);
						dc.FillRect(CRect(j*20,i*20,j*20+20,i*20+20),&brush1);
					}
					else dc.FillRect(CRect(j*20,i*20,j*20+20,i*20+20),&brush);

				}

			}
	}
	// Do not call CView::OnPaint() for painting messages
}


void CCbuttonView::OnCancelMode() 
{
	CView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CCbuttonView::OnMenuCaption() 
{
	// TODO: Add your command handler code here

  MessageBox("简易版扫雷游戏图形界面框架","扫雷");
}


BOOL CCbuttonView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
    
	int ii,jj,k,ButtonCmdId=LOWORD(wParam);
	if (ButtonCmdId == 1)
	{
		ii = 0;
		jj = 0;
	}
	else
	{
		ii = (ButtonCmdId / 400);
		jj = (ButtonCmdId - 400 * ii) / 20;
	}

		/************************************************************************/
		/***/ win=RefreshGamePanel(GamePanel,ii,jj,mine,20,20,minenum); /********/
        /************************************************************************/

		CRect rect1;
		GetClientRect(&rect1);
		current_j=jj;
		current_i=ii;
		
		if(win==-1 || win==1)
		{
			InvalidateRect(rect1);
		
			if(win==-1)
				MessageBox("你输了！点击确定重新开始","扫雷",MB_ICONEXCLAMATION);
			else MessageBox("恭喜，你赢了！点击确定重新开始","扫雷",MB_ICONINFORMATION);
			for(i=0;i<20;i++)
				for(j=0;j<20;j++)
				{	
					mine[i][j]=0;
					GamePanel[i][j]=-1;
					::ShowWindow(cbutton[i][j],SW_SHOW);
				}
			
			for(int k=0;k<minenum;k++)
			{
				i=rand()%20;
				j=rand()%20;
				while(mine[i][j]!=0)
				{
					i=rand()%20;
					j=rand()%20;
				}
				mine[i][j]=1;
			}
			x=0;y=0;
			id=0;
			i=0;j=0;
			win=0;
			showmine=-1;
			current_i=-1;
			current_j=-1;
			machinestart=false;
		}
		//InvalidateRect(rect1);
		{
			CClientDC dc(this); // device context for painting
			for(i=0;i<20;i++)
				for(j=0;j<20;j++)
				{
					if(GamePanel[i][j]==0)
						::ShowWindow(cbutton[i][j],SW_HIDE);
					else if(GamePanel[i][j]>0 && GamePanel[i][j]<9)
					{
						::ShowWindow(cbutton[i][j],SW_HIDE);
						str.Format("%d",GamePanel[i][j]);
						dc.SetTextColor(RGB(0,0,255));
						dc.DrawText(str,CRect(j*20,i*20,j*20+20,i*20+20),DT_CENTER);
					}
				}
			
		}
	
	return CView::OnCommand(wParam, lParam);
}

void CCbuttonView::OnMachine() 
{
	// TODO: Add your command handler code here
	int x=-1,y=-1;
	machinestart=true;
	int tim=50,count=0;
	while(machinestart && count<400)
	{
		/*************************************************/
		/*********/machine(GamePanel,20,20, x,y);/********/
		/*************************************************/
		if (x<0 || x>19 || y<0 || y>19) break;
		count++;
		SendMessage(WM_COMMAND,MAKEWPARAM(x*400+20*y,BN_CLICKED),0); 
		Sleep(tim);
	}
}
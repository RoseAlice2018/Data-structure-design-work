#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<limits.h>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<iostream>
using namespace std;

#define BLACK 0
#define WHITE 1
#define EMPTY 2

int MoveRoadX[4] = { 0,1,1,1 };//���������ƶ�����
int MoveRoadY[4] = { 1,0,-1,1 };
int Width;//���������
int Depth;//���������



struct Point { //��ṹ
  int x, y;
};
struct Step { //���ṹ
  Point first, second;
  int value;
};
struct pointincludevalue
{
	int x,y;
	int value;
};
struct TreeNode {//������ʹ�õĽڵ�
  vector<Point>ComputerChess;//�ҷ��������
  vector<Point>EnemyChess;//�з��������
  int BeginX, BeginY;//��Χ
  int EndX, EndY;
  int value;//��ǰ��������
  vector<TreeNode*> Son;
};

int Board[19][19];//�洢������Ϣ����Ԫ��ֵΪ BLACK, WHITE, EMPTY ֮һ��·�����ķ���ο�github��"����˳���Լ����յ㷽��.png"
int comparee(Step a,Step b)// ���մӴ�С��˳������
{
    return a.value<b.value;
}
int comparee2(Step a,Step b)// ���մ�С�����˳������
{
    return a.value>b.value;
}                 
int IfNot_Road(int Board[19][19], int RangeBeginX, int RangeBeginY, int RangeEndX, int RangeEndY, int BeginX, int BeginY, int &flag, int dir, int limit, Point LimitChess) {//�ж��Ƿ���һ��·
  int num = 0;//�����·�����е����Ӹ���
  if (BeginX < RangeBeginX || BeginX >RangeEndX || BeginX + 5 * MoveRoadX[dir] < RangeBeginX || BeginX + 5 * MoveRoadX[dir] > RangeEndX) return -1;//��������Χ�����и���Ϊ��㣬������������Χ
  if (BeginY < RangeBeginY || BeginY >RangeEndY || BeginY + 5 * MoveRoadX[dir]< RangeBeginY || BeginY + 5 * MoveRoadX[dir] >RangeEndY) return -1;//���ӱ������β�RangeBeginX/Y��RangeEndX/Y,Ŀǰ��EndBegin��·������յ�
  //2����δ�������ӣ�1���ӣ�0���ӡ�
  int a = BeginX, b = BeginY;
  for (int i = 0; i < 6; i++) {
    a = BeginX + i * MoveRoadX[dir];//��ͬ�ķ���
    b = BeginY + i * MoveRoadY[dir];
    if (limit == 1 && LimitChess.x == a && LimitChess.y == b) return -1;//�������ۺ������ظ�����·ʹ��
    else if (Board[a][b] == EMPTY) continue;
    else if (Board[a][b] == BLACK && flag == 1) return -1;//����-1������·
    else if (Board[a][b] == WHITE && flag == 0) return -1;
    else if (Board[a][b] == BLACK) {
      num++;
      flag = 0;
    }
    else if (Board[a][b] == WHITE) {
      num++;
      flag = 1;
    }
  }
  return num;//�������Ӹ���
}

int ALL_EvalueFucation(int VirtualBoard[19][19], int RangeBeginX,int RangeBeginY,int RangeEndX,int RangeEndY,int ComputerSide) {//ȫ�����ۺ���
  
  int NumOfMyRoad[7] = { 0,0,0,0,0,0,0 };//��ͬ��������·������
  int NumOfEnemyRoad[7]= { 0,0,0,0,0,0,0 };
  int ScoreOfRoad[7] = {};//��ͬ��������·�ķ���
  
  for (int dir = 0; dir < 4; dir++) {
    for (int i = RangeBeginX; i <= RangeEndX; i++) {//��ÿ�е�·���з���
      for (int j = RangeBeginY; j <= RangeEndY; j++) {
        int flag = 2;
        int limit = 0;
        
        Point fake;//�ٵģ�ֻΪ����βΣ����Ժ���
        fake.x = -1;fake.y = 1;
        
        int num = IfNot_Road(VirtualBoard,RangeBeginX, RangeBeginY, RangeEndX, RangeEndY, i, j, flag, dir, limit, fake);
        if (num == -1)continue;
        
        if (flag == ComputerSide) NumOfMyRoad[num]++;
        else NumOfEnemyRoad[num]++;
      }
    }
  }
  int Score=0;
  for (int i = 0; i < 7; i++) {
    Score += NumOfMyRoad[i] * ScoreOfRoad[i] - NumOfEnemyRoad[i] * ScoreOfRoad[i];
  }
  return Score;
}
vector<pointincludevalue> firstsection(int Board[19][19],int computerside,int w)
{
   vector<pointincludevalue> LL;
  for(int i=0;i<19;i++)
  {
	 for(int j=0;j<19;j++)
	  {
		 if(Board[i][j]==EMPTY)// �Կյ���й�ֵ
		 {
			 pointincludevalue temp;temp.x=i;temp.y=j;
       Point firstchess;firstchess.x=temp.x;firstchess.y=temp.y;
			  temp.value=ALL_EvalueFucation(Board,0,0,19,19,computerside);
			 LL.push_back(temp);
		 }
	  }
 }
  //sort()
  sort(LL.begin(),LL.end(),comparee2);//�Ӵ�С
  while (LL.size()>w)
  {
    /* code */
    LL.pop_back();
  }
  return LL;
}
Step PreSeek_ReturnEmpty(int Board[19][19], int RangeBeginX, int RangeBeginY, int RangeEndX, int RangeEndY, int BeginX, int BeginY ,int dir,int WillWin,int ComputerSide) {//Ѱ��һ��·����>=4�����ӵĿ�λ

  Step ReturnEmpty;//�˺���Ҫ�����ߵ�Ҫ��
  ReturnEmpty.first.x = -1;
  ReturnEmpty.first.y = -1;
  ReturnEmpty.second.x = -1;
  ReturnEmpty.second.y = -1;
  
  int a = BeginX, b = BeginY;
  if (WillWin) {//�����Ѿ��γ����������·,ֱ�ӷ��ؿյ�λ�����ӣ���ֱ�ӻ�ʤ
    for (int i = 0; i < 6; i++) {
      a = BeginX + i * MoveRoadX[dir];
      b = BeginY + i * MoveRoadY[dir];
      if (Board[a][b] == EMPTY) {
        if (ReturnEmpty.first.x != -1) {
          ReturnEmpty.second.x = a;
          ReturnEmpty.second.y = b;
          return ReturnEmpty;
        }
        else {
          ReturnEmpty.first.x = a;
          ReturnEmpty.first.y = b;
        }
      }
    }
    return ReturnEmpty;
  }
  else {//�з��γ������������� 
    int FirstNotEmptyFlag = 0;
    Point FirstNotEmpty,LastNotEmpty;
    for (int i = 0; i < 6; i++) {//�ҵ�һ����λ�ã�����з������ڡ�
      a = BeginX + i * MoveRoadX[dir];
      b = BeginY + i * MoveRoadY[dir];
      if (i != 5 && Board[a][b] == EMPTY && Board[a + MoveRoadX[dir]][b + MoveRoadY[dir]] != EMPTY) {//ʹĿ��λ�ý�����ǰ����
        ReturnEmpty.first.x = a;
        ReturnEmpty.first.y = b;
        break;
      }
      else if (i == 5 && Board[a][b] == EMPTY) {
        ReturnEmpty.first.x = a;
        ReturnEmpty.first.y = b;
        break;
      }
    }
    for (int i = 0; i < 6; i++) {//�л��Ļ���������������ʼ���
      a = BeginX + i * MoveRoadX[dir];
      b = BeginY + i * MoveRoadY[dir];
      if (Board[a][b] != EMPTY && FirstNotEmptyFlag == 0) {//��ǵ�һ��·�Ϸǿյ�λ�ã����ڼ����ĵȱ����������ӵ����
        FirstNotEmptyFlag = 1;
        FirstNotEmpty.x = a;
        FirstNotEmpty.y = b;
      }
      if (Board[a][b] != EMPTY && FirstNotEmptyFlag == 0) {
        LastNotEmpty.x = a;
        LastNotEmpty.y = b;
      }
    }

    int OriginColor = Board[ReturnEmpty.first.x][ReturnEmpty.first.y];//��ʱ�ı�board
    Board[ReturnEmpty.first.x][ReturnEmpty.first.y] = ComputerSide;
    
    int flag = 2;
    int limit = 0;
    int num1, num2;
    
    Point Fake;
    Fake.x = -1;
    Fake.y = -1;
     num1 = IfNot_Road(Board, RangeBeginX,  RangeBeginY,RangeEndX, RangeEndY, FirstNotEmpty.x,  FirstNotEmpty.y,flag, dir,limit,Fake);
     num2 = IfNot_Road(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY, LastNotEmpty.x-5*MoveRoadX[dir],LastNotEmpty.y-5*MoveRoadY[dir], flag, dir, limit, Fake);
    
    if (num1 >= 4||num2 >= 4) {//�ӵ�һ�������������������һ����㷴�����
      Point FindSecondChess;
      if (num1 >= 4) {
        FindSecondChess.x = FirstNotEmpty.x;
        FindSecondChess.y = FirstNotEmpty.y;
      }
      else {
        FindSecondChess.x = LastNotEmpty.x - 5 * MoveRoadX[dir];
        FindSecondChess.y = LastNotEmpty.y - 5 * MoveRoadY[dir];
      }
      
      for (int i = 0; i < 6; i++) {//�ҵ�һ����λ�ã�����з������ڡ�
        a = FindSecondChess.x + i * MoveRoadX[dir];
        b = FindSecondChess.y + i * MoveRoadY[dir];
        if (i != 5 && Board[a][b] == EMPTY && Board[a + MoveRoadX[dir]][b + MoveRoadY[dir]] != EMPTY) {//ʹĿ��λ�ý�����ǰ����
          ReturnEmpty.second.x = a;
          ReturnEmpty.second.y = b;
          break;
        }
        else if (i == 5 && Board[a][b] == EMPTY) {
          ReturnEmpty.second.x = a;
          ReturnEmpty.second.y = b;
          break;
        }
      }
    }
    Board[ReturnEmpty.first.x][ReturnEmpty.first.y] = OriginColor;//�ָ�board
    return ReturnEmpty;//���ر����ӵ�����
  }
  return ReturnEmpty;
}

Step PreSeek(int Board[19][19],int RangeBeginX, int RangeBeginY, int RangeEndX, int RangeEndY,int ComputerSide) {//�ж����������·�Ƿ��л��ģ����壬����
  
  Step ReturnStep;
  ReturnStep.first.x = -1;
  ReturnStep.first.y = -1;
  ReturnStep.second.x = -1;
  ReturnStep.second.y = -1;

  for (int i = RangeBeginX; i <= RangeEndX; i++) {//��Ŀǰ������Χ�����и���Ϊ���
    for (int j = RangeBeginY; j <= RangeEndY; j++) {
      for (int dir = 0; dir < 4; dir++) {//һ��������ĸ�����
        int num = 0;
        int flag = 2;
        Point Fake;
        Fake.x = -1;
        Fake.y = -1;

        num = IfNot_Road(Board,  RangeBeginX, RangeBeginY,  RangeEndX, RangeEndY, i, j,flag, dir,0,Fake);
        if (num == -1||num<4) continue;
        
        int WillWin;
        if (ComputerSide==flag) {//�������Ļ�����
          WillWin=1;
          ReturnStep=PreSeek_ReturnEmpty(Board, RangeBeginX,  RangeBeginY,  RangeEndX, RangeEndY, i, j, dir, WillWin,ComputerSide);
          return ReturnStep;
        }
        else {//�з����Ļ�����
          WillWin = 0;
          ReturnStep = PreSeek_ReturnEmpty(Board,  RangeBeginX,  RangeBeginY,  RangeEndX,  RangeEndY, i, j,  dir, 0,ComputerSide);
          return ReturnStep;
        }
      }
    }
  }
  return ReturnStep;
}

void BoardRange(int Board[19][19],int &RangeBeginX, int &RangeBeginY,int &RangeEndX,int& RangeEndY ) {//20,-1,20,-1//�Ѳ���
  
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 19; j++) {
      if (Board[i][j] != EMPTY) {
        if (i < RangeBeginX) RangeBeginX = i;
        if (i > RangeEndX)RangeEndX = i;
        if (j < RangeBeginY)RangeBeginY = j;
        if (j > RangeEndY)RangeEndY = j;
      }
    }
  }
  for (int i = 1; i <= 2; i++) {//����Χ����������λ���õ���Ҫ�������ӵ�����
    if (RangeBeginX != 0) RangeBeginX--;
    if (RangeBeginY != 0) RangeBeginY--;
    if (RangeEndX != 18) RangeEndX++;
    if (RangeEndY != 18) RangeEndY++;
  }
  return;
}

int PartScore_EvalueFucation(int Board[19][19],int  RangeBeginX,int RangeBeginY,int RangeEndX,int RangeEndY, Point FirstChess, Point LimitChess,int ComputerSide,int limit) {
  int sum = 0;                                            //���Firstchess��Ϊ�գ�board����FirstChess�ı��
  int NumOfMyRoad[7] = { 0,0,0,0,0,0,0 };//��ͬ��������·������
  int NumOfEnemyRoad[7] = { 0,0,0,0,0,0,0 };
  int ScoreOfRoad[7] = {};//��ͬ��������·�ķ���!!!
  int MoveRoadX[4] = { 0,1,1,1 };
  int MoveRoadY[4] = { 1,0,-1,1 };
  for (int dir = 0; dir < 4; dir++) {
    for (int i = 0; i < 6; i++) {//���ϵ�·
      Point Begin;
      Begin.y = FirstChess.y - i * MoveRoadY[dir];//����㣬������·�����ķ����෴
      Begin.x = FirstChess.x - i * MoveRoadX[dir];
      int flag = 2;
      int num = IfNot_Road(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY, Begin.x, Begin.y, flag, dir,limit,LimitChess);
      if (num == -1) continue;
      else {
        if (flag == ComputerSide) {
          NumOfMyRoad[num]++;
        }
        else {
          NumOfEnemyRoad[num]++;
        }
      }
    }
  }
  int score;
  for (int i = 0; i < 7; i++) {
    score += NumOfMyRoad[i] * ScoreOfRoad[i] - NumOfEnemyRoad[i] * ScoreOfRoad[i];
  }
  return score;
}
int Part_EvalueFucation(int Board[19][19],Point FirstChess,Point SecondChess,int ComputerSide) {//
  int Score1, Score2;
  int RangeBeginX = 20; int RangeBeginY = 20;//Ŀǰ������Χ��ʼ��
  int RangeEndX = -1; int RangeEndY = -1;
  
  BoardRange(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY);//����̽�����淶Χ
  Board[FirstChess.x][FirstChess.y] = EMPTY;//�ı�ԭ����
  Board[SecondChess.x][SecondChess.y] = EMPTY;
  int Before=PartScore_EvalueFucation(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY, FirstChess, SecondChess, ComputerSide, 0) + PartScore_EvalueFucation(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY, SecondChess, FirstChess, ComputerSide, 1);
  
  Board[FirstChess.x][FirstChess.y] = ComputerSide;//�ָ�ԭ����
  Board[SecondChess.x][SecondChess.y] = ComputerSide;
  int After= PartScore_EvalueFucation(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY,FirstChess, SecondChess, ComputerSide, 0) + PartScore_EvalueFucation(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY,SecondChess, FirstChess, ComputerSide, 1);
  
  return After - Before;//���ؾֲ�����
}

queue<Step> GenerateSon(int Board[19][19],int w,int ComputerSide,int OneOrTwo_Flag,int MaxorMIn) //ѡ��һ����㻹���������
{
  // �����ڵ������
  if(OneOrTwo_Flag==0)
  {
    //�����ӽڵ���к���
	  // 1.1 �����еĿյ�������������������ֵ��С�������У������¼�ڱ�L�С�ע������ֻ���ع�ֵ��ߵ�w����
	  vector<pointincludevalue> L;
	  L= firstsection(Board,ComputerSide,w);
 	  //1.2 ��L�� ȡ����ֵ��ߵ�W���㣬 ����s1��s2,s3,s4,s5..)
 	  vector<pointincludevalue> S;S=L;
  	vector<vector<pointincludevalue> > Li;
 	  vector<vector<Step> > LC;
  	for(int i=0;i<w;i++)
 	  {
	 	//3.1 ��si ������һ�����ӣ� Ȼ��ִ������1�Ĳ��������¶�ʣ�µĿյ���й�ֵ�����򣬽����¼��Li�ĵ�i����λ��
		Board[S[i].x][S[i].y]=ComputerSide;//��S[i]������һ������
		Li[i]=firstsection(Board,ComputerSide,w);
		//3.2 ��Li��ȡ����ֵ��ߵ�wi���㣬 ����si������������
		vector<Step> LLc;
		for(int j=0;j<w;j++)
		{
			//������ظ��߷������Թ�
      Step temp;temp.value=0;
			temp.first.x=S[i].x;temp.first.y=S[i].y;
			temp.second.x=Li[i][j].x;temp.second.y=Li[i][j].y;
      LLc.push_back(temp);
		}
		LC.push_back(LLc);
    //��Board���и�ԭ
    Board[S[i].x][S[i].y]=EMPTY;
    }
    //4 ����LC���߷������µ���� �����µ���ֹ�ֵ ���߷� �԰��� �µĹ�ֵ���� ������ѡ����õ�B���߷��ԡ�
    //������B����W��
    vector<Step> res;
    for(int i=0;i<LC.size();i++)
    {
      for(int j=0;j<LC[0].size();j++)
      {
          res.push_back(LC[i][j]);
      }
    }   
    //sort();
      if(MaxorMIn==-1)// Min ��С�������
        sort(res.begin(),res.end(),comparee);
      else if(MaxorMIn==1)
        sort(res.begin(),res.end(),comparee2);
    while (res.size()>w)
    {
      res.pop_back();
    }
    queue<Step> r;
    for(int i=0;i<res.size();i++)
    {
      r.push(res[i]);
    }
    return r;
    }
	else if(OneOrTwo_Flag==1)//��ʾһ���ڵ��Ѿ�ȷ��
  {
    
  }
  



}
queue<Step> GenerateSon2(int Board[19][19],int w,int ComputerSide,int OneOrTwo_Flag,int MaxorMIn,Point fornode)
{
    //�����ӽڵ���к���
	  // 1.1 �����еĿյ�������������������ֵ��С�������У������¼�ڱ�L�С�ע������ֻ���ع�ֵ��ߵ�w����
	  vector<pointincludevalue> L;
	  L= firstsection(Board,ComputerSide,w);
 	  //1.2 ��L�� ȡ����ֵ��ߵ�W���㣬 ����s1��s2,s3,s4,s5..)
 	  vector<pointincludevalue> S;S=L;
  	vector<vector<pointincludevalue> > Li;
 	  vector<vector<Step> > LC;
  	for(int i=0;i<w;i++)
 	  {
	 	//3.1 ��si ������һ�����ӣ� Ȼ��ִ������1�Ĳ��������¶�ʣ�µĿյ���й�ֵ�����򣬽����¼��Li�ĵ�i����λ��
		Board[S[i].x][S[i].y]=ComputerSide;//��S[i]������һ������
		Li[i]=firstsection(Board,ComputerSide,w);
		//3.2 ��Li��ȡ����ֵ��ߵ�wi���㣬 ����si������������
		vector<Step> LLc;
		for(int j=0;j<w;j++)
		{
			//������ظ��߷������Թ�
      Step temp;temp.value=0;
			temp.first.x=S[i].x;temp.first.y=S[i].y;
			temp.second.x=fornode.x;temp.second.y=fornode.y;
      LLc.push_back(temp);
		}
		LC.push_back(LLc);
    //��Board���и�ԭ
    Board[S[i].x][S[i].y]=EMPTY;
    }
    //4 ����LC���߷������µ���� �����µ���ֹ�ֵ ���߷� �԰��� �µĹ�ֵ���� ������ѡ����õ�B���߷��ԡ�
    //������B����W��
    vector<Step> res;
    for(int i=0;i<LC.size();i++)
    {
      for(int j=0;j<LC[0].size();j++)
      {
          res.push_back(LC[i][j]);
      }
    }   
    //sort();
      if(MaxorMIn==-1)// Min ��С�������
        sort(res.begin(),res.end(),comparee);
      else if(MaxorMIn==1)
        sort(res.begin(),res.end(),comparee2);
    while (res.size()>w)
    {
      res.pop_back();
    }
    queue<Step> r;
    for(int i=0;i<res.size();i++)
    {
      r.push(res[i]);
    }
    return r;
}


Step GetFrontNode(queue<Step> Son) {//�õ�����ͷ�ڵ㲢pop��
  Step ReturnNode;
  ReturnNode = Son.front();
  Son.pop();
  return ReturnNode;
}

int NegaMax_AlphaBeta(TreeNode *Node, int Alpha,int Beta,int depth,int ComputerSide) {//������ֵ����
  
  int NegaBoard[19][19];//��ǰ���ڵ����
  
  int EnemySide;//���˵���ɫ
  if (ComputerSide == BLACK)EnemySide = WHITE;
  else EnemySide = BLACK;

  for (int i = 0; i < 19; i++) {//�����ʼ��
    for (int j = 0; j < 19; j++) {
      NegaBoard[i][j] = EMPTY;
    }
  }
  for (int i = 0; i < Node->ComputerChess.size(); i++) {
    NegaBoard[Node->ComputerChess[i].x][Node->ComputerChess[i].y] = ComputerSide;
  }
  for (int i = 0; i < Node->EnemyChess.size(); i++) {
    NegaBoard[Node->EnemyChess[i].x][Node->EnemyChess[i].y] = EnemySide;
  }
  
  int value;
  int BestValue = -INT_MAX;
  
  if (depth <= 0) {
    return Node->value;//��������ֵ�����ݹ�
  }
  
  queue<Step> SonQueue;//���Ӷ���
  SonQueue=GenerateSon(NegaBoard,Width,ComputerSide,0,1);//ͨ�����ڵ�Ľ��������ɶ��ӽ��
  
  while (!SonQueue.empty()) {//��ÿ�����ܵ��������ӽ���������
    Step NextSonStep;
    NextSonStep = GetFrontNode(SonQueue);
    
    TreeNode *TreeSon = (TreeNode *)malloc(sizeof(TreeNode));
    TreeSon->ComputerChess.assign(Node->ComputerChess.begin(), Node->ComputerChess.end());
    TreeSon->EnemyChess.assign(Node->EnemyChess.begin(), Node->EnemyChess.end());

    Point FirstStep, SecondStep;//��������
    TreeSon->ComputerChess.push_back(FirstStep);
    TreeSon->ComputerChess.push_back(SecondStep);

    NegaBoard[FirstStep.x][FirstStep.y] = ComputerSide;//���ӽ�����
    NegaBoard[SecondStep.x][SecondStep.y] = ComputerSide;
    
    TreeSon->value = Part_EvalueFucation(NegaBoard,FirstStep,SecondStep,ComputerSide)+Node->value;//����
    
    NegaBoard[FirstStep.x][FirstStep.y] = EMPTY;//�ָ����Ա���һ������ʹ��
    NegaBoard[SecondStep.x][SecondStep.y] = EMPTY;
    Node->Son.push_back(TreeSon);//���ӽ��ѹ��
    value = -NegaMax_AlphaBeta(TreeSon, -Beta,-Alpha,depth - 1,ComputerSide);//�����еķ���������˴��룬��û����(
    if (value >= Alpha) {
      Alpha = value;
    }
    if (Alpha >= Beta) {
      break;
    }
  }
  return Alpha;
}

	

Step machine(int ComputerSide)
 {
  
  int EnemySide;//���˵���ɫ
  if (ComputerSide == BLACK)EnemySide = WHITE;
  else EnemySide = BLACK;

  Step NextTwoStep;

  int RangeBeginX = 20;int RangeBeginY = 20;//Ŀǰ������Χ��ʼ��
  int RangeEndX = -1;int RangeEndY = -1;
  BoardRange(Board,RangeBeginX, RangeBeginY, RangeEndX,RangeEndY);//����̽�����淶Χ

  Step PreSeekStep;
  Step Current;
  int OneOrTwo_Flag = 0;//1����һ�������Ѿ�ȷ��
  Point mustputnode;
  PreSeekStep=PreSeek(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY, ComputerSide);//ʹ�ò�����֮ǰ����ǰ��ɨ�裬�ж��Ƿ��л��Ļ���ȱ������ӵ����
  
  if (PreSeekStep.first.x != -1) {
    NextTwoStep.first.x = PreSeekStep.first.x;
    NextTwoStep.first.y = PreSeekStep.first.y;
    Current.first.x = PreSeekStep.first.x;
    Current.first.y = PreSeekStep.first.y;
    Board[NextTwoStep.first.x][NextTwoStep.first.y] = ComputerSide;//�ѵ�һ������д�����
    mustputnode.x=NextTwoStep.first.x;
    mustputnode.y=NextTwoStep.first.y;
    OneOrTwo_Flag = 1;
  }
  if (PreSeekStep.second.x != -1) {
    NextTwoStep.second.x = PreSeekStep.second.x;
    NextTwoStep.second.y = PreSeekStep.second.y;
    return NextTwoStep;//�������Ӿ�ȷ����ֱ�ӷ���
  }
  //----------����������------------//

  int Max_Score = INT_MIN;

  Step ReturnStep;//����ֵ��ʼ��
  ReturnStep.first.x = -1; ReturnStep.first.y = -1;
  ReturnStep.second.x = -1; ReturnStep.second.y = -1;
  
  queue<Step> ImpossibleFact;//���ڵ���Ӷ���
  if(OneOrTwo_Flag==0)
  {
     ImpossibleFact=GenerateSon(Board, Width, ComputerSide, OneOrTwo_Flag,1);//1 ��ʾȡMax 
  }
  else
  {
    ImpossibleFact=GenerateSon2(Board,Width,ComputerSide,OneOrTwo_Flag,1,mustputnode);
  }
  
  while (!ImpossibleFact.empty()) {//�����п��ܵĵ�һ����������������NegaMax��ֵ
    int Alpha = INT_MIN;
    int Beta = INT_MAX;
    Current= GetFrontNode(ImpossibleFact);

    Board[Current.first.x][Current.first.y] = ComputerSide;//������
    Board[Current.second.x][Current.second.y] = ComputerSide;
    
    TreeNode *Node = (TreeNode *)malloc(sizeof(TreeNode));//���ڵ�
    
    for (int i = 0; i < 19; i++) {
      for (int j = 0; j < 19; j++) {
        Point Chess;
        Chess.x = i; Chess.y = j;
        if (Board[i][j] == EMPTY) continue;
        else if (Board[i][j] == ComputerSide) Node->ComputerChess.push_back(Chess);
        else if (Board[i][j] == EnemySide) Node->EnemyChess.push_back(Chess);
      }
    }
    Node->value = ALL_EvalueFucation(Board, RangeBeginX, RangeBeginY, RangeEndX, RangeEndY,ComputerSide);
    int temp = NegaMax_AlphaBeta(Node, Alpha, Beta, Depth,ComputerSide);//�õ����ڵ�����
    if (temp > Max_Score) {
      ReturnStep.first.x = Current.first.x;//����Ŀǰ������ߵ���������
      ReturnStep.first.y = Current.first.y;
      ReturnStep.second.x = Current.second.x;
      ReturnStep.second.y = Current.second.y;
    }
    Board[Current.first.x][Current.first.y] = EMPTY;//�ָ�����
    Board[Current.second.x][Current.second.y] = EMPTY;
  }
  return ReturnStep;//������������
}

int main()
{
  Step step;//��ʱ���ṹ
  char message[256];//ͨ����Ϣ����
  int computerSide;//����ִ����ɫ
  int start = 0;//�Ծֿ�ʼ���
  srand(int(time(0)));
  //�˴����ó�ʼ������
    //...

  while (1)	//������ѭ��
  {
    fflush(stdout);//��Ҫɾ������䣬�������������
    scanf("%s", message);//��ȡƽ̨������Ϣ
        //��������
    if (strcmp(message, "name?") == 0)//���սƽ̨���Ͷ���
    {
      fflush(stdin);
      /***********��"�����"��Ϊ��Ķ�����������6�����ֻ�12��Ӣ����ĸ�������޳ɼ�************/
      /*******/		printf("name ���ֵ�һλ\n");		/**ֻ�޸�����壬��Ҫɾ��name�ո�****/
      /***********��"�����"��Ϊ��Ķ�����������6�����ֻ�12��Ӣ����ĸ�������޳ɼ�************/
    }
    else if (strcmp(message, "new") == 0)//���������
    {
      int i, j;
      scanf("%s", message);//��ȡ����ִ����ɫ
      fflush(stdin);
      if (strcmp(message, "black") == 0)	computerSide = BLACK;  //ִ��
      else  computerSide = WHITE;   //ִ��

      for (i = 0; i < 19; ++i)   //��ʼ�����
        for (j = 0; j < 19; ++j)
          Board[i][j] = EMPTY;
      start = 1;

      if (computerSide == BLACK)
      {
        /**********���ɵ�һ���ŷ�����������step�ṹ�У���������Ϊ(step.first.x,step.first.y)**********/
        /****************************���·������룬���滻�ҵ�ʾ������******************************/


        step.first.x = 9;
        step.first.y = 9;


        /******************************����������һ���������*******************************************/

        Board[step.first.x][step.first.y] = computerSide;//����������
        printf("move %c%c@@\n", step.first.x + 'A', step.first.y + 'A');//����ŷ�
      }
    }
    else if (strcmp(message, "move") == 0)//����,���������
    {
      scanf("%s", message);//��ȡ���������ŷ�
      fflush(stdin);
      step.first.x = message[0] - 'A';		step.first.y = message[1] - 'A';
      step.second.x = message[2] - 'A';		step.second.y = message[3] - 'A';
      //�����������
      Board[step.first.x][step.first.y] = 1 - computerSide;
      if (!(step.second.x == -1 && step.second.y == -1)) Board[step.second.x][step.second.y] = 1 - computerSide;

    /**********************************************************************************************************/
    /***�������ӵ����꣬������step�ṹ�У���1������(step.first.x,step.first.y)����2������(step.first.x,step.first.y)*****/
    /**************************************���·������룬���滻�ҵ�ʾ������*****************************************/
      
      
      
      step = machine(computerSide);

      
      
    /*****************************************������������******************************************************/
    /**********************************************************************************************************/

      printf("move %c%c%c%c\n", step.first.x + 'A', step.first.y + 'A', step.second.x + 'A', step.second.y + 'A');//����ŷ�
    }
    else if (strcmp(message, "error") == 0)//�ŷ�����
    {
      fflush(stdin);
    }
    else if (strcmp(message, "end") == 0)//�Ծֽ���
    {
      fflush(stdin);
      start = 0;
    }
    else if (strcmp(message, "quit") == 0)//�˳�����
    {
      fflush(stdin);
      printf("Quit!\n");
      break;
    }
  }
  return 0;
}

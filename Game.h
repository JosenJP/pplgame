// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__B8D6EE41_801D_401F_B14F_F3A9834FE334__INCLUDED_)
#define AFX_GAME_H__B8D6EE41_801D_401F_B14F_F3A9834FE334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//存储6个不同的方位（逆时针）
	static int ps1[6][2]={{-1,-1},{0,-1},{1,-1},{1,0},{0,1},{-1,0}};
	static int ps2[6][2]={{0,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};
	//得分
	static char Points[20];


class CGame  
{
public:
	void PointsClear();
	void SetGameoverflag();
	void MoveDown();
	bool GetGameflag();
	void ShowPoints(int point);
	void JudgeGame();
	void Scanner();
	void Delete();
	void Fix(int i,int j);
	void DrawSend();
	void send();
	void SetCurrent(CPoint p);
	void DrawNext();
	void GetNextRand();
	void GetRandOne(int n);
	void GetRand();
	void GetMask();
	void Draw(CDC *pDC);
	void GetPoint(CPoint p);
	void CalPoint(int &x,int &y);
	void DrawLine();
	void DrawOne(int i,int j,int no);
	void DrawBmp();
	void DrawBackGround();
	void InitImg(CDC *pDC);

	
	int mx,my;    //鼠标的坐标
	int cx,cy;    //线的原点
	int length;   //线的长度
	int m_cx,m_cy;//绘制小面具的起点
	int m_dx,m_dy;//小图的大小
	int m_x,m_y;  //发射后小面具的坐标
	int bcx,bcy;  //用来储存小面具发送的起点坐标
	int fx,fy;    //记录固定点的坐标
	int showwidth,showheight;//记录显示区域的大小
	int plusx,plusy; //用来记录坐标的改变数值
	int fr;          //用来记录发射面具号
	int data[15][17];//整个显示图像区域
	CDC bkgMen;   //背景图
	CDC imgDC;    //用来实现双缓冲
	int r;        //用来存储当前面具号
	int count;    //记录发送的面具个数


	bool startmoveflag;   //用来记录鼠标是否已经在图片范围内移动
	bool currentfixedflag;//用来记录当前的小面具是否已经固定
	bool moveflag;        //记录小面具是否在移动中
	bool ready;           //记录小面具是否可以发射
	bool gameoverflag;    //记录游戏是否结束

	//用来保存mask图后的两张图片
	CDC bmpMen;       //用来存储整个小面具图像 
	CDC maskMen;      //用来存储整个小面具图像的mask图
	CBitmap imgBitmap;
	CGame();
	virtual ~CGame();

};

#endif // !defined(AFX_GAME_H__B8D6EE41_801D_401F_B14F_F3A9834FE334__INCLUDED_)

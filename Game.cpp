// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pplgame.h"
#include "Game.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGame::CGame()
{
	//移动线的起始坐标
	cx=281;
	cy=523;
	//小图的大小
	m_dx=30;
	m_dy=31;
	//绘制小面具的起点
	m_cx=24;
	m_cy=25;
	//线的长度
	length=50;
	//发送起始坐标
	bcx=266;
	bcy=507;
	//显示界面大小
	showwidth=525;
	showheight=498;
	//面具起始发射坐标
	m_x=bcx;
	m_y=bcy;
	//发射的面具个数
	count=0;
	//对data进行初始化
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<17;j++)
		{
			data[i][j]=-1;
		}
	}
	startmoveflag=false;
	currentfixedflag=true;
	moveflag=false;
	ready=false;
	gameoverflag=false;
	//得分初始化
	Points[0]='0';
	for(int i=1;i<20;i++)
	{
		Points[i]='\0';
	}
}


CGame::~CGame()
{

}

//初始化各个变量
void CGame::InitImg(CDC *pDC)
{
	CBitmap bmp;

	//载入背景图
	bmp.LoadBitmap(IDB_BACKGROUND);
	bkgMen.CreateCompatibleDC(pDC);
	bkgMen.SelectObject(&bmp);
	bmp.DeleteObject();
	
	//载入小面具图片
	bmp.LoadBitmap(IDB_IMG);
	bmpMen.CreateCompatibleDC(pDC);
	bmpMen.SelectObject(&bmp);
	bmp.DeleteObject();

	//maskMen的初始化
	bmp.LoadBitmap(IDB_IMG);
	maskMen.CreateCompatibleDC(pDC);
	maskMen.SelectObject(&bmp);
	bmp.DeleteObject();
	
	
	//生成mask图
	GetMask();
		
	//对双缓冲区的CDC进行初始化
	imgDC.CreateCompatibleDC(NULL);
	imgBitmap.CreateCompatibleBitmap(pDC,757,569);
	CBitmap *POldBit=imgDC.SelectObject(&imgBitmap);

	//以时间为种子设置随机数
	time_t tm ;	
	time(&tm) ;
	srand((int)tm) ;

}

//绘制背景
void CGame::DrawBackGround()
{
	imgDC.BitBlt(0,0,757,569,&bkgMen,0,0,SRCCOPY);
}

//绘制所有小图
void CGame::DrawBmp()
{
	int i,j;
	for(i=0;i<15;i++)
	{
		for(j=0;j<17;j++)
		{
			if(data[i][j]!=-1)
				DrawOne(j,i,data[i][j]);
		}
	}
	imgDC.TextOut(578,438,Points);
	if(gameoverflag)
	{
		imgDC.TextOut(m_cx+showwidth/2-50,m_cy+showwidth/2-50,"Game Over!!");
		imgDC.TextOut(578,438,Points);
	}
}

//绘制单个小图
void CGame::DrawOne(int i,int j,int no)
{
	int x;
	/*
	偶数：  	1   1    1
    奇数：    1   1   1
	*/
	if(j%2==0)
	{
		x=39;
	}
	else
	{
		x=24;
	}
	imgDC.BitBlt(x+i*m_dx,m_cy+j*m_dy,m_dx,m_dy,&maskMen,no*m_dx,0,SRCAND);
	imgDC.BitBlt(x+i*m_dx,m_cy+j*m_dy,m_dx,m_dy,&bmpMen,no*m_dx,0,SRCPAINT);
}

//绘制方向
void CGame::DrawLine()
{
	int x,y;
	CalPoint(x,y);
	CPen pen(0,10,RGB(0,0,0));
	imgDC.SelectObject(&pen);
	imgDC.MoveTo(cx,cy);
	if(!startmoveflag)
	{
	imgDC.LineTo(cx,cy-length);
	}
	else
	{
	imgDC.LineTo(x,y);
	}
	pen.DeleteObject();
}

//得到计算后的坐标
void CGame::CalPoint(int &x,int &y)
{
	double mlength=sqrt((cy-my)*(cy-my)*1.0+(cx-mx)*(cx-mx));
	int xlength=mx-cx;
	int ylength=cy-my;
	x=int(cx+xlength/mlength*length);
	y=int(cy-ylength/mlength*length);
	
}

//记录鼠标的坐标
void CGame::GetPoint(CPoint p)
{
	if((p.x>=m_cx&&p.x<=m_cx+17.5*m_dx)&&(p.y>=m_cy&&p.y<=m_cy+m_dy*14.5))
	{
	mx=p.x;
	my=p.y;
	startmoveflag=true;
	}
}

//在屏幕中显示
void CGame::Draw(CDC *pDC)
{
	DrawBackGround();
	DrawLine();
	DrawBmp();
	//发射的面具数大于等于6时整体下移
	if(count>=6)
	{
		MoveDown();
		JudgeGame();
		count=count%6;
	}
	if(moveflag&&!currentfixedflag)
	{
		send();
	}
	if(ready)
	{
		GetNextRand();
		ready=false;
	}
	DrawNext();
	pDC->BitBlt(0,0,757,569,&imgDC,0,0,SRCCOPY);
}

//生成mask图
void CGame::GetMask()
{
	for(int i = 0; i < m_dx*6; i++)
	{
		for(int j = 0;j < m_dy; j++)
		{
			if(bmpMen.GetPixel(i,j)==RGB(252,2,252))
			{
				bmpMen.SetPixel(i,j,0);
				maskMen.SetPixel(i,j,RGB(255,255,255));
			}
			else
			{
				maskMen.SetPixel(i,j,0);
			}
		}
	}
}

//获得所有随机数
void CGame::GetRand()
{
	//初始化数组
	for(int m=0;m<15;m++)
	{
		for(int n=0;n<17;n++)
		{
			data[m][n]=-1;
		}
	}
	for(int i=0;i<9;i++)
	{
		GetRandOne(i);
	}
}

//获得一组随机数
void CGame::GetRandOne(int n)
{
	int j;
	for(int i=0;i<17;i++)
	{
		j=rand()%6;
		data[n][i]=j;
	}
}

//获得当前要发送的小面具号
void CGame::GetNextRand()
{
	r=rand()%6;
}

//绘制要发射的小面具
void CGame::DrawNext()
{
	imgDC.BitBlt(bcx,bcy,30,31,&maskMen,r*m_dx,0,SRCAND);
	imgDC.BitBlt(bcx,bcy,30,31,&bmpMen,r*m_dx,0,SRCPAINT);
}

//对发射所需的变量进行赋值
void CGame::SetCurrent(CPoint p)
{
	/*
	当在界面内且上一个面具已经固定时执行。步长为鼠标的坐标和面积发射点坐标差的1/20，记录发射起点m_x,m_y，
	移动标记moveflag和发射准备标记ready赋true，固定标记currentfixedflag赋为false,已发送的面具数加1
	*/
	if((p.x>=m_cx&&p.x<=m_cx+17.5*m_dx)&&(p.y>=m_cy&&p.y<=m_cy+m_dy*14.5)&&currentfixedflag)
	{
		plusx=(p.x-bcx)/20;
		plusy=(p.y-bcy)/20;
		m_x=bcx;
		m_y=bcy;
		fr=r;
		moveflag=true;
		currentfixedflag=false;
		ready=true;
		count++;
	}
}

//改变要发送的小面具的坐标
void CGame::send()
{
	if((m_x+plusx)>=m_cx&&(m_x+plusx)<=(m_cx+showwidth-m_dx)&&(m_y+plusy)>=m_cy&&(m_y+plusy)<=cy&&!currentfixedflag)
	{
		m_x+=plusx;
		m_y+=plusy;
		if(m_x<=m_cx+15||m_x>=m_cx+showwidth-m_dx-15)
		{
			plusx=0-plusx;
			m_x+=plusx;
		}
	}
	DrawSend();
	//四舍五入后进行固定判断和操作
	//偶数行
	if((m_y/31)%2==0)
	{
		Fix(m_y/31,(int)(m_x-15+0.5)/30);
	}
	//奇数行
	else
	{
		Fix(m_y/31,(int)(m_x+0.5)/30);
	}

}

//根据像素进行绘制发射的面具
void CGame::DrawSend()
{
	imgDC.BitBlt(m_x,m_y,m_dx,m_dy,&maskMen,fr*m_dx,0,SRCAND);
	imgDC.BitBlt(m_x,m_y,m_dx,m_dy,&bmpMen,fr*m_dx,0,SRCPAINT);
}

//进行面具固定操作
void CGame::Fix(int i, int j)
{
	//固定以后对各个参数进行赋值
	//偶数行
	/*
	1   1   
	  2   2
	*/
	if(i%2==0&&(data[i-1][j]!=-1||data[i-1][j+1]!=-1)&&i<15)
	{
		data[i][j]=fr;
		fx=i;
		fy=j;
		currentfixedflag=true;   
		//进行消去判断和操作     
		Delete();
		//判断游戏是否结束
		JudgeGame();
	}
	//奇数行
	/*
	   1   1
	2    2
	*/
	else if(i%2!=0&&(data[i-1][j]!=-1||data[i-1][j-1]!=-1)&&i<15)
	{
		data[i][j]=fr;
		fx=i;
		fy=j;
		currentfixedflag=true;
		Delete();
		JudgeGame();
	}
}

//消去面具
void CGame::Delete()
{
	/*
	使用数组来模拟递归以固定的点为中心对六个不同的方位进行遍历，找到3个或以上则进行消去操作
	*/
	int head,j,tail;
	int p[15*17+1][2];//保存相同点的坐标
	p[0][0]=fx;
	p[0][1]=fy;
	tail=1;
	for(head=0;head<tail;head++)
	{
		//判断时，奇偶行需要分开(以图中的0为中心点)
		/*
		2 2 1
		2 0 2
		2 2 1
		*/
		if(p[head][0]%2!=0)   //奇数
		{	
			for(int i=0;i<6;i++)
			{
				if(data[p[head][0]+ps1[i][0]][p[head][1]+ps1[i][1]]==fr&&(p[head][0]+ps1[i][0])<=15&&
					(p[head][1]+ps1[i][1])<=17)
				{
					for(j=0;j<tail;j++)
					{
						if((p[head][0]+ps1[i][0])==p[j][0]&&(p[head][1]+ps1[i][1])==p[j][1])
							break;
					}
					if(j==tail)
					{
						p[tail][0]=p[head][0]+ps1[i][0];
						p[tail][1]=p[head][1]+ps1[i][1];
						tail++;
					}
				}
			}
		}
		/*
		1 2 2
		2 0 2
		1 2 2
		*/
		else    //偶数
		{
			for(int i=0;i<6;i++)
			{
				if(data[p[head][0]+ps2[i][0]][p[head][1]+ps2[i][1]]==fr&&(p[head][0]+ps1[i][0])<=15&&
					(p[head][1]+ps1[i][1])<=17)
				{
					for(j=0;j<tail;j++)
					{
						if((p[head][0]+ps2[i][0])==p[j][0]&&(p[head][1]+ps2[i][1])==p[j][1])
							break;
					}
					if(j==tail)
					{
						p[tail][0]=p[head][0]+ps2[i][0];
						p[tail][1]=p[head][1]+ps2[i][1];
						tail++;
					}
				}
			}
		}
	}
	if(tail>=3)
	{
		for(int i=0;i<tail;i++)
		{
			data[p[i][0]][p[i][1]]=-1;
		}
		ShowPoints(tail);
		//设置还可发射的面具个数
		if(tail==3)
			count--;
		else
			count-=2;
		if(count<0)
			count=0;
	}
}


//消去悬空面具
void CGame::Scanner()
{

}

//判断游戏是否结束
void CGame::JudgeGame()
{
	int i;
	for(i=0;i<17&&data[14][i]==-1;i++);
	if(i!=17)
	{
		gameoverflag=true;
	}
}

//计分
void CGame::ShowPoints(int point)
{
	int a[20],i,j,k,m;
	k=strlen(Points);
	for(i=0,j=k;i<20;i++,j--)
	{
		if(Points[i]!='\0')
		{
			a[i]=Points[j-1]-'0';
		}
		else
			a[i]=-1;
	}
	m=a[0]+point;
	a[0]=m%10;
	i=1;
	while(m>=10&&i<20)
	{
		if(a[i]!=-1)
		{
			a[i-1]=m-10;
			m=a[i]++;
			i++;
		}
		else
		{
			a[i]=m/10;
			m=m%10;
			k++;
		}
	}
	for(i=0;i<20;i++,k--)
	{
		if(a[i]!=-1)
		{
			Points[k-1]=a[i]+'0';
		}
		else
		{
			Points[i]='\0';
		}
	}
}

//返回gameoverflag的值
bool CGame::GetGameflag()
{
	return gameoverflag;
}

//整体向下移动
void CGame::MoveDown()
{
	for(int i=14;i>0;i--)
	{
		for(int j=0;j<17;j++)
		{
		  data[i][j]=data[i-1][j];
		}
	}
	GetRandOne(0);
}

//设置游戏开始标记
void CGame::SetGameoverflag()
{
	gameoverflag=false;

}


//分数清零
void CGame::PointsClear()
{
	Points[0]='0';
	for(int i=1;i<20;i++)
	{
		Points[i]='\0';
	}
	count=0;
}

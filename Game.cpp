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
	//�ƶ��ߵ���ʼ����
	cx=281;
	cy=523;
	//Сͼ�Ĵ�С
	m_dx=30;
	m_dy=31;
	//����С��ߵ����
	m_cx=24;
	m_cy=25;
	//�ߵĳ���
	length=50;
	//������ʼ����
	bcx=266;
	bcy=507;
	//��ʾ�����С
	showwidth=525;
	showheight=498;
	//�����ʼ��������
	m_x=bcx;
	m_y=bcy;
	//�������߸���
	count=0;
	//��data���г�ʼ��
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
	//�÷ֳ�ʼ��
	Points[0]='0';
	for(int i=1;i<20;i++)
	{
		Points[i]='\0';
	}
}


CGame::~CGame()
{

}

//��ʼ����������
void CGame::InitImg(CDC *pDC)
{
	CBitmap bmp;

	//���뱳��ͼ
	bmp.LoadBitmap(IDB_BACKGROUND);
	bkgMen.CreateCompatibleDC(pDC);
	bkgMen.SelectObject(&bmp);
	bmp.DeleteObject();
	
	//����С���ͼƬ
	bmp.LoadBitmap(IDB_IMG);
	bmpMen.CreateCompatibleDC(pDC);
	bmpMen.SelectObject(&bmp);
	bmp.DeleteObject();

	//maskMen�ĳ�ʼ��
	bmp.LoadBitmap(IDB_IMG);
	maskMen.CreateCompatibleDC(pDC);
	maskMen.SelectObject(&bmp);
	bmp.DeleteObject();
	
	
	//����maskͼ
	GetMask();
		
	//��˫��������CDC���г�ʼ��
	imgDC.CreateCompatibleDC(NULL);
	imgBitmap.CreateCompatibleBitmap(pDC,757,569);
	CBitmap *POldBit=imgDC.SelectObject(&imgBitmap);

	//��ʱ��Ϊ�������������
	time_t tm ;	
	time(&tm) ;
	srand((int)tm) ;

}

//���Ʊ���
void CGame::DrawBackGround()
{
	imgDC.BitBlt(0,0,757,569,&bkgMen,0,0,SRCCOPY);
}

//��������Сͼ
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

//���Ƶ���Сͼ
void CGame::DrawOne(int i,int j,int no)
{
	int x;
	/*
	ż����  	1   1    1
    ������    1   1   1
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

//���Ʒ���
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

//�õ�����������
void CGame::CalPoint(int &x,int &y)
{
	double mlength=sqrt((cy-my)*(cy-my)*1.0+(cx-mx)*(cx-mx));
	int xlength=mx-cx;
	int ylength=cy-my;
	x=int(cx+xlength/mlength*length);
	y=int(cy-ylength/mlength*length);
	
}

//��¼��������
void CGame::GetPoint(CPoint p)
{
	if((p.x>=m_cx&&p.x<=m_cx+17.5*m_dx)&&(p.y>=m_cy&&p.y<=m_cy+m_dy*14.5))
	{
	mx=p.x;
	my=p.y;
	startmoveflag=true;
	}
}

//����Ļ����ʾ
void CGame::Draw(CDC *pDC)
{
	DrawBackGround();
	DrawLine();
	DrawBmp();
	//�������������ڵ���6ʱ��������
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

//����maskͼ
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

//������������
void CGame::GetRand()
{
	//��ʼ������
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

//���һ�������
void CGame::GetRandOne(int n)
{
	int j;
	for(int i=0;i<17;i++)
	{
		j=rand()%6;
		data[n][i]=j;
	}
}

//��õ�ǰҪ���͵�С��ߺ�
void CGame::GetNextRand()
{
	r=rand()%6;
}

//����Ҫ�����С���
void CGame::DrawNext()
{
	imgDC.BitBlt(bcx,bcy,30,31,&maskMen,r*m_dx,0,SRCAND);
	imgDC.BitBlt(bcx,bcy,30,31,&bmpMen,r*m_dx,0,SRCPAINT);
}

//�Է�������ı������и�ֵ
void CGame::SetCurrent(CPoint p)
{
	/*
	���ڽ���������һ������Ѿ��̶�ʱִ�С�����Ϊ�����������������������1/20����¼�������m_x,m_y��
	�ƶ����moveflag�ͷ���׼�����ready��true���̶����currentfixedflag��Ϊfalse,�ѷ��͵��������1
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

//�ı�Ҫ���͵�С��ߵ�����
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
	//�����������й̶��жϺͲ���
	//ż����
	if((m_y/31)%2==0)
	{
		Fix(m_y/31,(int)(m_x-15+0.5)/30);
	}
	//������
	else
	{
		Fix(m_y/31,(int)(m_x+0.5)/30);
	}

}

//�������ؽ��л��Ʒ�������
void CGame::DrawSend()
{
	imgDC.BitBlt(m_x,m_y,m_dx,m_dy,&maskMen,fr*m_dx,0,SRCAND);
	imgDC.BitBlt(m_x,m_y,m_dx,m_dy,&bmpMen,fr*m_dx,0,SRCPAINT);
}

//������߹̶�����
void CGame::Fix(int i, int j)
{
	//�̶��Ժ�Ը����������и�ֵ
	//ż����
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
		//������ȥ�жϺͲ���     
		Delete();
		//�ж���Ϸ�Ƿ����
		JudgeGame();
	}
	//������
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

//��ȥ���
void CGame::Delete()
{
	/*
	ʹ��������ģ��ݹ��Թ̶��ĵ�Ϊ���Ķ�������ͬ�ķ�λ���б������ҵ�3���������������ȥ����
	*/
	int head,j,tail;
	int p[15*17+1][2];//������ͬ�������
	p[0][0]=fx;
	p[0][1]=fy;
	tail=1;
	for(head=0;head<tail;head++)
	{
		//�ж�ʱ����ż����Ҫ�ֿ�(��ͼ�е�0Ϊ���ĵ�)
		/*
		2 2 1
		2 0 2
		2 2 1
		*/
		if(p[head][0]%2!=0)   //����
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
		else    //ż��
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
		//���û��ɷ������߸���
		if(tail==3)
			count--;
		else
			count-=2;
		if(count<0)
			count=0;
	}
}


//��ȥ�������
void CGame::Scanner()
{

}

//�ж���Ϸ�Ƿ����
void CGame::JudgeGame()
{
	int i;
	for(i=0;i<17&&data[14][i]==-1;i++);
	if(i!=17)
	{
		gameoverflag=true;
	}
}

//�Ʒ�
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

//����gameoverflag��ֵ
bool CGame::GetGameflag()
{
	return gameoverflag;
}

//���������ƶ�
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

//������Ϸ��ʼ���
void CGame::SetGameoverflag()
{
	gameoverflag=false;

}


//��������
void CGame::PointsClear()
{
	Points[0]='0';
	for(int i=1;i<20;i++)
	{
		Points[i]='\0';
	}
	count=0;
}

// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__B8D6EE41_801D_401F_B14F_F3A9834FE334__INCLUDED_)
#define AFX_GAME_H__B8D6EE41_801D_401F_B14F_F3A9834FE334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//�洢6����ͬ�ķ�λ����ʱ�룩
	static int ps1[6][2]={{-1,-1},{0,-1},{1,-1},{1,0},{0,1},{-1,0}};
	static int ps2[6][2]={{0,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};
	//�÷�
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

	
	int mx,my;    //��������
	int cx,cy;    //�ߵ�ԭ��
	int length;   //�ߵĳ���
	int m_cx,m_cy;//����С��ߵ����
	int m_dx,m_dy;//Сͼ�Ĵ�С
	int m_x,m_y;  //�����С��ߵ�����
	int bcx,bcy;  //��������С��߷��͵��������
	int fx,fy;    //��¼�̶��������
	int showwidth,showheight;//��¼��ʾ����Ĵ�С
	int plusx,plusy; //������¼����ĸı���ֵ
	int fr;          //������¼������ߺ�
	int data[15][17];//������ʾͼ������
	CDC bkgMen;   //����ͼ
	CDC imgDC;    //����ʵ��˫����
	int r;        //�����洢��ǰ��ߺ�
	int count;    //��¼���͵���߸���


	bool startmoveflag;   //������¼����Ƿ��Ѿ���ͼƬ��Χ���ƶ�
	bool currentfixedflag;//������¼��ǰ��С����Ƿ��Ѿ��̶�
	bool moveflag;        //��¼С����Ƿ����ƶ���
	bool ready;           //��¼С����Ƿ���Է���
	bool gameoverflag;    //��¼��Ϸ�Ƿ����

	//��������maskͼ�������ͼƬ
	CDC bmpMen;       //�����洢����С���ͼ�� 
	CDC maskMen;      //�����洢����С���ͼ���maskͼ
	CBitmap imgBitmap;
	CGame();
	virtual ~CGame();

};

#endif // !defined(AFX_GAME_H__B8D6EE41_801D_401F_B14F_F3A9834FE334__INCLUDED_)

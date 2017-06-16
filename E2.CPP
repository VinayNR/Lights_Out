#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<dos.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<graphics.h>
//-------------------------------------------------------------------------
class player
{
	char name[30];
       public:
	char * getname()
	{
		return name;
	}
	void setname(char *str)
	{
		strcpy(name,str);
	}
};

class Score:public player
{
	int score;
       public:
	int getscore()
	{
		return score;
	}
	void setscore(int scr)
	{
		score=scr;
	}
	friend istream& operator >> (istream&, Score&);
	friend ostream& operator << (ostream&, Score&);
}o;
ostream& operator << (ostream& obj, Score& S)
{
	obj<<"\nName:"<<S.getname();
	obj<<"\nScore:"<<S.score<<endl;
	return obj;
}
istream& operator >> (istream& obj, Score& S)
{
	char name[30];
	gotoxy(10,3);
	cout<<"PLAYER DETAILS";
	cout<<"\n\nEnter Name:";
	obj>>name;
	S.setname(name);
	return obj;
}
//----------------------------------------------------------------------------
int ctr=0;
//----------------------------------------------------------------------------
void easy(int [20][20], int);
//----------------------------------------------------------------------------

void sort(Score obj[20], int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n-1-i;j++)
		{
			if(obj[j].getscore()<obj[j+1].getscore())
			{
				Score temp=obj[j];
				obj[j]=obj[j+1];
				obj[j+1]=temp;
			}
		}
	}
}
//----------------------------------------------------------------------------
void file(Score obj)
{
	fstream f("LO.txt",ios::in|ios::out|ios::app);
	f.write((char *)&obj,sizeof(obj));
	f.close();
}
//----------------------------------------------------------------------------
long int time_func()
{
	static long int time=0;
	int sec=0,min=0;
	gotoxy(50,3);
	time++;
	min=time/599;
	sec=(time%599)/10;
	cout<<min<<" : "<<sec;
	delay(100);
	gotoxy(50,3);
	cout<<"         ";
	return time;
}
//----------------------------------------------------------------------------
void matrix(int arr[20][20],int n,int p,int q,int moves,long int time)
{
	int check=0;
	float score;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==p && j==q)
				arr[i][j]=(arr[i][j]+1)%2;
			if(i==p)
				if(abs(j-q)%2==1)
					arr[i][j]=(arr[i][j]+1)%2;
			if(j==q)
				if(abs(i-p)%2==1)
					arr[i][j]=(arr[i][j]+1)%2;
		}
	}
	for(i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			if(arr[i][j]!=0)
			{
				check++;
				break;
			}
	}
	if(check==0)
	{
		cleardevice();
		gotoxy(10,10);
		score=10000*exp(-(float)time*moves/10000);
		cout<<"Total score:"<<(int)score;
		o.setscore((int)score);
		file(o);
		easy(arr,n);
		getch();
		exit(0);
	}
}
//----------------------------------------------------------------------------
void func(int arr[20][20], int n)
{
	static int p=0,q=0,moves=0;
	long int time;
	char ch=' ',buffer[50];
	lbl:
	setfillstyle(SOLID_FILL,8);
	while(ch!='q' || ch!='Q')
	{
	     fillellipse(9*(n+1)+q*(40*n-20)/n,9*(n+1)+p*(40*n-20)/n,(4*n-2)/n,(4*n-2)/n);
	     if(kbhit())
	     {
		ch=getch();
		if(ch=='q' || ch=='Q')
			break;
		if(ch=='w')
		{
			cleardevice();
			easy(arr,n);
			if(p==0)
				p=n-1;
			else
				p--;
			goto lbl;
		}
		if(ch=='s')
		{
			cleardevice();
			easy(arr,n);
			if(p==n-1)
				p=0;
			else
				p++;
			goto lbl;
		}
		if(ch=='a')
		{
			cleardevice();
			easy(arr,n);
			if(q==0)
				q=n-1;
			else
				q--;
			goto lbl;
		}
		if(ch=='d')
		{
			cleardevice();
			easy(arr,n);
			if(q==n-1)
				q=0;
			else
				q++;
			goto lbl;
		}
		if(ch==13)
		{
			sprintf(buffer,"%d",++moves);
			matrix(arr,n,p,q,moves,time);
			cleardevice();
			easy(arr,n);
		}
	     }
	     sprintf(buffer,"%d",moves);
	     outtextxy(300,60,"Moves:");
	     outtextxy(300,30,"Time:");
	     outtextxy(420,60,buffer);
	     outtextxy(200,200,"Press q to quit the game!");
	     time=time_func();
	}
}
//----------------------------------------------------------------------------
void easy(int arr[20][20],int n)
{
	float x,y,z;
	setbkcolor(1);
	rectangle(20,20,n*40,n*40);
	for(int i=1;i<n;i++)
	{
		z=20+(float)i*(40*n-20)/n;
		line(z,20,z,n*40);
		line(20,z,n*40,z);
	}
	setfillstyle(SOLID_FILL,6);
	for(i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(arr[i][j]==1)
			{
				x=20+(float)(n*20-1)*(2*i+1)/n;
				y=20+(float)(n*20-1)*(2*j+1)/n;
				floodfill(y,x,getmaxcolor());
			}
		}
	}
	if(ctr==0)
	{
		ctr++;
		func(arr,n);
	}
}
//----------------------------------------------------------------------------
void play(int y)
{
	char ch;
	int n,i,arr[20][20];
	lbl:
	cleardevice();
	randomize();
	outtextxy(60,40,"SELECT LEVEL");
	outtextxy(40,80,"1.Easy");
	outtextxy(40,100,"2.Medium");
	outtextxy(40,120,"3.Hard");
	outtextxy(0,y,"->");
	while(!kbhit())
	{
		ch=getch();
		if(ch=='w')
		{
			if(y>80)
			{
				y-=20;
				goto lbl;
			}
		}
		else if(ch=='s')
		{
			if(y<120)
			{
				y+=20;
				goto lbl;
			}
		}
		else if(ch==13)
		{
			n=y/20-1;
			break;
		}
		else
			continue;
	}
	for(i=0;i<n;i++)
		for(int j=0;j<n;j++)
			arr[i][j]=random(2);
	cleardevice();
	easy(arr,n);
}
//----------------------------------------------------------------------------
void hscr()
{
	cleardevice();
	int i=0;
	Score obj[20];
	setbkcolor(2);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
	outtextxy(200,20,"HIGHSCORES");
	cout<<"\n\n\n";
	ifstream f("LO.txt",ios::in);
	f.seekg(0);
	while(f.read((char *)&obj[i],sizeof(Score)))
		i++;
	sort(obj,i);
	for(int j=0;j<i;j++)
		cout<<obj[j];
	getch();
	f.close();
}
//----------------------------------------------------------------------------
void game(int y)
{
	char ch;
	lbl:
	cleardevice();
	setbkcolor(1);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
	outtextxy(200,20,"LIGHTS OFF");
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(50,y,"->");
	outtextxy(100,80,"1.PLAY GAME");
	outtextxy(100,120,"2.HIGHSCORES");
	outtextxy(100,160,"3.EXIT");
	while(!kbhit())
	{
		ch=getch();
		if(ch=='w')
		{
			if(y>80)
			{
				y-=40;
				goto lbl;
			}
		}
		if(ch=='s')
		{
			if(y<160)
			{
				y+=40;
				goto lbl;
			}
		}
		if(ch==13)
		{
			if(y==160)
				exit(0);
			if(y==80)
			{
				cleardevice();
				cin>>o;
				play(80);
				break;
			}
			else
			{
				hscr();
				goto lbl;
			}
		}
	}
	closegraph();
}
//----------------------------------------------------------------------------
void main()
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		cout<<"Graphics error: %s\n"<<grapherrormsg(errorcode);
		cout<<"Press any key to halt:";
		getch();
		exit(1);
	}
	for(int i=0;i<13;i++)
	{
		setbkcolor(i);
		delay(100);
	}
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
	outtextxy(150,20,"LIGHTS OUT");
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
	outtextxy(200,150,"Press any key");
	getch();
	game(80);
}
//----------------------------------THE END-----------------------------------
#include<stdio.h>
#include "iGraphics.h";
#include "gamePlay.h";

void menu();
void name();
void instruct();
void about();
void score();
void play();
void finish();
void drawTextBox();
void writeText(int x,int y,int x1,int y1);
void menuControl(int x,int y,int x1,int y1);
void backButton(int x,int y,int x1,int y1);
void finishControl(int x,int y,int x1,int y1);


int mx=10,my=10;



int len=0;
int mode=0;



struct buttonCoordinate{
	int x;
	int y;
}bCoordinate[4];


char button[10][100] = {"button//play.bmp","button//instruct.bmp","button//score.bmp","button//about.bmp"};

int width = 1200;
int height = 600;
int music = true;


void iDraw()
{
	iClear();

	//firstIntroPage
	iShowBMP(0,0,"back//intro.bmp");
	iShowBMP2(650,65,"button//homeButton.bmp",0);

	if(page == 1)
		menu();
	if(page == 2)
		name();
	if(page == 3)
		instruct();
	if(page == 4)
		score();
	if(page == 5)
		about();
	if(page == 6)
		play();
	if(page == 7)
	{
		finish();
		hScore();
	}

	//itWillShowInEveryPage
	iText(500,20,"Press 'END' To EXIT",GLUT_BITMAP_TIMES_ROMAN_24);


}

void iKeyboard(unsigned char x)
{
	//takeInputNameAndSaveInFile
	int i;
	if(mode == 1)
	{
        if(x == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			page=6;
			//PlaySound("music//play.wav",NULL,SND_LOOP | SND_ASYNC);
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = x;
			len++;
		}
	}


	if(page == 6)
	{

		if(x == 'p')
		{

			iPauseTimer(timer);
			iPauseTimer(timer1);
			iPauseTimer(timer2);
		}

		if(x == 'r')
		{
		
			iResumeTimer(timer);
			iResumeTimer(timer1);
			iResumeTimer(timer2);

		}


	}


}

void iSpecialKeyboard(unsigned char x)
{

	if(x == GLUT_KEY_HOME)
		page = 1;

	if(x == GLUT_KEY_END)
		exit(0);


}

void iMouse(int x,int y,int x1,int y1)
{
	if(page == 1)
		menuControl(x,y,x1,y1);

	if(page == 3 || 4 || 5)
		backButton(x,y,x1,y1);
	
	if(page == 2)
	{
		backButton(x,y,x1,y1);
		writeText(x,y,x1,y1);
	}

	if(page == 6)
		playerControl(x,y,x1,y1);

	if(page == 7)
		finishControl(x,y,x1,y1);
}

void iMouseMove(int x,int y)
{

}

void iPassiveMouse(int x,int y)
{
	
}

void iPassiveMouseMove(int x,int y)
{
	
}

void menu()//thisShowsMenu
{
	iShowBMP(0,0,"back//menu.bmp");
	for(int i=0;i<4;i++)
	{
		iShowBMP2(bCoordinate[i].x,bCoordinate[i].y,button[i],0);
	}
}

void name()//thisShowsNameInputTextBox
{
	iShowBMP(0,0,"back//name.bmp");
	iShowBMP2(1030,12,"button\\back.bmp",0);
	drawTextBox();

	if(mode == 1)
	{
		iText(230, 300, str, GLUT_BITMAP_TIMES_ROMAN_24);
	}

}

void drawTextBox()//thisDrawNameBox
{
	iText(20,300,"Enter Your Name: ",GLUT_BITMAP_TIMES_ROMAN_24);
	iRectangle(220,280,300,60);
	iText(20, 370, "Click In The Box To Activate The Box, Press 'ENTER' To Finish.",GLUT_BITMAP_HELVETICA_18);

}

void writeText(int x,int y,int x1,int y1)//thisControlWritingInTextBox
{

	if(x == GLUT_LEFT_BUTTON && y == GLUT_DOWN)
	{
		if(x1 >= 220 && x1 <= 220+300 && y1 >= 280 && y1 <= 280+60 && mode == 0)
		{
			mode = 1;
		}
	}
}


void instruct()//thisShowsInstructionPage
{
	iShowBMP(0,0,"back//instruct.bmp");
	iShowBMP2(1030,12,"button\\back.bmp",0);
}

void score()//thisShowsScorePage
{
	iShowBMP(0,0,"back//score.bmp");
	iShowBMP2(1030,12,"button\\back.bmp",0);
	iText(100,350,"Name: ",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,255);
	iFilledRectangle(180,330,400,50);
	iSetColor(255,255,255);
	iText(100,280,"Score: ",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,255);
	iFilledRectangle(180,260,200,50);
	iSetColor(255,255,255);



	char hs[100];
	f_in = fopen(filename,"r");
	fscanf(f_in, "%s %d", &namee, &s);
	sprintf(hs, "%d",s);

	iText(190,350,namee,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(190,280,hs,GLUT_BITMAP_TIMES_ROMAN_24);
	

}


void about()//thisShowsAboutPage
{
	iShowBMP(0,0,"back//about.bmp");
	iShowBMP2(1030,12,"button\\back.bmp",0);
}


void menuControl(int x,int y,int x1,int y1)//thisControlMenu
{
	if(x == GLUT_LEFT_BUTTON && y == GLUT_DOWN)
	{
		for(int i=0;i<4;i++)
		{
			if((x1>=bCoordinate[i].x && x1<=bCoordinate[i].x+380) && (y1>=bCoordinate[i].y && y1<=bCoordinate[i].y+110))
				page = i+2;
		}
	}
}

void backButton(int x,int y,int x1,int y1)//thisControlsBackButtonInEveryPage
{
	if(x == GLUT_LEFT_BUTTON && y == GLUT_DOWN)
	{
		
		if((x1>=1030 && x1<=1030+150) && (y1>=12 && y1<=12+75))
				page = 1;
	}
}

void finish()
{

	iShowBMP(0,0,"back//finish.bmp");
	iSetColor(0,0,255);
	iFilledRectangle(420,300,100,50);
	iSetColor(255,255,255);
	iText(450,320,scoree,GLUT_BITMAP_TIMES_ROMAN_24);
	iShowBMP2(30,120,"button//backMainMenu.bmp",0);

}

void finishControl(int x,int y,int x1,int y1)//thisControlsFinishPage'sButton
{
	

	if(x == GLUT_LEFT_BUTTON && y == GLUT_DOWN)
	{

		if((x1>=30 && x1<=30+380) && (y1>=120 && y1<=120+110))
		{
			page = 1;
			bx = 590, by = 60;
			scores = 0;

		}

	}

}

int main()
{

	page = 0;



	int sum = 30;

	timer = iSetTimer(15,ballControl);
	timer2 = iSetTimer(15,ballControl2);
	timer1 = iSetTimer(15,goalkeeperControl);




	if(!music)
		PlaySound("music//intro.wav",NULL,SND_LOOP | SND_ASYNC);

	for(int i=3;i>=0;i--)//insertButtonCoordinate
	{
		bCoordinate[i].x = 760;
		bCoordinate[i].y = sum;
		sum+=140;

	}

	iInitialize(width,height,"FIFA'20 2D");




	iStart();
	return 0;

}

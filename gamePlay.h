#include<math.h>
void goalCheck();
void goalCheck2();
void hScore();

int page;

int bx=590,by=60;
int timer,timer1,timer2;

int gx = 600,gy =480,g = 20;
int scores = 0;
char scoree[100];

FILE *fp;
FILE *f_in;
char filename[] = "score.txt";

double dx, dy, dr, m, dest_x, dest_y;
volatile bool moving;

volatile bool save;
volatile bool goal;

volatile bool save2;
volatile bool goal2;

double xu = 0.0 , yu = 0.0 , u = 0.0 ;
int cx[4], cy[4];

char str[100], str2[100];
char namee[80];
int s;

volatile bool moving2;

void play()
{
	iShowBMP(0,0,"back//field.bmp");
	iShowBMP2(bx,by,"object//ball.bmp",0);
	iShowBMP2(450,500,"object//goalbar.bmp",0);
	iShowBMP2(gx,gy,"object//goalkeeper.bmp",0);
	iShowBMP2(590,55,"object//player1.bmp",0);
	iText(800,20,"Scores : ",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(50,20,"Press 'p' For Pause & 'r' for Resume",GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(scoree, "%d",scores);
	iText(880,20,scoree,GLUT_BITMAP_TIMES_ROMAN_24);

}

void goalkeeperControl()
{
	gx+=g;
	if(gx+64>=450+300 || gx<=450)
		g = g*(-1);

}

void ballControl()
{

	if(moving){

		if (abs(dest_x - bx) <= 20 && abs(dest_y - by) <= 20)
		{
			bx = dest_x;
			by = dest_y;
			moving = false;
		}

		else if(dest_x == bx)
		{
			by+=dy;
			if((dest_y - by) <= 20)
			{
				by = dest_y;
				moving = false;
			}

		}

		else
		{
			bx += dx;
			by += dy;
		}



		if((bx >= gx && bx <= gx + 64) && (by >= gy && by <= gy + 110))
		{
			save = true;
			goalCheck();
	
		}


		else if((bx>=450 && bx<=450+300) && (by>=500 && by<=600))
		{
			goal = true;
			goalCheck();

		}

	}

}


void ballControl2()
{

	if(moving2)
	{

		
		if(u <=1){ 
			xu = pow(1-u,3)*cx[0]+3*u*pow(1-u,2)*cx[1]+3*pow(u,2)*(1-u)*cx[2] +pow(u,3)*cx[3];
			yu = pow(1-u,3)*cy[0]+3*u*pow(1-u,2)*cy[1]+3*pow(u,2)*(1-u)*cy[2] +pow(u,3)*cy[3]; 
			bx = xu;
			by = yu;
			u+= .075;
		}
		else
			moving2 = false;


		if((bx >= gx && bx <= gx + 64) && (by >= gy && by <= gy + 110))
		{

			save2 = true;
			goalCheck2();
			
		}


		else if((bx>=450 && bx<=450+300) && (by>=500 && by<=600))
		{

			goal2 = true;
			goalCheck2();
			
		}

	}
	
}


void goalCheck()
{
	

	if(goal)
	{
			scores+=10;
			
			bx=590;by=60;
			moving = false;
		

	}


	if(save)
	{
		moving = false;
		//PlaySound("music//intro.wav",NULL,SND_LOOP | SND_ASYNC);
		page = 7;
		
	}

}


void goalCheck2()
{


	if(goal2)
	{
			scores+=20;
			
			bx=590;by=60;
			moving2 = false;

	}

	if(save2)
	{
	
		moving2 = false;
		//PlaySound("music//intro.wav",NULL,SND_LOOP | SND_ASYNC);
		page = 7;
		
	}

}


void hScore()
{

	f_in = fopen(filename,"r");
	fscanf(f_in, "%s %d", &namee, &s);
	if(scores > s)
	{
		fp = fopen(filename,"w");
		fprintf(fp,str2);
		fprintf(fp," ");
		fprintf(fp,"%d",scores);
		fclose(fp);
	}
	fclose(f_in);
}


void ballMove()
{

	dr = 20;

	if(dest_x == bx)
	{

		dy = dr;
		moving = true;
	}

	else{
		m = (dest_y - by)/(dest_x - bx);
		dx = cos(atan(m)) * dr;
		if(dest_x < bx)
			dx = dx*(-1);
		dy = m*dx;
		moving = true;
	}

}

void ballMove2()
{

	xu = 0.0 , yu = 0.0 , u = 0.0 ;

	
	cx[0] = bx;
	cx[1] = bx + (dest_x - bx)/3 - 150;
	cx[2] = bx + 2*(dest_x - bx)/3 - 150;
	cx[3] = dest_x;

	cy[0] = by;
	cy[1] = by + (dest_y - by)/3;
	cy[2] = by + 2*(dest_y - by)/3;
	cy[3] = dest_y;


	moving2 = true;

}


void playerControl(int state,int button,int a,int b)
{

	
	if(state == GLUT_LEFT_BUTTON && button == GLUT_DOWN && a>=450 && a<=450+300 && b>=500 && b<=600)
	{
		dest_x = a;
		dest_y = b;



		moving = false;

		save = false;
		goal = false;




		ballMove();

	}

	if(state == GLUT_RIGHT_BUTTON && button == GLUT_DOWN && a>=450 && a<=450+300 && b>=500 && b<=600)
	{
		dest_x = a;
		dest_y = b;




		moving2 = false;

	


		save2 = false;
		goal2 = false;



		cx[0] = bx;
		cx[1] = bx + (bx +dest_x)/3;
		cx[2] = bx + 2*(bx +dest_x)/3;
		cx[3] = dest_x;

		cy[0] = by;
		cy[1] = by + (by +dest_y)/3;
		cy[2] = by + 2*(by +dest_y)/3;
		cy[3] = dest_y;





		ballMove2();
	}

}

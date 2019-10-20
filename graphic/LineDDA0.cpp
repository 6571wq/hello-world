#include"windows.h" 
#include<glut.h>
#include<math.h>

typedef struct {
	int x,y;
}point;
void init()
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}
int LineDDA(int x0,int y0,int x1,int y1,point pixels[])
{
	
	int num,x,y,dx,dy;
	float k,xf,yf;
	dx = x1-x0;
	dy = y1-y0;
	num = 0;
	if(dx!=0)
		k = dy*1.0/dx;
	if(dx==0) //垂直线
	{
		for(y=y0;y<=y1;y++)
		{
			pixels[num].x = x0;
			pixels[num].y = y;
			num ++;
		}

	}
	else if(dy==0) //水平线
	{
		for(x=x0;x<=x1;x++)
		{
			pixels[num].x = x;
			pixels[num].y = y0;
			num ++;
		}
	}
	else if(fabs(k)<=1)
	{
		yf = y0;
		for(x=x0;x<=x1;x++)
		{
			pixels[num].x = x;
			pixels[num].y = (int)(yf+0.5);
			num ++;
			yf += k;
		}
	}
	else
	{
		xf = x0;
		for(y=y0;y<=y1;y++)
		{
			pixels[num].x = (int)(xf+0.5);
			pixels[num].y = y;
			num ++;
			xf += 1/k;
		}
	}
	return num;
}
void drawLine(int x1,int y1,int x2,int y2)
{
	point pixels[1000];
	int num;
	int i;
	num = LineDDA(x1,y1,x2,y2,pixels);
	glBegin(GL_POINTS);
		for(i=0;i<num;i++)
			glVertex2i(pixels[i].x,pixels[i].y);
	glEnd();
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f,0.0f,0.f);
	glPointSize(1);
	drawLine(10,10,320,300);
	glFlush();
}
void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
		glOrtho(10,350,10/aspectRatio,350/aspectRatio,1.0,-1.0);
	else
		glOrtho(10*aspectRatio,350*aspectRatio,10,350,1.0,-1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main()
{ 
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(300,300);
	glutInitWindowPosition(500,500);
	glutCreateWindow("LineDDA");
	
	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}

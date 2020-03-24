#include "windows.h" 
#include <glut.h>
//方块的初始位置和大小
GLfloat x1=0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;
//在x和y方向的步进大小
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
//追踪窗口宽度和高度的变化
GLfloat windowWidth;
GLfloat windowHeight;

void init()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);//用当前的清除色清除窗口
	glColor3f(1.0f,0.0f,0.0f);//把当前的绘图颜色设置为红色
	glRectf(x1,y1,x1+rsize,y1-rsize);//用当前颜色绘制一个填充矩形
	glutSwapBuffers();//刷新绘图命令并进行交换
}
//当窗口改变大小时由GLUT函数库调用
void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	// 防止被0除
	if(h==0)
		h=1;
	//把视口设置为窗口的大小
	glViewport(0,0,w,h);
	//重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//建立裁剪区域（左、右、底、顶、近、远）
	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
	{
		windowWidth = 100;
		windowHeight = 100/aspectRatio;
		glOrtho(-100.0,100.0,-windowHeight,windowHeight,1.0,-1.0);
	}
	else
	{
		windowWidth = 100*aspectRatio;
		windowHeight = 100;
		glOrtho(-windowWidth,windowWidth,-100.0,100.0,1.0,-1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
//当空闲时由GLUT函数库调用（窗口未改变大小或移动时）
void TimerFunction(int value)
{
	//在到达左边或右边时翻转方向
	if(x1>windowWidth-rsize||x1<-windowWidth)
		xstep = -xstep;
	//在到达顶边或底边时翻转方向
	if(y1>windowHeight||y1<-windowHeight+rsize)
		ystep = -ystep;
	//实际移动方块
	x1 += xstep;
	y1 += ystep;

	//检查边界。这是为了防止方块在反弹时窗口变小，使方块出现在新的裁剪区域之外
	if(x1>(windowWidth-rsize+xstep))
		x1 = windowWidth-rsize-1;
	else if(x1<-(windowWidth+xstep))
		x1 = -windowWidth-1;

	if(y1>(windowHeight+ystep))
		y1 = windowHeight-1;
	else if(y1<-(windowHeight-rsize+ystep))
		y1 = -windowHeight+rsize-1;
	//用新的坐标重新绘制场景
	glutPostRedisplay();
	glutTimerFunc(33,TimerFunction,1);
}
int main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutCreateWindow("GLRectFlash");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33,TimerFunction,1);

	glutMainLoop();
	return 0;
}

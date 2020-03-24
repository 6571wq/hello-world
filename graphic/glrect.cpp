#include "windows.h"
#include "glut.h"

void init()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);//用当前的清除色清除窗口
	glColor3f(1.0f,0.0f,0.0f);//把当前的绘图颜色设置为红色
	glRectf(-25.0f,25.0f,25.0f,-25.0f);//用当前颜色绘制一个填充矩形
	glFlush();//刷新绘图命令
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
		gluOrtho2D(-100.0,100.0,-100/aspectRatio,100.0/aspectRatio);
	else
		gluOrtho2D(-100.0*aspectRatio,100.0*aspectRatio,-100.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
int main()
{
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("GLRect");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}

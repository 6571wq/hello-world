#include "windows.h" 
#include <GL/glut.h>

//设置渲染状态
void init()
{
	glClearColor(0.0f,0.0f,1.0f,1.0f);
}
//绘制场景
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//用当前清除颜色清除窗口
	glFlush();//刷新绘图命令
}

int main( )
{
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutCreateWindow("Simple");

  init();

  glutDisplayFunc( display );

  glutMainLoop();
  return 0;
}

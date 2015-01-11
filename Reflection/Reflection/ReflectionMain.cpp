
#include "../HeadFile/math3d.h"
#include "../HeadFile/gltools.h"

GLfloat fLightPos[4] = {-100.0f, 100.0f, 50.0f, 1.0f};
GLfloat fLightPosMirror[4] = {-100.0f, -100.0f, 50.0f, 1.0f};
GLfloat fNoLight[4] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat fLowLight[4] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat fBrightLight[4] = {1.0f, 1.0f, 1.0f, 1.0f};

static GLfloat yRot = 0.0f;

void SetupRC()
{
	glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fNoLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, fNoLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fLowLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, fBrightLight);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
}

void DrawGround()
{
	GLfloat fExtent = 20.0f;
	GLfloat fStep = 0.5f;
	GLfloat y = 0.0f;
	GLfloat fColor;
	GLfloat iStrip, iRun;
	GLint iBounce = 0;

	glShadeModel(GL_FLAT);
	for(iStrip = -fExtent; iStrip <= fExtent; iStrip += fStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(iRun = fExtent; iRun >= -fExtent; iRun -= fStep)
		{
			if((iBounce %2) == 0)
				fColor = 1.0f;
			else
				fColor = 0.0f;

			glColor4f(fColor, fColor, fColor, 0.5f);
			glVertex3f(iStrip, y, iRun);
			glVertex3f(iStrip + fStep, y, iRun);

			iBounce++;
		}
		glEnd();
	}
	glShadeModel(GL_SMOOTH);
}

void DrawSphere()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, -3.5f);
	glPushMatrix();
	//glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.32f, 32, 9);
	glPopMatrix();


	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glPopMatrix();
}

void RenderScene()
{
	// �����ɫ����������Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ----------------------- ���Ȼ��Ƶذ��·������� --------------------
	// �������״̬
	glPushMatrix();
	// ����Դ0��λ�ðڷŵ��ذ��·�
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosMirror);
	// �������״̬
	glPushMatrix();
	// ����˳ʱ�뻷�Ƶ�һ��Ϊ����ε����棬�Զ���ν��о���
	glFrontFace(GL_CW);          
	// ��Y��ʹ��-1��������������תY��
	glScalef(1.0f, -1.0f, 1.0f);
	// ���Ƶذ��·�������
	DrawSphere();
	// ������ʱ�뻷�Ƶ�һ��Ϊ����ε�����
	glFrontFace(GL_CCW);
	// �ָ�����״̬
	glPopMatrix();

	// ----------------- ͨ���Եذ�����͸������ɫ���Ч������ʵ�ַ���Ļþ� -----------------
	// �رչ��ռ���
	glDisable(GL_LIGHTING);
	// ����ɫ���
	glEnable(GL_BLEND);
	// ���û������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ���Ƶذ�
	DrawGround();
	// �ر���ɫ���
	glDisable(GL_BLEND);
	// �򿪹��ռ���
	glEnable(GL_LIGHTING);

	// -------------------- �����Ƶذ��Ϸ������� ---------------------------
	// ����Դ0��λ�ðڷŵ��ذ�����
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
	// ���Ƶذ��Ϸ�������
	DrawSphere();
	// �ָ�����״̬
	glPopMatrix();

	// ִ�л������Ľ���
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	yRot += 1.0f;  

	glutPostRedisplay();

	glutTimerFunc(1,TimerFunction, 1);
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();    
	glTranslatef(0.0f, -0.4f, 0.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("OpenGL Reflection Demo");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	//glutTimerFunc(10, TimerFunction, 1);

	SetupRC();
	glutMainLoop();

	return 0;
}
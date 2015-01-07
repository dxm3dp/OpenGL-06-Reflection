
#include <math.h>
#include "../HeadFile/gltools.h"

GLfloat fLightPos[4] = {-100.0f, 100.0f, 50.0f, 1.0f};
GLfloat fLightPosMirror[4] = {-100.0f, -100.0f, 50.0f, 1.0f};
GLfloat fNoLight[4] = {0.0f, 0.0f, 0.0f, 0.0f};
GLfloat fLowLight[4] = {0.25f, 0.25f, 0.25f, 1.0f};
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

void DrawGround(void)
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

void DrawWorld(void)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, -3.5f);

	glPushMatrix();
	glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.1f, 17, 9);
	glPopMatrix();


	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//gltDrawTorus(0.35, 0.15, 61, 37);

	glPopMatrix();
}



int main(int argc, char* argv[])
{
	return 0;
}
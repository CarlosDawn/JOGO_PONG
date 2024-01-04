#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

int janelaPlacar;
static char label[200];
int ptsJogador1 = 0;
int ptsJogador2 = 0;
int N_MAX_Rodadas = 10;

GLfloat verifica = 0.0f;
GLfloat x1, ybola, xleft, yleft, xright, yright;
GLsizei tamanhoQuadrado = 15;
GLsizei tamanhoBarraW = 10;
GLsizei tamanhoBarraH = 110;

GLfloat xMove = 15.5f;
GLfloat yMove = 15.5f;
GLfloat yMoveBarra = 10.5f;

GLfloat LarguraJanela = 1000.0f;
GLfloat AlturaJanela = 800.0f;

GLint VerifBarraLeftUP, VerifBarraLeftDown, VerifBarraRightDown, VerifBarraRightUp;

void DesenhaTexto(char *s){
	unsigned int i;
	for (i = 0; i < strlen (s); i++)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, s[i]);
}

void DesenhaPtsPlacar(char *s){
	unsigned int i;
	for (i = 0; i < strlen (s); i++)
		glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void JanelaPlacar(void){
	float angulo2;
	glutSetWindow(janelaPlacar);
	/* MARGENS DA JANELA */
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2i(10, AlturaJanela-290);
		glVertex2i(10, AlturaJanela-10);
		glVertex2i(LarguraJanela-10, AlturaJanela-10);
		glVertex2i(LarguraJanela-10, AlturaJanela-290);
	glEnd();
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2i(15, AlturaJanela-285);
		glVertex2i(15, AlturaJanela-15);
		glVertex2i(LarguraJanela-15, AlturaJanela-15);
		glVertex2i(LarguraJanela-15, AlturaJanela-285);
	glEnd();


	/* Texto Estatico */
	glColor3f (1.0f, 1.0f, 1.0f);
	sprintf (label, "Aluno: Carlos Yuri Rodrigues Oliveira");
	glRasterPos2f (30.0f, 740.0f);
	DesenhaTexto (label);

	//COMANDOS DO JOGO
	sprintf (label, "Tecle ESC - Sair");
	glRasterPos2f (30.0f, 680.0f);
	DesenhaTexto (label);
	sprintf (label, "Tecle SPACE - Iniciar");
	glRasterPos2f (30.0f, 620.0f);
	DesenhaTexto (label);
	sprintf (label, "Tecle R - Reiniciar");
	glRasterPos2f (30.0f, 560.0f);
	DesenhaTexto (label);


	//PLACAR
	sprintf (label, "PLACAR");
	glRasterPos2f (710.0f, 700.0f);
	DesenhaTexto (label);

	//PONTOS JOGADOR1
	glColor3f(1.0, 1.0, 0.0);
	sprintf (label,  "%i",ptsJogador1);
	glRasterPos2f (650.0f, 640.0f);
	DesenhaPtsPlacar (label);
	glColor3f(1.0, 1.0, 1.0);
	sprintf (label,  "JOGADOR 1");
	glRasterPos2f (600.0f, 600.0f);
	DesenhaTexto (label);

	if(ptsJogador1==N_MAX_Rodadas){
		glColor3f(1.0, 1.0, 1.0);
		sprintf (label,  "Vencedor");
		glRasterPos2f (650.0f, 620.0f);
		DesenhaTexto (label);
	}

	//PONTOS JOGADOR2
	glColor3f(1.0, 1.0, 0.0);
	sprintf (label, "%i",ptsJogador2);
	glRasterPos2f (820.0f, 640.0f);
	DesenhaPtsPlacar (label);
	glColor3f(1.0, 1.0, 1.0);
	sprintf (label,  "JOGADOR 2");
	glRasterPos2f (780.0f, 600.0f);
	DesenhaTexto (label);
	
	if(ptsJogador2==N_MAX_Rodadas){
		glColor3f(1.0, 1.0, 1.0);
		sprintf (label,  "Vencedor");
		glRasterPos2f (820.0f, 620.0f);
		DesenhaTexto (label);
	}

	glFlush();
}

void desenha(){
	float angulo;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2i(LarguraJanela/2-tamanhoBarraW/2, 0+(AlturaJanela-290));
		glVertex2i(LarguraJanela/2-tamanhoBarraW/2, 0);
		
		glVertex2i(LarguraJanela/2+tamanhoBarraW/2, 0);
		glVertex2i(LarguraJanela/2+tamanhoBarraW/2, 0+(AlturaJanela-290));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, 80+300);
		glVertex2i(0, 80);
		
		glVertex2i(0+170, 80);
		glVertex2i(0+170, 80+300);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2i(1000-170, 80+300);
		glVertex2i(1000-170, 80);
		
		glVertex2i(1000, 80);
		glVertex2i(1000, 80+300);
	glEnd();
	glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 50; i++){
			angulo = i * 2 * M_PI / 50;
			glVertex2f((LarguraJanela/2) + (cos(angulo) * (300/2)), (((AlturaJanela/2)/2)+30) + (sin(angulo) * (300/2)));
		}
	glEnd();
	
	glColor3f(0.0f, 0.0f, 0.0f);
	
	glBegin(GL_QUADS);
		glVertex2i(x1, ybola+tamanhoQuadrado);
		glVertex2i(x1, ybola);
		
		glVertex2i(x1+tamanhoQuadrado, ybola);
		glVertex2i(x1+tamanhoQuadrado, ybola+tamanhoQuadrado);
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex2i(xleft, yleft+tamanhoBarraH);
		glVertex2i(xleft, yleft);
		
		glVertex2i(xleft+tamanhoBarraW, yleft);
		glVertex2i(xleft+tamanhoBarraW, yleft+tamanhoBarraH);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2i(xright, yright+tamanhoBarraH);
		glVertex2i(xright, yright);
		
		glVertex2i(xright+tamanhoBarraW, yright);
		glVertex2i(xright+tamanhoBarraW, yright+tamanhoBarraH);
	glEnd();
	JanelaPlacar();
	glFlush();
}
void Iniciar(void){
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	x1 = LarguraJanela/2-tamanhoQuadrado/2;
	ybola = ((AlturaJanela/2)/2)+30;
	xleft = 100.0f;
	yleft = ((AlturaJanela/2)/2)-30;
	xright = 900.0f;
	yright = ((AlturaJanela/2)/2)-30;
}
void MudarTamanhoJanela(GLsizei LarguraJanela, GLsizei AlturaJanela){
	if(LarguraJanela == 0)AlturaJanela = 1;
	glViewport(0,0, LarguraJanela, AlturaJanela);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(LarguraJanela<=AlturaJanela){
		gluOrtho2D(0.0f, 300.0f, 0.0f, 300.0f*AlturaJanela/LarguraJanela);
	}else{
		gluOrtho2D(0.0f, 800.0f*LarguraJanela/AlturaJanela, 0.0f, 800.0f);
	}
}
void MoveSozinho(int valor){
	if(x1 < xright + tamanhoBarraW &&
		x1 + tamanhoQuadrado > xright&&
		ybola < yright + tamanhoBarraH &&
		ybola + tamanhoQuadrado > yright){
			xMove = -xMove;
	}
	if(x1 < xleft + tamanhoBarraW &&
		x1 + tamanhoQuadrado > xleft&&
		ybola < yleft + tamanhoBarraH &&
		ybola + tamanhoQuadrado > yleft){
			xMove = -xMove;
	}
	
	if(x1>LarguraJanela){
		verifica = 0;
		Iniciar();
		ptsJogador1+=1;
	}
	if(x1<0){
		verifica = 0;
		Iniciar();
		ptsJogador2+=1;
	}
	
	if(ybola>AlturaJanela-tamanhoQuadrado-300||ybola<0){
		yMove = -yMove;
	}
	
	if(verifica == 1){
		x1 += xMove;
		ybola += yMove;	
	}
		
	if (VerifBarraLeftUP==1){
		if(yleft+tamanhoBarraH<AlturaJanela-tamanhoQuadrado-280){
			yleft+=yMoveBarra;
		}
	}
	if (VerifBarraLeftDown==1){
		if(yleft>0){
			yleft-=yMoveBarra;
		}
	}
	if (VerifBarraRightUp==1){
		if(yright+tamanhoBarraH<AlturaJanela-tamanhoQuadrado-280){
			yright+=yMoveBarra;
		}
	}
	if (VerifBarraRightDown==1){
		if(yright>0){
		yright-=yMoveBarra;
		}
	}
	
  glutPostRedisplay();
  glutTimerFunc(33,MoveSozinho, 1);
}
void Movimenta(int key, int x, int y){
	switch(key)
	{
	case GLUT_KEY_UP:
		VerifBarraRightUp = 1;
		break;
	case GLUT_KEY_DOWN:
		VerifBarraRightDown = 1;
		break;
	}
	
	glutPostRedisplay();
}
void Movimenta2(int key, int x, int y){
	if(key == GLUT_KEY_UP){
		VerifBarraRightUp = 0;
	}
	if(key == GLUT_KEY_DOWN){
		VerifBarraRightDown = 0;
	}
	
	glutPostRedisplay();
}
void MovimentaBarraLeft(unsigned char key, int x, int y){
	switch(key)
	{
	case 'w':
		VerifBarraLeftUP = 1;
		break;
	case 's':
		VerifBarraLeftDown = 1;
		break;
	case ' ':
		if(ptsJogador1==N_MAX_Rodadas||ptsJogador2==N_MAX_Rodadas){
			ptsJogador1=0;
			ptsJogador2=0;
		}
		verifica = 1;
		break;
	case 'r':
		Iniciar();
		ptsJogador1=0;
		ptsJogador2=0;
		break;
	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();
}
void MovimentaBarraLeft2(unsigned char key, int x, int y){
	switch(key)
	{
	case 'w':
		VerifBarraLeftUP = 0;
		break;
	case 's':
		VerifBarraLeftDown = 0;
		break;
	}
	glutPostRedisplay();
}
int main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LarguraJanela, AlturaJanela);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("TELEJOGO");
	glutDisplayFunc(desenha);
	glutReshapeFunc(MudarTamanhoJanela);
	glutKeyboardFunc(MovimentaBarraLeft);
	glutKeyboardUpFunc(MovimentaBarraLeft2);
	glutSpecialFunc(Movimenta);
	glutSpecialUpFunc(Movimenta2);
	glutTimerFunc(33,MoveSozinho, 1);
	Iniciar();
	glutMainLoop();
}
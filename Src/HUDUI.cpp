#include "HUDUI.h"
#include "DDS.h"
#include "VBMD.h"
GLuint UItexture1,UItexture2,UItexture3;
extern CLoadVBMD *m_VBMD;//VBMDģ�Ͷ���
extern tModelID ModelID[100];
extern int winwidth,winheight;
extern bool PlayerLocked;
extern int hited;
extern int ModelID_hud;
extern GLuint UItexture4;
void DrawUI1totexture(double latitude)
{
	char line[128]={0};
	for(int i=-90;i<100;i=i+5)
	{
		sprintf(line,"--------- %3d  ---------",i);
		glPrint(4,(GLint)(124+i*8-latitude*8),line,0);
	}

	glBindTexture(GL_TEXTURE_2D,UItexture1);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 256, 256, 0);

}
void DrawUI2totexture(double speed)
{
	char line[128]={0};
	int tmpstart=((int)speed)/10-20;
	if(tmpstart<0)
		tmpstart=0;
	for(int i=tmpstart;i<((int)speed)/10+20;i=i++)
	{
		if(i%5==0)
		sprintf(line,"-%4d",i*10);
		else
			sprintf(line,"-");
		glPrint(0,(GLint)(256+(i-speed/10)*10),line,0);
	}

	glBindTexture(GL_TEXTURE_2D,UItexture2);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 512, 512, 0);

}
void DrawUI3totexture(double ATL)
{
	char line[128]={0};
	int tmpstart=((int)ATL)/50-20;
	if(tmpstart<0)
		tmpstart=0;
	for(int i=tmpstart;i<((int)ATL)/50+20;i=i++)
	{
		if(i%5==0)
		sprintf(line,"%5d-",i*50);
		else
			sprintf(line,"     -");
		glPrint(438,(GLint)(256+(i-ATL/50)*10),line,0);
	}

	glBindTexture(GL_TEXTURE_2D,UItexture3);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 512, 512, 0);

}

void DrawUI1(double rotation)
{
	GLint DRX=(GLint)(winwidth/2.0f);
	GLint DRY=(GLint)(winheight/2.0f);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-DRX,DRX,-DRY,DRY,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	if(PlayerLocked)
		glColor4f(1.0f,0.0f,0.0f,1.0f);
	else
		glColor4f(0.0f,1.0f,0.0f,1.0f);
	glEnable(GL_BLEND);
	glScaled(0.7, 0.7, 1.0);
	glRotated(-rotation,0.0f,0.0f,1.0f);
	if(hited>0)
		glTranslated(float(rand()%10-5),float(rand()%10-5),0);
	glBindTexture(GL_TEXTURE_2D, UItexture1);	
		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0,0.0);glVertex2i(-(DRY*2/5),-(DRY*2/5));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(1.0,0.0);glVertex2i( (DRY*2/5),-(DRY*2/5));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(1.0,1.0);glVertex2i( (DRY*2/5), (DRY*2/5));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0,1.0);glVertex2i(-(DRY*2/5), (DRY*2/5));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();
		
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

}
void DrawUI2()
{
	GLint DRX=(GLint)(winwidth/2.0f);
	GLint DRY=(GLint)(winheight/2.0f);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-400,400,-300,300,-1000,2000);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	if(PlayerLocked)
		glColor3f(1.0f,0.0f,0.0f);
	else
		glColor3f(0.0f,1.0f,0.0f);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, UItexture2);
	glTranslated(320,-7.0,0.0);
	glScaled(1.4, 1.4, 1.4);
	glRotated(30.0,0.0f,1.0f,0.0f);
	if(hited>0)
		glTranslated(float(rand()%10-5),float(rand()%10-5),0);
	m_VBMD->ShowVBMD(ModelID_hud,false);
	glColor3f(1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

}

void DrawUI3()
{
	GLint DRX=(GLint)(winwidth/2.0f);
	GLint DRY=(GLint)(winheight/2.0f);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_COLOR   );
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-400,400,-300,300,-1000,2000);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	if(PlayerLocked)
		glColor3f(1.0f,0.0f,0.0f);
	else
		glColor3f(0.0f,1.0f,0.0f);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, UItexture3);	

	glTranslated(-308,-7.0,0.0);
	glScaled(1.4, 1.4, 1.4);
	glRotated(-30,0.0f,1.0f,0.0f);
	if(hited>0)
		glTranslated(float(rand()%10-5),float(rand()%10-5),0);
	m_VBMD->ShowVBMD(ModelID_hud,false);


	glColor3f(1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

}
void DrawUI4(float turnX,float turnY,float turnZ)
{
	int DRY=30;
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(-400,400,-300,300,-1000,2000);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	

	if(PlayerLocked)
		glColor4f(1.0f,0.0f,0.0f,1.0f);
	else
		glColor4f(0.0f,1.0f,0.0f,1.0f);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, UItexture4);	

	if(hited>0)
		glTranslated(float(rand()%10-5),float(rand()%10-5),0);


		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0,0.5);glVertex2i(-(DRY*2/5),-(DRY*2/5));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5,0.5);glVertex2i( (DRY*2/5),-(DRY*2/5));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5,1.0);glVertex2i( (DRY*2/5), (DRY*2/5));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0,1.0);glVertex2i(-(DRY*2/5), (DRY*2/5));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();

		glTranslated(0.0,-0.25*turnX,0.0);

		glRotatef(-turnZ*0.5f, 0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0,0.0);glVertex2i(-(DRY*2/5),-(DRY*2/5));	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(0.5,0.0);glVertex2i( (DRY*2/5),-(DRY*2/5));	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(0.5,0.5);glVertex2i( (DRY*2/5), (DRY*2/5));	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0,0.5);glVertex2i(-(DRY*2/5), (DRY*2/5));	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();


	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							
}
void DrawTex(unsigned int PTexID,int posx,int posy,int SizeW,int SizeH,int winW,int winH,float colorR,float colorG,float ColorB,float ColorA)
{


	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,winW,0,winH,-10,20);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	

	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, PTexID);	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(colorR,colorG,ColorB,ColorA);

		glBegin(GL_QUADS);							// Use A Quad For Each Character
			glTexCoord2f(0.0f,0.0f);glVertex2i(posx,posy);	// Texture Coord (Bottom Left)// Vertex Coord (Bottom Left)
			glTexCoord2f(1.0f,0.0f);glVertex2i(posx+SizeW,posy);	// Texture Coord (Bottom Right)// Vertex Coord (Bottom Right)
			glTexCoord2f(1.0f,1.0f);glVertex2i(posx+SizeW,posy+SizeH);	// Texture Coord (Top Right)// Vertex Coord (Top Right)
			glTexCoord2f(0.0f,1.0f);glVertex2i(posx,posy+SizeH);	// Texture Coord (Top Left)// Vertex Coord (Top Left)
		glEnd();


	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);				
}
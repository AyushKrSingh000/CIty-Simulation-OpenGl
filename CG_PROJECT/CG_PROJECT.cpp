
#include <GL/glut.h>
#include <GL/gl.h>
#define GL_SILENCE_DEPRECATION
#include<iostream>
using namespace std;
float tmp[] = { 0,0,1 },tmp2[] = { 0,1,0 },bridgeY = 0.0,shipX=-50.0,shipY=-50.0,bridgeWidth = 300.0,trainX=0.0,
bridgeColor[] = { 0.4, 0.2, 0.05 }, frontColor[] = { 0, 0.5, 0.2 },supportColor[] = {0.5, 0.5, 1 },
greyColor[] = { 0.4,0.4,0.4 }, redColor[] = {1,0,0},greenColor[]={0,1,0},
blackColor[]={0,0,0}, c1 = 0.0,c2=0.0,c3=0.0,c4=0;
bool isShipGone = false,isBridgeUp=false;
int sides = 360,pos1=90,pos2=45,pos3=270;
const float radius = 600.0f;
const float PI = 3.14159265f;


void myInit(void) {
	glClearColor(0,0.0,0.2, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1500, 000, 1000,1500,-2000);//viewport
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void drawCircle(int r, int a, int b, float color[]) {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < sides; i++) {
		float angle = 2.0f * PI * i / sides;
		float x = a + r * cos(angle);
		float y = b + r * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}
void circle( int r,int a,int b, float color[]) {
	glColor3f(color[0],color[1],color[2]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++) {
		float angle = 2.0f * PI * i / sides;
		float x =a+ r * cos(angle);
		float y =b+ r * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}
void drawFront(int h, int w, int x, int y, float curentColor[3]) {
	glColor3f(curentColor[0], curentColor[1], curentColor[2]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}
void getTop(int w, int x1, int y1, int x2, int y2,float color[]) {
	glColor3f(color[0],color[1],color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2 + w, y2);
	glVertex2f(x1 + w, y1);
	glEnd();

}
void getSide(int h, int x1, int y1, int x2, int y2) {
	glColor3f(0.5, 0.5, 0.2);
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x2, y2 + h);
	glVertex2f(x1, y1 + h);
	glEnd();

}
void drawBase(int h, int w, int x1, int y1, int x2, int y2) {
	glBegin(GL_QUADS);
	glColor3f(0, 0.5, 0.2);
	getTop(w, x1, y1 + h, x2, y2 + h,bridgeColor);
	getSide(h, x1, y1, x2, y2);
	drawFront(h, w, x1, y1, frontColor);
	glEnd();
}
void drawTriangles(int x1, int y1, int x2, int y2, int x3, int y3, float curentColor[3]) {
	glColor3f(curentColor[0], curentColor[1], curentColor[2]);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();

}
void drawSupportBeams(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float color[3]) {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}
void drawVertLog(int h, int a1, int b1, int w, float color[3]) {
	getSide(h, a1 + w - 3, b1 + 3, a1 + w, b1);
	drawFront(h, w, a1 - 3, b1 + 3, tmp2);
	getSide(h, a1 - 3, b1 + 3, a1, b1);
	drawFront(h, w, a1, b1, color);
}
void ocean() {
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.4, 0.6);
	glVertex2f(0, 0);
	glVertex2f(1500, 0);
	glVertex2f(1500, 700);
	glVertex2f(0, 680);
	glEnd();

}
void railway() {
	getTop(650, 0, 250, -50, 280, bridgeColor);
	getTop(50, 600, 250, 550, 280, tmp2);
	float front[] = { 0.56, 0.39, 0.05 };
	drawFront(60, 650, 0, 190, front);
	getTop(1000, 850, 250, 800, 280, bridgeColor);
	getTop(50, 850, 250, 800, 280, tmp2);
	getSide(60, 850, 190, 800, 220);
	drawFront(60, 1000, 850, 190, front);

}
void railTrack() {
	glLineWidth(2);

	glBegin(GL_LINES);
	for (int i = 0; i < 12; i++) {
		glColor3f(0, 0, 0);
			glVertex2f(i * 50 + 2, 255 );
			glVertex2f((i + 1) * 50, 255 );
			glVertex2f(i * 50 + 2 - 30, 275 );
			glVertex2f((i + 1) * 50 - 30, 275 );
			glColor3f(1, 1, 1);
			glVertex2f(i * 50 + 2, 255 );
			glVertex2f(i * 50 + 2 - 30, 275 );
	}
	for (int i = 0; i < 13; i++) {
		glColor3f(0, 0, 0);
		glVertex2f( 900+ i * 50 + 2, 255);
		glVertex2f(900 + (i + 1) * 50, 255);
		glVertex2f(900 + i * 50 + 2 - 30, 275);
		glVertex2f(900 + (i + 1) * 50 - 30, 275);
		glColor3f(1, 1, 1);
		glVertex2f(900 + i * 50 + 2, 255);
		glVertex2f(900 + i * 50 + 2 - 30, 275);
	}
	glColor3f(0, 0, 0);
	glVertex2f(600, 255);
	glVertex2f(645, 255);
	glVertex2f(550, 275);
	glVertex2f(610, 275);
	glColor3f(1, 1, 1);
	glVertex2f(590, 255);
	glVertex2f(560, 275);
	glVertex2f(645, 255);
	glVertex2f(610, 275);
	glColor3f(0, 0, 0);
	glVertex2f(840, 255);
	glVertex2f(900, 255);
	glVertex2f(810, 275);
	glVertex2f(900, 275);
	glColor3f(1, 1, 1);
	glVertex2f(840, 255);
	glVertex2f(810, 275);
	glEnd();
}
void boat(int s, int x, int y) {
	frontColor[0] = 0;frontColor[1] = 0.5;frontColor[2] = 0.2;
	drawBase(25 * s, 55 * s, 180 * s + x, 200 * s + y, 130 * s + x, 250 * s + y);	//bottom-base
	drawBase(18 * s, 50 * s, 180 * s + x, 228 * s + y, 136 * s + x, 272 * s + y);//second-base
	drawBase(14 * s, 45 * s, 180 * s + x, 248 * s + y, 142 * s + x, 286 * s + y);//top-base
	//top-base-cuboid
	drawFront(70 * s, 20 * s, 162 * s + x, 290 * s + y, frontColor);
	getSide(70 * s, 190 * s + x, 280 * s + y, 182 * s + x, 290 * s + y);
	getSide(70 * s, 170 * s + x, 280 * s + y, 162 * s + x, 290 * s + y);
	frontColor[0] = 2;
	drawFront(70 * s, 20 * s, 170 * s + x, 280 * s + y, frontColor);
	frontColor[2] = 0.6;
	//boat-front-design
	drawTriangles(235 * s + x, 200 * s + y, 235 * s + x, 225 * s + y, 265 * s + x, 218 * s + y, frontColor);
	float tmpColor[] = { 0,0,0 };
	drawTriangles(180 * s + x, 200 * s + y, 235 * s + x, 200 * s + y, 265 * s + x, 218 * s + y, tmpColor);
	frontColor[2] = 0;frontColor[1] = 0.5;frontColor[0] = 1;
	drawTriangles(180 * s + x, 200 * s + y, 180 * s + x, 225 * s + y, 265 * s + x, 218 * s + y, frontColor);
}
void drawRightBackBridge() {
	tmp2[1] = 0.2;
	int a1 = 850,b1 = 252;
	drawSupportBeams(920, 280, 970, 280, 808, 525, 808, 545, supportColor);//side-support
	a1 = 810;b1 = 276;
	drawVertLog(250, a1, b1, 15, tmp);//lower-big-log
	drawVertLog(40, 812, 540,15,tmp);//upper-smaller-log
	
}
void drawRightFrontBridge() {
	tmp2[1] = 0.2;
	int a1 = 850,b1 = 252;
	drawSupportBeams(1000, 250, 1055, 250, 848, 490, 848, 520, supportColor);//side-support
	drawVertLog(250, a1, b1, 15, tmp);//lower-big-log
	drawVertLog(40, 850, 510, 15, tmp);//upper-smaller-log
	drawBase(20, 20, 855, 485, 785, 542);//log-joining-both-ver-log
}
void drawLeftBackBridge() {
	int a1 = 595,b1 = 276;
	drawVertLog(250, a1, b1, 15, tmp);//lower-big-log
	drawSupportBeams(420, 280, 475, 280, 592, 525, 592, 545, supportColor);//side-support
	drawVertLog(40, 595, 540, 15, tmp);;//upper-smaller-log
}
void drawLeftFrontBridge() {
	tmp2[1] = 0.2;
	int a1 = 633, b1 = 252;
	drawVertLog(40, 633, 510, 15, tmp);//upper-smaller-log
	a1 = 633; b1 = 252;
	drawVertLog(250, a1, b1, 15, tmp);//lower-big-log
	drawBase(20, 20, 635, 485, 570, 545);//log-joining-both-ver-log
	drawSupportBeams(470, 250, 525, 250, 631, 490, 631, 510, supportColor);//side-support
}
void movingBackBridge() {
	drawBase(5, 202, 645, 250,605, 275);
	glBegin(GL_LINES);
	for (int i = 0; i < 4; i++) {
		glColor3f(0, 0, 0);
		glVertex2f(645+ i * 50 + 2, 255 + i * 0.01);
		glVertex2f(645+ (i + 1) * 50, 255 + (i + 1) * 0.01);
		glVertex2f(646+i * 50 + 2 - 30, 275 + i * 0.01);
		glVertex2f(646+ (i + 1) * 50 - 30, 275 + (i + 1) * 0.01);
		glColor3f(1, 1, 1);
		glVertex2f(645+ i * 50 + 2, 255 + i * 0.01);
		glVertex2f(645+ i * 50 + 2 - 30, 275 + i * 0.01);
	}
	float fColor[] = { 0.3, 0.2, 0.1 };
	
	
	drawVertLog(150, 788, 275, 20, fColor);
	drawBase(15, 160, 628, 410, 625, 413);
	drawVertLog(150, 608, 275, 20, fColor);
	glEnd();
	

}
void movingFrontBridge() {
	float fColor[] = { 0.3, 0.2, 0.1 };
	drawVertLog(150, 828, 255, 20, fColor);
	drawBase(15, 160, 668, 390, 665, 393);
	drawVertLog(150, 648, 255, 20, fColor);
}
void drawTrain(int x) {
	glPushMatrix();
	drawBase(70, 100, 1950 + x, 255, 1920 + x, 275);//sixth-box
	drawFront(35, 40, 1960 + x, 280, blackColor);
	drawFront(35, 40, 2005 + x, 280, blackColor);
	drawBase(70, 100, 1840 + x, 255, 1810 + x, 275);//fifth-box
	drawFront(35, 40, 1850 + x, 280, blackColor);
	drawFront(35, 40, 1895 + x, 280, blackColor);
	drawBase(70, 100, 1730 + x, 255, 1700 + x, 275);//fourth-box
	drawFront(35, 40, 1740 + x, 280, blackColor);
	drawFront(35, 40, 1785 + x, 280, blackColor);
	drawBase(70, 100, 1620 + x, 255, 1590 + x, 275);//third-box
	drawFront(35, 40, 1630 + x, 280, blackColor);
	drawFront(35, 40, 1675 + x, 280, blackColor);
	drawBase(70, 100, 1510 + x, 255, 1480 + x, 275);//second-box
	drawFront(35, 40, 1520 + x, 280, blackColor);
	drawFront(35, 40, 1565 + x, 280, blackColor);
	drawBase(70, 100, 1400 + x, 255, 1370 + x, 275);//first-box
	drawFront(35, 40, 1410 + x, 280, blackColor);
	drawFront(35, 40, 1455 + x, 280, blackColor);
	//train-engine
	drawFront(35, 60, 1340 + x, 255, redColor);
	getSide(35, 1340 + x, 255, 1305 + x, 275);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(1340 + x, 290);
	glVertex2f(1305 + x, 310);
	glVertex2f(1370 + x, 345);
	glVertex2f(1400 + x, 325);
	glEnd();
	drawTriangles(1340 + x, 290, 1400 + x, 290, 1400 + x, 325, greyColor);
	glColor3f(0.7, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(1345 + x, 300);
	glVertex2f(1323 + x, 313);
	glVertex2f(1367 + x, 340);
	glVertex2f(1390 + x, 325);
	glEnd();
	glPopMatrix();
}
void drawCircleRoads() {
	float baseColor[] = { 0.3f, 0.3f, 0.3f };
	//lower-cricle-for-depth
	circle(radius, 0, -60, baseColor);
	float topColor[] = { 0.35f, 0.35f, 0.35f };
	//base-circle
	circle(radius, 0, 0, topColor);
	glColor3f(0, 0, 0);
	//base-border-for-road
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < sides; i++) {
		float angle = 2.0f * PI * i / sides;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex2f(x, y);

	}
	glEnd();
	//city-circle
	float cityGroundColor[] = { 0.6f, 0.6f, 0.6f };
	circle(radius - 130, 0, 0, cityGroundColor);
	//road-lines
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	sides = 600;
	for (int i = 0; i < sides; i++) {
		float angle = 2.0f * PI * i / sides;
		float x = (radius - 60) * cos(angle);
		float y = (radius - 60) * sin(angle);
		glVertex2f(x, y);
		i += 3;
	}
	glEnd();
	
}
void drawWheel(int x, int y,int z) {
	for (float i = -1.0; i <= 5.0; i += 0.1) {
		//right-back
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(x, y, -i);
		circle(8, x, y, blackColor);
		glPopMatrix();
	//right-front
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(x, y+45, -i);
		circle(8, x, y, blackColor);
		glPopMatrix();
		//left-front
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(x, y + 45, 54-i);
		circle(8, x, y, blackColor);
		glPopMatrix();
		//left-back
		glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(x, y, 54 - i);
		circle(8, x, y, blackColor);
		glPopMatrix();
	}
}
void drawHeadLight(int x, int y, float color[]) {
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(x, y, -16);
	glVertex3f(x - 3, y, -14);
	glVertex3f(x - 3, y, -12);
	glVertex3f(x, y, -8);
	glVertex3f(x + 3, y, -12);
	glVertex3f(x + 3, y, -14);
	glEnd();
}
void drawCar(float c1,float c2) {
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	//right-side
	glColor3f(c1*0.5,c2*0.5,0);
	glVertex3f(50, 00, -5);
	glVertex3f(50, 0, -20);
	glVertex3f(50, 100, -20);
	glVertex3f(50, 100, -5);
	//back-panel-base
	glColor3f(c1*1, c2*1, 0);
	glVertex3f(0, 0, -20);
	glVertex3f(0, 100, -20);
	glVertex3f(50, 100, -20);
	glVertex3f(50, 0, -20);
	//left-side
	glColor3f(c1 * 0.5, c2 * 0.5, 0);
	glVertex3f(0, 0, -5);
	glVertex3f(0, 0, -20);
	glVertex3f(0, 100, -20);
	glVertex3f(0, 100, -5);
	//back-face
	glColor3f(c1 * 0.5, c2 * 0.5, 0);
	glVertex3f(0, 0, -5);
	glVertex3f(0, 0, -20);
	glVertex3f(50, 0, -20);
	glVertex3f(50, 0, -5);
	//front-face
	glColor3f(c1 * 0.4, c2 * 0.4, 0);
	glVertex3f(0, 100, -5);
	glVertex3f(0, 100, -20);
	glVertex3f(50, 100, -20);
	glVertex3f(50, 100, -5);
	glEnd();
	//left-window
	glBegin(GL_POLYGON);
	glColor3f(c1 * 0.2, c2 * 0.2, 0.2);
	glVertex3f(0, 10, -20);
	glVertex3f(4, 10, -25);
	glVertex3f(10, 20, -30);
	glVertex3f(10, 70, -30);
	glVertex3f(4, 80, -25);
	glVertex3f(0, 80, -20);
	glEnd();
	//right-window
	glBegin(GL_POLYGON);
	glVertex3f(50, 10, -20);
	glVertex3f(46, 10, -25);
	glVertex3f(40, 20, -30);
	glVertex3f(40, 70, -30);
	glVertex3f(46, 80, -25);
	glVertex3f(50, 80, -20);
	glEnd();
	//top
	glBegin(GL_POLYGON);
	glColor3f(c1 * 0.5, c2 * 0.5, 0);
	glVertex3f(10, 20, -30);
	glVertex3f(10, 70, -30);
	glVertex3f(40, 70, -30);
	glVertex3f(40, 20, -30);
	glEnd();
	//back-window
	glBegin(GL_POLYGON);
	glColor3f(0.7, 1.0, 1.0);
	glVertex3f(10, 20, -30);
	glVertex3f(40, 20, -30);
	glVertex3f(46, 10, -25);
	glVertex3f(4, 10, -25);
	glEnd();
	//front-window
	glBegin(GL_POLYGON);
	glColor3f(0.7, 1.0, 1.0);
	glVertex3f(10, 70, -30);
	glVertex3f(40, 70, -30);
	glVertex3f(46, 80, -25);
	glVertex3f(4, 80, -25);
	glEnd();
	//bonet-left-triangle
	glBegin(GL_POLYGON);
	glColor3f(c1 * 0.6, c2 * 0.6, 0);
	glVertex3f(0, 100, -20);
	glVertex3f(0, 80, -20);
	glVertex3f(4, 80, -25);
	glEnd();
	//bonet-right-triangle
	glBegin(GL_POLYGON);
	glVertex3f(46, 80, -25);
	glVertex3f(50, 80, -20);
	glVertex3f(50, 100, -20);
	glEnd();
	//bonet
	glBegin(GL_POLYGON);
	glColor3f(c1 * 1, c2 * 1, 0);
	glVertex3f(50, 100, -20);
	glVertex3f(0, 100, -20);
	glVertex3f(4, 80, -25);
	glVertex3f(46, 80, -25);
	glEnd();
	float headLightColor1[] = {1,1,1};
	float headLightColor2[] = {0.3,0.3,0.3};
	drawHeadLight(8, 101,headLightColor1);
	drawHeadLight(42, 101,headLightColor1);
	drawHeadLight(8, -1,headLightColor2);
	drawHeadLight(42, -1, headLightColor2);
	drawWheel(4,15,-1);
	glDisable(GL_DEPTH_TEST);
	
}
void drawCity() {
	int x1 = 900, y1 = 1000;
	glPushMatrix();
	glRotatef(65.0f, 1.0f, 0.0f, 0.0f);// Rotate around the x-axis by 60 so that roads looks 3d
	glTranslatef(1750, 1300, 0);//translate to the position
	drawCircleRoads();//roads
	//first-car-translation-and-rotation-logic
	glPushMatrix();
	glTranslatef((radius - 75)*cos(c1), (radius - 75) * sin(c1), 0);
	glPushMatrix();
	glRotatef(c1 * 180 / PI, 0, 0, 1);
	drawCar(1,0);
	glPopMatrix();
	glPopMatrix();
	//second-car-translation-and-rotation-logic
	glPushMatrix();
	glTranslatef(-(radius - 85) * cos(c2), (radius - 85) * sin(c2), 0);
	glPushMatrix();
	glRotatef(-c2 * 180 / PI, 0, 0, 1);
	drawCar(0.5,0.5);
	glPopMatrix();
	glPopMatrix();
	//second-car-translation-and-rotation-logic
	glPushMatrix();
	glTranslatef(-(radius - 85) * cos(c3), (radius - 85) * sin(c3), 0);
	glPushMatrix();
	glRotatef(-c3 * 180 / PI, 0, 0, 1);
	drawCar(0.7, 0.2);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//buildings
	drawBase(400, 60, 1400, 560, 1380, 610);
	drawBase(200, 50, 1340, 500, 1320, 550);
	drawBase(250, 70, 1430, 430, 1410, 480);
	
}
void drawFerrisWheel() {
	drawBase(20, 170, 1030, 420, 980, 490);
	glPushMatrix();
	glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(900, 750, 800);
	float baseColor[] = { 1,1,1 };
	float topColor[] = { 0.8, 0.8, 0.8 };
	glLineWidth(3);
	drawCircle(radius - 450, 50, -50, topColor);
	glColor3f(1, 0, 0);
	for (int i = 0; i < sides; i++) {
		float angle = 2.0f * PI * i / sides;
		float x = 20 + (radius - 450) * cos(c4 + angle);
		float y = -20 + (radius - 450) * sin(c4 + angle);
		i += 78;
		drawFront(50, 50, x - 50, y - 50, tmp);
		drawFront(50, 50, x - 30, y - 30, redColor);
	}
	drawCircle(radius - 450, 0, -50, baseColor);
	float curColor[] = { 0,0,0 };
	//drawSquare(200, 50, -200, -200, curColor);
	glPopMatrix();
	glPopMatrix();
}

void lightPole() {
	drawBase(150, 15, 1050, 275, 1045, 280);
	drawBase(80, 35, 1040, 425, 1035, 430);
	glPushMatrix();
	glRotatef(30, 0, 1, 0);
	//red-light
	circle(15, 1223, 480, bridgeY == 0 ? greyColor : redColor);
	//green-light
	circle(15, 1223, 445,bridgeY!=0? greyColor : greenColor);
	glPopMatrix();
}
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 1, 1);
	glPushMatrix();
	//ocean
	ocean();
	///rail
	railway();
	railTrack();
	glPopMatrix();
	//rail-static-bridge-right-portion
	drawRightBackBridge();
	if(shipX<=600)
	drawRightFrontBridge();
	//boat-translation-logic
	glPushMatrix();
	glTranslatef(shipX, -shipY, 0);
	boat(1.75, 230 ,300);
	glPopMatrix();
	//rail-moving-bridge-back-portion
	glPushMatrix();
	glTranslatef(0, bridgeY, 0);
	movingBackBridge();
	glPopMatrix();
	//rail-static-bridge-left-back-portion
	drawLeftBackBridge();
	//city-with-cars-and-building
	drawCity();
	drawFerrisWheel();
	lightPole();
	//train-with-engine
	drawTrain(trainX);
	//rail-static-bridge-right-front-portion
	if (shipX >= 600)
		drawRightFrontBridge();
	//rail-moving-bridge-front-portion
	glPushMatrix();
	glTranslatef(0, bridgeY, 0);
	movingFrontBridge();
	glPopMatrix();
	//rail-static-bridge-left-front-portion
	drawLeftFrontBridge();
	glPopMatrix();
	glFlush();
}
void timer(int value) {
	
	c1 = 2* PI * pos1/sides ;
	c2 = 2 * PI * pos2 / sides;
	c3 = 2 * PI * pos3 / sides;
	c4 = 2 * PI * pos2 / sides;
	pos1++;
	pos2+=2;
	pos3+=3;
	if (pos1 == sides) {
		pos1 = 0;
	}
	if (pos2 == sides) {
		pos2 = 0;
	}
	if (pos3 == sides) {
		pos3 = 0;
	}
	if (isBridgeUp) {
		if (shipX <= 1400) {
			shipX += 4;
			shipY += 4;
			if (shipX >= 360) {
				isShipGone = true;
			}

		}
		else {
			shipX = -50;
			shipY = -50;
			bridgeY = 0;
			trainX = 0;
			isShipGone = false;
			isBridgeUp = false;
		}
	}
	
		if (isShipGone) {
			bridgeY -= 3;
			if (bridgeY - 3 <= 0) {
				bridgeY = 0;
				trainX -= 12;
			}
		}
		else if (bridgeY < 250) {
			bridgeY += 5;
		}
		else {
			isBridgeUp = true;
		}
	
	glutPostRedisplay();
	glutTimerFunc(1, timer, 0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 1000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ship Under Bridge Simulation");
	myInit();
	glutDisplayFunc(myDisplay);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();

}

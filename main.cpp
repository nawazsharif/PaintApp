#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdarg.h>
#define white 1,1,1
#define black 0.0,0.0,0.0
#define orange 255.0,201.0,14.0
#define red 255.0,0.0,0.0
#define green 0.0,255.0,0.0
#define blue 0.0,0.0,255.0
#define maroon 185.0,122.0,87.0
#define greyishYellow 239.0,228.0,176.0
#define yellow 255.0,242.0,0.0
#define brown_tree 255, 0, 0
#define brown 77, 0, 0
#define blue1 0, 102, 204
#define blue2 128, 191, 255
#define blue3 128, 191, 255
#define clearWater 0.118, 0.565, 1.000
#define houseWalls 211,212,213
#define clear 1,1,1

using namespace std;


int X ;
int Y ;

int paletteYBound,paletteXBound,paletteGrassXBound,paletteTreeXBound,paletteCloudXBound,paletteHouseXBound;
int paletteSingleBirdXBound,paletteBunchOfFlowersXBound,paletteAFlockOfBirdsXBound,paletteBrushXBound;
int paletteSunXBound,paletteBoatXBound,paletteWaterBrushXBound,paletteRubberXBound,paletteHutXBound;
int paletteColorXBound;

int sampX,sampY,sampXOld,sampXNew,sampYOld,sampYNew,colorMode;

int scaleMode;

int drawMode = 0;


int convertToYCoordinate(int i){return Y-i;}

//Help to calculate correct Y using paint
int y(int a){
    int ans=Y-a;
    return ans;
}


void drawLine(float r,float g, float b ,int x1,int y1, int x2, int y2){
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(r,g,b);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
    glFlush();
    glPopMatrix();
}


void drawScaledPolygon(float scaleX,float scaleY,float r,float g, float b ,int cx,int cy, int numArgs ,...){
    glPushMatrix();

    glTranslatef(cx,cy,1);
    glScalef(scaleX,scaleY,0);


    glRotatef(180,0.0,1.0,0.0);
    glRotatef(180,1.0,0.0,0.0);


    va_list points;
    va_start(points,numArgs);
    int i;



    glBegin(GL_POLYGON);
    glColor3f (r,g,b);
    for(i=1;i<numArgs;i+=2){
        int px,py;

        px=va_arg(points,int);
        py=va_arg(points,int);

        glVertex2i(px,py);
    }
    glEnd();

    va_end(points);
    glFlush();

    glPopMatrix();
}

void d1rawPolygon(float scaleX,float scaleY,float r,float g, float b ,int cx,int cy, int numArgs ,...){
    glPushMatrix();

    glTranslatef(cx,cy,1);
    glScalef(scaleX,scaleY,0);



    va_list points;
    va_start(points,numArgs);
    int i;



    glBegin(GL_POLYGON);
    glColor3f (r,g,b);
    for(i=1;i<numArgs;i+=2){
        int px,py;

        px=va_arg(points,int);
        py=va_arg(points,int);

        glVertex2i(px,py);
    }
    glEnd();

    va_end(points);
    glFlush();

    glPopMatrix();
}


void drawHut(float scaleX, float scaleY ,int cx,int cy)
{
    d1rawPolygon(scaleX,scaleY,yellow,cx,cy,8,122, y(35),164, y(114),344, y(91),299, y(35));
    d1rawPolygon(scaleX,scaleY,brown,cx,cy,8,93, y(113),93, y(193),170, y(204),170, y(113));
    d1rawPolygon(scaleX,scaleY,brown,cx,cy,8,170, y(204),170, y(113),334, y(151),334, y(93));
    d1rawPolygon(scaleX,scaleY,brown,cx,cy,6,93, y(113),170, y(115),134, y(57));
    d1rawPolygon(scaleX,scaleY,brown,cx,cy,6,168, y(113),274, y(150),334, y(94));
    d1rawPolygon(scaleX,scaleY,brown,cx,cy,8,113, y(122),113, y(148),149, y(148),149, y(122));
    d1rawPolygon(scaleX,scaleY,black,cx,cy,8,113, y(123),113, y(150),148, y(150),148, y(122));

    d1rawPolygon(scaleY,scaleY,black,cx,cy,8,229, y(118),229, y(183),272, y(169),272, y(112));
    //drawLine(black,170,f(113),170,f(203));
    d1rawPolygon(scaleX,scaleY,blue,cx,cy,8,66, y(113),95, y(113),134, y(57),122, y(35));

}


void drawAScaledCloud(float scaleX, float scaleY ,int cx,int cy){
    if(scaleX == 0.5){cx+=20;}
    drawScaledPolygon(scaleX,scaleY,blue,cx,cy,52,-60,45,-41,42,-16,20,-5,45,7,48,10,48,26,25,34,39,47,40,58,16,71,32,92,21,94,8,85,
                  -1,72,-1,67,-16,57,-21,42,-15,34,-39,21,-43,3,-36,-20,-29,-28,-15,-35,-21,-53,-13,-74,0,-84,8,-84,18);

}

void drawAScaledHouse(float scaleX, float scaleY ,int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,brown,cx,cy,8,180,30,442,30,442,18,180,18);
    drawScaledPolygon(scaleX,scaleY,green,cx,cy,8,200,18,422,18,422,-84,200,-84);
    drawScaledPolygon(scaleX,scaleY,brown,cx,cy,6,160,-84,304,-180,462,-84);
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,290,18,330,18,330,-60,290,-60);
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,355,-18,390,-18,390,-40,355,-40);
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,232,-18,265,-18,265,-40,232,-40);
}


void drawAScaledSimpleTree(float scaleX, float scaleY  ,int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,green,cx,cy,56,120,-118,130,-102,140,-92,160,-98,170,-112,180,-112,190,-98,215,-92,
                230,-102,242,-120,232,-130,228,-140,238,-150,242,-160,238,-170,208,-180,202,-192,
                192,-198,182,-180,150,-191,140,-181,130,-161,98,-141,100,-131,150,-92,140,-98,130,-92,
                120, -102);

    drawScaledPolygon(scaleX,scaleY,brown_tree,cx,cy,34,160,10,210,10,195,-3,193,-22,190,-38,192,-50,200,-90,188,-100,212,-112,
                204,-122,189,-98,178,-122,165,-112,160,-100,165,-90,155,-60,160,-40);

}

void drawAScaledBird(float scaleX, float scaleY ,int cx,int cy){


        //leg
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,22,-32,31,-68,69,-34,54,-25,56,-57,90,-34,76,-41,107,-24,82,-19,103,-14,79,-19,40);

        //body
    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,20,-84,-32,-87,-7,-82,15,-68,39,-40,62,-12,67,16,60,39,42,55,23,64,-7);

        //tail
    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,26,64,-7, 86,-12,107,-19,117,-22,142,-37,170,-66,138,-57,171,-100,134,-82,143,-111,106,-83,77,-47,55,-23);

        //head
    drawScaledPolygon(scaleX,scaleY,blue,cx,cy,42,-110,-91,-102,-118,-90,-129,-79,-133,-73,-150,-55,-161,-66,-140,-32,-153,-47,-141,-32,-138,
                -20,-127,-42,-127,-30,-118,-20,-95,-19,-70,-25,-52,-33,-37,-58,-23,-86,-26,-102,-38,-108,-55);

        //leap
    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,6,-140,-89,-110,-100,-100,-74);

        //leap
    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-100,-74,-113,-78,-135,-55,-100,-62);

        //wings
    drawScaledPolygon(scaleX,scaleY,green,cx,cy,50,14,-53,-8,-59,-29,-53,-42,-35,-48,-22,-49,-9,-40,9,-25,24,-4,31,18,32,31,23,48,19,60,8,47,6,71,-3,
                84,-13,50,-6,76,-16,97,-30,72,-23,87,-38,100,-54,75,-41,57,-40,34,-41);

        //eye white
    drawScaledPolygon(scaleX,scaleY,white,cx,cy,24,-85,-74,-70,-68,-56,-73,-53,-85,-53,-99,-60,-109,-72,-116,-80,-113,-83,-107,-88,-98,-87,-87,-87,-78);

        //eye black
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,18,-80,-80,-71,-82,-66,-88,-64,-96,-63,-107,-76,-109,-83,-105,-86,-97,-87,-87 );
}

void drawAScaledBunchOFlowers(float scaleX, float scaleY ,int cx,int cy){


    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,-22,-55,-22,125,-5,125,-11,-151);

    drawScaledPolygon(scaleX,scaleY,red,cx,cy,22,-30,-246,-41,-200,-30,-166,-15,-150,17,-160,35,-180,36,-212,27,-245,15,-210,-3,
                -250,-20,-210);

    drawScaledPolygon(scaleX,scaleY,black,cx,cy,6,60,-150,27,34,53,37);

    drawScaledPolygon(scaleX,scaleY,red,cx,cy,16,69,-216,48,-182,49,-150,64,-135,87,-140,109,-162,108,-210,74,-175);

    drawScaledPolygon(scaleX,scaleY,black,cx,cy,6,143,-132,75,100,100,100);

    drawScaledPolygon(scaleX,scaleY,red,cx,cy,14,120,-166,114,-130,134,-106,170,-110,184,-130);

    drawScaledPolygon(scaleX,scaleY,red,cx,cy,14,120,-166,138,-190,145,-150,171,-192,162,-135,197,-165,184,-130);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,6,-39,91,-39,155,72,111);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,36,-72,-89,-60,-53,-57,-24,-67,6,-58,29,-61,54,-45,77,-35,111,-8,138,7,154,
               18,154,-7,141,-14,90,-35,65,-35,33,-45,12,-46,-40,-60,-69 );

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,22,13,155,-1,121,-9,78,-4,43,13,9,11,-15,49,-63,29,7,17,71,26,128,39,153);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,24,-103,-8,-99,8,-92,36,-72,56,-52,75,-41,135,-50,150,-34,159,-20,157,-52,37,
                -74,21,-80,-2);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,36,-72,-89,-60,-53,-57,-24,-67,6,-58,29,-61,54,-45,77,-35,111,-8,138,7,154,18,154,
                -7,141,-14,90,-35,65,-35,33,-45,12,-46,-40,-60,-69);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,22,13,155,-1,121,-9,78,-4,43,13,9,11,-15,49,-63,29,7,17,71,26,128,39,153);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,20,29,-88,9,-29,19,30,31,69,12,54,32,154,47,78,44,30,27,-35,25,-64);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,36,-72,-89,-60,-53,-57,-24,-67,6,-58,29,-61,54,-45,77,-35,111,-8,138,7,154,
               18,154,-7,141,-14,90,-35,65,-35,33,-45,12,-46,-40,-60,-69);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,22,13,155,-1,121,-9,78,-4,43,13,9,11,-15,49,-63,29,7,17,71,26,128,39,153);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,16,-14,-59,-22,-25,-8,-3,-14,28,-8,54,8,37,4,3,-9,-25);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,36,-72,-89,-60,-53,-57,-24,-67,6,-58,29,-61,54,-45,77,-35,111,-8,138,7,154,
               18,154,-7,141,-14,90,-35,65,-35,33,-45,12,-46,-40,-60,-69 );

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,22, 13,155,-1,121,-9,78,-4,43,13,9,11,-15,49,-63,29,7,17,71,26,128,39,153);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,16,60,-57,49,-2,61,66,47,150,71,150,79,102,68,26,71,-22);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,36,-72,-89,-60,-53,-57,-24,-67,6,-58,29,-61,54,-45,77,-35,111,-8,138,7,154,
               18,154,-7,141,-14,90,-35,65,-35,33,-45,12,-46,-40,-60,-69);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,22,13,155,-1,121,-9,78,-4,43,13,9,11,-15,49,-63,29,7,17,71,26,128,39,153);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,14,169,-64,137,-17,121,60,78,147,110,152,143,72,154,-8);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,16,106,-46,82,-16,83,30,61,148,83,149,95,74,101,17,95,-12);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,22,178,-16,173,11,164,25,161,52,150,111,123,149,154,149,167,129,177,88,179,40,192,17);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,6,127,-47,69,150,90,150);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,6,-10,-27,-12,152,17,155);

    drawScaledPolygon(scaleX,scaleY,green,cx,cy,6,58,-95,18,155,54,155);
}

void drawAScaledSun(float scaleX, float scaleY ,int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,red,cx,cy,50,0,38,7,37,14,35,23,30,30,25,33,20,35,15,36,7,35,0,33,-5,32,-10,27,-15,20,-20,0,-26,
                -19,-20,-22,-15,-31,-10,-34,-5,-35,0,-37,7,-35,15,-31,20,-29,25,-22,30,-15,34);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-5,-34,1,-34,1,-110,-5,-110);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-5,123,1,123,1,48,-5,48);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-130,9,-42,9,-42,2,-130,2);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,44,9,134,9,134,2,44,2);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,44,-6,91,-31,86,-36,42,-13);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,37,-20,88,-84,83,-87,31,-26);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,19,-35,36,-75,30,-77,13,-38);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-25,-35,-20,-38,-33,-77,-40,-75);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-36,-18,-31,-27,-98,-75,-103,-72);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-52,-6,-49,-11,-83,-29,-87,-23);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-41,27,-44,23,-79,35,-77,40);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-24,41,-29,37,-92,81,-87,87);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,-15,58,-20,54,-37,84,-32,87);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,18,53,23,50,40,87,35,90);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,30,43,35,40,94,98,90,103);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,8,45,29,49,25,89,51,84,54);
}

void drawAScaledBoat(float scaleX, float scaleY ,int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,-94,-71,-28,-15,26,12,26,-42);

    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,140,-42,140,12,188,-12,255,-85);

    drawScaledPolygon(scaleX,scaleY,black,cx,cy,20,26,-42,26,12,49,24,82,28,119,22,140,12,140,-42,111,-28,72,-26,43,-30);

    drawScaledPolygon(scaleX,scaleY,red,cx,cy,18,6,-45,23,-28,169,-37,169,-58,162,-83,147,-103,22,-103,8,-82,4,-61);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,6,-94,-71,6,-45,23,-28);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,6,255,-85,169,-58,169,-37);

    drawScaledPolygon(scaleX,scaleY,yellow,cx,cy,6,6,-45,23,-28,25,-45);

    drawScaledPolygon(scaleX,scaleY,blue,cx,cy,12,6,-45,25,-45,29,-78,22,-103,8,-82,4,-61);
}


void drawAScaledTuftOfGrass(float scaleX,float scaleY , int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,green,cx,cy,18,-2,13,2,13,7,-3,7,-17,2,6,0,-16,-3,2,-6,-18,-10,-9);
}

void drawWater(float scaleX,float scaleY , int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,clearWater,cx,cy,14,-1,11,2,11,10,5,10,-5,1,-10,-10,-5,-9,5);
}

void drawpoint(int r,int g ,int b,float scaleX,float scaleY , int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,r,g,b,cx,cy,14,-1,11,2,11,10,5,10,-5,1,-10,-10,-5,-9,5);
}

void DrawBrush(float scaleX,float scaleY , int cx,int cy){
    drawScaledPolygon(scaleX,scaleY,black,cx,cy,8,3,412,34,431,54,400,18,380);
    drawScaledPolygon(scaleX,scaleY,blue,cx,cy,8,54,400,18,380,34,354,67,372);
    drawScaledPolygon(scaleX,scaleY,red,cx,cy,8,32,352,69,371,155,249,125,225);
}




void drawRubberOutline(int cx,int cy){

    glPushMatrix();
    glTranslatef(cx,cy,1);
    glColor3f (black);
    glBegin(GL_LINE_LOOP);
    glVertex2i(-10,10);
    glVertex2i(7,10);
    glVertex2i(7,-12);
    glVertex2i(-10,-12);
    glEnd();
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cx,cy,1);
    glColor3f (black);
    glBegin(GL_LINE_LOOP);
    glVertex2i(-7,13);
    glVertex2i(10,13);
    glVertex2i(10,-9);
    glVertex2i(7,-12);
    glVertex2i(7,10);
    glVertex2i(-10,10);
    glEnd();
    glFlush();
    glPopMatrix();
}
void rubUsingRubber(int cx,int cy){

    glPushMatrix();
    glTranslatef(cx,cy,1);
    glColor3f (white);
    glBegin(GL_POLYGON);
    glVertex2i(-10,10);
    glVertex2i(7,10);
    glVertex2i(7,-12);
    glVertex2i(-10,-12);
    glEnd();
    glFlush();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(cx,cy,1);
    glColor3f (white);
    glBegin(GL_POLYGON);
    glVertex2i(-7,13);
    glVertex2i(10,13);
    glVertex2i(10,-9);
    glVertex2i(7,-12);
    glVertex2i(7,10);
    glVertex2i(-10,10);
    glEnd();
    glFlush();
    glPopMatrix();
}

void scaleSelector(int x, int y){
    if(y<=paletteYBound && y>((Y/10)*6)){
       scaleMode =1;
    }
    else if(y>=(Y/10)*3 && y<=((Y/10)*6)){
       scaleMode =2;
    }
    else if(y<(Y/10)*3){
       scaleMode =3;
    }
}


void scalePaletteShapeCreator(int x,int y){
    d1rawPolygon(1,1,white,0,0,8,0,0,90,0,90,((Y/10)*9)+10,0,((Y/10)*9)+10);

    if(drawMode==1){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledTuftOfGrass(1.2,1.2,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledTuftOfGrass(1.6,1.6,50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledTuftOfGrass(2,2,50,Y-650);

    }
    else if(drawMode==2){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledSimpleTree(0.3,0.3,100,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledSimpleTree(0.5,0.5,130,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledSimpleTree(0.7,0.7,160,Y-700);
    }

    else if(drawMode==3){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledCloud(0.3,0.3,40,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledCloud(0.5,0.5,30,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledCloud(0.7,0.7,40,Y-700);
    }


    else if(drawMode==4){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledHouse(0.2,0.2,100,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledHouse(0.3,0.3,130,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledHouse(0.4,0.4,150,Y-700);
    }

    else if(drawMode==5){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledBird(0.02,0.02,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledBird(0.03,0.03,50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledBird(0.04,0.04,50,Y-700);
    }

    else if(drawMode==6){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledBunchOFlowers(0.02,0.02,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledBunchOFlowers(0.03,0.03,50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledBunchOFlowers(0.04,0.04,50,Y-700);
    }
     else if(drawMode==7){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledSun(0.2,0.2,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledSun(0.3,0.3,50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledSun(0.4,0.4,50,Y-700);
    }
    else if(drawMode==8){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawAScaledBoat(0.2,0.2,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawAScaledBoat(0.3,0.3,50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawAScaledBoat(0.4,0.4,50,Y-700);
    }
    else if(drawMode==9){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawWater(1,1,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawWater(1.5,1.5,50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawWater(2,2,50,Y-700);
    }
    else if(drawMode==10){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawRubberOutline(50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawRubberOutline(50,Y-430);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawRubberOutline(50,Y-700);
    }

    else if(drawMode==11){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawHut(.2,.2,-10,Y-300);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawHut(.3,.3,-25,Y-600);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawHut(.4,.4,-50,Y-900);
    }
    else if(drawMode==12){
        drawLine(black,0,(Y/10)*9,90,(Y/10)*9);
        drawpoint(black,.2,.2,50,Y-200);

        drawLine(black,0,(Y/10)*6,90,(Y/10)*6);
        drawpoint(black,.5,.5,50,Y-400);

        drawLine(black,0,(Y/10)*3,90,(Y/10)*3);
        drawpoint(black,1,1,50,Y-700);
    }

}

void colorPaletteItemSelector(int x,int y){
    if(y>=sampY){
        if(x<=sampX && x>=sampXOld){
            colorMode = 1;
            cout << "colour mode 1" << endl;
        }
        else if(x<=sampXNew ){
            colorMode = 2;
            cout << "colour mode 2" << endl;
        }
    }
    else if(y>=sampYOld){
        if(x<=sampX && x>=sampXOld){
            colorMode = 3;
            cout << "colour mode 3" << endl;
        }
        else if(x<=sampXNew ){
            colorMode = 4;
            cout << "colour mode 4" << endl;
        }
    }
}

/*
Draw Mode Selector starts here
*/
void drawModeSelector(int x, int y){
    if(x<=paletteGrassXBound){   drawMode = 1;}
    else if(x<=paletteTreeXBound) { drawMode = 2; }
    else if(x<=paletteCloudXBound) { drawMode = 3;}
    else if(x<=paletteHouseXBound) drawMode = 4;
    else if(x<=paletteSingleBirdXBound) drawMode = 5;
    else if(x<=paletteBunchOfFlowersXBound) drawMode = 6;
    else if(x<=paletteSunXBound) drawMode = 7;
    else if(x<=paletteBoatXBound) drawMode = 8;
    else if(x<=paletteWaterBrushXBound) drawMode = 9;
    else if(x<=paletteRubberXBound) drawMode = 10;
    else if(x<=paletteHutXBound) drawMode = 11;
    else if(x<=paletteBrushXBound) drawMode = 12;
    //else if(x<=paletteColorXBound) drawMode = 13;


    scalePaletteShapeCreator(x,y);

    colorPaletteItemSelector(x,y);
}

void onMouseLeftClick(int mx,int my){
    if(my >= paletteYBound){
       printf("Selecting draw mode\n");

        drawModeSelector(mx,my);
        printf("draw mode is %d\n",drawMode);
    }
    else{
        if(mx<=90){
            printf("Selecting scale\n");
            scaleSelector(mx,my);
        }
        else{
            printf("draw mode is %d  ;;;  drawing now...\n",drawMode);

            if(drawMode==1) {
                    if(scaleMode ==1){
                        drawAScaledTuftOfGrass(1.2,1.2,mx,my);
                    }
                    else if(scaleMode ==2){
                        drawAScaledTuftOfGrass(1.6,1.6,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledTuftOfGrass(2.7,7.7,mx,my);
                    }
            }
             if(drawMode==2 && (my<Y-150)) {
                    if(scaleMode ==1){
                        drawAScaledSimpleTree(0.3,0.3,mx+60,my-30);
                    }
                    else if(scaleMode ==2){
                        drawAScaledSimpleTree(0.5,0.5,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledSimpleTree(0.7,0.7,mx+120,my-50);
                    }
            }
            if(drawMode==3 && (my<Y-120)) {
                    if(scaleMode ==1){
                        drawAScaledCloud(0.3,0.3,mx,my);
                    }
                    else if(scaleMode ==2){
                        drawAScaledCloud(0.5,0.5,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledCloud(0.7,0.7,mx,my);
                    }
            }

            if(drawMode==4 && (my<Y-150)) {
                    if(scaleMode ==1){
                        drawAScaledHouse(0.2,0.2,mx+60,my-10);
                    }
                    else if(scaleMode ==2){
                        drawAScaledHouse(0.3,0.3,mx+90,my-10);
                    }
                    else if(scaleMode ==3){
                        drawAScaledHouse(0.5,0.5,mx,my);
                    }
            }
             if(drawMode==5) {
                    if(scaleMode ==1){
                        drawAScaledBird(0.02,0.02,mx,my);
                    }
                    else if(scaleMode ==2){
                        drawAScaledBird(0.03,0.03,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledBird(0.05,0.05,mx,my);
                    }
            }

             if(drawMode==6) {
                    if(scaleMode ==1){
                        drawAScaledBunchOFlowers(0.03,0.02,mx,my);
                    }
                    else if(scaleMode ==2){
                        drawAScaledBunchOFlowers(0.05,0.03,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledBunchOFlowers(0.08,0.05,mx,my);
                    }
            }


             if(drawMode==7 && (my<Y-120)) {
                    if(scaleMode ==1){
                        drawAScaledSun(0.2,0.2,mx,my);
                    }
                    else if(scaleMode ==2){
                        drawAScaledSun(0.35,0.35,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledSun(0.45,0.45,mx,my);
                    }
            }
            if(drawMode==8) {
                    if(scaleMode ==1){
                        drawAScaledBoat(0.2,0.2,mx+20,my);
                    }
                    else if(scaleMode ==2){
                        drawAScaledBoat(0.35,0.35,mx+40,my);
                    }
                    else if(scaleMode ==3){
                        drawAScaledBoat(0.45,0.45,mx+40,my);
                    }
            }

             if(drawMode==9) {
                    if(scaleMode ==1){
                        drawWater(1,1,mx,my);
                    }
                    else if(scaleMode ==2){
                        drawWater(1.5,1.5,mx,my);
                    }
                    else if(scaleMode ==3){
                        drawWater(2.5,2.5,mx,my);
                    }
            }
            if(drawMode==10) {
                    if(scaleMode ==1){
                        rubUsingRubber(mx,my);
                    }
                    else if(scaleMode ==2){
                        rubUsingRubber(mx,my);
                    }
                    else if(scaleMode ==3){
                        rubUsingRubber(mx,my);
                    }
            }

            if(drawMode==11) {
                    if(scaleMode ==1){
                        drawHut(.2,.2,mx-40,my-140);
                    }
                    else if(scaleMode ==2){
                        drawHut(.35,.35,mx-65,my-230);
                    }
                    else if(scaleMode ==3){
                        drawHut(.5,.5,mx-90  ,my-330);
                    }
            }


            if(drawMode==12) {

            if(scaleMode ==1){
                if(colorMode==1){
                    drawpoint(red,.3,.3,mx,my);
                }
                else if(colorMode==2){
                    drawpoint(green,.3,.3,mx,my);
                }
                else if(colorMode==3){
                    drawpoint(blue,.3,.3,mx,my);
                }
                else if(colorMode==4){
                    drawpoint(black,.3,.3,mx,my);
                }

            }
            else if(scaleMode ==2){
                if(colorMode==1){
                    drawpoint(red,.5,.5,mx,my);
                }
                else if(colorMode==2){
                    drawpoint(green,.5,.5,mx,my);
                }
                else if(colorMode==3){
                    drawpoint(blue,.5,.5,mx,my);
                }
                else if(colorMode==4){
                    drawpoint(black,.5,.5,mx,my);
                }

            }
            else if(scaleMode ==3){
                if(colorMode==1){
                    drawpoint(red,1,1,mx,my);
                }
                else if(colorMode==2){
                    drawpoint(green,1,1,mx,my);
                }
                else if(colorMode==3){
                    drawpoint(blue,1,1,mx,my);
                }
                else if(colorMode==4){
                    drawpoint(black,1,1,mx,my);
                }

            }

            }
        }
    }
}


void MouseButton(int button,int state,int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			onMouseLeftClick(x,convertToYCoordinate(y));
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
}

void MouseMotion(int mx, int my)
{
	if(y(my) < (Y-100) && mx> paletteXBound+10){
            cout << mx <<" "<< my << endl;
        if(drawMode==1) {
            if(scaleMode ==1){
                drawAScaledTuftOfGrass(1.2,1.2,mx,Y-my);
            }
            else if(scaleMode ==2){
                drawAScaledTuftOfGrass(1.6,1.6,mx,Y-my);
            }
            else if(scaleMode ==3){
                drawAScaledTuftOfGrass(2.7,7.7,mx,Y-my);
            }
        }
        else if(drawMode==9){
            if(scaleMode ==1){
                drawWater(1,1,mx,Y-my);
            }
            else if(scaleMode ==2){
                drawWater(1.5,1.5,mx,Y-my);
            }
            else if(scaleMode ==3){
                drawWater(2.5,2.5,mx,Y-my);
            }

        }
        else if(drawMode==10){
            if(scaleMode ==1){
                rubUsingRubber(mx,Y-my-20);
            }
            else if(scaleMode ==2){
                rubUsingRubber(mx,Y-my-20);
            }
            else if(scaleMode ==3){
                rubUsingRubber(mx,Y-my-20);
            }
        }


        else if(drawMode==12){
                cout <<colorMode<< endl;

            if(scaleMode ==1){
                if(colorMode==1){
                        cout << "draw" << endl;
                    drawpoint(red,.3,.3,mx,Y-my);
                }
                else if(colorMode==2){
                    drawpoint(green,.3,.3,mx,Y-my);
                }
                else if(colorMode==3){
                    drawpoint(blue,.3,.3,mx,Y-my);
                }
                else if(colorMode==4){
                    drawpoint(black,.3,.3,mx,Y-my);
                }

            }
            else if(scaleMode ==2){
                if(colorMode==1){
                    drawpoint(red,.5,.5,mx,Y-my);
                }
                else if(colorMode==2){
                    drawpoint(green,.5,.5,mx,Y-my);
                }
                else if(colorMode==3){
                    drawpoint(blue,.5,.5,mx,Y-my);
                }
                else if(colorMode==4){
                    drawpoint(black,.5,.5,mx,Y-my);
                }

            }
            else if(scaleMode ==3){
                if(colorMode==1){
                    drawpoint(red,1,1,mx,Y-my);
                }
                else if(colorMode==2){
                    drawpoint(green,1,1,mx,Y-my);
                }
                else if(colorMode==3){
                    drawpoint(blue,1,1,mx,Y-my);
                }
                else if(colorMode==4){
                    drawpoint(black,1,1,mx,Y-my);
                }

            }
        }
    }

}

void drawingPaletteCreation(){

int linX=X/15;
 int reqy = (Y/10)*9;
    drawLine(black,linX,0,linX,reqy);
    drawLine(black,0,reqy,X,reqy);
    paletteYBound=reqy;
    paletteXBound=linX;

   // Item 1 : Grass

    int reqX =X/20;
    paletteGrassXBound=reqX;
    //creating vertical end boundary for grass
    drawLine(black,reqX,reqy,reqX,Y);
    drawAScaledTuftOfGrass(1,1,30,Y-30);



    //Item 2 : Tree

    reqX =(X/20)*2;
    paletteTreeXBound=reqX;
    //creating vertical end boundary for Tree
    drawLine(black,reqX,reqy,reqX,Y);
    //Drawing Tree to palette
    glPushMatrix();
    drawAScaledSimpleTree(0.3,0.3,150,Y-70);
    glPopMatrix();

    //Item 3 : Cloud
    reqX =(X/20)*3;
    paletteCloudXBound=reqX;
    //creating vertical end boundary for Cloud
    drawLine(black,reqX,reqy,reqX,Y);
    //Drawing Cloud to palette
    glPushMatrix();
    drawAScaledCloud(0.3,0.3,170,Y-40);
    glPopMatrix();

    //Item 4 : House

    reqX =(X/20)*4;
    paletteHouseXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    glPushMatrix();
    drawAScaledHouse(0.2,0.2,300,Y-50);
    glPopMatrix();


    //Item 5 : Single Bird
    reqX =(X/20)*5;
    paletteSingleBirdXBound=reqX;
    //creating vertical end boundary for Single Bird
    drawLine(black,reqX,reqy,reqX,Y);
    //Drawing Single Bird to palette
    drawAScaledBird(0.03,0.03,300,Y-50);



    //Item 6 : Bunch Of Flowers

    reqX =(X/20)*6;
    paletteBunchOfFlowersXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    drawAScaledBunchOFlowers(0.08,0.08,380,Y-50);



    //Item 7: Sun

    reqX =(X/20)*7;
    paletteSunXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    drawAScaledSun(0.2,0.2,440,Y-40);




    //Item 8 : Boat

    reqX =(X/20)*8;
    paletteBoatXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    drawAScaledBoat(0.15,0.15,520,Y-50);



    //Item 9 : Water Brush

    reqX =(X/20)*9;
    paletteWaterBrushXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    drawWater(1.5,1.5,580,Y-40);


    //Item 10 : Rubber

    reqX =(X/20)*10;
    paletteRubberXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    drawRubberOutline(650,Y-40);

    //Item 10 : Hut
    reqX =(X/20)*11;
    paletteHutXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    drawHut(.2,.2,670,Y-170);

    //Item 10 : Brush
    reqX =(X/20)*12;
    paletteBrushXBound=reqX;
    drawLine(black,reqX,reqy,reqX,Y);
    DrawBrush(.2,.2,800,Y+20);


    //Color palette boundaries
    sampY = (Y/10)/2+(Y/10)*9;
    sampX = (X/20)/2+(X/20)*12;
    sampXOld = (((X/20)*12)+1);
    sampXNew = (((X/20)*13)-1);
    paletteColorXBound = ((X/20)*13);
    sampYOld = (Y/10)*9+1;

    drawLine(black,(X/20)*12,sampY,(X/20)*13,sampY);
    drawLine(black,(X/20)*13,(Y/10)*9,(X/20)*13,Y);
    drawLine(black,(X/20)*13,(Y/10)*9,(X/20)*13,Y);
    drawLine(black,sampX,(Y/10)*9,sampX,Y);
    d1rawPolygon(1,1,red,0,0,8,sampXOld,sampY,sampX,sampY,sampX,Y,sampXOld,Y);
    d1rawPolygon(1,1,green,0,0,8,sampX,sampY,sampXNew,sampY,sampXNew,Y,sampX,Y);
    d1rawPolygon(1,1,blue,0,0,8,sampXOld,sampYOld,sampX,sampYOld,sampX,sampY,sampXOld,sampY);
    d1rawPolygon(1,1,black,0,0,8,sampX,sampYOld,sampXNew,sampYOld,sampXNew,sampY,sampX,sampY);

}


void myDisplay(void){
    glClear (GL_COLOR_BUFFER_BIT);
drawingPaletteCreation();

}

void myInit (void)
{
glClearColor(1.0, 1.0, 1.0, 0.0);
glColor3f(0.0f, 0.0f, 0.0f);
glPointSize(15.0);
glLineWidth(4.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, X, 0.0, Y);

}

void setFullScreen(){
    X=1366;
    Y=768;
}


int main(int argc, char** argv)
{
setFullScreen();
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (X, Y);
glutCreateWindow ("Scenery Maker");
glutDisplayFunc(myDisplay);
glutMouseFunc(MouseButton);
glutMotionFunc(MouseMotion);
myInit ();

glClear (GL_COLOR_BUFFER_BIT);

glutMainLoop();
}





//
//  main.cpp
//  Proyecto Final de Graficas Computacionales
//
//  Clean The City (Brick Breaker)
//
//  Created by Azael Alanis & Ivan Diaz on 10/13/14.
//  Copyright (c) 2014 Azael Alanis & Ivan Diaz. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Basura.h"
#include "Sound.h"
#include "SOIL.h"
#include "Imageloader.h"

using namespace std;

int angulo = 0;
int winWidth = 600;
int winHeight = 600;
float xRaqueta = 0;
float yRaqueta = 0;
float xBola = 3;
int dirX = 1;
float yBola = 0;
int dirY = 3;
float zBola = 0;
int dirZ = -3;
bool enMarcha = true;
bool showMenu = true;
string jugar = "JUGAR";
string titulo ="C L E A N  T H E  C I T Y";
string titulo2 = "Clean The City - Instrucciones";
bool musica = true;
bool suelta = false;
int cont = 0;
int vidas = 3;
int tiempo = 0;
Basura objeto = Basura();
vector<Basura> listaBasuras;
static GLuint texName[36];
static GLfloat zPos = -60.0f;


Sound background = Sound("/Users/ivandiaz/Desktop/Proyecto Final/BackgroundSong.wav");

//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
    
}

void initRendering()
{
    int i=0;
    /*glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);*/
    // glEnable(GL_COLOR_MATERIAL);
    glGenTextures(5, texName); //Make room for our texture
    Image* image = loadBMP("/Users/ivandiaz/Downloads/Tercer Parcial/Semana12/ImagenesMemorama/ciervo.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/ivandiaz/Downloads/Tercer Parcial/Semana12/ImagenesMemorama/Lobo.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/ivandiaz/Downloads/Tercer Parcial/Semana12/ImagenesMemorama/Brick.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/ivandiaz/Downloads/Tercer Parcial/Semana12/ImagenesMemorama/Clouds.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/ivandiaz/Downloads/Tercer Parcial/Semana12/ImagenesMemorama/Foto.bmp");
    loadTexture(image,i++);
    image = loadBMP("/Users/ivandiaz/Downloads/Tercer Parcial/Semana12/ImagenesMemorama/dragon.bmp");
    loadTexture(image,i++);
    // image = loadBMP("/Users/mariaroque/Imagenes/ojo.bmp");
    delete image;
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 1.0f, -6.0f);
}

void sound (int value){
    if (musica) {
        background.PlaySound();
        glutTimerFunc(90000,sound,0);
    }
}

void cuentaTiempo(int i) { //funcion del timer que se utilizara en el programa
    if (i == 1) {
        if (enMarcha == true) {
            tiempo+=1;
            angulo = angulo +1;
            glutTimerFunc(100, cuentaTiempo, 1);
        }
    }
}

string creaFormato(int t){ //funcion que te crea el formato en base a un numero entero que representa el tiempo transcurrido
    string hora;
    int min, sec, msec;
    msec = t % 10;
    sec = t/10;
    min = sec/60;
    if (min != 0) {
        sec -= (min*60);
    }
    if (sec<10) {
        hora = to_string(min)+":0" + to_string(sec)+"."+to_string(msec)+"\0";
    } else {
        hora = to_string(min)+":" + to_string(sec)+"."+to_string(msec)+"\0";
    }
    return hora;
}

void controlBola (int v){
    if (enMarcha && suelta && !showMenu){
        xBola += dirX;
        yBola += dirY;
        zBola += dirZ;
    }
    
    if (xBola > 149.333) { //Limite derecha
        xBola = 149.333;
        dirX = -dirX;
    }
    
    if (xBola < -149.333) { //Limite izquierda
        xBola = -149.333;
        dirX = -dirX;
    }
    
    if (yBola > 149.333) { //Limite derecha
        yBola = 149.333;
        dirY = -dirY;
    }
    
    if (yBola < -149.333) { //Limite izquierda
        yBola = -149.333;
        dirY = -dirY;
    }
    
    if(zBola <= -100){
        zBola = -100;
        dirZ = -dirZ;
    }
    
    if(zBola > 45){ //Hardcoded
        cont = 1;
        suelta = false;
        vidas--;
    }
    
    if ((yBola < yRaqueta + 50 && yBola > yRaqueta - 50) && (xBola > xRaqueta - 50 && xBola < xRaqueta + 50) && zBola > 40){
        zBola = 40;
        dirZ = -dirZ;
    }
    
    objeto.colision(xBola, yBola, zBola, 5);
    for (int i = 0; i < listaBasuras.size(); i++) {
        if (listaBasuras[i].colision(xBola, yBola, zBola, 5)){
            dirX = -dirX;
            dirY = -dirY;
            dirZ = -dirZ;
            listaBasuras.erase(listaBasuras.begin() + i );
            break;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(60, controlBola, 0);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    tiempo = 0;
    objeto.setPositions(0, 0, -100);
    int cont = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 2; k++) {
                listaBasuras.push_back(Basura((-170 + (55 * i)), //En x
                                              (164 - (96 * j)), //En y
                                              (-80 + (45 * k))));
            }
        }
    }
}

void drawNumber (float x, float y, float z, char *string){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(.8, .8, 1.0);
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string);
    glPopMatrix();
}

void borraBasurasActuales() {
    for (int i = 0; i < listaBasuras.size(); i++) {
        listaBasuras.erase(listaBasuras.begin() + i );
    }
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY) {
    switch (theKey) {
        case 27:
            exit(-1); //Se acaba el programa
            break;
        case 'i':
        case 'I':
            if (enMarcha == false) {
                enMarcha = true;
                cuentaTiempo(1);
            }
            break;
        case 'r':
        case 'R':
            borraBasurasActuales();
            init();
            glutPostRedisplay();
            break;
        case 'p':
        case 'P':
            enMarcha = false;
            break;
        case 'm':
        case 'M':
            musica = !musica;
            if (!musica){
                background.StopSound();
            }else{
                sound(0);
            }
            break;
        default:
            break;
    }
}

void onMenu(int opcion) {
    switch(opcion) {
        case 0:
            break;
        case 1: //Iniciar
            
            break;
        case 2: //Pausa
            enMarcha = false;
            break;
        case 3: // Reiniciar
            init();
            break;
        case 4:
            musica = !musica;
            if (!musica){
                background.StopSound();
            }else{
                sound(0);
            }
            break;
        case 5:
            exit(1);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void creacionMenu(void) {
    int menuFondo, menuPrincipal;
    menuFondo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Azael Alanis - A01175470", 0);
    glutAddMenuEntry("Ivan Diaz - A01175445", 0);
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Autor", menuFondo);
    glutAddMenuEntry("Iniciar", 1);
    glutAddMenuEntry("Pausa", 2);
    glutAddMenuEntry("Reiniciar", 3);
    glutAddMenuEntry("Musica", 4);
    glutAddMenuEntry("Salir", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawGeneralText(const char *text, int length, double x, double y){
    glRasterPos2d(x, y);
    for(int i=0; i<length; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
    }
}

void drawGeneralText2(const char *text, int length, double x, double y){
    glRasterPos2d(x, y);
    for(int i=0; i<length; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)text[i]);
    }
}

void SpecialKey(int key, int x, int y) {
    
}

void myMouseMotionPass(int mouseX, int mouseY){
    cout<< "mouse X = " << mouseX << endl;
    cout<< "mouse Y = " << mouseY << endl;
    if(mouseX <= 76){
        xRaqueta = -149.333;
    } else if (mouseX >= 524) {
        xRaqueta = 149.333;
    } else {
        xRaqueta = ((float)mouseX) / 600.0f * 400.0f - 200.0f;
    }
    
    if(mouseY <= 76){
        yRaqueta = 149.333;
    } else if (mouseY >= 524){
        yRaqueta = -149.333;
    } else {
        yRaqueta = (((float)mouseY) / 600.0f * 400.0f - 200.0f) * -1.0f;
    }
    cout<< "raqueta X = " << xRaqueta << endl;
    cout<< "raqueta Y = " << yRaqueta << endl;
    glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y){
    //cout<<"X: " << x << endl;
    //cout<<"Y: " << y << endl;
    GLint xmouse = (x - 400) * 2;
    GLint ymouse = winHeight - y * 2;
    //cout<<"Xmouse: " << xmouse << endl;
    //cout<<"Ymouse: " << ymouse << endl;
    
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            //cout <<"xraqueta: " << xRaqueta << endl;
            //cout <<"yraqueta: " << yRaqueta << endl;
            cont++;
            if (xmouse >= -308 && xmouse <= -76 && ymouse >= 58 && ymouse <= 172){
                showMenu = false;
            }
            if (cont == 2){
                suelta = true;
                cuentaTiempo(1);
            }
            glutPostRedisplay();
        }
    }
}

void reshape (int ancho, int alto) {
    winWidth = ancho;
    winHeight = ancho;
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum (-200.0, 200.0, -200.0, 200.0, 160, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (showMenu)
    {
        //glColor3f(0.0, 0.0, 0.0);
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, texName[11]);
        
        glPushMatrix();
        
        glBindTexture(GL_TEXTURE_2D, texName[4]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-200.0f, -200.0f, 200);
        
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(200.0f, -200.0f, -200);
        
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-200.0f, 200.0f, -200);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(200.0f, 200.0f, 200);
        glEnd();
        
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(3, 50, 0);
        glScalef(1.0, 0.5, 0.0);
        glutWireCube(100.0);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(3, -20, 0);
        glScalef(1.0, 0.5, 0.0);
        glutWireCube(100.0);
        glPopMatrix();
        
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(3, -90, 0);
        glScalef(1.0, 0.5, 0.0);
        glutWireCube(100.0);
        glPopMatrix();
        
        drawGeneralText(jugar.data(),jugar.size(), -30, 40);
        drawGeneralText(titulo.data(),titulo.size(), -100, 150);
        
    }
    else
    {
        //objeto.draw();
        for (int i = 0; i < listaBasuras.size(); i++) {
            listaBasuras[i].draw();
        }
        
        glColor3f(1.0, 1.0, 1.0);
        
        glPushMatrix();
        glTranslatef(0, 0, 169);
        glScaled(400, 400, 140);
        glutWireCube(1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(xRaqueta, yRaqueta, 37.0);
        glScalef(100.0, 100.0, 5.00);
        glutWireCube(1.0);
        glPopMatrix();
        
        //bola
        if (!suelta)
        {
            xBola = xRaqueta;
            yBola = yRaqueta;
            glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(xBola, yBola, 1.0);
            glScalef(10, 10, 10);
            glutWireSphere(1, 30, 30);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glColor3f(1.0, 1.0, 1.0);
            glTranslatef(xBola, yBola, zBola);
            glScalef(10, 10, 10);
            glutWireSphere(1, 30, 30);
            glPopMatrix();
        }
        
        glPushMatrix();
        glTranslatef(1, 1, zBola);
        glScaled(400, 400, 10);
        glutWireCube(1);
        glPopMatrix();
        
        //Lineas de apoyo
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(1, yBola, zBola);
        glScaled(400, 1, 1);
        glutSolidCube(1);
        glPopMatrix();
        
        glPushMatrix();
        glTranslatef(xBola, 1, zBola);
        glScaled(1, 400, 1);
        glutSolidCube(1);
        glPopMatrix();
        //Fin de lineas de apoyo
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        glTranslatef(0, 0, -30);
        glScaled(400, 400, 139);
        glutWireCube(1);
        glPopMatrix();
        
        GLUquadricObj *qobj;
        
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, texName[11]);
        
        glPushMatrix();
        
        
           /* glBindTexture(GL_TEXTURE_2D, texName[1]);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-200.0f, -200.0f, z);
            
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-200.0f, -200.0f, z - 10.0f);
            
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-200.0f, 200.0f, z - 10.0f);
            
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-200.0f, 200.0f, z);
            glEnd();*/
            
            //FONDO
            /* glBindTexture(GL_TEXTURE_2D, texName[0]);
             // glutSolidSphere(1.0,10,10);
             glBegin(GL_QUADS);
             glTexCoord2f(0.0f, 0.0f);
             glVertex3f(-200.0f, -200.0f, -200);
             
             glTexCoord2f(1.0f, 0.0f);
             glVertex3f(200.0f, -200.0f, -200);
             
             glTexCoord2f(1.0f, 1.0f);
             glVertex3f(200.0f, 200.0f, 200);
             
             glTexCoord2f(0.0f, 1.0f);
             glVertex3f(-200.0f, 200.0f, 200);
             glEnd();*/
            
            // Floor
            
            glBindTexture(GL_TEXTURE_2D, texName[2]);
            
            // glutSolidSphere(1.0,10,10);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-200.0f, -200.0f, -200);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(200.0f, -200.0f, -200);
            
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(200.0f, -200.0f, 200);
            
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-200.0f, -200.0f, 200);
            glEnd();
            
            //Ceiling
            glBindTexture(GL_TEXTURE_2D, texName[3]);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-200.0f, 200.0f, -200);
            
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(200.0f, 200.0f, -200);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(200.0f, 200.0f, 200);
        
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-200.0f, 200.0f, 200);
            glEnd();
            
            
            // Left Wall
            glBindTexture(GL_TEXTURE_2D, texName[4]);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(-200.0f, -200.0f, 200);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(-200.0f, -200.0f, -200);
            
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(-200.0f, 200.0f, -200);
            
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(-200.0f, 200.0f, 200);
            glEnd();
            
            
            // Right Wall
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(200.0f, 200.0f, 200);
            
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(200.0f, 200.0f, -200);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(200.0f, -200.0f, -200);
            
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(200.0f, -200.0f, 200);
            glEnd();
            
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }
    
    glColor3f(1.0, 0.0, 0.0);
    string aux = creaFormato(tiempo);
    string vida = "Vidas = ";
    string tiempo = "Tiempo = ";
    string vidas2 = to_string(vidas);
    drawGeneralText(tiempo.data(), tiempo.size(), -200, -195);
    drawGeneralText(aux.data(), aux.size(), -130, -195);
    drawGeneralText(vida.data(), vida.size(), 130, -195);
    drawGeneralText(vidas2.data(), vidas2.size(), 185, -195);
    
    glutSwapBuffers();
}

void myDisplay2 () {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glColor3ub(255, 255, 255);
    //string titulo2 = "Clean The City - Instrucciones";
    string linea1 = " El juego esta inspirado en Brick Breaker y lo que";
    string linea2 = " tienes que hacer es mover la 'paleta' para hacer";
    string linea3 = " que la pelota rebote y destruya la mayor cantidad";
    string linea4 = " botes de basura posibles y de esta manera limpiar";
    string linea5 = " la ciudad.";
    string linea6 = " Mouse: mover la paleta";
    string linea7 = " Click: lanzar la pelota";
    string linea8 = " Tecla P: pausar juego";
    string linea9 = " Tecla R: reiniciar juego";
    string linea10 = " Tecla I: mover pelota despues de reiniciar juego";
    string linea11 = " Boton derecho: mostrar menu";
    string credito = "Creditos";
    string credito1 = "Azael Alanis Garza - A01175470";
    string credito2 = "Ivan Diaz Martinez - A01175445";
    drawGeneralText(titulo2.data(), titulo2.size(), -.8, 0.9);
    drawGeneralText2(linea1.data(), linea1.size(), -1, 0.8);
    drawGeneralText2(linea2.data(), linea2.size(), -1, 0.7);
    drawGeneralText2(linea3.data(), linea3.size(), -1, 0.6);
    drawGeneralText2(linea4.data(), linea4.size(), -1, 0.5);
    drawGeneralText2(linea5.data(), linea5.size(), -1, 0.4);
    drawGeneralText2(linea6.data(), linea6.size(), -1, 0.3);
    drawGeneralText2(linea7.data(), linea7.size(), -1, 0.2);
    drawGeneralText2(linea8.data(), linea8.size(), -1, 0.1);
    drawGeneralText2(linea9.data(), linea9.size(), -1, 0.0);
    drawGeneralText2(linea10.data(), linea10.size(), -1, -0.1);
    drawGeneralText2(linea11.data(), linea11.size(), -1, -0.2);
    drawGeneralText(credito.data(), credito.size(), -.25, -0.5);
    drawGeneralText2(credito1.data(), credito1.size(), -0.7, -0.6);
    drawGeneralText2(credito2.data(), credito2.size(), -0.7, -0.7);
    glutSwapBuffers ();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Clean the City");
    init();
    glEnable(GL_DEPTH_TEST);
    creacionMenu();
    initRendering();
    //glClearColor(1.0,1.0,1.0,1.0);
    glutDisplayFunc(myDisplay);
    glutTimerFunc(100, controlBola, 0);
    glutTimerFunc(0, sound, 0);
    
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(SpecialKey);
    glutPassiveMotionFunc(myMouseMotionPass);
    glutMouseFunc(myMouse);
    
    //Ventana 2
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(winWidth/2, winHeight);
    glutInitWindowPosition(winWidth, 0);
    glutCreateWindow("Instrucciones");
    glutDisplayFunc(myDisplay2);
    //glutTimerFunc(100, cuentaTiempo, 1);
    glutMainLoop();
    return 0;
}

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{
    
}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }
        
        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }
        
        T* get() const
        {
            return array;
        }
        
        T &operator*() const
        {
            return *array;
        }
        
        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        T* operator->() const
        {
            return array;
        }
        
        T* release()
        {
            isReleased = true;
            return array;
        }
        
        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }
        
        T* operator+(int i)
        {
            return array + i;
        }
        
        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}


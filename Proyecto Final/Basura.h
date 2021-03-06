//
//  Basura.h
//  Proyecto Final de Graficas Computacionales
//
//  Clean The City (Brick Breaker)
//
//  Created by Azael Alanis & Ivan Diaz on 10/13/14.
//  Copyright (c) 2014 Azael Alanis & Ivan Diaz. All rights reserved.
//

#ifndef Proyecto_Final_Basura_h
#define Proyecto_Final_Basura_h

class Basura {
private:
    double posicionX;
    double posicionY;
    double posicionZ;
    int angulo;
    int resiste;
    double radio;
    int altura;
    bool visible;
    
public:
    Basura() {
        posicionX = 0.0;
        posicionY = 0.0;
        posicionZ = 0.0;
        resiste = 1;
        visible = true;
        radio = 20;
        altura = 70;
        angulo = 0;
    }
    
    Basura (double posX, double posY, double posZ) {
        posicionX = posX;
        posicionY = posY;
        posicionZ = posZ;
        resiste = 1;
        visible = true;
        radio = 20;
        altura = 70;
        angulo = 0;
    }
    
    void setPositions(double posX, double posY, double posZ){
        posicionX = posX;
        posicionY = posY;
        posicionZ = posZ;
    }
    
    void setRadio (int r) {
        radio = r;
    }
    
    int getRadio (){
        return radio;
    }
    
    void setAltura (int a) {
        altura = a;
    }
    
    int getAltura (){
        return altura;
    }
    
    void setPosicionX (double posX){
        posicionX = posX;
    }
    
    double getPosicionX () {
        return posicionX;
    }
    
    void setPosicionY (double posY) {
        posicionY = posY;
    }
    
    double getPosicionY () {
        return posicionY;
    }
    
    
    void setPosicionZ (double posZ) {
        posicionZ = posZ;
    }
    
    double getPosicionZ () {
        return posicionZ;
    }
    
    void setResiste (int res) {
        resiste = res;
    }
    
    int getResiste () {
        return resiste;
    }
    
    void setVisible (bool vis) {
        visible = vis;
    }
    
    bool getVisible () {
        return visible;
    }
    
    bool dentroDelRango (double valor, double valorInferior, double valorSuperior) {
        if ((valorInferior <= valor) && (valor <= valorSuperior)) {
            return true;
        } else {
            return false;
        }
    }
    
    //Aqui se mandan como parametros las posiciones en X, Y y Z de algun objeto y revisa si hubo colision
    //Con una instancia de bote de basura
    bool colision (double posExternaX, double posExternaY, double posExternaZ, double radioExterno) {
        double valorInferiorX = posicionX - radio;
        double valorSuperiorX = posicionX + radio;
        double valorInferiorY = posicionY - (altura * .5);
        double valorSuperiorY = posicionY + (altura * .5);
        
        if ((dentroDelRango((posExternaX + radioExterno), valorInferiorX, valorSuperiorX) ||
             dentroDelRango((posExternaX - radioExterno), valorInferiorX, valorSuperiorX)) &&
            (dentroDelRango((posExternaY + radioExterno), valorInferiorY, valorSuperiorY) ||
             dentroDelRango((posExternaY - radioExterno), valorInferiorY, valorSuperiorY)) &&
            (posExternaZ <= (posicionZ + radio) || posExternaZ <= (posicionZ - radio))) {
            resiste--;
            if (resiste == 0) {
                visible = false;
            }
            return true;
        }
        return false;
    }
    
    
    void draw() {
        GLUquadricObj *qobj;
        qobj = gluNewQuadric();
        if(angulo < 360)
            angulo+=3;
        else
            angulo = 0;
        if (visible) { // Si dibujarlo
            glPushMatrix();
            glColor3ub(90, 160, 160);
            glTranslatef(posicionX, posicionY, posicionZ);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glRotated(angulo, 0, 0, 1);
            gluQuadricDrawStyle(qobj, GLU_FILL);
            gluQuadricNormals(qobj, GLU_FLAT);
            gluQuadricTexture(qobj, GLU_TRUE);
            gluCylinder(qobj, radio, radio, altura, 10, 10);
            glPopMatrix();
        }
        //glDisable(GL_TEXTURE_2D);
    }
};

#endif

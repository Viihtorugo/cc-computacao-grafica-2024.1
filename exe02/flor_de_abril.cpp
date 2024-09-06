//
//  Transformacoes1
//
//  Created by Marcelo Costa on 15/12/12.
//  Copyright (c) 2012 Universidade Federal de Alagoas - UFAL. All rights reserved.
//
#include <iostream>
#include <GL/glut.h>

using namespace std;

float angle = 0.0f;
bool isRotating = false;
bool direction = true;
bool stop = true;
float rotationSpeed = 1.0f;

void init(void)
{
    /* selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION); // Projecao 2D

    gluOrtho2D(0.0, 600.0, 0.0, 400.0); // Definindo os limites da Porta de Visao (ViewPort)
}

void update_angle()
{
    if (direction)
    {
        angle += rotationSpeed; // Incrementa o ângulo de rotação
        if (angle > 360)
        {
            angle -= 360;
        }
    }
    else
    {
        angle -= rotationSpeed; // Incrementa o ângulo de rotação
        if (angle < 0)
        {
            angle = 360;
        }
    }
}

void update(int value)
{
    if (isRotating)
    {
        update_angle();
    }
    else
    {
        if (stop)
        {
            if (rotationSpeed > 10.0f)
                rotationSpeed -= 0.5f;

            if (rotationSpeed > 2.0f)
                rotationSpeed -= 0.1f;

            if (rotationSpeed > 1.0f)
                rotationSpeed -= 0.01f;

            if (rotationSpeed > 1.0)
                update_angle();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void display(void)
{
    /* Limpar todos os pixels  */
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    /* Palito */
    glColor3f(1.0, 1.0, .0);
    glBegin(GL_POLYGON);
    glVertex3f(249.0f, 250.0f, -1.0f);
    glVertex3f(251.0f, 250.0f, -1.0f);
    glVertex3f(249.0f, 100.0f, -1.0f);
    glVertex3f(251.0f, 100.0f, -1.0f);
    glEnd();

    /* Aplica a rotação
     Coordenadas do ponto fixo (o centro do triângulo) */
    float px = 250.0f;
    float py = 250.0f;

    /* Translada o triângulo para que o ponto fixo fique na origem */
    glTranslatef(px, py, 0.0f);
    /* Rotação */
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    /* Translada de volta para a posição original*/
    glTranslatef(-px, -py, 0.0f);

    /* Desenhar um polígono branco  */
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(250.0f, 250.0f);
    glVertex2f(230.0f, 200.0f);
    glVertex2f(270.0f, 200.0f);
    glEnd();

    /* Desenhar um polígono vermelho */
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(250.0f, 250.0f);
    glVertex2f(300.0f, 230.0f);
    glVertex2f(300.0f, 270.0f);
    glEnd();

    /* Desenhar um polígono verde */
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(250.0f, 250.0f);
    glVertex2f(230.0f, 300.0f);
    glVertex2f(270.0f, 300.0f);
    glEnd();

    /* Desenhar um polígono azul */
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(250.0f, 250.0f);
    glVertex2f(200.0f, 270.0f);
    glVertex2f(200.0f, 230.0f);
    glEnd();

    /* Não esperar! */
    glFlush();

    glPopMatrix();

    glutSwapBuffers();
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p': // 'r' para rodar/parar
        if (!isRotating)
            rotationSpeed = 2.0f;

        stop = !stop;
        isRotating = !isRotating;
        break;

    case 'd': // 'd' mudar direção
        if (isRotating)
            direction = !direction;

        break;
    case '+': // '+' para aumentar a velocidade
        if (isRotating && rotationSpeed < 40.0)
            rotationSpeed += 1.0f;
        break;
    case '-': // '-' para diminuir a velocidade
        if (isRotating && rotationSpeed > 2.0f)
            rotationSpeed -= 1.0f;
        break;
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flor de Abril");

    init();

    glutDisplayFunc(display);

    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    /* C ANSI requer que main retorne um inteiro */
    return 0;
}

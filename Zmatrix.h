#ifndef ZMATRIX_CLASS_H
#define ZMATRIX_CLASS_H
#include<iostream>
#include<iomanip>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Parser.h"
using namespace std;
class Zmatrix {
public:
    float** zmat;
    float* xmat;
    float* ymat;
    //GLuint* indices;
    int sizex;
    int sizey;
    //GLfloat * vertices;
    int numindices;

    Zmatrix(int xn, int yn, GLuint indices[]);

    void evaluate(string postfix);
    void displayXYZ(GLfloat vertices[]);
    void displayIndexArray(GLuint indices[]);
    void createVertexArray(GLfloat vertices[]);
    ~Zmatrix();
};


#endif

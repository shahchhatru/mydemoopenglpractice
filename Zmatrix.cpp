#include"Zmatrix.h"

Zmatrix::Zmatrix(int xn, int yn,GLuint indices[]) {
    sizex = xn;
    sizey = yn;
    zmat = new float* [yn];
    int s = xn * yn;
    xmat = new float[s];
    ymat = new float[s];
    s = s * 6;
    //indices = new GLuint[s];
    //vertices = new GLfloat[s];
    for (int i = 0; i < yn; i++) {
        zmat[i] = new float[xn];
    }
    int k = 0;
    for (int i = 0; i < yn; i++) {

        for (int j = 0; j < xn; j++) {
            zmat[i][j] = 0.0;
            if (i < (sizey - 1) && j < (sizex - 1)) {
                //cout<<indices[k]<<endl;
                *(indices + k) = (10 * i + j);
                k++;
                indices[k] = (10 * i + (j + 1));
                k++;
                indices[k] = (10 * (i + 1) + j);
                k++;
                indices[k] = (10 * (i + 1) + j + 1);
                k++;
                indices[k] = (10 * i + (j + 1));
                k++;
                indices[k] = (10 * (i + 1) + j);
                k++;
                //cout<<"k is"<<k<<endl;
                //cout<<k<<endl;
                numindices = k;
            }
            

        }
    }

}
void Zmatrix::evaluate(string postfix) {

    float y = -0.5;
    float k = 0.1;
    float h = 0.1;
    for (int i = 0; i < sizey; i++) {
        float x = -0.5;
        for (int j = 0; j < sizex; j++) {
            zmat[i][j] = Parser::evaluator(postfix, x, y);
            cout << setw(8) << zmat[i][j];
            xmat[10 * i + j] = x;
            ymat[10 * i + j] = y;
            x += h;

        }
        cout << endl;
        y += k;
    }
}

void Zmatrix::displayIndexArray(GLuint indices[]) {
    int k = 0;
    for (int i = 0; i < (sizex * sizey * 6); i++) {
        k++;
        cout << indices[i] << " ,";
        if (k >= 3) {
            cout << endl;
            k = 0;
        }
    }
}

void Zmatrix::createVertexArray(GLfloat vertices[]) {
    int k = 0;
    for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            vertices[k] =xmat[sizey * i + j];
            k++;
            vertices[k] = ymat[sizey * i + j];
            k++;
            vertices[k] = zmat[i][j];
            k++;
            vertices[k] = 1.0f;//1 - xmat[sizey * i + j];
            k++;
            vertices[k] = 0.0f;//1 - ymat[sizey * i + j];
            k++;
            vertices[k] = 0.0f;//1 - zmat[i][j];
            k++;
        }
    }
}
void Zmatrix::displayXYZ(GLfloat vertices[]) {
    cout << setw(8) << "x" << setw(8) << "y" << setw(8) << "z" << endl;
  /* for (int i = 0; i < sizey; i++) {
        for (int j = 0; j < sizex; j++) {
            cout << setw(8) << xmat[10 * i + j] << setw(8) << ymat[10 * i + j] << setw(8) << zmat[i][j] << endl;
        }

    }*/
    int s = sizex * sizey * 6;
    int k = 0;
    for (int i = 0; i < s; i++) {
        cout << setw(10)<<vertices[i];
        k++;
        if (k >= 6) {
            k = 0;
            cout << endl;
        }
    }
}
Zmatrix::~Zmatrix() {
    for (int i = 0; i < sizey; i++)    //To delete the inner arrays
        delete[] zmat[i];
    delete[] zmat;
    delete[] xmat;
    delete[] ymat;
    //delete[] indices;
    //delete[] vertices;        //To delete the outer array

}
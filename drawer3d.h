#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <GL/gl.h>
#include <d3d8types.h>


// ====================================================
class drawer3D : public QOpenGLWidget {

protected:
    void initializeGL( );
    void resizeGL (int nWidth, int nHeight);
    void paintGL ();
    QSize minimumSizeHint() const;
    //    QSize sizeHint();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public:
    drawer3D(QWidget* pwgt = 0);


public slots:
    void rotate(double x);
    void setXRot(int angle);
    void setYRot(int angle);
    void setZRot(int angle);

private:
    void draw_Axis();
    void draw(QVector<double>xvec,QVector<double>yvec);
    void renderText(D3DVECTOR &textPosWorld, QString text);
    inline project(GLdouble objx, GLdouble objy, GLdouble objz,
                   const GLdouble model[16], const GLdouble proj[16],
    const GLint viewport[4],
    GLdouble * winx, GLdouble * winy, GLdouble * winz);
    inline void transformPoint(GLdouble out[4], const GLdouble m[16], const GLdouble in[4]);
    int xRot;
    int yRot;
    int zRot;
    double zoomScale;
    QPoint lastPos;
};

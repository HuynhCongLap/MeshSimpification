#ifndef GLDISPLAYWIDGET_H
#define GLDISPLAYWIDGET_H

#include <QGLWidget>
#include <QtWidgets>
#include <QTimer>
#include "mesh.h"
#include <QPushButton>
class GLDisplayWidget : public QGLWidget
{
public:
    explicit GLDisplayWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL(); // Display Gl
    void resizeGL(int width, int height);
    bool wireFrame = false;
protected:
    // Mouse Management
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:

    QTimer _timer; // To update the scene
    float _X, _Y ,_Z; // Translation
    float _angle; // Rotation

    QPoint _lastPosMouse; // To keep the last position of the mouse
    QPushButton button;
    Mesh _mesh; // The object to be displayed
};

#endif // GLDISPLAYWIDGET_H

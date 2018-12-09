#include "gldisplaywidget.h"
#include "QDebug"
#include "QVector3D"
#ifdef __APPLE__
    #include <glu.h>
#else
    #include <GL/glu.h>
#endif

#include "QDebug"

GLDisplayWidget::GLDisplayWidget(QWidget *parent) : QGLWidget(parent)
{
    // Update the scene
    connect( &_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    _timer.start(16);
}

void GLDisplayWidget::initializeGL()
{
    // background color
    glClearColor(0, 0, 0, 1);

    // Shader
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    Mesh box(Vertex(-2,-2,0),Vertex(2,-2,0), Vertex(-2,2,0), Vertex(2,2,0));
       _mesh = box;
    _mesh.readPointFromFile("test.off"); // Add point from File

}

void GLDisplayWidget::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Center the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,  0,0,0,   0,1,0);

    // Translation
    glTranslated(_X, _Y, _Z);

    // Rotation
    glRotatef(_angle, 1.0f, 1.0f, 0.0f);

    // Color for your mesh
    glColor3f(0, 1 ,0);

    // example with a tetraedra
   // _mesh.drawTetraedra();

      _mesh.draw();




}

void GLDisplayWidget::resizeGL(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    updateGL();
}

// - - - - - - - - - - - - Mouse Management  - - - - - - - - - - - - - - - -
// When you click, the position of your mouse is saved
void GLDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL )
        _lastPosMouse = event->pos();
        selectPositionAndColorOn3DModel();
}

// Mouse movement management
void GLDisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - _lastPosMouse.x();
    // int dy = event->y() - lastPosMouse.y();

    if( event != NULL )
    {
        _angle += dx;
        _lastPosMouse = event->pos();

        updateGL();
    }
}

// Mouse Management for the zoom
void GLDisplayWidget::wheelEvent(QWheelEvent *event) {
    QPoint numDegrees = event->angleDelta();
    double stepZoom = 0.25;
    if (!numDegrees.isNull())
    {
      _Z = (numDegrees.x() > 0 || numDegrees.y() > 0) ? _Z + stepZoom : _Z - stepZoom;
    }
}

void GLDisplayWidget::selectPositionAndColorOn3DModel() {
    int xMouse = _lastPosMouse.x();
    int yMouse = height() - 1 - _lastPosMouse.y();

    float OnObjectZ;

    unsigned char color[4];
    color[3] = 0;
    glReadPixels(xMouse, yMouse, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, &color[0]);

    if(color[0] != 0 || color[1] != 0 || color[2] != 0)
    {
        glReadPixels(xMouse,yMouse,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&OnObjectZ);
        QVector3D posClickSelected = unproject(xMouse,yMouse,OnObjectZ); // Pos of click
        qDebug() << posClickSelected;

        Vertex insert(posClickSelected.x(),posClickSelected.y(),0);
        _mesh.insertMesh(insert);
        qDebug() << color[0]<< ", " << color[1] << ", "<< color[2]; // Color of face

    }
}

// UnProjection: **Model** => GL_MODELVIEW_MATRIX => **View** => GL_PROJECTION_MATRIX ==> **Projection**
// Return the position on the face
QVector3D GLDisplayWidget::unproject(int X, int Y, float Depth)
{
  std::vector<GLdouble> ModelView(16),Projection(16);
  glGetDoublev(GL_MODELVIEW_MATRIX,&ModelView[0]);
  glGetDoublev(GL_PROJECTION_MATRIX,&Projection[0]);
  std::vector<GLint> Viewport(4);
  glGetIntegerv(GL_VIEWPORT,&Viewport[0]);
  GLdouble x,y,z;
  gluUnProject(X,Y,Depth,&ModelView[0],&Projection[0],&Viewport[0],&x,&y,&z);
  return QVector3D(x,y,z);
}


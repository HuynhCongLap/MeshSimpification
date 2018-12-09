#ifndef MESH_H
#define MESH_H

#include <QGLWidget>
#include <QMap>
#include <QString>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <iterator>
#include <iostream>
#include <qmath.h>
using namespace std;
// TO MODIFY
// Advice => You should create a new file for each module but not necessarily for each class
class Vertex
{

    // Class to be enriched, otherwise it would have been simply named as 3DPoint!!
    double _x;
    double _y;
    double _z;


public:
    Vertex():_x(),_y(),_z() {}
    Vertex(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_) {}
    // get
    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }
};


//** TO MODIFY
class Triangle
{
    Vertex _a;
    Vertex _b;
    Vertex _c;



public:
    Triangle():_a(),_b(),_c() {}
    Triangle(Vertex a_, Vertex b_, Vertex c_):_a(a_),_b(b_),_c(c_) {}
    // get
    Vertex a() const { return _a; }
    Vertex b() const { return _b; }
    Vertex c() const { return _c; }
};

// New class for Vertex and Triangle -> PVertex, Triangle
class PVertex // un sommet
{

    int _vtriangle_index; // keep a index face of this vertex
    double _x;
    double _y;
    double _z;


public:
    PVertex():_x(),_y(),_z(), _vtriangle_index(-1) {}
    PVertex(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_), _vtriangle_index(-1) {}
    // get
    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }

    void setFace(int faceIndex){ _vtriangle_index = faceIndex; }
    int getFace() {return _vtriangle_index; } // return the face index that this vertex belongs to
};


class PTriangle
{

    QVector <int> _vertexIndex;
    QVector <int> _triangleIndex;


public:
    PTriangle(){}

    PTriangle(int a, int b, int c){
        _vertexIndex.push_back(a);
        _vertexIndex.push_back(b);
        _vertexIndex.push_back(c);

        _triangleIndex.push_back(-1);
        _triangleIndex.push_back(-1);
        _triangleIndex.push_back(-1);
    }

    PTriangle(int a, int b, int c, int voisin_one, int voisin_two, int voisin_three){
          _vertexIndex.push_back(a);
          _vertexIndex.push_back(b);
          _vertexIndex.push_back(c);

          _triangleIndex.push_back(voisin_one);
          _triangleIndex.push_back(voisin_two);
          _triangleIndex.push_back(voisin_three);
      }


    // get
    int a() const { return  _vertexIndex[0]; }
    int b() const { return  _vertexIndex[1]; }
    int c() const { return  _vertexIndex[2]; }


    int v1() const { return  _triangleIndex[0]; }
    int v2() const { return  _triangleIndex[1]; }
    int v3() const { return  _triangleIndex[2]; }

    bool testVertex(int i) // check if this face has this vertex inside
    {
                    return _vertexIndex.indexOf(i) != -1;
    }

    void showVoisin()
    {
        //std::cout<<"Voisin: "<< _triangle1Index << " and " << _triangle2Index << " and " << _triangle3Index << std::endl;
    }

    int index_v(int vt)
    {
        return _vertexIndex.indexOf(vt);
    }
    void setV(int index, int vt1, int vt2)
    {
        cout<<"v1:"<<_vertexIndex.indexOf(vt1)<<" v2:"<<_vertexIndex.indexOf(vt2)<<endl;
        cout<<"v3:"<<(_vertexIndex.indexOf(vt1)+_vertexIndex.indexOf(vt2)%3)<<endl;
        _triangleIndex[(_vertexIndex.indexOf(vt1)+_vertexIndex.indexOf(vt2))%3] = index;
    }

    bool haveV(int index)
    {
        return _triangleIndex[0] == index || _triangleIndex[1] == index || _triangleIndex[2] == index;
    }


   /*
    void attachedTriangle(int a, int b, int c) // index attached triangles
    {
        _triangle1Index = a;
        _triangle2Index = b;
        _triangle3Index = c;
    }

    void setVoisin(int attached) // index attached triangles
    {
        if (_triangle1Index == -1)
            _triangle1Index = attached;
        else
            if (_triangle2Index == -1)
                _triangle2Index = attached;
            else
                if (_triangle3Index == -1)
                    _triangle3Index = attached;

    }*/
};

class Edge{
    QVector <int> _vertexIndex;
    float len;

public:
    Edge(){}
        Edge(int v1, int v2, float l){
            _vertexIndex.push_back(v1);
            _vertexIndex.push_back(v2);
            len = l;
        }
        int v1()
        {
            return _vertexIndex[0];
        }

        int v2()
        {
            return _vertexIndex[1];
        }
        float length()
        {
            return len;
        }
};


//** TO MODIFY
class Mesh
{
    int _vertex_number;
    int _face_number;
    int _edge_number;

    QVector<PVertex> _vertexArray;
    QVector<PTriangle> _facesArray;
    QVector<Edge> _edgeArray;
public:

    Mesh();

    // The two following functions could be displaced into a module OpenGLDisplayMesh that would include Mesh
    void drawTetraedra();
    void drawTetraedraWireFrame();
    void readMesh(QString fileName);

    void drawTetrahedron(); // draw a Tetrahedron in new structure
    void drawTetrahedronWireFrame(); // draw a Wire Frame Tetrahedron in new Structure


    void draw(); // Draw the mesh
    void drawWire(); // Draw the mesh in WireFrame
    void init();

    void quickSort(QVector<Edge> & edge_array, int low, int high); // sort edge array
    int partition(QVector<Edge> & edge_array, int low, int high);
    float length(int v1, int v2);

    void test_face()
    {
        cout<<"Test\n";
        bool err = false ;
       /* for(int i=0; i<_facesArray.size(); i++)
        {
            cout<<"Face["<<i<<"]\n";
            if (_facesArray[i].v1() == _facesArray[i].v2() || _facesArray[i].v2() == _facesArray[i].v3() || _facesArray[i].v1() == _facesArray[i].v3())
                err = true;
            if (_facesArray[i].v1() > 96713 || _facesArray[i].v2() > 96713 || _facesArray[i].v3() > 96713)
                err = true;
            if (_facesArray[i].v1() < 0 || _facesArray[i].v2() < 0 || _facesArray[i].v3() < 0)
                err = true;
            if (_facesArray[i].v1() == -1 || _facesArray[i].v2() == -1 || _facesArray[i].v3() == -1)
                err= true;

            cout<<"v1: "<<_facesArray[i].v1()<<" v2: "<<_facesArray[i].v2()<<" v3: "<<_facesArray[i].v3()<<endl;
        }*/

         for(int i=0; i<_facesArray.size(); i++)
         {
            if(!_facesArray[_facesArray[i].v1()].haveV(i) || !_facesArray[_facesArray[i].v2()].haveV(i) || !_facesArray[_facesArray[i].v3()].haveV(i))
                err = true;
            else
            {
                cout<<"It's okay !"<<endl;
            }
         }


        if(err)
            cout<<"Test is not fine"<<endl;
        else
            cout<<"Test is fine"<<endl;
    }

    bool wireFrameMode = false;


};

#endif // MESH_H

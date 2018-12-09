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

    int _vertex1Index, _vertex2Index, _vertex3Index;
    int _triangle1Index, _triangle2Index,_triangle3Index;


public:
    PTriangle():_vertex1Index(),_vertex2Index(),_vertex3Index(),_triangle1Index(-1),_triangle2Index(-1),_triangle3Index(-1){}

    PTriangle(int a, int b, int c){
        _vertex1Index = a;
        _vertex2Index = b;
        _vertex3Index = c;

        _triangle1Index = -1;
        _triangle2Index = -1;
        _triangle3Index = -1;
    }
    // get
    int a() const { return  _vertex1Index; }
    int b() const { return  _vertex2Index; }
    int c() const { return  _vertex3Index; }


    int voisin1() const { return  _triangle1Index; }
    int voisin2() const { return  _triangle2Index; }
    int voisin3() const { return  _triangle3Index; }

    bool testVertex(int i) // check if this face has this vertex inside
    {
        return (_vertex1Index == i || _vertex2Index==i || _vertex3Index==i);
    }

    void showVoisin()
    {
        std::cout<<"Voisin: "<< _triangle1Index << " and " << _triangle2Index << " and " << _triangle3Index << std::endl;
    }


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

    }
};

// Tp 2 Iterator

class Iterator_on_vertices
{
  PVertex* p;
public:
  Iterator_on_vertices():p(NULL){}
  Iterator_on_vertices(PVertex* x) :p(x) {}
  Iterator_on_vertices(const Iterator_on_vertices& mit) : p(mit.p) {}
  Iterator_on_vertices& operator++() {++p;return *this;}
  Iterator_on_vertices operator++(int) {Iterator_on_vertices tmp(*this); operator++(); return tmp;}
  bool operator==(const Iterator_on_vertices& rhs) const {return p==rhs.p;}
  bool operator!=(const Iterator_on_vertices& rhs) const {return p!=rhs.p;}

  Iterator_on_vertices& operator=(const Iterator_on_vertices& rhs) {
     this->p = rhs.p;
      return *this;
  }
  PVertex& operator*() {return *p;}


};


class Iterator_on_faces
{
  PTriangle* p;
public:
  Iterator_on_faces(): p(NULL){}
  Iterator_on_faces(PTriangle* x) :p(x) {}
  Iterator_on_faces(const Iterator_on_faces& mit) : p(mit.p) {}
  Iterator_on_faces& operator++() {++p;return *this;}
  Iterator_on_faces operator++(int) {Iterator_on_faces tmp(*this); operator++(); return tmp;}
  bool operator==(const Iterator_on_faces& rhs) const {return p==rhs.p;}
  bool operator!=(const Iterator_on_faces& rhs) const {return p!=rhs.p;}

  Iterator_on_faces& operator=(const Iterator_on_faces& rhs) {
     this->p = rhs.p;
      return *this;
  }
  PTriangle& operator*() {return *p;}
};




class Circulator_on_faces
{
    PTriangle* m_f;

    int v_index;
    int f_index;

    PTriangle* previous;
  public:
    Circulator_on_faces(): m_f(NULL), v_index(-1), f_index(-1), previous(NULL){}
    Circulator_on_faces(PTriangle* f, int v_in, int f_in) :m_f(f), v_index(v_in),f_index(f_in), previous(NULL){}
    Circulator_on_faces(const Circulator_on_faces& mit) : m_f(mit.m_f), v_index(mit.v_index), f_index(mit.f_index), previous(mit.previous) {}

    Circulator_on_faces& operator++()
    {
       int step1 = 0;
       int step2 = 0;
       int step3 = 0;
       step1 = m_f->voisin1() - f_index;
       step2 = m_f->voisin2() - f_index;
       step3 = m_f->voisin3() - f_index;
       PTriangle* keeper = m_f + step1;
       if(keeper->testVertex(v_index) && keeper != previous)
       {
           previous = m_f;
           f_index = m_f->voisin1();
           m_f = keeper;
           return *this;
       }
       else
       {
           keeper = m_f + step2;
           if(keeper->testVertex(v_index) && keeper != previous)
           {
               previous = m_f;
               f_index = m_f->voisin2();
               m_f = keeper;
               return *this;
           }
           else
           {
               keeper = m_f + step3;
               if(keeper->testVertex(v_index) && keeper != previous)
               {
                   previous = m_f;
                   f_index = m_f->voisin3();
                   m_f = keeper;


                   return *this;
               }
               else
                   return *this;
           }
       }

    }
    Circulator_on_faces operator++(int) {Circulator_on_faces tmp(*this); operator++(); return tmp;}

    bool operator!=(const Circulator_on_faces& rhs) const {return this->m_f != rhs.m_f;}

    Circulator_on_faces& operator=(const Circulator_on_faces& rhs) {
        this->m_f = rhs.m_f;
        this->f_index = rhs.f_index;
        this->v_index = rhs.v_index;
        return *this;
    }
    PTriangle& operator*() {return *m_f;}
};



class Circulator_on_vertices
{
    PVertex* m_v;
    Circulator_on_faces *m_it;
    int v_index;


  public:
    Circulator_on_vertices(): m_v(NULL), v_index(-1), m_it(NULL){}
    Circulator_on_vertices(PVertex* v, int v_in, Circulator_on_faces *it) :m_v(v), v_index(v_in), m_it(it) {}
    //Circulator_on_faces(const Circulator_on_faces& mit) : p(mit.p), v(mit.v), f_index(mit.f_index), _mesh(mit._mesh) {}

    Circulator_on_vertices& operator++()
    {

       std::cout<<"-----Debug------"<<std::endl;
       Circulator_on_faces m_it2(*m_it);
       m_it2++;
        if((*(*m_it)).a() != v_index && (*m_it2).testVertex((*(*m_it)).a()))
        {


            int step = (*(*m_it)).a() - v_index;

            m_v += step;


            (*m_it)++;
            return *this;
        }
        else
        if((*(*m_it)).b() != v_index && (*m_it2).testVertex((*(*m_it)).b()))
        {

            int step = (*(*m_it)).b() - v_index;

            m_v += step;

            (*m_it)++;
            return *this;
        }
        else
        if((*(*m_it)).c() != v_index && (*m_it2).testVertex((*(*m_it)).c()))
        {

            int step = (*(*m_it)).c() - v_index;

            m_v += step;

            (*m_it)++;
            return *this;
        }
        else
            return *this;

        std::cout<<"--------"<<std::endl;

    }
    Circulator_on_vertices operator++(int) {Circulator_on_vertices tmp(*this); operator++(); return tmp;}


    Circulator_on_vertices& operator=(const Circulator_on_vertices& rhs) {
        m_v = rhs.m_v;
        m_it = rhs.m_it;
        v_index = rhs.v_index;
        return *this;
    }
    PVertex& operator*() {return *m_v;}
};


//** TO MODIFY
class Mesh
{
    int _vertex_number;
    int _face_number;
    int _edge_number;

    QVector<PVertex> _vertexArray;
    QVector<PTriangle> _facesArray;
public:

    Mesh();
    //------ Iterator begin() and end() functions
    PTriangle* getTriangle(int i){ return &_facesArray[i];}

    Iterator_on_vertices vertices_begin(){
            return Iterator_on_vertices(&_vertexArray[0]);
   }

    Iterator_on_vertices vertices_past_the_end(){
       return Iterator_on_vertices(&_vertexArray[_vertexArray.size()-1]);
    }

    Iterator_on_faces face_begin(){
        return Iterator_on_faces(&_facesArray[0]);
    }

    Iterator_on_faces faces_past_the_end(){
        return Iterator_on_faces(&_facesArray[_facesArray.size()-1]);
    }


    Circulator_on_faces incident_faces(int v_index){
        return Circulator_on_faces(&_facesArray[_vertexArray[ v_index].getFace()], v_index, _vertexArray[v_index].getFace());
    }

    Circulator_on_vertices adjacent_vertices(int v_index){
        Circulator_on_faces f(&_facesArray[_vertexArray[ v_index].getFace()], v_index, _vertexArray[v_index].getFace());
        return Circulator_on_vertices(&_vertexArray[v_index],v_index,&f);
    }


 // to check Tp2
    void litteMain(){

        Iterator_on_vertices its;
        Circulator_on_faces cf ;
         std::cout << "----Little Main Tp2 Test verticles interator----" << std:: endl;
        int i =0;
         for (its=vertices_begin(); its !=vertices_past_the_end(); its++)
        {
            std::cout<< "Verticle:" <<(*its).x() << " " <<  (*its).y() << " " <<  (*its).z()  ;
            std::cout<<"   Face index of this verticle: "<<(*its).getFace()<<std::endl;


            Circulator_on_faces cfbegin = incident_faces(i) ;
             int cmpt=0 ;
             for (cf=cfbegin,++cf; cf!=cfbegin; cf++)
                 cmpt++ ;
             std ::cout<< "valence of the vertex: "   << cmpt <<std ::endl ;
               i++;
         }
            std::cout<<"Verticle: " <<(*its).x() << " " <<  (*its).y() << " " <<  (*its).z()  ;
            std::cout<<"   Face index of of this verticle: "<<(*its).getFace() << std::endl;
            std::cout << "-------" << std:: endl;

//-------------------------------------------------------------------
         Iterator_on_faces its2;
         std::cout << "----Little Main Tp2 Test face interator----" << std:: endl;
         for (its2=face_begin(); its2 !=faces_past_the_end(); its2++)
        {
            std::cout<< "Face Triangles Index: "<< (*its2).a() << " " <<  (*its2).b() << " " <<  (*its2).c() << std::endl ;
            (*its2).showVoisin();
        }
            std::cout<< "Face Triangles Index:: "<<(*its2).a() << " " <<  (*its2).b() << " " <<  (*its2).c() << std::endl ;
            (*its2).showVoisin();
            std::cout << "-------" << std:: endl;



    }

    //------------------------------------------------------






    // The two following functions could be displaced into a module OpenGLDisplayMesh that would include Mesh
    void drawTetraedra();
    void drawTetraedraWireFrame();
    void readMesh(QString fileName);

    void drawTetrahedron(); // draw a Tetrahedron in new structure
    void drawTetrahedronWireFrame(); // draw a Wire Frame Tetrahedron in new Structure
    void drawPyramid(); //draw a Pyramid with a square base
    void draw2DBoudingBox(); // draw a 2D bouding box


};

#endif // MESH_H

HUYNH Cong Lap - 1452019
Travail seul

TP2 – Iterators on a triangulated surface data structure

My work implemented:

Iterator_on_faces class:
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

class Mesh
{
   ....
    QVector<PVertex> _vertexArray;
    QVector<PTriangle> _facesArray;
    ....
}

This iterator keeps pointer* P Triangle to point to an element of vector _faceArray of class Mesh
Mesh class provides :

 Iterator_on_faces face_begin(){
      return Iterator_on_faces(&_facesArray[0]);
  }

  Iterator_on_faces faces_past_the_end(){
      return Iterator_on_faces(&_facesArray[_facesArray.size()-1]);
  }
Then we can use operator ++ to traverse through the _facesArray
operator  *  to return a reference on the current face
-------------------------------------------------------------

Iterator_on_vertices class:
This class is the almost the same with Iterator_on_faces class

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
Just change the atribute Ptriangle to Pvertex.
Like Iterator_on_faces class, class Mesh provide vertices_begin(),
vertices_past_the_end() to traverse the _vertexArray vector of mesh

------------------------------------------------------------------
Circulator_on_faces class:
This class has an atribute PTriangle* to keep the current face it points to.
atribute v_index to keep the vertex that faces turn around
atribute f_index to keep the index of current face
atribute previous to keep the previous faces

Circulator_on_faces incident_faces(int v_index){
    return Circulator_on_faces(&_facesArray[_vertexArray[ v_index].getFace()], v_index, _vertexArray[v_index].getFace());
}
Mesh class provide a function to get a vertex Index and return a Circulator_on_faces that is pointing to the face, which belongs to this vertex by _vtriangle_index
This face will be initiation.

Then we find a neighbours in 3 of this face that has Vertex[v_index] too
Then we save the atribute previous by current face and switch to new neighbours.
Do the same with next face, the previous atribute is to avoid we come back to last face we've gone througt.
By this way, we can traverse around a vertex in faces like a circle.

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

-------------------------------------------------------------

Circulator_on_vertices class:
This class has 3 atributes:
PVertex* m_v : point to the current Vertex
Circulator_on_faces *m_it: to traverse faces around the first vertex
v_index: keep the index initial vertex.

The idea is: adjacent vertices of a vertex is lying on the faces around that vertex.
By the Circulator_on_faces we will traverse around that vertex by faces, and then posible to traverse by vertices.

First we find the initial face that belongs to initial vertex
and surely, others verticles of this face is adjacent initial vertex.
chose one, and go to the next face, and do the same thing.


Circulator_on_vertices adjacent_vertices(int v_index){
    Circulator_on_faces f(&_facesArray[_vertexArray[ v_index].getFace()], v_index, _vertexArray[v_index].getFace());
    return Circulator_on_vertices(&_vertexArray[v_index],v_index,&f);
}


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

HUYNH Cong Lap - 1452019
Travail seul
 
TP1 – Getting started with QT Creator, Meshes and Data Structures

My work implemented:

1. Enrich the triangulated mesh data structure
I have created 2 mores class Pvertex and PTriangle and modified the
class Mesh to change the data structure

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

A Pvertex got 4 atributes, x,y,z is simple the position of the Vertex
and _vtriangle_index is one of the face this vertex belongs to




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

    .....more functions....
}

A class Triangle now has 3 index of 3 verticles
And 3 index of 3 neighborhoods. that means for a triangle, we can know
3 others triangles that are its neighborhoods


class Mesh
{
    int _vertex_number;
    int _face_number;
    int _edge_number;

    QVector<PVertex> _vertexArray;
    QVector<PTriangle> _facesArray;

    ....more functions...
}



A Mesh now keeps 1 vector of all verticles, and 1 vector of all face from these verticlies.
Besides, they keep 3 attributes to know how many verticles, faces, edge it has.
-----------------------------------------------
2. Modeling of elementary meshes to test your data structure
Some functions to paints some basic models with the new data Structure

void drawTetrahedron();
void drawTetrahedronWireFrame();
.... 

---------------------------------------------------------
3.Write a routine to read and load, in your data structure, a triangulated
mesh written in an OFF file

Function to load mesh from file - Mesh::readMesh(QString fileName)

This function read a text file .off. Line by line
At first, it reads the first line to save the number of verticles, faces, edges into Mesh structure.
Then it reads line by line, and save the position of each vertex into the vertex array of Mesh.
Finally, it reads line by line, and save faces into the face array of Mesh.

And how to save the information of attached Faces ????

One Edge is shared by 2 faces
In the processus of reading face, it will use a Map to store an edges by the value of first Face.
For exemple:
  Map(EdgeAB) = 1; this means Face[1] has this Edges

  Then if the second face has EdgeAB, they are neighbours.
  We save this information into these faces.

If there is no file, it will show "can not find document"


----------------------------------------------------------------

function init()
This function will initiate a Mesh with verticles and faces, that means loading the mesh by hand

function draw()
This function will draw that coloful mesh into screen, no matter how the mesh is.

function drawWire
Like draw, but draw in wireframe mode

Now you can load any Mesh from file .off by readMesh(), And simply draw it by function Draw() or DrawWire()
-----------------------------------------------------------------
4. Set up a menu with some buttons to change the display mode

I have created 2 button Exit and WireFrame
Exit: to exit the application
WireFrame: to turn on the wireFrame mode.

I have attached the signal released() of wireFrame button, to a bool variable to turn it on
if we click it and release

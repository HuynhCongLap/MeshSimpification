HUYNH Cong Lap - 1452019
Travail seul

TP3 – Split one face into three, Naive incremental triangulation

My work implemented:

Provide a function to test if a 2D point is within a 2D triangle.

float sign (Vertex p1, Vertex p2, Vertex p3)
{
    return (p1.x() - p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y());
}

bool PointInTriangle (Vertex pt, Vertex v1, Vertex v2, Vertex v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

These functions use the idea that the 3 edges are visible by a point which is located inside a triangle.

-----------------------------------------------------------
a function to split one face of a triangulation into 3. The integrity of the Mesh will be recovered after that operation


bool testVoisin(Triangle one, Triangle two)
{

}
This function will check if these triangles are neighbours


bool splitMesh(Vertex pt, int n)
{
  //.................code......................
}


This function will split the triangle index n into 3 triangles by the vertex PT

Idea: check vertex inside Triangle, if false do nothing
in case true, we create 3 new triangles, one of them will replace the triangle[n], others will insert to _facesArray, that means now, we got 3 new triangles with index: n, _facesArray.size(), _facesArray.size()+1
Then we will recover the mesh, by setting neighbours for each new triangles, and the neighbours triangles of Triangle index n


--------------------------------------------------
Enrich  Mesh data structure with a constructor that will initialize a Mesh with the 4 points of a 2D bounding box and a fictitious infinite vertex.

Mesh(Vertex one, Vertex two, Vertex three, Vertex four) // constuctor bouding box with 2 vertex
{
    _vertexArray.push_back(one);
    _vertexArray.push_back(two);
    _vertexArray.push_back(three);
    _vertexArray.push_back(four);

    Triangle first(0,1,2);
    Triangle second(1,2,3);

    first.setVoisin(1); // set voisin index by 1 = second
    second.setVoisin(0); // set voisin index by 0 = first
    _facesArray.push_back(first);
    _facesArray.push_back(second);
}


we push new verticles, and face to Mesh's Array (_facesArray, _vertexArray). then Set neighbours for them


--------------------------------------------------------------
Enrich  Mesh data structure with a function that will insert a point P into a 2D triangulation (P should be within some given bounding box integrated into the mesh).

void insertMesh(Vertex pt)
{
    int i = 0;
    while (!splitMesh(pt,i))
    {
        i++;
    }

 }

I provide a function: void insertMesh(Vertex pt)
Using function splitMesh() above, whenever i click on the screen, they will get the coordinator of mouse position. If the coordinator is inside the bouding box, we add this point into Mesh, and new three triangles will appear

The idea is, insertMesh will check all the faces of Mesh, if there is one face contain this Vertex -> splitMesh this faces into 3
-------------------------------------------------------------

 Enrich Mesh data structure with a function that will incrementally insert a set of 2D points read from a file (we will assume that this set of points does not contain 3 aligned points) in a triangulation initialized to a bounding box.

This function will read point from the File,and use insertMesh above to add it into the Mesh
A test file named: test.off
containing some verticles inside, it will read this file and insert them into the bouding box.

 void Mesh::readPointFromFile(QString fileName)
 {
     QFile inputFile(fileName);
         inputFile.open(QIODevice::ReadOnly);
         if (!inputFile.isOpen()){
             std::cout << "Can't not find documents" << std::endl;
             return;
          }

         QTextStream stream(&inputFile);
         QString line = stream.readLine();

         QString numStr;

         while (!line.isNull()) {

                line = stream.readLine();
                if(line.split(" ", QString::SkipEmptyParts).count() == 3)
                {
                    // read vertex
                    float a = line.split(" ", QString::SkipEmptyParts)[0].toFloat();
                    float b = line.split(" ", QString::SkipEmptyParts)[1].toFloat();
                    float c = line.split(" ", QString::SkipEmptyParts)[2].toFloat();
                    insertMesh(Vertex(a,b,c));

                }
         }
 }

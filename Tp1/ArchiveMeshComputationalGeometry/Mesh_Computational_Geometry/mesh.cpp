#include "mesh.h"
#include <iostream>
#include <algorithm>
#include <string>

Mesh::Mesh()
{

}

double randd() {
  return (double)rand() / (RAND_MAX + 1.0);
}

// The following functions could be displaced into a module OpenGLDisplayMesh that would include Mesh
// Draw a vertex
void glVertexDraw(Vertex vertex) {
    glVertex3f(vertex.x(), vertex.y(), vertex.z());
}

void glPVertexDraw(PVertex vertex) {
    glVertex3f(vertex.x(), vertex.y(), vertex.z());
}

//Example with a tetraedra
void Mesh::drawTetraedra() {

    QVector<Vertex> vertexTab;
    vertexTab.push_back(Vertex(-0.5,-0.5,-0.5)); //0
    vertexTab.push_back(Vertex(0.5,-0.5,-0.5)); // 1
    vertexTab.push_back(Vertex(0,0.5,-0.5)); // 2
    vertexTab.push_back(Vertex(0,-0.5,0.5)); // 3

    int faces[12]={
        0,1,2, // 1
        1,3,2, // 2
        3,0,2, // 3
        0,1,3  // 4
    };

    for(int i = 0; i < 12; i+=3) {

        if (i < 3) glColor3d(1,0,0);
        else if (i < 6) glColor3d(0,1,0);
        else if (i < 9) glColor3d(0,0,1);
        else glColor3d(1,1,0);

        glBegin(GL_TRIANGLES);
        glVertexDraw(vertexTab[faces[i]]);
        glVertexDraw(vertexTab[faces[i+1]]);
        glVertexDraw(vertexTab[faces[i+2]]);
        glEnd();
    }


}

//Example with a wireframe tedraedra
void Mesh::drawTetraedraWireFrame() {
    QVector<Vertex> vertexTab;
    vertexTab.push_back(Vertex(-0.5,-0.5,-0.5)); //0
    vertexTab.push_back(Vertex(0.5,-0.5,-0.5)); // 1
    vertexTab.push_back(Vertex(0,0.5,-0.5)); // 2
    vertexTab.push_back(Vertex(0,-0.5,0.5)); // 3

    int faces[12]={
        0,1,2, // 1
        1,3,2, // 2
        3,0,2, // 3
        0,1,3  // 4
    };

    for(int i = 0; i < 12; i+=3) {
        glBegin(GL_LINE_STRIP);
            glVertexDraw(vertexTab[faces[i]]);
            glVertexDraw(vertexTab[faces[i+1]]);
        glEnd();
        glBegin(GL_LINE_STRIP);
            glVertexDraw(vertexTab[faces[i+1]]);
            glVertexDraw(vertexTab[faces[i+2]]);
        glEnd();
        glBegin(GL_LINE_STRIP);
            glVertexDraw(vertexTab[faces[i+2]]);
            glVertexDraw(vertexTab[faces[i]]);
        glEnd();
    }

}
//------------------------------------------------------------------
//Example with a Tetrahedron in new structure
void Mesh::drawTetrahedron() {



}

void Mesh::init()
{


}

void Mesh::draw()
{
    for(int i = 0; i < _face_number; i++) {

        glColor3d(randd(),randd(),randd());
        glBegin(GL_TRIANGLES);
        glPVertexDraw(_vertexArray[_facesArray[i].a()]);
        glPVertexDraw(_vertexArray[_facesArray[i].b()]);
        glPVertexDraw(_vertexArray[_facesArray[i].c()]);
        glEnd();
    }
}

void Mesh::drawWire()
{

    for(int i = 0; i < _face_number; i++) {
            glBegin(GL_LINE_STRIP);
            glColor3d(1,0,0);
            glPVertexDraw(_vertexArray[_facesArray[i].a()]);
            glPVertexDraw(_vertexArray[_facesArray[i].b()]);
            glPVertexDraw(_vertexArray[_facesArray[i].c()]);
            glPVertexDraw(_vertexArray[_facesArray[i].a()]);
            glEnd();
    }


}



//Example with a wireframe Tetrahedron in new structure
void Mesh::drawTetrahedronWireFrame() {



}

QString sortString(int a, int b)
{
        return QVariant(a).toString() + "-" + QVariant(b).toString();
}

void  Mesh::readMesh(QString fileName)
{
    QFile inputFile(fileName);
    inputFile.open(QIODevice::ReadOnly);
    if (!inputFile.isOpen()){
        std::cout << "Can't not find documents" << std::endl;
        return;
     }

    QTextStream stream(&inputFile);
    QString line = stream.readLine();
    std::cout << line.toStdString() << std::endl;

   QString numStr;
   _vertex_number = line.split(" ", QString::SkipEmptyParts)[0].toInt();
   _face_number = line.split(" ", QString::SkipEmptyParts)[1].toInt();
   _edge_number = line.split(" ", QString::SkipEmptyParts)[2].toInt();


    QMap <QString, int > Edges;
    int countFace = 0;

    while (!line.isNull()) {
        line = stream.readLine();
        if(line.split(" ", QString::SkipEmptyParts).count() == 3)
        {
            std::cout << "vertex\n" << std::endl;
            // read vertex
            float a = line.split(" ", QString::SkipEmptyParts)[0].toFloat();
            float b = line.split(" ", QString::SkipEmptyParts)[1].toFloat();
            float c = line.split(" ", QString::SkipEmptyParts)[2].toFloat();
            _vertexArray.push_back(PVertex(a,b,c));

        }
        else
            if(line.split(" ", QString::SkipEmptyParts).count() == 4)
            {
                std::cout << "face\n" << std::endl;
                // read faces
                int a = line.split(" ", QString::SkipEmptyParts)[1].toInt();
                int b = line.split(" ", QString::SkipEmptyParts)[2].toInt();
                int c = line.split(" ", QString::SkipEmptyParts)[3].toInt();
                //--------------------------


                if(_vertexArray[a].getFace() == -1)
                    _vertexArray[a].setFace(countFace);
                if(_vertexArray[b].getFace() == -1)
                    _vertexArray[b].setFace(countFace);
                if(_vertexArray[c].getFace() == -1)
                    _vertexArray[c].setFace(countFace);


                _facesArray.push_back(PTriangle(a,b,c));


                if(Edges.count(sortString(a,b)) > 0 || Edges.count(sortString(b,a)) > 0){
                    std::cout<<"------My debug---------"<<std::endl;
                    std::cout<<"face sort: "<<Edges[sortString(a,b)]<<std::endl;
                    _facesArray[Edges[sortString(a,b)]].setV(countFace,a,b);
                    std::cout<<"face count: "<<countFace<<std::endl;
                    _facesArray[countFace].setV(Edges[sortString(a,b)],a,b);
                    std::cout<<"------My debug---------"<<std::endl;
                }
                else
                {

                    Edges[sortString(a,b)] = countFace;
                    Edges[sortString(b,a)] = countFace;
                    _edgeArray.push_back(Edge(a,b,length(a,b)));
                }

                    //
                if(Edges.count(sortString(b,c)) > 0 || Edges.count(sortString(c,b)) > 0){
                     std::cout<<"------My debug---------"<<std::endl;
                     std::cout<<"face sort: "<<Edges[sortString(b,c)]<<std::endl;
                    _facesArray[Edges[sortString(b,c)]].setV(countFace,b,c);

                    std::cout<<"face count: "<<countFace<<std::endl;
                    _facesArray[countFace].setV(Edges[sortString(b,c)],b,c);
                     std::cout<<"------My debug---------"<<std::endl;
                }
                else
                {

                    Edges[sortString(b,c)] = countFace;
                    Edges[sortString(c,b)] = countFace;
                    _edgeArray.push_back(Edge(b,c,length(b,c)));
                }

                if(Edges.count(sortString(c,a)) > 0 || Edges.count(sortString(a,c)) > 0){
                     std::cout<<"------My debug---------"<<std::endl;
                     std::cout<<"face sort: "<<Edges[sortString(c,a)]<<std::endl;
                     _facesArray[Edges[sortString(c,a)]].setV(countFace,c,a);
                     std::cout<<"face count: "<<countFace<<std::endl;
                     _facesArray[countFace].setV(Edges[sortString(c,a)],c,a);
                      std::cout<<"------My debug---------"<<std::endl;
                   }
                 else
                {

                     Edges[sortString(c,a)] = countFace;
                     Edges[sortString(a,c)] = countFace;
                     _edgeArray.push_back(Edge(c,a,length(c,a)));
                }


                countFace++;

            }

    };

    quickSort(_edgeArray,0,_edgeArray.size()-1);

    for(int i=0; i<_edgeArray.size(); i++)
    {
        cout<<_edgeArray[i].length()<<" < ";
    }
    cout<<endl;
}
float Mesh::length(int v1, int v2)
{
    float x1 = _vertexArray[v1].x();
    float x2 = _vertexArray[v2].x();
    float y1 = _vertexArray[v1].y();
    float y2 = _vertexArray[v2].y();
    float z1 = _vertexArray[v1].z();
    float z2 = _vertexArray[v2].z();

    return qSqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2) );

}
void Mesh::quickSort(QVector<Edge> & edge_array, int low, int high)
{
    if (low < high)
        {
            /* pi is partitioning index, arr[p] is now
               at right place */
            int pi = partition(edge_array, low, high);

            // Separately sort elements before
            // partition and after partition
            quickSort(edge_array, low, pi - 1);
            quickSort(edge_array, pi + 1, high);
        }
}
int Mesh::partition(QVector<Edge> & edge_array, int low, int high)
{
    float pivot = edge_array[high].length();    // pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j <= high- 1; j++)
        {
            // If current element is smaller than or
            // equal to pivot
            if (edge_array[j].length() > pivot)
            {
                i++;    // increment index of smaller element
                Edge arr_i = edge_array[i];
                edge_array[i] =  edge_array[j];
                edge_array[j] =  arr_i;
            }
        }
        Edge arr_i1 = edge_array[i+1];
        edge_array[i+1] =  edge_array[high];
        edge_array[high] =  arr_i1;

        return (i + 1);
}


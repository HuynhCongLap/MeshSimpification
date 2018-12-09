#include "mesh.h"
#include <iostream>
#include <algorithm>
#include <string>

Mesh::Mesh()
{

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
    _vertex_number = 4; // load vertex number
    _face_number = 4; // load faces number
    _edge_number = 6; // load edges number

    _vertexArray.push_back(PVertex(-0.5,-0.5,-0.5)); //0
    _vertexArray.push_back(PVertex(0.5,-0.5,-0.5)); // 1
    _vertexArray.push_back(PVertex(0,0.5,-0.5)); // 2
    _vertexArray.push_back(PVertex(0,-0.5,0.5)); // 3

    _facesArray.push_back(PTriangle(0,1,2)); //0
    _facesArray.push_back(PTriangle(1,3,2)); // 1
    _facesArray.push_back(PTriangle(3,0,2)); // 2
    _facesArray.push_back(PTriangle(0,1,3)); // 3

    _facesArray[0].attachedTriangle(1,2,3);
    _facesArray[1].attachedTriangle(0,2,3);
    _facesArray[2].attachedTriangle(0,1,3);
    _facesArray[3].attachedTriangle(0,1,2);


    for(int i = 0; i < _face_number; i++) {

        if (i == 0) glColor3d(1,0,0);
        else if (i == 1) glColor3d(0,1,0);
        else if (i == 2) glColor3d(0,0,1);
        else glColor3d(1,1,0);
        glBegin(GL_TRIANGLES);
        glPVertexDraw(_vertexArray[_facesArray[i].a()]);
        glPVertexDraw(_vertexArray[_facesArray[i].b()]);
        glPVertexDraw(_vertexArray[_facesArray[i].c()]);
        glEnd();
    }


}


//Example with a wireframe Tetrahedron in new structure
void Mesh::drawTetrahedronWireFrame() {
    _vertex_number = 4;
    _face_number = 4;
    _edge_number = 6;

    _vertexArray.push_back(PVertex(-0.5,-0.5,-0.5)); //0
    _vertexArray.push_back(PVertex(0.5,-0.5,-0.5)); // 1
    _vertexArray.push_back(PVertex(0,0.5,-0.5)); // 2
    _vertexArray.push_back(PVertex(0,-0.5,0.5)); // 3

    _facesArray.push_back(PTriangle(0,1,2)); //0
    _facesArray.push_back(PTriangle(1,3,2)); // 1
    _facesArray.push_back(PTriangle(3,0,2)); // 2
    _facesArray.push_back(PTriangle(0,1,3)); // 3

    _facesArray[0].attachedTriangle(1,2,3);
    _facesArray[1].attachedTriangle(0,2,3);
    _facesArray[2].attachedTriangle(0,1,3);
    _facesArray[3].attachedTriangle(0,1,2);



    for(int i = 0; i < _face_number; i++) {

        if (i == 0) glColor3d(1,0,0);
        else if (i == 1) glColor3d(0,1,0);
        else if (i == 2) glColor3d(0,0,1);
        else glColor3d(1,1,0);

        glBegin(GL_LINE_STRIP);
            glPVertexDraw(_vertexArray[_facesArray[i].a()]);
            glPVertexDraw(_vertexArray[_facesArray[i].b()]);
        glEnd();
        glBegin(GL_LINE_STRIP);
            glPVertexDraw(_vertexArray[_facesArray[i].b()]);
            glPVertexDraw(_vertexArray[_facesArray[i].c()]);
        glEnd();
        glBegin(GL_LINE_STRIP);
            glPVertexDraw(_vertexArray[_facesArray[i].c()]);
            glPVertexDraw(_vertexArray[_facesArray[i].b()]);
        glEnd();
    }


    for(int i = 0; i < 4; i++) {

        if (i == 0) glColor3d(1,0,0);
        else if (i == 1) glColor3d(0,1,0);
        else if (i == 2) glColor3d(0,0,1);
        else glColor3d(1,1,0);
        glBegin(GL_TRIANGLES);
        glPVertexDraw(_vertexArray[_facesArray[i].a()]);
        glPVertexDraw(_vertexArray[_facesArray[i].b()]);
        glPVertexDraw(_vertexArray[_facesArray[i].c()]);
        glEnd();
    }


}

QString sortString(int a, int b)
{
    if (a < b)
        return QVariant(a).toString() + "-" + QVariant(b).toString();
    else
        return QVariant(b).toString() + "-"+ QVariant(a).toString();
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
    int countFace = 1;


    int countDebug = 0;
    while (!line.isNull()) {

        line = stream.readLine();
        if(line.split(" ", QString::SkipEmptyParts).count() == 3)
        {
            // read vertex
            float a = line.split(" ", QString::SkipEmptyParts)[0].toFloat();
            float b = line.split(" ", QString::SkipEmptyParts)[1].toFloat();
            float c = line.split(" ", QString::SkipEmptyParts)[2].toFloat();
            _vertexArray.push_back(PVertex(a,b,c));

        }
        else
            if(line.split(" ", QString::SkipEmptyParts).count() == 4)
            {
                // read faces
                int a = line.split(" ", QString::SkipEmptyParts)[1].toInt();
                int b = line.split(" ", QString::SkipEmptyParts)[2].toInt();
                int c = line.split(" ", QString::SkipEmptyParts)[3].toInt();
                //--------------------------


                if(_vertexArray[a].getFace() == -1)
                    _vertexArray[a].setFace(countFace-1);
                if(_vertexArray[b].getFace() == -1)
                    _vertexArray[b].setFace(countFace-1);
                if(_vertexArray[c].getFace() == -1)
                    _vertexArray[c].setFace(countFace-1);

                std::cout<< "debug: " << a<<b <<c << std::endl;
                _facesArray.push_back(PTriangle(a,b,c));

                // Test attached faces


                if(Edges.count(sortString(a,b)) > 0){
                     countDebug++;
                     std::cout<<"------My debug---------"<<std::endl;

                     std::cout<<Edges[sortString(a,b)]<<std::endl;
                     std::cout<<countFace -1 <<std::endl;

                    _facesArray[Edges[sortString(a,b)]].setVoisin(countFace-1);
                    _facesArray[countFace-1].setVoisin(Edges[sortString(a,b)]);
                    _facesArray[Edges[sortString(a,b)]].showVoisin();
                    _facesArray[countFace-1].showVoisin();
                    std::cout<<"------My debug---------"<<std::endl;
                }
                else
                    Edges[sortString(a,b)] = countFace-1;
                    //
                if(Edges.count(sortString(a,c)) > 0){
                     countDebug++;
                     std::cout<<"------My debug---------"<<std::endl;

                     std::cout<<Edges[sortString(a,c)]<<std::endl;
                     std::cout<<countFace -1 <<std::endl;

                    _facesArray[Edges[sortString(a,c)]].setVoisin(countFace-1);
                    _facesArray[countFace-1].setVoisin(Edges[sortString(a,c)]);


                    _facesArray[Edges[sortString(a,c)]].showVoisin();
                    _facesArray[countFace-1].showVoisin();
                     std::cout<<"------My debug---------"<<std::endl;
                }
                else
                    Edges[sortString(a,c)] = countFace-1;

                if(Edges.count(sortString(b,c)) > 0){
                    std::cout<<"------My debug---------"<<std::endl;

                    std::cout<<Edges[sortString(b,c)]<<std::endl;
                    std::cout<<countFace -1 <<std::endl;

                     _facesArray[Edges[sortString(b,c)]].setVoisin(countFace-1);
                     _facesArray[countFace-1].setVoisin(Edges[sortString(b,c)]);
                     _facesArray[Edges[sortString(b,c)]].showVoisin();
                     _facesArray[countFace-1].showVoisin();
                      std::cout<<"------My debug---------"<<std::endl;
                   }
                 else
                     Edges[sortString(b,c)] = countFace-1;



                countFace++;

            }

    };
}


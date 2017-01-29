//
//  Modell.cpp
//  mac_obj
//
//  Created by depeng LIU on 2017/1/26.
//  Copyright © 2017年 depeng LIU. All rights reserved.
//

#include "Model.hpp"
#include <stdio.h>
#include <GLUT/GLUT.h>

//vertex data
struct Vertex{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};//Vertex

//vertex normal data
struct VertexN{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};//VertexN

//vertex texture data
struct VertexT{
    GLfloat x;
    GLfloat y;
};//VertexT

//face node data
struct FaceNode{
    int v;
    int vn;
    int vt;
};//FaceNode

//face
struct Face{
    FaceNode node[5];
};






















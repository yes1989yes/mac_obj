//
//  main.cpp
//  mac_obj
//
//  Created by depeng LIU on 2017/1/26.
//  Copyright © 2017年 depeng LIU. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Model.cpp"

using namespace std;

int count_v=0;
int count_vn=0;
int count_f=0;
int face;
Vertex *vContainer;
VertexN *vnContainer;
Face *fContainer;

string dataName;//
GLfloat data2,data3,data4;//

int countFileData(string fileName){
    int count = 0;//统计函数计数器
    string oneLine;
    ifstream infile(fileName.c_str());
    
    if(!infile)
    {
        cerr<<"errorrrr"<<endl;
        return 1;
    }
    
    while(getline(infile, oneLine)){//while
        if(oneLine[0]=='f'){
            count_f ++;
        }//if
        
        if(oneLine[0]=='v'){//if
            if(oneLine[1]=='n'){//if1
                count_vn++;
            }else{
                count_v++;
            }//if1
        }//if
        count++;
    }//while
    return count;
    
    //import the data into vector

}//countFlieData


void analyseFile(string fileName) {
    //dynamic initialization
    vContainer = new Vertex[count_v];
    vnContainer = new VertexN[count_vn];
    fContainer = new Face[count_f];
    
    //read the obj file
    string oneLine;//every line
    ifstream infile(fileName.c_str());
    //normal,vertex,face subscript
    int vn_index=0,v_index=0,f_index=0;
    // loop every line
    while(getline(infile, oneLine)){//while_getline
        if(oneLine[0]=='f'){//1
            istringstream streamIn1(oneLine);
            GLfloat a;
            streamIn1>>dataName;
            int i,k;
            for(i=0;i<face;i++){//for   //face的取值是多少？运行程序的时候留意一下
                streamIn1>>dataName;
                cout<<dataName<<endl;
                
                //1. get the vertex index
                a=0;
                
                
                for(k=0;dataName[k]!='/'&&dataName[k]!='\0';k++){//for2
                    char tmp=dataName[k];
                    a=a*10+(dataName[k]-48);
                }//for2
                
                fContainer[f_index].node[i].v=a;
                
                //judge if there is a normal index
                if(dataName[k]!='/')
                    continue;
                
                //2. normal index
                a=0;
                for(k=k+1;dataName[k]!='/'&&dataName[k]!='\0';k++){//for3
                    a=a*10+(dataName[k]-48);
                }//for3
                fContainer[f_index].node[i].vn=a;
                
                //judge if there is a texture coordinate index
                if (dataName[k]!='/')
                    continue;
                
                //3. texture coordinate index
                //...
                
            }//for
            f_index++;
        }//1
        
        //vertex and the vertex normal
        if(oneLine[0]=='v'){//if1
            //vn normal
            if (oneLine[1]=='n'){//if1.1
                istringstream streamIn2(oneLine);
                streamIn2>>dataName>>data2>>data3>>data4;
                vnContainer[vn_index].x=data2;
                vnContainer[vn_index].y=data3;
                vnContainer[vn_index].z=data4;
                vn_index++;
            }//if1.1
            //vn vertex
            else{//else1.1
                istringstream streamIn2(oneLine);
                streamIn2>>dataName>>data2>>data3>>data4;
                vContainer[v_index].x=data2;
                vContainer[v_index].y=data3;
                vContainer[v_index].z=data4;
                v_index++;
            }//else1.1
        }//if1
    }//while_getline
    
}//analyseFile


void display(){//display
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // zoom
    glScalef(0.05, 0.05, 0.05);
    //rotation
    glRotatef(-30.0, 66.0, 1.0, 0.0);
    //glRotatef(15.0, 1.0, 0.0, 0.0);
    //translation
    glTranslated(0.01, 0.0, 0.0);
    
    //draw the model
    for (int i=0;i<count_f;i++){//for2.1
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        glBegin(GL_POLYGON);
        glColor3f(0.0,1.0,0.0);
        
        for(int f=0;f<face;f++){//for2.2
            //1. vertex index
            int v_index=fContainer[i].node[f].v-1;
            // draw the vertex of the polygon
            glVertex3f(vContainer[v_index].x, vContainer[v_index].y, vContainer[v_index].z);
            
            //2.normal index
            //int vn_index=fContainer[i].node[f].vn-1;
            //normal
            //glNormal3f(vnContainer[vn_index].x, vnContainer[vn_index].y, vnContainer[vn_index].z);
            
            //3.texture coordinate
            //...
        }//for2.2
        glEnd();
        
    }//for2.1
    glFlush();
}//display

    //program entry

int main(int argc, char ** argv)
{//main
    //file name
    string obj = "/Users/dp/Documents/all_codes_dp/mac_obj/s.obj";
    // appoint the number of vertex in every unit
    face=4;
    // analyse the information of data
    int count = countFileData(obj);
    cout<<"Number of Lines="<<count<<endl;
    // read the model
    analyseFile(obj);
    
    //initialize the window
    glutInit(&argc, argv);
    //create the window
    glutCreateWindow("Imaging");
    //set the window size
    glutReshapeWindow(500, 500);
    //drawing
    glutDisplayFunc(display);
    glutMainLoop();


    cout<<"end"<<endl;
}//main




















    
    
    
    






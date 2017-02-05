
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


//---------define the state variaries--------------------------------
double global_angle_x,global_angle_y,global_angle_z;//variable: angle in x,y,z axis
double global_angleRate_x,global_angleRate_y,global_angleRate_z;//variable: angle rate in x,y,z axis
double global_pixel_hight, global_pixel_width;//the pixel number of CCD sensor
int global_number_pixels;


//-----------------------------------------


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
                //cout<<dataName<<endl;
                
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
                cout<<"normal="<<data2<<" "<<data3<<" "<<data4<<" "<<endl;
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
    
    //clear the color and depth buffer information
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    //设置光照
    glEnable(GL_LIGHTING); //启动光照
    GLfloat ambient[]={0.8f, 0.6f, 0.2f, 1.0f}; //环境光 RGBA 值
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient); //设置全局环境光
    
    //设置材质属性
    if(0)
    {
        glEnable(GL_COLOR_MATERIAL); //启动颜色跟踪法
        //指定多边形的正面使用颜色跟踪法
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    }
    else
    {
        glDisable(GL_COLOR_MATERIAL); //关闭颜色跟踪法
        GLfloat material_ambiemt[]={0.75f, 0.75f, 0.75f, 1.0f};
        //指定多边形的正面的环境反射和漫反射值
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_ambiemt);
    }
    
    GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat mat_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    GLfloat light0_diffuse[]= { 0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat light1_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat light1_diffuse[]= { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light1_specular[] = { 1.0f, 0.6f, 0.6f, 1.0f };
    GLfloat light1_position[] = { -63.0f, -3.0f, 3.0f, 1.0f };
    GLfloat spot_direction[]={ 1.0f, 1.0f, -1.0f};
    //定义材质属性
    glEnable(GL_COLOR_MATERIAL); //启动颜色跟踪法
    //指定多边形的正面使用颜色跟踪法
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS,mat_shininess);
    //light0 为漫反射的蓝色点光源
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION,light0_position);
    //light1 为红色聚光光源
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR,light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION,light1_position);
    glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,spot_direction);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    */
    
    
    
/*
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //define light
    GLfloat sun_light_position[] = {-1.0f, -1.0f, -1.0f, 0.0f};
    GLfloat sun_light_ambient[]  = {0.90f, 0.90f, 0.90f, 2.0f};
    GLfloat sun_light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //指定第0号光源的位置
    glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient); //GL_AMBIENT表示各种光线照射到该材质上，
    //经过很多次反射后最终遗留在环境中的光线强度（颜色）
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse); //漫反射后~~
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//镜面反射后~~~
    
    glEnable(GL_LIGHT0); //使用第0号光照
    glEnable(GL_LIGHTING); //在后面的渲染中使用光照
    glEnable(GL_DEPTH_TEST); //这句是启用深度测试，这样，在后面的物体会被挡着，例如房子后面有棵树，如果不启用深度测试，
    //你先画了房子再画树，树会覆盖房子的；但启用深度测试后无论你怎么画，树一定在房子后面（被房子挡着）

    
    GLfloat target_mat_ambient[]  = {0.5f, 0.2f, 0.5f, 1.0f};
    GLfloat target_mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat target_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat target_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat target_mat_shininess  = 30.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   target_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   target_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  target_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  target_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, target_mat_shininess);
*/
    
    // zoom
    glScalef(0.1, 0.1, 0.1);
    //rotation
    glRotatef(global_angle_x, 1.0, 0.0, 0.0);
    glRotatef(global_angle_y, 0.0, 1.0, 0.0);
    glRotatef(global_angle_z, 0.0, 0.0, 1.0);
    
    //glRotatef(15.0, 1.0, 0.0, 0.0);
    //translation
    glTranslated(0.0, 0.0, 0.0);
    
    //draw the model
    for (int i=0;i<count_f;i++){//for2.1
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        
        
        glBegin(GL_POLYGON);//GL_POLYGON,GL_POINTS,
        glColor3f(1,0,0);
        
        for(int f=0;f<face;f++){//for2.2
            
                   // cout<<"face#="<<i<<",point#="<<f<<endl;
            //1. vertex index
            int v_index=fContainer[i].node[f].v-1;
            // draw the vertex of the polygon
            glVertex3f(vContainer[v_index].x, vContainer[v_index].y, vContainer[v_index].z);
            
            //2.normal index
//            int vn_index=fContainer[i].node[f].vn-1;
            //normal
//            glNormal3f(vnContainer[vn_index].x, vnContainer[vn_index].y, vnContainer[vn_index].z);
            //cout<<vnContainer[vn_index].x<< vnContainer[vn_index].y<< vnContainer[vn_index].z<<endl;

            //3.texture coordinate
            //...
        }//for2.2
        glEnd();
        
        //glutSwapBuffers();

    }//for2.1
//      glutSolidSphere(2.0f, 50, 50);
    GLubyte* image_pixel_value=(GLubyte*)malloc(global_number_pixels);
    //new float[global_number_pixels];
    glReadPixels(0, 0, global_pixel_width,global_pixel_hight, GL_RED, GL_UNSIGNED_BYTE, image_pixel_value);
    printf("image pixel data read !\n");
    
    ofstream out1("/Users/dp/Documents/all_codes_dp/mac_obj2/mac_obj2/img002.txt",ios::out|ios::in|ios::trunc);
    //out1.open("/Users/dp/Documents/all_codes_dp/mac_obj2/mac_obj2/img001.txt",ios::out|ios::in|ios::trunc);
    if (out1.is_open())
    {//if
        out1<<"angle in x, y, z is "<<global_angle_x<<","<<global_angle_y<<","<<global_angle_z<<"\n";
        out1<<"image size is "<<global_pixel_width<<"\n";
        
        
        for(int pix_n=0;pix_n<global_pixel_width*global_pixel_hight;pix_n++){
        //for
       
            
            
        out1 << int(image_pixel_value[pix_n]);
            
        if((pix_n+1)%int(global_pixel_width)==0)
        {//if1
            out1<<"\n";
        }//if1
            else
        {//if1
            out1<<" ";
        }//if1
            
            
        //    cout << bool(image_pixel_value[pix_n])<<" ";
        }//for
        
            
        out1.close();
    cout<<"the image data is recorded in txt"<<endl;
    }//if


    
    glFlush();
    
    

}//display

    //program entry


    
    int main(int argc, char ** argv)
 {//main
    //======input the parameters and excute the pre-processing===================================================
    //file name
    string obj = "/Users/dp/Documents/all_codes_dp/mac_obj/s.obj";
    cout<<"input the angle in x,y,z="<<endl;
    cin>>global_angle_x>>global_angle_y>>global_angle_z;
    
    cout<<"input the global_pixel_hight = global_pixel_width="<<endl;
    cin>>global_pixel_hight;
    global_pixel_width=global_pixel_hight;
    
    global_number_pixels=global_pixel_hight*global_pixel_width*3;
    float *image_pixel_value= new float[global_number_pixels];
    
    
    //===========================================================================================================
    
    
    // appoint the number of vertex in every unit
    face=4;
    // analyse the information of data
    int count = countFileData(obj);
    //cout<<"Number of Lines="<<count<<endl;
    // read the model
    analyseFile(obj);
    
    //initialize the window
    glutInit(&argc, argv);
    //create the window
    glutCreateWindow("Imaging");
    //set the window size
    glutReshapeWindow(global_pixel_width,global_pixel_hight);
    cout<<"begin drawing..."<<endl;
    //drawing
    glutDisplayFunc(display);
    
    glutMainLoop();



    return 0;
}//main




















    
    
    
    






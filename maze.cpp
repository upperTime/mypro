#include "maze.h"
#include<QTimer>
#include<QKeyEvent>
#include<QDebug>
Maze::Maze(QWidget *parent) : QGLWidget(parent)
{
    fullscreen=false;

    m_xPos=0.0f;
    m_yRot=0.0f;
    m_zPos=0.0f;
    m_Fog = 0;
    m_FileName="E:/image/maze.jpg";
    m_BlackName="E:/image/blackmaze.jpg";
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timerout()),this,SLOT(upadteGl()));
    timer->start(10);
}
Maze::~Maze(){

}
void Maze::setMaze(int (*myMaze)[55][55],int (*value)[55][55],int c,int m[],int n[]){
    qDebug()<<"kaishi";
    for (int k=0;k<c;k++) {
        for(int col=1;col<=m[k];col++){
            for(int row=1;row<=n[k];row++){
                this->myMaze[k][col][row]=myMaze[k][col][row];
                this->value[k][col][row]=value[k][col][row];
                qDebug()<<this->myMaze[k][col][row]<<"+"<< this->value[k][col][row];
            }
        }
    }
}


void Maze::initializeGL(){

    m_Texture = bindTexture(QPixmap(m_FileName));       //载入位图并转换成纹理
    m_Black=bindTexture(QPixmap(m_BlackName));          //背景纹理
    glEnable(GL_TEXTURE_2D);                            //启用纹理映射
    buildLists();                                       //创建显示列表

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);               //黑色背景
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑

    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正

    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};  //环境光参数
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  //漫散光参数
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
    glEnable(GL_LIGHT1);                                //启动一号光源

    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};      //雾的颜色
    glFogi(GL_FOG_MODE, GL_EXP);                        //设置雾气的初始模式
    glFogfv(GL_FOG_COLOR, fogColor);                    //设置雾的颜色
    glFogf(GL_FOG_DENSITY, 0.05);                       //设置雾的密度
    glHint(GL_FOG_HINT, GL_DONT_CARE);                  //设置系统如何计算雾气
    glFogf(GL_FOG_START, 1.0f);                         //雾的开始位置
    glFogf(GL_FOG_END, 5.0f);                           //雾的结束位置
    glEnable(GL_FOG);                                   //启动雾效果

}

void Maze::resizeGL(int w, int h){

    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();                                   //重置投影矩阵//设置视口的大小
    gluPerspective(45.0,((GLdouble)w/(GLdouble)h),0.1,100.0);
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();
    updateGL();
}

void Maze::buildLists(){
    m_Box = glGenLists(1);                              //创建两个显示列表的空间
    glNewList(m_Box, GL_COMPILE);                       //开始创建第一个显示列表
    glBegin(GL_QUADS);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)


    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)


    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)


    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd();
    glEndList();                                        //第一个显示列表结束

}
void Maze::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    Map();
}
void Maze::Map(){
    glBindTexture(GL_TEXTURE_2D, m_Texture);            //选择纹理
    qDebug()<<"cout="<<count<<"c="<<c;
    for (int y=-10;y<10;y++) {

        for (int z=-10; z<10; z++)                             //循环来控制画盒子
        {
            for (int x=-10; x<10; x++)

            {
                if(y<7&&y>-9&&x<9&&x>-9&&z<9&&z>-9)
                    continue;
                if(z==9&&x>-3&&x<3&&y<9&&y>1)
                    continue;
                if(y==7&&x<9&&x>-9&&z<9&&z>-9){

                    if(x>0&&z>0&&myMaze[count][x][z]>0){
                        qDebug()<<"myMaze="<<myMaze[count][x][z];
                        glBindTexture(GL_TEXTURE_2D, m_Black);
                        glLoadIdentity();//设置盒子的位置
                        glTranslatef(0.0f+(float(x)*2.0f+m_xPos),
                                     -1.0f-float(y)*2.0f+m_yRot, -50.0f+float(z)*2.0f+m_zPos);
                        glCallList(m_Box);
                    }
                }else{
                    glBindTexture(GL_TEXTURE_2D, m_Texture);
                    glLoadIdentity();//设置盒子的位置
                    glTranslatef(0.0f+(float(x)*2.0f+m_xPos),
                                 -1.0f-float(y)*2.0f+m_yRot, -50.0f+float(z)*2.0f+m_zPos);
                    glCallList(m_Box);    //绘制盒子
                }

            }
        }
    }

}

void Maze::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
    case Qt::Key_F1:                                    //F1为全屏和普通屏的切换键
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        break;
    case Qt::Key_Escape:                                //ESC为退出键
        close();
        break;
    case Qt::Key_Up:
        m_xPos -= (float)sin(m_yRot * m_PIOVER180) * 1.05f;
        m_zPos -= (float)cos(m_yRot * m_PIOVER180) * 1.05f;
        //m_zPos+=0.1f;
        break;
    case Qt::Key_Down:
        m_xPos += (float)sin(m_yRot * m_PIOVER180) * 1.05f;
        m_zPos += (float)cos(m_yRot * m_PIOVER180) * 1.05f;
        //m_zPos-=1.0f;
        break;
    case Qt::Key_PageUp:                                //按下PageUp视角向上转
        m_LookUpDown -= 1.0f;
        if (m_LookUpDown < -90.0f)
        {
            m_LookUpDown = -90.0f;
        }
        break;
    case Qt::Key_PageDown:                              //按下PageDown视角向下转
        m_LookUpDown += 1.0f;
        if (m_LookUpDown > 90.0f)
        {
            m_LookUpDown = 90.0f;
        }
        break;
    case Qt::Key_Right:                                 //Right按下向左旋转场景
        m_yRot -= 1.0f;
        break;
    case Qt::Key_Left:                                  //Left按下向右旋转场景
        m_yRot += 1.0f;
        break;
    }
    updateGL();
}


void Maze::setX(double x){
    m_xPos+=x;
    updateGL();
    qDebug()<<x;
}
void Maze::setY(double y){
    m_yRot+=y;
    updateGL();
    qDebug()<<y;
}
void Maze::setZ(double z){
    m_zPos+=z;
    updateGL();
    qDebug()<<z;
}
void Maze::setFull(bool full){
    qDebug()<<full;
    if(full){
        count++;
        if(count>=c){
            count=c;
        }
    }
    updateGL();
}
void Maze::setC(int c, int count){
    this->c=c;
    this->count=count;
    qDebug()<<"c="<<c<<"count="<<count;
}


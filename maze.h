#ifndef MAZE_H
#define MAZE_H

#pragma once
#include<QWidget>
#include<QGLWidget>

#include<gl/GL.h>
#include<gl/GLU.h>
#include<iostream>
#include<algorithm>
#include<string>
//row 行 col 列
using namespace std;
class Maze : public QGLWidget
{
    Q_OBJECT
public:
    explicit Maze(QWidget *parent = nullptr);
    ~Maze();
    void setMaze(int myMaze[][55][55],int value[][55][55],int c,int m[],int n[]);
protected:
    void initializeGL();        //初始化界面
    void resizeGL(int w,int h); //窗口刷新时重置
    void paintGL();             //绘图函数
    //void keyPressEvent(QKeyEvent *event);//键盘响应事件
    // void inputKey(int key, int x, int y);//键盘响应事件
    void orientMe(float ang);
    void moveMeFlat(int direction);
    //void keyPressEvent(QKeyEvent *event);//键盘响应事件
private:
    void Map();                 //初始化场景
    void buildLists();          //初始化显示列
private:
    int myMaze[5][55][55];       //迷宫宝藏
    int value[5][55][55];        //迷宫宝藏的价值
    int c;
    int m[5];
    int n[5];
    int count=0;                  //计数器
    bool nextMaze;           //是否全屏显示
    bool run=false;                   //是否走迷宫
    QString m_FileName;         //图片路径
    GLuint m_Texture;           //存储纹理
    QString m_BlackName;        //背景路径
    GLuint m_Black;               //背景
    QString m_run1Name;              //路径
    GLuint m_run1;                       //路径
    QString m_run2Name;
    GLint m_run2;
    GLuint m_Fog;                                   //雾的模式
    GLuint m_Box;               //保存盒子的显示列表

    constexpr static const float m_PIOVER180 = 0.0174532925f; //实现度和弧度直接的折算
    GLfloat m_xPos;                                 //储存当前位置
    GLfloat m_zPos;
    GLfloat m_yRot;                                 //视角的旋转
    GLfloat m_LookUpDown;                           //记录抬头和低头


public:
    void setX(double x);                    //控制移动
    void setY(double y);
    void setZ(double z);
    void setnext(bool full);              //是否全屏
    void setC(int c,int count);                       //总数
    void runMaze();                             //走迷宫
    void full();
};

#endif // MAZE_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMovie>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMovie *movie =new QMovie("E:/image/mazesearch .gif");
    ui->logo->setMovie(movie);
    movie->start();
    connect(ui->begin,SIGNAL(clicked()),this,SLOT(initMaze()));
    //connect(ui->mazegroup,SIGNAL(on_mazegroup_currentIndexChanged()),)
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mazegroup_currentIndexChanged(int index)
{
    c=index+1;
    ui->mazewidget->setC(c,0);
    qDebug()<<c;
}
void MainWindow::init_string(){
    QString str;
    str=ui->mazeText->toPlainText();
    QStringList list=str.split(" ");
    memset(m,0,sizeof(m));
    memset(n,0,sizeof(n));
    int num=0;
    for(int i=0;i<c;i++){
        m[i]=list.at(num).toInt();
        num++;
        n[i]=list.at(num).toInt();
        num++;
        for(int col=1;col<=m[i];col++){
            for(int row=1;row<=n[i];row++){
                maze[i][col][row]=list.at(num).toInt();
                num++;
            }
        }
        if(num>=(list.size()-1))
            break;
    }
    for (int k=0;k<c;k++) {
        for(int col=1;col<=m[k];col++){
            for(int row=1;row<=n[k];row++){
                qDebug()<<maze[k][col][row];
            }
        }

    }
}
void MainWindow::find_ans(int k,int total, int row, int col) {
    for (int l = 2; l<total; l++) {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                if (i != j&&l >= i&&l >= j) {
                    dp[l][i][j] = max(max(dp[l - 1][i - 1][j], dp[l - 1][i][j - 1]), max(dp[l - 1][i - 1][j - 1], dp[l - 1][i][j])) + maze[k][i][l - i] + maze[k][j][l - j];
                }
                  qDebug() << dp[l][i][j] << "\t";
            }
             qDebug() << endl;
        }
         qDebug() << endl;
    }
    dp[total][row][col] = max(dp[total - 1][row][row - 1], dp[total - 1][row - 1][row]) + maze[k][row][col];
}
void MainWindow::find_route(int k, int total, int row, int col) {
    int max[3][1];
    max[0][0] = row;
    max[1][0] = row;
    max[2][0] = dp[total][row][col];
    mark[k][row][col] = 3;
    //printf_s("%d\n", max[2][0]);
    for (int l = total; l > 2; l--) {
        int r1 = maze[k][max[0][0]][l - max[0][0]];
        if (l == total) {
            r1 = 0;
        }
        // qDebug() <<"r1="<< r1 <<endl;
        int r2 = maze[k][max[1][0]][l - max[1][0]];
        // qDebug() << "r2=" << r2 << endl;
        max[2][0] = max[2][0] - r1 - r2;
        // qDebug()<< "testmax" << max[2][0]<<endl;
        for (int i = 1; i <= row; i++) {
            for (int j = i; j <= col; j++) {
                if (dp[l - 1][i][j] == max[2][0]) {
                    max[0][0] = i;
                    max[1][0] = j;
                    // qDebug() <<"test"<< max[0][0] << "\t" << max[1][0] << endl;
                    break;
                }
            }
        }
        mark[k][max[0][0]][l - max[0][0] - 1] = 1;
        mark[k][max[1][0]][l - max[1][0] - 1] = 2;
        //qDebug() << max[0][0] << "\t" << max[1][0] << "\t" << max[2][0] << endl;
    }
    //cout << endl;

}
void  MainWindow::initMaze() {

    init_string();
    memset(mark, 0, sizeof(mark));
    for (int k=0;k<c;k++) {
        memset(dp, 0, sizeof(dp));
        find_ans(k,n[k] + m[k], m[k], n[k]);
        find_route(k,n[k] + m[k], m[k], n[k]);
        mark[k][1][1] = 3;
        for (int i = 1; i <= m[k]; i++) {
            for (int j = 1; j <= n[k]; j++) {
                qDebug() << mark[k][i][j] << "\t";
            }
            qDebug()<<"\n";
        }
    }
    ui->mazewidget->setMaze(maze,mark,c,m,n);
    ui->mazewidget->updateGL();
}


void MainWindow::on_left_clicked()
{
    ui->mazewidget->setX(1);
}

void MainWindow::on_right_clicked()
{
    ui->mazewidget->setX(-1);
}

void MainWindow::on_up_clicked()
{
    ui->mazewidget->setZ(1);
}



void MainWindow::on_down_clicked()
{
    ui->mazewidget->setZ(-1);
}

void MainWindow::on_pgup_clicked()
{
    ui->mazewidget->setY(-1);
}

void MainWindow::on_pgdn_clicked()
{
    ui->mazewidget->setY(1);
}



void MainWindow::on_nextMaze_clicked()
{
    ui->mazewidget->setnext(true);
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    switch (event->key())
    {
    case Qt::Key_F1:                                    //F1为全屏和普通屏的切换键
        on_nextMaze_clicked();
        break;
    case Qt::Key_F2:
        on_beforeMaze_clicked();
        break;
    case Qt::Key_F5:
        on_runMaze_clicked();
        break;
    case Qt::Key_Escape:                                //ESC为退出键
        close();
        break;
    case Qt::Key_W:
        on_up_clicked();
        //m_zPos+=0.1f;
        break;
    case Qt::Key_S:
        on_down_clicked();
        //m_zPos-=1.0f;
        break;
    case Qt::Key_Q:                                //按下PageUp视角向上转
        on_pgup_clicked();
        break;
    case Qt::Key_E:                              //按下PageDown视角向下转
        on_pgdn_clicked();
        break;
    case Qt::Key_D:                                 //Right按下向左旋转场景
        on_right_clicked();
        break;
    case Qt::Key_A:                                  //Left按下向右旋转场景
        on_left_clicked();
        break;
    case Qt::Key_Enter:
        on_pushButton_clicked();
        break;
    }
    ui->mazewidget->updateGL();
}



void MainWindow::on_beforeMaze_clicked()
{
    ui->mazewidget->setnext(false);
}

void MainWindow::on_runMaze_clicked()
{
   ui->mazewidget->runMaze();
}

void MainWindow::on_pushButton_clicked()
{
    ui->mazewidget->resize(1366,768);
    ui->mazewidget->full();
}

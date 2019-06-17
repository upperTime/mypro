#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void find_ans(int k,int total, int row, int col);
    void find_route(int k, int total, int row, int col);
private slots:


    void on_up_clicked();




    void on_mazegroup_currentIndexChanged(int index);

    void init_string();

    void initMaze();
    void on_left_clicked();

    void on_right_clicked();

    void on_down_clicked();

    void on_pgup_clicked();

    void on_pgdn_clicked();



    void on_fullScreen_clicked();

    void keyPressEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
    int c;              //数据组数
    int m[5];              //行
    int n[5];              //列
    int maze[5][55][55];    //迷宫
    int dp[110][55][55];    //表
    int mark[5][55][55];    //路线
};

#endif // MAINWINDOW_H

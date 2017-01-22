#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <cstring>
#include <time.h>
#include <windows.h>
#include <fstream>
#include "CLinkedQueue.h"
#include "CLinkedStack.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <cstdlib>
#include <QDebug>
#include <QProcess>
using namespace std;
#define MAXSIZE 1638400
int rank[MAXSIZE];
int parent[MAXSIZE];
int wid=100;
int MAX = 100;

struct node {
    int x,y,fx,fy;
    int content;
    bool visited;
};

node laby[500][500];

void BFS(int sx, int sy,int ex, int ey) {

    CLinkedQueue<node> myQueue;
    QFile file("../Maze/maze/path.pt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    node temp = laby[sx][sy];
    myQueue.EnQueue(temp);

    int delx[4] = {0,0,-1,1};
    int dely[4] = {1,-1,0,0};

    while (!myQueue.IsEmpty()) {
        node currentNode = myQueue.GetFront();

        myQueue.DeQueue();

        int m = currentNode.x;
        int n = currentNode.y;

        currentNode.visited = true;

        if (currentNode.x == ex && currentNode.y == ey) {
            break;
        }

        for(int i = 0; i < 4;i++) {
            int next_m = m + delx[i];
            int next_n = n + dely[i];
            if (next_m < 0 || next_m >= MAX || next_n < 0 || next_n >= MAX) continue;

            if (laby[next_m][next_n].content != 1 && laby[next_m][next_n].visited == false) {
                laby[next_m][next_n].fx = m;
                laby[next_m][next_n].fy = n;
                myQueue.EnQueue(laby[next_m][next_n]);
                laby[next_m][next_n].visited = true;
            }
        }
    }

    int backx = ex, backy = ey;
    int step = 0;
    CLinkedStack<node> showStack;

    while (backx != sx || backy != sy) {

        showStack.Push(laby[backx][backy]);

        int tempBackx = laby[backx][backy].fx;
        int tempBacky = laby[backx][backy].fy;

        backx = tempBackx;
        backy = tempBacky;

        step++;
    }
    out<<1<<" "<<1<<"\n";
    cout<<"路径:"<<endl;
    while (!showStack.IsEmpty()) {
        node current = showStack.GetTop();
        showStack.Pop();
        cout<<'('<<current.x<<','<<current.y<<") ";
        out<<current.x<<" "<<current.y<<"\n";
    }
    file.close();
    cout<<endl;

    cout<<"步长:"<<step<<endl;
}

void Init()
{
    memset(rank, 0, sizeof(rank));
    for(int i=0; i < MAXSIZE; ++i )
        parent[i] = i;
}

int FindSet(int x)
{
    if( x != parent[x] )
        parent[x] = FindSet(parent[x]);
    return parent[x];
}

void UnionSet(int root1, int root2)
{
    int x = FindSet(root1), y = FindSet(root2);
    if( x == y ) return ;
    if( rank[x] > rank[y] ) parent[y] = x;
    else
    {
        parent[x] = y;
        if( rank[x] == rank[y] ) ++rank[y];
    }
}
int postolist(int x,int y)
{
    return x*wid+y;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::do_make_maze(){
    int length = ui->lineEdit->text().toInt();
    if(length==0){
        QMessageBox::information(this,"Message","wrong!");
        return;
    }
    wid = MAX = length;

    int x,y,i,j,d,xt1,yt1,xt2,yt2;

        char dun[1001][1001];

        Init();
        for (i=0; i<wid; i++)
        {
            for (j=0; j<wid; j++)
            {
                dun[i][j]='1';
            }
        }
        for (i=1; i<wid; i++)
        {
            if (i%2 == 1)
            {
                for (j=1; j<wid; j+=2)
                {
                    dun[i][j]='0';
                }
            }
            else
            {
                for (j=2; j<wid; j+=2)
                {
                    dun[i][j]='1';
                }
            }

        }
        srand(time(NULL));
        while (FindSet(postolist(1,1)) != FindSet(postolist(wid-3,wid-3)))
        {

            do
            {
                x=rand()%(wid-2)+1;
                y=(rand()+123)%(wid-2)+1;
            }
            while (dun[x][y] != '1');
            d=x%2;

            if (d == 0)
            {
                xt1=x+1;
                yt1=y;
                xt2=x-1;
                yt2=y;
                if (FindSet(postolist(xt1,yt1)) != FindSet(postolist(xt2,yt2)))
                {
                    dun[x][y]='0';
                    UnionSet(postolist(xt1,yt1),postolist(xt2,yt2));
                }
            }
            else if (d == 1)
            {
                xt1=x;
                yt1=y+1;
                xt2=x;
                yt2=y-1;
                if (FindSet(postolist(xt1,yt1)) != FindSet(postolist(xt2,yt2)))
                {
                    dun[x][y]='0';
                    UnionSet(postolist(xt1,yt1),postolist(xt2,yt2));
                }
            }

        }
        for (i=0; i<wid; i++)
        {
            dun[i][wid-1]='1';
            dun[wid-1][i]='1';
        }
        dun[1][1] = '5';
        dun[wid-2][wid-2] = '8';
        dun[wid-3][wid-2] = '0';
        dun[wid-2][wid-3] = '0';
    QString file_name = QFileDialog::getSaveFileName(this,tr("保存迷宫"),"../Maze/maze",tr(".txt"));
    QFile file(file_name);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        for (i = 0; i < wid; i++)
            {
                for(j = 0; j<wid; j++)
                    if(j==wid-1)
                    {
                       out<<dun[i][j]<<endl;
                    }
                    else
                       out<<dun[i][j]<<" ";
            }
        file.close();
    }
    if(!file_name.isNull())
    QMessageBox::information(this,"Message","Successful!");
}
void MainWindow::do_find_path(){
    QString file_name = QFileDialog::getOpenFileName(this,tr("解锁迷宫"),"../Maze/maze",tr(".txt"));
    if(file_name.isNull()){
        return;
    }
    ifstream in;
    string filename = file_name.toStdString();

    const char *fileName = filename.c_str();
    ifstream infile(fileName);
    char str[1000];
    int row=0;
    while(!infile.eof())
    {
     infile.getline(str, sizeof(str));
     row++;
    }
    infile.close();
    row--;
    MAX = row;
    in.open(fileName,ios::in);
    int sx,sy,ex,ey;

        int curNum;
        int m = 0, n = 0;

        while (!in.eof()) {
            in>>curNum;
            laby[m][n].content = curNum;
            laby[m][n].x = m;
            laby[m][n].y = n;
            laby[m][n].visited = false;
            if (curNum == 5) {
                sx = m;
                sy = n;
            }
            if (curNum == 8) {
                ex = m;
                ey = n;
            }
            n ++;
            if (n == MAX) {
                n = 0;
                m++;
            }
        }
        for(int i = 0; i < MAX; i++) {
            for(int j = 0; j < MAX; j++) {
                cout<<laby[i][j].content<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        double bTime = clock();
        BFS(sx, sy, ex, ey);
        double eTime = clock();
        cout<<"花费时间:"<<(eTime-bTime)*10<<" ms"<<endl;
        return ;
}

void MainWindow::on_pushButton_clicked()
{
    do_make_maze();
}

void MainWindow::on_pushButton_2_clicked()
{
    do_find_path();

}


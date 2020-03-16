#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include<QMessageBox>
#include<QTimer>

#include "ui_mainwindow.h"
class MainWindow : public QMainWindow
{    Q_OBJECT
 public:
     bool isPicOnLabel;
     explicit MainWindow(QWidget *parent = 0);
     QImage* img=new QImage,* scaledimg=new QImage;
     ~MainWindow();
 public slots:
       void slot_replyFinished(QNetworkReply* reply);
 private slots:    void on_PicButton_clicked();
 private:
        Ui::MainWindow *ui;
        void PicConnect(QString p);
        void SetWindow();
        void ShowPic();
        void StopPic();
};

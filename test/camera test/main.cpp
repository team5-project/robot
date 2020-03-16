#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
QString PU="http://192.168.137.226:8080/javascript_simple.html";
void MainWindow::PicConnect(QString PicUrl)
{       //connect to picture
    QNetworkAccessManager *manager;
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_replyFinished(QNetworkReply*)));
    QNetworkRequest request;
    request.setUrl(QUrl(PicUrl));
    manager->get(request);
}

void MainWindow::slot_replyFinished(QNetworkReply* reply){       //save the picture
    QPixmap pix;
    QByteArray data = reply->readAll();

    pix.loadFromData(data, "JPG");
    pix.save("/root/Qt/program/netpicture/tmp1.jpg", "JPG", 100);
}

void MainWindow::SetWindow()
{       //set the window with one label and pushButton
    this->resize(800,600);
    ui->PicLabel->setGeometry(10,10,640,480);
    ui->PicLabel->setText("PICTURE......");
    ui->PicButton->setGeometry(300,500,30,15);
    isPicOnLabel=false;
    ui->PicButton->setText("Show");
}

void MainWindow::on_PicButton_clicked()
{
    if(isPicOnLabel==false)
    {        ShowPic();    }
    else
    {        StopPic();    }}

void MainWindow::ShowPic()
{    isPicOnLabel=true;
     ui->PicButton->setText("stop");
      while(1)    {
          if(isPicOnLabel==false)
              break;
          PicConnect(PU);
          QEventLoop eventloop;
          QTimer::singleShot(10, &eventloop, SLOT(quit()));//等待10*0.001秒
          eventloop.exec();
          if(! ( img->load("/root/Qt/program/netpicture/tmp1.jpg") ) ) //加载图像
          {
              QMessageBox::information(this,
                                       tr("打开图像失败"),
                                       tr("打开图像失败!"));
              delete img;
              return;            }
          *scaledimg=img->scaled(640,480,Qt::KeepAspectRatio);
          ui->PicLabel->setPixmap(QPixmap::fromImage(*scaledimg));    }
}

void MainWindow::StopPic(){
    isPicOnLabel=false;
    ui->PicButton->setText("show");
}

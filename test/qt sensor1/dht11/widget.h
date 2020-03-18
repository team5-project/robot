#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <QTimer>
#include <QtDebug>

#define MAX_TIMINGS	85
#define DHTPIN	 3	// GPIO2
#define TUNING_FACTOR 64

typedef unsigned char uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int uint32_t;


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
     void delay(double mSec);
    // uint8_t dht_data[5] = { 0, 0, 0, 0, 0 };
 //    uint8_t laststate	= HIGH;
 //    int previoustBlockState()!=1;
    // double f;
     uint8_t counter		= 0;
     uint8_t j			= 0, i;
      QTimer *timer;


public slots:
     void read_dht_data();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

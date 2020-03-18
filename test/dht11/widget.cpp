#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    wiringPiSetup();
    timer = new QTimer(this);
   // timer->start(2000);
   // wiringPiSetup();
    connect(timer,SIGNAL(timeout()),this,SLOT(read_dht_data()));
     timer->start(2000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::read_dht_data()
{
    if (-1 == wiringPiSetup())
    {
    qDebug()<<"Setup wiringPi failed!"<<endl;
    return;
    }
    uint8_t dht_data[5] = { 0, 0, 0, 0, 0 };
     uint8_t laststate = HIGH;
    //int laststate	= HIGH;
    // uint8_t counter		= 0;
     //uint8_t j			= 0, i;
     //float f;
    // int lasts = LOW;

    dht_data[0] = dht_data[1] = dht_data[2] = dht_data[3] = dht_data[4] = 0;

   // uint8_t laststate	= HIGH;
    pinMode( DHTPIN, OUTPUT );
    digitalWrite( DHTPIN, LOW );
    delay( 18 );
    digitalWrite(DHTPIN, HIGH);
    delay(0.04);
    pinMode( DHTPIN, INPUT ); /* prepare to read the pin */


    for ( i = 0; i < MAX_TIMINGS; i++ )  /* detect change and read data */
    {
        counter = 0;
        while ( digitalRead( DHTPIN ) == laststate )
        {
            counter++;
            delay(0.001);
            if ( counter == 255 )
            {
                break;
            }
        }
        laststate = digitalRead( DHTPIN );
            if ( counter == 255 )
            break;

        if ( (i >= 4) && (i % 2 == 0) )
        {
            dht_data[j / 8] <<= 1;
            if ( counter > TUNING_FACTOR )
                dht_data[j / 8] |= 1;
            j++;
        }

    }


    if ( (j >= 40) &&
         (dht_data[4] == ( (dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3]) & 0xFF) ) )
    {
        uint8_t h = (uint8_t)((dht_data[0] << 8) + dht_data[1]) / 10;
        if ( h > 100 )
        {
            h = dht_data[0];
        }
        uint8_t c = (uint8_t)(((dht_data[2] & 0x7F) << 8) + dht_data[3]) / 10;
        if ( c > 125 )
        {
            c = dht_data[2];
        }
        if (dht_data[2] & 0x80 )
        {
            c = -c;
        }

        ui->temp->setText(QString::number(c));
        ui->humi->setText(QString::number(h));
        qDebug() <<"The temperature is " << c << "C" << endl;
        qDebug() <<"The humidity is " << h << "%" << endl;
       // f= dht_data[2]*9./5.+32;
       // qDebug("humidity=%d.%d%% temperature=%d.%d*C \n",dht_data[0],dht_data[1],dht_data[2],dht_data[3]);
        //ui->humi->setText(QString::number(dht_data[0])+"."+QString::number(dht_data[1])+"%");
        //ui->temp->setText(QString::number(dht_data[2])+"."+QString::number(dht_data[3])+"c");
       //ui->temp->setText(QString::number(c));
       // ui->humi->setText(QString::number(h));
        //qDebug("humidity=%d.%d%% temperature=%d.%d*C \n",dht_data[0],dht_data[1],dht_data[2],dht_data[3]);

        delay(2000);

    }
    else  {
       qDebug()<< "No Data, skip"<<endl;
    }
}

void Widget::delay(double mSec)
{
    QEventLoop loop;
    QTimer::singleShot(mSec, &loop, SLOT(quit()));
    loop.exec();
}

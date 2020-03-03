#include <iostream>
#inclede <wiringPi.h>
#include <softPwm.h>

using namespace std ;
#define pwm_pin1 1

int main()
{  
        wiringPiSetup();
        softPwmCreate( pwm_pin1 , 0 , 100 );
        int i ;
        for ( i=0 ; i<2 ; i++ )
        {    
               softPwmWrite(pwm_pin1 , 20 ) ;
               delay ( 1000 ) ;
               softPwmWrite(pwm_pin1 , 0 ) ;
               delay ( 1000 ) ;   
         }     
}

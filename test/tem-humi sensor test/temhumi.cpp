#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#define MAX_TIMINGS	85
#define DHTPIN		3	// GPIO22 

int dht_data[5] = { 0, 0, 0, 0, 0 };

void read_dht_data()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j			= 0, i;

	dht_data[0] = dht_data[1] = dht_data[2] = dht_data[3] = dht_data[4] = 0;

	
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40);
	pinMode( DHTPIN, INPUT ); 

	
	for ( i = 0; i < MAX_TIMINGS; i++ )  /* detect change and read data */
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
        //digitalRead( DHTPIN ) == HIGH;
	
			if ( counter == 255 )
			break;

		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht_data[j / 8] <<= 1;
			if ( counter > 50 )
				dht_data[j / 8] |= 1;
			j++;
		}
	}

	
	if ( (j >= 40) &&
	     (dht_data[4] == ( (dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3]) & 0xFF) ) )
	{
		float h = (float)((dht_data[0] << 8) + dht_data[1]) / 10;
		if ( h > 100 )
		{
			h = dht_data[0];	
		}
		float c = (float)(((dht_data[2] & 0x7F) << 8) + dht_data[3]) / 10;
		if ( c > 125 )
		{
			c = dht_data[2];	
		}
		if (dht_data[2] & 0x80 )
		{
			c = -c;
		}
		
		printf( "T = %.1f *C  H= %.1f %% \n", c, h );
		
		
	}
	else  {
		printf( "No Data, skip\n" );
	}
}

int main( void )
{
	

	if ( wiringPiSetup() == -1 )
		exit( 1 );

	while ( 1 )
	{
		read_dht_data();
		delay( 2000 ); 
	}

	return(0);
}


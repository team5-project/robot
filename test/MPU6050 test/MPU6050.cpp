#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

#define gy521_Address 0x68

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define AcX 0x3B
#define AcY 0x3D
#define AcZ 0x3F

int fd;

void MPU_Init()
{
	wiringPiI2CWriteReg8(fd, SMPLRT_DIV, 0x07);
	wiringPiI2CWriteReg8(fd, PWR_MGMT_1, 0x01);
	wiringPiI2CWriteReg8(fd, CONFIG,0);
	wiringPiI2CWriteReg8(fd, GYRO_CONFIG, 24);
	wiringPiI2CWriteReg8(fd, INT_ENABLE, 0x01);
}
	
short read_raw_data(int addr){
	short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}

void ms_delay(int val){
	int i,j;
	for(i=0;i<=val;i++)
		for(j=0;j<1200;j++);
}

int main(){
	
	float Acc_x,Acc_y,Acc_z;
	float Ax=0, Ay=0, Az=0;
	fd = wiringPiI2CSetup(gy521_Address);    /*Initializes I2C with device Address*/
	MPU_Init();		                 /* Initializes GY521 */
	
	while(1)
	{
		/*Read raw value of Accelerometer from gy521*/
		Acc_x = read_raw_data(AcX);
		Acc_y = read_raw_data(AcY);
		Acc_z = read_raw_data(AcZ);
		
		
		/* Divide raw value by sensitivity scale factor */
		Ax = Acc_x/16384.0;
		Ay = Acc_y/16384.0;
		Az = Acc_z/16384.0;
		
		
		printf("\n  Ax=%.3f g\tAy=%.3f g\tAz=%.3f g\n",Ax,Ay,Az);
		
		delay(500);
		if (Acc_x>5000 &&Acc_x<16000){
			printf("LEAN FORWARD");
		}
		else if (Acc_x<-5000&&Acc_x>-16000){
			printf("LEAN back");	
			 }
		else if (Acc_y>5000&&Acc_y<16000){
			printf("LEAN LEFT");	
			 }
		else if (Acc_y<-5000&&Acc_y>-16000){
			printf("LEAN RIGHT");	
			 }
		
		else if (Acc_x<5000&&Acc_x>-5000){
			printf("LEVEL");	
			 }
		else if (Acc_y<5000&&Acc_y>-5000){
			printf("LEVEL");	
			 }	 
		
	}
	return 0;
}
	
	

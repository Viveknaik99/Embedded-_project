#include<reg51.h>

sbit mot1=P1^0; // motor 1 connected port1.0
sbit mot2=P1^1; // motor 2 connected port1.1	    
sbit mot3=P1^2;	// motor 3 connected port1.2
sbit mot4=P1^3;	// motor 4 connected port1.3

sbit s_left=P0^0;  // IR sensor1 connected to port0.0
sbit s_right=P0^1; // IR sensor2 connected to port0.1

void forward (void);
void backward (void);
void left (void);
void right (void);

void forward (void)	 // To move forward direction
{
    mot1=0;
	mot2=1;
	mot3=1;
	mot4=0;
}

void backward (void) // TO move backward direction
{
    mot1=0;
	mot2=1;
	mot3=0;
	mot4=1;
}

void left (void)  // To move  left side direction
{
    mot1=0;
	mot2=1;
	mot3=0;
	mot4=0;
}
			   
void right (void)  //To move right side direction
{	 
    mot1=0;
	mot2=0;
	mot3=1;
	mot4=0;
}

void stop (void)   // To stop the rotation of the  both the motor
{
    mot1=0;
	mot2=0;
	mot3=0;
	mot4=0;
}

void main()
{
	s_left=1;  // IR senor  1 left
	s_right=1; // IR sensor 2 right
	while(1)
	{ 
	 if(s_left==0 && s_right==0)   // if both the sensor is 0 the bot will moves forward
	 {
		 forward();
	 }
	 else if(s_left==1 && s_right==1) // if the both the senor is 1 the bot will stop moving
 	 {
	 stop();
	 }
	 else if(s_left==0 && s_right==1)  // if the left sensor  is 0 and right sensor is 1 the bot will move  towards left
	 {
		 left();
	 }
	 else if(s_left==1 && s_right==0)	// if the left sensor  is 1  and right sensor  is 0 the bot will move towards right
	 {
       right();
	   }
	   }
	   }
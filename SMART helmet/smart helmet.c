#include"lcd.h"
#include"header.h"
#include<stdio.h>


sbit UltrasonicSwitch = P1^0; // Switch for Ultrasonic sensor
sbit DHTSwitch = P1^1;        // Switch for DHT11 sensor
sbit echo = P3^3;             // Ultrasonic Echo pin
sbit trig = P3^5;             // Ultrasonic Trig pin
sbit DHT11 = P3^4;            // DHT11 sensor data pin
sfr16 DPTR=0x82;
sbit sensor = P1^3;  // P1^3 is connected to the output of the MQ gas sensor

unsigned int I_RH, D_RH, I_Temp, D_Temp, checksum;
unsigned char DHT11Switch;
unsigned int range=0;


void delay_40ms() {
    _nop_(); _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_(); _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_(); _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_(); _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
}


void Request() 
{
    DHT11 = 0;
    delay_40ms();
    DHT11 = 1;
}

void Response() 
{
    while(DHT11 == 1);
    while(DHT11 == 0);
    while(DHT11 == 1);
}


int Receive_data() 
{
    int i, dataD = 0;
    for(i = 0; i < 8; i++) {
        while(DHT11 == 0);
        delay_40ms();
        if(DHT11 == 1)
            dataD = (dataD << 1) | (0x01);
        else
            dataD = (dataD << 1);
        while(DHT11 == 1);
    }
    return dataD;
}


void Display_DHT11() 
{
    unsigned int a, b, c, d;
    cmd_lcd(0x01);
    cmd_lcd(0x80);
    Print_String("Humidity ");
    cmd_lcd(0xC0);
    Print_String("Temperature");
    Request();
    Response();
    I_RH = Receive_data();
    D_RH = Receive_data();
    I_Temp = Receive_data();
    D_Temp = Receive_data();
    checksum = Receive_data();

    if((I_RH + D_RH + I_Temp + D_Temp) != checksum) 
	{
        Print_String("Error");
    } 
	else 
	{
        a = (I_RH / 10) + 48;
        b = (I_RH % 10) + 48;
        cmd_lcd(0x89);
        data_lcd(a);
        cmd_lcd(0x8A);
        data_lcd(b);
        cmd_lcd(0x8B);
        data_lcd('%');

        c = (I_Temp / 10) + 48;
        d = (I_Temp % 10) + 48;
        cmd_lcd(0xCC);
        data_lcd(c);
        cmd_lcd(0xCD);
        data_lcd(d);
        cmd_lcd(0xCE);
        data_lcd(0xDF);
        cmd_lcd(0xCF);
        data_lcd('C');
    
	}
}

void send_pulse(void) 
{
  TH0=0x00;TL0=0x00; 
   trig=1;
   _nop_();_nop_();_nop_();_nop_();_nop_();
   _nop_();_nop_();_nop_();_nop_();_nop_();
   trig=0;
}

unsigned char ultrasonic()
{
  unsigned char get;
  send_pulse();
  while(!echo);
  while(echo);
  DPH=TH0;
  DPL=TL0;
  TH0=TL0=0xff;
  if(DPTR<38000)
    get=DPTR/59;
  else
    get=0;
  return get;
}






void Gas_Sensor() 
{
    // Assuming the Gas Sensor operation 
	if(sensor == 1)
	{
		Led = 1;
	}
	else
	{
		Led = 0;
	}
}

void main() {
    //Ultrasonic_Init();
    initlcd(); // Call your LCD initialization function
	cmd_lcd(0x01);
    cmd_lcd(0x80); // Set cursor to the beginning of the first line
    Print_String("LCD init..");
    delay_ms(100); // Delay for 40ms
    

    while (1) 
	{
        if (UltrasonicSwitch == 0) 
		{
			TMOD=0x09;
			TH0=TL0=0;
			TR0=1;
			//initlcd();
			cmd_lcd(0x01);
			Print_String("DISTANCE:");
			P3|=(1<<2);
		    cmd_lcd(0x8A);
		    range=ultrasonic();
		    data_lcd((range/100)+48);
		    data_lcd(((range/10)%10)+48);
		    data_lcd((range%10)+48);	
			delay_ms(200);
		}
		 
		else if (DHTSwitch == 0) 
		{
         
		    //cmd_lcd(0x01); // Clear the LCD display
			//cmd_lcd(0x80); // Set cursor to the beginning of the first line
    		//Print_String("Switch 2 pressed");
            Display_DHT11();
			delay_ms(100);
        }
		else 
		{
            Gas_Sensor();
        }
    }
}

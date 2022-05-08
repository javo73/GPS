#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <AltSoftSerial.h>
AltSoftSerial serialgps; //Puerto serie del gps


#include <MicroNMEA.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


char nmeaBuffer[100];
MicroNMEA nmea(nmeaBuffer,sizeof(nmeaBuffer));


void setup() {
    // put your setup code here, to run once:
    serialgps.begin(9600); //enciendo el serie del gps
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //enciendo la pantalla
    display.display(); //arranca la animacion de Adafruit
    delay(2000);
    display.clearDisplay(); //limpio la pantalla
    

}




void loop() {
    // put your main code here, to run repeatedly:


  while (serialgps.available()) 
{
  char c =   serialgps.read(); //Parseo el string que larga el GPS
  if(nmea.process(c))
  {


      
      //Guardo en variables los datos que quiero mostrar
      delay(100);
      long latitud = nmea.getLatitude();
      long longitud = nmea.getLongitude();
      int ano = nmea.getYear();
      int mes = nmea.getMonth();
      int dia = nmea.getDay();
      


    //Muestro los datos almacenados
     display.clearDisplay();  
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0,10);
     display.println();
     display.println("Latitud [deg]:" + latitud/1000000);
     display.println("Longitud [deg]:" + longitud/1000000);
     display.print("Altitud [m]:");
     long alt;
     if(nmea.getAltitude(alt))
     display.println(alt/1000,3);
     else 
     display.println("No Disponible");

     
     display.print("Fecha:");
     display.print(dia);
     display.print("/");
     display.print(mes);
     display.print("/");
     display.print(ano);

     display.display();// Muestro Todo en Pantalla
    
     
  }
}
}
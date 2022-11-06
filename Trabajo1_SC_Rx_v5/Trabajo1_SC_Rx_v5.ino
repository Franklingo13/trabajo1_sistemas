#include <Wire.h>             //wire library
#include <Adafruit_MCP4725.h> // MCP4725 library from adafrui
#include <SD.h> //libreria SD
#define RXPIN 7

Adafruit_MCP4725 MCP4725; 
//#define UMBRAL 10
//int ambientelectura = 0;

File myFile;

void setup() {
  // put your setup code here, to run once:
  pinMode(RXPIN, INPUT);
  Serial.begin(9600);
  //ambientelectura = analogRead(RXPIN);
  MCP4725.begin(0x60); // Default I2C Address of MCP4725 breakout board (sparkfun)   If not try 0x61 or 0x62
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
}

void loop() {
  // put your main code here, to run repeatedly:
  myFile = SD.open("datalog.txt", FILE_WRITE);//abrimos  el archivo
  int lectura = digitalRead(RXPIN);
  int bits[10];
  int val=0;
  
  // Escuchando el bit de inicio
  //LOW xq cuando llega luz laser muestra cero 
   if(lectura == LOW ){
    for(int i =0; i<10; i++){
      
      if(digitalRead(RXPIN)== LOW){
        bits[i]=1;
      }
      else{
        bits[i]=0;
      }
      //delay(10);
      delayMicroseconds(1000);
    }
  }

      for(int i=0; i<10; i++){
      //Serial.print( bits[i]);
      val = val * 2 + ( bits[i]);
    } 
    //Serial.println("");
    
    //Serial.println(val);

    // ....................  escribir datos .... 
    if (myFile) {
          Serial.println(val);
          myFile.print(val)
          myFile.close(); //cerramos el archivo
    }else{
    Serial.println("Error al abrir el archivo");
    }

    

    MCP4725.setVoltage(val, false);
    //delayMicroseconds(50);
    //for(int i=0; i<10; i++){
    //  bits[i]=0;
    //} 
 //dela yMicroseconds(50);
 //delay(1);
} 

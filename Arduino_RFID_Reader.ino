#include <SPI.h>
#include <Ethernet.h>

byte mac [ ] = { 0x90 , 0xA2 , 0xDA, 0x0D , 0x1F , 0 x80 } ; // MAC
byte ip [ ] = { 192 , 168 , 2 , 20 }; // IP
byte subnet[]= { 255,255,255,0 };
byte gateway [] = { 192, 168, 2, 1};
byte server [] = { 10, 4, 254, 1 }; // ip server

EthernetClient client ;
int RFIDResetPin = 7;
void setup (){ 
  Serial.begin(9600);
  Serial.println ("Comunicacion Serial Lista");
  Serial.println (" ");
  pinMode(RFIDResetPin,OUTPUT);
  digitalWrite(RFIDResetPin,HIGH);
  Ethernet.begin(mac,ip,subnet,gateway);
  Serial.print("Direccion IP del Lector RFID");
  Serial.println(Ethernet.localIP());

voidloop(){
  char tagString [11];
  int index = 0;
  boolean reading = false ;
  while(Serial.available()){
    int readByte = Serial.read(); // lee el s igu ien te byte d ispon ible
    if( readByte == 2 ) 
      reading = true; // in ic i o del tag
    if( readByte == 3 ) 
      reading = false; // f i n al del tag
    if( reading && readByte != 2 && readByte != 10 && readByte != 1 3 ) { 
        tagString[inde x] = readByte ; inde x ++; 
        } 
    }
  enviartag (tagString);
  clearTag(tagString); // limpia cualquier valor conteniso en el char
  resetReader(); // r e s e t e a r e l l e c t o r RFID
}

void enviartag ( char tag []){ 
  if(strlen(tag) == 0 ) 
    return ;
  if(client.connect(server,80)){ // puerto al que envira la peticion
    Serial.println("El␣Contenido␣del␣tag␣es␣");
    Serial.println(tag);
    client.print("GET␣/hospital/Arduino.php?tag="); // Envia los datos utilizando GET
    client.print(tag);
    client.println("HTTP/1.0") ;
    client.println("User!Agent : Arduino 1.0");
    client.println(); 
    Serial.println("Conexion exitosa");
    tag [11]= 0; 
    } else {
      Serial.println("Falla en la conexion");
    }
  if(client.connected()) {
    }
  else {
    Serial.println("Desconectado"); 
    }
  client.stop();
  client.flush();
  delay(1000); 
}
  
void resetReader(){
  digitalWrite(RFIDResetPin,LOW);
  digitalWrite(RFIDResetPin,HIGH) ;
  delay (150);
}
  
void clearTag ( char one [] ) {
  for(int i = 0; i< strlen(one); i++){
    one[i]=0;
    }
  }
}

#include <string.h>
#include <EEPROM.h>
// 1 поле - ID пакета
// 2 поле - контрольная сумма остальных полей
// 3 поле  -ID устройства
// 4 поле  -команда
// 5 поле  - данные
unsigned long time;
int ID=EEPROM.read(0);
String RXstring = "";
int STAT[]={0,0,0,0,0,0,0,0,0,0};
String CMD[7];
boolean RXline = false;
char  RXchar[30];
int retval;


void setup() {
  time=millis();
  Serial.begin(9600);
  String VID=eeprom_read(0,1);
  Serial.print("device ID is ");
  Serial.println(VID.toInt());
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  

}

void loop() {
 if (RXline) {
      int pt=1;
      int str_len = RXstring.length();
      char RXchar[str_len+1];
      RXstring.toCharArray(RXchar, str_len+1);
      char * pch;
      pch = strtok (RXchar,";");
      while (pch != NULL)
          {
        CMD[pt]=(String)pch;
        pch = strtok (NULL, ";");
        pt=pt+1;
        }
        
        if (CMD[3].toInt() == ID ) {
          int serpayload=(CMD[3].toInt()+CMD[4].toInt()+CMD[5].toInt());
          Serial.println(serpayload);
          if ( serpayload == CMD[2].toInt()) {
           Serial.print(CMD[1]);
           Serial.print(";");
           Serial.print(CMD[2]);
           Serial.print(";");
           Serial.print("1");
           Serial.println(";");
           exec();
           }
           else
           {
           Serial.print(CMD[1]);
           Serial.print(";");
           Serial.print(CMD[2]);
           Serial.print(";");
           Serial.print("2");
           Serial.println(";");
           }
           
        }
      
RXstring = "";
RXline = false;
 Serial.println("-------------------------"); 
 }

}



void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    RXstring += inChar;
    if (inChar == '\n') {
      RXstring.trim();
      RXline = true;
    }
  }
}

void exec() {
  Serial.println("command received");
  switch(CMD[4].toInt()) {
    case 0:
       STAT[CMD[5].toInt()]=0;
       Serial.println(CMD[5]+" off");
       digitalWrite(CMD[5].toInt(),HIGH);
       break;
    case 1:
      STAT[CMD[5].toInt()]=1;
      Serial.println(CMD[5]+" on");
      digitalWrite(CMD[5].toInt(),LOW);
      break;
    case 9:
       Serial.print("change ID from ");
      Serial.print(ID);
      Serial.print(" to ");
      ID=CMD[5].toInt();
      Serial.println(ID);
      EEPROM.write(0, ID); 
      break;
    }
    return 1;
}


String eeprom_read(int sector_start, int sector_len) {
  int ccount=0;
  String result="";
  while (sector_len > ccount) {
    byte Cell = EEPROM.read(sector_start+ccount);
    result=result += Cell;
    ccount +=1;
  }
  return result;
};

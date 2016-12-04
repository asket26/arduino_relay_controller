#include <string.h>
unsigned long time;
String ID="01";
String RXstring = "";
int STAT[]={0,0,0,0,0,0,0,0,0,0};
String CMD[7];
boolean RXline = false;
char  RXchar[30];
int retval;
void setup() {
  time=millis();
  Serial.begin(9600);
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
        if (CMD[1] == ID ) {
           exec();
        }
        Serial.print(ID+";");
        Serial.print(CMD[5]+";");
        Serial.println(str_len);
      
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
  if(CMD[2]=="2") {
    if(CMD[4]=="1") {
      STAT[CMD[3].toInt()]=1;
      Serial.println(CMD[3]+" on");
      digitalWrite(CMD[3].toInt(),LOW);
    }
    if(CMD[4]=="0") {
      STAT[CMD[3].toInt()]=0;
      Serial.println(CMD[3]+" off");
      digitalWrite(CMD[3].toInt(),HIGH);
    }
    }
  return 1;
}



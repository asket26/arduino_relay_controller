#include <string.h>
String ID="01";
String RXstring = "";
String CMD[5];
boolean RXline = false;
char  RXchar[30];
int retval;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  char MOD="OUTPUT";
  pinMode(2,MOD);
  digitalWrite(2,HIGH);
  pinMode(3,MOD);
  digitalWrite(3,HIGH);
  pinMode(4,MOD);
  digitalWrite(4,HIGH);
  pinMode(5,MOD);
  digitalWrite(5,HIGH);
  

}

void loop() {
  // put your main code here, to run repeatedly
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
        Serial.print(pt);
        Serial.print("    ");
        Serial.println(CMD[pt]);
        pch = strtok (NULL, ";");
        pt=pt+1;
        }
        if (CMD[1] == ID ) {
           exec();
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
  Serial.println("action..");
  if(CMD[2]=="2") {
    Serial.println("writing");
    if(CMD[4]=="1") {
      Serial.println("on");
      digitalWrite(CMD[3].toInt(),LOW);
    }
    if(CMD[4]=="0") {
      Serial.println("off");
      digitalWrite(CMD[3].toInt(),HIGH);
    }
    }
  return 1;
}


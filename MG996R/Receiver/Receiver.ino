#include <ESP32Servo.h>
#include <Ble.h>

#define SERVO_PIN 12
#define BUILTIN_LED_PIN 2

long prev_millis=millis();
int angle=0;

Servo servo;
Ble ble;
 
void setup()
{  
  ble.begin();
  pinMode(BUILTIN_LED_PIN,OUTPUT);
  servo.attach(SERVO_PIN);
  //Serial.begin(115200);  //debug
}
 
void loop()
{  
  if(ble.recvd()!=""){  //если с BT пришла команда
    delay(100);//debug
    String command_from_ble="";
    command_from_ble=ble.recvd();
    ble.clr();    
    if(command_from_ble.startsWith("a=")){
      command_from_ble.replace("a=", "");
      angle=(signed int)command_from_ble.toInt();
      servo.write(angle);
    }    
  }
  

  if(millis()>prev_millis+500){
    digitalWrite(BUILTIN_LED_PIN,!digitalRead(BUILTIN_LED_PIN));
    prev_millis=millis();
  }
    
}
 

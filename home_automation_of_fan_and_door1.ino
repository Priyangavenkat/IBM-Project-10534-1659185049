//home automation
//
#include<Servo.h>
#define outsens 2
#define insens 5
#define buzzer 3
#define shutter 4
#define tablefan 9
#define tempsens A0
#define LED 7

int trival=6;
int sound=7;
float time_ms, dist_cm;
Servo Myservo;
void setup()
{
  pinMode(outsens, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(insens, INPUT);
  Myservo.attach(4);
  pinMode(tablefan,OUTPUT);
  Serial.begin(9600);
  pinMode(trival, OUTPUT);
  pinMode(sound, INPUT);
  
}

void loop()
{
  
  //out shutter
  if(digitalRead(outsens)==0)
  {
    digitalWrite(buzzer,0);  
  }
  else
  {
    digitalWrite(buzzer,1);  
    delay(500);
    digitalWrite(buzzer,0);  
  }
  //in shutter
  
  digitalWrite(trival, HIGH);
  delay(100);
  digitalWrite(trival, LOW);
  time_ms = pulseIn(sound, HIGH);
  dist_cm = 0.012 * time_ms;
  Serial.print("dist_cm:");
  Serial.print(dist_cm);
  Serial.println("cm");
  delay(1000);
  
   if(dist_cm>90)
   {   
    Myservo.write(0); 
  }
  else
  
  {
    Myservo.write(90);            
  }
    int val = analogRead(tempsens);
    val = map(val, 20,358, 0,1000);
  
  if(val<=100)
  {
    analogWrite(tablefan ,0);
  }
  else if(val<=500)
  {
    analogWrite(tablefan ,val);
  }
  else
  {
    analogWrite(tablefan ,0);
    digitalWrite(buzzer,1);  
      delay(500);
    digitalWrite(buzzer,0); 
      delay(200);
    digitalWrite(LED,HIGH);
  }
  
  Serial.println(val);
}
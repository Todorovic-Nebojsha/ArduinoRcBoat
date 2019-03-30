#include "IRremote.h"
#include<Servo.h>
// najlev pin minus , sredishan +, najdesan ide na 11 zaradi citanje na podatoci !!! relay info
//servo 8 pin mu e output od arduino, zuta boja, crna e minus GND, crvena e plus 5V
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11, remote codes info
long oldValue;
/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
Servo servo;


int motor1=12;
int led=4;
int sensorPin=7;

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  servo.attach(8);
  servo.write(90);
  pinMode(motor1,OUTPUT);
  // HIGH STOI A LOW VRTI 
  digitalWrite(motor1,HIGH);
   pinMode(led,OUTPUT);
   pinMode(sensorPin,INPUT);
  delay(2000);

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  //Serial.println("LOOP");
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  } 
  else{
    digitalWrite(motor1,HIGH);
  }
 // digitalWrite(led,HIGH);
  int val=digitalRead(sensorPin);
    if(val==1){
    digitalWrite(led,LOW); 
    Serial.println(val);
    }
    else{
    digitalWrite(led,HIGH);
    }
  val=0;
}/* --(end main loop )-- */

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{
  //Serial.println(results.value);
  long val=results.value;
  int flag=0;
  Serial.print(val);
  Serial.print(" OLD VALUE:");
  Serial.print(oldValue);
  Serial.println("");

  switch(val)
  {
  case -1:
              Serial.println("ULAZA KAKO STO TREBA");
              flag=1;
              break;
  case 16718055: 
                Serial.println(" FORWARD");  
                oldValue=val; 
                servo.write(90);  
                digitalWrite(motor1,LOW); 
                break;
  
  case 16716015: 
                Serial.println(" LEFT");
                oldValue=val; 
                servo.write(10); 
                digitalWrite(motor1,LOW);
                break;
  case 16726215:
                Serial.println(" -OK-");
                oldValue=val;
                digitalWrite(motor1,HIGH);
                break;
  case 16734885:
                Serial.println(" RIGHT");
                oldValue=val;
                servo.write(170);
                digitalWrite(motor1,LOW); 
                break;
  case 16730805:
                Serial.println(" REVERSE");
                oldValue=val;
                 digitalWrite(motor1,HIGH);
                break;
  //case 4294967295: Serial.println(" LONG PRESSED");   break;
  
  default: 
    digitalWrite(motor1,HIGH);
    Serial.println(val);
    
   // Serial.println(" other button   ");

  }// End Case
  
  if(flag==1){
    Serial.println(oldValue);
        switch(oldValue)
        {
            case 16718055: 
                          Serial.println(" FORWARD");  
                          servo.write(90); 
                          digitalWrite(motor1,LOW);  
                          break;
            
            case 16716015: 
                          Serial.println(" LEFT");
                          servo.write(10); 
                          digitalWrite(motor1,LOW);
                          break;
            case 16726215:
                          Serial.println(" -OK-");
                          digitalWrite(motor1,HIGH);
                          break;
            case 16734885:
                          Serial.println(" RIGHT");
                          servo.write(170);
                          digitalWrite(motor1,LOW); 
                          break;
            case 16730805:
                          Serial.println(" REVERSE");
                          digitalWrite(motor1,HIGH);
                          break;
            //case 4294967295: Serial.println(" LONG PRESSED");   break;
            
            default: 
              //Serial.println(val);
              digitalWrite(motor1,HIGH);
              Serial.println(" other button   ");

        }
  }
  delay(700); // Do not get immediate repeat


} 

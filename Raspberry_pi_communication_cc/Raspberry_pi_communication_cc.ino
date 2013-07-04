#include <Wire.h>
#include <Servo.h>

//initalise servo
Servo myservo;
int pos = 0;

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
int ledPins[] = {2,3,4,5,6,7,8};


void setup() {
  myservo.attach(9); //attach the servo to pin 9
   for(int i = 0; i < 7; i++){ 
   pinMode(ledPins[i], OUTPUT); } //set the LED Pins to output
   
    Serial.begin(9600);         // start serial for output
    // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

    // define callbacks for i2c communication
    

    Serial.println("Ready!");
}

void loop() {
  Wire.onReceive(receiveData); //define how the arduino should respond to receiving Data
    Wire.onRequest(sendData);
  digitalWrite(1,HIGH);
  delay(500);
  digitalWrite(1,LOW);
    delay(100);
}

// callback for received data
void receiveData(int byteCount){

    while(Wire.available()) {
        number = Wire.read(); //read the byte sent by the pi
               
        Serial.print("data received: ");
        Serial.println(number);
        int pn = number -1; //This part is just toggling the LEDs or instructing the servo.
        if ( number < 8) { 
          if (digitalRead(ledPins[pn]) == 0) { digitalWrite(ledPins[pn],HIGH); }
           else { digitalWrite(ledPins[pn], LOW);} }
        else { myservo.write(number);}
}
}

// callback for sending data
void sendData(){
    Wire.write(number);
}

void oneAfterAnotherLoop(){
  int delayTime = 3000; //the time (in milliseconds) to pause between LEDs
                       //make smaller for quicker switching and larger for slower

//Turn Each LED on one after another
  for(int i = 0; i <= 7; i++){
    digitalWrite(ledPins[i], HIGH);  //Turns on LED #i each time this runs i
    delay(delayTime);                //gets one added to it so this will repeat 
  }                                  //8 times the first time i will = 0 the final
                                     //time i will equal 7;

//Turn Each LED off one after another
  for(int i = 7; i >= 0; i--){  //same as above but rather than starting at 0 and counting up
                                //we start at seven and count down
    digitalWrite(ledPins[i], LOW);  //Turns off LED #i each time this runs i
    delay(delayTime);                //gets one subtracted from it so this will repeat 
  }                                  //8 times the first time i will = 7 the final
                                     //time i will equal 0;                                     
                                     
}

void oneB4Loop(){
  int delayTime = 3000; //the time (in milliseconds) to pause between LEDs
                       //make smaller for quicker switching and larger for slower

//Turn Each LED on one after another
  for(int i = 7; i >=0; i--){
    digitalWrite(ledPins[i], HIGH);  //Turns on LED #i each time this runs i
    delay(delayTime);                //gets one added to it so this will repeat 
  }                                  //8 times the first time i will = 0 the final
                                     //time i will equal 7;

//Turn Each LED off one after another
  for(int i = 0; i <= 7; i++){  //same as above but rather than starting at 0 and counting up
                                //we start at seven and count down
    digitalWrite(ledPins[i], LOW);  //Turns off LED #i each time this runs i
    delay(delayTime);                //gets one subtracted from it so this will repeat 
  }                                  //8 times the first time i will = 7 the final
}


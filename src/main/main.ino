//Specify digital pin on the Arduino that the positive lead of piezo buzzer is attached.
int piezoPin = 8;
int buttonPin = 7; 

int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
int buttonState = 0;
int flag=0;

/*
Get mode value from server
mode = 0: OFF alarm mode
mode = 1: ON alarm mode
*/
int mode = 0;
 
void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(buttonPin, INPUT_PULLUP); 
  Serial.begin(9600);        // initialize serial
}
 
void loop() {
  val = digitalRead(sensor); // read sensor value

  //Read button state (pressed or not pressed?)
  buttonState = digitalRead(buttonPin);

  //If button pressed...
  if (buttonState == LOW) { 
    //...ones, control LIGHT
    if ( flag == 1){
      Serial.println("Controling LIGHT...");
      flag=0; //change flag variable
    }
    //...twice, control ALARM
    else if ( flag == 0){
      Serial.println("Controling ALARM...");
      tone(piezoPin, 1000, 1000);
      val = LOW;
      delay(20000);
      flag=1; //change flag variable again 
    }    
  }

  if (flag == 0){
    controlLight(val); //Initial state is controling light
  }
  else {
    controlAlarm(val);  //Press the button to switch to Security Mode
  }
  delay(200); //Small delay
}

void controlAlarm(int val) {
  digitalWrite(led, LOW); // turn LED OFF
  if (val == HIGH) {
    /*Tone needs 2 arguments, but can take three
      1) Pin#
      2) Frequency - this is in hertz (cycles per second) which determines the pitch of the noise made
      3) Duration - how long teh tone plays
    */
    tone(piezoPin, 500, 200); //Alarming
    digitalWrite(led, HIGH); // turn LED ON
    
    if (state == LOW) {
      Serial.println("WARNING! Sending email...");
      Serial.flush();
      sendEmail(); 
      state = HIGH;       // update variable state to HIGH
    }
  }
  else{
    if (state == HIGH){
      Serial.println("Motion stopped!");
      //delay(5000);        //because the sensor is too sensitive
      state = LOW;       // update variable state to LOW
    }
  }
}

void sendEmail() {
  Serial.println(";");
}
void controlLight(int val) {
  if (val == HIGH) {          // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 

    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  }
  else {
    digitalWrite(led, LOW); // turn LED OFF
    delay(200);             // delay 200 milliseconds

    if (state == HIGH){
      Serial.println("Motion stopped!");
      state = LOW;       // update variable state to LOW
    }
  }
}

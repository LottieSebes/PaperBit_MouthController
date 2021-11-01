//CODE FOR THE RELATION BETWEEN A SENSOR AND AN ANALOGUE (VOLTAGE) OUTPUT

//int value (0, 256); //put the values you're getting from the sensor inside the brackets - lowest number, highest number

//Thresholds
int BACKGROUND_HUMIDITY = 420; // allows for calibration depending on humidity in the air
int CONSTRAIN_MINIMUM = 1;
int UPDATE_DELAY = 100; //allows  me to update the delay time easily - this can bring about some nice sonic varietry between discrete and gradual change 

void setup() {
  // put your setup code here, to run once:
  TCCR0B = TCCR0B &0b11111000 | 0x01; //you need this line of code if you are using Analog write and you want to do audio with it. Be careful though, this messes with your timer 

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
 
  long valueHumidity = analogRead(A1); //read humidity sensor. 10 bit (between 0 and 1023)
 // Serial.println("Humidity");
  //Serial.println(valueHumidity);

   valueHumidity = map(valueHumidity, BACKGROUND_HUMIDITY, 850, 0, 1023); //maximizing impact of effective range of humidity sensor 
  //Serial.println(valueHumidity);
  
  long valueLight = analogRead(A2); //read LDR. 10 bit (between 0 and 1023)
   //Serial.println("LDR");  
  //Serial.println(valueLight); 

  valueLight = map(valueLight, 0, 1023, 0, 800); 
   //Serial.println(valueLight); 

  long output6 = (valueHumidity*valueLight)/1024; // multiplies the LDR values by the humidity sensor values
  //Serial.println("Preconstrained output6");
  //Serial.println(output6);
 
  long valuePressure = analogRead(A0); //read air pressure sensor. 10 bit (between 0 and 1023)
  // print out the value you read:
  //Serial.println("AirPressure");
  //Serial.println(valuePressure);

  output6 = constrain(map(output6, 0, 1023, 0, 255), CONSTRAIN_MINIMUM, 255); //maps 10 bit to 8 bit of HS x LDR
  
  valuePressure = constrain(map(valuePressure, 0, 1023, 0, 256), 0, 256); //maps 10 bit to 8 bit of air pressure sensor
  // Serial.println("Preconstrained output7");
  // Serial.println(valuePressure);

  // Serial.println("output6");
  // Serial.println(output6);
  // Serial.println("output5");
  // Serial.println(valuePressure);

  analogWrite(6, output6); // output 8 bit value (between 0 and 256) combined from LDR and humidity sensor
  
  analogWrite(5, valuePressure); // output 8 bit value (between 0 and 256) from air pressure sensor

  delay(100);        // delay in between reads for stability/flow
}

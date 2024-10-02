#define pot1 A0
#define pot2 A1
#define pot3 A2
int redPin=5;
int greenPin=6;
int bluePin=7;

void setup() {

  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(pot1,INPUT);
  pinMode(pot2,INPUT);
  pinMode(pot3,INPUT);

}

void loop() {
  int pot1Value=analogRead(pot1);
  int pot2Value=analogRead(pot2);
  int pot3Value=analogRead(pot3);

  int value1=map(pot1Value,0,1023,0,255);
  int value2=map(pot2Value,0,1023,0,255);
  int value3=map(pot3Value,0,1023,0,255);

  Serial.print("Pot1 value: ");
  Serial.println(value1);

  Serial.print("Pot2 value: ");
  Serial.println(value2);  
  
  Serial.print("Pot3 value: ");
  Serial.println(value3);

  delay(100);
  setColor(value1,value2,value3);
  delay(400);  
  /*
  setColor(255, 0, 0); // Red Color
  delay(1000);
  setColor(0, 255, 0); // Green Color
  delay(1000);
  setColor(0, 0, 255); // Blue Color
  delay(1000);
  setColor(255, 255, 255); // White Color
  delay(1000);
  setColor(170, 0, 255); // Purple Color
  delay(1000);
*/

}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

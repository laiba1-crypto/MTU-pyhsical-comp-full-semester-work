int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
const int LED_PIN = 13;
void setup() {
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, HIGH);
 for(int pinNumber = 4; pinNumber < 7; pinNumber++)
{
  pinMode(pinNumber,OUTPUT);
  digitalWrite(pinNumber, LOW);
}
// open a serial connection to display values
Serial.begin(9600);
// calibrate for the first five seconds after program runs
while (millis() < 5000) {
sensorValue = analogRead(A0);
if (sensorValue > sensorHigh) {
sensorHigh = sensorValue;
}
if (sensorValue < sensorLow) {
sensorLow = sensorValue;
}
}
// turn the LED off, signaling the end of the calibration period
digitalWrite(LED_PIN, LOW);
}
void loop() {
sensorValue = analogRead(A0);
Serial.print(sensorValue);
float voltage = (sensorValue/1023.0)*5.0;
float R = (4700)/(5-voltage);
Serial.print(R);
// map the sensor values to a wide range of pitches
int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);
//D4 = Red RED2
//D5 = Green GRN2
//D6 = Amber AMB
if(pitch <=1000)
{
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}
else if (pitch > 1000 && pitch <=2000)
{
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
}
else if (pitch > 2000 && pitch <=3000)
{
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
}
else 
{
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
}
// play the tone for 20 ms on pin 8
tone(8, pitch, 20);
// wait for 10 ms to give sound time to play
delay(10);
}

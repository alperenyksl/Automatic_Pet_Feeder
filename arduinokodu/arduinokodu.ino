#include <Servo.h>
#include <SoftwareSerial.h>

Servo sg90_servo;
Servo sg90_servo_bluetooth;
int buzzerPin = 11; // Buzzer
int ledPin = 12;    // LED

#define RX_PIN 0 // Bluetooth RX 
#define TX_PIN 1 // Bluetooth TX

SoftwareSerial BTSerial(RX_PIN, TX_PIN); // RX, TX tanımla

bool servo180 = false; // Servo motorunun başlangıç pozisyonu 0 derecede olacak

void setup()
{
  sg90_servo.attach(9); // 9 numaralı pine bağlı servo motoru başlat
  sg90_servo_bluetooth.attach(10); // 10 numaralı pine bağlı servo motoru başlat
  pinMode(buzzerPin, OUTPUT); // Buzzer pinini çıkış olarak ayarla
  pinMode(ledPin, OUTPUT);    // LED pinini çıkış olarak ayarla
  Serial.begin(9600);        
  BTSerial.begin(9600);       
}

void moveServo(Servo &servo, int targetAngle)
{
  int currentAngle = servo.read();
  if (currentAngle < targetAngle)
  {
    for (int angle = currentAngle; angle <= targetAngle; angle++)
    {
      servo.write(angle);
      delay(30);
    }
  }
  else
  {
    for (int angle = currentAngle; angle >= targetAngle; angle--)
    {
      servo.write(angle);
      delay(30);
    }
  }
}

void loop()
{
  // Bluetooth ile servo kontrolü
  while (Serial.available() > 0)
  {
    char komut = Serial.read();
    if (komut == '1')
    {
      if (sg90_servo_bluetooth.read() == 180)
      {                   
        moveServo(sg90_servo_bluetooth, 0);
      }
      else
      { 
        moveServo(sg90_servo_bluetooth, 180);
      }
    }
    else if (komut == '0')
    {
      if (servo180)
      {
        moveServo(sg90_servo_bluetooth, 0);
        servo180 = false; 
      }
      else
      {
        moveServo(sg90_servo_bluetooth, 180); 
        servo180 = true; 
      }
    }
  }

  if (BTSerial.available())
  {
    char receivedChar = BTSerial.read();
    Serial.println(receivedChar);        
  }

  delay(1000);
}
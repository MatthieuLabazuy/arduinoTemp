#include <SimpleDHT.h>
#include <LiquidCrystal.h>

int pinDHT11 = 5;
int pinAnalogTherm = A0;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal lcd(7,8,9,10,11,12);

void setup() {
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.print("Bienvenue !");
  delay(2000);
  lcd.clear();
}

void loop() {  
  // read without samples.
  byte temperatureDHT11 = 0;
  int temperatureAnalog = analogRead(pinAnalogTherm);
  double tempK = log(10000.0 * ((1024.0/temperatureAnalog -1)));
  tempK = 1/(0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK))*tempK);
  float tempC = tempK - 273.15;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  lcd.setCursor(0,1);
  if ((err = dht11.read(&temperatureDHT11, &humidity, NULL)) != SimpleDHTErrSuccess) {
    lcd.print("Read DHT11 fail"); 
    lcd.setCursor(1,1);
    lcd.print("Error : "); lcd.print(err); delay(1000);
    return;
  }
  lcd.setCursor(0,0);
  lcd.print("Td:   *C  H:   %");
  lcd.setCursor(0,1);
  lcd.print("Ta:      *C");
  lcd.setCursor(4,0);
  lcd.print((int)temperatureDHT11);
  lcd.setCursor(13,0);
  lcd.print((int)humidity);
  lcd.setCursor (4,1);
  lcd.print((float)tempC);
  
  // DHT11 sampling rate is 1HZ.
  delay(1000);
}

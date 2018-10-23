#include <SimpleDHT.h>
#include <LiquidCrystal.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 5;
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
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  lcd.setCursor(0,1);
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    lcd.print("Read DHT11 fail"); 
    lcd.setCursor(1,1);
    lcd.print("Error : "); lcd.print(err); delay(1000);
    return;
  }
  lcd.setCursor(0,0);
  lcd.print("Temp: ");lcd.print((int)temperature); lcd.print(" *C, "); 
  lcd.setCursor(0,1);
  lcd.print("Humi: ");lcd.print((int)humidity); lcd.print(" H");
  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
}

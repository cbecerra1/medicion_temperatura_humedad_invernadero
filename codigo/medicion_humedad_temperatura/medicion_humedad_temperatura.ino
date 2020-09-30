// librería para LCD1602 (LCD 16 caracteres 2 líneas) con módulo I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// definimos el objeto lcd
// en la dirección 0x27, le especificamos que son 16 caracteres y 2 líneas
LiquidCrystal_I2C lcd(0x27, 16, 2);

//libreria DHT sensor library Adafruit
#include "DHT.h" 

#define DHTPIN 2     // pin usado para recibir la medición
#define DHTTYPE DHT22   // impirtante verificar que sea el sensor que estamos usando
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Declaro las variables
int BuenaH = 3; //Led verde
int AltaH = 4; //Led Rojo
int BajaH = 5; //Led Amarillo

void setup() {
  // put your setup code here, to run once:
  //Asignamos el led como una salida
  //pinMode solo se utiliza para pines digitales
  pinMode(BuenaH,OUTPUT); 
  pinMode(AltaH,OUTPUT);
  pinMode(BajaH,OUTPUT);
  
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Inicializamos el sensor DHT
  dht.begin();

  // Inicializamos el LCD,
  lcd.begin();
  lcd.setBacklight(HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Esperamos 2 segundos entre cada medida del sensor
  delay(2000);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  //mensajes LCD
  lcd.clear(); // limpiamos LCD
  
  lcd.setCursor (0, 0); // vamos al inicio de la linea 1
  lcd.print("Humedad: ");
  lcd.print(h);
  
  lcd.setCursor (0, 1); // vamos al inicio de la linea 2
  lcd.print("Temp: ");
  lcd.print(t);
  
  //mensajes Serial 
  Serial.println("Humedad: ");
  Serial.println(h);
  Serial.print(" %\t");
  Serial.println("Temperatura: ");
  Serial.println(t);
  Serial.print(" *C ");

  //Para saber si la humedad se encuentra en rangos optimos
  //Prendemos los leds
  if((h >= 60) && (h<=70)) {
    //Buena humedad
    //Prende led verde
    digitalWrite(BuenaH, HIGH);
    digitalWrite(AltaH, LOW);
    digitalWrite(BajaH, LOW);
  }

  else if (h > 70) {
    //Alta humedad
    //Prende led rojo
    digitalWrite(BuenaH, LOW);
    digitalWrite(AltaH, HIGH);
    digitalWrite(BajaH, LOW);
  }
    
  else {
    //baja humedad
    //Prende led amarillo
   digitalWrite(BuenaH, LOW);
    digitalWrite(AltaH, LOW);
    digitalWrite(BajaH, HIGH);
  }
    
}

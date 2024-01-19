#include <HTTPClient.h>
#include <WiFi.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

#include <ESP32Servo.h>
#define DS18B20  15
#define ON_Board_LED 2
#define LED_D8 13
#define LED_D12 12

Servo myservo; 

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Instacia o Objeto oneWire e Seta o pino do Sensor para iniciar as leituras
OneWire oneWire(DS18B20);

//Repassa as referencias do oneWire para o Sensor Dallas (DS18B20)
DallasTemperature Sensor(&oneWire);

// Variavel para Armazenar os dados de Leitura Temperatura
float leitura;

//Sensor pH
const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;

int buf[10],temp=0;

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 26;

String URL1 = "http://192.168.158.170/Demo_2/sensorPH.php";
String URL = "http://192.168.158.170/Demo_2/temperatura.php";
const char* ssid = "onildo";
const char* password = "00001111";
const char* host = "http://192.168.158.170";

void setup() {
  lcd.init();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("Ola, ESP32!");
        lcd.setCursor(0, 1);
        lcd.print("Marraca, Onildo!");
  // Inicia a Serial
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); 
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH);
  
  pinMode(LED_D12,OUTPUT);
  digitalWrite(LED_D12, LOW);
  pinMode(LED_D8,OUTPUT);
  digitalWrite(LED_D8, LOW); 

  //----------------------------------------Esperando a conexao wi-fi
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);


      // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400);
    
  }

  digitalWrite(ON_Board_LED, HIGH); 
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------

  // Inicia o Sensor
  Sensor.begin();
  lcd.clear();
}

void acionarAlimentador() {
  HTTPClient http;
  String GetAddress, LinkGet, getData;
  int id = 0; //--> ID in Database
  int Stat;
  GetAddress = "/Demo_2/GetData_Alimentador.php"; 
  LinkGet = host + GetAddress; 
  getData = "ID=" + String(id);
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Get LED Status from Server or Database");
  Serial.print("Request Link : ");
  Serial.println(LinkGet);
  http.begin(LinkGet); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    
  int httpCodeGet = http.POST(getData); 
  String payloadGet = http.getString(); 
  Serial.print("Response Code : ");  
  Serial.println(httpCodeGet); 
  Serial.print("Returned data from Server : ");
  Serial.println(payloadGet); 

  if (payloadGet == "1") {
    Serial.println("Alimentador acionado com sucesso");
    digitalWrite(LED_D8, HIGH);

    unsigned long startTime = millis(); // marca o início do tempo

    while (millis() - startTime <= 5000) {  // executa por 5 segundos
      for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(15);
      }
      for (pos = 180; pos >= 0; pos -= 1) {
        myservo.write(pos);
        delay(15);
      }
    }   
  }
  if (payloadGet == "0") {
    Serial.println("Alimentador Desligado");
    digitalWrite(LED_D8, LOW); 
  }
  http.end();
}

 void acionarBomba(){
  HTTPClient http;
  String GetAddress, LinkGet, getData;
  int id = 0; 
  GetAddress = "/Demo_2/GetData.php"; 
  LinkGet = host + GetAddress; 
  getData = "ID=" + String(id);
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Get LED Status from Server or Database");
  Serial.print("Request Link : ");
  Serial.println(LinkGet);
  http.begin(LinkGet); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    
  int httpCodeGet = http.POST(getData); 
  String payloadGet = http.getString(); 
  Serial.print("Response Code : "); 
  Serial.println(httpCodeGet); 
  Serial.print("Returned data from Server : ");
  Serial.println(payloadGet);

  if (payloadGet == "1") {
    digitalWrite(LED_D12, HIGH);
     Serial.println("Bomba acionada com sucesso");
  }
  if (payloadGet == "0") {
   digitalWrite(LED_D12, LOW);
   Serial.println("Bomba desligada!");
  }
  http.end();
}


void sensorpH(){

  for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 
 float pHVol=(float)avgValue*5.0/1024/4.3;
 //float phValue = -5.70 * pHVol +29.5 ;
 float phValue = -3.0 * pHVol+17.5;
  phValue=10.5-phValue;
 Serial.print("sensor = ");
 Serial.println(phValue);
 delay(1000);

     
      lcd.setCursor(0,1);
      lcd.print("pH: ");
      lcd.print(phValue);
      


 String postData = "pH=" + String(phValue);
  
  HTTPClient http;
  http.begin(URL1);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.print("URL : "); Serial.println(URL1); 
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload : "); Serial.println(payload);
  Serial.println("--------------------------------------------------");
  delay(5000);
      
  
  }





void sensorTemperatura(){
  
// Leitura do Sensor  DS18B20  //////////////
  Sensor.requestTemperatures();

  // Armazerna na variavel o valor da Leitura
  leitura = Sensor.getTempCByIndex(0);


 // Imprime na Tela a Leitura
  Serial.println("--------------------------------------");
  Serial.println("Temperatura: ");
  Serial.print(leitura);
  Serial.println("ºC"); 
  Serial.println("--------------------------------------"); 
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(leitura);
      lcd.print(" C");
      delay(3000);


 String postData = "temperatura=" + String(leitura);
  
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData);
  String payload = http.getString();

  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData);
  Serial.print("httpCode: "); Serial.println(httpCode);
  Serial.print("payload : "); Serial.println(payload);
  Serial.println("--------------------------------------------------");
  delay(5000);
      
  
  }



void loop() {

  sensorpH();
 
  sensorTemperatura();
  // Acionar o alimentador
  acionarAlimentador();
  delay(1000);

  // Acionar a bomba
  acionarBomba();
  delay(1000); 
}

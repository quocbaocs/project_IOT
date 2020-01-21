/*********
Nhom Sinh Vien: DHKHMT 11A
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
// Tai thu vien Adafruit
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define D3 5 // GPIO5
#define D4 4 // GPIO4
#define D5 14 // GPIO0
#define D6 12 // GPIO2
#define D7 13 // GPIO14

// Replace with your network credentials
const char* ssid     = "IoT";
const char* password = "hoangdinh";

//IPAddress staticIP(192,168,0,100);
//IPAddress gateway(192,168,0,1);
//IPAddress subnet(255,255,255,0);

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header, Request;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "khanhhuyenconse"
#define AIO_KEY  "3ce30416355a48ce81a13524ac74bef2"
WiFiClient client;


// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output14State = "off";
String output13State = "off";
String output12State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;
const int output14 = 14;
const int output12 = 12;
const int output13 = 13;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe automation = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/automation");

boolean MQTT_connect();

boolean MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return true;
  }  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(2000);
    retries--;
    if (retries == 0) {
      return false;
    }
  } return true;
}

void setup() {
  Serial.begin(115200);
  Request = "";

  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output14, OUTPUT);
  pinMode(output12, OUTPUT);
  pinMode(output13, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output14, LOW);
  digitalWrite(output12, LOW);
  digitalWrite(output13, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  //WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected... Let's go :)))))");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Ket noi theo phuong thuc MQTT
  mqtt.subscribe(&automation);
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Lang nghe hanh dong den tu client

  if (client) {                             // Neu 1 client duoc ket noi,
    Serial.println("Client moi.");          // Xuat 1 thong diem serial port monitor
    String currentLine = "";                // Tạo mot bien String de luu giu thong diep duoc gui den tu client 
    while (client.connected()) {            // Trong khi client's da ket noi
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            } else if (header.indexOf("GET /14/on") >= 0) {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, HIGH);
            } else if (header.indexOf("GET /14/off") >= 0) {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, LOW);
            } else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            } else if (header.indexOf("GET /13/on") >= 0) {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, HIGH);
            } else if (header.indexOf("GET /13/off") >= 0) {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><meta charset=\"utf-8\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println(".hinhnen {background-color:#c9e7f9;}</style></head>");
            
            
            // Web Page Heading
            client.println("<body class = \"hinhnen\"><h1 style = \"color: \"#FF0000\"\">Điều khiển thiết bị với ESP8266 Webserver</h1>");
            
            // Hien thi trang thai hien tai và nút ON/OFF cho cổng GPIO 5  
            client.println("<p>Đèn phòng khách đang: " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Hien thi trang thai hien tai và nút ON/OFF cho cổng GPIO 4  
            client.println("<p>Đèn phòng bếp đang: " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

             // Hien thi trang thai hien tai và nút ON/OFF cho cổng GPIO 14  
            client.println("<p>Đèn phòng ngủ 1 đang: " + output14State + "</p>");
            // If the output14State is off, it displays the ON button       
            if (output14State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

             // Hien thi trang thai hien tai và nút ON/OFF cho cổng GPIO 12  
            client.println("<p>Đèn phòng ngủ 2 đang: " + output12State + "</p>");
            // If the output12State is off, it displays the ON button       
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

             // Hien thi trang thai hien tai và nút ON/OFF cho cổng GPIO 13  
            client.println("<p>Đèn toilet đang: " + output13State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            }



            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  else if (MQTT_connect()) {
    Adafruit_MQTT_Subscribe *subscription_name;
    while ((subscription_name = mqtt.readSubscription(1000))) {
      if (subscription_name == &automation) {
        Request = ((char *)automation.lastread);

         if(Request!=""){
          Serial.println('Ten ten!!!!');
          for (int i=0; i<Request.length(); i++){
            
            if(Request[i] == ' '){
              Request.remove(i, 1);
              i--;
              }
            }
          }

        Serial.println(Request);
        if (Request == "d1on") {
          digitalWrite(D3, HIGH);
          Serial.println("Den phong khach sang");
        }
        if (Request == "d1off") {
          digitalWrite(D3, LOW);
          Serial.println("Den phong khach tat");
        }

        if (Request == "d2on") {
          digitalWrite(D4, HIGH);
          Serial.println("Den phong bep sang");
        }
        if (Request == "d2off") {
          digitalWrite(D4, LOW);
          Serial.println("Den phong bep tat");
        }

        if (Request == "d3on") {
          digitalWrite(D5, HIGH);
          Serial.println("Den phong ngu 1 sang");
        }
        if (Request == "d3off") {
          digitalWrite(D5, LOW);
          Serial.println("Den phong ngu 1 tat");
        }

         if (Request == "d4on") {
          digitalWrite(D6, HIGH);
          Serial.println("Den phong ngu 2 sang");
        }
        if (Request == "d4off") {
          digitalWrite(D6, LOW);
          Serial.println("Den phong ngu 2 tat");
        }

         if (Request == "d5on") {
          digitalWrite(D7, HIGH);
          Serial.println("Den nha ve sinh sang");
        }
        if (Request == "d5off") {
          digitalWrite(D7, LOW);
          Serial.println("Den nha ve sinh tat");
        }

      }

    }

  }
}

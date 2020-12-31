/* -- Headerdateien -- */
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>     
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

/* -- Defines -- */
#define NB_TRYWIFI 10             //Verbindungsversuche zum Netzwerk
#define PIN 15                    //Output Pin 
#define NUMPIXELS 97              //Anzahl Pixels
#define AnalogPin A0              //Analog Pin
#define interruptPin 2            //Interrupt Pin D4

/* -- Variablen -- */
String header;                    //Hier wird die Response vom Webserver gespeichert
int h_aus = -1, min_aus = -1;     //Uhrzeit ab der der Nachtmodus aktiv ist
int red=255, blue=255, green=255; //Default Werte für die Farbe der LEDs
String textcolor = "white";       //Default Werte für die Farbe der Schrift
int helligkeit = 100;             //Helligkeit der Pixels
int stunde, minute, sekunde;      //Stunde und Minute vom NTP
unsigned int offset_stunde = 0;                
volatile byte interruptCounter = 0;



WiFiServer server(80);            //Setzt neuen server an Port 80
WiFiUDP ntpUDP;                   //Setzt ntp UDP auf
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//NTPClient timeClient(Name WiFiUDP Client, "Serveradresse", Offset[s] , Aktualisierungsintervall[ms]);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);
  //pinMode(AnalogPin, INPUT); 
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(helligkeit);
  pixels.clear();
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.autoConnect("Wortuhr Konfiguration");
  WiFi.hostname("wortuhs");
  server.begin();
  timeClient.begin();


  
}

void loop() {

    timeClient.update();
    //delay(500);


 if(interruptCounter>0){
      delay(700);   
      offset_stunde++;
      if(offset_stunde == 12)
      {
        offset_stunde =0;
      }
      //Serial.print("Uhrzeit: ");
      //Serial.println(offset_stunde+stunde);
      interruptCounter--;
  }
    
    String stime = timeClient.getFormattedTime(); //speichert die Zeit im String im Format hh:mm:ss
    stunde = (stime.substring(0,2)).toInt();   //Schneidet die Stelle 0 bis 2 von sTime raus und typcastet nach int
    minute = (stime.substring(3,5)).toInt();    //Schneidet die Stelle 3 bis 5 von sTime raus und typcastet nach int
    sekunde = (stime.substring(6,8)).toInt();  //Schneidet die Stelle 6 bis 8 von sTime raus und typcastet nach int
    int stunde2 = stunde + offset_stunde;
    zeigeZeit(stunde2,minute);                 //Diese Funktion schaltet die LEDs für die Anzeige   
 
  WiFiClient client = server.available();   // Listen for incoming clients
  IPAddress ip = WiFi.localIP();
  
if (client){                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0){

client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Access-Control-Allow-Origin: * ");
client.println("Connection: close");
client.println();


        if(header.startsWith("GET /api/get_rgb"))
        {
          client.println(rgbToJSON(red,green,blue,helligkeit));
        }
        if(header.startsWith("GET /api/set_rgb"))
        {
        red = header.substring(19,22).toInt()-100;
        green = header.substring(25,28).toInt()-100;
        blue = header.substring(31,34).toInt()-100;
        helligkeit = header.substring(38,41).toInt()-100;
        Serial.println(helligkeit);
        client.println(rgbToJSON(red,green,blue,helligkeit));
        

        if(red >= 0 && red <= 255 && green >= 0) //usw....
        client.println("1");
        else
        client.println("0"); 
        }
        

            
            
if(header.startsWith("GET /pix"))
{
        red = header.substring(20,23).toInt()-100;
        green = header.substring(26,29).toInt()-100;
        blue = header.substring(32,35).toInt()-100; 
        helligkeit = header.substring(39,42).toInt()-100; //liest hier 0 aus und ausgabe dann -100 = -100
        pixels.setBrightness(helligkeit);
        Serial.print("Helligkeit auf: ");
        Serial.println(helligkeit);
        Serial.println("");
}
String rgb = "rgb(" + String(red) + "," + String(green) + "," + String(blue) + ");"; 
        
        if(header.startsWith("GET /uhrzeit"))
        {
          h_aus = header.substring(21,23).toInt();
          min_aus = header.substring(26,28).toInt();
          Serial.println(h_aus);
          Serial.println(min_aus); 
          pixels.clear();     
          int i = 0;
      while(i < 20){   
         pixels.setPixelColor(114,pixels.Color(255,0,0));
         pixels.setPixelColor(111,pixels.Color(0,255,0));
         pixels.setPixelColor(110,pixels.Color(0,0,255));
         pixels.setPixelColor(113,pixels.Color(255,255,255));
         pixels.show();
         delay(100);
         pixels.setPixelColor(114,pixels.Color(0,0,0));
         pixels.setPixelColor(111,pixels.Color(0,0,0));
         pixels.setPixelColor(110,pixels.Color(0,0,0));
         pixels.setPixelColor(113,pixels.Color(0,0,0));
         pixels.show();
         delay(100);
         i++;
        }
       }


String Aus1 = "" + String(h_aus) +":" + String(min_aus) + "";
if(h_aus+8 > 24)
{
  h_aus = h_aus - 24;
}
String Aus2 = "" + String(h_aus+8) +":" + String(min_aus) + "";
        
// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
// and a content-type so the client knows what's coming, then a blank line:

            
/*--Wenn die Hintergrundfarbe nahezu weiß ist, wird die Schriftfarbe auf schwarz umgestellt*/
if(red >= 240 && blue >= 240 && green >= 240)
{
   textcolor = "black";
}
else{
  textcolor = "white";            
}
/*
client.println("<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><style>");
client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".button1 {border: 2px solid black; color: "+textcolor+"; background-color:" + String(rgb) +"padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px;}");
client.println(".button2 {border: 2px solid #e7e7e7;color: white;background-color: #555555;padding: 15px 32px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;}");
client.println("</style></head><body><h1><font size=\"7\">Wortuhr</font></h1><body><center><br/>");
client.println("<h1>LED Farbe</h1>");
client.println("<div style=\"max-width: 650px; text-align: left;\"><form action=\"pixelgraphic\" methode=\"get\">");
client.println("<p><center>Hier kann die Farbe der LEDs eingestellt werden</center></p><br/>");
client.println("<table cellpadding=\"5px\" align=\"center\"><tbody><tr>");
client.println("<th>Grundfarbe</th><th>Regler (0 bis 255)</th>");
client.println("<th width=\"20px\">dezimal</th></tr><tr>");
client.println("<td>rot</td>");
client.println("<td><input id=\"slider_r\" max=\"355\" min=\"100\" step=\"1\" type=\"range\" value=\"" + String(red+100) +"\" name=\"r\" onchange=\"document.getElementById('textfield_r10').value = (document.getElementById('slider_r').value)-100;\" /></td>");
client.println("<td><input id=\"textfield_r10\" style=\"text-align: right;\" maxlength=\"3\" size=\"1\" type=\"text\" value=\"" + String(red) +"\" onchange=\"document.getElementById('slider_r').value = document.getElementById('textfield_r10').value\" /></td></tr><tr>");
client.println("<td>gr&uuml;n</td>");
client.println("<td><input id=\"slider_g\" max=\"355\" min=\"100\" step=\"1\" type=\"range\" value=\"" + String(green+100) +"\" name=\"g\" onchange=\"document.getElementById('textfield_g10').value = (document.getElementById('slider_g').value)-100;\" /></td>");
client.println("<td><input id=\"textfield_g10\" style=\"text-align: right;\" maxlength=\"3\" size=\"1\" type=\"text\" value=\"" + String(green) + "\" onchange=\"document.getElementById('slider_g').value = document.getElementById('textfield_g10').value\" /></td></tr><tr>");
client.println("<td>blau</td>");
client.println("<td><input id=\"slider_b\" max=\"355\" min=\"100\" step=\"1\" type=\"range\" value=\"" + String(blue+100) +"\" name=\"b\" onchange=\"document.getElementById('textfield_b10').value = (document.getElementById('slider_b').value)-100;\" /></td>");
client.println("<td><input id=\"textfield_b10\" style=\"text-align: right;\" maxlength=\"3\" size=\"1\" type=\"text\" value=\"" + String(blue) +"\" onchange=\"document.getElementById('slider_b').value = document.getElementById('textfield_b10').value\" /></td></tr></tbody></table><center>");
client.println("<br><br><button class=\"button1\" type=\"submit\">Farbe generieren</button></form><br><br><hr><br>");
client.println("<p>Hier kann ein Nachtmodus eingeschaltet werden. Dieser schaltet die Uhr f&uuml;r 8 Stunden, ab der anggegeben Uhrzeit, aus</p>");
client.println("<form action=\"uhrzeit\" methode=\"get\">");
client.println("<input type=\"time\" id=\"Zeit\" background-color=\"#e7e7e7\" name=\"uhrzeit\"><br><br>");
client.println("<button class=\"button2\" type=\"submit\">Nachtmodus</button></form>");
if(h_aus != -1 || min_aus != -1){
client.println("<br><p><b>Ihre Uhr wird zwischen " + Aus1 + " und " + Aus2 + " ausgeschaltet");
}
client.println("<br></div></center></body></html>");
client.println();
client.println(rgbToJSON(red,green,blue,helligkeit));
*/


      // Break out of the while loop
         break;
         }else { // if you got a newline, then clear currentLine
          currentLine = "";
         }
         }else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
         }
      }
}
      
    header = "";
    // Close the connection
    client.stop();
    h_aus = -1;
    min_aus = -1;
  }
}

#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

// MAC address for arduino
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// IP for arduino
IPAddress ip(192, 168, 1, 177);

//Port for web server (def. http is 80)
EthernetServer server(80);

File webPage;
String HTTP_req;          // stores the HTTP request


//Flags for change color to red
//-------------------------------------------------------------------//
int light = 1;
int    U1 = 1;
int    U2 = 0;
int    U3 = 2;
int    U4 = 0;
int    U5 = 0;
int    U6 = 0;
int    U7 = 0;
int    U8 = 0;
int    U9 = 0;
int    U10 = 0;
int    U11 = 0;
int    U12 = 0;
int    U13 = 0;
int    U14 = 0;
int    U15 = 0;
//------------------------------------------------------------------//
//Led Pin on arduino
#define arduinoPIN		3
// What type stripe is connected
#define ledtype	NEO_GRBW
// How many leds are on stripe?
#define ledsonstrip	60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledsonstrip, arduinoPIN, ledtype + NEO_KHZ800);

void setup() {
Ethernet.begin(mac, ip);  // initialize Ethernet device
  server.begin();           // start to listen for clients
  Serial.begin(9600);       // for debugging
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // initialize SD card
  Serial.println("Checking SD card is accessible...");
  if (!SD.begin(4)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  Serial.println("SUCCESS - SD card initialized.");
  HTTP_req = "";
  
//Initalizes stripe
  strip.begin();
//Turns off all leds
  strip.show();
}

void loop() {

//---------------------------------------------------//

// U1 begins here:
if (U1 == 0) (strip.setPixelColor(0,0,0,0,0), strip.setPixelColor(1,0,0,0,0), strip.setPixelColor(2,0,0,0,0));
    else if  (U1 == 1) (strip.setPixelColor(0,0,150,0,0),strip.setPixelColor(1,0,150,0,0),strip.setPixelColor(2,0,150,0,0));
       else  (strip.setPixelColor(0,150,0,0,0),strip.setPixelColor(1,150,0,0,0),strip.setPixelColor(2,150,0,0,0));
//--------------------------------------------------//
// U2 begins here:
if (U2 == 0) (strip.setPixelColor(3,0,0,0,0), strip.setPixelColor(4,0,0,0,0), strip.setPixelColor(5,0,0,0,0));
    else if  (U1 == 2) (strip.setPixelColor(3,0,150,0,0),strip.setPixelColor(4,0,150,0,0),strip.setPixelColor(5,0,150,0,0));
       else  (strip.setPixelColor(3,150,0,0,0),strip.setPixelColor(4,150,0,0,0),strip.setPixelColor(5,150,0,0,0));
//--------------------------------------------------//
// U3 begins here:
if (U3 == 0) (strip.setPixelColor(6,0,0,0,0), strip.setPixelColor(7,0,0,0,0), strip.setPixelColor(8,0,0,0,0));
    else if  (U3 == 1) (strip.setPixelColor(6,0,150,0,0),strip.setPixelColor(7,0,150,0,0),strip.setPixelColor(8,0,150,0,0));
       else (strip.setPixelColor(6,150,0,0,0),strip.setPixelColor(7,150,0,0,0),strip.setPixelColor(8,150,0,0,0));
//-------------------------------------------------//
//-------------------------------------------------//
// U4 begins here:
if (U4 == 0) (strip.setPixelColor(9,0,0,0,0), strip.setPixelColor(10,0,0,0,0), strip.setPixelColor(11,0,0,0,0));
    else if  (U4 == 1) (strip.setPixelColor(9,0,150,0,0),strip.setPixelColor(10,0,150,0,0),strip.setPixelColor(11,0,150,0,0));
       else (strip.setPixelColor(9,150,0,0,0),strip.setPixelColor(10,150,0,0,0),strip.setPixelColor(11,150,0,0,0));
//-------------------------------------------------//
//-------------------------------------------------//
// U5 begins here:
if (U5 == 0) (strip.setPixelColor(12,0,0,0,0), strip.setPixelColor(13,0,0,0,0), strip.setPixelColor(14,0,0,0,0));
    else if  (U1 == 1) (strip.setPixelColor(12,0,150,0,0),strip.setPixelColor(13,0,150,0,0),strip.setPixelColor(14,0,150,0,0));
       else (strip.setPixelColor(12,150,0,0,0),strip.setPixelColor(13,150,0,0,0),strip.setPixelColor(14,150,0,0,0));
//-------------------------------------------------//
//-------------------------------------------------//
// U6 begins here:
if (U6 == 0) (strip.setPixelColor(15,0,0,0,0), strip.setPixelColor(16,0,0,0,0), strip.setPixelColor(17,0,0,0,0));
    else if  (U1 == 1) (strip.setPixelColor(15,0,150,0,0),strip.setPixelColor(16,0,150,0,0),strip.setPixelColor(17,0,150,0,0));
       else (strip.setPixelColor(15,150,0,0,0),strip.setPixelColor(16,150,0,0,0),strip.setPixelColor(17,150,0,0,0));
//------------------------------------------------//
strip.show();

 // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // read 1 byte (character) from client
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if ( HTTP_req.length() < 80)
          HTTP_req += c;  // save the HTTP request 1 char at a time
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // send web page
          if (HTTP_req.indexOf("ajaxrefresh") >= 0 ) {
            ajaxRequest(client);  //update the analog values
            break;
          }
          else {
            webPage = SD.open("index.htm");        // open web page file
            if (webPage) {
              while (webPage.available()) {
                client.write(webPage.read()); // send web page to client
              }
              webPage.close();
            }
            break;
          }
          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          } else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    HTTP_req = "";
    Serial.println("client disconnected");
  } // end if (client)
}

// send the state of the switch to the web browser
void ajaxRequest(EthernetClient client)
{
  if (U1 == 0) {
    client.println(" <bgcolor='#00FF00;'> ");

  }
}

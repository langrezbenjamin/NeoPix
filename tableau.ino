
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
 
#define PIN      4
#define N_LEDS  30

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

const char* ssid = "benaur";
const char* password = "benjaminaurelie";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
//  Serial.begin(9600);
  strip.begin();
  delay(10);

  // prepare GPIO0 Led frontale = GPIO16
  pinMode(0, OUTPUT);
  digitalWrite(0, 0);
  
  // prepare GPIO4 Interupteur front
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);

  // prepare GPIO5 Input carte mere (declencheur start)
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);

  // prepare GPIO16 Ouput carte mere (connaitre l etat on/off de la carte mere)
  pinMode(16, OUTPUT);
  digitalWrite(16, 0);

  WiFi.begin(ssid, password);
  
  
  // Start the server
  server.begin();
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}

void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< N_LEDS; i++) {
      c=Wheel(((i * 256 / N_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

void showStrip() {

 #ifdef ADAFRUIT_NEOPIXEL_H

   // NeoPixel

   strip.show();

 #endif

 #ifndef ADAFRUIT_NEOPIXEL_H

   // FastLED

   FastLED.show();

 #endif

}

void setPixel(int Pixel, byte red, byte green, byte blue) {

 #ifdef ADAFRUIT_NEOPIXEL_H

   // NeoPixel

   strip.setPixelColor(Pixel, strip.Color(red, green, blue));

 #endif

 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < N_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}


byte * Wheel(byte WheelPos) {
static byte c[3];
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }
  return c;
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  client.flush();
  
  // Match the request
  bool val0, val4, val5, val16;
  val0=digitalRead(0);
  val4=digitalRead(4);
  val5=digitalRead(5);
  val16=digitalRead(16);
  if (req.indexOf("5") != -1)
      {
        digitalWrite(5, 1);
      }
  if (req.indexOf("50") != -1)
      {
        digitalWrite(5, 0);
      }
  if (req.indexOf("4") != -1)
      {
        digitalWrite(4, 1);
      }
  if (req.indexOf("40") != -1)
      {
        digitalWrite(4, 0);
      }
  if (req.indexOf("red") != -1)
      {
        chase(strip.Color(255, 0, 0)); // Red
      }
  if (req.indexOf("green") != -1)
      {
        chase(strip.Color(0, 255, 0)); // green
      }
  if (req.indexOf("blue") != -1)
      {
        chase(strip.Color(0, 0, 255)); // vert
      }
  if (req.indexOf("violet") != -1)
      {
        chase(strip.Color(128, 0, 128)); // violet
      }
  if (req.indexOf("violets") != -1)
      {
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
            strip.setPixelColor(i  ,128, 0, 128); // Draw new pixel
            strip.show();
            delay(25);
    }
  }
     if (req.indexOf("1") != -1)
      {
            strip.setPixelColor(2  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(6  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(10  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(11  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(12  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(13  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(14  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(15  ,255, 0, 0); // Draw new pixel
            strip.show();

    }
    if (req.indexOf("2") != -1)
      {
            strip.setPixelColor(0  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(2  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(3  ,255, 0, 0); // Draw new pixel            
            strip.setPixelColor(4  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(5  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(7  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(9  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(10  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(11  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(14  ,255, 0, 0); // Draw new pixel
            strip.show();

    }
   if (req.indexOf("3") != -1)
      {
            strip.setPixelColor(0  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(2  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(4  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(5  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(7  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(9  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(10  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(11  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(12  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(13  ,255, 0, 0); // Draw new pixel
            strip.setPixelColor(14  ,255, 0, 0); // Draw new pixel
            strip.show();

    }
    if (req.indexOf("cc") != -1)
      {      
      for(uint16_t i=0; i<strip.numPixels()+4; i++) {
            strip.setPixelColor(i  ,0, 0, 0); // Draw new pixel
            strip.show();
      }
      }
    if (req.indexOf("all") != -1)
      {      
        rainbowCycle(20); 
      }
    if (req.indexOf("/gpio16/0") != -1)
      {
        digitalWrite(16, 0);
      }
  client.flush();
  // Prepare the response 
 String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  if (req.indexOf("/etat/") != -1 ){
    s += "Etat GPIO 0<br>";  
    s += (val0)?"ON<br>":"OFF<br>";
    s += "Etat GPIO 16<br>";  
    s += (val16)?"ON<br>":"OFF<br>";
    s += "Etat GPIO 4<br>";  
    s += (val4)?"ON<br>":"OFF<br>";
    s += "Etat GPIO 4<br>";  
    s += (val4)?"ON<br>":"OFF<br>";
    s += "</html>\n";
  }
  // Send the response to the client
  client.print(s);
  delay(1);
  
}


https://cdn-learn.adafruit.com/downloads/pdf/adafruit-neopixel-uberguide.pdf


int delayval = 500; // delay for half a second

----

 for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

 }


----------

  leds.setPixelColor(0, 255, 0, 0); // Set the first pixel to RED
  leds.setPixelColor(1, 0, 255, 0); // Set the second pixel to GREEN
  leds.setPixelColor(2, 0, 0, 255); // Set the third pixel to BLUE
  leds.show(); //Display the colors

------------

https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/

https://gist.github.com/dougalcampbell/7243998

Brightness :
https://learn.sparkfun.com/tutorials/lilypad-pixel-board-hookup-guide/using-neopixel-library-and-sample-code

I-G. SHL (Décalage à gauche)
L'opérateur binaire SHL a pour opérande de gauche la valeur initiale et pour opérande de droite le nombre de bits à décaler à gauche. Les bits de poids forts sont perdus et les bits de poids faibles entrés (à droite) sont à 0. Ce n'est pas une rotation. 
L'opérateur C est <<. Il agit sur chaque bit de la valeur : 
  
Sélectionnez
unsigned a = 0xF0F0;
unsigned b = 2;
unsigned c = a << b; /* c == 1100 0011 1100 0000 soit 0xC3C0 */ 

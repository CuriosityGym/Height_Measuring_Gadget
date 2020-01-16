#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
int trigpin = 7;
int echopin = 8;
int duration;
int duration2;
int height;
float placing_height;
int obstruction;
 
void draw(int h) {
  // graphic commands to redraw the complete screen should be placed here 
  u8g.setFont(u8g_font_unifont);
  char cHeight[10];     // array of values that is required to make sure the OLED displays numbers.
  //u8g.setFont(u8g_font_osb21);
  itoa(h,cHeight,10);
  u8g.drawStr( 0, 22,cHeight);
}
 
void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  Serial.begin(9600);
  digitalWrite(trigpin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration = pulseIn(echopin ,HIGH);
  placing_height = duration*0.034/2;
  delay(1500);
  Serial.println(placing_height);
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);   // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);       // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);       // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
 
 
}
 
void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration2 = pulseIn(echopin ,HIGH);
  obstruction = duration2 * 0.034/2;
  Serial.println(obstruction);
  delay(2000);
  height = placing_height - obstruction;
  Serial.println(height);
  Serial.println("done");
  delay(2000);
  // picture loop
  u8g.firstPage(); 
  do {
    draw(height);
  } while( u8g.nextPage() );
 
  // rebuild the picture after some delay
  //delay(50);
  delay(1000);
}

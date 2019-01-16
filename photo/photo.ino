#include <U8g2lib.h>
#define LDR_PIN A0
#define LED_PIN A1
#define AXIS 14


U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                          2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);


char vals[127];
void setup(void)
{
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  for (short i = 0; i < 127; ++i) {
    vals[i] = 0;
  }
}
 
void loop(void)
{
  u8g2.clearBuffer();
short raw, val, ui_val;
  raw = analogRead(LDR_PIN);
  val = map(raw, 0, 1023, 50, 0);
  ui_val = map(raw, 0, 1023, 100, 0);  
  append(val);
  char cstr[3];
  itoa(ui_val, cstr, 10);
  u8g2.drawStr(0, 12, cstr);
  for (char i = 0; i < 127; ++i) {
    u8g2.drawBox(i, 63-vals[i], 1, vals[i]);
  }
  u8g2.sendBuffer();
  if (val <= 10) {
    analogWrite(LED_PIN, 1023);
  } else {
    analogWrite(LED_PIN, 0);
  }

  //delay(300);

}

void append(char value)
{
  for (char i = 1; i < 127; ++i) {
    vals[i - 1] = vals[i];
  }
  vals[126] = value;
}

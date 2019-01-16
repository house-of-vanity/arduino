#include <U8g2lib.h>
#define DELAY 50
#define SIZE 8
U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                          2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);

void setup(void) 
{
  u8g2.begin();
}
 
void loop(void)
{
  u8g2.clearBuffer();
  u8g2.setDrawColor(true);
  int height = 64;
  int width = 128;
  int h = 0;
  int w = 0;
  while (h < height) {
    while (w < width) {
      u8g2.drawBox(w,h,SIZE,SIZE);
      u8g2.sendBuffer();
      delay(DELAY);
      w = w + SIZE;
    }
    w = 0;
    u8g2.drawBox(w,h,SIZE,SIZE);
    u8g2.sendBuffer();
    delay(DELAY);
    h = h + SIZE;
  }
}

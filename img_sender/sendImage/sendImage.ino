#include <U8g2lib.h>
//#include <MemoryFree.h>

#define MESSAGE 256
#define image_width 128
#define image_height 16
#define BAUD_RATE 115200

U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                          2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);

static const unsigned char firstSeg = '\00';
static const unsigned char secondSeg = '\01';
static const unsigned char thirdSeg = '\02';
static const unsigned char fourthSeg = '\03';
byte image[MESSAGE];


void setup() {
  u8g2.begin();
  //u8g2.clearBuffer();
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ;
  }
  /*
    u8g2.setFont(u8g2_font_6x12_t_cyrillic);
    u8g2.drawStr(5,15,"Waiting for agent...");
    u8g2.sendBuffer();
  */
}
//freeMemory()
void loop() {
  while (Serial.available()) {
    unsigned char type = Serial.read();
    delay(10);
    Serial.print("Found header:");
    Serial.println(type, DEC);
    Serial.readBytes(image, MESSAGE);
    switch (type) {
      case firstSeg:
        u8g2.clearBuffer();
        u8g2.drawXBM(0, 0, image_width, image_height, image);
        break;
      case secondSeg:
        u8g2.drawXBM(0, image_height, image_width, image_height, image);
        break;
      case thirdSeg:
        u8g2.drawXBM(0, image_height * 2, image_width, image_height, image);
        break;
      case fourthSeg:
        u8g2.drawXBM(0, image_height * 3, image_width, image_height, image);
        u8g2.sendBuffer();
        break;

    }
  }
}



// u8g2_font_6x12_t_cyrillic - cyrilic 7px
// u8g2_font_unifont_t_cyrillic - cyrilic 10px

// stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
// echo "Hello Arduino" > /dev/ttyACM0

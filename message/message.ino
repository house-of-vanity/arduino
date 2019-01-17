#include <U8g2lib.h>

#define MESSAGE 100
#define FONT_SIZE_TITLE 10
#define FONT_SIZE_TEXT 7
#define SPACING 2
#define LCD_WIDTH 128
#define LCD_HEIGHT 64

U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                          2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);

char temp_arr[MESSAGE];

struct message_t {
  char type;
  String title;
  String text;
} message;

void setup() {
  u8g2.begin();
  //u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  Serial.begin(9600);
  Serial.println("Ready\n");
  u8g2.drawStr(0, 12, "Ready");
  u8g2.sendBuffer();
  while (!Serial) {
    ; 
  }
}

void loop() {
  while (Serial.available()) {
    /*
    message.type = '\0';
    message.title = '\0';
    message.text = '\0';
    */
    message.type = Serial.read();
    if (message.type == '\11') {
      /* type 1 (x01)
       *  0x01TITLE0x00lorem ipsum0x00
       */
      message.title = Serial.readStringUntil('\0');
      Serial.println(message.title);
      message.text = Serial.readStringUntil('\0');
      Serial.println(message.text);
    } else {
      continue;
    }
    u8g2.clearBuffer();
    display(message.title, 'h');
    display(message.text, 't');
    u8g2.sendBuffer();
    /*
    Serial.print("\n=== *** ===\nTitle: ");
    Serial.println(message.title);
    Serial.print("Text: ");
    Serial.println(message.text);*/
  }
}

void display(String str, char type) {
  char start = 0;
  str.toCharArray(temp_arr, MESSAGE);
  int str_len = u8g2.getUTF8Width(temp_arr);
  
  if (type == 'h'){
    u8g2.setFont(u8g2_font_unifont_t_cyrillic);
    if (str_len >= LCD_WIDTH) {
      ;
    } else {
      start = (LCD_WIDTH - str_len) / 2;
    }
    u8g2.drawUTF8(start, FONT_SIZE_TITLE, temp_arr);
  } else if (type == 't') {
    u8g2.setFont(u8g2_font_6x12_t_cyrillic);
    if (str_len >= LCD_WIDTH) {
      ;
    } else {
      start = (LCD_WIDTH - str_len) / 2;
      u8g2.drawUTF8(start, FONT_SIZE_TITLE+FONT_SIZE_TEXT+SPACING, temp_arr);
    }
  }
  Serial.print("== Display ==\nStr len: ");
  Serial.println(str_len, DEC);
  Serial.print("Start: ");
  Serial.println(start, DEC);
  Serial.print("Type: ");
  Serial.println(type);
  Serial.print("Text: ");
  Serial.println(str);
}
/*
\1TITLE\0Lorem\0
wtf

01:58:21.823 -> Ready
01:58:21.823 -> 
01:58:31.558 -> == Display ==
01:58:31.591 -> Str len: 39
01:58:31.591 -> Start: 44
01:58:31.624 -> Type: h
01:58:31.624 -> Text: TITLE
01:58:31.624 -> == Display ==
01:58:31.657 -> Str len: 40
01:58:31.657 -> Start: 44
01:58:31.657 -> Type: t
01:58:31.690 -> Text: Lorem
01:58:38.146 -> == Display ==
01:58:38.179 -> Str len: 29
01:58:38.179 -> Start: 49
01:58:38.212 -> Type: h
01:58:38.212 -> Text: TITLE
01:58:38.212 -> == Display ==
01:58:38.245 -> Str len: 40
01:58:38.245 -> Start: 44
01:58:38.279 -> Type: t
01:58:38.279 -> Text: Lorem

 */


// u8g2_font_6x12_t_cyrillic - cyrilic 7px
// u8g2_font_unifont_t_cyrillic - cyrilic 10px

// stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
// echo "Hello Arduino" > /dev/ttyACM0

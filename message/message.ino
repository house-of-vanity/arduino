#include <U8g2lib.h>

#define MESSAGE 256
#define FONT_SIZE 10

U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                          2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);

String message = "";
char to_send[MESSAGE];
unsigned int lastStringLength = 0;

void setup() {
  u8g2.begin();
  //u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_cyrillic);
  Serial.begin(9600);
  Serial.print("Ready\n");
  u8g2.drawStr(0, 12, "Ready");
  u8g2.sendBuffer();
  while (!Serial) {
    ; 
  }
}

void loop() {
  while (Serial.available()) {
    message = Serial.readStringUntil('\0');
    lastStringLength = message.length();
    message.toCharArray(to_send, 64);
    int test = sizeof(to_send);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 12, to_send);
    u8g2.sendBuffer();
    Serial.print("to_send: ");
    Serial.print(message);
    Serial.print("sizeof: ");
    Serial.print(test);
    Serial.print("\n");
  }
}

char* append(char* arr, char a)
{
    size_t len = strlen(arr);


    char* ret = new char[len+2];

    strcpy(ret, arr);    
    ret[len] = a;
    ret[len+1] = '\0';
    Serial.print(ret);
    Serial.print(arr);
        
    return ret;
}

// stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
// echo "Hello Arduino" > /dev/ttyACM0

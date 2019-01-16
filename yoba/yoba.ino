// библиотека для работы с графическими дисплеями
#include <U8g2lib.h>
 
/* пины дисплея:
  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 |
  |+5В|Vdd|Vo |DB0|DB1|DB2|DB3|DB4|DB5| DB6| DB7| CS1| CS2| RST| R/W| D/I| E  | Vee| A  | K  |
 
  U8G2_KS0108_128X64_F u8g2(ROTATION, D0, D1, D2, D3, D2, D3, D4, D5, D6, D7,
                            EN, D/I, CS0, CS1, CS2, RESET);
  ROTATION:   угол поворота дисплея
    U8G2_R0:  0 градусов
    U8G2_R1:  90 градусов
    U8G2_R2:  180 градусов
    U8G2_R3:  270 градусов
  D0..D7: пины данных
  EN: стробирование данных
  D/I: команды / данные
  CS0-CS2: выбор кристала
  RESET: сброс
  R/W: чтение / запись (подключайте к земле)
*/
 
// размер ширины и высоты изображения
#define matryoshka_width 64
#define matryoshka_height 64
 
// массив изображения
static const unsigned char matryoshka_bits[] U8X8_PROGMEM = {
   0x00, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0x03, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00,
   0x00, 0x7e, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0xf0, 0x00, 0x00,
   0x00, 0xe0, 0x01, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0xf0, 0x00, 0x00,
   0x00, 0x80, 0x07, 0x00, 0x00, 0x3c, 0x00, 0x04, 0x00, 0x00, 0x0e, 0x00,
   0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
   0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0xc0, 0x01, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03,
   0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x70, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x07, 0x30, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x06,
   0x38, 0xa0, 0xe8, 0x01, 0x00, 0x00, 0x00, 0x0e, 0x18, 0x0c, 0xe0, 0x07,
   0x00, 0x94, 0x01, 0x0c, 0x1c, 0x00, 0x45, 0x05, 0x00, 0x81, 0x07, 0x1c,
   0x0c, 0x00, 0x08, 0x0a, 0x00, 0x2b, 0x0d, 0x18, 0x0c, 0x00, 0xa0, 0x01,
   0x00, 0x00, 0x10, 0x38, 0x0e, 0x10, 0x00, 0x01, 0x00, 0x12, 0x00, 0x30,
   0x06, 0x00, 0x50, 0x00, 0x00, 0x08, 0x00, 0x30, 0x06, 0x00, 0x00, 0x00,
   0x00, 0x10, 0x00, 0x30, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70,
   0x06, 0x00, 0x09, 0x04, 0x00, 0x40, 0x00, 0x70, 0x07, 0x00, 0xa8, 0x00,
   0x00, 0x80, 0x09, 0x60, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x60,
   0x03, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x60, 0x03, 0x00, 0x34, 0x00,
   0x00, 0x00, 0x04, 0x60, 0x07, 0x00, 0x50, 0x00, 0x00, 0x00, 0x04, 0x60,
   0x03, 0x00, 0x80, 0x0a, 0x00, 0x80, 0x05, 0x60, 0x07, 0x00, 0x60, 0x50,
   0xa5, 0x5a, 0x02, 0x70, 0x07, 0x00, 0x60, 0x11, 0x10, 0x50, 0x04, 0x60,
   0x06, 0x00, 0xc0, 0xd2, 0x80, 0x72, 0x01, 0x30, 0x06, 0x00, 0x80, 0xff,
   0x10, 0xff, 0x01, 0x30, 0x06, 0x00, 0x80, 0xff, 0xf9, 0x7f, 0x00, 0x30,
   0x0e, 0x00, 0x00, 0xff, 0xff, 0x7f, 0x00, 0x30, 0x0c, 0x00, 0x00, 0xfe,
   0xff, 0x1f, 0x00, 0x38, 0x0c, 0x00, 0x00, 0xfc, 0xff, 0x0f, 0x00, 0x18,
   0x0c, 0x00, 0x00, 0x78, 0x1d, 0x02, 0x00, 0x18, 0x1c, 0x00, 0x00, 0x00,
   0x50, 0x00, 0x00, 0x1c, 0x18, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0c,
   0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x30, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x06, 0x70, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x07,
   0xe0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x03, 0xc0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x20, 0xc0, 0x01,
   0x80, 0x03, 0x20, 0x00, 0x00, 0x20, 0xe0, 0x00, 0x00, 0x07, 0x00, 0x01,
   0x00, 0x00, 0x70, 0x00, 0x00, 0x0e, 0x00, 0x02, 0x00, 0x10, 0x38, 0x00,
   0x00, 0x3c, 0x00, 0x88, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x78, 0x00, 0x00,
   0x00, 0x00, 0x0f, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0xc0, 0x07, 0x00,
   0x00, 0xc0, 0x07, 0x00, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x1f, 0x00,
   0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x40, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x5f, 0xfd, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xff,
   0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

 
// создаём объект для работы с графическим дисплеем
U8G2_KS0108_128X64_F u8g2(U8G2_R0, 13, 12, 11, 10, 9, 8, 7, 6,
                          2, 3, 5, 4, U8X8_PIN_NONE, U8X8_PIN_NONE);
 
// переменная для хранения цвета изображения
bool color = true;
 
void setup(void) 
{
  // начало работы с дисплеем
  u8g2.begin();
}
 
void loop(void)
{
  // очищаем память дисплея
  u8g2.clearBuffer();
  // устанавливаем цвет рисования
  u8g2.setDrawColor(color);
  // выводим изображение на дисплей
  u8g2.drawXBMP(0, 0, matryoshka_width, matryoshka_height, matryoshka_bits);
  // отсылаем данные на дисплей
  u8g2.sendBuffer();
  // ждём 3 секунды
  delay(3000);
  // инвертируем цвет
  //color = !color;
}

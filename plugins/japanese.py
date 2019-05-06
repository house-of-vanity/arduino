from PIL import Image, ImageDraw, ImageFont
import io
import logging
import random
import time


LCD_H = 64
LCD_W = 128
log = logging.getLogger(__name__)
def japanese():
    alpabet = dict()
    alpabet = {
        'ア':'a',
        'イ':'i',
        'ウ':'u',
        'エ':'e',
        'オ':'o',
        'カ':'ka',
        'キ':'ki',
        'ク':'ku',
        'ケ':'ke',
        'コ':'ko',}
    img = Image.new('1', (LCD_W, LCD_H), color = 'black')
    font_size_jp = 70
    font_size_latin = 70
    spacing = 5
    letter = random.choice(list(alpabet))
    letter = (letter, alpabet[letter])
    fnt_jp = ImageFont.truetype('koharufont.ttf', font_size_jp)
    fnt_jp = ImageFont.truetype('DroidSansJapanese.ttf', font_size_jp)
    fnt_latin = ImageFont.truetype('clacon.ttf', font_size_latin)
    draw = ImageDraw.Draw(img)
    draw.rectangle((0,0,LCD_H,LCD_W/2), fill="white")
    draw.text((-2, (LCD_H-font_size_jp)*3), letter[0], font=fnt_jp, fill='black')
    text_offset = draw.textsize(letter[1], font=fnt_latin)[0]
    draw.text(((LCD_W-text_offset)/4 + LCD_W/2 - spacing*2, (font_size_latin-LCD_H)/2), letter[1], font=fnt_latin, fill='white')
    draw.line(((0,0),(LCD_W-1,0),(LCD_W-1,LCD_H-1),(0, LCD_H-1),(0,0)), fill='white')
    img_io = io.BytesIO()
    img.save(img_io, 'XBM')
    img_io.seek(0)

    array = img_io.read().decode('utf-8')
    array = array[array.find('{')+1:-3]
    array = array.replace('\n', '').replace(',', '').replace('0x', '')
    bytes_list = []

    for i in range(0, len(array), 2):
        bytes_list.append( int (array[i:i+2], 16 ) )

    return bytes_list


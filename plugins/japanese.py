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
        'コ':'ko',
        'サ':'sa',
        'シ':'shi',
        'ス':'su',
        'セ':'se',
        'ソ':'so',
        'タ':'ta',
        'チ':'chi',
        'ツ':'tsu',
        'テ':'te',
        'ト':'to',
        'ナ':'na',
        'ニ':'ni',
        'ヌ':'nu',
        'ネ':'ne',
        'ノ':'no',
        'ハ':'ha',
        'ヒ':'hi',
        'フ':'fu',
        'ヘ':'he',
        'ホ':'ho',
        'マ':'ma',
        'ミ':'mi',
        'ム':'mu',
        'メ':'me',
        'モ':'mo',
        'ヤ':'ya',
        'ユ':'yu',
        'ヨ':'yo',
        'ラ':'ra',
        'リ':'ri',
        'ル':'ru',
        'レ':'re',
        'ロ':'ro',
        'ワ':'wa',
        'ヲ':'wo',
        'ン':'nn',
        'あ':'a',
        'い':'i',
        'う':'u',
        'え':'e',
        'お':'o',
        'か':'ka',
        'き':'ki',
        'く':'ku',
        'け':'ke',
        'こ':'ko',
        'さ':'sa',
        'し':'shi',
        'す':'su',
        'せ':'se',
        'そ':'so',
        'た':'ta',
        'ち':'chi',
        'つ':'tsu',
        'て':'te',
        'と':'to',
        'な':'na',
        'に':'ni',
        'ぬ':'nu',
        'ね':'ne',
        'の':'no',
        'は':'ha',
        'ひ':'hi',
        'ふ':'fu',
        'へ':'he',
        'ほ':'ho',
        'ま':'ma',
        'み':'mi',
        'む':'mu',
        'め':'me',
        'も':'mo',
        'や':'ya',
        'ゆ':'yu',
        'よ':'yo',
        'ら':'ra',
        'り':'ri',
        'る':'ru',
        'れ':'re',
        'ろ':'ro',
        'わ':'wa',
        'を':'wo',
        'ん':'nn'
    }
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


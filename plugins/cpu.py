from PIL import Image, ImageDraw, ImageFont
import io
import logging
import subprocess
import time


LCD_H = 64
LCD_W = 128
log = logging.getLogger(__name__)
def cpu():
    cmd = 'top -bn1 1 | grep -P "%Cpu\d" | awk -F \',\' \'{sub(" id","",$4); print $4}\''
    try:
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    except OSError:
        time.sleep(5)
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    cores = list()
    for core in output.decode('utf-8').split('\n'):
        if core != '':
            cores.append(float(core))
    img = Image.new('1', (LCD_W, LCD_H), color = 'black')
    fnt = ImageFont.truetype('clacon.ttf', 20)
    draw = ImageDraw.Draw(img)
    text_offset = draw.textsize('CPU Usage', font=fnt)[0]
    draw.text(((LCD_W-text_offset)/2,0), 'CPU Usage', font=fnt, fill='white')
    draw.line(((0,0),(LCD_W-1,0),(LCD_W-1,LCD_H-1),(0, LCD_H-1),(0,0)), fill='white')
    i = 0
    bar_w = 16
    bar_h = 45
    spacing_top = 20
    spacing = 2
    while i < len(cores):
        draw.rectangle((bar_w * i + spacing, LCD_H, 12 + bar_w * i, int(cores[i])/100 * (LCD_H-spacing_top) + spacing_top), fill="white")
        i += 1
    draw.line(((0,spacing_top-spacing),(LCD_W,spacing_top-spacing)), fill='white')
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

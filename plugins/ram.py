from PIL import Image, ImageDraw, ImageFont
import io
import logging
import subprocess

LCD_H = 64
LCD_W = 128
log = logging.getLogger(__name__)
def ram():
    rams = dict()
    for ram_type in ['Mem', 'Swap']:
        cmd = 'free | awk \'/%s:/{print $2, $3}\'' % ram_type
#       cmd = 'cat /tmp/free1 | awk \'/%s:/{print $2, $3}\'' % ram_type
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
        output, error = process.communicate()
        rams[ram_type] = dict()
        ram = output.decode('utf-8').split('\n')[0]
        log.debug('Memory "%s" usage: %s' % (ram_type, ram))
        rams[ram_type]['Total'] = int(ram.split()[0])
        rams[ram_type]['Used'] = int(ram.split()[1])
    img = Image.new('1', (LCD_W, LCD_H), color = 'black')
    fnt = ImageFont.truetype('clacon.ttf', 20)
    fnt_small = ImageFont.truetype('clacon.ttf', 16)
    draw = ImageDraw.Draw(img)
    text_offset = draw.textsize('Memory usage', font=fnt)[0]
    draw.text(((LCD_W-text_offset)/2,0), 'Memory usage', font=fnt, fill='white')
    # border
    draw.line(((0,0),(LCD_W-1,0),(LCD_W-1,LCD_H-1),(0, LCD_H-1),(0,0)), fill='white')
    bar_w = 16
    bar_h = 45
    spacing_top = 20
    spacing = 2
    # RAM
    used = rams['Mem']['Used'] / rams['Mem']['Total']
    ram_top = spacing_top+spacing + (LCD_H-spacing_top)-(LCD_H-spacing_top)*used
    draw.rectangle((
        (spacing, LCD_H),
        (LCD_W/2-spacing, ram_top)), fill="white")
    ram_gi = rams['Mem']['Used']/1024/1024
    ram_total_gi = rams['Mem']['Total']/1024/1024
    ram_text = "%.1f/%.1fg" % (ram_gi, ram_total_gi)
    text_offset = draw.textsize(ram_text, font=fnt_small)
    if ram_top < LCD_H-text_offset[1]-3:
        draw.text((spacing*2,LCD_H-text_offset[1]-3), ram_text, font=fnt_small, fill='black')
    else:
        draw.text((spacing*2,spacing_top+2), 'RAM', font=fnt, fill='white')
    # SWAP
    used = rams['Swap']['Used'] / rams['Swap']['Total']
    ram_top = spacing_top+spacing + (LCD_H-spacing_top)-(LCD_H-spacing_top)*used
    draw.rectangle((
        (spacing+LCD_W/2, LCD_H),
        (LCD_W-spacing, ram_top)), fill="white")
    ram_gi = rams['Swap']['Used']/1024/1024
    ram_total_gi = rams['Swap']['Total']/1024/1024
    ram_text = "%.1f/%.1fg" % (ram_gi, ram_total_gi)
    text_offset = draw.textsize(ram_text, font=fnt_small)
    if ram_top < LCD_H-text_offset[1]-3:
        draw.text((LCD_W-text_offset[0] - spacing,LCD_H-text_offset[1]-3), ram_text, font=fnt_small, fill='black')
    else:
        draw.text((LCD_W-text_offset[0] - spacing,spacing_top+2), 'SWAP', font=fnt, fill='white')

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


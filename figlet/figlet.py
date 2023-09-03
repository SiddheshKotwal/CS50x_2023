import sys
import pyfiglet
import random

if len(sys.argv) == 1:
    string = input("Enter a Text: ")
    all_font = pyfiglet.FigletFont.getFonts()
    random_font = random.choice(all_font)
    font = pyfiglet.Figlet(font = random_font)
    print(font.renderText(string))
elif len(sys.argv) == 3:
    if not(sys.argv[1] == '-f' or sys.argv[1] == '--font'):
        sys.exit("Invalid Usage")
    with open("fonts_Figlet.txt", "r") as file:
        font_list = file.read()
    fonts_list = font_list.split()
    print(fonts_list)
    for Font in fonts_list:
        if Font == sys.argv[2]:
            break
    else:
        sys.exit("Invalid Usage")
    str = input("Enter a Text: ")
    f = pyfiglet.Figlet(font = sys.argv[2])
    print(f.renderText(str))
else:
    sys.exit("Invalid Usage")
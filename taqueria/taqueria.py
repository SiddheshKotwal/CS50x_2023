import sys

menu  = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

menu_list = list(menu.keys())
total = 0
while True:
    try:
        items = input("Items: ").title()
        if items in menu:
            total += menu[items]
            print("Total: ${:.2f}".format(total))

    except:
        print()
        break
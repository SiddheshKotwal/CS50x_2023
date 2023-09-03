import string

greeting = input("Greeting: ").strip().capitalize()
word = greeting.split(',')

if word[0] == "Hello":
    print("$0")
elif greeting[0] == 'H':
    print("$20")
else:
    print("$100")
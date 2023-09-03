import cs50

while True:
    # Taking input between 1 and 8 inclusively
    num = cs50.get_int("Height: ")
    if num <= 8 and num >= 1:
        break

# Printing half pyramid right bounded
for i in range(1, num + 1):
    print(" " * (num - i), end='')
    print("#" * i)
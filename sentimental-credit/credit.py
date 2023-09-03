import cs50
import sys

# Getting input from user
num = cs50.get_int("Number: ")
length = len(str(num))
digits = []
i = 0
j = 1

# Listing all digits of number
while i < length:
    tmp = int(num / j) % 10
    digits.append(tmp)
    i += 1
    j *= 10

mul = 0

# Applying Luhn's Algorithm
# first step multiplying every second digit and adding them according to the Algorithm
for i in digits[1::2]:
    tmp = i * 2
    if len(str(tmp)) > 1:
        temp = tmp % 10
        mul += temp
        temp = int(tmp / 10) % 10
        mul += temp
    else:
        mul += tmp

add = mul

# Now adding all remaining digits from number
# If length is odd adding 1st digit
if length % 2 != 0:
    add += digits[-1]

# Else adding upto 2nd digit
for j in digits[:-1:2]:
    add += j

# Checking if Luhn's Algorithm is satisfied, if not returning INVALID
if add % 10 != 0:
    print("INVALID")
    sys.exit()

# Checking conditions for various credit cards
if ((length == 15) and (digits[-1] == 3)) and (digits[-2] == 4 or digits[-2] == 7):
    print("AMEX")
elif ((length == 16) and (digits[-1] == 5)) and (digits[-2] == 1 or digits[-2] == 2 or digits[-2] == 3 or digits[-2] == 4 or digits[-2] == 5):
    print("MASTERCARD")
elif (length == 16 or length == 13) and digits[-1] == 4:
    print("VISA")
else:
    print("INVALID")
    sys.exit()
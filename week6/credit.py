from cs50 import get_string

# Prompt user for amount of cash
while True:
    try:
        cardNumber = get_string("Card Number: ")
        length = len(cardNumber)
        if length > 0 and int(cardNumber):
            break
    except ValueError:
        print("Not an integer! Use only numbers")

# Check if card number is valid - Luhn’s Algorithm
single_sum = 0
doubled_sum = 0
odd = 0
even = 0

for i in range(length):
    backwards = int(cardNumber[length - 1 - i])  # gets numbers from right to left
    if i % 2 != 0:
        odd = backwards * 2  # odd positions * 2
        odd1 = 0
        odd2 = 0
        if odd > 9:  # sum digits from multiplication when needed
            odd1 = odd % 10
            odd2 = odd // 10
            odd = odd1 + odd2
        doubled_sum += odd
    else:
        even = backwards  # even positions do not change value
        single_sum += even

total = single_sum + doubled_sum

valid = total % 10

# Check type of credit card

if valid == 0:
    if length == 13 or (length == 16 and cardNumber.startswith(('4'))):
        print("VISA")
    elif length == 15 and cardNumber.startswith(('34', '37')):
        print("AMEX")
    elif length == 16 and cardNumber.startswith(('51', '52', '53', '54', '55')):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")

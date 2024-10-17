from cs50 import get_float

# Prompt user for amount of cash
while True:
    change = get_float("Change: ")
    if change > 0:
        break  # exit loop and move on


cents = round(change * 100)  # turn everything into cents

coins = 0
quarters = 0
dimes = 0
nickels = 0
pennies = 0

while cents >= 25:
    coins += 1
    quarters += 1
    cents = cents - 25

while cents >= 10:
    coins += 1
    dimes += 1
    cents = cents - 10

while cents >= 5:
    coins += 1
    nickels += 1
    cents = cents - 5

while cents >= 1:
    coins += 1
    pennies += 1
    cents = cents - 1

print(f"{quarters} quarters")
print(f"{dimes} dimes")
print(f"{nickels} nickels")
print(f"{pennies} pennies")
print(f"Total: {coins} coins")

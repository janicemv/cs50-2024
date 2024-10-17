from cs50 import get_string

# Prompt user for text
text = get_string("Text: ")

# Count number of letters, words and sentences

letters = 0
words = 1
sentences = 0

for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i].isspace():
        words += 1
    elif text[i] in [".", "!", "?"]:
        sentences += 1

# Calculate Coleman-Liau index

l = letters / words * 100
s = sentences / words * 100

index = round(0.0588 * l - 0.296 * s - 15.8)

# Print Grade

if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")

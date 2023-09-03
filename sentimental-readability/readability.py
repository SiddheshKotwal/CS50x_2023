import cs50

# Getting input text
text = cs50.get_string("Text: ")
letters = 0

# Calculating number of letters in the text
for i in text:
    if (i.isalpha()) == True:
        letters += 1

# Calculating number of words in the text
words = text.split(" ")
num_words = len(words)

# Calculating number of sentences in the text
sentences = 0
for i in text:
    if (i == '?' or i == '.' or i == '!'):
        sentences += 1

# Calculating Average letters per word and average words per sentence
L = (letters / num_words) * 100
S = (sentences / num_words) * 100

# Calculating Coleman-Liau index
index = round(0.0588 * L - 0.296 * S - 15.8)

# Printing the grades of the text according to Coleman-Liau formula
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float l = (letters / (float) words) * 100;
    float s = (sentences / (float) words) * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i])) // counts all alphanumerical characters
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int word = 1;

    for (int w = 0; w < strlen(text); w++)
    {
        if (isspace(text[w])) // If there is a space, count +1 word
        {
            word++;
        }
    }

    return word;
}

int count_sentences(string text)
{
    int sentence = 0;
    for (int s = 0; s < strlen(text); s++)
    {
        if (text[s] == '.' || text[s] == '!' ||
            text[s] == '?') // If there is a punctuation, count +1 sentence
        {
            sentence++;
        }
    }

    return sentence;
}

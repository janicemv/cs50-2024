#include <cs50.h>
#include <math.h>
#include <stdio.h>

int sumDoubleCardNumber(int digit);
void checkAmex(long card);
void checkMaster(long card);

int main(void)
{

    // Get card number

    long card_number = get_long("Card Number: ");
    long original_cn = card_number;

    // Count number of digits in the card

    int digits = 0;
    while (card_number > 0)
    {
        card_number = card_number / 10;
        digits++;
    }

    // Check validity of the length

    if (digits < 13 || digits > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // Reset card_number to the original value for checksum calculation
    card_number = original_cn;

    // Calculate checksum

    long cn = card_number;
    int last;           // store the last numbers after each do while loop
    int sum = 0;        // sum of the numbers that we don't double
    int sum_double = 0; // sum of the numbers that we double
    int secondToLast;

    while (cn > 0)
    {
        last = cn % 10; // drop the current last
        cn = cn / 10;
        sum += last;

        secondToLast = cn % 10; // get the second to last number
        cn = cn / 10;           // continue to divide to get the last numbers from right to left
        int doubled =
            sumDoubleCardNumber(secondToLast); // a function to deal with the double digit numbers
        sum_double += doubled; // stores the sum of every digit that needs to be doubled
    }

    int total = sum + sum_double; // the final number to be checked
    int remainder = total % 10;

    // Card validations

    if (remainder != 0) // the remainder needs to be 0!
    {
        printf("INVALID\n");
        return 0;
    }

    // Check brands
    if (digits == 13 && remainder == 0)
    {
        printf("VISA\n");
    }
    else if (secondToLast == 4 && digits == 16)
    {
        printf("VISA\n");
    }
    else if (digits == 15)
    {
        checkAmex(card_number); // checks for AMEX in a function
    }
    else if (digits == 16)
    {
        checkMaster(card_number); // checks for MasterCard conditions
    }
    return 0;
}

int sumDoubleCardNumber(int digit) // deals with the doubled digit numbers
{
    digit = digit * 2;
    if (digit >= 10)
    {
        digit =
            1 +
            digit %
                10; // if it is a double digit number, they get separated and individually summed
        return digit;
    }

    return digit;
}

void checkAmex(long card)
{
    do
    {
        card = card / 10; // remove digits until the last two
    }
    while (card > 38);
    if (card == 34 || card == 37)
    {
        printf("AMEX\n");
        return;
    }
    printf("INVALID\n");
}

void checkMaster(long card)
{
    do
    {
        card = card / 10; // remove digits until the last two
    }
    while (card > 56);
    if (card == 51 || card == 55)
    {
        printf("MASTERCARD\n");
        return;
    }
    printf("INVALID\n");
}

import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py *.csv *.txt")
        sys.exit(1)  # Finish the program

    # TODO: Read database file into a variable
    database = []  # create a database to put the info from the file
    with open(sys.argv[1], 'r') as file:
        read = csv.DictReader(file)  # get file and put in this variable
        for row in read:
            database.append(row)  # fill database with info
        str = read.fieldnames[1:]  # dictionary of STRs to search

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as seq:
        sequence = seq.read()  # get file and put in this variable

    # TODO: Find longest match of each STR in DNA sequence

    str_count = {}  # stores number of repetitions

    for str_name in str:
        str_count[str_name] = longest_match(sequence, str_name)

    # TODO: Check database for matching profiles

    for profile in database:
        match = True
        for str_name in str:
            if int(profile[str_name]) != str_count[str_name]:
                match = False
                break
        if match:
            print(profile['name'])
            return

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

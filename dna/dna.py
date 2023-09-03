import csv
import sys

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py /STR_list.csv /sequences.txt")
        sys.exit()

    STR_dict = {}
    strr = []
    # TODO: Read database file into a variable
    with open(sys.argv[1], 'r') as f:
        file = csv.DictReader(f)
        strr = file.fieldnames[1:]
        # Reading csv file contents in a dictionary
        for row in file:
            STR_dict.update(row)

            # TODO: Read DNA sequence file into a variable
            with open(sys.argv[2], 'r') as infile:
                DNA_sequence = infile.read()

            tmp = list(STR_dict.keys())

            # TODO: Find longest match of each STR in DNA sequence
            long_run = []
            for i in tmp[1:]:
                # Getting longest matches for each STR type and Storing in a list
                long_run.append(longest_match(DNA_sequence, i))

            # TODO: Check database for matching profiles
            # Getting values from dictionary
            val = list(STR_dict.values())
            i = count = 0
            # Checking for all matches of longest match with the existing dataset
            for value in val[1:]:
                if int(value) == long_run[i]:
                    count += 1
                i += 1

            # Printing the name of person who's DNA sequence matches all STR types
            if count == i:
                print(val[0])
                return

    # If no match found
    print("No match")
    return


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

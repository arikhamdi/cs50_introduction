# Open the CSV file and DNA sequence, read contents into memory
# For each STR, compute the longest run of consecutive repeats in the DNA sequence
# Compare the STR counts against each row in the CSV file
# Hints
# Python's CSV module has reader and DICTREADER
# Python's sys module gives you acces to sys.argv for command-line arguments
# (first arg is csv file, second is DNA sequence)
# once you've opened a text file f using open(filename), you can read its contents using f.read()
import csv
from sys import argv, exit


def main():
    # Open the files
    # First row of CSV file has name as the first column, and then STRs for each of the remainning columns
    # Each remaing row corrsponds to a person
    if len(argv) != 3:
        print("missing command-line argument")
        exit(1)

    databases_file = argv[1]
    sequences_file = argv[2]
    person = []
    mydict = {}

    with open(sequences_file, "r") as text_file:
        sequence = text_file.read()

    with open(databases_file, "r") as csv_file:
        dna_reader = csv.reader(csv_file)
        for title in dna_reader:
            titles = title[1:len(title)]
            break

    with open(databases_file, "r") as csv_file:
        dna_dictreader = csv.DictReader(csv_file)
        for d in dna_dictreader:
            person.append(d.copy())

    # Computing STR Counts
    # For each position in the sequence: compute how many times the STR repeats starting at the position
    # For each position, keep checking succesive substring until STR repeats no longer
    max_found = 0
    for t in titles:
        mydict[t] = 0
        max_found = 0
        for cpt in range(len(sequence)):
            if t in sequence[cpt:cpt + len(t)]:
                for i in range(cpt, len(sequence), len(t)):
                    if t in sequence[i:i + len(t)]:
                        mydict[t] += 1
                    else:
                        break
            else:
                if mydict[t] > max_found:
                    max_found = mydict[t]
                mydict[t] = 0
        mydict[t] = max_found

    # Comparing Against Data
    # Save STR counts in some data structure
    # For each row in the data, check if each STR count matches, if so, print out the person's name.

    for p in person:
        count = 0
        for t in titles:
            if int(p[t]) == int(mydict[t]):
                count += 1
                if count == len(titles):
                    print(p['name'])
                    exit(0)

    print('No match')


main()

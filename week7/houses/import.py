from cs50 import SQL
from sys import argv, exit
import csv


def main():
    # Check command-line arguments
    if len(argv) != 2:
        print("")
        exit(1)

    file = argv[1]
    # connecting to db
    db = SQL("sqlite:///students.db")

    # Open csv file given by command-line argument
    with open(file, 'r') as csvfile:
        f = csv.DictReader(csvfile)
        for row in f:
            # For each row, parse name
            if len(row['name'].split()) == 2:
                first = row['name'].split()[0]
                middle = None
                last = row['name'].split()[1]
            else:
                first = row['name'].split()[0]
                middle = row['name'].split()[1]
                last = row['name'].split()[2]

            # Insert each student into the students table of students.db

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)",
                       first, middle, last, row['house'], row['birth'])


main()
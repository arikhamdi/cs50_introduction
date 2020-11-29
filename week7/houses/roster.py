# Hints
# use db.execute to select rows from the table
# Return value will be a list of Python dicts, where each dict represents a row in the table
# Remember to check for NULL values for middle names
from sys import argv, exit
from cs50 import SQL


def main():
    # Check command-line arguments
    if len(argv) != 2:
        exit(1)

    # Query database for all students in house
    # Students should be sorted alphabetically by last name, then first name
    db = SQL("sqlite:///students.db")

    lists = db.execute("Select * from students where house=? order by last", argv[1])

    # Print out each student's full name and birth year
    for l in lists:
        print(l['first'], end=" ")
        if l['middle'] != None:
            print(l['middle'], end=" ")
        print(l['last']+",", "born", l['birth'])


main()
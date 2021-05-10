import sys
import csv


def main():

    # Validate command line arguments 
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    dna_db = []

    # Read DNA database into memory
    with open(sys.argv[1], "r") as file:
        dna_reader = csv.DictReader(file)
        tandems = dna_reader.fieldnames[1:]
        
        for row in dna_reader:
            dna_db.append(row)
    
    # Read testing sequence into memory
    with open(sys.argv[2], "r") as file:
        sequence = file.read().strip()

    test = {}

    # Calculate STR counts and store them in test
    for tandem in tandems:
        test[tandem] = calc(sequence, tandem) 

    # Check testing sequence against dna database
    result = check(dna_db, test, tandems)

    # Print matching result
    print(result)
    sys.exit(0)


# Calculate longest consecutive repeat for given STR
def calc(sequence, tandem):
    repeats = []
    
    for i in range(len(sequence)):
        repeat = 0

        # Calculate repeat time when STR is found
        while sequence[i: i + len(tandem)] == tandem:
            repeat += 1
            i += len(tandem)
            
        repeats.append(repeat)
        
    return max(repeats)


# Check whether a person exists in database or not
def check(database, test, tandems):
    for people in database:

        # Track matching STRs
        tandem_match = 0

        for tandem in tandems:
            if int(people[tandem]) == test[tandem]:
                tandem_match += 1

        # If all STR counts match, return the name 
        if tandem_match == len(tandems):
            return people["name"]
    
    return "No match"


if __name__ == "__main__":
    main()
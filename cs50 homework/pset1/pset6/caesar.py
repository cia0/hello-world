import cs50
import sys

if len(sys.argv) != 2:
    print("Usage: python caesar.py key")
    exit(1)

def scramble(plain, key):
    scrambled = ""
    key = int(key)
    key = key%26
    
    for c in plain:
        if not c.isalpha():
            scrambled += c
        elif ord(c) > 96:
            scrambled += chr(((ord(c)-96+key)%26)+96)
        else:
            scrambled += chr(((ord(c)-64+key)%26)+64)
    return scrambled
    
def main():
    print("plaintext:  ", end="")
    cypher = scramble(cs50.get_string(), sys.argv[1])
    print("cyphertext: {}".format(cypher))
    return

if __name__ == "__main__":
    main()
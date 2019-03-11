import string
import sys
import cs50
import crypt

def crack(hashpass, salt):
    letters = [i for i in string.ascii_lowercase + string.ascii_uppercase] #how I missed list comprehension while working with C!
    for letter in letters:
        if crypt.crypt(letter, salt) == hashpass:
            print("{}".format(letter))
            return 
        
    for i in letters:
        for j in letters:
            if crypt.crypt("{}".format(i+j), salt) == hashpass:
                print("{}".format(i+j))
                return
    for i in letters:
        for j in letters:
            for k in letters:
                if crypt.crypt("{}".format(i+j+k), salt) == hashpass:
                    print("{}".format(i+j+k))
                    return   
    for i in letters:
        for j in letters:
            for k in letters:
                for l in letters:
                    if crypt.crypt("{}".format(i+j+k+l), salt) == hashpass:
                        print("{}".format(i+j+k+l))
                        return   
    print("UNCRACKABLE")
def main():
    
    # ensure proper usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python crack.py password")
        
    
    hashpass = sys.argv[1]
    salt = hashpass[:2]
    crack(hashpass, salt)
    
    return
    
if __name__ == "__main__":
    main()
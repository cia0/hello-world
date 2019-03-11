import cs50

def valid(n):
    total = 0
    for i in range(len(n)-1, 0, -2): #go through the string from the second last char by 2 at a time
        
        num = int(n[i-1:i]) * 2 #turn the chr into int and multiply it by 2
        
        if num > 9: #seperate the number into individual digits
            total += num%10
            num = num//10
        total += num
        
    for i in range(len(n), 0, -2):
        total += int(n[i-1:i])
        
    if total%10 == 0:
        return True
        
    return False

def check(card): #accepts card number as a string
    american = ['34', '37']
    master = ['51', '52', '53', '54', '55']
    
    if card[:2] in american and len(card) == 15:
        if valid(card):
            print("AMEX")
        
    elif card[:2] in master and len(card) == 16:
        if valid(card):
            print("MasterCard")
        
    elif card[:1] == '4' and (len(card) == 13 or len(card) == 16):
        if valid(card):
            print("VISA")
    
    else:
        print("INVLALID")
    
    return

def get_number(): #take a string that consists only of numbers
    print("Number: ", end="")
    while True:
        a = cs50.get_string()
        if a.isdigit():
            break
        print("Retry: ", end="")
    return a #returns a string because that's easier to iterate over and I'm too lazy to do floor division
    
def main():
    check(get_number())
    return

if __name__ == "__main__":
    main()
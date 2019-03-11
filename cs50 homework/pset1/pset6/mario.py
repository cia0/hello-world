import cs50

def get_positive_int():
    print("Height: ", end="")
    while True:
        n = cs50.get_int()
        if n > 0 and n < 24:
            break
        print("Retry: ", end="")
    return n

def pyramid(height):
    for i in range(1, height+1):
        print(" "*(height-i) + "#"*i + "  " + "#"*i)
    return

def main():
    pyramid(get_positive_int())

if __name__ == "__main__":
    main()
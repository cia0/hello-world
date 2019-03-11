from PIL import ImageGrab, ImageOps
from numpy import*
import os
import time
import threading
import win32api, win32con
"""
All coordinates assume a 1366 x 768px display
On Chrome browser
Page is scrolled all the way up
x_pad = 8
y_pad = 99
Play area = x_pad+1, y_pad+1, 647, 578
"""

# Globals
# ------------------
x_pad = 8
y_pad = 99
game_screen = 0 #will be used to store continuous updates of the screen
#miscellaneous coordinates
p_exit = (591,337)
clear_plates = ((79,201),(172,201),(270,201),(375,201),(476,201),(579,201))
mat = (142,383)
next_level = ((304,378),(304,378))#debatable
start = ((316,206),(304,393),(578, 456),(314, 383))

#---------------------------------------------------------------------------------------------
class FoodItem:
    def __init__(self, pos, order_sequence, unavailable, amount):
        self.pos = pos
        self.order_sequence = order_sequence #tuple of the coordinates necessary to order this item
        self.unavailable = unavailable #tuple:grayscale pixel value of item when unavaible
        self.amount = amount #amount of the item
        self.order_amount = amount #the amount recieved in an ordere is the same as the initial amount
        self.being_delivered = False #should not order again if food is already on way

    def order(self):
        for i in range(len(self.order_sequence)):
            if i == 2:
                image = screenGrab()
                if image.getpixel(self.order_sequence[i]) == self.unavailable:
                    mousePos(p_exit)
                    leftClick()
                    time.sleep(0.1)
                    return False

            mousePos(self.order_sequence[i])
            leftClick()
            time.sleep(0.3)

        threading.Thread(target = order_time_delay, args=(self,)).start()#delays the amount to simulate waiting time but allows the rest of the program to run


class Seat:
    def __init__(self, x, location, plate, bub_x):
        
        self.box = (x + x_pad, 46 + y_pad, x + x_pad+10, y_pad + 84)#location of the image that the customer desires
        self.plate = plate
        
        self.location = location #location of the seat occupant
        self.emptyPixel = (88, 68, 57) #RBG value of pixel at self.location when unoccupied

        self.bub_loc = (bub_x,155)
        self.bubble = False
        
        self.vacant = True #if someone is sitting there or not
        self.ordered = False #is their food on its way?
        self.ordered_twice = False #sometimes people steal other's food and they have to order again

        self.waiting_time = 0 #how long have they been waiting for food
        self.cleared = True

    def take_order(self): #can only be passed values in the list
        im = ImageOps.grayscale(ImageGrab.grab(self.box))
        a = array(im.getcolors())
        a = a.sum()
        return a

        #im.save(os.getcwd() + '\\seat_{}__'.format(self.location) + str(int(time.time())) + '.png', 'PNG')

#initialize food items
#----------------[coordinates]----------------------- [pixel value]-amout ordered
shrimp = FoodItem((34,330), ((556,350),(531,270),(488,220),(490,290)), (127, 102, 90), 5)
unagi = FoodItem((93, 446), ((556,350),(531,270),(571,220),(490,290)), (94, 49, 8), 5)
nori = FoodItem((34, 394), ((556,350),(531,270),(499,269),(490,290)), (33, 30, 11), 10)
roe = FoodItem((93, 394), ((556,350),(531,270),(571,280),(490,290)), (127, 61, 0), 10)
salmon = FoodItem((34, 446), ((556,350),(531,270),(485,335),(490,290)), (127, 71, 47), 5)
rice = FoodItem((93, 330), ((556,350),(509,294),(543,279),(490,290)), (127, 127, 127), 10)

foods = (shrimp, unagi, nori, roe, salmon, rice)

#initialize seats
#-5 from the top right black pixel in bubble----pixel coordinate---plate coordinate--bub_x
s1 = Seat(50,  (63,163), (79, 201), 64)
s2 = Seat(151, (172,166),(185, 204),165)
s3 = Seat(252, (259,156),(270, 201),266)
s4 = Seat(353, (392,162),(375, 201),367)
s5 = Seat(454, (474,166),(476, 201),468)
s6 = Seat(555, (570,161),(579, 201),569)

seats = (s1,s2,s3,s4,s5,s6)

#order_sake = [(556,350),(512,312),(543,279),(490,290)]

#recipes
#-----------ingredients------------------gray pixel sum--------
onigiri = (rice, rice, nori)
cali = (rice, nori, roe)
gunkan = (rice, nori, roe, roe)
salmon_roll = (rice, nori, salmon, salmon)
shrimp_roll = (rice, nori, shrimp, shrimp)
unagi_roll = (rice, nori, unagi, unagi)
dragon = (rice, rice, nori, roe, unagi, unagi)
wombocombo = (rice, rice, nori, roe, salmon, unagi, shrimp)

sushi = {2495:onigiri, 3326:cali, 2492:gunkan, 2657:salmon_roll, 3104:shrimp_roll, 2371:unagi_roll, 3459:dragon, 4134:wombocombo} #dictionary to keep track of sushi and pixel array sums
#---------------------------------------

def leftClick():
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,0,0)#these coordinates tell the cursor how far to move in relation to its current position
    time.sleep(.05)
    win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,0,0)
    #print "Click" #for debugging purposes
    time.sleep(.05)
        
def mousePos(cord): #set mouse posistion given coordinates
    win32api.SetCursorPos((x_pad + cord[0], y_pad + cord[1]))

def get_cords(): #get current coordinates of mouse on the PrtSc
    x,y = win32api.GetCursorPos()
    x = x - x_pad
    y = y - y_pad
    print x,y

def screenGrab(): #returns a screen capture of the entire game area
    box = (x_pad+1,y_pad+1,x_pad+640,y_pad+480)
    im = ImageGrab.grab(box)
    #im.save(os.getcwd() + '\\full_snap__' + str(int(time.time())) + '.png', 'PNG')
    return im

def startGame():
    for pos in start:
        mousePos(pos)
        leftClick()
        time.sleep(0.1) #wait for the menu to update

def nextLevel():#NEED TO RESET AMOUNTS OF FOOD AND OTHER THINGS
    for pos in next_level:
        mousePos(pos)
        leftClick()
        time.sleep(0.1) #wait for the menu to update

def clearPlates():
    for seat in seats:
        mousePos(seat.plate)
        leftClick()

def foldmat():
    mousePos(mat)
    leftClick()
    time.sleep(1.3)


def is_enough(recipe):    
    for foodItem in foods: #check to see if ingredients are in stock
        if foodItem in recipe:
            if foodItem.being_delivered:
                return False
            elif foodItem.amount < 3: #keep stocked up but could do away if looking for highest profit
                foodItem.order()
                if recipe.count(foodItem) > foodItem.amount:#need to come back and try again in 6 seconds
                    return False
    return True #if all else is well proceed to make the sushi

def make(recipe): #make food as fast as possible
    for foodItem in recipe:
        mousePos(foodItem.pos)
        leftClick()
        foodItem.amount -= 1
        time.sleep(0.18)
    foldmat()

def order_time_delay(foodItem): #ajusts for the delay when buying more food
        foodItem.being_delivered = True
        time.sleep(6.5) #it takes around 6.5 seconds for the order to come in
        foodItem.being_delivered = False
        foodItem.amount += foodItem.order_amount
        #print "ALL STOCKED UP"

def update(seat):
    
    if seat.emptyPixel == game_screen.getpixel(seat.location):
        seat.vacant = True
        seat.bubble = False
        
    else:
        seat.vacant = False
        seat.cleared = False
        if game_screen.getpixel(seat.bub_loc) == (250, 198, 168):
            seat.bubble = True

        else:
            seat.bubble = False

    
def main():
    global game_screen
    #startGame()
    #nextLevel()
    game_screen = screenGrab()
        
    while game_screen.getpixel((309,151)) != (245, 255, 233): #end of level screen
        
        for seat in seats:
            game_screen = screenGrab()
            update(seat)

            if seat.bubble and not seat.vacant:
                if not seat.ordered:
                    try: #when someone steals another's food and the order bubble disapears it results in a key error
                        order = sushi[seat.take_order()]
                        
                        if is_enough(order):
                            make(order)
                            seat.waiting_time = time.time()
                            seat.ordered = True

                        else:
                            seat.ordered = False
                            
                    except KeyError:
                        seat.ordered = False

                elif seat.waiting_time + 35 < time.time() and not seat.ordered_twice: #order again if they haven't received their order in 35 seconds
                    try:
                        order = sushi[seat.take_order()]

                        if order == wombocombo:
                            print is_enough(order)
                        
                        if is_enough(order):
                            make(order)
                            seat.ordered_twice = True

                            
                        else:
                            seat.ordered_twice = False
                    except KeyError:
                        seat.ordered = False

            elif seat.vacant:
                if seat.ordered:
                    mousePos(seat.plate)
                    leftClick()
                    seat.ordered = False
                    seat.ordered_twice = False
                    seat.vacant = True
                    seat.cleared = True

                elif not seat.cleared:
                    mousePos(seat.plate)
                    leftClick()
                    seat.ordererd = False
                    seat.ordered_twice = False
                    seat.cleared = True


                
    print "END OF LEVEL"
            


if __name__ == '__main__':
    main()








###########

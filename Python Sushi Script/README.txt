CS50 Final Project Submission
Marcus Kruger
December 31, 2017

Purpose: This program is designed to play the Sushi Go Round online flash game from the client side.

Description: The program recognizes what type of sushi the customer wants by analyzing screen captures. It then checks to see whether or not there are enough ingredients and proceeds to make the sushi.

Instructions: 
	
	1)Open the HTML file in the Chrome browser because the game assumes a specific location of the flash game on the screen.
	The dimensions must match SCREEN1.png

	2)Run application.py in IDLE. Make sure the IDLE and python editor positioned so that Sushi Go Round is fully visible. 
	Should resemble SCREEN2.png
	
	3)This program must be run at the start of each level. This is to avoid situations where the program would control the cursor for an undesirable amount of 		time.

	4)After the first level, there is a line of code in main() that must be commented out.
		Comment out startGame() on line 209
			&
		Uncomment nextLevel() on line 210
	Should resemble SCREEN3.png

WARNING: This program does take control of your cursor. In order to prematurely terminate the program simply put the computer to sleep (or in the case of a laptop simply close it). This will result in an IOError and stop the program.

Weaknesses:

	Because the borders are statically defined, the pixel positions needs to be manually updated when chrome updates/changes or the display dimensions change. Therefore, the script tends to malfunction unless the dimenions of the screen are the exact same as the one that I used to create this project.
	This program is resource intensive as it takes and processes many screenshots. Most errors arise out of the discrepancies between what the program perceives to be happening and what is actually happening. Sometimes the lefClick() function is not registered by the Sushi Go Round game and that results in other errors. There are many time.sleep() function calls peppered throughout the program to allow for processing time and allow for the game to react to the program.
	
Next Steps:
	The next steps to improving this project are to enable dynamic recognition of game borders and scale pixel sampling accordingly.

Sources:

Game: https://www.miniclip.com/games/sushi-go-round/en/

Tutorial: https://code.tutsplus.com/tutorials/how-to-build-a-python-bot-that-can-play-web-games--active-11117
This idea was taken from a tutorial demonstrating the basic concepts of how to build a program that can play flash games. This program improves upon the tutorial in three main ways: makes the program scallable with the use of objects; employs multithreading capabilities to better simulate the ordering time of food items; the main algorithm requires fewer assumptions and responds more dynamically. 

	
	

## Arduino Game 
(06/05/2021)

Inspired by the uber sucessful app "Flappy Bird," the goal of the game design was to create a simplified version of this. Ultimately it ressembled something closer to the app "Crossy Road." The project was a final assignment for a digital electronics lab. 

#Design Summary
The bird-like icon navigates through amaze of blocks. Its movement is user controlled. A Hitachi HD47880 LCD controller is powered by an Arduino Nano. The Arduino interprets two push button inputs (button 1 correlates to vertical motion, button 2 correlates to horizontal motion) to control the bird’s next move. If the icon collides with a maze block the user is notified and is prompted to press reset on the Arduino. If the icon makes it to the end of the maze, the user is notified and congratulated. 

A diagram of the hardware can be found [here](https://drive.google.com/file/d/1IgaXpi5LFQStU8pF7Zd6-mWAR1SxCoEL/view?usp=sharing). And a video of the game play is available on [YouTube](https://youtube.com/shorts/emP_VaV-6Og).

#Narrative of the Code
Before the setup(), all variables are defined as being constant or subject to change in the loop(). The code is looping at 9600 baud.

Under setup() the two shapes which will be displayed on the screen are constructed. There is ‘bigBlock’ which is a simple block shape hurdle the bird icon will have to navigate around. The second is the bird icon. It is referred to as ‘flappy’ or ‘flappy bird’ in the code.

Loop() runs through the followings steps to create a display.

1. The block icon is printed multiple times across the screen. The setCursor(col, row) function defined the location of each block. The full library of where the blocks are located was indexed into two arrays defined before ‘void setup( )’: columns[ ] and rows[ ]. The value of columns[i] always associated to row[i]. For example if I wanted to know the location of the third block I could find it under column[2] for its x position and row[2] for its y position.
2. A symbol indicating where the final cell is, that is where the bird is trying to get, is marked by character 219. Under the ASCII chart you will see that this is an open rectangle symbol. This is why ultimately I ended up naming the file “Bird Box” since the bird is trying to get into the box.
3. The Arduino identifies if the button state of each button matches it’s previous state. The current state becomes the previous state in the next loop. This is a quick fix on how to store and utilize previous states. The button states are read at a delayed rate of 20 ms.
4. The for loop evaluates three conditional statements. It repeats 9 times because there are nine blocks. Each time the for loop cycles it is asking will the bird’s next coordinate location match the coordinate location of one of the blocks? If the answer is yes, the game stops and the user is prompted on the display to hit reset on the Arduino. If the answer is no, the bird is permitted to move a step. If the answer is yes and the block it’s going to collide with is the winning box, the user is notified they have won with a message on the display.

#Challenges
To define a problem I need to first clarify how the display functions. It 2 rows of blocks. Each row has 16 blocks across. Each block contains 5x7 individual bits the can be programmed HI or LO. As to not confuse the LCD blocks with the maze blocks displayed on the screen, I will refer to the LCD blocks as cells from now on.

There were two major problems I faced. I originally designed a maze with blocks of varying heights. The initial idea was that a block could sit on the upper or lower half of a cell and the bird could occupy the other half of the cell. However, the system LCD interpreted each icon (block or bird) as occupying the entire cell. I could not figure out how to code so that they could display in the same cell at the same time. Anytime the bird would enter a cell with a block in it, the block would disappear. Because they were in the same block it could not work even if they were not occupying the same bits. I did not resolve how to make both icons display within the cell together. Instead, I opted only to use full size blocks for the maze which occupied the full length of the cell. The user can only move the bird between rows or from column x to x+1. The user cannot move the bird within an individual cell.

In my original code, I specified that the bird would move if the push button registered high. The problem was that the program loops in milliseconds. So although it seems to the user that the button is being pressed once, to the Arduino is was being pressed often between 3-7 times. On the display, it looked like every time the button was pressed the bird would jump across the screen a random number of cells. This was fixed in the code. Instead of movement being defined as the button being high, it was changed to a positive edge trigger. If the button was switching from low to high the bird would move one, otherwise it did not move. 

I was limited to two push button controls. The bird can move both up and down since there are only two rows. If bird cannot move up then it will move down. The bird can only move forward which means that if a user goes forward but wants to move back, it is not possible. The user’s only other option is to restart the game completely. 

Another minor problem is that you cannot clear an individual cell without clearing the entire screen. To move the bird forward, erase it from its current position, and make it reappear one cell forward, the entire screen has to be cleared and the entire maze has to be rebuilt. This was resolved with the loop() code specified under Narrative Explanation of the Code.

#Next time...
Looking forward, I would be interested to figure out how to dictate motion using a potentiometer instead of push buttons. I think the potentiometer could act as a joystick in substitution of the buttons. How much more directional freedom could I create for the bird icon if the motion was being interpreted through varying voltage input instead of a digital binary high/low input?

Also, I really would have liked to constructed a better solution to the block/bird occupying the same cell problem. The game could be more challenging and engaging if the obstacles were more complicated.

Let’s say the user successfully makes it through the maze that is currently displayed on the screen, I would have like to code new levels of the game. Ideally the mazes would get increasingly difficult with each level. But I am not confident that the Arduino sketch could handle storing the amount of memory it would take to create many levels of the game. I wonder, how many mazes could the code store? Is there a way to randomly generate the geography of the block mazes? Had I started my project earlier, I would have been interested in exploring this option.

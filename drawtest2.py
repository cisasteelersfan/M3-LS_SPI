# Import a library of functions called 'pygame'
import pygame
from math import pi
import numpy as np
# Initialize the game engine
pygame.init()

# Initialize the joysticks
pygame.joystick.init()

# Define the colors we will use in RGB format
BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)
 
# Set the height and width of the screen
sizex = 400
sizey = 400
size = [sizex, sizey]
screen = pygame.display.set_mode(size)
 
pygame.display.set_caption("Example code for the draw module")
 
joystick_count = pygame.joystick.get_count()

joystick = pygame.joystick.Joystick(0)

    
# Get the name from the OS for the controller/joystick
name = joystick.get_name()
#Loop until the user clicks the close button.
done = False
clock = pygame.time.Clock()


oldDotXaxis = int(sizex/2)
oldDotYaxis = int(sizey/2)
oldDotZaxis = 10
oldXdisplace = 0
oldYdisplace = 0
oldZdisplace = 0
btnPrevUp = True
btnPrevDown = False
f = 170

pygame.draw.circle(screen, BLUE, [oldDotXaxis, oldDotYaxis] ,oldDotZaxis)

while not done:
 
    # This limits the while loop to a max of 10 times per second.
    # Leave this out and we will use all CPU we can.
    clock.tick(60)
     
    for event in pygame.event.get(): # User did something
        if event.type == pygame.QUIT: # If user clicked close
            done=True # Flag that we are done so we exit this loop
 
    # All drawing code happens after the for loop and but
    # inside the main while done==False loop.
     
    # Clear the screen and set the screen background
    screen.fill(WHITE)
    joystick.init()
    joystick_count = pygame.joystick.get_count()
    
    ######################
    # BEGIN MANIPULATION #
    ######################

    button = joystick.get_button(0)
    
    if button == True:
        btnPrevDown = True
        if btnPrevUp:
            btnPrevUp = False

        dotXaxis = f*int(2+joystick.get_axis(0)-oldXdisplace+oldDotXaxis)
        dotYaxis = f*int(2+joystick.get_axis(1)-oldYdisplace+oldDotYaxis)
        dotZaxis = 2+int(joystick.get_axis(2))
        
        pygame.draw.circle(screen, BLUE, [dotXaxis, dotYaxis] , dotZaxis)
        
    else:
        btnPrevUp = True
        if btnPrevDown:
            oldDotXaxis = f*int(2+joystick.get_axis(0))
            oldDotYaxis = f*int(2+joystick.get_axis(1))
            oldDotZaxis = 2+int(joystick.get_axis(2))
            btnPrevDown = False
        oldXdisplace = f*int(joystick.get_axis(0))
        oldYdisplace = f*int(joystick.get_axis(1))
        oldZdisplace = 2-int(joystick.get_axis(2))
        pygame.draw.circle(screen, BLUE, [oldDotXaxis, oldDotYaxis] , oldDotZaxis)

    pygame.display.flip()
        
    # Go ahead and update the screen with what we've drawn.
    # This MUST happen after all the other drawing commands.
  
 
# Be IDLE friendly
pygame.quit()

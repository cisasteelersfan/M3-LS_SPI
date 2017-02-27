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
size = [400, 400]
screen = pygame.display.set_mode(size)

pygame.display.set_caption("Example code for the draw module")

joystick_count = pygame.joystick.get_count()

joystick = pygame.joystick.Joystick(1)


# Get the name from the OS for the controller/joystick
name = joystick.get_name()
#Loop until the user clicks the close button.
done = False
clock = pygame.time.Clock()

pygame.draw.circle(screen, BLUE, [200,200],4)
snewaxisx = 0
snewaxisy = 0
snewaxisz = 0
newaxisx = 0
newaxisy = 0
newaxisz = 0
axisx = 0
axisy = 0
axisz = 0
prevdown = True
prevup = True
f = 170

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


    # Draw a circle

    button = joystick.get_button(0)
    ncenterx = 0
    ncentery = 0

    if button == True:
        prevdown = True
        if prevup:
            ncenterx = snewaxisx
            ncentery = snewaxisy
            prevup = False
        axisx = joystick.get_axis(0)-snewaxisx
        axisy = joystick.get_axis(1)-snewaxisy
        axisz = joystick.get_axis(2)

        pygame.draw.circle(screen, BLUE, [int(f*(axisx-ncenterx)+200), int(f*(axisy-ncentery)+200)], int(10*(1.1+axisz)))


    else:
        prevup = True
        if prevdown:
            centerx = f*int(joystick.get_axis(1))+200
            centery = f*int(joystick.get_axis(2))+200
            oldx = int(f*(axisx+ncenterx)+200)
            oldy = int(f*(axisy+ncentery)+200)
            prevdown = False

        axisz = joystick.get_axis(2)
        pygame.draw.circle(screen, BLUE, [oldx+centerx, oldy+centery], int(10*(1.1+axisz)))

        snewaxisx = joystick.get_axis(0)
        snewaxisy = joystick.get_axis(1)
        snewaxisz = joystick.get_axis(2)

    pygame.display.flip()

    # Go ahead and update the screen with what we've drawn.
    # This MUST happen after all the other drawing commands.


# Be IDLE friendly
pygame.quit()

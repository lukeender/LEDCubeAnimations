# LEDCubeAnimations
A collection of 5x5x5 LED cube animations using the FastLED library

I recently built a 5x5x5 LED cube using PL9823 RGB LEDs, which are supported by the extremely well maintained multiplatform LED control library [FastLED](https://github.com/FastLED/FastLED). In this repository I'll be uploading and maintaining animations I've created for the cube using this library.


![LEDcube](https://i.imgur.com/icKBHii.jpg)

My LED cube.



## Animations ##

### Bounce ###
My first idea upon completing the cube was to recreate the infamous "bouncing logo" screensaver but in 3D space within the cube. The current version of this code works by randomizing the position and velocity of a "ball" within the cube, calculating the distance between this ball and each LED, and then activating the LEDs with brightness as function of this distance. The color of the LEDs is also blended over time for visual effect. Collisions with the wall are treated as perfectly elastic.

[Here](https://gfycat.com/GorgeousConfusedAfghanhound) is a video of the animation.

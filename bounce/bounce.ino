#include <FastLED.h>
#define LED_PIN     2 //data pin for LEDs
#define NUM_LEDS    125 //5*5*5

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
float coords[3]; // this holds the xyz coordinates for the bouncing balls. Range of 0 to 4.
float dt = .02; // the timestep 
float r[125] = {0}; // stores the distances between the ball and each LED
float v[3] = {0}; // the velocity of the ball

CRGBPalette16 currentPalette = PartyColors_p;
TBlendType    currentBlending = LINEARBLEND;
uint8_t colorIndex = 0;

void XYZtoLEDnum();
void timeStep();

void setup() {
   delay( 3000 ); // power-up safety delay
   FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   Serial.begin(9600);
   for (int i = 0; i < 3; i++){ // this loop randomizes the initial position and velocity of the ball
    coords[i] = random(40)/10;
    v[i] = random(20);
   }
}

void loop() {
   findNear(); // calculate all r[] distances
   
   for (int i = 0; i < 125; i++){ // set the bridgtness of every LED to go as r^7
      leds[i] = ColorFromPalette( currentPalette, colorIndex, (int)(255/pow(r[i],7)), currentBlending);
   }
  FastLED.show();
  FastLED.delay(1000*dt); //delay for timestep length
  timeStep(); // find new position values after for t+dt
  colorIndex += 1; // change the color to be selected from the palette
}

int XYZtoLEDnum(int x,int y,int z){ // converts xyz values to the corresponding LED number.
                                    // The LEDs are connected in a snaking pattern, reversing directions in x every other value of y.
  if ((y == 1) || (y == 3)) 
    x = -x + 4;
  return(x + 5*y + 25*z);
}

void timeStep(){ // very simple integration of velocity over time to get position
  for (int i = 0; i < 3; i++){
    coords[i] += v[i]*dt;
    if ((coords[i] > 4) || (coords[i] < 0)){ //detect collisions, model as perfectly elastic
      v[i] = -v[i];
    }
  }
}


void findNear(){ // because LEDs define the coordinate system, there is no reason to store their positions in arrays;
                 // we can simply loop through them.
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      for (int k = 0; k < 5; k++){
        r[XYZtoLEDnum(i,j,k)] = sqrt( pow((i - coords[0]),2) + pow((j - coords[1]),2) + pow((k - coords[2]),2)); // r = sqrt(x^2 + y^2 + z^2)
      }
}


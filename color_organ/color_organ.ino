// port for sound input.
int SOUND_PORT = 0;

// to store sound levels.
int sound = 0;

/*
 * analog pins to be used for pair of leds.
 * using analog pins to smooth out the intensity.
 */
int LED[5] = {3, 5, 6, 9, 10};

// delay for effect.
int DELAY = 10;

/*
 * Defining levels for sound so that
 * decision to turn LEDs on or off 
 * can be made.
 * LEVEL 0 - 50
 * LEVEL 1 - 100
 * LEVEL 2 - 150
 * LEVEL 3 - 200
 * LEVEL 4 - 250
 */
int LEVEL[5] = {50, 100, 150, 200, 250};

/*
 * Select the effect to be displayed here.
 * 1        - Linear Effect.
 * 2        - Random Effect.
 * default  - Random effect.
 */
int effect = 2;

void setup() {
  // inputs
  pinMode(SOUND_PORT, INPUT);
  
  // outputs
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(LED[4], OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the sound level.
  sound = analogRead(SOUND_PORT);
  // set the seed for random function based on sound.
  randomSeed(sound);
  switch (effect) {
    case 1:
      // show the effect.
      showLinearEffect(sound);
      // added some delay for a better show.
      delay(DELAY);
      break;
    case 2:
      showRandomEffect(sound);
      break;
    default:
      showRandomEffect(sound);
      break;
  }
}

void showLinearEffect(int sound) {
  setLEDIntensityBasedOnSoundAndLevel(LED[0], sound, LEVEL[0]);
  setLEDIntensityBasedOnSoundAndLevel(LED[1], sound, LEVEL[1]);
  setLEDIntensityBasedOnSoundAndLevel(LED[2], sound, LEVEL[2]);
  setLEDIntensityBasedOnSoundAndLevel(LED[3], sound, LEVEL[3]);
  setLEDIntensityBasedOnSoundAndLevel(LED[4], sound, LEVEL[4]);
}

void showRandomEffect(int sound) {
  setLEDIntensityBasedOnSoundAndLevel(LED[random(0,5)], sound, LEVEL[0]);
  setLEDIntensityBasedOnSoundAndLevel(LED[random(0,5)], sound, LEVEL[1]);
  setLEDIntensityBasedOnSoundAndLevel(LED[random(0,5)], sound, LEVEL[2]);
  setLEDIntensityBasedOnSoundAndLevel(LED[random(0,5)], sound, LEVEL[3]);
  setLEDIntensityBasedOnSoundAndLevel(LED[random(0,5)], sound, LEVEL[4]);
  delay(random(20, sound));
}

void setLEDIntensityBasedOnSoundAndLevel(int led, int sound, int level) {
  int intensity;
  if (sound > level) {
    intensity = calculateIntensity(sound, level);
    analogWrite(led, intensity);
  } else {
    analogWrite(led, LOW);
  }
}

int calculateIntensity(int sound, int level) {
  int differenceFromTheLevel;
  int calculatedIntensity;
  double scaledDifference;
  
  // Calculate the difference between the sound level and the given level.
  differenceFromTheLevel = sound - level;
  // Scale it down to a range of 0 to 5.
  scaledDifference = (double) differenceFromTheLevel / 10;
  // Calculate intensity and return it.
  calculatedIntensity = (int) 51 * scaledDifference;
  
  return calculatedIntensity;
}

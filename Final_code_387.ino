#include <HX711.h>


HX711 scaleright;
HX711 scalecenter;
HX711 scaleleft;

#define calibration_factorright -8800.0 
#define calibration_factorcenter -8200.0
#define calibration_factorleft -8500.0

float current_weightright;
float start_weightright;

float current_weightcenter;
float start_weightcenter;

float current_weightleft;
float start_weightleft;

#define DOUTright  26
#define CLKright  24

#define DOUTcenter  25
#define CLKcenter  27

#define DOUTleft  29
#define CLKleft  31

int left_LED = 48;
int right_LED = 38;
int center_LED = 49;
int piezo = 5;

int randNum;


void setup() {
  
  Serial.begin(9600);

  randNum = random(3); //randomely selects a number between 0 and 2

  Serial.println("Leg Throw Game");
  scaleright.begin(DOUTright, CLKright); //begins reading values taken in from the scale
  scaleright.set_scale(calibration_factorright); //This value is obtained by using the HX711_Calibration sketch
  scaleright.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.print("Reading Right: ");
  start_weightright = scaleright.get_units(); //scale.get_units() returns a float
  Serial.print(start_weightright, 1);
  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();

  scalecenter.begin(DOUTcenter, CLKcenter);
  scalecenter.set_scale(calibration_factorcenter); 
  scalecenter.tare(); 

  Serial.print("Reading Center: ");
  start_weightcenter = scalecenter.get_units(); 
  Serial.print(start_weightcenter, 1);
  Serial.print(" lbs"); 
  Serial.println();

  scaleleft.begin(DOUTleft, CLKleft);
  scaleleft.set_scale(calibration_factorleft); 
  scaleleft.tare();

  Serial.print("Reading Left: ");
  start_weightleft = scaleleft.get_units(); 
  Serial.print(start_weightleft, 1);
  Serial.print(" lbs"); 
  Serial.println();

}

void throw_left() { // function for when you have to hit the left scale

  digitalWrite(left_LED, HIGH);
  if (current_weightleft >= start_weightleft + 5) {
    digitalWrite(left_LED, LOW);


    delay(3000);
    randNum = random(3);
  } else if (current_weightright >= start_weightright + 5 || current_weightcenter >= start_weightcenter + 5) {
    randNum = 4;
  }
}

void throw_right() { // function for when you have to hit the right scale

  digitalWrite(right_LED, HIGH);

  if (current_weightright >= 5) {
    digitalWrite(right_LED, LOW);
    delay(3000);
    randNum = random(3);
  } else if (current_weightleft >= start_weightleft + 5 || current_weightcenter >= start_weightcenter + 5) {
    randNum = 4;
  }
}

void throw_center() { // function for when you have to hit the center scale

  digitalWrite(center_LED, HIGH);

  if (current_weightcenter >= 5) {
    digitalWrite(center_LED, LOW);
    delay(3000);
    randNum = random(3);
  } else if (current_weightleft >= start_weightright + 5 || current_weightright >= start_weightleft + 5) {
    randNum = 4;
    }
}

void gameover() { //gameover if you hit the wrong scale
  digitalWrite(left_LED, HIGH);
  digitalWrite(right_LED, HIGH);
  digitalWrite(center_LED, HIGH);
  tone(5, 2000);
  delay(100);
  digitalWrite(left_LED, LOW);
  digitalWrite(right_LED, LOW);
  digitalWrite(center_LED, LOW);
  tone(5, 2000);
  delay(100);
  digitalWrite(left_LED, HIGH);
  digitalWrite(right_LED, HIGH);
  digitalWrite(center_LED, HIGH);
  tone(5, 2000);
  delay(100);
}
void loop() {
  // keeps checking for the hit on the scales
  Serial.print("Reading Right: "); 
  current_weightright = scaleright.get_units(); 
  Serial.print(start_weightright, 1);
  Serial.print(" lbs"); 
  Serial.println();

  Serial.print("Reading Center: "); 
  current_weightcenter = scalecenter.get_units(); 
  Serial.print(start_weightcenter, 1);
  Serial.print(" lbs"); 
  Serial.println();

  Serial.print("Reading Left: "); 
  current_weightleft = scaleleft.get_units(); 
  Serial.print(start_weightleft, 1);
  Serial.print(" lbs"); 
  Serial.println();
  
  //Loop to pick which way to throw legs or if its a game over
  if (randNum == 0) {
    throw_left();
  }
  else if (randNum == 1) {
    throw_right();
  }
  else if (randNum == 2){
    throw_center();
  }
  else if (randNum == 4){
    gameover();
  }
  
}

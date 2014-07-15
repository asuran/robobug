#include <Servo.h>
#include <Oscillator.h>

class Robobug
{
  public:
 Oscillator osc_middle;
 Oscillator osc_left;
 Oscillator osc_right;
 
 public:
 void init()
 {
   osc_middle.attach(4); // 2,3 and 4 are the digital pins
  osc_right.attach(2);
  osc_left.attach(3);
   osc_middle.SetO(15); // Correction for the offset of the servos
  osc_right.SetO(0);
  osc_left.SetO(0);
   osc_middle.SetA(10); // Middle motor needs a small amplitude (5-10)
  osc_right.SetA(30);
  osc_left.SetA(30);
   osc_middle.SetT(3000); // Set the period of work
  osc_right.SetT(3000);
  osc_left.SetT(3000);
   osc_middle.SetPh(DEG2RAD( 90 ));
  osc_left.SetPh(  DEG2RAD( 0 )); 
  osc_right.SetPh( DEG2RAD( 0 ));
 }
 void setForwardState()
 {
   osc_right.SetPh( DEG2RAD( 0 ));
   osc_left.SetPh( DEG2RAD( 0 ));
 }
 void setLeftState()
 {
   osc_right.SetPh( DEG2RAD( 0 ));
   osc_left.SetPh( DEG2RAD( 180 ));
 }
 void setRightState()
 {
   osc_right.SetPh( DEG2RAD( 180 ));
   osc_left.SetPh( DEG2RAD( 0 ));
 }
 void setBackState()
 {
   osc_right.SetPh( DEG2RAD( 180 ));
   osc_left.SetPh( DEG2RAD( 180 ));
 }
 void refresh()
 {
   osc_middle.refresh();
   osc_right.refresh();
   osc_left.refresh();
 }
};

Robobug robot;

/*Oscillator osc_left;
osc_left.attach(2);*/

void setup() {
   robot.init();
}

void loop() {
  robot.refresh();
}

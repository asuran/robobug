#include <Servo.h>
#include <Oscillator.h>
#include <Ultrasonic.h>

class Robobug
{
  public:
 Oscillator osc_middle;
 Oscillator osc_left;
 Oscillator osc_right;
 Servo grab;
 int state;  //-1 - stop, 0-forward, 1 - left, 2 - right
 
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
   
   osc_middle.SetT(1000); // Set the period of work
   osc_right.SetT(1000);
   osc_left.SetT(1000);
   
   osc_middle.SetPh(DEG2RAD( 90 ));
   osc_left.SetPh(  DEG2RAD( 0 )); 
   osc_right.SetPh( DEG2RAD( 0 ));
   
   state = 0;
   
   grab.attach(5);
   grab.write(120);
 }
 void setForwardState()
 {
   osc_right.SetPh( DEG2RAD( 0 ));
   osc_left.SetPh( DEG2RAD( 0 ));
   state = 0;
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
 void setRandomTurnState()
 {
    if(state == 0)
    {
     if(random(2) == 0)
     {
       state = 1;
     }
     else
     {
       state = 2;
     } 
    }
    int time1 = millis();
    int time2 = millis();
    while(time2 - time1 < 5000)
    {
     time2 = millis();
     switch(state)
     {
       case 1: setLeftState(); break;
       case 2: setRightState(); break;
     }
     refresh();
    }
 }
 void setStopState()
 {
   state = -1; 
 }
 void refresh()
 {
   if(state >= 0)
   {
     osc_middle.refresh();
     osc_right.refresh();
     osc_left.refresh();
   }
 }
  bool hasObject()
  {
    return !digitalRead(6); 
  }
  void clench()
  {
    grab.write(170);
  }
  void unclench()
  {
    grab.write(120); 
  }
};

Robobug robot;
Ultrasonic ultrasonic(12, 11);


void setup() {
   randomSeed(analogRead(0));
   robot.init();
}

void loop() {
  unsigned int time = millis();
  if(checkRange(20))
  {
    robot.setRandomTurnState();
  }
  else if(robot.hasObject())
  {
    robot.setStopState();
    robot.clench();
  }
  else
  {
    robot.setForwardState();
    robot.unclench(); 
  }
  
  robot.refresh();
}

bool checkRange(int distanse)
{
  static int i = 0;
  static int resultsArray[20] = {distanse};
  int sum = 0, average = 0;
  int dist = ultrasonic.Ranging(1);  //CM
  if(dist > 0 && dist < 1000)
  {
    resultsArray[i] = dist;
    if(i < 10)
    { 
      i++;
    }
   else
   {
     i=0;
   }
  }
  for(int j = 0; j < 10; j++)
  {
    sum += resultsArray[j]; 
  }
  average = sum / 10;
  if(average < distanse)
  {
    return true;
  }
  else
  {
    return false;
  }
}

#include <NewPing.h>
#define TRIGGER_PIN_L  13  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_L     12  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_R  10  
#define ECHO_PIN_R     11  


#define MAX_DISTANCE 60 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MIN_DISTANCE 1

// Left  motor 
#define IN1  6
#define IN2  5

// Right Motor 
#define IN3  4
#define IN4  3

// Velocity
#define vel  255


// Cases for  Braitenberg modes
#define love  2
#define fear 3


/*
// weights for nominal velocities LOVE
#define w0_L 180
#define w0_R 180
// weight for sensors LOVE
#define w1_L 130
#define w1_R 130

*/


// weights for nominal velocities FEAR
#define w0_L 50
#define w0_R 50
// weight for sensors FEAR
#define w1_L 150
#define w1_R 150


float  s1 = 0; // Left sensor
float  s2 = 0; // Right sensor

// wheels final velocities intialization 
float v_L = 0; 
float v_R = 0;

NewPing sonarL(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
NewPing sonarR(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);    
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);    
  pinMode(IN4, OUTPUT);
}

void loop() {
// Data from sensors
  delay(35);
  unsigned int uS_L = sonarL.ping();
  delay(50);
  unsigned int uS_R = sonarR.ping();
  
  unsigned int distance_L = sonarL.convert_cm(uS_L);
  unsigned int distance_R = sonarR.convert_cm(uS_R);
 // Serial.print("distance L ");
 // Serial.println(distance_L);
 // Serial.print("distance R ");
 // Serial.println(distance_R);


    // LOVE mode = 2,  FEAR mode = 3
   int mode = 3;
   
   switch(mode)
   {
    case love:
      // LOVE
      if( distance_L == 0 && distance_R == 0)
      {
        analogWrite(IN1,0);
        analogWrite(IN2,0);
        analogWrite(IN3,0);
        analogWrite(IN4,0);
        
      }
      else
      {
      s1 = getSensorStatus(distance_L);
      s2 = getSensorStatus(distance_R);
    
      v_L = w0_L - (s1*w1_L);
      v_R = w0_R - (s2*w1_R);
      
      analogWrite(IN1,0);
      analogWrite(IN2,v_L);
      analogWrite(IN3,0);
      analogWrite(IN4,v_R);
      }

      Serial.print("wL: ");
      Serial.println(v_L);
      Serial.print("wR: ");
      Serial.println(v_R);
      break;

    case fear:
      // FEAR
      if( distance_L == 0 && distance_R == 0)
      {
        v_L = 35;
        v_R = 35;
        analogWrite(IN1,0);
        analogWrite(IN2,v_L);
        analogWrite(IN3,0);
        analogWrite(IN4,v_R);
      }
      else
      {
      s1 = getSensorStatus(distance_L);
      s2 = getSensorStatus(distance_R);
      
      if(s1 && s2)
      {
        v_L = 35;
        v_R = 35;
        analogWrite(IN1,0);
        analogWrite(IN2,v_L);
        analogWrite(IN3,0);
        analogWrite(IN4,v_R); 
      }
      else
      {

      v_L = w0_L + (s1*w1_L);
      v_R = w0_R + (s2*w1_R);
      
      analogWrite(IN1,0);
      analogWrite(IN2,v_L);
      analogWrite(IN3,0);
      analogWrite(IN4,v_R);
      }
      }
      Serial.print("wL: ");
      Serial.println(v_L);
      Serial.print("wR: ");
      Serial.println(v_R);
      
      break;

    default:
    break;
   }

}

/*
float getSensorStatus(int d_i)
{
  return (1-((d_i-MIN_DISTANCE)/(MAX_DISTANCE-MIN_DISTANCE)));
}
*/


int getSensorStatus(int d_i)
{
  if(d_i)
    return 1;
  else
    return 0; 
    
  

}

#include <Wire.h>
#include <AS5600.h>

#include <AccelStepper.h>
AccelStepper stepper(1,A0,A1);

AMS_5600 ams5600;

double rawAngleToDeg(word angle)
{
  return angle * 0.087d;
}

void moveTo(double angle) {
  
  double currentAngle = rawAngleToDeg(ams5600.getRawAngle());
  double distance = angle - currentAngle;
  double speed = 10 * distance * abs(distance);
    Serial.print(distance);
    Serial.print(" ");
        Serial.print(speed);
    Serial.print(" ");
    Serial.println(currentAngle);
  stepper.setSpeed(-speed);
  stepper.moveTo(stepper.currentPosition() - speed);
  
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  stepper.setMaxSpeed(100);
  stepper.setAcceleration(200);
}

void loop()
{
  moveTo(200);
    
  stepper.runSpeed();
}

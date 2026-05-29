#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(9, 10); // RX, TX

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

String command = "";
char currentState = 'S'; // Default STOP

void setup()
{

  bluetoothSerial.begin(9600);
}

void loop()
{
  // Read voice command
  while (bluetoothSerial.available())
  {
    char c = bluetoothSerial.read();
    command += c;
    delay(5);
  }

  if (command.length() > 0)
  {
    command.trim();

    if (command == "forward") currentState = 'F';
    else if (command == "back") currentState = 'B';
    else if (command == "left") currentState = 'L';
    else if (command == "right") currentState = 'R';
    else if (command == "stop") currentState = 'S';

    command = "";
  }

  // Execute continuously
  switch (currentState)
  {
    case 'F':
      forward();
      break;

    case 'B':
      back();
      break;

    case 'L':
      forwardLeft();   // changed
      break;

    case 'R':
      forwardRight();  //  changed
      break;

    case 'S':
      Stop();
      break;
  }
}

// ===== FUNCTIONS =====

void forward()
{
  setSpeed(180, 180);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void back()
{
  setSpeed(180, 180);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

//  LEFT TURN (forward + slow left side)
void forwardLeft()
{
  setSpeed(100, 200); // left slow, right fast
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

//  RIGHT TURN (forward + slow right side)
void forwardRight()
{
  setSpeed(200, 100); // left fast, right slow
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// Custom speed: left side motors & right side motors
void setSpeed(int leftSpeed, int rightSpeed)
{
  // Left motors
  motor1.setSpeed(leftSpeed);
  motor2.setSpeed(leftSpeed);

  // Right motors
  motor3.setSpeed(rightSpeed);
  motor4.setSpeed(rightSpeed);
}
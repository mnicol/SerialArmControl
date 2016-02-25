#include <Servo.h>

#define ROTATE 0
#define BASE 1
#define ELBOW 2
#define WRIST 3
#define GRIP 4

int inbyte;
int nextByte;
int length;
int opcode;
int servoNum;

// Used for servo move to degree
int degree;
int moveAmount;
int number;
boolean done;

// Servo positions
int rotatePos;
int basePos;
int elbowPos;
int wristPos;
int handPos;

Servo BaseRotate;     // HS-485HB   (600 | 1500 | 2400)
Servo ArmBase;        // HS-805BB+  (600 | 1500 | 2400)
Servo Elbow;          // HS-755HB   (600 | 1500 | 2400)
Servo Wrist;          // HS-645MG   (600 | 1500 | 2400)
Servo Hand;           // HS-425BB   (600 | 1500 | 2400)

void setup()
{
  Serial.begin(9600);
  
  // Setup Servos
  // Setup servos
  BaseRotate.attach(11, 600, 2400);
  ArmBase.attach(10, 600, 2400);
  Elbow.attach(9, 600, 2400);
  Wrist.attach(6, 600, 2400);
  Hand.attach(5, 600, 2400);
  
  rotatePos = 90;
  basePos = 90;
  elbowPos = 90;
  wristPos = 90;
  handPos = 0;
}

void loop()
{
  // Variables
  opcode = -1;
  
  nextByte = Serial.read();
  
  // Start reception of data
  if(nextByte >= 0 && nextByte != ';')
  {
    ///////////////////////////////////////////////
    // First two bytes are for the opcode        //
    ///////////////////////////////////////////////
    
    // Set the first number to the tens index
    opcode = (nextByte-48) * 10;
    
    // Get next value
    nextByte = getNextByte();
    
    // Add the ones data
    opcode += inbyte-48;
    
    ///////////////////////////////////////////////
    // Next two bytes are the opcode             //
    ///////////////////////////////////////////////
    
    switch(opcode)
    {
      // Move servo to degree
      case 0:
        
        nextByte = getNextByte();
        
        servoNum = nextByte - 48;
  
        degree = getInt();
        
        if(degree > 180)
          degree = 180;
        if(degree < 0)
          degree = 0;
        
        moveToDegree(servoNum, degree);
        
      break;
      
      // Move servo by amount (+)
      case 1:
        nextByte = getNextByte();
        servoNum = nextByte - 48;
        
        moveAmount = getInt();
        
        moveByOffset(servoNum, moveAmount);
        
      break;
      
      // Move servo by amount (-)
      case 2:
        nextByte = getNextByte();
        servoNum = nextByte - 48;
        
        moveAmount = getInt();
        
        moveByOffset(servoNum, -moveAmount);
        
      break;
      
      default:
        Serial.print("ERROR: Illegal Opcode - ");
        Serial.print(opcode);
        Serial.println();
    } 
  }
}

int getNextByte()
{
  inbyte = Serial.read();
  while(inbyte < 0 && inbyte != ';')
    inbyte = Serial.read();
  
  return inbyte;
}

// Gets an integer terminated with a ;
int getInt()
{
  number = 0;
  done = false;
  
  // Get the degree to move to
  nextByte = getNextByte();
    
  while(!done)
  {
    // Check if byte is non zero
    if((nextByte-48) >= 0 && nextByte != ';')
    {
      number = number * 10;
      number += (nextByte-48);
      
      // Get next byte
      nextByte = getNextByte();
    }
    else
    {
      done = true;
    }
  }
  return number;
}

// Function to parse out serial data
void moveToDegree(int servo, int degree)
{
  switch(servo)
  {
     case ROTATE:
       Serial.print("Rotate to ");
       Serial.println(degree);
       BaseRotate.write(degree);
       break; 
       
     case BASE:
       Serial.print("Base to ");
       Serial.println(degree);
       ArmBase.write(degree);
       break;
       
     case ELBOW:
       Serial.print("Elbow to ");
       Serial.println(degree);
       Elbow.write(degree);
       break;
  
    case WRIST:
       Serial.print("Wrist to ");
       Serial.println(degree);
       Wrist.write(degree);
       break;
       
     case GRIP:
       Serial.print("Grip to ");
       Serial.println(degree);
       Hand.write(degree);
       break;
       
     default:
       Serial.print("ERROR: Illegal Servo - ");
       Serial.println(servo);
  } 
}


void moveByOffset(int servo, int moveAmount)
{
  switch(servo)
  {
     case ROTATE:
       Serial.print("Rotate by ");
       Serial.println(moveAmount);
       
       rotatePos += moveAmount;
       
       if(rotatePos > 180)
         rotatePos = 180;
         
       if(rotatePos < 0)
         rotatePos = 0;
       
       BaseRotate.write(rotatePos);
       
     break; 
       
     case BASE:
       Serial.print("Base by ");
       Serial.println(moveAmount);
       
       basePos += moveAmount;
       
       if(basePos > 180)
         basePos = 180;
         
       if(basePos < 0)
         basePos = 0;
       
       ArmBase.write(basePos);
     break;
       
     case ELBOW:
       Serial.print("Elbow by ");
       Serial.println(moveAmount);
       
       elbowPos += moveAmount;
       
       if(elbowPos > 180)
         elbowPos = 180;
         
       if(elbowPos < 0)
         elbowPos = 0;
       
       Elbow.write(elbowPos);
     break;
  
    case WRIST:
       Serial.print("Wrist by ");
       Serial.println(moveAmount);
       
       wristPos += moveAmount;
       
       if(wristPos > 180)
         wristPos = 180;
         
       if(wristPos < 0)
         wristPos = 0;
       
       Wrist.write(wristPos);
     break;
       
     case GRIP:
       Serial.print("Grip by ");
       Serial.println(degree);
       
       handPos += moveAmount;
       
       if(handPos > 180)
         handPos = 180;
         
       if(handPos < 0)
         handPos = 0;
       
       Hand.write(handPos);
     break;
       
     default:
       Serial.print("ERROR: Illegal Servo - ");
       Serial.println(servo);
  }
}


#include <Servo.h>
#include <SerialCommand.h>

int PWM1 = 9;   //control servo
int PWM_CE = 11;  //servo enable

int AIN1 = 4;  //control motor
int AIN2 = 5;  //control motor
int AIN3 = 6;  //control motor
int AIN4 = 7;  //control motor

int BIN3 = A2;  //control laser
int BIN4 = A3;  //control laser

Servo myservo;
SerialCommand sCmd;

uint8_t camera_angle = 120;
uint8_t camera_angle_range[] = {
  60, 150
};
uint8_t laser_is_on = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

//  while (!Serial);
  Serial.println("----- Car ----");
  
  // initialize the digital pin as an output.
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN3, OUTPUT);
  pinMode(AIN4, OUTPUT);
  pinMode(BIN3, OUTPUT);
  pinMode(BIN4, OUTPUT);
  digitalWrite(BIN3, LOW);  // turn off LASER
  digitalWrite(BIN4, LOW);

  pinMode(PWM_CE, OUTPUT);
  myservo.attach(PWM1);
  digitalWrite(PWM_CE, HIGH);
  myservo.write(camera_angle);
  digitalWrite(PWM_CE, LOW); //disable servo


  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("laser", trigger_laser);
  sCmd.addCommand("camera", adjust_camera);
  sCmd.addCommand("motor", set_motor);
  sCmd.setDefaultHandler(unrecognized);
}

// the loop routine runs over and over again forever:
void loop() {
  sCmd.readSerial();
}

void trigger_laser()
{
  if (laser_is_on) {
    digitalWrite(BIN3, LOW);  // turn off LASER
    laser_is_on = 0;
    Serial.println("laser off");
  }
  else {
    digitalWrite(BIN3, HIGH);  // turn on LASER
    laser_is_on = 1;
    Serial.println("laser on");
  }
}

void adjust_camera()
{
  char *param;

  param = sCmd.next();
  if (!strcmp(param, "down")) {
    if (camera_angle < camera_angle_range[1]) {
      camera_angle += 10;

      digitalWrite(PWM_CE, HIGH);
      myservo.write(camera_angle);
      digitalWrite(PWM_CE, HIGH);
    }
  }
  else if (!strcmp(param, "up")) {
    if (camera_angle > camera_angle_range[0]) {
      camera_angle -= 10;

      digitalWrite(PWM_CE, HIGH);
      myservo.write(camera_angle);
      digitalWrite(PWM_CE, HIGH);
    }
  }

  Serial.print("camera angle: ");
  Serial.println(camera_angle);
}

void set_motor()
{
  char *param;
  int16_t left = 0;
  int16_t right = 0;

  param = sCmd.next();
  if (param == NULL) {
    return;
  }
  left = atoi(param);

  param = sCmd.next();
  if (param == NULL) {
    return;
  }
  right = atoi(param);

  Serial.print("motor ");
  Serial.print(left);
  Serial.print(" ");
  Serial.println(right);


  if (left > 30) {
    analogWrite(AIN2, left);
    digitalWrite(AIN1, LOW);
  } else if (left < -30)  {
    analogWrite(AIN2, 255 + left);
    digitalWrite(AIN1, HIGH);
  }
  else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }

  if (right > 30) {
    analogWrite(AIN3, right);
    digitalWrite(AIN4, LOW);
  }
  else if (right < -30) {
    analogWrite(AIN3, 255 + right);
    digitalWrite(AIN4, HIGH);
  }
  else {
    digitalWrite(AIN3, LOW);
    digitalWrite(AIN4, LOW);
  }

}


// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println('?');
}



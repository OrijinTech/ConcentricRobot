#include <Arduino.h>
#include <CONFIG.h>
#include <button.h>
#include <Joystick.h>
#include <Stage.h>

// ------------------- Stage Objects
bool reversed = true;
Stage *outerStage = new Stage(new PIDMotor(.5, 0.0, 0, 0, 0, 
                                  new Motor(MOTOR1_EN, MOTOR1_IN1, MOTOR1_IN2, reversed), 
                                  new Encoder(ENCPIN1_1, ENCPIN1_2), 0),
                              new PIDMotor(.3, 0.0, 0.0, 0, 0, 
                                  new Motor(MOTOR2_EN, MOTOR2_IN1, MOTOR2_IN2, false),
                                  new Encoder(ENCPIN2_1, ENCPIN2_2), 1),
                                new Joystick(JOY1_X, JOY1_Y));

Stage *innerStage = new Stage(new PIDMotor(.5, 0.0, 0, 0, 0, 
                                  new Motor(MOTOR3_EN, MOTOR3_IN1, MOTOR3_IN2, reversed), 
                                  new Encoder(ENCPIN3_1, ENCPIN3_2), 0),
                              new PIDMotor(.3, 0.0, .0, 0, 0, 
                                  new Motor(MOTOR4_EN, MOTOR4_IN1, MOTOR4_IN2, false),
                                  new Encoder(ENCPIN4_1, ENCPIN4_2), 1),
                              new Joystick(JOY2_X, JOY2_Y));
  

//------------------ Buttons
/**
 * Modes:
 * 0 - PID
 * 1 - Manual Joystick ctrl
 **/
Button mode_butt(MODE_BUTT, 5);
int mode = 0;
int max_mode = 1;

// iterate through setpoints
Button sp_butt(SP_BUTT, 5);
int outerSP_list[2] = {0, 0};
int innerSP_list[2] = {25, 0};
int curr_sp = 0;


// ------------------ others
bool debug = false;
long printTimer = 0;


void setup() {
  // put your setup code here, to run once:
  
  // change pwm frequencies for enable pins
  TCCR4B = (TCCR4B & B11111000) | B00000001;   // for PWM frequency of 31372.55 Hz for D11 & D12
  TCCR5B = (TCCR5B & B11111000) | B00000001;  // for PWM frequency of 31372.55 Hz for D44 & D46

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  mode_butt.Init();
  sp_butt.Init();
  outerStage->Init();
  innerStage->Init();

  // outerStage->setSetpoints(20, 0);
  // innerStage->setSetpoints(20, 0);
  outerStage->goHome();
  innerStage->goHome();

  Serial.begin(115200);
  Serial.println("Beginning Loop");
  Serial.println("LED: Green = Manual  Blue = PID");
}

void loop() {
  // switch between modes on button press 
  if (mode_butt.CheckButtonPress()){
    mode = mode + 1;
    if (mode > max_mode) mode = 0;
  }

  // check button press and go to next point
  if (sp_butt.CheckButtonPress()){
    curr_sp ++;
    if (curr_sp >= 2 ) curr_sp = 0;

    // go to next point
    Serial.print("Change Setpoint ");
    Serial.println(curr_sp);

    if (curr_sp  == 1){
      outerStage->setSetpoints(outerSP_list[0], outerSP_list[1]);
      
      innerStage->setSetpoints(innerSP_list[0], innerSP_list[1]);
    } 
    // go home every otherpoint
    else{
        outerStage->goHome();
        innerStage->goHome();
    }

  }


  if (mode == 0){
    // stages driven manually by joysticks
    // LED is green

    digitalWrite(LED_G, 1);
    digitalWrite(LED_B, 0);

    outerStage->manualDrive();
    innerStage->manualDrive();
  }
  else if (mode == 1){
    // stages driven by PID to defined setpoint
    // LED is blue

    digitalWrite(LED_G, 0);
    digitalWrite(LED_B, 1);

    outerStage->calculatePID();
    innerStage->calculatePID();
  }

  // if 1 s has passed, print
  if ((millis() - printTimer > 1000) && debug){
    // outerStage->printPos();
    outerStage->printPID();
    Serial.print("\tInner: ");
    innerStage->printPID();
    Serial.println();
    printTimer = millis();
  }
  
  delay(1);
}
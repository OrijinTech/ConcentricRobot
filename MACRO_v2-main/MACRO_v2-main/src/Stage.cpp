#include "Stage.h"

Stage::Stage(PIDMotor* trans, PIDMotor* rot, Joystick* js){
    this->transMotor = trans;
    this->rotMotor = rot;
    this->js = js;
}

void Stage::Init(){
    this->js->Init();
    this->transMotor->Init();
    this->rotMotor->Init();
}

void Stage::calculatePID(){
    this->transMotor->calculate();
    this->rotMotor->calculate();
}

void Stage::manualDrive(){
    this->transMotor->runMotor(this->js->readX());
    this->rotMotor->runMotor(this->js->readY()); 
}

void Stage::goHome(){
    this->transMotor->setSetpoint(this->transMotor->getHome());
    this->rotMotor->setSetpoint(this->rotMotor->getHome());
}

// ------------- Cascaded Functions
void Stage::setHomePosition(){
    this->transMotor->setHomePosition();
    this->rotMotor->setHomePosition();
}


void Stage::setSetpoints(double transSP, double rotSP){
    this->transMotor->setSetpoint(transSP);
    this->rotMotor->setSetpoint(rotSP);
}

    
bool Stage::setpointReached(){
    return this->transMotor->setpointReached() && this->rotMotor->setpointReached();
}


// --------------------- PRINT FUNCTIONS ---------------
void Stage::printJoystick(){
    sprintf(this->txt, "X Val: %d\t Y Val: %d", (int)(this->js->readX()*1000), (int)(this->js->readY()*1000));
    Serial.print(this->txt);
}

void Stage::printPos(){
    Serial.print("Trans: ");
    Serial.print(this->transMotor->getPos());
    Serial.print("mm  Rot: ");
    Serial.print(this->rotMotor->getPos());
    Serial.print("deg  ");

    // sprintf(this->txt, "Trans: %dmm\t Rot: %ddeg", this->transMotor->getPos(), this->rotMotor->getPos());
    // Serial.print(this->txt);
}

void Stage::printPID(){
    Serial.print("Trans SP: ");
    Serial.print(this->transMotor->getSetpoint());
    Serial.print("mm Error:  ");
    Serial.print(this->transMotor->getCurrError());
    
    Serial.print(" Rot SP: ");
    Serial.print(this->rotMotor->getSetpoint());
    Serial.print("deg Error:  ");
    Serial.print(this->rotMotor->getCurrError());
}
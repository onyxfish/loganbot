#include <AFMotor.h>
#include <PS2X_lib.h>

AF_DCMotor front_left(2);
AF_DCMotor front_right(1);
AF_DCMotor rear_left(3);
AF_DCMotor rear_right(4);

PS2X ps2x;

const int CLOCK_PIN = 2; // blue
const int COMMAND_PIN = 9; // orange
const int ACK_PIN = 10; // yellow
const int DATA_PIN = 13; // brown

int error = 0; 
byte left_speed = 0;
byte right_speed = 0;
byte mode = RELEASE;
byte speed = 0;

void setup() {
    Serial.begin(9600);

    /*error = ps2x.config_gamepad(CLOCK_PIN, COMMAND_PIN, ACK_PIN, DATA_PIN, false, false); 

    if (error == 1) {
        Serial.println("Controller not found.");
    } else if (error == 2) {
        Serial.println("Controller not accepting commands.");
    } else if (error == 3) {
        Serial.println("Controller refusing to enter pressure mode. ");
    }

    byte type = ps2x.readType(); 
    
    Serial.println(type);

    if (type != 1) {
        Serial.println("Unknown controller type.");
    }*/

    set_front_left(0, RELEASE);
    set_front_right(0, RELEASE);
    set_rear_left(0, RELEASE);
    set_rear_right(0, RELEASE);
}

void set_front_left(byte speed, byte mode) {
    front_left.setSpeed(speed);
    front_left.run(mode);
}

void set_front_right(byte speed, byte mode) {
    if (mode == FORWARD) {
        mode = BACKWARD;
    } else if (mode == BACKWARD) {
        mode = BACKWARD;
    } else {
        mode = RELEASE;
    }

    front_right.setSpeed(speed);
    front_right.run(mode);
}

void set_rear_left(byte speed, byte mode) {
    if (mode == FORWARD) {
        mode = BACKWARD;
    } else if (mode == BACKWARD) {
        mode = BACKWARD;
    } else {
        mode = RELEASE;
    }

    rear_left.setSpeed(speed);
    rear_left.run(mode);
}

void set_rear_right(byte speed, byte mode) {
    rear_right.setSpeed(speed);
    rear_right.run(mode);
}

void loop() {
    if (error == 1) {
        return; 
    }
  
    /*ps2x.read_gamepad(); 
    
    left_speed = ps2x.Analog(PSS_LY);
    right_speed = ps2x.Analog(PSS_RY);

    if (left_speed >= 118 && left_speed <= 138) {
        speed = 0;
        mode = RELEASE;
    }
    else if (left_speed < 128) {
        speed = (128 - left_speed) * 2;
        mode = FORWARD;
    } else {
        speed = (left_speed - 128) * 2;
        mode = BACKWARD;
    }

    set_left(speed, mode);

    if (right_speed >= 118 && right_speed <= 138) {
        speed = 0;
        mode = RELEASE;
    }
    else if (right_speed < 128) {
        speed = (128 - right_speed) * 2;
        mode = FORWARD;
    } else {
        speed = (right_speed - 128) * 2;
        mode = BACKWARD;
    }

    Serial.println(speed);
    Serial.println(mode);

    set_right(speed, mode);*/

    set_front_left(128, FORWARD);
    set_front_right(128, FORWARD);
    set_rear_left(128, FORWARD);
    set_rear_right(128, FORWARD);
}

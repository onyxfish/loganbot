#include <AFMotor.h>
#include <PS2X_lib.h>

AF_DCMotor front_left(2, MOTOR12_64KHZ);
AF_DCMotor front_right(1, MOTOR12_64KHZ);
AF_DCMotor rear_left(3, MOTOR34_64KHZ);
AF_DCMotor rear_right(4, MOTOR34_64KHZ);

PS2X ps2x;

const int CLOCK_PIN = 2; // blue
const int COMMAND_PIN = 9; // orange
const int ACK_PIN = 10; // yellow
const int DATA_PIN = 13; // brown

const int ANALOG_CENTER = 128;
const int ANALOG_DEAD_ZONE_MIN = ANALOG_CENTER - 10; 
const int ANALOG_DEAD_ZONE_MAX = ANALOG_CENTER + 10; 

int error = 0; 
byte left_analog = 0;
byte right_analog = 0;
byte mode = RELEASE;
byte speed = 0;

void setup() {
    Serial.begin(9600);

    error = ps2x.config_gamepad(CLOCK_PIN, COMMAND_PIN, ACK_PIN, DATA_PIN, false, false); 

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
    }

    set_front_left(0, RELEASE);
    set_front_right(0, RELEASE);
    set_rear_left(0, RELEASE);
    set_rear_right(0, RELEASE);
}

byte invert_mode(byte mode) {
    if (mode == FORWARD) {
        return BACKWARD;
    } else if (mode == BACKWARD) {
        return FORWARD;
    } else {
        return mode;
    }
}

void set_front_left(byte speed, byte mode) {
    front_left.setSpeed(speed);
    front_left.run(mode);
}

void set_front_right(byte speed, byte mode) {
    mode = invert_mode(mode);

    front_right.setSpeed(speed);
    front_right.run(mode);
}

void set_rear_left(byte speed, byte mode) {
    mode = invert_mode(mode);

    rear_left.setSpeed(speed);
    rear_left.run(mode);
}

void set_rear_right(byte speed, byte mode) {
    rear_right.setSpeed(speed);
    rear_right.run(mode);
}

byte speed_from_analog(byte analog) {
    if (analog >= ANALOG_DEAD_ZONE_MIN && analog <= ANALOG_DEAD_ZONE_MAX) {
        return 0;
    }
    else if (analog < ANALOG_CENTER) {
        if (analog == 0) {
            analog = 1;
        }

        return (ANALOG_CENTER - analog) * 2;
    } else {
        return (analog - ANALOG_CENTER) * 2;
    }
}

byte mode_from_analog(byte analog) {
    if (analog >= ANALOG_DEAD_ZONE_MIN && analog <= ANALOG_DEAD_ZONE_MAX) {
        return RELEASE;
    }
    else if (analog < ANALOG_CENTER) {
        return FORWARD;
    } else {
        return BACKWARD;
    }
}

void loop() {
    if (error == 1) {
        return; 
    }
  
    ps2x.read_gamepad(); 
    
    left_analog = ps2x.Analog(PSS_LY);
    right_analog = ps2x.Analog(PSS_RY);

    speed = speed_from_analog(left_analog);
    mode = mode_from_analog(left_analog);

    Serial.print("Left: ");
    Serial.print(left_analog);
    Serial.print(" ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.print(mode);
    Serial.println();

    set_front_left(speed, mode);
    set_rear_left(speed, mode);

    speed = speed_from_analog(right_analog);
    mode = mode_from_analog(right_analog);

    Serial.print("Right: ");
    Serial.print(right_analog);
    Serial.print(" ");
    Serial.print(speed);
    Serial.print(" ");
    Serial.print(mode);
    Serial.println();

    set_front_right(speed, mode);
    set_rear_right(speed, mode);

    delay(100);
}

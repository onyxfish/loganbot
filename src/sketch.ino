#include <AFMotor.h>
#include <PS2X_lib.h>

PS2X ps2x;

const int CLOCK_PIN = 8; // blue
const int COMMAND_PIN = 10; // orange
const int ACK_PIN = 9; // yellow
const int DATA_PIN = 11; // brown

int error = 0; 
byte type = 0;
byte vibrate = 0;

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

    type = ps2x.readType(); 

    if (type != 1) {
        Serial.println("Unknown controller type.");
    }
}

void loop() {
    if (error == 1) {
        return; 
    }
  
    ps2x.read_gamepad(); 
    
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC); 
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC); 
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC); 
 
    delay(50);
}

/*
 * SimpleSender.cpp
 *
 *  Demonstrates sending IR codes in standard format with address and command
 *  An extended example for sending can be found as IRsendDemo.
 *
 * For Arduino Uno, Nano etc., an IR LED must be connected to PWM pin 3 (IR_SEND_PIN).
 *
 *  Copyright (C) 2020-2021  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-IRremote https://github.com/z3t0/Arduino-IRremote.
 *
 *  MIT License
 */

#include <IRremote.h>
#define LED_BUILTIN 22

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);

    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

    /*
     * The IR library setup. That's all!
     * The Output pin is board specific and fixed at IR_SEND_PIN.
     * see https://github.com/Arduino-IRremote/Arduino-IRremote#hardware-specifications
     */
    IrSender.begin(true); // Enable feedback LED,
}

/*
 * Be aware, that some protocols have 5, some 8 and some 16 bit Address
 */
//  초기 값
uint16_t sAddress = 0x0102;
uint8_t sCommand = 0x34;
uint8_t sRepeats = 0;
// Results to Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)

void loop() {
    /*
     * Print current send values
     */
    Serial.println();
    Serial.print(F("Send now: address=0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" command=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(" repeats="));
    Serial.print(sRepeats);
    Serial.println();

    Serial.println(F("Send NEC with 16 bit address"));
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
    // Results for the first loop to: Protocol=NEC Address=0x102 Command=0x34 Raw-Data=0xCB340102 (32 bits)

    /*
     * If you cannot avoid to send a raw value like e.g. 0xCB340102 you must use sendNECRaw()
     */
//    Serial.println(F("Send NECRaw 0xCB340102"));
//    IrSender.sendNECRaw(0xCB340102, sRepeats);

    /*
     * Increment send values
     */

    sAddress = 0x0001;
    sCommand = 0x11;
    sRepeats++;
    // clip repeats at 4
    if (sRepeats > 4) {
        sRepeats = 4;
    }

    delay(5000);  // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal
}

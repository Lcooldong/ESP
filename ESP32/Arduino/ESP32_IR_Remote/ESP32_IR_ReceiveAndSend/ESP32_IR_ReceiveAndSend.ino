/*
 * ReceiveAndSend.cpp
 *
 * Record and play back IR signals as a minimal
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to the output PWM pin 3.
 * A button must be connected between the input SEND_BUTTON_PIN and ground.
 * A visible LED can be connected to STATUS_PIN to provide status.
 *
 * The logic is:
 * If the button is pressed, send the IR code.
 * If an IR code is received, record it.
 *
 * Initially coded 2009 Ken Shirriff http://www.righto.com
 *
 *  This file is part of Arduino-IRremote https://github.com/z3t0/Arduino-IRremote.
 *
 ************************************************************************************
 * MIT License
 *
 * Copyright (c) 2020-2021 Armin Joachimsmeyer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ************************************************************************************
 */

#include <IRremote.h>

#if defined(ESP32)
int IR_RECEIVE_PIN = 15;
int SEND_BUTTON_PIN = 16; // RX2 pin
#else
int IR_RECEIVE_PIN = 11;
int SEND_BUTTON_PIN = 12;
#endif
int STATUS_PIN = LED_BUILTIN;

int DELAY_BETWEEN_REPEAT = 50;

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

// Storage for the recorded code IR???????????????
struct storedIRDataStruct {
    IRData receivedIRData;
    // extensions for sendRaw
    uint8_t rawCode[RAW_BUFFER_LENGTH]; // The durations if raw
    uint8_t rawCodeLength; // The length of the code
} sStoredIRData;

int lastButtonState;

void storeCode(IRData *aIRReceivedData);
void sendCode(storedIRDataStruct *aIRDataToSend);

void setup() {
    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(2000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition

    IrSender.begin(true); // Enable feedback LED,

    pinMode(SEND_BUTTON_PIN, INPUT_PULLUP);
    pinMode(STATUS_PIN, OUTPUT);

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);

#if defined(SENDING_SUPPORTED)
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.print(IR_SEND_PIN);
    Serial.print(F(" on press of button at pin "));
    Serial.println(SEND_BUTTON_PIN);

#else
    Serial.println(F("Sending not supported for this board!"));
#endif
}

void loop() {

    // If button pressed, send the code. ?????? ????????? ??? LOW
    int buttonState = digitalRead(SEND_BUTTON_PIN); // Button pin is active LOW

    /*
     * Check for button just released in order to activate receiving
     */
     // falling edge  ????????? ?????? ??????, ???????????? ???
    if (lastButtonState == LOW && buttonState == HIGH) {
        // Re-enable receiver
        Serial.println(F("Button released"));
        IrReceiver.start();
    }

    /*
     * Check for static button state
     */
     // ????????? ?????? ??????, ????????? ????????? ??????
    if (buttonState == LOW) {
        IrReceiver.stop();
        /*
         * Button pressed send stored data or repeat
         */
        Serial.println(F("Button pressed, now sending"));
        digitalWrite(STATUS_PIN, HIGH);
        if (lastButtonState == buttonState) {
            sStoredIRData.receivedIRData.flags = IRDATA_FLAGS_IS_REPEAT;
        }
        sendCode(&sStoredIRData);
        digitalWrite(STATUS_PIN, LOW);
        delay(DELAY_BETWEEN_REPEAT); // Wait a bit between retransmissions

        /*
         * Button is not pressed, check for incoming data
         */
         //????????? ????????? ?????????
    } else if (IrReceiver.available()) {
        // ?????? ?????? ??????
        storeCode(IrReceiver.read());
        // 
        IrReceiver.resume(); // resume receiver
    }
    
    lastButtonState = buttonState;
}

// Stores the code for later playback in sStoredIRData
// Most of this code is just logging
// ?????? ????????? ??????
void storeCode(IRData *aIRReceivedData) {
    // flag??? REPEAT ??????, ??????????????? ????????????
    if (aIRReceivedData->flags & IRDATA_FLAGS_IS_REPEAT) {
        Serial.println(F("Ignore repeat"));
        return;
    }
    // flag??? AUTO_REPEAT ??????, ??????
    if (aIRReceivedData->flags & IRDATA_FLAGS_IS_AUTO_REPEAT) {
        Serial.println(F("Ignore autorepeat"));
        return;
    }
    // flag??? PARITY_FAILED ??????, ?????? ????????? ???
    if (aIRReceivedData->flags & IRDATA_FLAGS_PARITY_FAILED) {
        Serial.println(F("Ignore parity error"));
        return;
    }
    /*
     * Copy decoded data
     */
    // ???????????? ????????? ??????(receivedIRData) ??? ?????? ????????? ????????? ??? ??????
    sStoredIRData.receivedIRData = *aIRReceivedData;

    // ???????????? ?????? ?????? ??? ??????, ??????
    if (sStoredIRData.receivedIRData.protocol == UNKNOWN) {
        Serial.print(F("Received unknown code saving "));
        Serial.print(IrReceiver.results.rawlen - 1);
        Serial.println(F(" TickCounts as raw "));
        sStoredIRData.rawCodeLength = IrReceiver.results.rawlen - 1;
        IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData.rawCode);
    } else {  // ?????? ?????????????????? ??????
        IrReceiver.printIRResultShort(&Serial);
        sStoredIRData.receivedIRData.flags = 0; // clear flags -esp. repeat- for later sending
        Serial.println();
    }
}

// ????????? ????????? ??????
void sendCode(storedIRDataStruct *aIRDataToSend) {
    if (aIRDataToSend->receivedIRData.protocol == UNKNOWN /* i.e. raw */) {
        // Assume 38 KHz
        IrSender.sendRaw(aIRDataToSend->rawCode, aIRDataToSend->rawCodeLength, 38);

        Serial.print(F("Sent raw "));
        Serial.print(aIRDataToSend->rawCodeLength);
        Serial.println(F(" marks or spaces"));
    } else {

        /*
         * Use the write function, which does the switch for different protocols
         */
        IrSender.write(&aIRDataToSend->receivedIRData, NO_REPEATS);

        Serial.print(F("Sent: "));
        printIRResultShort(&Serial, &aIRDataToSend->receivedIRData);
    }
}

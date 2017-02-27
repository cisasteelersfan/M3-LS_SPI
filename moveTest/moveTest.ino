/*
Colby Rome 2/25/17
First test of the M3-LS
*/

#include <SPI.h>

const int CS = 4;
char buf[10000];

void setup(){
    Serial.begin(9600);
    pinMode(CS, OUTPUT);
    for(int i=0; i<10000; i++){
        buf[i] = 0;
    }
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
    delay(1000);
}


void loop(){
    Serial.println("Sending to controller: <87 4>\r");

    char command[10] = "<87 4>\r";
    digitalWrite(CS, LOW);
    delay(1);
    for(int i=0; i<7; i++){
        buf[i] = SPI.transfer(command[i]);
        if(buf[i] == 0x01) buf[i] = '1';
        delayMicroseconds(60);
    }
    for(int i=6; i<10000; i++){
        buf[i] = SPI.transfer(0x01);
        if(buf[i] == 0x01) buf[i] = '1';
        delayMicroseconds(60);
        if(buf[i] == '\r'){ // carriage return
            buf[i+1] = 0;
            Serial.print("Took ");
            Serial.print(i);
            Serial.println(" iterations.");
            break;
        }
    }
    SPI.endTransaction();

    digitalWrite(CS, HIGH);
    Serial.println("Done!");
    Serial.println("Received from M3-LS:");
    Serial.println(buf);
    delay(500);

    Serial.println("Sending to controller: <08 000000C8>\r");
    digitalWrite(CS, LOW);
    delay(1);
    char command2[16] = "<08 000000C8>\r";
    for(int i=0; i<14; i++){
        buf[i] = SPI.transfer(command2[i]);
        if(buf[i] == 0x01) buf[i] = '1';
        delayMicroseconds(60);
    }
    for(int i=13; i<1000; i++){
        buf[i] = SPI.transfer(0x01);
        if(buf[i] == 0x01) buf[i] = '1';
        delayMicroseconds(60);
        if(buf[i] == '\r'){
            buf[i+1] = 0;
            Serial.print("Took ");
            Serial.print(i);
            Serial.println(" iterations.");
            break;
        }
    }
    SPI.endTransaction();

    digitalWrite(CS, HIGH);
    Serial.println("Done!");
    Serial.println("Received from M3-LS:");
    Serial.println(buf);
    delay(1000);


    Serial.println("Sending to controller: <08 0000F0C8>\r");
    digitalWrite(CS, LOW);
    delay(1);
    char command3[16] = "<08 0000F0C8>\r";
    for(int i=0; i<14; i++){
        buf[i] = SPI.transfer(command3[i]);
        if(buf[i] == 0x01) buf[i] = '1';
        delayMicroseconds(60);
    }
    for(int i=13; i<1000; i++){
        buf[i] = SPI.transfer(0x01);
        if(buf[i] == 0x01) buf[i] = '1';
        delayMicroseconds(60);
        if(buf[i] == '\r'){
            buf[i+1] = 0;
            Serial.print("Took ");
            Serial.print(i);
            Serial.println(" iterations.");
            break;
        }
    }
    SPI.endTransaction();

    digitalWrite(CS, HIGH);
    Serial.println("Done!");
    Serial.println("Received from M3-LS:");
    Serial.println(buf);

    Serial.println("Delaying 1 second");
    delay(1000);
}

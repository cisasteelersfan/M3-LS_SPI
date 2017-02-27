#include <SPI.h>

const int CS = 4;

void setup(){
    Serial.begin(9600);
    pinMode(CS, OUTPUT);
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
    delay(1000);
}


void loop(){

    char tmp;
    digitalWrite(CS, LOW);
    delay(1);
    Serial.println("Sending to controller: <87 4>\r");
    char cmd[10] = "<87 4>\r";
    for(int i=0; i<7; i++){
        SPI.transfer(cmd[i]);
        delayMicroseconds(60);
    }
    for(int i=0; i<1000; i++){
        if((tmp = SPI.transfer(0x01)) == '\r'){
            Serial.print("Got '\\r' at ");
            Serial.println(i);
            break;
        }
        delayMicroseconds(60);
    }

    digitalWrite(CS, HIGH);
    SPI.endTransaction();
    Serial.println("done. delaying 3 seconds");
    delay(3000);
}

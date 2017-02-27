/*
Colby Rome 2/27/17
*/

#include <SPI.h>
#define IN_PROGRESS 0x01
#define DONE '\r'

#define DEBUG   //If you comment this line, the DPRINT & DPRINTLN lines are defined as blank.
#ifdef DEBUG    //Macros are usually in all capital letters.
  #define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
#else
  #define DPRINT(...)     //now defines a blank line
  #define DPRINTLN(...)   //now defines a blank line
#endif

const int CS = 4;
char buf[10001];

void setup(){
    Serial.begin(115200);
    pinMode(CS, OUTPUT);

    // Order of these two calls is very important
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE1));
    delay(1000);
}

void loop(){
    char getInfo[6] = "<01>\r";
    char getSpeed[6] = "<40>\r";
    char twoMM[15] = "<08 00000FA0>\r";
    char fourMM[15] = "<08 00001F40>\r";
    char getPos[6] = "<10>\r";
    char calibrate[8] = "<87 5>\r";

    Serial.println("Starting Test!");
    Serial.println("Sending <30>, expecting <24>");
    sendCommand("<30>\r", 5);
    delay(500);
    Serial.println("Sending <10B>>, expecting <23>");
    sendCommand("<10B>>\r", 7);



    delay(3000);
}

/*
Returns 0 if completed successfully; nonzero otherwise:
-1 if no response
*/
int sendCommand(char *command, int length){
    DPRINT("Sending to controller: ");
    DPRINTLN(command);
    memset(buf, 0, 10001);
    digitalWrite(CS, LOW);
    for(int i=0; i<length; i++){
        if(IN_PROGRESS == (buf[i] = SPI.transfer(command[i]))){
            buf[i] = '1';
        }
        if(0xFF == buf[i]){
            buf[i] = 0;
            //return -1;
        }
        // Minimum delay time: 60 microseconds between SPI transfers.
        delayMicroseconds(60);
    }

    for(int i=length; i<10000; i++){
        if(IN_PROGRESS == (buf[i] = SPI.transfer(IN_PROGRESS))){
            buf[i] = '1';
        }
        if(0xFF == buf[i]){
            buf[i] = 0;
        }
        if(DONE == buf[i]){
            DPRINT("Done!\nReceived from M3-LS:");
            DPRINTLN(buf);
            DPRINT("Took ");
            DPRINT(i);
            DPRINTLN(" iterations.\n");
            break;
        }
//        if(i == 9999) return -2;
        delayMicroseconds(60);
    }
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
    return 0;
}

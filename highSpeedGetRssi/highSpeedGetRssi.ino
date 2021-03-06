#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
uint8_t payload[] = { 0 , 0 };
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40b3c215);
XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
uint8_t cmd[] = {'D', 'B'};
uint8_t cmdVal[] = {0};
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, cmd);
RemoteAtCommandResponse remoteResp = RemoteAtCommandResponse();

unsigned long time_ms;
unsigned long pre_time;

int counter = 0;

/*
void getRemoteAtReqFrame(){
  Serial.print("RemoteAtCommand : ");
  Serial.print(remoteAtRequest.getFrameData(11), HEX);
  Serial.print(remoteAtRequest.getFrameData(12), HEX);
  Serial.print("||");
}
*/

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
  delay(10000);
}

void loop() {
  
    while(millis() - pre_time < 1500){
      ;
    }
  

    Serial.print(counter);
    
    xbee.send(remoteAtRequest);
    xbee.readPacket(500);
    
    xbee.getResponse().getRemoteAtCommandResponse(remoteResp);
  
    Serial.print(' ');
    Serial.print(xbee.getResponse().isAvailable());
    Serial.print(' ');
    Serial.println(remoteResp.getValue()[0]);
    
    //delay(2500);

    pre_time = millis();
    counter++;

}

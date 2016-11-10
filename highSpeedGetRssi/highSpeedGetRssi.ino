#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
uint8_t payload[] = { 0 , 0 };
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40b3c215);
XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
uint8_t cmd[] = {'D', 'B'};
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, cmd);
RemoteAtCommandResponse remoteResp = RemoteAtCommandResponse();

int is_available[100];
uint8_t api_id[100];
uint8_t r_status[100];
uint8_t value[100];
int count = 0;

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
  delay(10000);
}

void loop() {
  if(count < 50){
    xbee.send(remoteAtRequest);
    xbee.readPacket(150);
    
    //is_available[count] = xbee.getResponse().isAvailable();
    api_id[count] = xbee.getResponse().getApiId();
    
    xbee.getResponse().getRemoteAtCommandResponse(remoteResp);
  
    //Serial.print(' ');
    //Serial.print(remoteResp.getStatus());
    //Serial.print(' ');
    //Serial.println(remoteResp.getValue()[0]);

    //r_status[count] = remoteResp.getStatus();
    value[count] = remoteResp.getValue()[0];

    count++;
    
    delay(350);
  }else if(count == 50){
      for(int i=0;i<50;i++){
        Serial.print(api_id[i], HEX);
        Serial.print(", ");
        Serial.println(value[i]);
      }
      
      count = 0;
      
      delay(500);
  }
  

}

#include <XBee.h>
#include <SoftwareSerial.h>

XBee xbee = XBee();
uint8_t payload[] = { 0 , 0 };
//XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40B3C215);
XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x0000ffff);
uint8_t cmd[] = {'D', 'B'};
RemoteAtCommandRequest remoteAtRequest = RemoteAtCommandRequest(addr64, cmd);
RemoteAtCommandResponse remoteResp = RemoteAtCommandResponse();

void setup() {
  Serial.begin(9600);
  xbee.begin(Serial);
  delay(5000);
}

void loop() {
  xbee.send(remoteAtRequest);
  delay(1000);
  xbee.readPacket(1000);

  if(xbee.getResponse().isAvailable()){ // 受信成功
    Serial.println("Succeeded");

    if(xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE){
      Serial.println(" AT_COMMAND_RESPONSE"); 
    }else if(xbee.getResponse().getApiId() == REMOTE_AT_COMMAND_RESPONSE){
      Serial.println(" REMOTE_AT_COMMAND_RESPONSE");
      xbee.getResponse().getRemoteAtCommandResponse(remoteResp);

      if(remoteResp.getStatus() == AT_OK){
        Serial.println(" AT_OK");
        Serial.print(" Length : ");
        Serial.println(remoteResp.getValueLength());
        Serial.print(" Value : ");
        Serial.println(remoteResp.getValue()[0]);
      }
      
    }else{
      Serial.println(" Other response");
    }
    
  }else{ // 受信失敗
    Serial.println("Miss");
  }

  delay(1000);
}

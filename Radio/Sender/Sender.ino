#include <SoftwareSerial.h>


#define BAUD 9600               //radio baud rate

#define PAKLEN 32               //length of data packets
#define PAKNUM 32               //size of data packets
#define PAKSIZE (PAKLEN*PAKNUM) //total size of data

char packetbuffer[PAKNUM][PAKLEN];//buffer to store packets in
char recbuffer[PAKLEN];//buffer to store recieved data

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(BAUD);               // Serial port to HC12

  HC12.setTimeout(1000); //time to wait for packets//adjust as small as possible
}

void loop() {
  
  makePackets();//generate random data to send
  
  Serial.println("Sending Packets");
  
  uint8_t fail = 0;//count number of packets droped
  uint32_t tik = micros();//get time at start of transmission
  for(uint8_t i = 0; i < PAKNUM; i++){//send all packets and get response
      HC12.write(packetbuffer[i], PAKLEN);//send packet
      
      uint8_t bytesRead = 0; 
      bytesRead = HC12.readBytes(recbuffer, PAKLEN);//read reply
      
      if(bytesRead != PAKLEN){fail++;}//check for correct length
      else if(checkPacket(i)){fail++;}//check for correct contence
  
  }
  uint32_t tok = micros();//get time at end of tranmission
  uint32_t time = tok - tik;//fine time taken
  
  //print results
  Serial.println("=========Results=========");
  Serial.println("Time: ");
  Serial.print(time);
  Serial.println(" us");
  Serial.println("Packet Transmitted: ");
  Serial.print((PAKLEN - fail));
  Serial.println();
  Serial.println("Packet Dropped: ");
  Serial.print(fail);
  Serial.println();
  Serial.println();
  
  delay(2000);

}

bool checkPacket(uint8_t paknum){//checks if recieved packet matches sent
    for(uint8_t i = 0; i< PAKLEN; i++){
        if(recbuffer[i] != packetbuffer[paknum][i]){return false;}
    }
    return true;
}


void makePackets(void){//makes random packets to send
    randomSeed(analogRead(0));
    for(uint8_t i = 0; i < PAKNUM; i++){
    for(uint8_t j = 0; j < PAKLEN; j++){
        packetbuffer[i][j] = (uint8_t) random(256);
    }    
    }    
}
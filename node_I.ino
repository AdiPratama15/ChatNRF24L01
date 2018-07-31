#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio (9,10); //pin CE & CSN
RF24Network network(radio);
const uint8_t chatID1 = 00;
const uint8_t chatID2 = 01;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, chatID1); //channel,thisAddress
  Serial.println("***Program Chat****");
  Serial.println("*nb : setiap chat maksimal 120 karakter*");
  Serial.println(" ");
  Serial.println(" ");
}

void loop() {
  network.update();
  
  if(Serial.available()){
    chat_sending();
  }
  while(network.available()){
    chat_receive();
  }
}

void chat_sending(){
  String chat;
  chat = Serial.readString();
  int chat_len = chat.length()+1;
  char chat_send[chat_len];
  chat.toCharArray(chat_send, chat_len);
  
  RF24NetworkHeader header(chatID2);
  bool ok = network.write(header, &chat_send, sizeof(chat_send));
  if(ok){
    Serial.print("Terkirim");
    Serial.print("\t: ");
    Serial.println(chat_send);
  }
  else{
    Serial.println("Pesan tidak terkirim!!!");
  }
}

void chat_receive(){
  char payload[120];
  RF24NetworkHeader header;
  network.read(header, &payload, sizeof(payload));
  Serial.print("Terima");
  Serial.print("\t: ");
  Serial.println(payload);
}

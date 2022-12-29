#include <IRremote.h>
IRsend irsend;


//int recvPin = 2;
//IRrecv irrecv(recvPin);



String IRsend_String = "";
int count_input_IRsend = 0;
int IRsend_int = 0;
unsigned int IR_raw_data[200];
String input_IRsend_String = "";


void setup() {
  Serial.begin(115200);
  //irrecv.enableIRIn();
}


void loop() {

  if (Serial.available() > 0) {

    char input_IRsend_char = Serial.read();

    if (isDigit(input_IRsend_char)) {     
      IRsend_String += (char)input_IRsend_char;      
    }

    input_IRsend_String += input_IRsend_char;

    if (input_IRsend_String.indexOf(",") != -1) {
      IRsend_int = IRsend_String.toInt();
      IR_raw_data[count_input_IRsend] = {IRsend_int};
      count_input_IRsend += 1;
      IRsend_String = "";
      input_IRsend_String = "";
    }

    if (input_IRsend_char == '\n') {
      IRsend_int = IRsend_String.toInt();
      IR_raw_data[count_input_IRsend] = {IRsend_int};

      int khz = 38; // 38kHz carrier frequency for the NEC protocol

      irsend.sendRaw(IR_raw_data, sizeof(IR_raw_data) / sizeof(IR_raw_data[0]), khz); //Note the approach used to automatically calculate the size of the array.
      delay(50);
      irsend.sendRaw(IR_raw_data, sizeof(IR_raw_data) / sizeof(IR_raw_data[0]), khz);
      delay(50);
      irsend.sendRaw(IR_raw_data, sizeof(IR_raw_data) / sizeof(IR_raw_data[0]), khz);
      
      /*
      for (int i = 0 ; i <= count_input_IRsend ; i++) {
        Serial.print(IR_raw_data[i]);
        if (i < count_input_IRsend) {
          Serial.print(", ");
        }
      }
      Serial.println("");
      */      

      for (int j = 0 ; j <= count_input_IRsend ; j++) {
        IR_raw_data[j] = {0};   
      }
      IRsend_String = "";
      count_input_IRsend = 0;      
    }    
  }  
}

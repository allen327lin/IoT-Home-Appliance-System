
/*
long oneData[300];
//long rawData[300];
int value;
int phase;
long finalTime;
long isToEnd;
long time0;
long time1;
long time2;
long lowTime;
long highTime;
int count = 0;
int i = 0;



void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT);

}


void loop() {

  //oneData[0] = 0;
  //oneData[1] = 0;
  //rawData[300] = {};
  value = digitalRead(2);
  phase = 0;
  finalTime = micros();
  count = 0;
  Serial.print("------------------------------------");
  Serial.println();


  while (i >= 0) {
    
    value = digitalRead(2);

    isToEnd = micros() - finalTime;

    if ((value == 0) && (phase == 0)) {
      time0 = micros();
      phase = 1;
      finalTime = micros();

    }


    if ((value == 1) && (phase == 1)) {
      time1 = micros();
      phase = 2;

    }


    if ((value == 0) && (phase == 2)) {
      time2 = micros();
      finalTime = micros();


      lowTime = time1 - time0;
      highTime = time2 - time1;


      oneData[count] = lowTime;
      oneData[count+1] = highTime;

      //Serial.print(oneData[0]);
      //Serial.print(",");
      //Serial.print(oneData[1]);
      //Serial.println();

      //rawData[count] = oneData;

      //Serial.print(rawData[count]);
      //Serial.println();

      count = count + 2;

      //oneData[0] = 0;
      //oneData[1] = 0;
      phase = 0;

    }


    if ((isToEnd >= 500000) && (rawData[0] != 0)) {
      Serial.print("~~~~~~~~~~~aaa~~~~~~~~~~~~");
      Serial.println();
      for ( int i = 0 ; i < count ; i++ ) {
        Serial.print(rawData[i]);
        Serial.println();
      }
      for ( int i = 0 ; i < count ; i++ ) {
        rawData[i] = 0;
      }
      count = 0;
      break;
    }
    
  }


}

*/


long A[10];
int a=0;
int b=0;
int i=0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int a=1 ; a<11 ; a++){
    A[a]=a;
  }
  for (int i=0 ; i<10 ; i++){
    Serial.print(A[i]);
    Serial.print(",");
  }
  for (int b=0 ; b<10 ; b++){
    Serial.print(A[b]);
    Serial.print(",");
  }
  delay(111111111111);
}

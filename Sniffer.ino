// Include RadioHead Amplitude Shift Keying Library

struct WaveInfo {
  bool highLow;
  int uSSinceTrans;
};
const byte interruptPin = 2;
volatile WaveInfo waveArr[500];
volatile unsigned long timer = 0;
volatile bool currState = 0;
volatile int arrPos = 0;
String tempStr = "";
bool inProgress = 0;
 
void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3,LOW);
    Serial.begin(9600);
    for(int i = 0; i<100;i++){
        waveArr[i] = {0,0};
    }
    
    attachInterrupt(digitalPinToInterrupt(interruptPin), record, CHANGE);
}
 
void loop()
{
  if(timer != 0){
    Serial.print((String)timer);
    Serial.print("  ");
    Serial.print((String)currState);
    Serial.print("  ");
    Serial.println((String)arrPos);
    delay(100);
    inProgress = 1;
    timer = 0;
    currState = 0;
    arrPos = 0;
    for(int i = 0;i < 50; i++){ 
      tempStr = "{" + ((String)waveArr[i].highLow) + ", " + ((String)waveArr[i].uSSinceTrans) + "}, ";
      Serial.print(tempStr);
    }
    for(int i = 0; i<100;i++){
        waveArr[i] = {0,0};
    }
    inProgress = 0;
  }

//  Serial.println((String)timer);
//  delay(200);
  
}



void record(){
  if(!inProgress){
  currState = !currState;  
  if(timer == 0){
      waveArr[arrPos] = {1,0};
  }else{
    waveArr[arrPos] = {currState, micros()-timer};
  }
   timer = micros();
   arrPos++;
  //digitalWrite(3,currState);
  }
}

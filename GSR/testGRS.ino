
const int GSR=A2;
int threshold=0;
int sensorValue;

void setup(){
  long sum=0;
  Serial.begin(9600);
  delay(1000);
  
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  }
  threshold = sum/500;
   Serial.print("threshold =");
   Serial.println(threshold);
  }

void loop(){
  int temp;
  sensorValue=analogRead(GSR);
  Serial.print("sensorValue=");
  Serial.println(sensorValue);
  temp = threshold - sensorValue;
  delay(2000);
  if(abs(temp)>50)
  {
    sensorValue=analogRead(GSR);
    temp = threshold - sensorValue;
  }
}

#define CapteurSonore 0

const int GSR = A2;

int threshold = 0;
int GSRValue;
int loudness;


void setup() {
  long sum = 0;
  Serial.begin(9600);
  delay(1000);

  for(int i=0;i<500;i++)
  {
    GSRValue = analogRead(GSR);
    sum += GSRValue;
    delay(5);
  }

  threshold = sum/500;
  Serial.print("threshhold = ");
  Serial.println(threshold);

}

void loop() {
  
  loudness = analogRead(CapteurSonore);

  int temp;
  GSRValue = analogRead(GSR);
  temp = threshold - GSRValue;

  Serial.print("Capteur GSR = ");
  Serial.println(GSRValue);
  Serial.print("Capteur Sonore = ");
  Serial.println(loudness);

  delay(1000);
  
  if(abs(temp)>50)
  {
    GSRValue = analogRead(GSR);
    temp = threshold - GSRValue;
  }
}

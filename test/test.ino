char str[8];

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
  for(char i = 0; i < 8; ++i)
  {
    str[i] = 0;
  }
}

void loop()
{
  char n = Serial.readBytes(str, 8);
  if(n == 8)
  {
    Serial.write(str, 8);
    delay(5);
  }
}

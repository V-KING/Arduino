void setup()
{
  pinMode(11,OUTPUT);  
}


void loop()
{
  for (int a=0; a<=255; a++)
  {
    analogWrite(11,a);
    delay(2);
  }
  for (int a=255; a>=0; a--)
  {
    analogWrite(11,a);
    delay(2);
  }
}

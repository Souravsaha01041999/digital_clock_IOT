#define INPUT_PIN 9
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
int h=0,m=0,s=1,count=6,temp=0;
boolean sec_ctrl=false;
String disp="",ampm="";

Adafruit_SSD1306 clock_display(128,64,&Wire,4);
int get_value()
{
  int data=analogRead(A0);
  if((data<=100))
  {
    data=1;
  }
  else if((data>=101)&&(data<=200))
  {
    data=2;
  }
  else if((data>=201)&&(data<=300))
  {
    data=3;
  }
  else if((data>=301)&&(data<=400))
  {
    data=4;
  }
  else if((data>=401)&&(data<=500))
  {
    data=5;
  }
  else if((data>=501)&&(data<=600))
  {
    data=6;
  }
  else if((data>=601)&&(data<=700))
  {
    data=7;
  }
  else if((data>=701)&&(data<=800))
  {
    data=8;
  }
  else if((data>=801)&&(data<=900))
  {
    data=9;
  }
  else if((data>=901)&&(data<=1023))
  {
    data=0;
  }
  return data;
}

void setup_clock()
{
  sec_ctrl=!sec_ctrl; //TRUE MEN : WILL SHOW FALSE MEAN : NOT WILL SHOW
  if(count<=5)
  {
    count++;
    //DISPLAY TIME IN DISPLAY
    if(h<10) disp="0"+String(h);
    else disp=String(h);
    if(sec_ctrl) disp=disp+":";
    else disp=disp+" ";
    if(m<10) disp=disp+"0"+String(m);
    else disp=disp+String(m);
    disp=disp+ampm;
  }
    clock_display.clearDisplay();
    clock_display.setCursor(1,25);
    clock_display.setTextColor(WHITE);
    clock_display.setTextSize(3);
    clock_display.print(disp);
    clock_display.display();
    disp="";
}

void setup() {
  pinMode(INPUT_PIN,INPUT);
  clock_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //ASK TIME
  delay(100);

clock_display.clearDisplay();
  clock_display.setCursor(1,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(3);
  clock_display.print("Hour");
  clock_display.display();
  delay(800);
  for(int i=1;i<=2;i++)
  {
  while(digitalRead(INPUT_PIN))
  {
    temp=get_value();
    clock_display.clearDisplay();
    clock_display.setCursor(30,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(3);
  clock_display.print(temp);
  clock_display.display();
    delay(500);
  }
  clock_display.clearDisplay();
    clock_display.setCursor(30,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(3);
  clock_display.print("NEXT");
  clock_display.display();
  h=(h*10)+temp;
  delay(2000);
  }
  
  clock_display.clearDisplay();
   clock_display.setCursor(1,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(2);
  clock_display.print("Minute");
  clock_display.display();
  delay(800);

  for(int i=1;i<=2;i++)
  {
  while(digitalRead(INPUT_PIN))
  {
    temp=get_value();
    clock_display.clearDisplay();
    clock_display.setCursor(30,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(2);
  clock_display.print(temp);
  clock_display.display();
    delay(500);
  }
  clock_display.clearDisplay();
    clock_display.setCursor(30,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(3);
  clock_display.print("NEXT");
  clock_display.display();
  m=(m*10)+temp;
  delay(2000);
  }
  clock_display.clearDisplay();
    clock_display.setCursor(30,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(3);
  clock_display.print("AM/PM");
  clock_display.display();
  delay(1000);
  while(digitalRead(INPUT_PIN))
  {
    if(analogRead(A0)>500)
    {
      ampm="AM";
    }
    else
    {
      ampm="PM";
    }
    clock_display.clearDisplay();
    clock_display.setCursor(30,25);
  clock_display.setTextColor(WHITE);
  clock_display.setTextSize(3);
  clock_display.print(ampm);
  clock_display.display();
    delay(500);
  }
  
  clock_display.clearDisplay();
  clock_display.display();
  delay(1000);
}
void loop() {
  s++;
  if(s==60)
  {
    s=1;
    m++;
    if(m==60)
    {
      h++;
      m=1;
      if(h==12) h=1;
    }
  }
  if(!digitalRead(INPUT_PIN)) 
  {
    count=1;
  }
  setup_clock();
  delay(1000);
}

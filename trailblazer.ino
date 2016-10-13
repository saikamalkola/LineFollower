#define mpin1cw 1
#define mpin1acw 2
#define mpin2cw 3
#define mpin2acw 4
#define IRM A0
#define IRL1 A1
#define IRL2 A2
#define IRR1 A3
#define IRR2 A4
#define IRRA A5
#define patchledL 5
#define patchledR 6
#define binary 7
#define octal 8
#define speedpin 9
/*mpin->motorpins cw clockwise acw anticlockwise
 IRM middle IR sensor IRL left IR sensor IRR right IR sensor IRA sensor above the bot
 */
 int systrack=0;
  int i=0;
  int leftturn=0;
  int rightturn=0;
  int turn=0;
  char exparr[200];
  int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(mpin1cw,OUTPUT);
  pinMode(mpin1acw,OUTPUT);
  pinMode(mpin2cw,OUTPUT);
  pinMode(mpin2acw,OUTPUT);
  pinMode(IRM,INPUT);
  pinMode(IRL1,INPUT);
  pinMode(IRL2,INPUT);
  pinMode(IRR1,INPUT);
  pinMode(IRR2,INPUT);
  pinMode(patchledL,OUTPUT);
  pinMode(patchledR,OUTPUT);
  pinMode(binary,OUTPUT);
  pinMode(octal,OUTPUT);
  pinMode(speedpin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly
  if(analogRead(IRRA)<200){
  if(analogRead(IRM)>800&&analogRead(IRL1)<200&&analogRead(IRR1)<200)
  { turn=turn;
    leftturn=0;
    rightturn=0;
    digitalWrite(speedpin,HIGH);
    digitalWrite(mpin1cw,HIGH);
    digitalWrite(mpin1acw,LOW);
    digitalWrite(mpin2cw,HIGH);
    digitalWrite(mpin2acw,LOW);
    
  }
  else if(analogRead(IRM)>800&&analogRead(IRL1)>800&&analogRead(IRR1)<200)
  { turn=turn+1;
    leftturn=1;
    rightturn=0;
    digitalWrite(speedpin,HIGH);
    digitalWrite(mpin1cw,HIGH);
    digitalWrite(mpin1acw,LOW);
    digitalWrite(mpin2cw,LOW);
    digitalWrite(mpin2acw,HIGH);
  }
  else if(analogRead(IRM)>800&&analogRead(IRL1)<200&&analogRead(IRR1)>800)
  { turn=turn+1;
     leftturn=0;
    rightturn=1;
     digitalWrite(speedpin,HIGH);
    digitalWrite(mpin1cw,LOW);
    digitalWrite(mpin1acw,HIGH);
    digitalWrite(mpin2cw,HIGH);
    digitalWrite(mpin2acw,LOW); 
  }
  if(turn%2==0)
  {
    systrack=0;
    digitalWrite(binary,HIGH);
    digitalWrite(octal,LOW);
  }
  else 
  {
    systrack=1;
    digitalWrite(octal,HIGH);
    digitalWrite(binary,LOW);
  }
  if(analogRead(IRL2)<200&&analogRead(IRR2)>800)
   {
    if(count%2==0)
    {if(systrack==0)
    exparr[count]='1';
    else exparr[count]='1';
    }
    else
    {
      if(leftturn==0&&rightturn==0)
      exparr[count]='+';
      else if(leftturn==1&&rightturn==0)
      exparr[count]='+';
      else if(leftturn==0&&rightturn==1)
      exparr[count]='*';
    }
    count=count+1;
    digitalWrite(patchledR,HIGH);
  }
  else if(analogRead(IRL2)>800&&analogRead(IRR2)<200)
  { 
    if(count%2==0)
    {if(systrack==0)
    exparr[count]='2';
    else exparr[count]='8';
    }
    else
    {
      if(leftturn==0&&rightturn==0)
      exparr[count]='-';
      else if(leftturn==1&&rightturn==0)
      exparr[i]='-';
      else if(leftturn==0&&rightturn==1)
      exparr[i]='/';
    couont=count+1;
    digitalWrite(patchledL,HIGH);
  }
  }
  }
   else{
    //evaluate the expression present in exparr array
  digitalWrite(speedpin,LOW);
   }

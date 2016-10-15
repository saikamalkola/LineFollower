int l1=2;
int l2=3;
//left motor pins
int r1=4;
int r2=5;
//right motor pins
int enl=A4;
int enr=A5;
//motor enabler pins
int a[6];
//sensor array
int last_proportional=0;
int integral=0;

int mod(int v);
//modulus function
int setmotors(int a,int b);
void turn(char dir);
int PID();
int right=0;
int left=0;

int systrack=0;
  int i=0;
  int turn=0;
  char exparr[200];
  int count=0;
  int IR_above=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(l1,OUTPUT);
  pinMode(l2,OUTPUT);

  pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);

  pinMode(enl,OUTPUT);
  pinMode(enr,OUTPUT);

  pinMode(patchledL,OUTPUT);
  pinMode(patchledR,OUTPUT);
  pinMode(binary,OUTPUT);
  pinMode(octal,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int k=PID();
  if(k!=0)
  {
  set_motors(150,150);
  delay(20);
  unsigned char found_left =0;
  unsigned char found_right=0;
  unsigned char found_st=0;

  readline();
  
  if(a[0]==LOW&&a[3]!=LOW)
  {
  found_left=1;
  found_right=0;
  turn=turn+1;
  }

  if(a[3]==LOW&&a[0]!=LOW)
  {
  found_right=1;
  found_left=0;
  turn=turn+1;
  }
  if(a[1]==LOW || a[2]==LOW)
  found_st=1
  
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

  unsigned char dir;

  dir=select_turn(found_left,found_right,found_st)
  turn(dir);
}
}
else
{
  set_motors(0,0);
  //evaluate expression
}
}
int set_motors(int l,int r)
{
  Serial.println(l);
  Serial.println(r);

 if(l>0 && r>0)
 {
 analogWrite(enl,mod(l));
 analogWrite(enr,mod(r));
 digitalWrite(l1,LOW);
 digitalWrite(l2,HIGH);
 digitalWrite(r1,LOW);
 digitalWrite(r2,HIGH); 
 }
 else if(l<0 && r>0)
 {
 analogWrite(enl,mod(l));
 analogWrite(enr,mod(r));
 digitalWrite(l1,HIGH);
 digitalWrite(l2,LOW);
 digitalWrite(r1,LOW);
 digitalWrite(r2,HIGH); 
 }
 else if(l>0 && r<0)
 {
 analogWrite(enl,mod(l));
 analogWrite(enr,mod(r));
 digitalWrite(l1,LOW);
 digitalWrite(l2,HIGH);
 digitalWrite(r1,HIGH);
 digitalWrite(r2,LOW); 
 }
 else if(l==0 && r==0)
 {
 analogWrite(enl,mod(l));
 analogWrite(enr,mod(r));
 digitalWrite(l1,HIGH);
 digitalWrite(l2,HIGH);
 digitalWrite(r1,HIGH);
 digitalWrite(r2,HIGH); 
 }
 
}
void turn(char dir)
{
  switch(dir)
  {
    case 'L':
    set_motors(-200,200);
    delay(350);
    break;
    case 'R':
    set_motors(200,-200);
    delay(350);
    break;
    case 'B':
    set_motors(200,-200);
    delay(650);
    break;
    case 'S':
    break;
  }
}
int PID()
{
  int i;
  int error=0;
  float Kp,Ki,Kd;
  unsigned int position;
  int derivative,proportional;
  while(1)
  {
   position=readline();
   if(IR_above==HIGH)
   {
   Serial.println(position);
   proportional=int(position-1500)
   derivative=proportional-lastproportional;
   integral=integral+proportional;
   last_proportional=proportional;
   Kp=0.09;
   Ki=0.0001;
   Kd=1.0;
   error=Kp*proportional+Ki*integral+Kd*derivative;
   const int max=180;
   if(error>max)
   error=max;
   if(erroe<-1*max)
   error=-1*max;
   if(error<0)
   set_motors(max+error,max);
   else
   set_motors(max,max-error);
    if(a[0]==HIGH&&a[5]==LOW)
   {
    if(count%2==0)
    {if(systrack==0)
    exparr[count]='1';
    else exparr[count]='1';
    }
    else
    {
      if(found_left==0&&found_right==0)
      exparr[count]='+';
      else if(found_left==1&&found_right==0)
      exparr[count]='+';
      else if(found_left==0&&found_right==1)
      exparr[count]='*';
    }
    count=count+1;
    digitalWrite(patchledR,HIGH);
  }
  else if(a[0]==HIGH&&a[5]==LOW)
  { 
    if(count%2==0)
    {if(systrack==0)
    exparr[count]='2';
    else exparr[count]='8';
    }
    else
    {
      if(found_left==0&&found_right==0)
      exparr[count]='-';
      else if(found_left==1&&found_right==0)
      exparr[i]='-';
      else if(found_left==0&&found_left==1)
      exparr[i]='/';
    couont=count+1;
    digitalWrite(patchledL,HIGH);
  }
  }
   readline();
   if(a[0]==HIGH&&a[1]==HIGH&&a[2]==HIGH&&a[3]==HIGH)
   return 1;
   else if(a[0]==LOW || a[3]==LOW)
   return 1;
  }
  else
  return 0;
}

int readline()
{ int pos=0,tot=0;
  for(int i=0;i<6;i++)
  {
    a[i]=digitalRead(i+2);
  }
  IR_above=digitalRead(8);
  pos=(3000*a[1]+2000*a[2]+1000*a[3]+0*a[4])/a[1]+a[2]+a[3]+a[4];
  return pos;  
}
char select_turn(unsigned char found_left,unsigned char found_right,unsigned char found_st)
{
  if(found_left==1)
  return 'L';
  else if(found_st==1)
  return 'S';
  else if(found_right==1)
  return 'R';
  else
  return 'B';
}


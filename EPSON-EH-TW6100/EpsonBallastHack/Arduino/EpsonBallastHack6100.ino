//http://forum.arduino.ua/viewtopic.php?id=125&p=8 
//Look for JBS user's post #184, he have Epson EB 92 projector

int data;
int StatusLamp;

#define  INIT1  1
#define  INIT2  2
#define  WORK1  3
#define  WORK2  4

void setup() {
  StatusLamp = INIT1;
  Serial.begin(4800);
}

void loop() {
}


void func_unique_request( int data )
{
 switch ( data )
 {
  case 0xF2:  Serial.write(0x01); break;
  default:   Serial.write(0x00); break;
 }
 }

void func_INIT1( int data )
{
 switch ( data )
 {
  case 0x00:  Serial.write(0x00); break;
  case 0xF2:  Serial.write(0x01); break;
  case 0xF4:  Serial.write(0x1F); break;
  case 0x22:  Serial.write(0x22); break;
  case 0x81:  Serial.write(0xDC); break;
  
  default  :  func_unique_request(data); break;  
 }
 // code change status lamp to step2 ( example 0x81 ) 
 if ( data ==  0x81 )   StatusLamp = INIT2;
}


void func_INIT2( int data )
{
 switch ( data )
 {
  case 0x81:  Serial.write(0x8C); break;
  case 0x10:  Serial.write(0x10); break;
  default  :  func_unique_request(data); break;   
 }
 // code change status lamp to step2 ( example 0x81 ) 
 if ( data ==  0x81 )   StatusLamp = WORK1;
}

 
void func_WORK1( int data )
{
 switch ( data )
 {
  case 0x81:  Serial.write(0x9A); break;
  default  : func_unique_request(data); break; 
 }
 // code change status lamp to step2 ( example 0x81 ) 
 if ( data ==  0x81 )   StatusLamp = WORK2;
}


void func_WORK2( int data )
{
 switch ( data )
 {
  case 0x81:  Serial.write(0x99); break;
  default  : func_unique_request(data);  
 }
 if ( data ==  0x81 )   StatusLamp = WORK1;
}


void serialEvent() 
{
  data = Serial.read();

switch ( StatusLamp )
{
 case INIT1: func_INIT1(data); break;
 case INIT2: func_INIT2(data); break;
 case WORK1: func_WORK1 (data); break;
 case WORK2: func_WORK2 (data); break;
}

}

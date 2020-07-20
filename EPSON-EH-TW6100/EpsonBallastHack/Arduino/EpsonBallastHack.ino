int data;
int StatusLamp;
int ledON;

#define  INIT1  1
#define  INIT2  2
#define  WORK1  3
#define  WORK2  4

void setup()
{
    StatusLamp = INIT1;
    ledON = 0;

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);


    //https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/
    //8 data bits, even parity and 1 stop bit would be - SERIAL_8E1
    //Serial.begin(4800, SERIAL_8E1);

    Serial.begin(4800);

}

void loop()
{
}

void ledBlink()
{
    if(ledON == 1)
    {
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        ledON = 0;
    }
    else
    {
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        ledON = 1;
    }
}

void func_unique_request( int data )
{
    switch ( data )
    {
        case 0xF2:  Serial.write(0x04); break;
        default:   Serial.write(0x00); break;
    }
}



void func_INIT1( int data )
{
    switch ( data )
    {
        case 0x00:  Serial.write(0x00); break;
        case 0x7F:  Serial.write(0x7F); break;
        case 0xF2:  Serial.write(0x04); break;
        case 0xF4:  Serial.write(0xFF); break;
        case 0x40:  Serial.write(0x40); break;
        case 0x32:  Serial.write(0x32); break;
        case 0x84:  Serial.write(0x02); break;
        case 0x83:  Serial.write(0x64); break;
        case 0x81:  Serial.write(0x17); break;
        default  :  func_unique_request(data); break;
    }
    // code change status lamp to step2 ( example 0x81 )
    if ( data ==  0x81 )   StatusLamp = INIT2;
}


void func_INIT2( int data )
{
    switch ( data )
    {
        case 0x81:  Serial.write(0x97); break;
        case 0x40:  Serial.write(0x40); break;
        case 0x34:  Serial.write(0x34); break;
        case 0x84:  Serial.write(0x04); break;
        case 0x83:  Serial.write(0x46); break;
        default  :  func_unique_request(data); break;
    }
    // code change status lamp to step2 ( example 0x81 )
    if ( data ==  0x83 )   StatusLamp = WORK1;
}

 
void func_WORK1( int data )
{
    switch ( data )
    {
        case 0x81:  Serial.write(0x98); break;
        case 0x92:  Serial.write(0x1B); break;
        case 0x40:  Serial.write(0x40); break;
        case 0x30:  Serial.write(0x30); break;
        case 0x84:  Serial.write(0x00); break;
        case 0x83:  Serial.write(0x42); break;
        default  : func_unique_request(data); break;
    }
    // code change status lamp to step2 ( example 0x81 )
    if ( data ==  0x83 ) StatusLamp = WORK2;
}


void func_WORK2( int data )
{
    switch ( data )
    {
        case 0x81:  Serial.write(0xB6); break;
        case 0x92:  Serial.write(0x2A); break;
        case 0x40:  Serial.write(0x40); break;
        case 0x34:  Serial.write(0x34); break;
        case 0x84:  Serial.write(0x04); break;
        case 0x83:  Serial.write(0x46); break;
        default  : func_unique_request(data);
    }
    if ( data ==  0x83 )   StatusLamp = WORK1;
}


void serialEvent() 
{
    ledBlink();
    data = Serial.read();

    switch ( StatusLamp )
    {
        case INIT1: func_INIT1(data); break;
        case INIT2: func_INIT2(data); break;
        case WORK1: func_WORK1(data); break;
        case WORK2: func_WORK2(data); break;
    }
}

int ledON = 0;

void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(4800);
}

void loop()
{
}
/*
void ledBlink() {
    if(ledON == 1){
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        ledON = 0;
    }else{
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        ledON = 1;
    }
}

void wrt(byte rcvd, byte snd){
    Serial.write(snd);
//    Serial.write(rcvd);
    ledBlink();
}
void step1(byte dt)
{
    switch ( dt )
    {
        case 0x00:
            wrt(dt, 0x00);
            break;
        case 0xF2:
            wrt(dt, 0x04);
            break;
        case 0xF4:
            wrt(dt, 0xFF);
            break;
        case 0x40:
            wrt(dt, 0x40);
            break;
        case 0x32:
            wrt(dt, 0x32);
            break;
        case 0x84:
            wrt(dt, 0x02);
            break;
        case 0x83:
            wrt(dt, 0x64);
            break;
        case 0x81:
            wrt(dt, 0x17);
            break;
        default:
            wrt(dt, 0x01);
            break;
    }
}
*/
void serialEvent()
{
    while(Serial.available())
    {
//        byte ch = Serial.read();
        Serial.write(Serial.read());
//        Serial.write(0x48);
    }
//
//    byte data = Serial.read();
//    step1(data);
}

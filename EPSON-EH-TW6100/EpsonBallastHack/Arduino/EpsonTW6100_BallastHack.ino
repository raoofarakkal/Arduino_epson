int data;
int StatusLamp;

int init2_0x84_cnt = 7;
int work1_vals[13] = {0x85, 0x85, 0x85, 0x86, 0x85, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x85};
int work1_vals_idx = 0;

int work2_val = 0x86;
int work2_val_times = 56;
int work2_val_cnt = work2_val_times;


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
        case 0x27:  Serial.write(0x27); break;
        //case 0x11:  Serial.write(0x11); break;
        default:  break;
    }
}

void func_INIT1( int data )
{
    switch ( data )
    {
        case 0xF2:  Serial.write(0x01); break;
        case 0xF1:  Serial.write(0x43); break;
        case 0xF4:  Serial.write(0xe0); break;
        case 0xF5:  Serial.write(0x07); break;
        case 0x81:  Serial.write(0x04); break;
        default  :  func_unique_request(data); break;
    }
    // code change status lamp to step2 ( example 0x81 )
    if ( data ==  0x81 )   StatusLamp = INIT2;
}


void func_INIT2( int data )
{
    switch ( data )
    {
        case 0x81:
            if(init2_0x84_cnt > 0)
            {
                Serial.write(0x84);
                init2_0x84_cnt--;
            }
            else
            {
                Serial.write(0x85);
            }
            break;
        case 0x11:  Serial.write(0x11); break;
        default  :  func_unique_request(data); break;
    }
    // code change status lamp to step3 ( example 0x11 )
    if ( data ==  0x11 )   StatusLamp = WORK1;
}


void func_WORK1( int data )
{
 switch ( data )
 {
  case 0x81:
    if(work1_vals_idx <= 12)
    {
        Serial.write(work1_vals[work1_vals_idx]);
        work1_vals_idx++;
    }
    else
    {
        StatusLamp = WORK2;
        func_WORK2(data);
    }
    break;
  default  : func_unique_request(data); break;
 }
}

void func_WORK2( int data )
{
    switch ( data )
    {
        case 0x81:
            if(work2_val_cnt <= 0)
            {
                work2_val_cnt = work2_val_times;
                if(work2_val == 0x86)
                {
                    work2_val = 0x87;
                }
                else
                {
                    work2_val = 0x86;
                }
            }
            Serial.write(work2_val);
            work2_val_cnt--;
            break;
        default  : func_unique_request(data);
    }
}

void serialEvent()
{
    data = Serial.read();

    switch ( StatusLamp )
    {
        case INIT1: func_INIT1(data); break;
        case INIT2: func_INIT2(data); break;
        case WORK1: func_WORK1(data); break;
        case WORK2: func_WORK2(data); break;
    }

}


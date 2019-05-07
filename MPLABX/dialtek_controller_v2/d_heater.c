#include "xc.h"
#include "main.h"
#include "d_one_wire.h"
#include "d_heater.h"

static unsigned int sensors_qty  = 0;       // current cfg sensors qty
static long T = 0;                          // temperature var
static unsigned int  IndexBuf[MAX_sens_qty];// array of ondexes
static char ReadState = SEND_MEAS_CMD;      // OW SM state, 1 - measure in progress, 0 - done
static volatile unsigned int Tconv = 0;     // OW sensors convertion progress flag
static unsigned int temp_buf = 0;           // temporary buffer
static int SensQtySaved = 0;                // current sensors qty

unsigned int heaterT = 0;                   // heater sensor temperature

xHeater heater; // heater struct instance
Tsensor sensor; // sensor struct instance

// array of instances
Tsensor SensorArray[MAX_sens_qty] = 
{ 
{0,0}, {0,0}, {0,0}, {0,0},
{0,0}, {0,0}, {0,0}, {0,0}
};

// T2/3 - OW state machine init
void Timer32_init(void)
{
    // 750 ms inerrupt - Tsensor measure time in 12 bit mode
    
    T3CONbits.TON = 0;      // Stop any 16-bit Timer3 operation
    T2CONbits.TON = 0;      // Stop any 16/32-bit Timer3 operation
    T2CONbits.T32 = 1;      // Enable 32-bit Timer mode
    T2CONbits.TCS = 0;      // Select internal instruction cycle clock
    T2CONbits.TGATE = 0;    // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b11; // Select 1:256 Prescaler
    
    // 1 timer tick = 60M/256 = 234 375 Hz = 4.26 us
    // 176 056 (2 AFB8) = 750 ms
    
    TMR3 = 0x00;            // Clear 32-bit Timer (msw)
    TMR2 = 0x00;            // Clear 32-bit Timer (lsw)
    
    PR3 = 0x0002;           // Load 32-bit period value (msw)
    PR2 = 0xAF58;           // Load 32-bit period value (lsw)
    
    IPC2bits.T3IP = 5;      // Set Timer3 Interrupt Priority Level
    IFS0bits.T3IF = 0;      // Clear Timer3 Interrupt Flag
    
    IEC0bits.T3IE = 1;      // Enable Timer3 interrupt
}

// T2/3 int
void _ISR_PSV _T3Interrupt(void)
{      
        Tconv = 0;   // clear OW measure timeout flag
        
        TMR3 = 0x00; // Clear 32-bit Timer (msw)
        TMR2 = 0x00; // Clear 32-bit Timer (lsw)
        
        IFS0bits.T3IF = 0;   // Clear Timer interrupt flag
} 

// check if the sensor was added earlier
unsigned char MatchSensorID(void)
  {
     unsigned char SensorExist = 0, eq_cnt = 0;
     
     // сравнение ID нового датчика с теми, что были добавлены ранее
     for(unsigned char i = 0; i < sensors_qty; i++)
     {
        for(unsigned char j = 0; j < ID_lenght; j++)
        {
            if(SensorArray[i].ID[j] == sensor.ID[j])
                eq_cnt++;          
        }
        
        if(eq_cnt < ID_lenght) eq_cnt = 0; // сброс счетчика перед новым поиском
     }
      
     if(eq_cnt >= ID_lenght) 
         SensorExist = 1;
      
      return SensorExist;
  }

// search and add the new OW sensor
unsigned int AddNewSensor(unsigned int RegisterValue)
{
    unsigned int status = 0;
    
    // check for a right cmd and index
    if(RegisterValue == 1U && sensor.index <= MAX_sens_qty-1 ) 
    {
        // put sensor ID into buffer
        if(get_sensor_ID(&sensor.ID))
        {
            if( !MatchSensorID() ) // chech if the ID already exist
            {
                for(char i = 0; i < ID_lenght; i++)
                    SensorArray[sensor.index].ID[i]= sensor.ID[i];
                
                sensors_qty++; // inc qty if its really new sensor
                status = 1;    // new sensor added
            }
        }
    }
    
    return status;
}

// reset config to default
void ConfigReset(void)
{
     sensors_qty = 0; // clear total sensor qty

     for(unsigned char i = 0; i < MAX_sens_qty; i++)
     {
        IndexBuf[i] = 0;              // clear indexes
        
        for(unsigned char j = 0; j < ID_lenght; j++)
        {
           SensorArray[i].ID[j] = 0;  // clear the ID buffer       
        }
     }
    
     // clear Modbus registers
     for(char i = 10; i < 110; i++)
     {
          input_reg_write(i,0);
          holding_reg_write(i-10,0);
     }
}

void UpdateIDregs(void)
{
    for (unsigned int i = 0; i < sensors_qty; i++) 
    {
        for (unsigned int j = 0; j < ID_lenght; j++) 
        {
            temp_buf = (10+10*sensor.index) + j;
            input_reg_write(temp_buf, SensorArray[i].ID[j] );
        } 
    }
}

void GetSensorsTemp(void)
{
    for(unsigned int i = 0; i < sensors_qty; i++)
    {
        OneWire_match_ID(&SensorArray[i].ID); 
        T = ds18b20_i_rd_t();
        holding_reg_write(i, (unsigned int)(T/10L)); // xxx.xx format
    }
}

// start/stop OW SM timer
OWtimerState(unsigned int state)
{
    TMR3 = 0x00;            // Clear 32-bit Timer (msw)
    TMR2 = 0x00;            // Clear 32-bit Timer (lsw)
    
    T2CONbits.TON = state;  // Start 32-bit Timer
}

// One wire sensors read state machine
void OWstateMachine(void)
{
    if(sensors_qty > 0)                  // read only sensors were added
    {
        switch(ReadState)                // states
        {
            case SEND_MEAS_CMD:          // state 1 - send cmd and async wait 750 ms
                Tconv = 1;               // set OW measure flag 
                OneWire_all_rd_t();      // send cmd to all sensprs perform convert
                OWtimerState(1);         // start Tconv timer
                ReadState = IDLE;        // goto IDLE state
            break;
            //===
            case IDLE:                   // state 2 - wait Tconv and read
                if(Tconv == 0)           // if Tconv elapsed
                {
                    OWtimerState(0);     // stop Tconv timer
                    Tconv = 0;           // clear Tconv flag
                    GetSensorsTemp();    // read all existing sensors, 5 sensors = 80 ms
                    ReadState = SEND_MEAS_CMD; // read cycle complete, goto state 1
                }
                else 
                   ReadState = IDLE;     // Tconv in progress, wait in IDLE
                break;
            //====
            default: break;
        }// switch
    }// if sensors_qty > 0

     holding_reg_write(15,heaterT);       // heater T 
     holding_reg_write(17,Tconv);         // conversion state, 1 - in progress, 0 - done
     holding_reg_write(10, sensors_qty);  // restore sensors qty register
     holding_reg_write(11,heater.state);  // heater state
     holding_reg_read(heater.sensorIndex,&heaterT);
}
     
// Restore One wire sensors ID from memory
void OWrestoreCfg(void)
{
   unsigned int buf = 0;
   unsigned char IDptr = 0;
   
   // init heater struct 
   heater.CurrT = 0;
   heater.SetT = 0;
   heater.hysteresis = 0;
   heater.sensorIndex = 0;
   heater.state = 0;
   heater.enable = 0;
   
   // saved sensors qty
   holding_reg_read(10, &SensQtySaved);       
   
   // check if restored sensors        
   if(SensQtySaved > 0 && SensQtySaved <= MAX_sens_qty) 
   {
    for(char i = 0; i < SensQtySaved; i++)
    {
        SensorArray[i].index = i;                   // save curr index
                
        for(char j = 0; j < ID_lenght; j++)
        {
             input_reg_read(IDptr+10, &buf);       // get ID from input regs
             IDptr++;
             // fill sensor array
             SensorArray[i].ID[j] = (unsigned char)buf; 
        }
        // ID - 8 regs
        IDptr += 2; // shift ptr to next ID point - 10,20,30...
    }
        // restore saved sensors and heater 
        holding_reg_read(12, &buf);                // heater T settings
        if(buf <= MAX_T)               
            heater.SetT = buf;
        
        holding_reg_read(13,&buf);
        if(buf <= MAX_sens_qty-1)
            heater.hysteresis = buf;               // heater hysteresis
        
        holding_reg_read(14,&buf);
        if(buf <= MAX_sens_qty-1)
            heater.sensorIndex = buf;              // heater sensor index
        
        // restore sensors qty
        if(SensQtySaved <= MAX_sens_qty)
            sensors_qty = SensQtySaved;
   }

}

unsigned int GetSensorsQty(void)
{
    return sensors_qty;
}



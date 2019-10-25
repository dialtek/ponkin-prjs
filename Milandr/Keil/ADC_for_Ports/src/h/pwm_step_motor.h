
#define USE_JTAG_A // используется JTAG_A на порте В

 void STEPPER_SPEED( uint32_t PWM_speed ); // функция регулирования скорости оборотов вала ШД
 void STEP_ENABLE(void); // функция включения драйвера ШД
 void STEP_DISABLE(void); // функция выключения драйвера ШД
 void DIR_LEFT(void); // функция выбора направления вращения вала влево (а может вправо)
 void DIR_RIGHT(void); // функция выбора направления вращения вправо (а может влево) (документацию было лень поглядеть)
 
 void PORTB_Init();

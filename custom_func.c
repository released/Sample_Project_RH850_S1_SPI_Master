/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "r_smc_entry.h"

#include "misc_config.h"
#include "custom_func.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

struct flag_32bit flag_PROJ_CTL;
#define FLAG_PROJ_TIMER_PERIOD_1000MS                 	(flag_PROJ_CTL.bit0)
#define FLAG_PROJ_TIMER_PERIOD_SPI                	    (flag_PROJ_CTL.bit1)
#define FLAG_PROJ_SPI_TX_END              	        	(flag_PROJ_CTL.bit2)
#define FLAG_PROJ_SPI_RX_END                   		    (flag_PROJ_CTL.bit3)
#define FLAG_PROJ_REVERSE4                              (flag_PROJ_CTL.bit4)
#define FLAG_PROJ_REVERSE5                              (flag_PROJ_CTL.bit5)
#define FLAG_PROJ_REVERSE6                              (flag_PROJ_CTL.bit6)
#define FLAG_PROJ_REVERSE7                              (flag_PROJ_CTL.bit7)


#define FLAG_PROJ_TRIG_1                                (flag_PROJ_CTL.bit8)
#define FLAG_PROJ_TRIG_2                                (flag_PROJ_CTL.bit9)
#define FLAG_PROJ_TRIG_3                                (flag_PROJ_CTL.bit10)
#define FLAG_PROJ_TRIG_4                                (flag_PROJ_CTL.bit11)
#define FLAG_PROJ_TRIG_5                                (flag_PROJ_CTL.bit12)
#define FLAG_PROJ_REVERSE13                             (flag_PROJ_CTL.bit13)
#define FLAG_PROJ_REVERSE14                             (flag_PROJ_CTL.bit14)
#define FLAG_PROJ_REVERSE15                             (flag_PROJ_CTL.bit15)

/*_____ D E F I N I T I O N S ______________________________________________*/

volatile unsigned int counter_tick = 0;
volatile unsigned long ostmr_tick = 0;

#define BTN_PRESSED_LONG                                (2500)

#pragma section privateData

const unsigned char dummy_3 = 0x5A;

volatile unsigned char dummy_2 = 0xFF;

volatile unsigned char dummy_1;

#pragma section default

char *g_pNextData;
char g_StatusText[256];
char *tmp = g_StatusText;

#define SPI_LEN                                         (64)
unsigned short t_buffer[SPI_LEN] = {0};
unsigned short r_buffer[SPI_LEN] = {0};

unsigned long spi_state = _CSIH_SELECT_CHIP_0;

#define SS2_HIGH                                        (PORT.P0 |= 1u<<11)
#define SS2_LOW                                         (PORT.P0 &= ~(1u<<11))

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/



void ostmr_tick_counter(void)
{
	ostmr_tick++;
}

void ostmr_1ms_IRQ(void)
{
	ostmr_tick_counter();
}

void ostimer_dealyms(unsigned long ms)
{
    R_Config_OSTM0_Start();
    ostmr_tick = 0;

    while(ostmr_tick < ms);

    R_Config_OSTM0_Stop();

}

unsigned int get_tick(void)
{
	return (counter_tick);
}

void set_tick(unsigned int t)
{
	counter_tick = t;
}

void tick_counter(void)
{
	counter_tick++;
    if (get_tick() >= 60000)
    {
        set_tick(0);
    }
}

void tmr_1ms_IRQ(void)
{
    tick_counter();

    if ((get_tick() % 1000) == 0)
    {
        FLAG_PROJ_TIMER_PERIOD_1000MS = 1;
    }


    if ((get_tick() % 100) == 0)
    {
        FLAG_PROJ_TIMER_PERIOD_SPI = 1;
    }

    if ((get_tick() % 50) == 0)
    {

    }	

}

void LED_Toggle(void)
{
    static unsigned char flag_gpio = 0;
	
    // P6_bit.no6 = ~P6_bit.no6;
    // P6_bit.no7 = ~P6_bit.no7;
	
    PORT.PNOT0 |= 1u<<14;
	
	if (!flag_gpio)
	{
		flag_gpio = 1;
        PORT.P8 |= 1u<<5;
	}
	else
	{
		flag_gpio = 0;
		PORT.P8 &= ~(1u<<5);
	}
}

unsigned char is_spi_rx_end(void)
{
    return FLAG_PROJ_SPI_RX_END;
}

void spi_rx_end(unsigned char flag)
{
    FLAG_PROJ_SPI_RX_END = flag;
}


unsigned char is_spi_tx_end(void)
{
    return FLAG_PROJ_SPI_TX_END;
}

void spi_tx_end(unsigned char flag)
{
    FLAG_PROJ_SPI_TX_END = flag;
}

void SPI_init(void)
{
    spi_tx_end(0);
    spi_rx_end(0);
}

void SPI_process(void)
{
    unsigned char i = 0;
    unsigned char len = 0;
    static unsigned char cnt = 0;

    switch(spi_state)
    {
        case _CSIH_SELECT_CHIP_0:
            len = 16;
            for(i = 0 ; i < len ; i++)
            {
                t_buffer[i] = i + cnt;
            }

            t_buffer[0] = 0x5A;
            t_buffer[1] = 0x5A;
            t_buffer[len-2] = 0xA5;
            t_buffer[len-1] = 0xA5;

            spi_tx_end(0);
            R_Config_CSIH1_Send_Receive((uint16_t*)t_buffer,len,(uint16_t*)r_buffer,_CSIH_SELECT_CHIP_0);
            while(!is_spi_tx_end());

            spi_state = _CSIH_SELECT_CHIP_1;
            break;

        case _CSIH_SELECT_CHIP_1:
            len = 8;
            for(i = 0 ; i < len ; i++)
            {
                t_buffer[i] = i + cnt;
            }

            t_buffer[0] = 0x5B;
            t_buffer[1] = 0x5B;
            t_buffer[len-2] = 0xB5;
            t_buffer[len-1] = 0xB5;

            spi_tx_end(0);
            R_Config_CSIH1_Send_Receive((uint16_t*)t_buffer,len,(uint16_t*)r_buffer,_CSIH_SELECT_CHIP_1);
            while(!is_spi_tx_end());

            spi_state = _CSIH_SELECT_CHIP_2;
            break;

        case _CSIH_SELECT_CHIP_2:
            SS2_LOW;

            len = 6;
            for(i = 0 ; i < len ; i++)
            {
                t_buffer[i] = i + cnt;
            }

            t_buffer[0] = 0x5C;
            t_buffer[1] = 0x5C;
            t_buffer[len-2] = 0xC5;
            t_buffer[len-1] = 0xC5;

            while(CSIH1.STR0 & (1 << 7));
            spi_tx_end(0);
            R_Config_CSIH1_Send_Receive((uint16_t*)t_buffer,len,(uint16_t*)r_buffer,_CSIH_SELECT_CHIP_2);
            while(!is_spi_tx_end());
            while(CSIH1.STR0 & (1 << 7));

            spi_state = _CSIH_SELECT_CHIP_0;

            SS2_HIGH;
            break;
    }


    cnt += 0x10;
}

void loop(void)
{
    // static unsigned long cnt = 0;

    if (FLAG_PROJ_TIMER_PERIOD_1000MS)
    {
        FLAG_PROJ_TIMER_PERIOD_1000MS = 0;

        LED_Toggle();  
        // printf("%s:%d\r\n",__func__,cnt);
        // sprintf(tmp, "loop:%3i%%", cnt);    
        // sprintf(tmp, "loop:%d\r\n", cnt);     
        // R_UART_SendString(tmp); 
        // cnt++;    
    }

    if (FLAG_PROJ_TIMER_PERIOD_SPI)
    {
        FLAG_PROJ_TIMER_PERIOD_SPI = 0;
        SPI_process();
    }

}

void UARTx_Process(unsigned char rxbuf)
{    
    if (rxbuf > 0x7F)
    {
        printf("invalid command\r\n");
    }
    else
    {
        printf("press:%c(0x%02X)\r\n" , rxbuf,rxbuf);   // %c :  C99 libraries.
        switch(rxbuf)
        {
            case '1':
                FLAG_PROJ_TRIG_1 = 1;
                break;
            case '2':
                FLAG_PROJ_TRIG_2 = 1;
                break;
            case '3':
                FLAG_PROJ_TRIG_3 = 1;
                break;
            case '4':
                FLAG_PROJ_TRIG_4 = 1;
                break;
            case '5':
                FLAG_PROJ_TRIG_5 = 1;
                break;

            case 'X':
            case 'x':
                // RL78_soft_reset(7);
                break;
            case 'Z':
            case 'z':
                // RL78_soft_reset(1);
                break;
        }
    }
}

void R_RLIN30_UartSendString(char send_string[])
{
    while((RLN30.LST&16u)==16u)
    {
    /* Wait until RLIN transmission is finished */
    }

    g_pNextData = send_string;

    RLN30.LUTDR.UINT16 = *g_pNextData;
}


unsigned char R_RLIN30_GetStatus(void)
{
    if((RLN30.LST&16u)==16u)
    {
        return RLIN_BUSY;
    }
    else                             /* If transmission bit is 0 (transmission ready) */
    {
        return RLIN_READY;
    }
}

void R_UART_SendString(char string[])
{
    while(R_RLIN30_GetStatus() == RLIN_BUSY);
    
    if(R_RLIN30_GetStatus()== RLIN_READY)
    {
        R_RLIN30_UartSendString(string);
    }
}

// retarget printf
int putchar(int c)
{

    RLN30.LUTDR.UINT16 = c;
    while((RLN30.LST&16u)==16u)
    {
        /* Wait until RLIN transmission is finished */
        /*
            (RLN30.LST&16u)==16u : BUSY
            (RLN30.LST&16u)!=16u : READY
            
        */
    }    

    // STMK0 = 1U;    /* disable INTST0 interrupt */
    // SDR00L = (unsigned char)c;
    // while(STIF0 == 0)
    // {

    // }
    // STIF0 = 0U;    /* clear INTST0 interrupt flag */

    return c;
}

void hardware_init(void)
{
    EI();

    R_Config_TAUJ0_0_Start();
    R_Config_OSTM0_Start();

    /*
        LED
        LED18:P0_14
        LED17:P8_5
    */
	
    /*
        UART
        USB TX:P0_2 
        USB RX:P0_3 
        USB EN:AP0_9
    */
    R_Config_UART0_Start();
    
    /*
        CSIH
        SC:P0_6
        SI:P0_4
        SO:P0_5
        SS0:P10_11
        SS1:P10_12
        SS2:P0_11 , default output HIGH
    */
   R_Config_CSIH1_Start();

}

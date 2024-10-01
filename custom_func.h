/*_____ I N C L U D E S ____________________________________________________*/

/*_____ D E C L A R A T I O N S ____________________________________________*/
// #define bool  _Bool

// #ifndef TRUE
// #define TRUE  (1)
// #endif

// #ifndef true
// #define true  (1)
// #endif

// #ifndef FALSE
// #define FALSE  (0)
// #endif

// #ifndef false
// #define false  (0)
// #endif

// #ifndef BIT0
// #define BIT0     (0x00000001UL)       ///< Bit 0 mask of an 32 bit integer
// #endif

// #ifndef BIT1
// #define BIT1     (0x00000002UL)       ///< Bit 1 mask of an 32 bit integer
// #endif

// #ifndef BIT2
// #define BIT2     (0x00000004UL)       ///< Bit 2 mask of an 32 bit integer
// #endif

// #ifndef BIT3
// #define BIT3     (0x00000008UL)       ///< Bit 3 mask of an 32 bit integer
// #endif

// #ifndef BIT4
// #define BIT4     (0x00000010UL)       ///< Bit 4 mask of an 32 bit integer
// #endif

// #ifndef BIT5
// #define BIT5     (0x00000020UL)       ///< Bit 5 mask of an 32 bit integer
// #endif

// #ifndef BIT6
// #define BIT6     (0x00000040UL)       ///< Bit 6 mask of an 32 bit integer
// #endif

// #ifndef BIT7
// #define BIT7     (0x00000080UL)       ///< Bit 7 mask of an 32 bit integer
// #endif

/*_____ D E F I N I T I O N S ______________________________________________*/
#define RLIN_OK      0
#define RLIN_ERROR   1
#define RLIN_NO_MSG  2
#define RLIN_READY   3
#define RLIN_BUSY    4

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/

void R_UART_SendString(char string[]);

unsigned char is_spi_rx_end(void);
void spi_rx_end(unsigned char flag);
unsigned char is_spi_tx_end(void);
void spi_tx_end(unsigned char flag);


void ostmr_1ms_IRQ(void);
void ostimer_dealyms(unsigned long ms);

void tmr_1ms_IRQ(void);

void LED_Toggle(void);

void loop(void);
void hardware_init(void);

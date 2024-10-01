/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_CSIH1.c
* Component Version: 1.4.1
* Device(s)        : R7F701684
* Description      : This file implements device driver for Config_CSIH1.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_CSIH1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
volatile uint16_t  g_csih1_tx_num;                         /* csih1 transmit data number */
volatile uint16_t * gp_csih1_tx_address;                   /* csih1 transmit buffer address */
volatile uint16_t  g_csih1_rx_num;                         /* csih1 receive data number */
volatile uint16_t * gp_csih1_rx_address;                   /* csih1 receive buffer address */
volatile uint16_t  g_csih1_total_num;                      /* csih1 transmit/receive data total times */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSIH1_Create
* Description  : This function initializes the Config_CSIH1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSIH1_Create(void)
{
    uint32_t tmp_port;

    CSIH1.CTL0 = _CSIH_OPERATION_CLOCK_STOP;
    /* Disable INTCSIH1IC operation and clear request */
    INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IC.BIT.RFCSIH1IC = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTCSIH1IRE operation and clear request */
    INTC2.ICCSIH1IRE.BIT.MKCSIH1IRE = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IRE.BIT.RFCSIH1IRE = _INT_REQUEST_NOT_OCCUR;
    /* Set CSIH1 interrupt(INTCSIH1IC) setting */
    INTC2.ICCSIH1IC.BIT.TBCSIH1IC = _INT_TABLE_VECTOR;
    INTC2.ICCSIH1IC.UINT16 &= _INT_PRIORITY_LOWEST;
    /* Set CSIH1 interrupt(INTCSIH1IRE) setting */
    INTC2.ICCSIH1IRE.BIT.TBCSIH1IRE = _INT_TABLE_VECTOR;
    INTC2.ICCSIH1IRE.UINT16 &= _INT_PRIORITY_LOWEST;
    /* Set CSIH1 control setting */
    CSIH1.CTL1 = _CSIH_CLOCK_INVERTING_HIGH | _CSIH_INTERRUPT_TIMING_NORMAL | _CSIH_DATA_CONSISTENCY_CHECK_DISABLE | 
                 _CSIH_NO_DELAY | _CSIH_CHIPSELECT0_ACTIVE_LOW | _CSIH_CHIPSELECT1_ACTIVE_LOW | 
                 _CSIH_CHIPSELECT2_ACTIVE_LOW | _CSIH_HANDSHAKE_DISABLE | _CSIH_CHIPSELECT_SIGNAL_HOLD_ACTIVE | 
                 _CSIH_SLAVE_SELECT_DISABLE;
    CSIH1.CTL2 = _CSIH1_MASTER_PCLK_DIV;
    CSIH1.BRS0 = _CSIH1_BAUD_RATE_0;
    CSIH1.BRS1 = _CSIH1_BAUD_RATE_1;
    CSIH1.BRS2 = _CSIH1_BAUD_RATE_2;
    CSIH1.BRS3 = _CSIH1_BAUD_RATE_3;
    /* Set CSIH1 configuration setting */
    CSIH1.CFG0 = _CSIH_USED_BAUDRATE_0 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_8 | _CSIH_DATA_DIRECTION_MSB | 
                 _CSIH_PHASE_SELECTION_TYPE4 | _CSIH_IDLE_INSERTED_ALWAYS | _CSIH_IDLE_TIME_0 | _CSIH_HOLD_TIME_0 | 
                 _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    CSIH1.CFG1 = _CSIH_USED_BAUDRATE_1 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_8 | _CSIH_DATA_DIRECTION_MSB | 
                 _CSIH_PHASE_SELECTION_TYPE4 | _CSIH_IDLE_INSERTED_NOT_ALWAYS | _CSIH_IDLE_TIME_0 | 
                 _CSIH_HOLD_TIME_0 | _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    CSIH1.CFG2 = _CSIH_USED_BAUDRATE_2 | _CSIH_PARITY_NO | _CSIH_DATA_LENGTH_8 | _CSIH_DATA_DIRECTION_MSB | 
                 _CSIH_PHASE_SELECTION_TYPE4 | _CSIH_IDLE_INSERTED_NOT_ALWAYS | _CSIH_IDLE_TIME_0 | 
                 _CSIH_HOLD_TIME_0 | _CSIH_INTER_DATA_DELAY_TIME_0 | _CSIH_SETUP_TIME_0;
    /* Synchronization processing */
    g_cg_sync_read = CSIH1.CTL1;
    __syncp();
    /* Set CSIH1SC pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT6;
    PORT.PBDC0 &= _PORT_CLEAR_BIT6;
    PORT.PM0 |= _PORT_SET_BIT6;
    PORT.PMC0 &= _PORT_CLEAR_BIT6;
    PORT.PIPC0 &= _PORT_CLEAR_BIT6;
    tmp_port = PORT.PDSC0;
    PORT.PPCMD0 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC0 = (tmp_port & _PORT_CLEAR_BIT6);
    PORT.PDSC0 = (uint32_t) ~(tmp_port & _PORT_CLEAR_BIT6);
    PORT.PDSC0 = (tmp_port & _PORT_CLEAR_BIT6);
    PORT.PFC0 &= _PORT_CLEAR_BIT6;
    PORT.PFCE0 |= _PORT_SET_BIT6;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT6;
    PORT.PIPC0 |= _PORT_SET_BIT6;
    PORT.PMC0 |= _PORT_SET_BIT6;
    /* Set CSIH1SO pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT5;
    PORT.PBDC0 &= _PORT_CLEAR_BIT5;
    PORT.PM0 |= _PORT_SET_BIT5;
    PORT.PMC0 &= _PORT_CLEAR_BIT5;
    PORT.PIPC0 &= _PORT_CLEAR_BIT5;
    tmp_port = PORT.PDSC0;
    PORT.PPCMD0 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC0 = (tmp_port & _PORT_CLEAR_BIT5);
    PORT.PDSC0 = (uint32_t) ~(tmp_port & _PORT_CLEAR_BIT5);
    PORT.PDSC0 = (tmp_port & _PORT_CLEAR_BIT5);
    PORT.PFC0 &= _PORT_CLEAR_BIT5;
    PORT.PFCE0 |= _PORT_SET_BIT5;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT5;
    PORT.PIPC0 |= _PORT_SET_BIT5;
    PORT.PMC0 |= _PORT_SET_BIT5;
    /* Set CSIH1SI pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT4;
    PORT.PBDC0 &= _PORT_CLEAR_BIT4;
    PORT.PM0 |= _PORT_SET_BIT4;
    PORT.PMC0 &= _PORT_CLEAR_BIT4;
    PORT.PFC0 &= _PORT_CLEAR_BIT4;
    PORT.PFCE0 |= _PORT_SET_BIT4;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT4;
    PORT.PMC0 |= _PORT_SET_BIT4;
    /* Set CSIH1CSS0 pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT11;
    PORT.PBDC10 &= _PORT_CLEAR_BIT11;
    PORT.PM10 |= _PORT_SET_BIT11;
    PORT.PMC10 &= _PORT_CLEAR_BIT11;
    PORT.PFC10 &= _PORT_CLEAR_BIT11;
    PORT.PFCE10 |= _PORT_SET_BIT11;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT11;
    PORT.PMC10 |= _PORT_SET_BIT11;
    PORT.PM10 &= _PORT_CLEAR_BIT11;
    /* Set CSIH1CSS1 pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT12;
    PORT.PBDC10 &= _PORT_CLEAR_BIT12;
    PORT.PM10 |= _PORT_SET_BIT12;
    PORT.PMC10 &= _PORT_CLEAR_BIT12;
    PORT.PFC10 &= _PORT_CLEAR_BIT12;
    PORT.PFCE10 |= _PORT_SET_BIT12;
    PORT.PMC10 |= _PORT_SET_BIT12;
    PORT.PM10 &= _PORT_CLEAR_BIT12;

    R_Config_CSIH1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSIH1_Start
* Description  : This function starts the Config_CSIH1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSIH1_Start(void)
{
    /* Enable CSIH1 operation */
    CSIH1.CTL0 = _CSIH_OPERATION_CLOCK_PROVIDE | _CSIH_TRANSMISSION_PERMIT | _CSIH_RECEPTION_PERMIT | 
                 _CSIH_DIRECTACCESS;
    /* Clear CSIH1 interrupt request and enable operation */
    INTC2.ICCSIH1IC.BIT.RFCSIH1IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IRE.BIT.RFCSIH1IRE = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_ENABLED;
    INTC2.ICCSIH1IRE.BIT.MKCSIH1IRE = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_Config_CSIH1_Stop
* Description  : This function stops the CSIH1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSIH1_Stop(void)
{
    /* Disable CSIH1 interrupt operation */
    INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_DISABLED;
    INTC2.ICCSIH1IRE.BIT.MKCSIH1IRE = _INT_PROCESSING_DISABLED;
    /* Disable CSIH1 operation */
    CSIH1.CTL0 &= (uint8_t) ~_CSIH_RECEPTION_PERMIT;
    CSIH1.CTL0 &= (uint8_t) ~_CSIH_TRANSMISSION_PERMIT;
    CSIH1.CTL0 &= (uint8_t) ~_CSIH_OPERATION_CLOCK_PROVIDE;
    /* Synchronization processing */
    g_cg_sync_read = CSIH1.CTL0;
    __syncp();
    /* Clear CSIH1 interrupt operation */
    INTC2.ICCSIH1IC.BIT.RFCSIH1IC = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICCSIH1IRE.BIT.RFCSIH1IRE = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICCSIH1IC.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSIH1_Send_Receive
* Description  : This function sends and receives CSIH1 data.
* Arguments    : tx_buf -
*                    send buffer pointer
*                tx_num -
*                    buffer size
*                rx_buf -
*                    receive buffer pointer
*                chip_id -
*                    set chip select id
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_CSIH1_Send_Receive(uint16_t* const tx_buf, uint16_t tx_num, uint16_t* const rx_buf, uint32_t chip_id)
{
    MD_STATUS status = MD_OK;
    uint32_t regValue = _CSIH1_SETTING_INIT;

    if ((tx_num < 1U) || (chip_id < _CSIH_SELECT_CHIP_0) || (chip_id > _CSIH_SELECT_CHIP_5))
    {
        status = MD_ARGERROR;
    }
    else
    {
        /* Set transmit setting */
        gp_csih1_tx_address = tx_buf;
        g_csih1_total_num = tx_num;
        g_csih1_tx_num = 0U;
        /* Set receive setting */
        gp_csih1_rx_address = rx_buf;
        /* Set select chip id */
        regValue &= (~chip_id);
        if (0U != gp_csih1_tx_address)
        {
            regValue |= (*gp_csih1_tx_address);
            gp_csih1_tx_address++;
        }
        else
        {
            regValue |= 0xFFFFU;
        }
        /* Disable CSIH1 interrupt operation */
        INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_DISABLED;
        /* Synchronization processing */
        g_cg_sync_read = INTC2.ICCSIH1IC.UINT16;
        __syncp();
        /* Set transmit data */
        CSIH1.TX0W = regValue;
        g_csih1_tx_num++;
        /* Enable CSIH1 interrupt operation */
        INTC2.ICCSIH1IC.BIT.MKCSIH1IC = _INT_PROCESSING_ENABLED;
        /* Synchronization processing */
        g_cg_sync_read = CSIH1.CTL1;
        __syncp();
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

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
* File Name        : Pin.c
* Version          : 1.0.0.0
* Device(s)        : R7F701684
* Description      : This file implements SMC pin code generation.
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Pins_Create(void)
{
    /* Set CSIH1CSS0(P10_11) pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT11;
    PORT.PBDC10 &= _PORT_CLEAR_BIT11;
    PORT.PM10 |= _PORT_SET_BIT11;
    PORT.PMC10 &= _PORT_CLEAR_BIT11;
    PORT.PFC10 &= _PORT_CLEAR_BIT11;
    PORT.PFCE10 |= _PORT_SET_BIT11;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT11;
    PORT.PMC10 |= _PORT_SET_BIT11;
    PORT.PM10 &= _PORT_CLEAR_BIT11;

    /* Set CSIH1CSS1(P10_12) pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT12;
    PORT.PBDC10 &= _PORT_CLEAR_BIT12;
    PORT.PM10 |= _PORT_SET_BIT12;
    PORT.PMC10 &= _PORT_CLEAR_BIT12;
    PORT.PFC10 &= _PORT_CLEAR_BIT12;
    PORT.PFCE10 |= _PORT_SET_BIT12;
    PORT.PMC10 |= _PORT_SET_BIT12;
    PORT.PM10 &= _PORT_CLEAR_BIT12;

    /* Set CSIH1SC(P0_6) pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT6;
    PORT.PBDC0 &= _PORT_CLEAR_BIT6;
    PORT.PM0 |= _PORT_SET_BIT6;
    PORT.PMC0 &= _PORT_CLEAR_BIT6;
    PORT.PIPC0 &= _PORT_CLEAR_BIT6;
    PORT.PFC0 &= _PORT_CLEAR_BIT6;
    PORT.PFCE0 |= _PORT_SET_BIT6;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT6;
    PORT.PIPC0 |= _PORT_SET_BIT6;
    PORT.PMC0 |= _PORT_SET_BIT6;

    /* Set CSIH1SI(P0_4) pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT4;
    PORT.PBDC0 &= _PORT_CLEAR_BIT4;
    PORT.PM0 |= _PORT_SET_BIT4;
    PORT.PMC0 &= _PORT_CLEAR_BIT4;
    PORT.PFC0 &= _PORT_CLEAR_BIT4;
    PORT.PFCE0 |= _PORT_SET_BIT4;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT4;
    PORT.PMC0 |= _PORT_SET_BIT4;

    /* Set CSIH1SO(P0_5) pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT5;
    PORT.PBDC0 &= _PORT_CLEAR_BIT5;
    PORT.PM0 |= _PORT_SET_BIT5;
    PORT.PMC0 &= _PORT_CLEAR_BIT5;
    PORT.PIPC0 &= _PORT_CLEAR_BIT5;
    PORT.PFC0 &= _PORT_CLEAR_BIT5;
    PORT.PFCE0 |= _PORT_SET_BIT5;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT5;
    PORT.PIPC0 |= _PORT_SET_BIT5;
    PORT.PMC0 |= _PORT_SET_BIT5;

    /* Set RLIN30RX(P0_3) pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT3;
    PORT.PBDC0 &= _PORT_CLEAR_BIT3;
    PORT.PM0 |= _PORT_SET_BIT3;
    PORT.PMC0 &= _PORT_CLEAR_BIT3;
    PORT.PIPC0 &= _PORT_CLEAR_BIT3;
    PORT.PFC0 &= _PORT_CLEAR_BIT3;
    PORT.PFCE0 |= _PORT_SET_BIT3;
    PORT.PFCAE0 |= _PORT_SET_BIT3;
    PORT.PMC0 |= _PORT_SET_BIT3;

    /* Set RLIN30TX(P0_2) pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT2;
    PORT.PBDC0 &= _PORT_CLEAR_BIT2;
    PORT.PM0 |= _PORT_SET_BIT2;
    PORT.PMC0 &= _PORT_CLEAR_BIT2;
    PORT.PIPC0 &= _PORT_CLEAR_BIT2;
    PORT.PFC0 |= _PORT_SET_BIT2;
    PORT.PFCE0 &= _PORT_CLEAR_BIT2;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT2;
    PORT.PMC0 |= _PORT_SET_BIT2;
    PORT.PM0 &= _PORT_CLEAR_BIT2;

    /* Set TAUJ0O0(P8_2) pin */
    PORT.PIBC8 &= _PORT_CLEAR_BIT2;
    PORT.PBDC8 &= _PORT_CLEAR_BIT2;
    PORT.PM8 |= _PORT_SET_BIT2;
    PORT.PMC8 &= _PORT_CLEAR_BIT2;
    PORT.PFC8 &= _PORT_CLEAR_BIT2;
    PORT.PFCE8 &= _PORT_CLEAR_BIT2;
    PORT.PMC8 |= _PORT_SET_BIT2;
    PORT.PM8 &= _PORT_CLEAR_BIT2;

}

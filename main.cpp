/**
 *  \file   main_eeprom_read.c
 *
 *  \brief  Example application main file. This application will read the data
 *          from eeprom and compares it with the known data.
 *
 */

/*
 * Copyright (C) 2014 - 2017 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BARE_METAL
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#endif

#include <stdio.h>
#include <string.h>

/* TI-RTOS Header files */
#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/drv/i2c/test/eeprom_read/src/I2C_log.h>
#include <ti/drv/i2c/test/eeprom_read/src/I2C_board.h>

#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

#include <inc/mpu6050.h>
#include <inc/convert.h>
#include <inc/ftoa.h>

#if defined (SOC_AM335X) || defined (SOC_AM437x)
/* EEPROM data -Board specific */
extern char eepromData[I2C_EEPROM_RX_LENGTH];
#endif

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/

#define I2C_TRANSACTION_TIMEOUT         (2000U)


void AppDelay();

bool Board_initI2C(void)
{
    Board_initCfg boardCfg;
    Board_STATUS  boardStatus;
    I2C_HwAttrs   i2c_cfg;

    /* Get the default I2C init configurations */
    I2C_socGetInitCfg(I2C_EEPROM_INSTANCE, &i2c_cfg);

    I2C_socSetInitCfg(I2C_EEPROM_INSTANCE, &i2c_cfg);

    boardCfg = BOARD_INIT_PINMUX_CONFIG |
            BOARD_INIT_MODULE_CLOCK |
            BOARD_INIT_UART_STDIO;
    boardStatus = Board_init(boardCfg);
    if (boardStatus != BOARD_SOK)
    {
        return (false);
    }

    return (true);
}

void i2c_test(UArg arg0, UArg arg1)
{

    I2C_Params i2cParams;
    I2C_Handle handle = NULL;

    I2C_init();

    I2C_Params_init(&i2cParams);

    handle = I2C_open(2, &i2cParams);

    mpu6050 acelerometro(&handle);

    if(!acelerometro.test())
        UART_printf("Modulo não esta funcionando Acelerometro\n");
    else{
        acelerometro.reset();
        acelerometro.configAccel(MPU6050_RANGE_4G);
        acelerometro.configGyro(MPU6050_SCALE_250DPS);
    }


    float xf, yf, zf;
    float xfGyro, yfGyro, zfGyro;
    char x[10];
    char y[10];
    char z[10];

    char xGyro[10];
    char yGyro[10];
    char zGyro[10];

    oled display(&handle);
    if(!display.test()){
        UART_printf("Modulo não esta funcionando\n");
    }else{
        display.init();
    }

    while(1){

        xf = acelerometro.getAccelX();
        yf = acelerometro.getAccelY();
        zf = acelerometro.getAccelZ();

        xfGyro = acelerometro.getGyroX();
        yfGyro = acelerometro.getGyroY();
        zfGyro = acelerometro.getGyroZ();

        ftoa(xf, x, 5);
        ftoa(yf, y, 5);
        ftoa(zf, z, 5);

        ftoa(xfGyro, xGyro, 5);
        ftoa(yfGyro, yGyro, 5);
        ftoa(zfGyro, zGyro, 5);

        display.setCursor(1, 10);
        display.printf("xAccel: %s\n", x);
        display.setCursor(2, 10);
        display.printf("yAccel: %s\n", y);
        display.setCursor(3, 10);
        display.printf("zAccel: %s\n", z);

        display.setCursor(5, 10);
        display.printf("xGyro: %s\n", xGyro);
        display.setCursor(6, 10);
        display.printf("yGyro: %s\n", yGyro);
        display.setCursor(7, 10);
        display.printf("zGyro: %s\n", zGyro);


        if(zf > 0.5)
            display.writeCommand(SSD1306_INVERT_DISPLAY);
        else
            display.writeCommand(SSD1306_NORMAL_DISPLAY);
        AppDelay();

    }


    I2C_close(handle);
}

void AppDelay(){    
#define T_1MS_COUNT                     (0x5DC0u)
    unsigned int delayVal = T_1MS_COUNT * 1000;

    while(delayVal)
    {
        delayVal--;
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    if (Board_initI2C() == false)
    {
        return (0);
    }

    Task_Handle task;
    Error_Block eb;

    Error_init(&eb);

    task = Task_create(i2c_test, NULL, &eb);
    if (task == NULL) {
        System_printf("Task_create() failed!\n");
        BIOS_exit(0);
    }

    BIOS_start();
    return (0);
}

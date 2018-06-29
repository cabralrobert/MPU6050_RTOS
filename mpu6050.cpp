#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include <stdio.h>
#include <string.h>

/* TI-RTOS Header files */
#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/drv/i2c/test/eeprom_read/src/I2C_log.h>
#include <ti/drv/i2c/test/eeprom_read/src/I2C_board.h>

#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/drv/i2c/test/eeprom_read/src/I2C_log.h>
#include <ti/drv/i2c/test/eeprom_read/src/I2C_board.h>
#include <convert.h>

#include <mpu6050.h>

mpu6050::mpu6050(I2C_Handle* handle) : handle(handle) {
    I2C_transactionInit(&this->i2cTransaction);
    i2cTransaction.slaveAddress = MPU6050_ADDRESS;
    i2cTransaction.timeout      = I2C_TRANSACTION_TIMEOUT;
}

bool mpu6050::test(){
    uint8_t txData = MPU6050_REG_WHO_AM_I;
    uint8_t rxData = 0x00;

    i2cTransaction.writeBuf     = &txData;
    i2cTransaction.writeCount   = sizeof(uint8_t);
    i2cTransaction.readBuf      = &rxData;
    i2cTransaction.readCount    = sizeof(uint8_t);
    transferStatus = I2C_transfer(*handle, &i2cTransaction);

    if(transferStatus == I2C_STS_SUCCESS && rxData == MPU6050_ADDRESS)
        return true;

    return false;
}

bool mpu6050::writeByte(char reg, char value){
    char txData[] = {reg, value};

    i2cTransaction.writeBuf     = txData;
    i2cTransaction.writeCount   = sizeof(txData);
    transferStatus = I2C_transfer(*handle, &i2cTransaction);

    if(transferStatus == I2C_STS_SUCCESS)
        return true;

    return false;
}



uint8_t mpu6050::readByte(char reg){
    char txData[] = {reg};

    uint8_t rxData = 0x00;

    i2cTransaction.writeBuf     = txData;
    i2cTransaction.writeCount   = sizeof(txData);
    i2cTransaction.readBuf      = &rxData;
    i2cTransaction.readCount    = sizeof(rxData);
    transferStatus = I2C_transfer(*handle, &i2cTransaction);

    if(transferStatus == I2C_STS_SUCCESS)
        return rxData;

    return -10;
}

bool mpu6050::configAccel(mpu6050_range_t range){

    switch (range) {
    case MPU6050_RANGE_2G:
        this->rangeAccel = 2;
        this->scaleAccel = 1/16384.0;
        break;
    case MPU6050_RANGE_4G:
        this->rangeAccel = 4;
        this->scaleAccel = 1/8192.0;
        break;
    case MPU6050_RANGE_8G:
        this->rangeAccel = 8;
        this->scaleAccel = 1/4096.0;
        break;
    case MPU6050_RANGE_16G:
        this->rangeAccel = 16;
        this->scaleAccel = 1/2048.0;
        break;
    default:
        break;
    }

    if(this->writeByte(MPU6050_REG_ACCEL_CONFIG, (range << 3)))
        return true;

    return false;
}

bool mpu6050::configGyro(mpu6050_dps_t range){

    switch (range) {
    case MPU6050_SCALE_250DPS:
        this->rangeGyro = 250;
        this->scaleGyro = 1/131.0;
        break;
    case MPU6050_SCALE_500DPS:
        this->rangeGyro = 500;
        this->scaleGyro = 1/65.5;
        break;
    case MPU6050_SCALE_1000DPS:
        this->rangeGyro = 1000;
        this->scaleGyro = 1/32.8;
        break;
    case MPU6050_SCALE_2000DPS:
        this->rangeGyro = 2000;
        this->scaleGyro = 1/16.4;
        break;
    default:
        break;
    }

    if(this->writeByte(MPU6050_REG_GYRO_CONFIG, (range << 3)))
        return true;

    return false;
}

bool mpu6050::reset(){
    if(this->writeByte(MPU6050_REG_PWR_MGMT_1, 0x0))
        return true;
    return false;
}

float mpu6050::getAccelX(){
    uint16_t x_aux;
    x_aux = (readByte(MPU6050_REG_ACCEL_XOUT_H) << 8) | (readByte(MPU6050_REG_ACCEL_XOUT_L));
    xAccel = convert_raw_to_float(x_aux, 16, &vali, this->rangeAccel * -1, this->rangeAccel, this->scaleAccel, 0);
    return xAccel;
}

float mpu6050::getAccelY(){
    uint16_t y_aux;
    y_aux = (readByte(MPU6050_REG_ACCEL_YOUT_H) << 8) | (readByte(MPU6050_REG_ACCEL_YOUT_L));
    yAccel = convert_raw_to_float(y_aux, 16, &vali, this->rangeAccel * -1, this->rangeAccel, this->scaleAccel, 0);
    return yAccel;
}

float mpu6050::getAccelZ(){
    uint16_t z_aux;
    z_aux = (readByte(MPU6050_REG_ACCEL_ZOUT_H) << 8) | (readByte(MPU6050_REG_ACCEL_ZOUT_L));
    zAccel = convert_raw_to_float(z_aux, 16, &vali, this->rangeAccel * -1, this->rangeAccel, this->scaleAccel, 0);
    return zAccel;
}

float mpu6050::getGyroX(){
    uint16_t x_aux;
    x_aux = (readByte(MPU6050_REG_GYRO_XOUT_H) << 8) | (readByte(MPU6050_REG_GYRO_XOUT_L));
    xGyro = convert_raw_to_float(x_aux, 16, &vali, this->rangeGyro * -1, this->rangeGyro, this->scaleGyro, 0);
    return xGyro;
}

float mpu6050::getGyroY(){
    uint16_t y_aux;
    y_aux = (readByte(MPU6050_REG_GYRO_YOUT_H) << 8) | (readByte(MPU6050_REG_GYRO_YOUT_L));
    yGyro = convert_raw_to_float(y_aux, 16, &vali, this->rangeGyro * -1, this->rangeGyro, this->scaleGyro, 0);
    return yGyro;
}

float mpu6050::getGyroZ(){
    uint16_t z_aux;
    z_aux = (readByte(MPU6050_REG_GYRO_ZOUT_H) << 8) | (readByte(MPU6050_REG_GYRO_ZOUT_L));
    zGyro = convert_raw_to_float(z_aux, 16, &vali, this->rangeGyro * -1, this->rangeGyro, this->scaleGyro, 0);
    return zGyro;
}

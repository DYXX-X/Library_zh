/*****************************************************************************
 * 版权所有（C）2011，Embedded Artists AB保留所有权利。
 *
 ****************************************************************************** 本文描述的软件仅用于说明目的，其向客户提供关于产品的编程信息。本软件按“原样”提供，无任何担保。Embedded Artists AB对软件的使用不承担任何责任或义务，不向产品转让任何专利、版权或掩模作品权利下的许可或所有权。Embedded Artists AB保留对软件进行更改的权利，恕不另行通知。Embedded Artists AB也不表示或保证此类应用程序适用于指定用途，无需进一步测试或修改。
 *****************************************************************************/
#ifndef __PCA9532C_H
#define __PCA9532C_H


#define PCA9532_I2C_ADDR    (0xC0>>1)

#define PCA9532_INPUT0 0x00
#define PCA9532_INPUT1 0x01
#define PCA9532_PSC0   0x02
#define PCA9532_PWM0   0x03
#define PCA9532_PSC1   0x04
#define PCA9532_PWM1   0x05
#define PCA9532_LS0    0x06
#define PCA9532_LS1    0x07
#define PCA9532_LS2    0x08
#define PCA9532_LS3    0x09

#define PCA9532_AUTO_INC 0x10


/*
 * 基板上的键映射到PCA9532上的LED0->LED3。
 */

#define KEY1 0x0001
#define KEY2 0x0002
#define KEY3 0x0004
#define KEY4 0x0008

#define KEY_MASK 0x000F

/*
 * MMC卡检测和MMC写保护映射到PCA9532上的LED4和LED5。请注意，WP处于低活动状态。
 */

#define MMC_CD 0x0010
#define MMC_WP 0x0020

#define MMC_MASK  0x30

/* 注意：PCA9532上的LED6和LED7未连接到任何东西*/
#define PCA9532_NOT_USED 0xC0

/*
 * 以下是启用/禁用LED时要使用的LED常量。LED名称是印刷在基板上的名称，而不是PCA9532设备的名称。PCA9532上的base_LED1->LED8、base_LED2->LED9等。
 */

#define LED1 0x0100
#define LED2 0x0200
#define LED3 0x0400
#define LED4 0x0800
#define LED5 0x1000
#define LED6 0x2000
#define LED7 0x4000
#define LED8 0x8000

#define LED_MASK 0xFF00

void pca9532_init (void);
uint16_t pca9532_getLedState (uint32_t shadow);
void pca9532_setLeds (uint16_t ledOnMask, uint16_t ledOffMask);
void pca9532_setBlink0Period(uint8_t period);
void pca9532_setBlink0Duty(uint8_t duty);
void pca9532_setBlink0Leds(uint16_t ledMask);
void pca9532_setBlink1Period(uint8_t period);
void pca9532_setBlink1Duty(uint8_t duty);
void pca9532_setBlink1Leds(uint16_t ledMask);

#endif /* 结束__PCA9532C_H*/
/****************************************************************************
**                            文件结尾
*****************************************************************************/


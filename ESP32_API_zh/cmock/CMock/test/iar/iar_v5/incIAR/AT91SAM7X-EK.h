// ----------------------------------------------------------------------------
//         ATMEL微控制器软件支持-ROUSSET-
// ----------------------------------------------------------------------------
// DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------
// 文件名：AT91SAM7X-EK.h
// 对象：AT91SAM7X-EK评估板功能定义文件
//
//  ----------------------------------------------------------------------------

#ifndef AT91SAM7X_EK_H
#define AT91SAM7X_EK_H

/*-----------------*/
/* LED定义*/
/*-----------------*/
#define AT91B_LED1            (1<<19)       // AT91C_PIO_PB19 AT91C_PB19_PWM0 AT91C_PB19_TCLK1
#define AT91B_LED2            (1<<20)       // AT91C_PIO_PB20 AT91C_PB20_PWM1 AT91C_PB20_PWM1
#define AT91B_LED3            (AT91C_PIO_PB21)       // AT91C_PIO_PB21 AT91C_PB21_PWM2 AT91C_PB21_PCK1
#define AT91B_LED4            (AT91C_PIO_PB22)       // AT91C_PIO_PB22 AT91C_PB22_PWM3 AT91C_PB22_PCK2
#define AT91B_NB_LEB          4
#define AT91B_LED_MASK        (AT91B_LED1|AT91B_LED2|AT91B_LED3|AT91B_LED4)
#define AT91D_BASE_PIO_LED 	  (AT91C_BASE_PIOB)

#define AT91B_POWERLED        (1<<25)       // PB25


/*-------------------------------*/
/* 操纵手柄位置定义*/
/*-------------------------------*/
#define AT91B_SW1           (1<<21)  // PA21向上按钮AT91C_PA21_TF AT91C_PA 21_NPCS10
#define AT91B_SW2           (1<<22)  // PA22向下按钮AT91C_PA22_TK AT91C_PA 22_SPCK1
#define AT91B_SW3           (1<<23)  // PA23左按钮AT91C_PA23_TD AT91C_PAG_MOSI1
#define AT91B_SW4           (1<<24)  // PA24右键AT91C_PA24_RD AT91C_PAG24_MISO1
#define AT91B_SW5           (1<<25)  // PA25按钮AT91C_PA25_RK AT91C_PAG_NPCS11
#define AT91B_SW_MASK       (AT91B_SW1|AT91B_SW2|AT91B_SW3|AT91B_SW4|AT91B_SW5)


#define AT91D_BASE_PIO_SW   (AT91C_BASE_PIOA)

/*------------------*/
/* CAN定义*/
/*------------------*/
#define AT91B_CAN_TRANSCEIVER_RS  (1<<2)    // PA2

/*--------------*/
/* 时钟*/
/*--------------*/
#define AT91B_MAIN_OSC        18432000               // 主振荡器MAINCK
#define AT91B_MCK             ((18432000*73/14)/2)   // 输出PLL时钟

#endif /* AT91SAM7X-EK_H */


#include <msp430.h>
#include <stdint.h>
#include "project_settings.h"
#include "nrf24.h"
#include "nrf24network.h"
#include "timing.h"
#include "task.h"
#include "uart.h"
#include "spi.h"
#include "hal_general.h"
#include "thief.h"
#include "thief_brainframe.h"
#include "adc.h"
#include "hal_adc.h"

/*  Macros */
#define RF_SPI_CH SPI_B0

/* Function Declarations */
void SetClk24MHz(void);
void SetVcoreUp (unsigned int level);

void RF1_CE(uint8_t out);
void RF1_CSN(uint8_t out);
void RF1_PollIRQ(void);

void RF2_CE(uint8_t out);
void RF2_CSN(uint8_t out);
void RF2_PollIRQ(void);

void RF1_Init(void);
void RF2_Init(void);

void RF1_RxPayloadHandler(uint8_t * data, uint8_t length);
void RF1_AckPayloadHandler(uint8_t * data, uint8_t length);
void RF1_AckReceivedHandler(void);
void RF1_MaxRetriesHandler(void);

void RF2_RxPayloadHandler(uint8_t * data, uint8_t length);
void RF2_AckPayloadHandler(uint8_t * data, uint8_t length);
void RF2_AckReceivedHandler(void);
void RF2_MaxRetriesHandler(void);

void SendTest(void);
void ThisNode_TestMsgHandler(uint8_t * data, uint8_t length, uint8_t from);
void ThisNode2_TestMsgHandler(uint8_t * data, uint8_t length, uint8_t from);

void Trip(void);
void SetHBridge(void);
void LEDoff(void);
void Arm(void);
void Disarm(void);
void Difficulty(uint8_t);
void printADCValue(uint16_t ADCval, void *);

/* Variables */
//nrfnet_t RF2_Net;

char test_msg[16] = {"Test Message!\r\n"};
char reply_msg[25] = {"Test Message Response!\r\n"};
uint8_t armed = 1;
uint8_t difficulty = 10;
uint8_t impact = 0;

int main(void) {

    static uint8_t sys_id;

    LogMsg(0, "System Starting...");
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    SetClk24MHz();

    DisableInterrupts();

    Timing_Init();
    Task_Init();

    ADC_Init();
    ADC_AddChannel(ADC0, 1000, printADCValue, 0);

	UART_Init(UART0);
    UART_Init(UART1);
    SetHBridge();

    // Setup the SPI channel to be used by the NRF nodes
    spi_settings_t spi_settings;
    spi_settings.channel = THIEF_SPI;
    spi_settings.bit_rate = 100000;
    spi_settings.hal_settings.char7bit = 0;
    spi_settings.hal_settings.msb_first = 1;
    spi_settings.mode = 0;
    SPI_Init(&spi_settings);

    //Setup IRQ, CE, CSN for node 1
    P2DIR |= BIT3 | BIT4; // CE, CSN as output
    P2DIR &= ~BIT5; // IRQ as input
    RF1_CSN(1);

    //Setup IRQ, CE, CSN for node 2
    P7DIR |= BIT0; // CE as output
    P2DIR |= BIT2; // CSN as output
    P6DIR &= ~BIT4; // IRQ as input
    RF2_CSN(1);

    EnableInterrupts();

    // Setup the default network, this uses the THIS_NODE macro found in project_settings.h
    Thief_Init(RF1_CE, RF1_CSN, Arm, Disarm, Difficulty);

    // Setup the second node as THIS_NODE2 using the extended network framework used on systems with
    // multiple nodes
    //Thief_BrainframeInit(RF2_CE, RF2_CSN, 0, 0);

    int8_t  Hit= Task_Schedule(Trip, 0, 0, 10);
    int8_t  LEDReset= Task_Schedule(LEDoff, 0, 0, 10);

    LogMsg(sys_id, "System Initialized!");
    while(1){
        SystemTick();
        // Poll the interrupt pins coming from the radios so we know whens something has happened
        RF1_PollIRQ();
        RF2_PollIRQ();
    }
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Enable pin on the radio
void RF1_CE(uint8_t out){
    P2OUT = (P2OUT & ~BIT4) | (out << 4);
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Select pin on the radio
void RF1_CSN(uint8_t out){
    P2OUT = (P2OUT & ~BIT3) | (out << 3);
    // Poll the interrupt here so that we poll all the time especially as SPI transactions are happening
    RF1_PollIRQ();
}

// Method to poll the interrupt pin and see if an interrupt has occured
void RF1_PollIRQ(void){
    static uint8_t pin_state = 1;
    uint8_t new_state = (P2IN & BIT5) >> 5;

    if( (new_state != pin_state) && !new_state) {
        nrf24_NetworkISRHandler();
    }
    pin_state = new_state;
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Enable pin on the radio
void RF2_CE(uint8_t out){
    P7OUT = (P7OUT & ~BIT0) | out;
}

// This function is provided to the network layer in the init function and is used to control the
// Chip Select pin on the radio
void RF2_CSN(uint8_t out){
    P2OUT = (P2OUT & ~BIT2) | (out << 2);
    // Poll the interrupt here so that we poll all the time especially as SPI transactions are happening
    RF2_PollIRQ();
}
extern nrfnet_t Brainframe_Net;
// Method to poll the interrupt pin and see if an interrupt has occured
void RF2_PollIRQ(void){
    static uint8_t pin_state = 1;
    uint8_t new_state = (P6IN & BIT4) >> 4;

    if( (new_state != pin_state) && !new_state) {
        nrf24_NetworkISRHandlerN(Brainframe_Net);
    }
    pin_state = new_state;
}


void SetClk24MHz(){
    // Increase Vcore setting to level3 to support fsystem=25MHz
    // NOTE: Change core voltage one level at a time..
    SetVcoreUp (0x01);
    SetVcoreUp (0x02);
    SetVcoreUp (0x03);

    P5SEL |= BIT2+BIT3;
    UCSCTL6 &= ~XT2OFF; // Enable XT2
    UCSCTL6 &= ~XT2BYPASS;
    UCSCTL3 = SELREF__XT2CLK; // FLLref = XT2
    UCSCTL4 |= SELA_2 + SELS__DCOCLKDIV + SELM__DCOCLKDIV;

    UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
    // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
    do
    {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                        // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
    }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

    // Disable the FLL control loop
    __bis_SR_register(SCG0);

    // Select DCO range 24MHz operation
    UCSCTL1 = DCORSEL_7;
    /* Set DCO Multiplier for 24MHz
    (N + 1) * FLLRef = Fdco
    (5 + 1) * 4MHz = 24MHz  */
    UCSCTL2 = FLLD0 + FLLN0 + FLLN2;
    // Enable the FLL control loop
    __bic_SR_register(SCG0);

  /* Worst-case settling time for the DCO when the DCO range bits have been
     changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
     UG for optimization.
     32 x 32 x 24MHz / 4MHz = 6144 = MCLK cycles for DCO to settle */
  __delay_cycles(70000);

    // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
    do {
        // Clear XT2,XT1,DCO fault flags
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
        // Clear fault flags
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG); // Test oscillator fault flag
}

void SetVcoreUp (unsigned int level)
{
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}

void SetHBridge()
{
    P1OUT &= ~BIT2;
    P1OUT |= BIT3;
    P1OUT |= BIT0; //led
}

void Trip()
{
    if(armed == 1 & impact == 1)
       {
           Thief_Trip(difficulty);
           P1OUT ^= BIT2;
           P1OUT ^= BIT3;
           P1OUT |= BIT0; //led
           impact = 0;
       }
}

void LEDoff(void)
{
    P1OUT &= ~BIT0; //led off
}

void Arm(void)
{
    armed = 1;
}

void Disarm(void)
{
    armed = 0;
}

void Difficulty(uint8_t diffSet)
{
    difficulty = diffSet;
}

void printADCValue(uint16_t ADCval, void * tempPointer) {
    //uint8_t ADC_percentage = (uint8_t) ((ADCval / 4096.0) *100.0);
    //UART_WriteByte(SUBSYSTEM_UART, ADC_percentage);
    if (ADCval >= 1000)
    {
        impact = 1;
    }
}

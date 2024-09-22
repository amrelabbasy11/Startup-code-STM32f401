/*
    @file   startup_stm32f401rc.c
    @author Your Name
    @brief  Startup code for STM32F401RC
*/

#define NULL 0

typedef unsigned int uint32_t;

extern uint32_t _estack, _etext, _sdata, _edata, _sbss, _ebss, _sidata;

extern int main(void);

void Reset_Handler(void);
void NMI_Handler(void) __attribute__ ((alias ("Default_Handler")));
void HardFault_Handler(void) __attribute__ ((alias ("Default_Handler")));
void MemManage_Handler(void) __attribute__ ((alias ("Default_Handler")));
void BusFault_Handler(void) __attribute__ ((alias ("Default_Handler")));
void UsageFault_Handler(void) __attribute__ ((alias ("Default_Handler")));
void SVC_Handler(void) __attribute__ ((alias ("Default_Handler")));
void DebugMon_Handler(void) __attribute__ ((alias ("Default_Handler")));
void PendSV_Handler(void) __attribute__ ((alias ("Default_Handler")));
void SysTick_Handler(void) __attribute__ ((alias ("Default_Handler")));

// Add other interrupt handlers as needed
void Default_Handler(void);

uint32_t * const MSP_Value = (uint32_t *)&_estack;

/* Vector table for Cortex M4 */
uint32_t *Vector_Table[] __attribute__ ((section (".isr_vector"))) = {
    (uint32_t *)MSP_Value,                          /* Main Stack Pointer */
    (uint32_t *)Reset_Handler,                     /* Reset Handler */
    (uint32_t *)NMI_Handler,                       /* NMI Handler */
    (uint32_t *)HardFault_Handler,                 /* Hard Fault Handler */
    (uint32_t *)MemManage_Handler,                 /* Memory Management Fault */
    (uint32_t *)BusFault_Handler,                  /* Bus Fault */
    (uint32_t *)UsageFault_Handler,                /* Usage Fault */
    0, 0, 0, 0,                                     /* Reserved */
    (uint32_t *)SVC_Handler,                       /* SVCall */
    (uint32_t *)DebugMon_Handler,                  /* Debug Monitor */
    0,                                             /* Reserved */
    (uint32_t *)PendSV_Handler,                    /* PendSV */
    (uint32_t *)SysTick_Handler,                   /* SysTick */
    // Other handlers go here
    (uint32_t *)Default_Handler                    /* Default handler for all interrupts */
};

static void System_Initialization(void) {
    /* Clock initialization and other system setup */
}

void Reset_Handler(void) {
    uint32_t Section_Size = 0;
    uint32_t *MemSourceAddr = NULL;
    uint32_t *MemDestAddr = NULL;

    /* 1) Copy the data segment initializers from flash to SRAM */
    Section_Size = &_edata - &_sdata;  /* Length of .data segment */
    MemSourceAddr = (uint32_t *)&_sidata;  /* Load Memory Address */
    MemDestAddr = (uint32_t *)&_sdata;     /* Virtual Memory Address */
    
    for(uint32_t MemCounter = 0; MemCounter < Section_Size; MemCounter++) {
        *MemDestAddr++ = *MemSourceAddr++;
    }

    /* 2) Initialize the .bss segment with zero */
    Section_Size = &_ebss - &_sbss;        /* Length of .bss segment */
    MemDestAddr = (uint32_t *)&_sbss;     /* Start address of .bss segment */

    for(uint32_t MemCounter = 0; MemCounter < Section_Size; MemCounter++) {
        *MemDestAddr++ = 0;
    }

    /* 3) Call the system initialization function */
    System_Initialization();

    /* 4) Call the main function */
    main();
}

void Default_Handler(void) {
    while (1) {
        // Handle unexpected interrupts
    }
}

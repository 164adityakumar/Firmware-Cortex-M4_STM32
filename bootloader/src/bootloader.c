#include "common-defines.h"
#include <libopencm3/stm32/memorymap.h>

#define BOOTLOADER_SIZE (0x8000U) //U stands for unsigned 32KB i.e. 32768 bytes is 8000H
#define MAIN_APP_START_ADDRESS (FLASH_BASE+BOOTLOADER_SIZE)

// const uint8_t data[0x8000]={0};

static void jump_to_main(void){

   typedef void (*void_fn)(void); //this is a function pointer that takes nothing as input and does nothing , a function pointer is a pointer that points to the memory address of a function. It allows you to call a function indirectly through the pointer

   uint32_t* reset_vector_entry = (uint32_t*) (MAIN_APP_START_ADDRESS + 4U); // we add 4 to get to the next address of the reset vector bcus 1st one is the stack pointer value as the size of each entry in vector interrupt table is 4 bytes so 4U is added

   uint32_t* reset_vector=(uint32_t*) (*reset_vector_entry);

   void_fn jump_fn=(void_fn)reset_vector; //this will help in jumping to that address
   jump_fn();
}

int main (void){

   // volatile uint8_t x=0;
   // for(uint32_t i=0;i<0x8000;i++)
   // {
   //    x+=data[i];
   // }
   // The above part of the code is to just see that on make if it throws the error if the bootloader exceed the permitted 32KB size

   jump_to_main();

   //never return

    return 0;
}

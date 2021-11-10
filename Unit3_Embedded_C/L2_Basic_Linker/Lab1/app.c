#include "uart.h"

unsigned char string_buffer[100] = "Learn-In-Depth: Mazen Talaat";

void main(void){
    Uart_Send_String(string_buffer);
}

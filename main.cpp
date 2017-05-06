#include "mbed.h"
#include "MAG3110.h"

int main(void);
Serial pc(USBTX, USBRX, 115200);
DigitalOut led1(LED1);
volatile int val1;
volatile int val2;
volatile int val3;

int main() {
    MAG3110 mag(D14, D15);
    wait_ms(100);
    mag.enable();
    wait_ms(100);
    pc.printf("%i", mag.whoAmI());
    wait_ms(100);
    while(true){
        led1 = !led1;
        val1 = mag.whoAmI();
        wait_ms(100);
        val2 = mag.dataReady();
        wait_ms(100);
        val3 = mag.getMagAxis(MAG3110_X_AXIS);
        wait_ms(100);

        pc.printf("val1: %i, ",val1);
        pc.printf("val2: %i, ",val2);
        pc.printf("val3: %i \r\n",val3);
    }

}
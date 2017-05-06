#include "mbed.h"
#include "MAG3110.h"
#include "main.h"

Serial pc(USBTX, USBRX, 115200);
DigitalOut led1(LED1);
MAG3110 mag(D14, D15);
Timer timer;
int data;

int main() {
    mag.enable();
    int revs = 0;
    int rpm = 0;
    int drev = 0;
    bool lock = false;
    timer.start();
    int begin = timer.read_us();

    while (true){

        led1 = !led1;
        data = mag.getMagAxis(MAG3110_X_AXIS);
        
        if (data > 1000) {
            if (lock == false) {
                revs++;
                drev++;
                lock = true;
            }
        } 
        else 
        {
            lock = false;
        }

        if (drev == 10 )
        {
            rpm = (timer.read_us() - begin) * .000006;
            drev = 0;
            timer.reset();
            begin = 0;
            pc.printf("rpm: %8i, ",rpm);
            pc.printf("revs: %8i\r",revs);
        }

    }

}
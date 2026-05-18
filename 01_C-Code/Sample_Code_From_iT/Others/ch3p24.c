#include <stdio.h>
main ()
{
    unsigned short a, b;
    int d, e;

    d = 0xff;
    e = -0xff;   // this is not a good example!!!!
    a = 0x01;
    b = 0xa1;

    printf ("%x %x %x\n", d << 1, e << 1, e >> 1);
    printf ("%x %x %x %x\n", a & b, a | b, a ^ b,(unsigned short) ~a);
}

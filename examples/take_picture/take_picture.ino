
#include "hicat.h"

void setup()
{
    hicat.begin();

    char name[16] = "0.jpg";
    for (int i = 0; i < 8; i++)
    {
        name[0] = '0' + i;
        hicat.snapshot(name);

        delay(10);
    }
}

void loop()
{
}
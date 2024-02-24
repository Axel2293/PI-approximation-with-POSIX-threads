#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double rectangels=100000000;

int main(void)
{
    double pi=0;
    double base_all= (double)1/rectangels; // Devide 1 to get all the bases of the rectangel
    double half=base_all/2.0;

    for (double i = 0; i <= 1.0; i+=base_all)
    {
        double base_curr = i+base_all;
        double height= sqrt(1.0-pow(i-half, 2)); //Calculate the height on the mid base point
        pi+=base_all*height;

    }
    printf("\nPI: %.16F\n", pi*4);

    return 0;
}

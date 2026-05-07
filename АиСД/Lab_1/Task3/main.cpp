#include "complex_number.h"
int main()
{
    try 
    {
        complex_number z1(3.0, 4.0);
        complex_number z2(1.0, -2.0);

        std::cout << "z1 = " << z1 << std::endl;
        std::cout << "z2 = " << z2 << std::endl;

        std::cout << "z1 + z2 = " << z1 + z2 << std::endl;
        std::cout << "z1 - z2 = " << z1 - z2 << std::endl;
        std::cout << "z1 * z2 = " << z1 * z2 << std::endl;
        std::cout << "z1 / z2 = " << z1 / z2 << std::endl;

        std::cout << "|z1| = " << z1.complexModulus(z1) << std::endl;
        std::cout << "|z2| = " << z2.complexModulus(z2) << std::endl;

        std::cout << "arg(z1) = " << z1.complexArgument(z1) << " radians" << std::endl;
        std::cout << "arg(z2) = " << z2.complexArgument(z2) << " radians" << std::endl;

    } 
    catch (const std::exception & e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
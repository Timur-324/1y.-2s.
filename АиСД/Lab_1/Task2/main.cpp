#include "logical_values_array.h"


int main()
{
    // std::cout << sizeof(unsigned int);
    std::cout << "=== logical_values_array Test ===\n\n";

    logical_values_array a(5);
    logical_values_array b(3);

    char bin_a[33], bin_b[33];
    a.to_binary_string(bin_a);
    b.to_binary_string(bin_b);

    std::cout << "a = " << a.get_value() << " (" << bin_a << ")\n";
    std::cout << "b = " << b.get_value() << " (" << bin_b << ")\n\n";

    auto and_ab = a & b;
    auto or_ab  = a | b;
    auto xor_ab = a ^ b;
    auto not_a  = ~a;

    char bin_and[33], bin_or[33], bin_xor[33], bin_not[33];
    and_ab.to_binary_string(bin_and);
    or_ab.to_binary_string(bin_or);
    xor_ab.to_binary_string(bin_xor);
    not_a.to_binary_string(bin_not);

    std::cout << "a & b = " << and_ab.get_value() << " → " << bin_and << "\n";
    std::cout << "a | b = " << or_ab.get_value()  << " → " << bin_or  << "\n";
    std::cout << "a ^ b = " << xor_ab.get_value() << " → " << bin_xor << "\n";
    std::cout << "~a    = " << not_a.get_value()  << " → " << bin_not << "\n\n";

    auto implies_ab = a.implies(b);
    auto equivalence_ab = a.equivalence(b);
    auto nand_ab = a.nand(b);
    auto nor_ab = a.nor(b);

    char bin_impl[33], bin_eqv[33], bin_nand[33], bin_nor[33];
    implies_ab.to_binary_string(bin_impl);
    equivalence_ab.to_binary_string(bin_eqv);
    nand_ab.to_binary_string(bin_nand);
    nor_ab.to_binary_string(bin_nor);

    std::cout << "a → b     = " << implies_ab.get_value()     << " → " << bin_impl << "\n";
    std::cout << "a ≡ b     = " << equivalence_ab.get_value() << " → " << bin_eqv  << "\n";
    std::cout << "a ↑ b     = " << nand_ab.get_value()        << " → " << bin_nand << "\n";
    std::cout << "a ↓ b     = " << nor_ab.get_value()         << " → " << bin_nor  << "\n\n";

    std::cout << "a == b: " << std::boolalpha << logical_values_array::equals(a, b) << "\n";
    std::cout << "a == a: " << logical_values_array::equals(a, a) << "\n\n";

    std::cout << "Bits of a (5):\n";
    for (size_t i = 0; i < 5; ++i) {
        std::cout << "a[" << i << "] = " << a[i] << "\n";
    }

    std::cout << "\n=== Test completed ===\n";
    return 0;
}
#include "matrix.h"


int main()
{
    try {
        std::cout << "=== Тестирование класса matrix ===\n\n";

        std::cout << "1. Создаём матрицу A (2x2):\n";
        matrix A(2, 2);
        A[{0,0}] = 1; A[{0,1}] = 2;
        A[{1,0}] = 3; A[{1,1}] = 4;

        std::cout << "A = \n" << A << "\n";

        std::cout << "2. Создаём матрицу B (2x2):\n";
        matrix B(2, 2);
        B[{0,0}] = 5; B[{0,1}] = 6;
        B[{1,0}] = 7; B[{1,1}] = 8;

        std::cout << "B = \n" << B << "\n";

        // 3. Сложение
        std::cout << "3. A + B:\n";
        matrix C = A + B;
        std::cout << "A + B = \n" << C << "\n";

        // 4. Умножение на скаляр
        std::cout << "4. 2 * A:\n";
        matrix D = 2.0 * A;
        std::cout << "2 * A = \n" << D << "\n";

        // 5. Умножение матриц
        std::cout << "5. A * B (матричное умножение):\n";
        matrix E = A * B;
        std::cout << "A * B = \n" << E << "\n";

        // 6. Транспонирование
        std::cout << "6. Транспонированная A^T:\n";
        matrix At = A.transposed();
        std::cout << "A^T = \n" << At << "\n";

        // 7. Определитель
        std::cout << "7. Определитель A: " << A.determinant() << "\n\n";

        // 8. Обратная матрица
        std::cout << "8. Обратная матрица A⁻¹:\n";
        matrix A_inv = A.inverse_matrix();
        std::cout << "A⁻¹ = \n" << A_inv << "\n";


    } catch (const std::exception & e) 
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
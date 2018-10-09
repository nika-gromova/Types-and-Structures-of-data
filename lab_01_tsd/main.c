#include "io.h"
#include "defines.h"
#include "process.h"

int main(void)
{
    int rc; // код возврата
    char first_num[40], second_num[40]; //  считываемые строки
    int M1[30], M2[30]; // массив цифр мантиссы
    int n1, n2; // длина массивов цифр мантиссы
    int P1 = 0, P2 = 0; // числа порядка
    int sign_m_1 = 0, sign_m_2 = 0; // знаки мантиссы
    int sign_p_1 = 0, sign_p_2 = 0; // знаки порядка
    int i_point_1 = -1, i_point_2 = -1; // место точки (значение индекса элемента массива, перед которым должна стоять точка)

    printf("This is a program for multiplication of two long numbers.\n");
    printf("Please enter two numbers in for '+/-0.mE+/-p' or '+/-0.me+/-p',\n");
    printf("where m - is a mantissa (not  more than 30 symbols)\n");
    printf("and p - is a numeric exponent (not more than 5 symbols).\n");
    rc = input(first_num, M1, &n1, &P1, &sign_m_1, &sign_p_1, &i_point_1);
    if (rc == OK)
    {
        rc = input(second_num, M2, &n2, &P2, &sign_m_2, &sign_p_2, &i_point_2);
        if (rc == OK)
        {
            /*printf ("%d ", sign_m_1);
            for (int i = 0; i < n1; i++)
            {
                if (i == i_point_1)
                    printf(" . ");
                printf("%d", M1[i]);
            }
            if (P1 != 0)
            {
                printf(" E ");
                printf("%d ", sign_p_1);
                printf("%d", P1);

            }

            printf("\n");
            printf ("%d ", sign_m_2);
            for (int i = 0; i < n2; i++)
            {
                if (i == i_point_2)
                    printf(" . ");
                printf("%d", M2[i]);
            }
            if (P2 != 0)
            {
                printf(" E ");
                printf("%d ", sign_p_2);
                printf("%d", P2);

            }*/

            printf("\n");

            int len_c = n1 + n2 + 1; // длина нового массива - результата
            int c[len_c]; // новый массив - результат
            int total_point = 0; // место точки в массиве-результате (значение индекса элемента массива, перед которым должна стоять точка)
            int total_P = 0; // порядок числа в результате
            int total_sign_P = 0; // знак порядка в результате
            int total_sign_m; // знак мантиссы в результате

            // определение знака мантисы результата (-1 соответствует минусу, 1 - плюсу
            if ((sign_m_1 > 0 && sign_m_2 > 0) || (sign_m_1 < 0 && sign_m_2 < 0))
                total_sign_m = 1;
            else
                total_sign_m = -1;

            // осуществление процесса умножения
            rc = process(M1, M2, n1, n2, i_point_1, i_point_2, &total_point, P1, P2, &total_P, sign_p_1, sign_p_2, &total_sign_P, c, &len_c);
            if (rc == OK) // если не возникло ошибок, результат выводится на экран
            {
                output(c, len_c, total_P, total_sign_m, total_sign_P, total_point);
            }
            else
                printf("Error, numbers can't be multiplied. Numeric exponent is overflow"); // Возникло переполнение порядка
        }
        else
        {
            if (rc == TOO_MUCH_SYMB)
                printf("Incorrect input. Too much symbols in string"); // слишком много символов введено
            else if (rc == INPUT_ERROR)
                printf("Incorrect input"); // Число введено неверно
            else if (rc == M_COUNT_ERROR)
                printf("Incorrect input. Mantissa is overflow"); // введено слишком много цифр мантиссы
            else if (rc == P_COUNT_ERROR)
                printf("Incorrect input. Numeric exponent is overflow"); // введено слишком много цифр порядка
            else if (rc == POINT_ERROR)
                printf("Incorrect input. Inputed too much dots"); // введено слишком много точек
        }
    }
    else
    {
        if (rc == TOO_MUCH_SYMB)
            printf("Incorrect input. Too much symbols in string"); // слишком много символов введено
        else if (rc == INPUT_ERROR)
            printf("Incorrect input"); // Число введено неверно
        else if (rc == M_COUNT_ERROR)
            printf("Incorrect input. Mantissa is overflow"); // введено слишком много цифр мантиссы
        else if (rc == P_COUNT_ERROR)
            printf("Incorrect input. Numeric exponent is overflow"); // введено слишком много цифр порядка
        else if (rc == POINT_ERROR)
            printf("Incorrect input. Inputed too much dots"); // введено слишком много точек
    }



    printf("\nReturn code: rc = %d\n", rc); // Печать кода возврата
    return rc;
}

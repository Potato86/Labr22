#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef double (*TFun)(double);

double funcY(double x);
double funcV(double x);
double funcS(double x);
void Out_Rez(TFun f, double xn, double xk, double h);
void transform(TFun prtf, double xmin, double dx);

int main() {
    setlocale(LC_CTYPE, "ru_RU.UTF-8");

    double a, b, h, x;
    int choice, funcChoice;
    TFun currentFunc = NULL;

    printf("Задание 1. Табуляция трёх функций\n");
    printf("Введите a, b, h: ");
    scanf("%lf %lf %lf", &a, &b, &h);

    printf("\nY(x):\n");
    Out_Rez(funcY, a, b, h);
    printf("\nV(x):\n");
    Out_Rez(funcV, a, b, h);
    printf("\nS(x):\n");
    Out_Rez(funcS, a, b, h);

    do {
        printf("\n--- МЕНЮ ---\n");
        printf("1 - вычислить значение\n");
        printf("2 - табулировать\n");
        printf("3 - выполнить операцию (Вариант 21)\n");
        printf("0 - выход\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice >= 1 && choice <= 3) {
            printf("Выберите функцию (1-Y, 2-V, 3-S): ");
            scanf("%d", &funcChoice);
            if (funcChoice == 1) currentFunc = funcY;
            else if (funcChoice == 2) currentFunc = funcV;
            else if (funcChoice == 3) currentFunc = funcS;
            else { printf("Неверный выбор функции\n"); continue; }
        }

        if (choice == 1) {
            printf("Введите x: ");
            scanf("%lf", &x);
            printf("y = %lf\n", currentFunc(x));
        }
        else if (choice == 2) {
            printf("Введите начало, конец, шаг: ");
            scanf("%lf %lf %lf", &a, &b, &h);
            Out_Rez(currentFunc, a, b, h);
        }
        else if (choice == 3) {
            printf("Введите начало интервала и шаг: ");
            scanf("%lf %lf", &a, &h);
            transform(currentFunc, a, h);
        }
        else {
            printf("Неверный выбор\n");
        }
    } while (1);

    return 0;
}

double funcY(double x) {
    if (x <= 0) return 0;
    return log(fabs(sqrt(pow(x, 3))));
}

double funcV(double x) {
    if (x > 1) return sqrt(tan(x * x - 1));
    else if (x >= 0 && x <= 1) return -2 * x;
    else return exp(cos(x));
}

double funcS(double x) {
    double t;
    if (fabs(x + 1) < 1e-12) return 0;
    t = (x - 1) / (x + 1);
    return t + (1.0 / 3.0) * pow(t, 3) + (1.0 / 5.0) * pow(t, 5) + (1.0 / 7.0) * pow(t, 7);
}

void Out_Rez(TFun f, double xn, double xk, double h) {
    double x;
    for (x = xn; x <= xk; x += h) {
        printf("| x = %6.2lf | y = %10.4lf |\n", x, f(x));
    }
}

void transform(TFun prtf, double xmin, double dx) {
    int i;
    int crossed = 0;
    double x_curr;

    for (i = 0; i <= 10; i++) {
        x_curr = xmin + i * dx;
        if (fabs(x_curr) < 1e-9) {
            crossed = 1;
            break;
        }
    }

    if (crossed) {
        printf("Функция пересекает ось ординат (x=0).\n");
    }
    else {
        printf("Функция НЕ пересекает ось ординат (x=0).\n");
    }
}
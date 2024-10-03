/*
Порядок выполнения программы
1 Задается u(x)
2 Для нее расчитывается значения f(x) в узлах сетки
3 По этим значениям строиться V_h 
4 Исследуем погрешноссть

Уравнение вида:
-Uxx + p(x)Ux + q(x)U = f(x)
q(x) >= c > 0
p(x),q(x)!= const

Для лабораторной будем изучать 
u(x) = x^2 * sin(2*pi*x)
*/

#include <iostream>
#include <cmath>
#include <vector>

#define NUM double
#define PI 3.141592653589793238462643383279


NUM Uxx(NUM x) {
    return (NUM)2 * sin(PI * x * 2) + 8 * PI * x * cos(PI * x * 2) - 4 * PI * PI * x * x * sin(PI * x * 2);
}

NUM Ux(NUM x) {
    return (NUM)2 * x * sin(x * PI * 2) + PI * x * x * 2 * cos(PI * x * 2);
}

NUM U(NUM x) {
    return x * x * sin(PI * x * 2);
}

NUM q(NUM x) {
    return x * 2 + sqrt(PI);
}

NUM p(NUM x) {
    return x * x + sqrt(PI * PI);
}
NUM f(NUM point) {
    return point * point;
}

bool f(std::vector<NUM> & f_h, NUM a, NUM b, NUM h) {
    f_h.resize((b - a) / h);
   
    for (auto& i : f_h) {
        i = -Uxx(a) + p(a) * Ux(a) + q(a) * U(a);
        a += h;
    }
    return true;
}

void thomas_algorithm(std::vector<NUM> &x, const std::vector<NUM>& a, const std::vector<NUM>& b, const std::vector<NUM>& c, const std::vector<NUM>& d) {
    int n = b.size();
    std::vector<NUM> x(n);  
    std::vector<NUM> cp(n); 
    std::vector<NUM> dp(n); 

    cp[0] = b[0];
    dp[0] = d[0];

    for (int i = 1; i < n; ++i) {
        NUM m = a[i - 1] / cp[i - 1];
        cp[i] = b[i] - m * c[i - 1];
        dp[i] = d[i] - m * dp[i - 1];
    }

    x[n - 1] = dp[n - 1] / cp[n - 1];

    for (int i = n - 2; i >= 0; --i) {
        x[i] = (dp[i] - c[i] * x[i + 1]) / cp[i];
    }
}

int main()
{
    std::vector<NUM> F;

    f(F, 0, 2, 0.1);
    for (auto i : F)
        std::cout << i << '\n';
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

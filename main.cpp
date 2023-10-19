// Численное интегрирование тремя методами: левый прямоугольник, правый прямоугольник и трапеция.

#include <iostream>
#include <cmath>
#include <clocale>
#include <Windows.h>
#include <string>

#define pi 3.1416
#define PI 180

using namespace std;


struct rectangle
                {
                    double a, b, S;   // Стороны прямоугольника
                };

struct trapezoid
                {
                    double a, b, H, S;   // Основания трапеции и её высота
                };

double rect (double, double); // Прототип функции вычисления площади прямоугольника
double trap (double, double, double); // Прототип функции вычисления площади трапеции
bool checkInteger (string); //Прототип функции, проверяющей значение int или string


int main()
{
// Проблемы с кодировкой у Win, подключила, чтобы кириллица выводилась на консоль
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    double Xmin, Xmax; // Границы интегрирования
    double interval; // Интервал интегрирования
    double h; // Шаг интегрирования

    string Steps; // Переменная, с которой будет идти сравнение по символам
    double ForSteps; // Переменная, помогающая вычислить численное значение; после это значение приравнивается к Steps
    double h2 = 1; // "Другой кусочек" шага
    int Nsteps; // Кол-во целых шагов
    double *ArrayX;
    double *ArrayY;
    double *ArrayRect;
    double *ArrayTrap;
    int n;
    double s = 0;
    double *ArrayXcurr;
    double *ArrayYcurr;
    double *ArrayTrapcurr;



// Ввод границ интегрирования
    cout << "Введите интервал интегрирования в диапазоне [-180PI; 180PI]" << endl;
    cout << endl;
    cout << "Введите левую граничную точку Xmin = ";
    cin >> Xmin;
    cout << endl;
    cout << "Введите правую граничную точку Xmax = ";
    cin >> Xmax;
    cout << endl;

// Проверка корректности ввода граничных точек
    while (Xmin > Xmax)
                    {
                        cout << "Ошибка. Неверно заданы граничные значения. Хmin не может быть больше Хmax." << endl;
                        cout << "Необходимо перезадать значения граничных точек" << endl;
                        // Повторный ввод граничных точек
                        cout << "Введите левую граничную точку Xmin = ";
                        cin >> Xmin;
                        cout << endl;
                        cout << "Введите правую граничную точку Xmax = ";
                        cin >> Xmax;
                        cout << endl;
                    }

// Проверка ненулевого интервала
    while (Xmin == Xmax)
                    {
                        interval = abs(Xmax) - abs(Xmin);
                        cout << "Ошибка. Интервал интегрирования не может быть равен нулю. Interval = " << interval;
                        cout << endl;
                        // Повторный ввод граничных точек
                        cout << "Введите левую граничную точку Xmin = ";
                        cin >> Xmin;
                        cout << endl;
                        cout << "Введите правую граничную точку Xmax = ";
                        cin >> Xmax;
                        cout << endl;
                    }


    if (Xmin >= 0)
                    {
                        if (Xmax > 0)
                                    {
                                        interval = Xmax - Xmin;
                                    }
                    }


    if (Xmin < 0)
                    {
                        if (Xmax < 0)  interval = abs(Xmin - Xmax);

                        else  interval = Xmax + abs(Xmin);

                    }



    cout << "Интервал = " << interval;
    cout << endl;


// Ввод шага интегрирования
    cout << "Введите шаг интегрирования h = ";
    cin >> h;
    cout << endl;

// Проверка совпадения шага разбиения с интервалом интегрирования
    while (h >= interval)
                    {
                        cout << "Ошибка. Шаг интегрирования не может иметь значение равное значению величины диапазона интегрирования или" << endl;
                        cout << "иметь значение большее, чем значение величины диапазона интегрирования." << endl;
                        cout << "Необходимо повторно перезадать значение шага интегрирования h = ";
                        cin >> h;
                        cout << endl;
                    }

    cout << "Xmin = " << Xmin << " Xmax = " << Xmax << " h = " << h << endl;
    cout << endl;

// Проверка разбиения диапазона интегрирования на равные шаги (делится ли интервал на равное число шагов или есть "хвостик")

    ForSteps = interval / h;

    cout << "Help for Steps = "<< ForSteps << endl;


    cout << "Steps = ";
    cin >> Steps;

    cout << endl;

    if (checkInteger(Steps))
                    {
                        cout << "Диапазон интегрирования делится на равные шаги" << endl;

                        Nsteps = interval / h;

                        cout << "Количество целых шагов h равно  " << Nsteps << endl;
                        cout << endl;


                        // Задание массива и нахождение значение Xi в соответсвии с шагом h; Запись Xi в массив ArrayX
                        n = Nsteps + 1;
                        ArrayX = new double [n];

                        for (int i = 0; i < n; i++)
                                                    {
                                                        ArrayX[0] = Xmin;
                                                        ArrayX[i+1] = ArrayX[i] + h;
                                                        ArrayX[n-1] = Xmax;

                                                   }
                    }
    else
                    {
                        cout << "Диапазон интегрирования НЕ делится на равные шаги" << endl;

                        h2 = fmod(interval, h); //Функция fmod() в C++ вычисляет остаток числителя / знаменателя с плавающей запятой (округленный до нуля).

                        cout << "Остаточный кусочек h2 = " << h2 << endl;


                        Nsteps = interval / h;

                        cout << "Количество целых шагов h равно  " << Nsteps << endl;
                        cout << endl;


                        n = Nsteps + 2;
                        ArrayX = new double [n];

                        for (int i = 0; i < n; i++)
                                                    {
                                                        ArrayX[0] = Xmin;
                                                        ArrayX[n-1] = Xmax;
                                                        ArrayX[i+1] = ArrayX[i] + h;

                                                    }

                    }
    cout << endl;


// Вывод массива аргументов Х
    cout << "Массив аргументов представлен ниже ArrayX = {   ";

    for (int i = 0; i < n; i++)
                    {
                        cout << ArrayX[i] << "   ";
                    }
    cout << "}" << endl << endl;



// Расчёт значений функции f(x) в зависимости от массива аргументов
    ArrayY = new double [n];

    cout << "Рассчитаем значения функции F(x) для всех точек массива ArrayX: " << endl << endl;
    cout << "Массив значений ArrayY = {   ";

    for (int i = 0; i < n; i++)
                    {
                        ArrayY[i] = ArrayX[i]*sin(ArrayX[i]);     // ФУНКЦИЯ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        cout << ArrayY[i] << "  ";

                    }

    cout <<"}";
    cout << endl << endl << endl;



// Расчёт площади маленьких прямоугольников методом левых прямоугольников
    ArrayRect = new double [n];

    cout << "Значение площадей маленьких прямоугольников методом левых прямоугольников {   ";

    if (h2 == 1)
                    {
                        for (int i = 0; i < n - 1; i++)
                                                    {
                                                        ArrayRect[i] = h * ArrayY[i];
                                                        cout << ArrayRect[i] << "   ";
                                                    }

                        cout <<"}";
                        cout << endl << endl;


                    }

    else
                    {
                        for (int i = 0; i < n - 1; i++)
                                                    {

                                                        ArrayRect[i] = h * ArrayY[i];
                                                        ArrayRect[n-2] = h2 * ArrayY[n-2];
                                                        cout << ArrayRect[i] << "  ";


                                                    }

                        cout <<"}";
                        cout << endl << endl;

                    }




// Расчёт общей площади методом левых прямоугольников
    for (int i = 0; i < n - 1; i++)
                    {
                        s+= ArrayRect[i];
                    }

    cout << "Значение площади функции методом левых прямоугольников Sлев = " << s;
    cout << endl << endl << endl;




//    delete[] ArrayRect;

//    ArrayRect = new double [n];

    s = 0; // Обнуление площади предыдущей !!!!!!!!!!!!!!!!!!




// Расчёт площади маленьких прямоугольников методом правых прямоугольников
    cout << "Значение площадей маленьких прямоугольников методом правых прямоугольников {  ";

    if (h2 == 1)
                    {
                        for (int i = 1; i < n; i++)
                                                    {
                                                        ArrayRect[i] = h * ArrayY[i];
                                                        cout << ArrayRect[i] << "  ";
                                                    }

                        cout <<"}";
                        cout << endl << endl;

                    }

    else
                    {
                        for (int i = 1; i < n; i++)
                                                    {

                                                        ArrayRect[i] = h * ArrayY[i];
                                                        ArrayRect[n-1] = h2 * ArrayY[n-1];
                                                        cout << ArrayRect[i] << "  ";

                                                    }

                        cout <<"}";
                        cout << endl << endl;

                    }



// Расчёт общей площади методом правых прямоугольников
    for (int i = 1; i < n; i++)
                    {
                        s+= ArrayRect[i];
                    }

    cout << "Значение площади функции методом правых прямоугольников Sпр = " << s;
    cout << endl << endl;



    s = 0; // Обнуление площади предыдущей !!!!!!!!!!!!!!!!!!


// Расчёт площади методом трапеции
    ArrayTrap = new double [n];
    cout << "Значение площадей маленьких трапеций методом трапеций {  ";

    if (h2 == 1)
                    {
                        for (int i = 0; i < n - 1; i++)
                                                    {
                                                        ArrayTrap[i] = 0.5*h*(ArrayY[i] + ArrayY[i+1]);
                                                        cout << ArrayTrap[i] << "  ";
                                                    }
                        cout <<"}";
                        cout << endl << endl;

                    }

    else
                    {
                        for (int i = 0; i < n - 1; i++)
                                                    {
                                                        ArrayTrap[i] = 0.5*h*(ArrayY[i] + ArrayY[i+1]);
                                                        ArrayTrap[n-2] = 0.5*h2*(ArrayY[n-2] + ArrayY[n-1]);
                                                        cout << ArrayTrap[i] << "  ";
                                                    }

                        cout <<"}";
                        cout << endl << endl;

                    }




    // Расчёт общей площади методом трапеции
    for (int i = 0; i < n - 1; i++)
                    {
                        s+= ArrayTrap[i];
                    }

    cout << "Значение площади функции методом трапеции Sтрап = " << s;
    cout << endl << endl;






    // Расчёт интеграла с точностью

    int N;
    double eps;
    double Scurr = 0;
    cout << "Введине значение количества шагов N = ";
    cin >> N;

    h = interval / N;



    ArrayXcurr = new double [N];
    ArrayYcurr = new double [N];
    ArrayTrapcurr = new double [N];

    for (int i = 0; i < N + 1; i++)
                    {
                        ArrayXcurr[0] = Xmin;
                        ArrayXcurr[i+1] = ArrayXcurr[i] + h;
                        ArrayXcurr[N + 1] = Xmax;
                    }


//    cout << "Массив аргументов представлен ниже ArrayXcurr = {   ";

//    for (int i = 0; i < N + 1; i++)
//                    {
//                        cout << ArrayXcurr[i] << "   ";
//                    }
//    cout << "}" << endl << endl;




    for (int i = 0; i < N + 1; i++)
                    {
                        ArrayYcurr[i] = ArrayXcurr[i]*sin(ArrayXcurr[i]);
                    }

//    cout << "Массив значений представлен ниже ArrayYcurr = {   ";

//    for (int i = 0; i < N + 1; i++)
//                    {
//                        cout << ArrayYcurr[i] << "   ";
//                    }
//    cout << "}" << endl << endl;




    for (int i = 0; i < N; i++)
                    {
                        ArrayTrapcurr[i] = 0.5*h*(ArrayYcurr[i] + ArrayYcurr[i+1]);
//                        cout << ArrayTrap[i] << "  ";
                    }
    cout << endl << endl;


    for (int i = 0; i < N; i++)
                    {
                        Scurr+= ArrayTrapcurr[i];
                    }

    cout << "Значение площади функции методом трапеции текущей Sтрап текущ = " << Scurr;
    cout << endl << endl;




    if (abs(s - Scurr) > 0 && abs(s - Scurr) < 1)
                    {
                        eps = abs(s - Scurr);
                        cout << "Точность выполняется, eps = " << eps << endl;
                    }
//    else if  (abs(s - Scurr) < 1)
//                    {
//                        eps = abs(s - Scurr);
//                        cout << "Точность выполняется, eps = " << eps << endl;
//                    }
    else
                    {
                        eps = abs(s - Scurr);
                        cout << "Ошибка точности, eps = " << eps << endl;
                    }

//    while (abs(s - Scurr) > 1 && abs(s - Scurr) < 0)
//                    {
//                        eps = abs(s - Scurr);
//                        cout << "Точность не выполняется, eps = " << eps << endl;
//                        cout << "Введите количество шагов интегрирования N = ";
//                        cin >> N;
//                    }

    delete [] ArrayX;
    ArrayX = nullptr;

    delete [] ArrayY;
    ArrayY = nullptr;

    delete [] ArrayRect;
    ArrayRect = nullptr;

    delete [] ArrayTrap;
    ArrayTrap = nullptr;

    delete [] ArrayXcurr;
    ArrayXcurr = nullptr;

    delete [] ArrayYcurr;
    ArrayYcurr = nullptr;

    delete [] ArrayTrapcurr;
    ArrayTrapcurr = nullptr;


    return 0;
}










// Функция вычисления площади прямоугольника
double rect (double a, double b)
                                {
                                    double S;

                                    S = a * b;

                                    return S;
                                }

// Функция вычисления площади трапеции
double trap (double a, double b, double H)
                                {
                                    double S;

                                    S = (a * b) * H / 2;

                                    return S;
                                }

// Функция проверки целое число или нет
bool checkInteger (string A)
                                {
                                    for (int i = 0; i < A.size(); i++)
                                                                    {
                                                                        if (!(A[i]=='0' || A[i]=='1' || A[i]=='2' || A[i]=='3' || A[i]=='4' || A[i]=='5' || A[i]=='6' || A[i]=='7' || A[i]=='8' || A[i]=='9'))
                                                                            return false;
                                                                    }
                                    return true;
                                }

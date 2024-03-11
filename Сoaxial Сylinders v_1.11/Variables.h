#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

extern double Pi;

extern double R0;
extern double R1;

/* Количество элементов */
extern int max_str, max_node, max_el;

/* Число Рейнольдса */
extern double Re;

/* Счетчик итераций */
extern int Iter_Glob;

/* Граничные условия */
extern double omega_0;
extern double omega_1;

/* Номер элемента для отслеживания */
extern int num_el_1, num_el_2, num_el_3;
extern int num_el_1_MUSCL;

/* Координаты контрольного элемента */
extern double xx_1, yy_1;

/* Параметр установления */
extern double E_U;
extern int E_U_Num_el;
extern int alfa_k;

/* Максимальная поправка давления */
extern double maxP_Corr;
extern int maxP_Cor_num_el;
extern double maxdivU;
extern int maxdivU_num_el;

/* Параметры для оптимизированной маркерной визуализации */
struct Marker
{
    /* Координаты маркера */
    double coord[2];

    /* Псоледний КО, в котором находтлся маркер */
    int CV_marker;
};
extern double dt_m;
extern double exp_moving_old;

extern Marker marker;
extern vector<Marker> vectorMarker;

/* Директория файла с сеткой и Save */
extern string File_Mesh_Name;
extern ifstream File_Mesh;

extern bool Read_From_Save;
extern string File_Save_Name;

extern bool Start_Flow_Evolution;

/* Расчет при переменной скорости*/
extern bool Variable_Speed;

/* Шаг и счетчик времени */
extern double dt;
extern double _time;
extern double _time_Flow_Evolution;
extern double final_time;

/* Структура точек и структура элементов*/
struct Point
{

    /* Индивидуальный номер узла */
    int Num_node;

    /*Принадлежность границе*/
    bool Boundary;

    /* Координаты узла */
    double x, y;

    /* КО, которые содержат точку */
    vector<int> Neighb_el;

};
struct Element
{
    /*Индивидуальный номер элемента */
    int Num_el;

    /* Тип элемента */
    int Geom_el;

    /* Тег границы */
    int Num_bound;

    /* Номера вершин элемента */
    int Num_vert[3];

    /* Координаты вершин элемента */
    Point Coord_vert[3];

    /* Длина грани элемента */
    double Length_face_el[3];

    /* Площадь элемента */
    double Area_el;

    /* Координаты центра элемента */
    Point Coord_center_el;

    /* Расстояние от центра до грани элемента */
    double h[3];

    /* Соседний элемент */
    int Neighb_el[3];

    /* Составляющие нормали */
    double Normal[3][2];

    /* Значение градиента U_x, U_y, P */
    double gradU_x[2], gradU_y[2], gradP[2], gradP_Corr[2];

    /* Значение температуры в КО на предыдущем шаге */
    double t;

    /* Значение температуры в КО на текущем шаге */
    double T;

    /* Значение ст. отверждения в КО на предыдущем шаге */
    double alfa;

    /* Значение ст. отверждения в КО на текущем шаге */
    double Alfa;

    /* Значение произв. от Alfa */
    double dalfa;

    /* Значение скорости на предыдущем шаге */
    double u_x, u_y;

    /* Значение скорости на текущем шаге */
    double U_x, U_y;

    /* Значение давления на текущем шаге */
    double P;

    /* Коэффициенты А для поправки давления */
    double A_0;

    /* Поправка давления */
    double P_Correction;

    /* Поправка скорости */
    double U_x_Correction;
    double U_y_Correction;

    /* Функция тока */
    double Psi;

    /* Диссипативная функция */
    double Q;

};

// FIXME: Зашить нумерацию границ в файл сетки, чтобы не следить
// за их правильностью в коде
// Нумерация элепментов границ
struct Border {
    // Расчетная область
    int calc;
    // Первый элемент внутренней стенки
    int in_1;

    // Первый элемент внутренней стенки (1 дуга внешней стенки)
    int out_1;
    // Второй элемент внутренней стенки (2 дуга внешней стенки)
    int out_2;

    /* Нумерация границ для разных конфигураций */
    /*
    Conf_0: out_1 = 1
    Conf_0: out_2 = 1
    Conf_0:  in_1 = 2

    Conf_1: out_1 = 6
    Conf_2: out_1 = 9
    Conf_3: out_1 = 17
    Conf_4: out_1 = 10
    Conf_5: out_1 = 18
    */
};

extern Border border;

extern vector<Point> vectorPoint;
extern vector<Element> vectorElement;

extern ofstream Test_n;
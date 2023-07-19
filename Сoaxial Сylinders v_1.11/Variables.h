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

/* Максимальная поправка давления */
extern double maxP_Corr;
extern int maxP_Cor_num_el;
extern double maxdivU;
extern int maxdivU_num_el;

/* Параметры маркерной визуализации */
extern int count_marker;
extern int count_angle;
extern vector<double> x_m, y_m;
extern vector<vector<double>>x_ang;
extern vector<vector<double>>y_ang;
extern double dt_m;

/* Директория файла с сеткой и Save */
extern string File_Mesh_Name;
extern ifstream File_Mesh;

extern bool Read_From_Save;
extern string File_Save_Name;

extern bool Start_Flow_Evolution;

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

};

enum Calculation_Area {
    calc
};
enum Inner_Wall {
    in_1 = 1, in_2, in_3, in_4,
    in_5, in_6, in_7, in_8
};
enum Outer_Wall {
    out_1 = 6, out_2

    /* Conf_1: out_1 = 6 */
    /* Conf_2: out_1 = 9 */
    /* Conf_2: out_1 = 17 */
};

extern vector<Point> vectorPoint;
extern vector<Element> vectorElement;

extern ofstream Test_n;
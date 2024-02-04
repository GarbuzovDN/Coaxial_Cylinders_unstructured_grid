#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <windows.h>
#include <map>

using namespace std;

double Pi = 3.14159;

double R0 = 0.2;
double R1 = 1.0;

/* Количество элементов */
int max_str, max_node, max_el;

/* Число Рейнольдса */
double Re = 90;

/* Счетчик итераций */
int Iter_Glob;

/* Граничные условия */
double omega_0 = 0.0;
double omega_1 = 1.0;

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

    /* Значение градиента U_x, U_y, P, P_Corr */
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

//Здесь можно не задавать сами значения
enum Calculation_Area {
    calc
};
enum Inner_Wall {
    in_1, in_2, in_3, in_4,
    in_5, in_6, in_7, in_8
};
enum Outer_Wall {
    out_1, out_2

    //Здесь можно не задавать сами значения

    /* Conf_0: out_1 = 1
       Conf_0: out_2 = 1 
       Conf_0:  in_1 = 2 */

    /* Conf_1: out_1 = 6 */
    /* Conf_2: out_1 = 9 */
    /* Conf_3: out_1 = 17 */
    /* Conf_4: out_1 = 10 */
    /* Conf_5: out_1 = 18 */
};

/* Вектор точек и вектор элементов */
vector<Point> vectorPoint;
vector<Element> vectorElement;

/* Номер элемента для отслеживания */
int num_el_1, num_el_2, num_el_3;
int num_el_1_MUSCL;

/* Координаты контрольного элемента */
double xx_1 = 0.0, yy_1 = 0.25;

/* Параметр установления */
double E_U;
int E_U_Num_el;

/* Коэффициент учета силы Кориолиса */
int alfa_k = 0.0;

/* Максимальная поправка давления */
double maxP_Corr = 0.0;
int maxP_Cor_num_el = 0;
double maxdivU = 0.0;
int maxdivU_num_el = 0;

/* Параметр для маркерной визуализации */
int count_marker = 0;
int count_angle = 0;
vector<double> x_m, y_m;
vector<vector<double>>x_ang;
vector<vector<double>>y_ang;
double dt_m = 0.001;
map<int, int> num_el_for_marker;

/* Параметры для оптимизированной маркерной визуализации */
struct Marker 
{
    /* Координаты маркера */
    double coord[2];

    /* Псоледний КО, в котором находтлся маркер */
    vector<int> CV_marker;
};

Marker marker;
vector<Marker> vectorMarker;

/* Директория файла с сеткой */
string File_Mesh_Name =
"Documents/Mesh/Approx/Mesh_Coaxial_Cylinders_WO_5_(El=5742).msh";
//"Documents/Mesh/Mesh_Coaxial_Cylinders_WO_(El=6922).msh";
ifstream File_Mesh(File_Mesh_Name);

/* Директория файла с Save */
bool Read_From_Save = false;
string File_Save_Name =
"Documents/Save/Re=1.000000/El = 27514/Save_(El=27514)_Steady.DAT";

bool Start_Flow_Evolution = false;

/* Шаг и счетчик времени */
double dt = 0.001;
double _time = 0.0;
double _time_Flow_Evolution = 0.0;

double final_time = 50;
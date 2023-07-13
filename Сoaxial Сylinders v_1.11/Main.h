#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

double Pi = 3.14159;

double R0 = 0.2;
double R1 = 1.0;

/* ���������� ��������� */
int max_str, max_node, max_el;

/* ����� ���������� */
double Re = 0.1;

/* ������� �������� */
int Iter_Glob;

/* ��������� ������� */
double omega_0 = 0.0;
double omega_1 = 1.0;

/* ��������� ����� � ��������� ���������*/
struct Point
{

    /* �������������� ����� ���� */
    int Num_node;

    /*�������������� �������*/
    bool Boundary;

    /* ���������� ���� */
    double x, y;

    /* ��, ������� �������� ����� */
    vector<int> Neighb_el;

};
struct Element
{
    /*�������������� ����� �������� */
    int Num_el;

    /* ��� �������� */
    int Geom_el;

    /* ��� ������� */
    int Num_bound;

    /* ������ ������ �������� */
    int Num_vert[3];

    /* ���������� ������ �������� */
    Point Coord_vert[3];

    /* ����� ����� �������� */
    double Length_face_el[3];

    /* ������� �������� */
    double Area_el;

    /* ���������� ������ �������� */
    Point Coord_center_el;

    /* ���������� �� ������ �� ����� �������� */
    double h[3];

    /* �������� ������� */
    int Neighb_el[3];

    /* ������������ ������� */
    double Normal[3][2];

    /* �������� ��������� U_x, U_y, P, P_Corr */
    double gradU_x[2], gradU_y[2], gradP[2], gradP_Corr[2];

    /* �������� ����������� � �� �� ���������� ���� */
    double t;

    /* �������� ����������� � �� �� ������� ���� */
    double T;

    /* �������� ��. ����������� � �� �� ���������� ���� */
    double alfa;

    /* �������� ��. ����������� � �� �� ������� ���� */
    double Alfa;

    /* �������� ������. �� Alfa */
    double dalfa;

    /* �������� �������� �� ���������� ���� */
    double u_x, u_y;

    /* �������� �������� �� ������� ���� */
    double U_x, U_y;

    /* �������� �������� �� ������� ���� */
    double P;

    /* ������������ � ��� �������� �������� */
    double A_0;

    /* �������� �������� */
    double P_Correction;

    /* �������� �������� */
    double U_x_Correction;
    double U_y_Correction;

    /* ������� ���� */
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
    out_1 = 17, out_2

    /* Conf_1: out_1 = 6 */
    /* Conf_2: out_1 = 9 */
    /* Conf_2: out_1 = 17 */
};

/* ������ ����� � ������ ��������� */
vector<Point> vectorPoint;
vector<Element> vectorElement;

/* ����� �������� ��� ������������ */
int num_el_1, num_el_2, num_el_3;
int num_el_1_MUSCL;

/* ���������� ������������ �������� */
double xx_1 = 0.6, yy_1 = 0.6;

/* �������� ������������ */
double E_U;
int E_U_Num_el;

/* ������������ �������� �������� */
double maxP_Corr = 0.0;
int maxP_Cor_num_el = 0;
double maxdivU = 0.0;
int maxdivU_num_el = 0;

/* �������� ��� ��������� ������������ */
int count_marker = 0;
int count_angle = 0;
vector<double> x_m, y_m;
vector<vector<double>>x_ang;
vector<vector<double>>y_ang;
double dt_m = 0.001;

/* ���������� ����� � ������ � Save */
string File_Mesh_Name =
"Documents/Mesh/Mesh_Coaxial_Cylinders_WO_3.1_(El=6943).msh";
ifstream File_Mesh(File_Mesh_Name);

bool Read_From_Save = false;
string File_Save_Name =
"Documents/Save/Re=90.000000/El = 6943/Save_(El=6943)_Steady.DAT";

bool Start_Flow_Evolution = true;

/* ��� � ������� ������� */
double dt = 0.001;
double _time = 0.0;
double _time_Flow_Evolution = 0.0;

double final_time = 13.0;
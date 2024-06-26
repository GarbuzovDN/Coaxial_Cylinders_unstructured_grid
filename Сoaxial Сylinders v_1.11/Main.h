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

double R0 = 0.06;
double R1 = 1.0;

/* ���������� ��������� */
int max_str, max_node, max_el;

/* ����� ���������� */
double Re = 1.0;

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

    /* ������������� ������� */
    double Q;

};

// ��������� ���������� ������
struct Border {
    // �� ��������� ��������� �������� -1, 
    // ����� ����� ����������� ������ ���������� ��������� 
    
    // ��������� �������
    int calc = -1;
    // ������ ������� ���������� ������
    int in_1 = -1;

    // ������ ������� ���������� ������ (1 ���� ������� ������)
    int out_1 = -1;
    // ������ ������� ���������� ������ (2 ���� ������� ������)
    int out_2 = -1;

    /* ��������� ������ ��� ������ ������������ */
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
Border border;

/* ������ ����� � ������ ��������� */
vector<Point> vectorPoint;
vector<Element> vectorElement;

/* ����� �������� ��� ������������ */
int num_el_1, num_el_2, num_el_3;
int num_el_1_MUSCL;

/* ���������� ������������ �������� */
double xx_1 = 0.0, yy_1 = 0.25;

/* �������� ������������ */
double E_U;
int E_U_Num_el;

/* ����������� ����� ���� ��������� */
int alfa_k = 0.0;

/* ������������ �������� �������� */
double maxP_Corr = 0.0;
int maxP_Cor_num_el = 0;
double maxdivU = 0.0;
int maxdivU_num_el = 0;

/* ��������� ��� ���������������� ��������� ������������ */
struct Marker 
{
    /* ���������� ������� */
    double coord[2];

    /* ��������� ��, � ������� ��������� ������ */
    int CV_marker;
};
double dt_m = 0.001;
double exp_moving_old = 1.0;


Marker marker;
vector<Marker> vectorMarker;

/* ���������� ����� � ������ */
string File_Mesh_Name =
//"Documents/Mesh/Approx/Mesh_Coaxial_Cylinders_WO_1_(El=3531).msh";
//"Documents/Mesh/Mesh_Coaxial_Cylinders_WO_5_(El=5742).msh"; 
"Documents/Mesh/Mesh_Coaxial_Cylinders_WO_4_0.7_Komoda(El=11069).msh";
ifstream File_Mesh(File_Mesh_Name);

/* ���������� ����� � Save */
bool Read_From_Save = false;
string File_Save_Name =
"Documents/Figure/Re=1.000000/El = 7195/Save/Save_(El=7195)_1.DAT";

/* ������ ������������� ��������� ������ ��� ���������� ��������*/
bool Start_Flow_Evolution = false;

/* ������ ��� ���������� ��������*/
bool Variable_Speed = true;

/* ��� � ������� ������� */
double dt = 0.0001;
double _time = 0.0;
double _time_Flow_Evolution = 0.0;

double final_time = 250;
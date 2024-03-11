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

/* ���������� ��������� */
extern int max_str, max_node, max_el;

/* ����� ���������� */
extern double Re;

/* ������� �������� */
extern int Iter_Glob;

/* ��������� ������� */
extern double omega_0;
extern double omega_1;

/* ����� �������� ��� ������������ */
extern int num_el_1, num_el_2, num_el_3;
extern int num_el_1_MUSCL;

/* ���������� ������������ �������� */
extern double xx_1, yy_1;

/* �������� ������������ */
extern double E_U;
extern int E_U_Num_el;
extern int alfa_k;

/* ������������ �������� �������� */
extern double maxP_Corr;
extern int maxP_Cor_num_el;
extern double maxdivU;
extern int maxdivU_num_el;

/* ��������� ��� ���������������� ��������� ������������ */
struct Marker
{
    /* ���������� ������� */
    double coord[2];

    /* ��������� ��, � ������� ��������� ������ */
    int CV_marker;
};
extern double dt_m;
extern double exp_moving_old;

extern Marker marker;
extern vector<Marker> vectorMarker;

/* ���������� ����� � ������ � Save */
extern string File_Mesh_Name;
extern ifstream File_Mesh;

extern bool Read_From_Save;
extern string File_Save_Name;

extern bool Start_Flow_Evolution;

/* ������ ��� ���������� ��������*/
extern bool Variable_Speed;

/* ��� � ������� ������� */
extern double dt;
extern double _time;
extern double _time_Flow_Evolution;
extern double final_time;

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

    /* �������� ��������� U_x, U_y, P */
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

// FIXME: ������ ��������� ������ � ���� �����, ����� �� �������
// �� �� ������������� � ����
// ��������� ���������� ������
struct Border {
    // ��������� �������
    int calc;
    // ������ ������� ���������� ������
    int in_1;

    // ������ ������� ���������� ������ (1 ���� ������� ������)
    int out_1;
    // ������ ������� ���������� ������ (2 ���� ������� ������)
    int out_2;

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

extern Border border;

extern vector<Point> vectorPoint;
extern vector<Element> vectorElement;

extern ofstream Test_n;
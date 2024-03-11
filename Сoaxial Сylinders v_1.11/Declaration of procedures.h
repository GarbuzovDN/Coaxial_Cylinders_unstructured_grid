#pragma once

void Create_WriteDir();

void Find_String(string Str);

void Mesh_Init();

void Blank();

void Blank_new(double t);

void Redistricting();

void Initial_Conditions();

void Calculation_Velocity_U();

void Calculation_Pressure_P();

void Development();

void Stream_Function();

void Dissipative_Function();

void Approximation_Accuracy(bool activate);

void Redistricting1();

double beta(int ii, int jj);

double divU(int ii);

double Section_value_MUSCL(double xx, double yy, string param);

double Section_value_MUSCL_Face(double xx, double yy, string param, int num_i);

void Write();

void Write_End();

void Time();

double Firsov_M(int ii, string param);

void Flow_Evolution_new(string param);
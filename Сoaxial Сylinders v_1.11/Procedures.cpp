#include "Variables.h"
#include "Declaration of procedures.h"

void Create_WriteDir()
{

    string _path = "Documents";
    CreateDirectoryA(_path.c_str(), NULL);

    _path = "Documents/Blank";
    CreateDirectoryA(_path.c_str(), NULL);
    _path = "Documents/Figure";
    CreateDirectoryA(_path.c_str(), NULL);
    _path = "Documents/Figure/Re=" + to_string(Re);
    CreateDirectoryA(_path.c_str(), NULL);
    _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el);
    CreateDirectoryA(_path.c_str(), NULL);
    _path = "Documents/Save";
    CreateDirectoryA(_path.c_str(), NULL);
    _path = "Documents/Save/Re=" + to_string(Re);
    CreateDirectoryA(_path.c_str(), NULL);
}

void Find_String(string Str)
{

    if (!File_Mesh)
    {
        cout << "ERROR opening the file MESH: " << File_Mesh_Name << endl << endl << endl;

        exit(1);
    }
    else
    {
        if (max_str != 0) cout << "File opened SUCCESSFULLY: " << File_Mesh_Name << endl;
        if (max_str != 0)
        {

            cout << fixed << setprecision(4) << "Time: " << _time << endl << "Mesh (Number of nodes): " << max_node << endl;

        }

    }

    int num_str;

    string line;

    num_str = 0;

    while (line != Str)
    {

        getline(File_Mesh, line);

        num_str++;

        int pp = 0;

    }

    File_Mesh >> max_str;

}

void Save_Read()
{

    ifstream File_Read_Save(File_Save_Name);

    if (!File_Read_Save)
    {
        cout << "ERROR opening the file SAVE: " << File_Save_Name << endl << endl << endl;

        exit(1);
    }
    else
    {
        File_Read_Save >> _time >> max_el >> max_node >> max_str;
        File_Read_Save >> Re >> num_el_1 >> num_el_2 >> num_el_3;
        File_Read_Save >> num_el_1_MUSCL >> xx_1 >> yy_1 >> E_U >> E_U_Num_el;
        File_Read_Save >> maxP_Corr >> maxP_Cor_num_el >> maxdivU >> maxdivU_num_el >> dt;

        Point node;

        /* ���������� ��������� ����� */
        for (int i = 1; i <= max_node; i++)
        {

            File_Read_Save >> node.Num_node >> node.Boundary >> node.x >> node.y;

            vectorPoint.push_back(node);

        }

        Element el;

        /* ������ ���������� ��������� */
        for (int i = 0; i <= max_el; i++)
        {
            File_Read_Save >> el.Num_el >> el.Geom_el >> el.Num_bound >> el.Num_vert[0] >> el.Num_vert[1] >> el.Num_vert[2];

            if (el.Geom_el == 15)
            {
                File_Read_Save >> el.U_x >> el.U_y >> el.P >> el.u_x >> el.u_y;
                File_Read_Save >> el.Coord_vert[0].x >> el.Coord_vert[0].y >> el.Coord_vert[1].x >> el.Coord_vert[1].y >> el.Coord_vert[2].x >> el.Coord_vert[2].y;
            }

            if (el.Geom_el == 1)
            {
                File_Read_Save >> el.U_x >> el.U_y >> el.P >> el.u_x >> el.u_y;
                File_Read_Save >> el.Coord_vert[0].x >> el.Coord_vert[0].y >> el.Coord_vert[1].x >> el.Coord_vert[1].y >> el.Coord_vert[2].x >> el.Coord_vert[2].y;
            }

            if (el.Geom_el == 2)
            {
                File_Read_Save >> el.U_x >> el.U_y >> el.P >> el.u_x >> el.u_y;
                File_Read_Save >> el.Coord_vert[0].x >> el.Coord_vert[0].y >> el.Coord_vert[1].x >> el.Coord_vert[1].y >> el.Coord_vert[2].x >> el.Coord_vert[2].y;
                File_Read_Save >> el.Length_face_el[0] >> el.Length_face_el[1] >> el.Length_face_el[2] >> el.Area_el;
                File_Read_Save >> el.Coord_center_el.x >> el.Coord_center_el.y >> el.h[0] >> el.h[1] >> el.h[2];
                File_Read_Save >> el.Neighb_el[0] >> el.Neighb_el[1] >> el.Neighb_el[2] >> el.Normal[0][0] >> el.Normal[1][0] >> el.Normal[2][0];
                File_Read_Save >> el.Normal[0][1] >> el.Normal[1][1] >> el.Normal[2][1] >> el.gradU_x[0] >> el.gradU_x[1] >> el.gradU_y[0] >> el.gradU_y[1];
                File_Read_Save >> el.gradP[0] >> el.gradP[1] >> el.gradP_Corr[0] >> el.gradP_Corr[1] >> el.t >> el.T;
                File_Read_Save >> el.alfa >> el.Alfa >> el.dalfa >> el.u_x >> el.u_y >> el.U_x >> el.U_y;
                File_Read_Save >> el.P_Correction >> el.A_0 >> el.U_x_Correction >> el.U_y_Correction >> el.Psi;
            }

            vectorElement.push_back(el);

        }

        File_Read_Save >> File_Mesh_Name;

        vectorElement.pop_back();
        cout << "File opened SUCCESSFULLY: " << File_Save_Name << endl;
        cout << fixed << setprecision(4) << "Time: " << _time << endl << "Mesh (Number of nodes): " << max_el << endl;

    }

}

void Mesh_Init()
{

    vectorPoint.clear();
    vectorElement.clear();

    if (Read_From_Save == false && Start_Flow_Evolution == false)
    {

        Find_String("$Nodes");

        max_node = max_str;

        vectorPoint.reserve(max_node);

        Point node;

        /* ���������� ��������� ����� */
        for (int i = 1; i <= max_node; i++)
        {

            double temp;
            int temp_int;

            File_Mesh >> temp_int >> node.x >> node.y >> temp;

            node.Num_node = temp_int - 1;

            node.Boundary = false;

            vectorPoint.push_back(node);

            i = i;

        }

        Find_String("$Elements");

        max_el = max_str;

        vectorElement.reserve(max_el);

        /* ���������� ��������� ��������� */
        for (int i = 1; i <= max_el; i++)
        {
            Element el;
            double temp;
            int temp_int;

            File_Mesh >> temp_int >> el.Geom_el;

            el.Num_el = temp_int - 1;

            if (el.Geom_el == 15)
            {
                int temp_int_1;

                File_Mesh >> temp >> temp >> temp >> temp_int_1;
                el.Num_vert[0] = temp_int_1 - 1;
                el.Coord_vert[0] = vectorPoint[el.Num_vert[0]];
                vectorPoint[el.Num_vert[0]].Boundary = true;

            }
            if (el.Geom_el == 1)
            {

                int temp_int_1, temp_int_2;

                File_Mesh >> temp >> temp >> el.Num_bound >> temp_int_1 >> temp_int_2;
                el.Num_vert[0] = temp_int_1 - 1;
                el.Num_vert[1] = temp_int_2 - 1;

                el.Coord_vert[0] = vectorPoint[el.Num_vert[0]];
                el.Coord_vert[1] = vectorPoint[el.Num_vert[1]];
                vectorPoint[el.Num_vert[0]].Boundary = true;
                vectorPoint[el.Num_vert[1]].Boundary = true;

                i = i;

            }
            if (el.Geom_el == 2)
            {

                int temp_int_1, temp_int_2, temp_int_3;

                File_Mesh >> temp >> temp >> temp >> temp_int_1 >> temp_int_2 >> temp_int_3;
                el.Num_vert[0] = temp_int_1 - 1;
                el.Num_vert[1] = temp_int_2 - 1;
                el.Num_vert[2] = temp_int_3 - 1;

                el.Coord_vert[0] = vectorPoint[el.Num_vert[0]];
                el.Coord_vert[1] = vectorPoint[el.Num_vert[1]];
                el.Coord_vert[2] = vectorPoint[el.Num_vert[2]];

                el.Num_bound = calc;

                /* ���� ���������� ������� � ������ �������� */
                {

                    /* ������� � ������ ����� */
                    {

                        double a_1 = (el.Coord_vert[1].y - el.Coord_vert[0].y);
                        if (a_1 == 0) a_1 = 1e-8;
                        double a_2 = (el.Coord_vert[1].x - el.Coord_vert[0].x);
                        if (a_2 == 0) a_2 = 1e-8;
                        double a = a_1 / a_2;
                        double ny_p = 1 / pow(a * a + 1, 0.5);
                        double ny_m = -1 / pow(a * a + 1, 0.5);
                        double nx_p = -a * ny_p;
                        double nx_m = -a * ny_m;

                        double n_check_p = (el.Coord_vert[1].x - el.Coord_vert[0].x) * ny_p - (el.Coord_vert[1].y - el.Coord_vert[0].y) * nx_p;
                        double n_check_m = (el.Coord_vert[1].x - el.Coord_vert[0].x) * ny_m - (el.Coord_vert[1].y - el.Coord_vert[0].y) * nx_m;

                        if (n_check_p < 0)
                        {

                            el.Normal[0][0] = -a * ny_p;
                            el.Normal[0][1] = ny_p;

                            i = i;

                        }
                        else if (n_check_m < 0)
                        {

                            el.Normal[0][0] = -a * ny_m;
                            el.Normal[0][1] = ny_m;

                            i = i;

                        }
                        else
                        {

                            cout << "Normal calculation ERROR (face 1)" << endl;
                            cout << el.Num_el + 1 << "\t" << el.Normal[0][0] << "\t" << el.Normal[0][1] << endl;
                            //system("pause");

                        }

                    }

                    /* ������� �� ������ ����� */
                    {

                        double a_1 = (el.Coord_vert[2].y - el.Coord_vert[1].y);
                        if (a_1 == 0) a_1 = 1e-8;
                        double a_2 = (el.Coord_vert[2].x - el.Coord_vert[1].x);
                        if (a_2 == 0) a_2 = 1e-8;
                        double a = a_1 / a_2;
                        double ny_p = 1 / pow(a * a + 1, 0.5);
                        double ny_m = -1 / pow(a * a + 1, 0.5);
                        double nx_p = -a * ny_p;
                        double nx_m = -a * ny_m;

                        double n_check_p = (el.Coord_vert[2].x - el.Coord_vert[1].x) * ny_p - (el.Coord_vert[2].y - el.Coord_vert[1].y) * nx_p;
                        double n_check_m = (el.Coord_vert[2].x - el.Coord_vert[1].x) * ny_m - (el.Coord_vert[2].y - el.Coord_vert[1].y) * nx_m;

                        if (n_check_p < 0)
                        {

                            el.Normal[1][0] = -a * ny_p;
                            el.Normal[1][1] = ny_p;

                            i = i;

                        }
                        else if (n_check_m < 0)
                        {

                            el.Normal[1][0] = -a * ny_m;
                            el.Normal[1][1] = ny_m;

                            i = i;

                        }
                        else
                        {

                            cout << "Normal calculation ERROR (face 2)" << endl;
                            cout << el.Num_el + 1 << "\t" << el.Normal[1][0] << "\t" << el.Normal[1][1] << endl;
                            //system("pause");

                        }

                    }

                    /* ������� � ������� ����� */
                    {
                        if (i == 1422)
                        {
                            i = i;
                        }

                        double a_1 = (el.Coord_vert[0].y - el.Coord_vert[2].y);
                        if (a_1 == 0) a_1 = 1e-8;
                        double a_2 = (el.Coord_vert[0].x - el.Coord_vert[2].x);
                        if (a_2 == 0) a_2 = 1e-8;
                        double a = a_1 / a_2;
                        double ny_p = 1 / pow(a * a + 1, 0.5);
                        double ny_m = -1 / pow(a * a + 1, 0.5);
                        double nx_p = -a * ny_p;
                        double nx_m = -a * ny_m;

                        double n_check_p = (el.Coord_vert[0].x - el.Coord_vert[2].x) * ny_p - (el.Coord_vert[0].y - el.Coord_vert[2].y) * nx_p;
                        double n_check_m = (el.Coord_vert[0].x - el.Coord_vert[2].x) * ny_m - (el.Coord_vert[0].y - el.Coord_vert[2].y) * nx_m;

                        if (n_check_p < 0)
                        {

                            el.Normal[2][0] = -a * ny_p;
                            el.Normal[2][1] = ny_p;

                            i = i;

                        }
                        else if (n_check_m < 0)
                        {

                            el.Normal[2][0] = -a * ny_m;
                            el.Normal[2][1] = ny_m;

                            i = i;

                        }
                        else if (a_2 == 0)
                        {

                            cout << "Normal calculation ERROR (face 3)" << endl;
                            cout << el.Num_el + 1 << "\t" << el.Normal[2][0] << "\t" << el.Normal[2][1] << endl;
                            //system("pause");

                        }

                    }

                }

            }


            el.Length_face_el[0] = sqrt(pow((el.Coord_vert[1].x - el.Coord_vert[0].x), 2) + pow((el.Coord_vert[1].y - el.Coord_vert[0].y), 2));
            el.Length_face_el[1] = sqrt(pow((el.Coord_vert[2].x - el.Coord_vert[1].x), 2) + pow((el.Coord_vert[2].y - el.Coord_vert[1].y), 2));
            el.Length_face_el[2] = sqrt(pow((el.Coord_vert[0].x - el.Coord_vert[2].x), 2) + pow((el.Coord_vert[0].y - el.Coord_vert[2].y), 2));

            if (i == 43)
                i = i;

            double a = el.Length_face_el[0];
            double b = el.Length_face_el[1];
            double c = el.Length_face_el[2];
            double p = 0.5 * (a + b + c);
            el.Area_el = sqrt(p * (p - a) * (p - b) * (p - c));

            if (i == 71)
                i = i;

            /* ���� ���������� ������ �������� */
            {

                /* ��������� ����������� �������������� 1 */
                double AB = el.Length_face_el[0], BC = el.Length_face_el[1], AC = el.Length_face_el[2];
                double x_a = el.Coord_vert[0].x, x_b = el.Coord_vert[1].x, x_c = el.Coord_vert[2].x;
                double y_a = el.Coord_vert[0].y, y_b = el.Coord_vert[1].y, y_c = el.Coord_vert[2].y;

                el.Coord_center_el.x = (BC * x_a + AC * x_b + AB * x_c) / (AB + BC + AC);
                el.Coord_center_el.y = (BC * y_a + AC * y_b + AB * y_c) / (AB + BC + AC);

            }

            el.h[0] = el.Area_el / p;
            el.h[1] = el.Area_el / p;
            el.h[2] = el.Area_el / p;

            vectorElement.push_back(el);

            i = i;

        }

        int p1, p2;

        /* ���� ���������� �������� � ��������� ��������� */
        for (int i = 1; i <= vectorElement.size() - 1; i++)
        {
            if (vectorElement[i].Geom_el == 2)
                for (int j = 0; j < 3; j++)
                {

                    int jj_temp = j + 1;
                    if (j + 1 == 3) jj_temp = 0;
                    /* C���� ����� ������� 1 � 2 */
                    p1 = vectorElement[i].Num_vert[j];
                    p2 = vectorElement[i].Num_vert[jj_temp];
                    if (vectorPoint[p1].Boundary && vectorPoint[p2].Boundary)
                    {

                        vectorElement[i].Neighb_el[j] = -1;

                        for (int jj = 0; jj < vectorElement.size(); jj++) // ����������� ���� �������
                        {
                            if (vectorElement[jj].Geom_el == 1)
                            {
                                bool pr1 = (p1 == vectorElement[jj].Num_vert[0] && p2 == vectorElement[jj].Num_vert[1]);
                                bool pr2 = (p1 == vectorElement[jj].Num_vert[1] && p2 == vectorElement[jj].Num_vert[0]);
                                if (pr1 || pr2)
                                {

                                    vectorElement[i].Num_bound = vectorElement[jj].Num_bound;

                                    break;

                                }
                            }
                        }

                    }
                    else
                    {

                        for (int jj = 0; jj < vectorElement.size(); jj++)
                        {
                            if ((p1 == vectorElement[jj].Num_vert[0] && p2 == vectorElement[jj].Num_vert[1] || p1 == vectorElement[jj].Num_vert[1] && p2 == vectorElement[jj].Num_vert[0]) && jj != vectorElement[i].Num_el) { vectorElement[i].Neighb_el[j] = jj; break; }
                            if ((p1 == vectorElement[jj].Num_vert[1] && p2 == vectorElement[jj].Num_vert[2] || p1 == vectorElement[jj].Num_vert[2] && p2 == vectorElement[jj].Num_vert[1]) && jj != vectorElement[i].Num_el) { vectorElement[i].Neighb_el[j] = jj; break; }
                            if ((p1 == vectorElement[jj].Num_vert[0] && p2 == vectorElement[jj].Num_vert[2] || p1 == vectorElement[jj].Num_vert[2] && p2 == vectorElement[jj].Num_vert[0]) && jj != vectorElement[i].Num_el) { vectorElement[i].Neighb_el[j] = jj; break; }
                        }

                    }

                    //cout << vectorElement[i].Num_el << " \t " << vectorElement[i].Neighb_el[0] << " \t " << vectorElement[i].Neighb_el[1] << " \t " << vectorElement[i].Neighb_el[2] << " \t " << vectorElement[i].Num_bound << endl;

                    i = i;
                }

            i = i;
        }

        /* ���� ���������� ���������, ����� ������� ������� ��������� */
        for (int i_p = 0; i_p <= vectorPoint.size() - 1; i_p++)
        {
            p1 = vectorPoint[i_p].Num_node;
            for (int i_el = 1; i_el <= vectorElement.size() - 1; i_el++)
            {
                if (vectorElement[i_el].Geom_el == 2)
                    for (int j = 0; j < 3; j++)
                        if (p1 == vectorElement[i_el].Num_vert[j])
                        {
                            vectorPoint[i_p].Neighb_el.push_back(vectorElement[i_el].Num_el);
                            i_el = i_el;
                        }
            }            
        }

        File_Mesh.close();

    }
    else Save_Read();

    Create_WriteDir();

}

void Blank()
{

    int Local_count = 0;
    int Local_it = 0;

    ofstream File_Blank("Documents/Blank/Blank_R0.BLN", ios_base::trunc);

    /* ������ ��������� ��������������� ����� */
    for (int i = 1; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 1 && (vectorElement[i].Num_bound != out_1 && vectorElement[i].Num_bound != out_2
            && vectorElement[i].Num_bound != calc))
        {
            Local_it++;
            if (Local_it == 1) Local_count = i;
            i = i;
        }
    }

    File_Blank << Local_it + 1 << "\t" << "1" << endl;

    /* ������ ��������� */
    for (int i = 0; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 1 && (vectorElement[i].Num_bound != out_1 && vectorElement[i].Num_bound != out_2
            && vectorElement[i].Num_bound != calc))
        {
            File_Blank << fixed << setprecision(4) << vectorElement[i].Coord_vert[0].x << " \t " << vectorElement[i].Coord_vert[0].y << endl;
        }
    }

    File_Blank << fixed << setprecision(4) << vectorElement[Local_count].Coord_vert[0].x << " \t " << vectorElement[Local_count].Coord_vert[0].y;

}

void Initial_Conditions()
{

    Blank();

    ofstream File_Init("Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/1. Initial Cond.DAT", ios_base::trunc);
    File_Init << "Coord_x" << "\t" << "Coord_y" << "\t" << "Velosity_Ux" << "\t" << "Velocity_Uy" << "\t" << "Velocity_P" << "\t" << "Num_el" << endl;

    if (Read_From_Save == false && Start_Flow_Evolution == false)
    {

        for (int i = 0; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {

                double r_temp = pow(vectorElement[i].Coord_center_el.x * vectorElement[i].Coord_center_el.x + vectorElement[i].Coord_center_el.y * vectorElement[i].Coord_center_el.y, 0.5);
                double U_an = ((omega_1 * R1 * R1 - omega_0 * R0 * R0) * r_temp + R0 * R0 * R1 * R1 * (omega_0 - omega_1) / r_temp) / (R1 * R1 - R0 * R0);
                              
                vectorElement[i].u_y = 0.0 + alfa_k * omega_1 * vectorElement[i].Coord_center_el.x;
                vectorElement[i].U_y = vectorElement[i].u_y;

                vectorElement[i].u_x = 0.0 - alfa_k * omega_1 * vectorElement[i].Coord_center_el.y;
                vectorElement[i].U_x = vectorElement[i].u_x;

                vectorElement[i].P = 0.0;

                /* vectorElement[i].u_y = vectorElement[i].Coord_center_el.x / r_temp * U_an;
                 vectorElement[i].U_y = vectorElement[i].u_y;

                 vectorElement[i].u_x = -vectorElement[i].Coord_center_el.y / r_temp * U_an;
                 vectorElement[i].U_x = vectorElement[i].u_x;

                 vectorElement[i].P = Re / pow((R1 * R1 - R0 * R0), 2) * (pow((omega_1 * R1 * R1 - omega_0 * R0 * R0), 2) * (r_temp * r_temp - R0 * R0) * 0.5 + 2 * R0 * R0 * R1 * R1 * (omega_0 - omega_1) * (omega_1 * R1 * R1 - omega_0 * R0 * R0) * log(r_temp / R0) - 0.5 * (omega_0 - omega_1) * (omega_0 - omega_1) * pow(R0 * R1, 4) * (1.0 / (r_temp * r_temp) - 1.0 / (R0 * R0)));*/

                vectorElement[i].P_Correction = 0.0;
            }
        }

        for (int i = 0; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {

                File_Init << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                    << vectorElement[i].U_x << " \t " << vectorElement[i].U_y << " \t " << vectorElement[i].P << " \t " << vectorElement[i].Num_el << endl;

            }
        }

        string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el);
        ofstream development(_path + "/2. development_(El = " + to_string(max_el) + ").DAT", ios_base::trunc);
        development << "Time" << "\t" << "U_x" << "\t" << "U_y" << "\t" << "P" << "\t" << "Max.Res." << endl;

        _time_Flow_Evolution = 0.0;

    }
    //else Save_Read();

}

double Value_bound(double x, double y, int ii, int jj, string param)
{
    double value_bound;

    if (param == "U_x")
    {
        if (vectorElement[ii].Num_bound == out_1 || vectorElement[ii].Num_bound == out_2)
        {
            value_bound = -omega_1 * sqrt(x * x + y * y) * vectorElement[ii].Normal[jj][1];
        }
        else if (vectorElement[ii].Num_bound != 0)
        {
            value_bound = -omega_0 * sqrt(x * x + y * y) * vectorElement[ii].Normal[jj][1];
        }
    }
    if (param == "U_y")
    {
        if (vectorElement[ii].Num_bound == out_1 || vectorElement[ii].Num_bound == out_2)
        {
            value_bound = omega_1 * sqrt(x * x + y * y) * vectorElement[ii].Normal[jj][0];
        }
        else if (vectorElement[ii].Num_bound != 0)
        {
            value_bound = omega_0 * sqrt(x * x + y * y) * vectorElement[ii].Normal[jj][0];
        }
    }
    return value_bound;

}

double Firsov_M(int num_i, string param)
{

    /*string _path = "Documents/Figure/El = " + to_string(max_el);
    ofstream Test_n(_path + "/1. Firsov-M_(El = " + to_string(max_el) + ").DAT", ios_base::trunc);*/

    /* Normal to face */
    double normal_to_face[3][2];
    double len_face_David[3];
    double coord_vertex_David[3][2];

    /* Calc coordinate vertex triangle David */
    for (int j = 0; j < 3; j++)
    {
        if (vectorElement[num_i].Neighb_el[j] == -1)
        {
            if (param == "P/dx" || param == "P/dy" || param == "P'/dx" || param == "P'/dy")
            {
                coord_vertex_David[j][0] = vectorElement[num_i].Coord_center_el.x;
                coord_vertex_David[j][1] = vectorElement[num_i].Coord_center_el.y;
            }
            else
            {
                if (Start_Flow_Evolution == false)
                {
                    int jj_temp = j + 1;
                    if (j + 1 == 3) jj_temp = 0;
                    coord_vertex_David[j][0] = 0.5 * (vectorElement[num_i].Coord_vert[j].x + vectorElement[num_i].Coord_vert[jj_temp].x);
                    coord_vertex_David[j][1] = 0.5 * (vectorElement[num_i].Coord_vert[j].y + vectorElement[num_i].Coord_vert[jj_temp].y);

                    //coord_vertex_David[j][0] = (vectorElement[num_i].Coord_vert[j].x + vectorElement[num_i].Coord_vert[jj_temp].x) - vectorElement[num_i].Coord_center_el.x;
                    //coord_vertex_David[j][1] = (vectorElement[num_i].Coord_vert[j].y + vectorElement[num_i].Coord_vert[jj_temp].y) - vectorElement[num_i].Coord_center_el.y;

                }
                
                if (Start_Flow_Evolution == true)
                {
                    coord_vertex_David[j][0] = vectorElement[num_i].Coord_center_el.x;
                    coord_vertex_David[j][1] = vectorElement[num_i].Coord_center_el.y;
                }
                
            }
        }
        else
        {
            coord_vertex_David[j][0] = vectorElement[vectorElement[num_i].Neighb_el[j]].Coord_center_el.x;
            coord_vertex_David[j][1] = vectorElement[vectorElement[num_i].Neighb_el[j]].Coord_center_el.y;
        }
    }

    /* Calc normals */
    for (int j = 0; j < 3; j++)
    {
        int jj_temp = j + 1;
        if (j + 1 == 3) jj_temp = 0;

        double a_1 = coord_vertex_David[jj_temp][1] - coord_vertex_David[j][1];
        if (a_1 == 0) a_1 = 1e-8;
        double a_2 = coord_vertex_David[jj_temp][0] - coord_vertex_David[j][0];
        if (a_2 == 0) a_2 = 1e-8;
        len_face_David[j] = sqrt(a_1 * a_1 + a_2 * a_2);
        double a = a_1 / a_2;
        double ny_p = 1 / pow(a * a + 1, 0.5);
        double ny_m = -1 / pow(a * a + 1, 0.5);
        double nx_p = -a * ny_p;
        double nx_m = -a * ny_m;

        double n_check_p = a_2 * ny_p - a_1 * nx_p;
        double n_check_m = a_2 * ny_m - a_1 * nx_m;

        if (n_check_p < 0)
        {

            normal_to_face[j][0] = -a * ny_p;
            normal_to_face[j][1] = ny_p;

        }
        else if (n_check_m < 0)
        {

            normal_to_face[j][0] = -a * ny_m;
            normal_to_face[j][1] = ny_m;

        }
        else
        {

            cout << "Normal calculation ERROR (face 1)" << endl;
            system("pause");

        }
    }

    /*double coord_2_1_x = N_el_neighb_x + (0.5 * (vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.x - N_el_neighb_x));
    double coord_2_1_y = N_el_neighb_y + (0.5 * (vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.y - N_el_neighb_y));
    double coord_3_2_x = vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.x + (0.5 * (vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.x - vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.x));
    double coord_3_2_y = vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.y + (0.5 * (vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.y - vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.y));
    double coord_1_3_x = vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.x + (0.5 * (N_el_neighb_x - vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.x));
    double coord_1_3_y = vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.y + (0.5 * (N_el_neighb_y - vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.y));
    double mod_n1 = n_1;
    double mod_n2 = n_2;
    double mod_n3 = n_3;

    Test_n << fixed << setprecision(5) << vectorElement[num_i].Num_el + 1
         << "\t" << N_el_neighb_x << "\t" << N_el_neighb_y << "\t" << vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.x << "\t" << vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.y << endl
         << "\t" << vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.x << "\t" << vectorElement[vectorElement[num_i].Neighb_el[1]].Coord_center_el.y << "\t" << vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.x << "\t" << vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.y << endl
         << "\t" << vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.x << "\t" << vectorElement[vectorElement[num_i].Neighb_el[2]].Coord_center_el.y << "\t" << N_el_neighb_x << "\t" << N_el_neighb_y << endl << endl;
     Test_n << fixed << setprecision(5)
         << "\t" << coord_2_1_x << "\t" << coord_2_1_y << "\t" << coord_2_1_x + n1_x_N << "\t" << coord_2_1_y + n1_y_N<< "\t\t" << mod_n1 << endl
         << "\t" << coord_3_2_x << "\t" << coord_3_2_y << "\t" << coord_3_2_x + n2_x_N << "\t" << coord_3_2_y + n2_y_N << "\t\t" << mod_n2 << endl
         << "\t" << coord_1_3_x << "\t" << coord_1_3_y << "\t" << coord_1_3_x + n3_x_N << "\t" << coord_1_3_y + n3_y_N << "\t\t" << mod_n3 << endl << endl;*/

    double a = len_face_David[0];
    double b = len_face_David[1];
    double c = len_face_David[2];
    double p = 0.5 * (a + b + c);
    double S_N = sqrt(p * (p - a) * (p - b) * (p - c));

    double test = 0.0;

    double UU_vert[3];
    for (int j = 0; j < 3; j++)
    {
        if (vectorElement[num_i].Neighb_el[j] == -1)
        {
            if (Start_Flow_Evolution == false)
            {
                /*int jj_temp = j + 1;
                if (j + 1 == 3) jj_temp = 0;
                double tmp_xx = 0.5 * (vectorElement[num_i].Coord_vert[j].x + vectorElement[num_i].Coord_vert[jj_temp].x);
                double tmp_yy = 0.5 * (vectorElement[num_i].Coord_vert[j].y + vectorElement[num_i].Coord_vert[jj_temp].y);

                if (param == "U_x/dx" || param == "U_x/dy") UU_vert[j] = 2.0 * Value_bound(tmp_xx, tmp_yy, num_i, j, "U_x") - vectorElement[num_i].U_x;
                if (param == "U_y/dx" || param == "U_y/dy") UU_vert[j] = 2.0 * Value_bound(tmp_xx, tmp_yy, num_i, j, "U_y") - vectorElement[num_i].U_y;*/

                if (param == "U_x/dx" || param == "U_x/dy") UU_vert[j] = Value_bound(coord_vertex_David[j][0], coord_vertex_David[j][1], num_i, j, "U_x");
                if (param == "U_y/dx" || param == "U_y/dy") UU_vert[j] = Value_bound(coord_vertex_David[j][0], coord_vertex_David[j][1], num_i, j, "U_y");
            }            
            
            if (Start_Flow_Evolution == true)
            {
                if (param == "U_x/dx" || param == "U_x/dy") UU_vert[j] = vectorElement[num_i].U_x;
                if (param == "U_y/dx" || param == "U_y/dy") UU_vert[j] = vectorElement[num_i].U_y;
            }
            

            if (param == "P/dx" || param == "P/dy") UU_vert[j] = vectorElement[num_i].P;
            if (param == "P'/dx" || param == "P'/dy") UU_vert[j] = vectorElement[num_i].P_Correction;
        }
        else
        {
            if (param == "U_x/dx" || param == "U_x/dy") UU_vert[j] = vectorElement[vectorElement[num_i].Neighb_el[j]].U_x;
            if (param == "U_y/dx" || param == "U_y/dy") UU_vert[j] = vectorElement[vectorElement[num_i].Neighb_el[j]].U_y;
            if (param == "P/dx" || param == "P/dy") UU_vert[j] = vectorElement[vectorElement[num_i].Neighb_el[j]].P;
            if (param == "P'/dx" || param == "P'/dy") UU_vert[j] = vectorElement[vectorElement[num_i].Neighb_el[j]].P_Correction;
        }

    }


    for (int j = 0; j < 3; j++)
    {
        int jj_temp = j + 1;
        if (j + 1 == 3) jj_temp = 0;
        if (param == "U_x/dx" || param == "U_y/dx" || param == "P/dx" || param == "P'/dx") test += normal_to_face[j][0] * 0.5 * (UU_vert[j] + UU_vert[jj_temp]) * len_face_David[j];
        if (param == "U_x/dy" || param == "U_y/dy" || param == "P/dy" || param == "P'/dy") test += normal_to_face[j][1] * 0.5 * (UU_vert[j] + UU_vert[jj_temp]) * len_face_David[j];
    }
    test /= S_N;

    return test;
}

void Redistricting()
{

    for (int i = 0; i < max_el; i++)
    {
        vectorElement[i].u_x = vectorElement[i].U_x;
        vectorElement[i].u_y = vectorElement[i].U_y;
    }

}

void Redistricting1()
{

    for (int i = 0; i < max_el; i++)
    {
        /* ���������� ���������� U_x, U_y, P */
        if (vectorElement[i].Geom_el == 2)
        {
            vectorElement[i].gradU_x[0] = Firsov_M(i, "U_x/dx");
            vectorElement[i].gradU_x[1] = Firsov_M(i, "U_x/dy");
            vectorElement[i].gradU_y[0] = Firsov_M(i, "U_y/dx");
            vectorElement[i].gradU_y[1] = Firsov_M(i, "U_y/dy");                        
            vectorElement[i].gradP[0] = Firsov_M(i, "P/dx");
            vectorElement[i].gradP[1] = Firsov_M(i, "P/dy");
        }
    }

}

void Redistricting_gradP_Corr()
{

    for (int i = 0; i < max_el; i++)
    {
        /* ���������� ���������� P_Corr */
        if (vectorElement[i].Geom_el == 2)
        {
            vectorElement[i].gradP_Corr[0] = Firsov_M(i, "P'/dx");
            vectorElement[i].gradP_Corr[1] = Firsov_M(i, "P'/dy");
        }
    }

}

double beta(int ii, int jj)
{
    int jj_temp = jj + 1;
    if (jj + 1 == 3) jj_temp = 0;

    double x_ik = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].x + vectorElement[ii].Coord_vert[jj].x);
    double y_ik = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].y + vectorElement[ii].Coord_vert[jj].y);
    double x_x_ik = vectorElement[ii].Coord_center_el.x - x_ik;
    double y_y_ik = vectorElement[ii].Coord_center_el.y - y_ik;
    double x1_x_ik = vectorElement[vectorElement[ii].Neighb_el[jj]].Coord_center_el.x - x_ik;
    double y1_y_ik = vectorElement[vectorElement[ii].Neighb_el[jj]].Coord_center_el.y - y_ik;
    double scal_x1_x_ik_n = abs(x1_x_ik * vectorElement[ii].Normal[jj][0] + y1_y_ik * vectorElement[ii].Normal[jj][1]);
    double scal_x_x_ik_n = abs(x_x_ik * vectorElement[ii].Normal[jj][0] + y_y_ik * vectorElement[ii].Normal[jj][1]);
    return scal_x1_x_ik_n / (scal_x1_x_ik_n + scal_x_x_ik_n);

}

double Section_value_MUSCL(double xx, double yy, string param)
{

    double dl;
    double temp_1 = 100;

    if (param == "NULL")
    {

        for (int i = 0; i < vectorElement.size(); i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {

                dl = sqrt(pow((vectorElement[i].Coord_center_el.x - xx), 2) + pow((vectorElement[i].Coord_center_el.y - yy), 2));

                if (dl < temp_1)
                {

                    temp_1 = dl;
                    num_el_1 = vectorElement[i].Num_el;

                    i = i;

                }
            }

        }

    }
    else
    {

        /* ����� �������� */
        for (int i = 0; i < vectorElement.size(); i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {

                dl = sqrt(pow((vectorElement[i].Coord_center_el.x - xx), 2) + pow((vectorElement[i].Coord_center_el.y - yy), 2));

                if (dl < temp_1)
                {

                    temp_1 = dl;
                    num_el_1_MUSCL = vectorElement[i].Num_el;

                }
            }
        }

        double test = 0.0;

        /* ������������ ������ �������� */
        {
            /* ��������� ��������� */
            double t1, t2, Param;

            double x_x_i = xx - vectorElement[num_el_1_MUSCL].Coord_center_el.x;
            double y_y_i = yy - vectorElement[num_el_1_MUSCL].Coord_center_el.y;

            if (param == "P")
            {
                t1 = vectorElement[num_el_1_MUSCL].gradP[0];
                t2 = vectorElement[num_el_1_MUSCL].gradP[1];
                Param = vectorElement[num_el_1_MUSCL].P;
            }
            if (param == "U_x")
            {
                t1 = vectorElement[num_el_1_MUSCL].gradU_x[0];
                t2 = vectorElement[num_el_1_MUSCL].gradU_x[1];
                Param = vectorElement[num_el_1_MUSCL].U_x;
            }
            if (param == "U_y")
            {
                t1 = vectorElement[num_el_1_MUSCL].gradU_y[0];
                t2 = vectorElement[num_el_1_MUSCL].gradU_y[1];
                Param = vectorElement[num_el_1_MUSCL].U_y;
            }
            if (param == "P'")
            {
                t1 = vectorElement[num_el_1_MUSCL].gradP_Corr[0];
                t2 = vectorElement[num_el_1_MUSCL].gradP_Corr[1];
                Param = vectorElement[num_el_1_MUSCL].P_Correction;
            }

            return Param + (x_x_i * t1 + y_y_i * t2);
        }
    }
}

double Section_value_MUSCL_Face(double xx, double yy, string param, int num_i)
{

    double temp_1 = 100;

    double test = 0.0;

    /* ������������ ������ �������� */
    {
        /* ��������� ��������� */
        double x_x_i = xx - vectorElement[num_i].Coord_center_el.x;
        double y_y_i = yy - vectorElement[num_i].Coord_center_el.y;

        double t1, t2, Param;

        if (param == "U_x")
        {
            t1 = vectorElement[num_i].gradU_x[0];
            t2 = vectorElement[num_i].gradU_x[1];
            Param = vectorElement[num_i].U_x;

            /*if (vectorElement[num_i].Num_bound == 2 || vectorElement[num_i].Num_bound == 1) 
            {

                Param = -1.0 / 0.96 * (yy - 0.04 * yy / (xx * xx + yy * yy));
                return Param;
            }*/
        }
        if (param == "U_y")
        {
            t1 = vectorElement[num_i].gradU_y[0];
            t2 = vectorElement[num_i].gradU_y[1];
            Param = vectorElement[num_i].U_y;

            /*if (vectorElement[num_i].Num_bound == 2 || vectorElement[num_i].Num_bound == 1) 
            {

                Param = 1.0 / 0.96 * (xx - 0.04 * xx / (xx * xx + yy * yy));
                return Param;
            }*/
        }
        if (param == "P")
        {
            t1 = vectorElement[num_i].gradP[0];
            t2 = vectorElement[num_i].gradP[1];
            Param = vectorElement[num_i].P;

            //if (vectorElement[num_i].Num_bound == 2 || vectorElement[num_i].Num_bound == 1) 
            //{
            //    double rr = sqrt(xx * xx + yy * yy);
            //    t1 = 1.0 / 0.96 / 0.96 * (xx - 0.08 * xx /rr / rr - 0.5 * 0.04 * 0.04 * 2.0 * xx / pow(rr,4));
            //    t2 = 1.0 / 0.96 / 0.96 * (yy - 0.08 * yy / rr / rr - 0.5 * 0.04 * 0.04 * 2.0 * yy / pow(rr, 4));
            //    Param = vectorElement[num_i].P;
            //    //return Param;
            //}
        }

        return  Param + (x_x_i * t1 + y_y_i * t2);
    }

}

double Section_value_MUSCL_Flow_Evo(double xx, double yy, int num,string param)
{

    double dl;
    double temp_1 = 100;
    bool MarkerInOldElement = false;
    bool MarkerInNeibElements = false;

    /* ����� ������� � ������ �������� */
    if (Iter_Glob > 1)
    {
        int num_el = num_el_for_marker[num];
        double x1 = vectorElement[num_el].Coord_vert[0].x;
        double y1 = vectorElement[num_el].Coord_vert[0].y;
        double x2 = vectorElement[num_el].Coord_vert[1].x;
        double y2 = vectorElement[num_el].Coord_vert[1].y;
        double x3 = vectorElement[num_el].Coord_vert[2].x;
        double y3 = vectorElement[num_el].Coord_vert[2].y;


        int a = (x1 - xx) * (y2 - y1) - (x2 - x1) * (y1 - yy);
        int b = (x2 - xx) * (y3 - y2) - (x3 - x2) * (y2 - yy);
        int c = (x3 - xx) * (y1 - y3) - (x1 - x3) * (y3 - yy);

        MarkerInOldElement = (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);

        if (MarkerInOldElement)
        {
            num_el_1_MUSCL = vectorElement[num_el].Num_el;
        }

        double debug = 0.0;

    }

    /* ����� ������� � �������� ��������� */
    if (Iter_Glob > 1 && !MarkerInOldElement)
    {
        int num_el = num_el_for_marker[num];
        
        /* �������� �������������� ������� ������ �� ������� */
        for (int j = 0; j < 3; j++)
        {
            if (vectorElement[num_el].Neighb_el[j] != -1)
            {
                double x1 = vectorElement[num_el].Coord_vert[0].x;
                double y1 = vectorElement[num_el].Coord_vert[0].y;
                double x2 = vectorElement[num_el].Coord_vert[1].x;
                double y2 = vectorElement[num_el].Coord_vert[1].y;
                double x3 = vectorElement[num_el].Coord_vert[2].x;
                double y3 = vectorElement[num_el].Coord_vert[2].y;


                int a = (x1 - xx) * (y2 - y1) - (x2 - x1) * (y1 - yy);
                int b = (x2 - xx) * (y3 - y2) - (x3 - x2) * (y2 - yy);
                int c = (x3 - xx) * (y1 - y3) - (x1 - x3) * (y3 - yy);

                MarkerInNeibElements = (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);

                if (MarkerInNeibElements)
                {
                    num_el_1_MUSCL = vectorElement[num_el].Num_el;
                }
            }
        }
    }

    /* ����� ������� �� ���� ����� */
    if (Iter_Glob == 1 || (!MarkerInOldElement && !MarkerInNeibElements))
    {
        for (int i = 0; i < vectorElement.size(); i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {

                dl = pow((vectorElement[i].Coord_center_el.x - xx), 2) + pow((vectorElement[i].Coord_center_el.y - yy), 2);

                if (dl < temp_1)
                {

                    temp_1 = dl;
                    num_el_1_MUSCL = vectorElement[i].Num_el;

                }
            }
        }

        num_el_for_marker[num] = num_el_1_MUSCL;

    }

    double test = 0.0;

    /* ������������ ������ �������� */
    {
        /* ��������� ��������� */
        double t1, t2, Param;

        double x_x_i = xx - vectorElement[num_el_1_MUSCL].Coord_center_el.x;
        double y_y_i = yy - vectorElement[num_el_1_MUSCL].Coord_center_el.y;

        if (param == "P")
        {
            t1 = vectorElement[num_el_1_MUSCL].gradP[0];
            t2 = vectorElement[num_el_1_MUSCL].gradP[1];
            Param = vectorElement[num_el_1_MUSCL].P;
        }
        if (param == "U_x")
        {
            t1 = vectorElement[num_el_1_MUSCL].gradU_x[0];
            t2 = vectorElement[num_el_1_MUSCL].gradU_x[1];
            Param = vectorElement[num_el_1_MUSCL].U_x;
        }
        if (param == "U_y")
        {
            t1 = vectorElement[num_el_1_MUSCL].gradU_y[0];
            t2 = vectorElement[num_el_1_MUSCL].gradU_y[1];
            Param = vectorElement[num_el_1_MUSCL].U_y;
        }
        if (param == "P'")
        {
            t1 = vectorElement[num_el_1_MUSCL].gradP_Corr[0];
            t2 = vectorElement[num_el_1_MUSCL].gradP_Corr[1];
            Param = vectorElement[num_el_1_MUSCL].P_Correction;
        }

        return Param + (x_x_i * t1 + y_y_i * t2);
    }
}

void Calculation_Velocity_U()
{
    /* ������ �������� U */
    {
        for (int i = 1; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {
                double temp_sum_ux = 0.0, temp_sum_uy = 0.0;
                vectorElement[i].A_0 = vectorElement[i].Area_el / dt;
                // �������� ��������
                double Sp_x = 0.0, Sp_y = 0.0;
                // �������� �������
                double Sd_x = 0.0, Sd_y = 0.0;
                // �������� ���������
                double Sc_x = 0.0, Sc_y = 0.0;
                // �������� ���� ���������
                double Sk_x = 0.0, Sk_y = 0.0;
                double debug_x = 0.0, debug_y = 0;

                if (i == 1418)
                    i = i;

                for (int j = 0; j < 3; j++)
                {

                    int jj_temp = j + 1;
                    if (j + 1 == 3) jj_temp = 0;

                    double x_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].x + vectorElement[i].Coord_vert[j].x);
                    double y_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].y + vectorElement[i].Coord_vert[j].y);

                    double grad_neidghb = 0.0;
                    if (vectorElement[i].Neighb_el[j] != -1)
                    {
                        int ii = vectorElement[i].Neighb_el[j];
                        double U_ik_x = 0.5 * (vectorElement[i].U_x + vectorElement[ii].U_x);
                        double U_ik_y = 0.5 * (vectorElement[i].U_y + vectorElement[ii].U_y);
                        /*double U_ik_x = 0.5 * (Section_value_MUSCL_Face(x_ik, y_ik, "U_x", i) + Section_value_MUSCL_Face(x_ik, y_ik, "U_x", ii));
                        double U_ik_y = 0.5 * (Section_value_MUSCL_Face(x_ik, y_ik, "U_y", i) + Section_value_MUSCL_Face(x_ik, y_ik, "U_y", ii));*/
                        double sc_n_U_ik = vectorElement[i].Normal[j][0] * U_ik_x + vectorElement[i].Normal[j][1] * U_ik_y;
                        double flux = sc_n_U_ik * vectorElement[i].Length_face_el[j];
                        double HH = vectorElement[i].h[j] + vectorElement[ii].h[j];
                        double coeff = fmax(-flux, 0) + vectorElement[i].Length_face_el[j] / (HH * Re);

                        temp_sum_ux += coeff * vectorElement[ii].U_x;
                        temp_sum_uy += coeff * vectorElement[ii].U_y;
                        vectorElement[i].A_0 += coeff;

                        grad_neidghb = Section_value_MUSCL_Face(x_ik, y_ik, "P", ii);

                        double Px, Py, Nx, Ny, xc, yc, nx, ny, xm, ym;
                        /* ���� ���������� ���. ��������� */
                        {
                            xm = x_ik, ym = y_ik;
                            xc = vectorElement[ii].Coord_center_el.x, yc = vectorElement[ii].Coord_center_el.y;
                            nx = vectorElement[i].Normal[j][0], ny = vectorElement[i].Normal[j][1];

                            Py = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                            Px = (yc - Py) * ny / nx + xc;//(Py - ym) * nx / ny + xm;

                            xc = vectorElement[i].Coord_center_el.x, yc = vectorElement[i].Coord_center_el.y;

                            Ny = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                            Nx = (yc - Ny) * ny / nx + xc;//(Ny - ym) * nx / ny + xm;

                        }

                        double t_0_x = Nx - vectorElement[i].Coord_center_el.x, t_0_y = Ny - vectorElement[i].Coord_center_el.y;
                        double t_i_x = Px - vectorElement[ii].Coord_center_el.x, t_i_y = Py - vectorElement[ii].Coord_center_el.y;

                        double scal_0_Ux = vectorElement[i].gradU_x[0] * t_0_x + vectorElement[i].gradU_x[1] * t_0_y;
                        double scal_i_Ux = vectorElement[ii].gradU_x[0] * t_i_x + vectorElement[ii].gradU_x[1] * t_i_y;

                        double scal_0_Uy = vectorElement[i].gradU_y[0] * t_0_x + vectorElement[i].gradU_y[1] * t_0_y;
                        double scal_i_Uy = vectorElement[ii].gradU_y[0] * t_i_x + vectorElement[ii].gradU_y[1] * t_i_y;

                        double h_c0_ci = sqrt((Nx - Px) * (Nx - Px) + (Ny - Py) * (Ny - Py));
                        Sd_x += vectorElement[i].Length_face_el[j] * (scal_i_Ux - scal_0_Ux) / h_c0_ci;
                        Sd_y += vectorElement[i].Length_face_el[j] * (scal_i_Uy - scal_0_Uy) / h_c0_ci;

                        /*double r_0_x = x_ik - vectorElement[i].Coord_center_el.x;
                        double r_0_y = y_ik - vectorElement[i].Coord_center_el.y;
                        double r_i_x = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].x + vectorElement[ii].Coord_vert[j].x) - vectorElement[ii].Coord_center_el.x;
                        double r_i_y = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].y + vectorElement[ii].Coord_vert[j].y) - vectorElement[ii].Coord_center_el.y;

                        scal_0_Ux = vectorElement[i].gradU_x[0] * r_0_x + vectorElement[i].gradU_x[1] * r_0_y;
                        scal_0_Uy = vectorElement[i].gradU_y[0] * r_0_x + vectorElement[i].gradU_y[1] * r_0_y;
                        scal_i_Ux = vectorElement[ii].gradU_x[0] * r_i_x + vectorElement[ii].gradU_x[1] * r_i_y;
                        scal_i_Uy = vectorElement[ii].gradU_y[0] * r_i_x + vectorElement[ii].gradU_y[1] * r_i_y;

                        debug_x += fmax(flux, 0) * (vectorElement[i].U_x + scal_0_Ux) - fmax(-flux, 0) * (vectorElement[ii].U_x + scal_i_Ux);
                        debug_y += fmax(flux, 0) * (vectorElement[i].U_y + scal_0_Uy) - fmax(-flux, 0) * (vectorElement[ii].U_y + scal_i_Uy);

                        //Sc_x += fmax(flux, 0) * scal_0_Ux - fmax(flux, 0) * scal_i_Ux;
                        //Sc_y += fmax(flux, 0) * scal_0_Uy - fmax(flux, 0) * scal_i_Uy;*/
                    }
                    else
                    {

                        double coeff = vectorElement[i].Length_face_el[j] / vectorElement[i].h[j];
                        temp_sum_ux += coeff * Value_bound(x_ik, y_ik, i, j, "U_x");
                        temp_sum_uy += coeff * Value_bound(x_ik, y_ik, i, j, "U_y");
                        vectorElement[i].A_0 += coeff;
                        grad_neidghb = Section_value_MUSCL_Face(x_ik, y_ik, "P", i);

                        double Nx, Ny;
                        /* ���� ���������� ���. ��������� */
                        {
                            double xm = x_ik, ym = y_ik;
                            double xc = vectorElement[i].Coord_center_el.x, yc = vectorElement[i].Coord_center_el.y;
                            double nx = vectorElement[i].Normal[j][0], ny = vectorElement[i].Normal[j][1];

                            xc = vectorElement[i].Coord_center_el.x, yc = vectorElement[i].Coord_center_el.y;

                            Ny = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                            Nx = (Ny - ym) * nx / ny + xm;

                            i = i;
                        }

                        double t_0_x = Nx - vectorElement[i].Coord_center_el.x, t_0_y = Ny - vectorElement[i].Coord_center_el.y;

                        double scal_0_Ux = vectorElement[i].gradU_x[0] * t_0_x + vectorElement[i].gradU_x[1] * t_0_y;

                        double scal_0_Uy = vectorElement[i].gradU_y[0] * t_0_x + vectorElement[i].gradU_y[1] * t_0_y;

                        double h_c0_ci = sqrt((Nx - x_ik) * (Nx - x_ik) + (Ny - y_ik) * (Ny - y_ik));
                        Sd_x += vectorElement[i].Length_face_el[j] * (-scal_0_Ux) / h_c0_ci;
                        Sd_y += vectorElement[i].Length_face_el[j] * (-scal_0_Uy) / h_c0_ci;

                    }

                    double test_1 = Section_value_MUSCL_Face(x_ik, y_ik, "P", i);
                    double test_2 = vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                    double test_4 = vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];

                    Sp_x += 0.5 * (Section_value_MUSCL_Face(x_ik, y_ik, "P", i) + grad_neidghb) * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                    Sp_y += 0.5 * (Section_value_MUSCL_Face(x_ik, y_ik, "P", i) + grad_neidghb) * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];
                }

                Sk_x = alfa_k * (2 * vectorElement[i].U_y + vectorElement[i].Coord_center_el.x) * vectorElement[i].Area_el;
                Sk_y = alfa_k * (-2 * vectorElement[i].U_x + vectorElement[i].Coord_center_el.y) * vectorElement[i].Area_el;

                vectorElement[i].U_x = (temp_sum_ux - Sp_x + vectorElement[i].Area_el / dt * vectorElement[i].u_x + Sd_x / Re - Sc_x + Sk_x) / vectorElement[i].A_0;
                vectorElement[i].U_y = (temp_sum_uy - Sp_y + vectorElement[i].Area_el / dt * vectorElement[i].u_y + Sd_y / Re - Sc_y + Sk_y) / vectorElement[i].A_0;
            }
        }
    }
}

double divU(int ii)
{

    /* ����������� �������� ����� ���������� �������� � ����� MUSCL */
    double x_ik, y_ik, U_x = 0.0, U_y = 0.0, a, b, c;
    double temp = 0;

    for (int j = 0; j <= 2; j++)
        if (vectorElement[ii].Neighb_el[j] != -1)
        {
            int i_nb = vectorElement[ii].Neighb_el[j];
            int jj_temp = j + 1;
            if (j + 1 == 3) jj_temp = 0;
            x_ik = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].x + vectorElement[ii].Coord_vert[j].x);
            y_ik = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].y + vectorElement[ii].Coord_vert[j].y);
                       
            U_x = 0.5 * (Section_value_MUSCL_Face(x_ik, y_ik, "U_x", ii) + Section_value_MUSCL_Face(x_ik, y_ik, "U_x", i_nb));
            U_y = 0.5 * (Section_value_MUSCL_Face(x_ik, y_ik, "U_y", ii) + Section_value_MUSCL_Face(x_ik, y_ik, "U_y", i_nb));

            double test = (vectorElement[ii].Normal[j][0] * U_x + vectorElement[ii].Normal[j][1] * U_y) * vectorElement[ii].Length_face_el[j];
            temp += (vectorElement[ii].Normal[j][0] * U_x + vectorElement[ii].Normal[j][1] * U_y) * vectorElement[ii].Length_face_el[j];

           /*int el_1 = 71;
           double x = vectorElement[el_1].Coord_vert[2].x;
           double y = vectorElement[el_1].Coord_vert[2].y;
           double test_x = Section_value_MUSCL_Face(x, y, "U_x", el_1);
           double test_y = Section_value_MUSCL_Face(x, y, "U_y", el_1);*/

            //Interpolation Rhie-Chow
            double beta_temp = beta(ii, j);
            double Df_avr = beta_temp * vectorElement[ii].Area_el / vectorElement[ii].A_0 + (1 - beta_temp) * vectorElement[i_nb].Area_el / vectorElement[i_nb].A_0;
            double nab_p_avr_x = beta_temp * vectorElement[ii].gradP[0] + (1 - beta_temp) * vectorElement[i_nb].gradP[0];
            double nab_p_avr_y = beta_temp * vectorElement[ii].gradP[1] + (1 - beta_temp) * vectorElement[i_nb].gradP[1];
            double sl1 = (nab_p_avr_x * vectorElement[ii].Normal[j][0] + nab_p_avr_y * vectorElement[ii].Normal[j][1]) * vectorElement[ii].Length_face_el[j];
            
            double Px, Py, Nx, Ny, xc, yc, nx, ny, xm, ym;
            /* ���� ���������� ����� N � P */
            {
                xm = x_ik, ym = y_ik;
                xc = vectorElement[i_nb].Coord_center_el.x, yc = vectorElement[i_nb].Coord_center_el.y;
                nx = vectorElement[ii].Normal[j][0], ny = vectorElement[ii].Normal[j][1];

                Py = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                Px = (Py - ym) * nx / ny + xm;

                xc = vectorElement[ii].Coord_center_el.x, yc = vectorElement[ii].Coord_center_el.y;

                Ny = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                Nx = (Ny - ym) * nx / ny + xm;

            }

            /*double P_0 = Section_value_MUSCL(Nx, Ny, "P");
            double P_i = Section_value_MUSCL(Px, Py, "P");
            double sl2 = (P_i - P_0) / (vectorElement[i_nb].h[j] + vectorElement[ii].h[j]) * vectorElement[ii].Length_face_el[j];*/
            double sl2 = (vectorElement[i_nb].P - vectorElement[ii].P) / (vectorElement[i_nb].h[j] + vectorElement[ii].h[j]) * vectorElement[ii].Length_face_el[j];
            temp -= Df_avr * (sl2 - sl1);
            double debug = 0.0;
        }
        else
        {
            int jj_temp = j + 1;
            if (j + 1 == 3) jj_temp = 0;
            double xx = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].x + vectorElement[ii].Coord_vert[j].x);
            double yy = 0.5 * (vectorElement[ii].Coord_vert[jj_temp].y + vectorElement[ii].Coord_vert[j].y);
            double U_x_bound = Value_bound(xx, yy, ii, j, "U_x");
            double U_y_bound = Value_bound(xx, yy, ii, j, "U_y");
            double test = (vectorElement[ii].Normal[j][0] * U_x_bound + vectorElement[ii].Normal[j][1] * U_y_bound) * vectorElement[ii].Length_face_el[j];
            temp += (vectorElement[ii].Normal[j][0] * U_x_bound + vectorElement[ii].Normal[j][1] * U_y_bound) * vectorElement[ii].Length_face_el[j];
        }

    return temp;
}

void Calculation_Pressure_P()
{

    string _path = "Documents/Figure/El = " + to_string(max_el);
    /*ofstream test_1(_path + "/1. divU_(El = " + to_string(max_el) + ").DAT", ios_base::trunc);
    ofstream test_2(_path + "/1. P_correction_procedure_(El = " + to_string(max_el) + ").DAT", ios_base::trunc);
    ofstream test_3(_path + "/1. Field_Corretion_(El = " + to_string(max_el) + ").DAT", ios_base::trunc);*/

    double* divU_temp = new double[max_el];

    /* ��������� �������� �������� */
    for (int i = 1; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 2)
        {
            vectorElement[i].P_Correction = 0.0;
            divU_temp[i] = divU(i);
            //test_1 << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t " << divU_temp[i] << " \t " << endl;
        }
    }

    double E_Press = 1.0;
    int E_Press_num_el = 0;
    int Iter_P = 0;

    /*test_3 << fixed << setprecision(10) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "vectorElement[i].P" << " \t " << "vectorElement[i].P_Correction" << " \t "
        << "vectorElement[i].U_x" << " \t " << "vectorElement[i].U_x_Correction" << " \t "
        << "vectorElement[i].U_y" << " \t " << "vectorElement[i].U_y_Correction" << " \t " << endl;*/

    /* ������ �������� �������� */
    while (E_Press > 0.0001)
    {
        //Redistricting_gradP_Corr();

        E_Press = 0.0;
        Iter_P++;
        maxP_Corr = 0.0;

        /* ���������� �������� �������� */
        for (int i = 1; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {
                double cp = 0.0;
                double sum = 0.0;
                for (int j = 0; j < 3; j++)
                {
                    double tmp_cp_1, tmp_cp_2;
                    if (vectorElement[i].Neighb_el[j] != -1)
                    {
                        int i_nb = vectorElement[i].Neighb_el[j];
                        double AA = beta(i, j) * vectorElement[i].Area_el / vectorElement[i].A_0 + (1 - beta(i, j)) * vectorElement[i_nb].Area_el / vectorElement[i_nb].A_0;
                        /*int jj_temp = j + 1;
                        if (j + 1 == 3) jj_temp = 0;
                        double x_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].x + vectorElement[i].Coord_vert[j].x);
                        double y_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].y + vectorElement[i].Coord_vert[j].y);
                        double Px, Py, Nx, Ny, xc, yc, nx, ny, xm, ym;

                        //���� ���������� ����� N � P
                        {
                            xm = x_ik, ym = y_ik;
                            xc = vectorElement[i_nb].Coord_center_el.x, yc = vectorElement[i_nb].Coord_center_el.y;
                            nx = vectorElement[i].Normal[j][0], ny = vectorElement[i].Normal[j][1];

                            Py = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                            Px = (Py - ym) * nx / ny + xm;

                            xc = vectorElement[i].Coord_center_el.x, yc = vectorElement[i].Coord_center_el.y;

                            Ny = ym * nx * nx + ny * (xc * nx + yc * ny - xm * nx);
                            Nx = (Ny - ym) * nx / ny + xm;

                        }

                        double P_Corr_pi = Section_value_MUSCL(Px, Py, "P'");
                        double t_0_x = Nx - vectorElement[i].Coord_center_el.x, t_0_y = Ny - vectorElement[i].Coord_center_el.y;
                        double scal_0_P_Corr = vectorElement[i].gradP_Corr[0] * t_0_x + vectorElement[i].gradP_Corr[1] * t_0_y;
                        double P_Corr_result = P_Corr_pi - scal_0_P_Corr;
                        tmp_cp_1 = -vectorElement[i].Length_face_el[j] * AA * P_Corr_result / (vectorElement[i].h[j] + vectorElement[i_nb].h[j]);
                        */
                        tmp_cp_1 = -vectorElement[i].Length_face_el[j] * AA / (vectorElement[i].h[j] + vectorElement[i_nb].h[j]);
                        tmp_cp_2 = -vectorElement[i].Length_face_el[j] * AA / (vectorElement[i].h[j] + vectorElement[i_nb].h[j]);
                        cp += tmp_cp_2;
                        sum += tmp_cp_1 * vectorElement[i_nb].P_Correction;
                    }
                }

                double tmp_pp = (sum + divU_temp[i]) / cp;

                if (E_Press < abs(vectorElement[i].P_Correction - tmp_pp))
                {
                    E_Press = abs(vectorElement[i].P_Correction - tmp_pp);
                    E_Press_num_el = vectorElement[i].Num_el;
                }

                vectorElement[i].P_Correction = tmp_pp;

                if (abs(vectorElement[i].P_Correction) > maxP_Corr)
                {
                    maxP_Corr = abs(vectorElement[i].P_Correction);
                    maxP_Cor_num_el = vectorElement[i].Num_el;
                }

                if (abs(divU_temp[i]) > maxdivU)
                {
                    maxdivU = abs(divU_temp[i]);
                    maxdivU_num_el = vectorElement[i].Num_el;
                }

                i = i;

            }

        }

        /*test_2 << fixed << setprecision(10) << Iter_P << "\t" << maxP_Corr << "\t" << maxP_Cor_num_el
            << "\t" << E_Press << "\t" << E_Press_num_el << endl;*/

        if (Iter_P >= 400) break;
    }

    double test = 0.0;

    /* ������ �������� �������� */
    {
        /* ��������� ��������� ��������*/
        double U_x_Corr_1 = 0, U_x_Corr_2 = 0, U_x_Corr_3 = 0;
        double U_y_Corr_1 = 0, U_y_Corr_2 = 0, U_y_Corr_3 = 0;

        double maxU_x_Corr = 0.0, maxU_y_Corr = 0.0;
        int maxU_x_Corr_num_el = 0, maxU_y_Corr_num_el = 0;

        for (int i = 1; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {
                double sum_x = 0.0, sum_y = 0.0;

                for (int j = 0; j < 3; j++)
                {
                    double tmp_c_U_x, tmp_c_U_y, tmp_p_0_i;
                    int ii = vectorElement[i].Neighb_el[j];
                    double tmp_bet = 1;
                    if (ii != -1) tmp_bet = beta(i, j);
                    if (ii == -1) ii = i;
                    tmp_p_0_i = tmp_bet * vectorElement[i].P_Correction + (1 - tmp_bet) * vectorElement[ii].P_Correction;
                    tmp_c_U_x = vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                    tmp_c_U_y = vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];
                    sum_x += tmp_c_U_x * tmp_p_0_i;
                    sum_y += tmp_c_U_y * tmp_p_0_i;
                }

                vectorElement[i].U_x_Correction = -sum_x / vectorElement[i].A_0;
                vectorElement[i].U_y_Correction = -sum_y / vectorElement[i].A_0;

                vectorElement[i].U_x = vectorElement[i].U_x + vectorElement[i].U_x_Correction;
                vectorElement[i].U_y = vectorElement[i].U_y + vectorElement[i].U_y_Correction;
                vectorElement[i].P = vectorElement[i].P + 0.25 * vectorElement[i].P_Correction;

                /*test_3 << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                    << vectorElement[i].P << " \t " << vectorElement[i].P_Correction << " \t "
                    << vectorElement[i].U_x << " \t " << vectorElement[i].U_x_Correction << " \t "
                    << vectorElement[i].U_y << " \t " << vectorElement[i].U_y_Correction << " \t " << endl;*/

                i = i;

            }

        }

        double test = 0.0;

    }
    delete[] divU_temp;
}

void Development()
{

    E_U = 0.0;

    double U, u;

    for (int i = 1; i < vectorElement.size(); i++)
    {

        U = sqrt(pow(vectorElement[i].U_x, 2.0) + pow(vectorElement[i].U_y, 2.0));
        u = sqrt(pow(vectorElement[i].u_x, 2.0) + pow(vectorElement[i].u_y, 2.0));

        if (vectorElement[i].Geom_el == 2 && E_U < fabs((U - u) / U))
        {

            E_U = fabs((U - u) / U);
            E_U_Num_el = vectorElement[i].Num_el;

            double debug = fabs((U - u) / U);
            i = i;

        }

        /*if (vectorElement[i].Geom_el == 2 && E_U_x < fabs(vectorElement[i].U_x - vectorElement[i].u_x) / vectorElement[i].U_x)
        {

            E_U_x = fabs(vectorElement[i].U_x - vectorElement[i].u_x) / vectorElement[i].U_x;
            E_U_x_abs = fabs(vectorElement[i].U_x - vectorElement[i].u_x);
            E_U_x_Num_el = vectorElement[i].Num_el;

            i = i;

        }

        if (vectorElement[i].Geom_el == 2 && E_U_y < fabs(vectorElement[i].U_y - vectorElement[i].u_y) / vectorElement[i].U_y)
        {

            E_U_y = fabs(vectorElement[i].U_y - vectorElement[i].u_y) / vectorElement[i].U_y;
            E_U_y_abs = fabs(vectorElement[i].U_y - vectorElement[i].u_y);
            E_U_y_Num_el = vectorElement[i].Num_el;

        }*/

    }

    double debug = 0.0;

    //if (E_U_y_Num_el <= E_U_x_Num_el)
    //{
    //    E_U_y_Num_el = E_U_x_Num_el;
    //    E_U_y_Num_el = E_U_x_Num_el;
    //}

}

void Stream_Function()
{

    /* ��������� ������� */
    for (int i = 1; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 2)
        {
            vectorElement[i].Psi = 0.0;
        }
    }

    double E_Stream = 0.0;

    /* ���������� ������� ���� */
    do
    {
        E_Stream = 0.0;
        for (int i = 1; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {

                double S_Psi = 0.0, S_Ux = 0.0, S_Uy = 0.0, S_dS = 0.0;

                for (int j = 0; j < 3; j++)
                {

                    int jj_temp = j + 1;
                    if (j + 1 == 3) jj_temp = 0;

                    double x_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].x + vectorElement[i].Coord_vert[j].x);
                    double y_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].y + vectorElement[i].Coord_vert[j].y);

                    if (vectorElement[i].Neighb_el[j] != -1)
                    {
                        int i_nb = vectorElement[i].Neighb_el[j];
                        double HH = vectorElement[i].h[j] + vectorElement[i_nb].h[j];

                        S_Psi += vectorElement[i_nb].Psi * vectorElement[i].Length_face_el[j] / HH;
                        S_Ux += Section_value_MUSCL_Face(x_ik, y_ik, "U_x", i) * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];
                        S_Uy += Section_value_MUSCL_Face(x_ik, y_ik, "U_y", i) * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                        S_dS += vectorElement[i].Length_face_el[j] / HH;
                    }

                    else if (vectorElement[i].Num_bound == out_1 || vectorElement[i].Num_bound == out_2)
                    {
                        double HH = 2.0 * vectorElement[i].h[j];
                        S_dS += vectorElement[i].Length_face_el[j] / HH;
                        S_Ux += -vectorElement[i].Normal[j][1] * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];
                        S_Uy += vectorElement[i].Normal[j][0] * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                        S_Psi += (vectorElement[i].Psi + HH) * vectorElement[i].Length_face_el[j] / HH;
                    }
                    else if (vectorElement[i].Num_bound != 0)
                    {
                        double HH = 2.0 * vectorElement[i].h[j];
                        S_dS += vectorElement[i].Length_face_el[j] / HH;
                        S_Psi += (-vectorElement[i].Psi) * vectorElement[i].Length_face_el[j] / HH;
                    }

                }

                double Psi_temp = (S_Psi + S_Ux - S_Uy) / S_dS;

                if (E_Stream < abs(vectorElement[i].Psi - Psi_temp))
                {
                    E_Stream = abs(vectorElement[i].Psi - Psi_temp);
                }

                vectorElement[i].Psi = 0.2 * vectorElement[i].Psi + 0.8 * Psi_temp;

            }
        }
    } while (E_Stream >= 1e-4); // 1e-8

}

void Dissipative_Function()
{

    string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el);
    ofstream Field_Q(_path + "/1. Field_Q_(El = " + to_string(max_el) + ").DAT");

    Field_Q << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "Q" << "\t" << "Q_analytic " << "\t" << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;

    /* ���������� ������� ����������� Q */
    for (int i = 1; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 2)
        {

            double U_ik_x = 0.0, U_ik_y = 0.0;
            double U_ik_x_nx = 0.0, U_ik_y_ny = 0.0;
            double U_ik_x_ny = 0.0, U_ik_y_nx = 0.0;

            for (int j = 0; j < 3; j++)
            {

                int jj_temp = j + 1;
                if (j + 1 == 3) jj_temp = 0;

                double x_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].x + vectorElement[i].Coord_vert[j].x);
                double y_ik = 0.5 * (vectorElement[i].Coord_vert[jj_temp].y + vectorElement[i].Coord_vert[j].y);

                if (vectorElement[i].Neighb_el[j] != -1)
                {
                    U_ik_x = Section_value_MUSCL_Face(x_ik, y_ik, "U_x", i);
                    U_ik_y = Section_value_MUSCL_Face(x_ik, y_ik, "U_y", i);

                    U_ik_x_nx += U_ik_x * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                    U_ik_y_ny += U_ik_y * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];

                    U_ik_x_ny += U_ik_x * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];
                    U_ik_y_nx += U_ik_y * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                }
                else
                {
                    U_ik_x = Value_bound(x_ik, y_ik, i, j, "U_x");
                    U_ik_y = Value_bound(x_ik, y_ik, i, j, "U_y");

                    U_ik_x_nx += U_ik_x * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                    U_ik_y_ny += U_ik_y * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];

                    U_ik_x_ny += U_ik_x * vectorElement[i].Normal[j][1] * vectorElement[i].Length_face_el[j];
                    U_ik_y_nx += U_ik_y * vectorElement[i].Normal[j][0] * vectorElement[i].Length_face_el[j];
                }
                

            }

            vectorElement[i].Q = 2 * (U_ik_x_nx * U_ik_x_nx + U_ik_y_ny * U_ik_y_ny) + pow(U_ik_x_ny + U_ik_y_nx, 2);

            double r = sqrt(pow(vectorElement[i].Coord_center_el.x, 2) + pow(vectorElement[i].Coord_center_el.y, 2));
            //double Q_analytic = pow((r / 0.96 * (1 + 0.04 / r / r)), 2);
            double Q_analytic = 4 * pow(1.0 / 12.0 * 1 / r / r, 2);

            Field_Q << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].Q / vectorElement[i].Area_el / vectorElement[i].Area_el << " \t "<< Q_analytic << " \t " << vectorElement[i].Num_el << endl;
        }
    }

    Field_Q.close();
}

void Approximation_Accuracy(bool activate)
{
    if (activate == true)
    {

        double R = 0.0;     // ����� �������� ��������� �����������
        double l = 0.0;     // ����� ���� ������ ��
        double S = 0.0;     // ����� �������� ��
        int n1 = 0.0;       // ���������� ������ ��
        int n2 = 0.0;       // ���������� ��

        double max_R = 0.0;
        double max_l = 0.0;
        double max_S = 0.0;

        int test1 = 0;
        int test2 = 0;

        double Q_Int = 0.0; // ����� ������������� �������

        for (int i = 1; i < max_el; i++)
        {
            if (vectorElement[i].Geom_el == 2)
            {
                ++n2;
                R += vectorElement[i].h[0];
                if (max_R < vectorElement[i].h[0])
                {
                    max_R = vectorElement[i].h[0];
                }

                S += vectorElement[i].Area_el;
                if (max_S < vectorElement[i].Area_el)
                {
                    max_S = vectorElement[i].Area_el;
                }

                for (int j = 0; j < 3; j++)
                {
                    int jj_temp = j + 1;
                    if (j + 1 == 3) jj_temp = 0;
                    
                    if (vectorElement[i].Neighb_el[j] != -1)
                    {
                        ++n1;
                        ++test1;
                        l += vectorElement[i].Length_face_el[j];
                    }
                    else
                    {
                        ++test2;
                        n1 += 2;
                        l += 2 * vectorElement[i].Length_face_el[j];
                    }

                    if (max_l < vectorElement[i].Length_face_el[j])
                    {
                        max_l = vectorElement[i].Length_face_el[j];
                    }
                }

                Q_Int += vectorElement[i].Q / vectorElement[i].Area_el /*/ vectorElement[i].Area_el*/;

            }
        }

        double h1 = 0.5 * l / n1;
        double h2 = 2.0 * R / n2;
        double h3 = sqrt(S / n2);

        string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el);
        ofstream Field_Approx(_path + "/3. Table_Approx_(El = " + to_string(max_el) + ").DAT");

        Field_Approx << fixed << setprecision(4) << "N (Mesh)" << " \t " << "h1 (face)" << " \t " << "h2 (radius)" << " \t " 
            << "h3 (area)" << " \t " << "Max (h1)" << " \t " << "Max (h2)" << "\t" << "Max (h3)" << "\t" << "Ux" 
            << "\t" << "�" << "\t" << "�_an" << "\t" << "�_Integral" << "\t" << "�_Integral_an" << "\t\t\t" << "Time: " << _time << "\t" << "x: " << xx_1 << "\t" << "y: " << yy_1 << endl;
        
        double r = sqrt(vectorElement[num_el_1].Coord_center_el.x * vectorElement[num_el_1].Coord_center_el.x + vectorElement[num_el_1].Coord_center_el.y * vectorElement[num_el_1].Coord_center_el.y);
        double Q_analytic = 4 * pow(1.0 / 12.0 * 1 / r / r, 2);

        Field_Approx << fixed << setprecision(10) << max_el << " \t " << h1 << " \t " << h2 << " \t " << h3 << " \t "
            << max_l << " \t " << 2 * max_R << " \t " << max_S << " \t " << Section_value_MUSCL(xx_1, yy_1, "U_x") << " \t " 
            << vectorElement[num_el_1].Q / vectorElement[num_el_1].Area_el / vectorElement[num_el_1].Area_el << "\t" 
            << Q_analytic << "\t" << Q_Int << "\t" << endl;
    }
}

void Flow_Evolution(string param) {

    string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Flow Evolution";
    CreateDirectoryA(_path.c_str(), NULL);
    
    if (param == "line")
    {
        string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Flow Evolution/Fixed Profile";
        CreateDirectoryA(_path.c_str(), NULL);

        double h = 0.05;

        /* �������� ������� */
        if (Iter_Glob == 1)
        {

            int ii = 0;
            
            do
            {

                double r = R0 + ii * h;
                double angle = 45 * Pi / 180;

                x_m.push_back(r * cos(angle));
                y_m.push_back(r * sin(angle));

                ii++;

            } while ((0.2 + ii * h) <= 1.0);

            count_marker = x_m.size();
        }

        /* ������ � ���� */
        if (Iter_Glob % 50 == 0 || Iter_Glob == 1)
        {
            int temp_time = Iter_Glob;
            ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::trunc);
            Flow_Evo << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;
            Flow_Evo_test << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;

            for (int i = 0; i < count_marker; i++)
            {

                ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::app);
                ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::app);
                Flow_Evo << fixed << setprecision(6) << x_m[i] << "\t" << y_m[i] << "\t" << i << endl;
                Flow_Evo_test << fixed << setprecision(6) << x_m[i] << "\t" << y_m[i] << "\t" << i << endl;

                i = i;
            }

            double debug = 0.0;
        }

        /* �������� ���� */
        for (int i = count_marker - 1; i >= 0; i--)
        {

            double debug_1 = Section_value_MUSCL(x_m[i], y_m[i], "U_x");
            double debug_2 = Section_value_MUSCL(x_m[i], y_m[i], "U_y");

            double x_tmp_n = x_m[i] + Section_value_MUSCL(x_m[i] + 0.5 * debug_1 * dt_m, y_m[i] + 0.5 * debug_2 * dt_m, "U_x") * dt_m;
            double y_tmp_n = y_m[i] + Section_value_MUSCL(x_m[i] + 0.5 * debug_1 * dt_m, y_m[i] + 0.5 * debug_2 * dt_m, "U_y") * dt_m;

            /*Section_value_MUSCL(x_m[i], y_m[i], "NULL");

            double debug = num_el_1;
            for (int j = 0; j < 3; j++)
            {
                if (vectorElement[num_el_1].Neighb_el[j] == -1)
                {
                    double debug_1 = Value_bound(x_m[i], y_m[i], num_el_1, j, "U_x");
                    double debug_2 = Value_bound(x_m[i], y_m[i], num_el_1, j, "U_y");

                    x_tmp_n = x_m[i] + Value_bound(x_m[i], y_m[i], num_el_1, j, "U_x") * dt_m;
                    y_tmp_n = y_m[i] + Value_bound(x_m[i], y_m[i], num_el_1, j, "U_y") * dt_m;

                }
            }*/

            /*double x_tmp_n_1 = x_tmp_n + 1.5 * Section_value_MUSCL(x_tmp_n, y_tmp_n, "U_x") * dt_m - 0.5 * Section_value_MUSCL(x_m[i], y_m[i], "U_x") * dt_m;
            double y_tmp_n_1 = y_tmp_n + 1.5 * Section_value_MUSCL(x_tmp_n, y_tmp_n, "U_y") * dt_m - 0.5 * Section_value_MUSCL(x_m[i], y_m[i], "U_y") * dt_m;

            double Ux_test = Section_value_MUSCL(x_m[i], y_m[i], "U_x");
            double Uy_test = Section_value_MUSCL(x_m[i], y_m[i], "U_y");*/

            /*double xm_1 = Section_value_MUSCL(x_m[i], y_m[i], "U_x") * dt_m;
            double ym_1 = Section_value_MUSCL(x_m[i], y_m[i], "U_y") * dt_m;

            double xm_2 = Section_value_MUSCL((x_m[i] + dt_m / 3.0), (y_m[i] + xm_1 / 3.0), "U_x") * dt_m;
            double ym_2 = Section_value_MUSCL((x_m[i] + dt_m / 3.0), (y_m[i] + ym_1 / 3.0), "U_y") * dt_m;

            double xm_3 = Section_value_MUSCL((x_m[i] + dt_m / 3.0), (y_m[i] + xm_1 / 6.0 + xm_2 / 6.0), "U_x") * dt_m;
            double ym_3 = Section_value_MUSCL((x_m[i] + dt_m / 3.0), (y_m[i] + ym_1 / 6.0 + ym_2 / 6.0), "U_y") * dt_m;

            double xm_4 = Section_value_MUSCL((x_m[i] + dt_m / 2.0), (y_m[i] + xm_1 / 8.0 + 3 * xm_3 / 8.0), "U_x") * dt_m;
            double ym_4 = Section_value_MUSCL((x_m[i] + dt_m / 2.0), (y_m[i] + ym_1 / 8.0 + 3 * ym_3 / 8.0), "U_y") * dt_m;

            double xm_5 = Section_value_MUSCL(x_m[i + 1], (y_m[i] + xm_1 / 2.0 - 3 * xm_3 / 2.0 + 2 * xm_4), "U_x") * dt_m;
            double ym_5 = Section_value_MUSCL(x_m[i + 1], (y_m[i] + ym_1 / 2.0 - 3 * ym_3 / 2.0 + 2 * ym_4), "U_y") * dt_m;

            double x_tmp_n_1 = x_m[i] + 1.0 / 6.0 * (xm_1 + 4 * xm_4 + xm_5);
            double y_tmp_n_1 = y_m[i] + 1.0 / 6.0 * (ym_1 + 4 * ym_4 + ym_5);*/

            x_m[i] = x_tmp_n;
            y_m[i] = y_tmp_n;

        }

        /* ���������� �������� */
        for (int i = 1; i < count_marker; i++)
        {

            double dx = (x_m[i] - x_m[i - 1]) * (x_m[i] - x_m[i - 1]);
            double dy = (y_m[i] - y_m[i - 1]) * (y_m[i] - y_m[i - 1]);

            double ds = sqrt(dx + dy);

            if (ds > h + 0.01)
            {
                x_m.resize(x_m.size() + 1);
                y_m.resize(x_m.size() + 1);

                // �������� �� i + 1 �� count_marker ������ �� 1
                for (int j = count_marker; j >= i + 1; j--)
                {

                    x_m[j] = x_m[j - 1];
                    y_m[j] = y_m[j - 1];

                }

                // ������� ������ �������
                x_m[i] = 0.5 * (x_m[i - 1] + x_m[i]);
                y_m[i] = 0.5 * (y_m[i - 1] + y_m[i]);

                count_marker++;

            }

        }
    }

    if (param == "array")
    {
        string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Flow Evolution/Marker Array";

        ofstream Integral_Char;
        double integral_char_N1 = 0.0;
        double integral_char_N2 = 0.0;
        int all_marker = 0;

        /* �������� ������� */
        if (Iter_Glob == 1)
        {
            CreateDirectoryA(_path.c_str(), NULL);
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::trunc);
            Integral_Char << "time\t" << "gamma\t" << "N1\t" << "N2\t" << "\t\t" << "Re = " << Re << endl;

            int eps = 0;
            double h = 0.025;
            double angle = -1.0;
            double r = 0.0;

            do
            {
                x_m.clear();
                y_m.clear();

                int ii = 0;

                do
                {

                    /*double r = R0 + ii * h;
                    double angle = ((270 + eps) * Pi / 180);

                    double check_x = r * cos(angle);
                    double check_y = r * sin(angle);*/
                                        
                    double check_x = r;
                    double check_y = angle;

                    Section_value_MUSCL(check_x, check_y, "NULL");

                    if (vectorElement[num_el_1].Num_bound == calc)
                    {
                        x_m.push_back(check_x);
                        y_m.push_back(check_y);

                    }

                    ii++;
                    r = ii * h;

                } while (ii * h < 1.0);

                x_ang.push_back(x_m);
                y_ang.push_back(y_m);

                eps++;
                angle = -1.0 + eps * h;

            } while (angle < 1.0);
                       
            count_angle = x_ang.size();
            count_marker = x_m.size();
        }

        /* ������ � ���� */
        if (Iter_Glob % 50 == 0 || Iter_Glob == 1)
        {
            int temp_time = Iter_Glob;
            ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::trunc);
            Flow_Evo << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;
            Flow_Evo_test << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;

            for (int j = 0; j < x_ang.size(); j++)
            {
                for (int i = 0; i < x_ang[j].size(); i++)
                {

                    ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::app);
                    ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::app);
                    Flow_Evo << fixed << setprecision(6) << x_ang[j][i] << "\t" << y_ang[j][i] << "\t" << i << "\t" << j << endl;
                    Flow_Evo_test << fixed << setprecision(6) << x_ang[j][i] << "\t" << y_ang[j][i] << "\t" << i << "\t" << j << endl;

                    i = i;
                }

                j = j;
            }   

            double debug = 0.0;
        }

        /* �������� ���� */
        for (int j = 0; j < x_ang.size(); j++)
        {
            for (int i = 0; i < x_ang[j].size(); i++)
            {

                /* ����� ����������
                1.��������� ��������� ������������ dot �� �� CV_marker & coord_marker
                2. if (dot false) {����� ������ ������������ ������ � ��������������� CV_marker[i]}
                    - ����� �� ���� ���������;
                    - ����� �� ��, ����������� �� ������� ��������
                3. Section_value_MUSCL____________________(coord_marker[i][0], coord_marker[i][1], "___",CV_marker[i] )
                */
                
                
                double debug_1 = Section_value_MUSCL(x_ang[j][i], y_ang[j][i], "U_x");
                double debug_2 = Section_value_MUSCL(x_ang[j][i], y_ang[j][i], "U_y");

                double x_tmp_n = x_ang[j][i] + Section_value_MUSCL(x_ang[j][i] + 0.5 * debug_1 * dt_m, y_ang[j][i] + 0.5 * debug_2 * dt_m, "U_x") * dt_m;
                double y_tmp_n = y_ang[j][i] + Section_value_MUSCL(x_ang[j][i] + 0.5 * debug_1 * dt_m, y_ang[j][i] + 0.5 * debug_2 * dt_m, "U_y") * dt_m;

                /*double debug_1_new = Section_value_MUSCL_Flow_Evo(x_ang[j][i], y_ang[j][i], all_marker, "U_x");
                double debug_2_new = Section_value_MUSCL_Flow_Evo(x_ang[j][i], y_ang[j][i], all_marker, "U_y");

                if (debug_1_old != debug_1) {
                    throw runtime_error("debug_1_old should be equal to debug_1");
                }

                double x_tmp_n = x_ang[j][i] + Section_value_MUSCL_Flow_Evo(x_ang[j][i] + 0.5 * debug_1_new * dt_m, y_ang[j][i] + 0.5 * debug_2_new * dt_m, all_marker, "U_x") * dt_m;
                double y_tmp_n = y_ang[j][i] + Section_value_MUSCL_Flow_Evo(x_ang[j][i] + 0.5 * debug_1_new * dt_m, y_ang[j][i] + 0.5 * debug_2_new * dt_m, all_marker, "U_y") * dt_m*/;


                all_marker++;

                /* ������ ������������ �������������� */
                {
                    if ((x_ang[j][i] > 0 && y_ang[j][i] > 0))
                    {
                        integral_char_N1++;
                        i = i;
                    }

                    if ((x_ang[j][i] < 0 && y_ang[j][i] < 0))
                    {
                        integral_char_N2++;
                        i = i;
                    }
                }               

                x_ang[j][i] = x_tmp_n;
                y_ang[j][i] = y_tmp_n;

                i = i;
            }

            j = j;
        }


        if (Iter_Glob % 200 == 0 || Iter_Glob == 1) 
        {
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::app);
            double integral_char = abs(integral_char_N1 - integral_char_N2) / (integral_char_N1 + integral_char_N2);
            Integral_Char << _time_Flow_Evolution << "\t" << integral_char << "\t" << integral_char_N1 << "\t" << integral_char_N2 << endl;

            double debug = 0.0;
        }
    }
}

void Save_Write() 
{

    string _path = "Documents/Save/Re=" + to_string(Re) + "/El = " + to_string(max_el);
    CreateDirectoryA(_path.c_str(), NULL);

    ofstream File_Save(_path + "/Save_(El=" + to_string(max_el) + ").DAT", ios_base::trunc);
    File_Save << fixed << setprecision(25) << _time << "\t" << max_el << "\t" << max_node << "\t" << max_str << endl;
    File_Save << fixed << setprecision(25) << Re << "\t" << num_el_1 << "\t" << num_el_2 << "\t" << num_el_3 << endl;
    File_Save << fixed << setprecision(25) << num_el_1_MUSCL << "\t" << xx_1 << "\t" << yy_1 << "\t" << E_U << "\t" << E_U_Num_el << endl;
    File_Save << fixed << setprecision(25) << maxP_Corr << "\t" << maxP_Cor_num_el << "\t" << maxdivU << "\t" << maxdivU_num_el << "\t" << dt << endl;

    /* ������ ��������� ����� */
    for (int i = 0; i < max_node; i++)
    {

        File_Save << fixed << setprecision(25) << vectorPoint[i].Num_node << "\t" << vectorPoint[i].Boundary << "\t" << vectorPoint[i].x << "\t" << vectorPoint[i].y << endl;

    }

    /* ������ ���������� ��������� */
    for (int i = 0; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 15)
        {
            File_Save << fixed << setprecision(25) << vectorElement[i].Num_el << "\t" << vectorElement[i].Geom_el << "\t" << vectorElement[i].Num_bound << "\t" << vectorElement[i].Num_vert[0] << "\t" << vectorElement[i].Num_vert[1] << "\t" << vectorElement[i].Num_vert[2] << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].U_x << "\t" << vectorElement[i].U_y << "\t" << vectorElement[i].P << "\t" << vectorElement[i].u_x << "\t" << vectorElement[i].u_y << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Coord_vert[0].x << "\t" << vectorElement[i].Coord_vert[0].y << "\t" << vectorElement[i].Coord_vert[1].x << "\t" << vectorElement[i].Coord_vert[1].y << "\t" << vectorElement[i].Coord_vert[2].x << "\t" << vectorElement[i].Coord_vert[2].y << endl;
        }

        if (vectorElement[i].Geom_el == 1)
        {
            File_Save << fixed << setprecision(25) << vectorElement[i].Num_el << "\t" << vectorElement[i].Geom_el << "\t" << vectorElement[i].Num_bound << "\t" << vectorElement[i].Num_vert[0] << "\t" << vectorElement[i].Num_vert[1] << "\t" << vectorElement[i].Num_vert[2] << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].U_x << "\t" << vectorElement[i].U_y << "\t" << vectorElement[i].P << "\t" << vectorElement[i].u_x << "\t" << vectorElement[i].u_y << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Coord_vert[0].x << "\t" << vectorElement[i].Coord_vert[0].y << "\t" << vectorElement[i].Coord_vert[1].x << "\t" << vectorElement[i].Coord_vert[1].y << "\t" << vectorElement[i].Coord_vert[2].x << "\t" << vectorElement[i].Coord_vert[2].y << endl;
        }

        if (vectorElement[i].Geom_el == 2)
        {
            File_Save << fixed << setprecision(25) << vectorElement[i].Num_el << "\t" << vectorElement[i].Geom_el << "\t" << vectorElement[i].Num_bound << "\t" << vectorElement[i].Num_vert[0] << "\t" << vectorElement[i].Num_vert[1] << "\t" << vectorElement[i].Num_vert[2] << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].U_x << "\t" << vectorElement[i].U_y << "\t" << vectorElement[i].P << "\t" << vectorElement[i].u_x << "\t" << vectorElement[i].u_y << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Coord_vert[0].x << "\t" << vectorElement[i].Coord_vert[0].y << "\t" << vectorElement[i].Coord_vert[1].x << "\t" << vectorElement[i].Coord_vert[1].y << "\t" << vectorElement[i].Coord_vert[2].x << "\t" << vectorElement[i].Coord_vert[2].y << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Length_face_el[0] << "\t" << vectorElement[i].Length_face_el[1] << "\t" << vectorElement[i].Length_face_el[2] << "\t" << vectorElement[i].Area_el << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Coord_center_el.x << "\t" << vectorElement[i].Coord_center_el.y << "\t" << vectorElement[i].h[0] << "\t" << vectorElement[i].h[1] << "\t" << vectorElement[i].h[2] << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Neighb_el[0] << "\t" << vectorElement[i].Neighb_el[1] << "\t" << vectorElement[i].Neighb_el[2] << "\t" << vectorElement[i].Normal[0][0] << "\t" << vectorElement[i].Normal[1][0] << "\t" << vectorElement[i].Normal[2][0] << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].Normal[0][1] << "\t" << vectorElement[i].Normal[1][1] << "\t" << vectorElement[i].Normal[2][1] << "\t" << vectorElement[i].gradU_x[0] << "\t" << vectorElement[i].gradU_x[1] << "\t" << vectorElement[i].gradU_y[0] << "\t" << vectorElement[i].gradU_y[1] << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].gradP[0] << "\t" << vectorElement[i].gradP[1] << "\t" << vectorElement[i].gradP_Corr[0] << "\t" << vectorElement[i].gradP_Corr[1] << "\t" << vectorElement[i].t << "\t" << vectorElement[i].T << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].alfa << "\t" << vectorElement[i].Alfa << "\t" << vectorElement[i].dalfa << "\t" << vectorElement[i].u_x << "\t" << vectorElement[i].u_y << "\t" << vectorElement[i].U_x << "\t" << vectorElement[i].U_y << endl;
            File_Save << fixed << setprecision(25) << vectorElement[i].P_Correction << "\t" << vectorElement[i].A_0 << "\t" << vectorElement[i].U_x_Correction << "\t" << vectorElement[i].U_y_Correction << "\t" << vectorElement[i].Psi << endl;

        }
        
    }

    File_Save << fixed << setprecision(15) << File_Mesh_Name << endl;

    File_Save.close();

}

void Write_Figure()
{
    string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el);

    ofstream Field_U_x(_path + "/1. Field_U_x_(El = " + to_string(max_el) + ").DAT");
    ofstream Field_U_y(_path + "/1. Field_U_y_(El = " + to_string(max_el) + ").DAT");
    ofstream Field_U_eps(_path + "/1. Field_U_eps_(El = " + to_string(max_el) + ").DAT");
    ofstream Field_P(_path + "/1. Field_P_(El = " + to_string(max_el) + ").DAT");
    ofstream Field_Psi(_path + "/1. Field_Psi_(El = " + to_string(max_el) + ").DAT");
    ofstream Profile_P_MUSCL(_path + "/2. Profile_P_MUSCL_(El = " + to_string(max_el) + ").DAT");
    ofstream Profile_U_x_MUSCL(_path + "/2. Profile_U_x_MUSCL_(El = " + to_string(max_el) + ").DAT");
    ofstream Profile_U_y_MUSCL(_path + "/2. Profile_U_y_MUSCL_(El = " + to_string(max_el) + ").DAT");

    Field_U_x << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "U_x_wall" << "\t" << "U_x_obst" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_U_y << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "U_y_wall" << "\t" << "U_y_obst" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_U_eps << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "U_eps_wall" << "\t" << "U_eps_obst" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_P << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "P" << "\t" 
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_Psi << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "Psi" << "\t" << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;

    /* ������ ������������ ����� */
    for (int i = 0; i < max_el; i++)
    {
        double r_temp, U_eps;

        if (vectorElement[i].Geom_el == 2)
        {

            Field_U_x << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].U_x << " \t " << vectorElement[i].U_x + omega_1 * vectorElement[i].Coord_center_el.y << " \t " << vectorElement[i].Num_el << endl;
            Field_U_y << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].U_y << " \t " << vectorElement[i].U_y - omega_1 * vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Num_el << endl;
            Field_P << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].P << " \t " << vectorElement[i].Num_el << endl;
            Field_Psi << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].Psi << " \t " << vectorElement[i].Num_el << endl;
            
            /* ������ ������� �������� � �������������� �� */
            r_temp = pow(vectorElement[i].Coord_center_el.x * vectorElement[i].Coord_center_el.x + vectorElement[i].Coord_center_el.y * vectorElement[i].Coord_center_el.y, 0.5);
            U_eps = vectorElement[i].U_x * r_temp / vectorElement[i].Coord_center_el.y + vectorElement[i].U_y * r_temp / vectorElement[i].Coord_center_el.x;

            Field_U_eps << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << U_eps << " \t " << r_temp << " \t " << vectorElement[i].Num_el << endl;
        }

    }

    /* ������ ����������� ���������� � ������� */
    int ii = 0;
    double h = 0.01;
    do
    {

        double angle = 315 * Pi / 180.0;
        double test_1 = cos(angle);
        double test_2 = sin(angle);

        double x = (0.2 + ii * h) * cos(angle);
        double y = (0.2 + ii * h) * sin(angle);

        Profile_P_MUSCL << fixed << setprecision(9) << 0.2 + ii * h << "\t" << Section_value_MUSCL(x, y, "P") << endl;
        Profile_U_x_MUSCL << fixed << setprecision(9) << 0.2 + ii * h << "\t" << Section_value_MUSCL(x, y, "U_x") << endl;
        Profile_U_y_MUSCL << fixed << setprecision(9) << 0.2 + ii * h << "\t" << Section_value_MUSCL(x, y, "U_y") << endl;

        ii++;

    } while ((0.2 + ii * h) <= 1.0);

    Field_U_x.close();
    Field_U_y.close();
    Profile_U_x_MUSCL.close();
    Profile_U_y_MUSCL.close();
    Profile_P_MUSCL.close();
}

void Write()
{
    if (Iter_Glob == 1)
    {

        cout << fixed << setprecision(5) << "Mesh (Number of elements): " << max_el << endl;
        cout << "The control element: El.num = " << num_el_1 + 1 << ";  " << "Re = " << Re << endl;
        cout << "==============================================================================" << endl;
        cout << " \t" << " \t" << "If everything is correct, then press ENTER" << endl;
        cout << "==============================================================================" << endl;
        cin.get();

    }

    cout << fixed << setprecision(4) << "Time: " << _time << "\t" << setprecision(10)
        << "El=" << num_el_1 + 1 << ":(U_x = " << vectorElement[num_el_1].U_x << "; U_y = " << vectorElement[num_el_1].U_y
        << "; P = " << setprecision(6) << vectorElement[num_el_1].P << ")" << "   " << "Max.Res. = " << E_U << " (El=" << E_U_Num_el << ")" << endl;
        
    if (Iter_Glob == 1 || (Iter_Glob % 500) == 0)
    {
        //Stream_Function();
        Write_Figure();
        Save_Write();
    }

    string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el);
    ofstream development(_path + "/2. development_(El = " + to_string(max_el) + ").DAT", ios_base::app);

    development << _time << "\t" << setprecision(10) << vectorElement[num_el_1].U_x << "\t" << vectorElement[num_el_1].U_y
        << "\t" << vectorElement[num_el_1].P << "\t" << E_U << endl;

    //string _path = "Documents/Figure/El = " + to_string(max_el);
    //ofstream Profile_P_MUSCL(_path + "/2. Profile_P_MUSCL_(El = " + to_string(max_el) + ").DAT");
    //ofstream Profile_U_x_MUSCL(_path + "/2. Profile_U_x_MUSCL_(El = " + to_string(max_el) + ").DAT");
    //ofstream Profile_U_y_MUSCL(_path + "/2. Profile_U_y_MUSCL_(El = " + to_string(max_el) + ").DAT");
    // ������ �������� T � Alfa � �������
    //int ii = 0;
    //double h = 0.1;
    //do
    //{
    //    double x = 0.5;
    //    double y = ii * h;
    //    double test = Section_value_MUSCL(x, y, "P");
    //    Profile_P_MUSCL << fixed << setprecision(9) << ii * h << "\t" << Section_value_MUSCL(x, y, "P") << endl;
    //    Profile_U_x_MUSCL << fixed << setprecision(9) << ii * h << "\t" << Section_value_MUSCL(x, y, "U_x") << endl;
    //    Profile_U_y_MUSCL << fixed << setprecision(9) << ii * h << "\t" << Section_value_MUSCL(x, y, "U_y") << endl;
    //    ii++;
    //} while ((ii * h) <= 1.0);

}

void Write_End()
{

    Dissipative_Function();
    Stream_Function();
    Approximation_Accuracy(true);
    Write_Figure();

    Section_value_MUSCL(xx_1, yy_1, "NULL");

    cout << "===========================================================================" << endl;

    cout << fixed << setprecision(4) << "Time: " << _time << setprecision(10)
        << "\tEl=" << num_el_1 + 1 << ":(U_x = " << vectorElement[num_el_1].U_x << "; U_y = " << vectorElement[num_el_1].U_y
        << "; P = " << setprecision(6) << vectorElement[num_el_1].P << ")" << "   " << "Max.Res. = " << E_U << " (El=" << E_U_Num_el << ")" << endl;

    if (Read_From_Save == false) cout << "Re = " << Re << ";\tThe calculation is OVER: " << endl << File_Mesh_Name << endl;
    if (Read_From_Save == true) cout << "Re = " << Re << ";\tThe calculation is OVER: " << endl << File_Save_Name << endl;

    cout << "===========================================================================" << endl;

    Save_Write();

}

void Time()
{

    _time += dt;
    _time_Flow_Evolution += dt_m;

}




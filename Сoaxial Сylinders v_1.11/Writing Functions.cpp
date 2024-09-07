#include "Variables.h"
#include "Declaration of procedures.h"

void Blank()
{
    /*
    * Процедура записывает бланкировочный файл для мешалки
    */

    int Local_count = 0;
    int Local_it = 0;

    ofstream File_Blank("Documents/Blank/Blank_R0_0.BLN", ios_base::trunc);

    /* Запись заголовка бланкировочного файла */
    for (int i = 1; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 1 && (vectorElement[i].Num_bound != border.out_1 && vectorElement[i].Num_bound != border.out_2
            && vectorElement[i].Num_bound != border.calc))
        {
            Local_it++;
            if (Local_it == 1) Local_count = i;
            i = i;
        }
    }

    File_Blank << Local_it + 1 << "\t" << "1" << endl;
    double teta_0 = 0.0; //(30 * Pi / 180);

    /* Запись коррдинат */
    for (int i = 0; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 1 && (vectorElement[i].Num_bound != border.out_1 && vectorElement[i].Num_bound != border.out_2
            && vectorElement[i].Num_bound != border.calc))
        {
            File_Blank << fixed << setprecision(4) << vectorElement[i].Coord_vert[0].x << " \t " << vectorElement[i].Coord_vert[0].y << endl;
        }
    }

    File_Blank << fixed << setprecision(4) << vectorElement[Local_count].Coord_vert[0].x << " \t " << vectorElement[Local_count].Coord_vert[0].y;

}

void Blank_new(double t = 0.0)
{
    /*
    * Функция записывает файл для мешалки. Предполагается использовать только для движущейся мешалки
    *
    * @param t - параметр, необходимый для расчета угла поворота лопастей. Если t=0, то мешалка будет стоять
    */

    //Создаем директорию
    string _path = "Documents/Blank/Blank Flow Evolution";
    CreateDirectoryA(_path.c_str(), NULL);

    int Local_count = 0;
    int Local_it = 0;
    double debug_x_temp = 0.0;
    double debug_y_temp = 0.0;

    //Создаем отдельный файл с координатами мешалки в момент для каждого момента времени temp_time
    int temp_time = Iter_Glob;
    ofstream File_Blank(_path + "/Blank_R0 " + to_string(temp_time / 10) + ".BLN", ios_base::trunc);
    //Создаем файл с координатами мешалки в момент времени temp_time, который постоянно перезаписывается
    ofstream File_Blank_temp(_path + "/Blank_R0.BLN", ios_base::trunc);

    double teta_0 = 0.0; //(30 * Pi / 180);

    /* Запись коррдинат */
    for (int i = 0; i < max_el; i++)
    {
        if (vectorElement[i].Geom_el == 1 && (vectorElement[i].Num_bound != border.out_1 && vectorElement[i].Num_bound != border.out_2
            && vectorElement[i].Num_bound != border.calc))
        {
            double debug_x = vectorElement[i].Coord_vert[0].x * cos(teta_0 + phi) + vectorElement[i].Coord_vert[0].y * sin(teta_0 + phi);
            double debug_y = -vectorElement[i].Coord_vert[0].x * sin(teta_0 + phi) + vectorElement[i].Coord_vert[0].y * cos(teta_0 + phi);
            double debug_x1 = vectorElement[i].Coord_vert[1].x * cos(teta_0 + phi) + vectorElement[i].Coord_vert[1].y * sin(teta_0 + phi);
            double debug_y1 = -vectorElement[i].Coord_vert[1].x * sin(teta_0 + phi) + vectorElement[i].Coord_vert[1].y * cos(teta_0 + phi);

            if (debug_x != debug_x_temp && Local_it > 0) // Замыкаем фигуру, когда дошли ее начальной точки
            {
                File_Blank_temp << endl;
                File_Blank << endl;
            }

            File_Blank_temp << fixed << setprecision(4) << debug_x << " \t " << debug_y << endl;
            File_Blank_temp << fixed << setprecision(4) << debug_x1 << " \t " << debug_y1 << endl;
            File_Blank << fixed << setprecision(4) << debug_x << " \t " << debug_y << endl;
            File_Blank << fixed << setprecision(4) << debug_x1 << " \t " << debug_y1 << endl;

            debug_x_temp = debug_x1;
            debug_y_temp = debug_y1;

            Local_it++;
        }
    }
}

void Save_Write()
{
    // FIXME: Добавить сохранение нумерации граничных элементов enum Inner_Wall, enum Outer_Wall
    string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Save";
    CreateDirectoryA(_path.c_str(), NULL);

    ofstream File_Save(_path + "/Save_(El=" + to_string(max_el) + ").DAT", ios_base::trunc);
    File_Save << fixed << setprecision(25) << _time << "\t" << max_el << "\t" << max_node << "\t" << max_str << endl;
    File_Save << fixed << setprecision(25) << Re << "\t" << num_el_1 << "\t" << num_el_2 << "\t" << num_el_3 << endl;
    File_Save << fixed << setprecision(25) << num_el_1_MUSCL << "\t" << xx_1 << "\t" << yy_1 << "\t" << E_U << "\t" << E_U_Num_el << endl;
    File_Save << fixed << setprecision(25) << maxP_Corr << "\t" << maxP_Cor_num_el << "\t" << maxdivU << "\t" << maxdivU_num_el << "\t" << dt << endl;

    /* Запись нумерации гарниц */
    File_Save << border.calc << "\t" << border.in_1 << endl;
    File_Save << border.out_1 << "\t" << border.out_2 << endl;

    /* Запись структуры точек */
    for (int i = 0; i < max_node; i++)
    {

        File_Save << fixed << setprecision(25) << vectorPoint[i].Num_node << "\t" << vectorPoint[i].Boundary << "\t" << vectorPoint[i].x << "\t" << vectorPoint[i].y << endl;

    }

    /* Запись струтктуры элементов */
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
    ofstream Field_U_eps(_path + "/1. Field_Ueps_Ur_(El = " + to_string(max_el) + ").DAT");
    ofstream Field_P(_path + "/1. Field_P_(El = " + to_string(max_el) + ").DAT");
    ofstream Field_Psi(_path + "/1. Field_Psi_(El = " + to_string(max_el) + ").DAT");
    ofstream Profile_P_MUSCL(_path + "/2. Profile_P_MUSCL_(El = " + to_string(max_el) + ").DAT");
    ofstream Profile_U_x_MUSCL(_path + "/2. Profile_U_x_MUSCL_(El = " + to_string(max_el) + ").DAT");
    ofstream Profile_U_y_MUSCL(_path + "/2. Profile_U_y_MUSCL_(El = " + to_string(max_el) + ").DAT");

    Field_U_x << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "U_x_wall" << "\t" << "U_x_obst" << "\t" << "U_wall" << "\t" << "U_obst" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_U_y << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "U_y_wall" << "\t" << "U_y_obst" << "\t" << "U_wall" << "\t" << "U_obst" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_U_eps << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "U_eps_wall" << "\t" << "U_r_wall" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_P << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "P" << "\t"
        << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;
    Field_Psi << fixed << setprecision(4) << "Coord_center_el.x" << " \t " << "Coord_center_el.y" << " \t "
        << "Psi" << "\t" << "Time: " << _time << "\t" << "Mesh (Number of cells): " << max_el << endl;

    /* Запись распределния полей */
    for (int i = 0; i < max_el; i++)
    {
        double r_temp, U_eps, U_r;

        if (vectorElement[i].Geom_el == 2)
        {

            double Ux_obst = vectorElement[i].U_x + omega_1 * vectorElement[i].Coord_center_el.y;
            double Uy_obst = vectorElement[i].U_y - omega_1 * vectorElement[i].Coord_center_el.x;

            Field_U_x << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].U_x << " \t " << Ux_obst << " \t "
                << sqrt(vectorElement[i].U_x * vectorElement[i].U_x + vectorElement[i].U_y * vectorElement[i].U_y) << " \t " 
                << sqrt(Ux_obst * Ux_obst + Uy_obst * Uy_obst) << " \t " << vectorElement[i].Num_el << endl;

            Field_U_y << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].U_y << " \t " << Uy_obst << " \t "
                << sqrt(vectorElement[i].U_x * vectorElement[i].U_x + vectorElement[i].U_y * vectorElement[i].U_y) << " \t " 
                << sqrt(Ux_obst * Ux_obst + Uy_obst * Uy_obst) << " \t " << vectorElement[i].Num_el << endl;

            Field_P << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].P << " \t " << vectorElement[i].Num_el << endl;

            Field_Psi << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << vectorElement[i].Psi << " \t " << vectorElement[i].Num_el << endl;

            /* Запись скорости в цилиндрической СК */
            r_temp = pow(vectorElement[i].Coord_center_el.x * vectorElement[i].Coord_center_el.x + vectorElement[i].Coord_center_el.y * vectorElement[i].Coord_center_el.y, 0.5);
            U_r = vectorElement[i].U_x * vectorElement[i].Coord_center_el.x / r_temp + vectorElement[i].U_y * vectorElement[i].Coord_center_el.y / r_temp;
            U_eps = -vectorElement[i].U_x * vectorElement[i].Coord_center_el.y / r_temp + vectorElement[i].U_y * vectorElement[i].Coord_center_el.x / r_temp;

            Field_U_eps << fixed << setprecision(10) << vectorElement[i].Coord_center_el.x << " \t " << vectorElement[i].Coord_center_el.y << " \t "
                << U_eps << " \t " << U_r << " \t " << vectorElement[i].Num_el << endl;
        }

    }

    double section = 0;

    Profile_P_MUSCL << fixed << setprecision(4) << "r" << " \t P" << " \t Time: " << _time << " \t Mesh (Number of cells): " << max_el << "\tAngle: " << section << endl;
    Profile_U_x_MUSCL << fixed << setprecision(4) << "r" << " \t U_x" << " \t U_r" << " \t Time: " << _time << " \t Mesh (Number of cells): " << max_el << "\tAngle: " << section << endl;
    Profile_U_y_MUSCL << fixed << setprecision(4) << "r" << " \t U_y" << " \t U_eps" << " \t Time: " << _time << " \t Mesh (Number of cells): " << max_el << "\tAngle: " << section << endl;

    /* Запись контрольных параметров в сечении */
    int ii = 0;
    double h = 0.01;
    do
    {        
        double angle = section * Pi / 180.0;
        double test_1 = cos(angle);
        double test_2 = sin(angle);

        double x = (R0 + ii * h) * cos(angle);
        double y = (R0 + ii * h) * sin(angle);

        double P = Section_value_MUSCL(x, y, "P");

        /* Скорость в декартовой СК */
        double Ux = Section_value_MUSCL(x, y, "U_x");
        double Uy = Section_value_MUSCL(x, y, "U_y");

        /* Скорость в цилиндрической СК */
        double U_r = Ux * cos(angle) + Uy * sin(angle);
        double U_eps = -Ux * sin(angle) + Uy * cos(angle);


        Profile_P_MUSCL << fixed << setprecision(9) << R0 + ii * h << "\t" << P << endl;
        Profile_U_x_MUSCL << fixed << setprecision(9) << R0 + ii * h << "\t" << Ux << "\t" << U_r << endl;
        Profile_U_y_MUSCL << fixed << setprecision(9) << R0 + ii * h << "\t" << Uy << "\t" << U_eps << endl;

        ii++;

    } while ((R0 + ii * h) <= 1.0);

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
        << "\t" << vectorElement[num_el_1].P << "\t" << E_U << "\t" << omega_1 << endl;

    //string _path = "Documents/Figure/El = " + to_string(max_el);
    //ofstream Profile_P_MUSCL(_path + "/2. Profile_P_MUSCL_(El = " + to_string(max_el) + ").DAT");
    //ofstream Profile_U_x_MUSCL(_path + "/2. Profile_U_x_MUSCL_(El = " + to_string(max_el) + ").DAT");
    //ofstream Profile_U_y_MUSCL(_path + "/2. Profile_U_y_MUSCL_(El = " + to_string(max_el) + ").DAT");
    // Запись значения T и Alfa в сечении
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

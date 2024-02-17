#include "Variables.h"
#include "Declaration of procedures.h"

void Blank()
{

    int Local_count = 0;
    int Local_it = 0;

    ofstream File_Blank("Documents/Blank/Blank_R0_0.BLN", ios_base::trunc);

    /* Запись заголовка бланкировочного файла */
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
    double teta_0 = 0.0; //(30 * Pi / 180);

    /* Запись коррдинат */
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

void Blank_new(double t = 0.0)
{
    /*
    * Функция записывает файл для мешалки
    *
    * @param t - параметр, необходимый для расчета угла поворота лопастей. Если t=0, то мешалка стоит
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
        if (vectorElement[i].Geom_el == 1 && (vectorElement[i].Num_bound != out_1 && vectorElement[i].Num_bound != out_2
            && vectorElement[i].Num_bound != calc))
        {
            double debug_x = vectorElement[i].Coord_vert[0].x * cos(teta_0 + omega_1 * t) + vectorElement[i].Coord_vert[0].y * sin(teta_0 + omega_1 * t);
            double debug_y = -vectorElement[i].Coord_vert[0].x * sin(teta_0 + omega_1 * t) + vectorElement[i].Coord_vert[0].y * cos(teta_0 + omega_1 * t);
            double debug_x1 = vectorElement[i].Coord_vert[1].x * cos(teta_0 + omega_1 * t) + vectorElement[i].Coord_vert[1].y * sin(teta_0 + omega_1 * t);
            double debug_y1 = -vectorElement[i].Coord_vert[1].x * sin(teta_0 + omega_1 * t) + vectorElement[i].Coord_vert[1].y * cos(teta_0 + omega_1 * t);

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

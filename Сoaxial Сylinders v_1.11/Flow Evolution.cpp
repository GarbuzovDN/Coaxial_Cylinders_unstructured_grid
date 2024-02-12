#include "Variables.h"
#include "Declaration of procedures.h"

bool Marker_in_element(double xx, double yy, int num)
{
    /**
    * Функция проверяет принадлежность точки определенному элементу сетки
    *
    * @param xx    - х координата точки
    * @param yy    - y координата точки
    * @param num   - номер элемента, относительно которого идет проверка
    */

    double x1 = vectorElement[num].Coord_vert[0].x;
    double y1 = vectorElement[num].Coord_vert[0].y;
    double x2 = vectorElement[num].Coord_vert[1].x;
    double y2 = vectorElement[num].Coord_vert[1].y;
    double x3 = vectorElement[num].Coord_vert[2].x;
    double y3 = vectorElement[num].Coord_vert[2].y;

    double a = (x1 - xx) * (y2 - y1) - (x2 - x1) * (y1 - yy);
    double b = (x2 - xx) * (y3 - y2) - (x3 - x2) * (y2 - yy);
    double c = (x3 - xx) * (y1 - y3) - (x1 - x3) * (y3 - yy);

    bool MarkerInElement = (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);

    return MarkerInElement;
}

int Find_element_for_point(double xx, double yy, int num = -10)
{
    /*
    * Функция ищет номер контрольного объема, в котором находится заданная точка
    * @param xx - х координата точки
    * @param yy - y координата точки
    * @param num - номер контрольного объема, в рамках (или среди соседей) которого следует искать точку. 
                   Если num не задан, то используется значение по умолчанию (-10), а поиск идет по всем элементам сетки
    */

    double temp_1 = 100;
    bool MarkerInOldElement = false;
    bool MarkerInNeibElements = false;
    bool MarkerInElement = false;

    int num_el_for_pts;

    /* Если num (флаг) не равен -10, то необходимо проверить принадлежность точки определенному КО, номер которого равен num */
    if (num != -10)
    {
        int num_el = vectorElement[num].Num_el;

        /* Проверим принадлежность точки к КО с номером num */
        MarkerInOldElement = Marker_in_element(xx, yy, num_el);

        if (MarkerInOldElement)
        {
            num_el_for_pts = vectorElement[num_el].Num_el;
            return num_el_for_pts;
        }
        else
        {
            /* Проверим принадлежность точки к соседям КО с номером num */
            for (int j = 0; j < 3; j++)
            {
                if (vectorElement[num_el].Neighb_el[j] != -1)
                {

                    int num_neib = vectorElement[num_el].Neighb_el[j];
                    MarkerInNeibElements = Marker_in_element(xx, yy, num_neib);

                    if (MarkerInNeibElements)
                    {
                        num_el_for_pts = vectorElement[num_neib].Num_el;
                        return num_el_for_pts;
                    }
                }
            }

        }
    }
    else
    {

        /* Проверка по всем КО */
        for (int i = 0; i < vectorElement.size(); i++)
        {

            if (vectorElement[i].Geom_el == 2)
            {
                int num_el = vectorElement[i].Num_el;

                MarkerInElement = Marker_in_element(xx, yy, num_el);

                if (MarkerInElement)
                {
                    num_el_for_pts = vectorElement[num_el].Num_el;
                    return num_el_for_pts;
                }
            }
        }

        /* Если не нашел элемент, к которому принадлежит точка, то возвращает флаг 0 */
        return 0;
    }

}

double Section_value_MUSCL_Flow_Evo(double xx, double yy, int num_CV, string variable)
{
    /**
    * Функция поиска градиента заданной переменной (Ux, Uy)
    *
    * @param xx       - х координата точки
    * @param yy       - y координата точки
    * @param CV       - номер контрольного объема, внутри которого может находиться точка
    * @param variable - переменная, для которой ищется градиент
    */

    double temp_1 = 100;

    double test = 0.0;

    /* Интерполяция внутри элемента */
    {
        /* Слагаемые градиента */
        double x_x_i = xx - vectorElement[num_CV].Coord_center_el.x;
        double y_y_i = yy - vectorElement[num_CV].Coord_center_el.y;

        double t1, t2, Param;

        if (variable == "U_x")
        {
            t1 = vectorElement[num_CV].gradU_x[0];
            t2 = vectorElement[num_CV].gradU_x[1];
            Param = vectorElement[num_CV].U_x;
        }
        if (variable == "U_y")
        {
            t1 = vectorElement[num_CV].gradU_y[0];
            t2 = vectorElement[num_CV].gradU_y[1];
            Param = vectorElement[num_CV].U_y;
        }
        if (variable == "P")
        {
            t1 = vectorElement[num_CV].gradP[0];
            t2 = vectorElement[num_CV].gradP[1];
            Param = vectorElement[num_CV].P;
        }

        return  Param + (x_x_i * t1 + y_y_i * t2);
    }

    return 0.0;
}

void Flow_Evolution_new(string param) {

    string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Flow Evolution";
    CreateDirectoryA(_path.c_str(), NULL);

    if (param == "line")
    {
        string _path = "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Flow Evolution/Fixed Profile";
        CreateDirectoryA(_path.c_str(), NULL);

        double h = 0.05;

        /* Начально условие */
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

        /* Запись в файл */
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

        /* Основной цикл */
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

        /* Добавление маркеров */
        for (int i = 1; i < count_marker; i++)
        {

            double dx = (x_m[i] - x_m[i - 1]) * (x_m[i] - x_m[i - 1]);
            double dy = (y_m[i] - y_m[i - 1]) * (y_m[i] - y_m[i - 1]);

            double ds = sqrt(dx + dy);

            if (ds > h + 0.01)
            {
                x_m.resize(x_m.size() + 1);
                y_m.resize(x_m.size() + 1);

                // смещение от i + 1 до count_marker вправо на 1
                for (int j = count_marker; j >= i + 1; j--)
                {

                    x_m[j] = x_m[j - 1];
                    y_m[j] = y_m[j - 1];

                }

                // вставка нового маркера
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

        /* Начально условие */
        if (Iter_Glob == 1)
        {
            CreateDirectoryA(_path.c_str(), NULL);
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::trunc);
            Integral_Char << "time\t" << "gamma\t" << "N1\t" << "N2\t" << "\t\t" << "Re = " << Re << endl;

            double h = 0.9;
            double x = 0.0;
            double y = 0.0;

            int ii = 0;

            do
            {
                x += ii * h;
                double check_y = 0;
                int num_CV_for_cheсk = Find_element_for_point(x, y);

                if (vectorElement[num_CV_for_cheсk].Num_bound == calc)
                {
                    marker.coord[0] = x;
                    marker.coord[1] = y;

                    marker.CV_marker = num_CV_for_cheсk;

                    vectorMarker.push_back(marker);

                }

                ii++;

            } while (ii * h < 1.0);

        }

        /* Запись в файл */
        if (Iter_Glob % 1 == 0 || Iter_Glob == 1)
        {
            int temp_time = Iter_Glob;
            ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::trunc);
            Flow_Evo << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;
            Flow_Evo_test << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;

            for (const auto& marker : vectorMarker)
            {
                double x = marker.coord[0];
                double y = marker.coord[1];
                int CV = marker.CV_marker;

                // TODO: Вынести открывание файла для записи в конец за цикл
                //ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::app);
                ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::app);
                //Flow_Evo << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;
                Flow_Evo_test << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;

                int debug = 0;
            }

            double debug = 0.0;
        }

        /* Основный цикл */
        for (auto& marker : vectorMarker)
        {
            // TODO: сделать следующиим образом 
            /* обход одномерный
                1.вычисляет векторное произведение dot по КО CV_marker & coord_marker
                2. if (dot false) {поиск нового контрольного объема и перепприсвоение CV_marker[i]}
                    - обход по всем элементам;
                    - обход по КО, опирающимся на вершины текущего
                3. Section_value_MUSCL____________________(coord_marker[i][0], coord_marker[i][1], "___",CV_marker[i] )
             */

            double x = marker.coord[0];
            double y = marker.coord[1];
            int CV = Find_element_for_point(x, y, marker.CV_marker);

            double U_x = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_x");
            double U_y = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_y");

            double x_tmp_n = x + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_x") * dt_m;
            double y_tmp_n = y + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_y") * dt_m;

            /* Расчет интегральной характеристики */
            /*{
                if ((x > 0 && y > 0))
                {
                    integral_char_N1++;
                    int debug = 0;
                }

                if ((x < 0 && y < 0))
                {
                    integral_char_N2++;
                    int debug = 0;
                }
            }*/

            marker.coord[0] = x_tmp_n;
            marker.coord[1] = y_tmp_n;
            marker.CV_marker = CV;

            int debug = 0;
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

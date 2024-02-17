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

    int num_el_for_pts = 0;

    /* Если num (флаг) не равен -10, то необходимо проверить принадлежность точки определенному КО, номер которого равен num */
    if (num != -10)
    {
        int num_el = vectorElement[num].Num_el;

        /* Проверим принадлежность точки к КО с номером num_el */
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

    /* Проверка по всем КО в том случае, когда MarkerInOldElement == MarkerInNeibElements == false.
       Поиск идет с помощью векторного произведения */
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

    /* Если элемент для точки не найден, то функция вернет -1 */
    return -1;

}

double Section_value_MUSCL_Flow_Evo(double xx, double yy, int num_CV, string variable)
{
    /*
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
            Integral_Char << "time\t" << "rotation\t" << "gamma\t" << "N1\t" << "N2\t" << "\t\t" << "Re = " << Re << endl;

            double h = 0.025;
            double x = 0.0;
            double y = -1.0;

            int i_y = 0;

            do
            {
                int i_x = 0;
                y += h;

                do
                {
                    x = i_x * h;

                    int num_CV_for_cheсk = Find_element_for_point(x, y);

                    if (num_CV_for_cheсk != -1) 
                    {
                        if (vectorElement[num_CV_for_cheсk].Num_bound == calc)
                        {
                            marker.coord[0] = x;
                            marker.coord[1] = y;

                            marker.CV_marker = num_CV_for_cheсk;

                            vectorMarker.push_back(marker);
                        }
                    }

                    i_x++;

                } while (x < 1.0);

                i_y++;

            } while (y < 1.0);
        }

        /* Запись в файл */
        if (Iter_Glob % 50 == 0 || Iter_Glob == 1)
        {
            int temp_time = Iter_Glob;
            ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::trunc);
            Flow_Evo << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;
            Flow_Evo_test << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;

            /* Параметр для передачи в бланикровку для поворота лопасти */
            double t = _time_Flow_Evolution + dt_m;
            Blank_new(t);

            for (const auto& marker : vectorMarker)
            {
                double x = marker.coord[0];
                double y = marker.coord[1];
                int CV = marker.CV_marker;

                /* Запись в файл в СК, когда крутится стенка */
                /*Flow_Evo << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;
                Flow_Evo_test << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;*/

                /* Перевод координат в СК, где крутится лопасть */
                double debug_x = x * cos(omega_1 * t) + y * sin(omega_1 * t);
                double debug_y = -x * sin(omega_1 * t) + y * cos(omega_1 * t);
                Flow_Evo << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                Flow_Evo_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;

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

            double x = marker.coord[0], y = marker.coord[1];
            double x_tmp_n, y_tmp_n;
            int CV = Find_element_for_point(x, y, marker.CV_marker);

            /* Если маркер вышел за область моделирования или попал внутрь лопасти, то берем его старые координаты */
            if (CV == -1) 
            {
                                
                CV = marker.CV_marker;

            }           
            
            double U_x = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_x");
            double U_y = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_y");

            x_tmp_n = x + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_x") * dt_m;
            y_tmp_n = y + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_y") * dt_m;

            /* Расчет интегральной характеристики */
            {
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
            }

            marker.coord[0] = x_tmp_n;
            marker.coord[1] = y_tmp_n;
            marker.CV_marker = CV;

            int debug = 0;
        }

        if (Iter_Glob % 200 == 0 || Iter_Glob == 1)
        {
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::app);
            double integral_char = abs(integral_char_N1 - integral_char_N2) / (integral_char_N1 + integral_char_N2);
            double rotation = (_time_Flow_Evolution * omega_1) / 2.0 / Pi;
            Integral_Char << _time_Flow_Evolution << "\t" << rotation << "\t"
                << integral_char << "\t" << integral_char_N1 << "\t" << integral_char_N2 << endl;

            double debug = 0.0;
        }
    }
}

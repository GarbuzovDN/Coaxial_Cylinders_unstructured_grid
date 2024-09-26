#include "Variables.h"
#include "Declaration of procedures.h"
#include <random>

bool Marker_in_element(double xx, double yy, int num)
{
    /**
    * Функция проверяет принадлежность точки определенному элементу сетки
    *
    * @param xx    - х координата точки
    * @param yy    - y координата точки
    * @param num   - номер элемента, относительно которого идет проверка
    */

    // Координаты вершин треугольника (элемента сетки)
    double x1 = vectorElement[num].Coord_vert[0].x;
    double y1 = vectorElement[num].Coord_vert[0].y;
    double x2 = vectorElement[num].Coord_vert[1].x;
    double y2 = vectorElement[num].Coord_vert[1].y;
    double x3 = vectorElement[num].Coord_vert[2].x;
    double y3 = vectorElement[num].Coord_vert[2].y;

    // Барицентрические координаты (векторные произведения трех сторон треугольника)
    double a = (x1 - xx) * (y2 - y1) - (x2 - x1) * (y1 - yy);
    double b = (x2 - xx) * (y3 - y2) - (x3 - x2) * (y2 - yy);
    double c = (x3 - xx) * (y1 - y3) - (x1 - x3) * (y3 - yy);

    bool MarkerInElement = (a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0);

    return MarkerInElement;
}

int Find_element_for_point(double xx, double yy, int num = -10)
{
    /*
    * Функция ищет номер контрольного объема, в котором находится заданная точка с помошью барицентрических координат
    * @param xx - х координата точки
    * @param yy - y координата точки
    * @param num - номер контрольного объема, в рамках (или среди соседей) которого следует искать точку. 
                   Если num не задан, то используется значение по умолчанию (-10), а поиск идет по всем элементам сетки
    */

    // Флаги нахождения/НЕнахождения точки в элементе (треугольнике)
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

int Find_element_for_point_old(double xx, double yy)
{
    /*
    * Функция ищет номер контрольного объема, в котором находится заданная точка с помошью расстояния до ближайшего центра КО
    * Предполагается использовать эту функцию в исключительных случаях
    * 
    * @param xx - х координата точки
    * @param yy - y координата точки
    */

    double dl;
    double temp_1 = 100;

    int num_el_for_pts = -1;

    for (int i = 0; i < vectorElement.size(); i++)
    {
        if (vectorElement[i].Geom_el == 2)
        {

            dl = sqrt(pow((vectorElement[i].Coord_center_el.x - xx), 2) + pow((vectorElement[i].Coord_center_el.y - yy), 2));

            if (dl < temp_1)
            {

                temp_1 = dl;
                num_el_for_pts = vectorElement[i].Num_el;

                i = i;

            }
        }

    }

    return num_el_for_pts;

}

double Section_value_MUSCL_Flow_Evo(double xx, double yy, int num_CV, string variable)
{
    /*
    * Функция поиска градиента заданной переменной (Ux, Uy)
    *
    * @param xx       - х координата точки
    * @param yy       - y координата точки
    * @param CV       - номер контрольного объема, внутри которого находится точка
    * @param variable - переменная, для которой ищется градиент
    */

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
        
        double t = 0.0;
        double h = 0.05;

        // Переменная для перехода в СК, где крутится лопасть
        bool WallRotate = false;

        /* Начально условие */
        if (Iter_Glob == 1)
        {
            CreateDirectoryA(_path.c_str(), NULL);
                        
            double x, y;
            int i_x = 0;
            double r = 0.0, angle = 0.0;

            do
            {
                r = R0 + i_x * h;
                angle = 45 * Pi / 180;

                x = r * cos(angle);
                y = r * sin(angle);

                int num_CV_for_cheсk = Find_element_for_point(x, y);

                // Если в начальный момент времени элемент не нашелся, то ищем его старым способом 
                // (сравнивая расстояния от точки до центра КО)
                if (num_CV_for_cheсk == -1) 
                    num_CV_for_cheсk = Find_element_for_point_old(x, y);

                marker.coord[0] = x;
                marker.coord[1] = y;
                marker.CV_marker = num_CV_for_cheсk;

                vectorMarker.push_back(marker);

                i_x++;

            } while (r < 1.0);
        }

        /* Запись в файл */
        if (Iter_Glob % 50 == 0 || Iter_Glob == 1)
        {
            int temp_time = Iter_Glob;
            ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::trunc);
            Flow_Evo << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;
            Flow_Evo_test << "time = " << (_time_Flow_Evolution + dt_m) << "\t" << "Re = " << Re << endl;

            if (!WallRotate)
            {
                /* Параметр, который передается в бланикровку для поворота лопасти */
                t = _time_Flow_Evolution + dt_m;
                Blank_new(t);
            }

            for (const auto& marker : vectorMarker)
            {
                double x = marker.coord[0];
                double y = marker.coord[1];
                int CV = marker.CV_marker;

                if (WallRotate)
                {
                    /* Запись в файл в СК, когда крутится стенка */
                    Flow_Evo << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;
                    Flow_Evo_test << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;
                }

                if (!WallRotate)
                {
                    /* Перевод координат в СК, где крутится лопасть */
                    double debug_x = x * cos(omega_1 * t) + y * sin(omega_1 * t);
                    double debug_y = -x * sin(omega_1 * t) + y * cos(omega_1 * t);
                    Flow_Evo << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                    Flow_Evo_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                }

                int debug = 0;
            }

            double debug = 0.0;
        }

        /* Добавление и удаление маркеров */
        for (int i = 1; i < vectorMarker.size(); i++)
        {
            double x0 = vectorMarker[i - 1].coord[0];
            double x1 = vectorMarker[i].coord[0];

            double y0 = vectorMarker[i - 1].coord[1];
            double y1 = vectorMarker[i].coord[1];

            double dx = (x1 - x0) * (x1 - x0);
            double dy = (y1 - y0) * (y1 - y0);

            double debug_0 = pow(x0 * x0 + y0 * y0, 0.5);
            double debug_1 = pow(x1 * x1 + y1 * y1, 0.5);

            double ds = sqrt(dx + dy);

            // Добавление 
            if (ds > h + 0.01)
            {
                vectorMarker.resize(vectorMarker.size() + 1);

                // Смещение от элементов вектора маркеров вправо на 1
                for (int j = vectorMarker.size() - 1; j >= i + 1; j--)
                {
                    vectorMarker[j] = vectorMarker[j - 1];
                }

                // Вставка нового маркера
                vectorMarker[i].coord[0] = 0.5 * (x0 + x1);
                vectorMarker[i].coord[1] = 0.5 * (y0 + y1);
            }

            // Удаление
            if (ds < 0.5 * h)
            {
                vectorMarker.erase(vectorMarker.begin() + i);
            }
        }

        /* Основный цикл */
        for (auto& marker : vectorMarker)
        {
            double x = marker.coord[0], y = marker.coord[1];
            double x_tmp_n, y_tmp_n;
            int CV = Find_element_for_point(x, y, marker.CV_marker);

            /* Если маркер вышел за область моделирования или попал внутрь лопасти, то берем коорд. центра последнего КО */
            if (CV == -1)
            {
                CV = marker.CV_marker;
                /*x = vectorElement[CV].Coord_center_el.x;
                y = vectorElement[CV].Coord_center_el.y;*/
            }

            double U_x = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_x");
            double U_y = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_y");

            x_tmp_n = x + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_x") * dt_m;
            y_tmp_n = y + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_y") * dt_m;

            marker.coord[0] = x_tmp_n;
            marker.coord[1] = y_tmp_n;
            marker.CV_marker = CV;

            int debug = 0;
        }

    }

    if (param == "array")
    {
        string _path = 
        "Documents/Figure/Re=" + to_string(Re) + "/El = " + to_string(max_el) + "/Flow Evolution/Marker Array";

        ofstream Integral_Char;
        double integral_char_N1 = 0.0;
        double integral_char_N2 = 0.0;
        double t = 0.0;
        double rotation = (_time_Flow_Evolution * omega_1) / 2.0 / Pi;

        // Переменная для перехода в СК, где крутится лопасть
        bool WallRotate = false;

        // Переменная для добавления шумма к начальным координатам
        bool AddDataNoise = true;

        // Для сравнения с экспериментом Комоды необходимо начальное условие задавать иначе
        bool InitForExpKomoda = true;

        /* Начально условие */
        if (Iter_Glob == 1 && !InitForExpKomoda)
        {
            CreateDirectoryA(_path.c_str(), NULL);
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::trunc);
            Integral_Char << "time\t" << "rotation\t" << "gamma\t" << "N1\t" << "N2\t"  << "exp_moving"
                << "\t\t" << "Re = " << Re << "\tMesh: " << max_el << endl;

            double h = 0.025;
            double x = 0.0;
            double y = -1.0;

            int i_y = 0;

            // Добавление РАВНОМЕРНЫХ координат для x, y 
            if (!AddDataNoise)
            {
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
                            if (vectorElement[num_CV_for_cheсk].Num_bound == border.calc)
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
            
            
            // Добавление псевдоСЛУЧАЙНЫХ координат для x, y 
            if (AddDataNoise)
            {
                double uniformNoise_x;
                double uniformNoise_y;

                // Специально берется псевдослучайное распределение (gen(0); 0 - seed), 
                // чтобы при перезапуске расчета получать одинаковое начальное распределение
                random_device rd;
                mt19937 gen(0);
                do
                {
                    
                    // Псевдослучайное распределение маркеов в нужных границ по x(0, 1) и y(-1, 1)
                    uniform_real_distribution<> dis_x(0, 1);
                    uniform_real_distribution<> dis_y(-1, 1);

                    uniformNoise_x = dis_x(gen);
                    uniformNoise_y = dis_y(gen);

                    x = uniformNoise_x;
                    y = uniformNoise_y;

                    // Проверка на принадлежность области расчета
                    int num_CV_for_cheсk = Find_element_for_point(x, y);

                    //Если num_CV_for_cheсk = -1, то элемент сетки для маркера не найден => 
                    // => маркер не принадлежит расчетной области
                    if (num_CV_for_cheсk != -1)
                    {
                        if (vectorElement[num_CV_for_cheсk].Num_bound == border.calc)
                        {
                            marker.coord[0] = x;
                            marker.coord[1] = y;

                            marker.CV_marker = num_CV_for_cheсk;
                            marker.color = "none";

                            /* Разделяем вектор маркеров на подобалсти */
                            double r = sqrt(x * x + y * y);
                            if (r <= 0.5 && x >= 0) marker.color = "red";
                            if (r >= 0.5 && x >= 0) marker.color = "black";
                            if (r <= 0.5 && x <= 0) marker.color = "blue";
                            if (r >= 0.5 && x <= 0) marker.color = "green";

                            vectorMarker.push_back(marker);

                        }
                    }

                } while (vectorMarker.size() < 10000);
            }
        }

        /* Начальное условие для эксперимента Комоды */
        if ((Iter_Glob == 0 || Iter_Glob % 10 == 0) && InitForExpKomoda)
        {
            CreateDirectoryA(_path.c_str(), NULL);
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::trunc);
            Integral_Char << "time\t" << "rotation\t" << "gamma\t" << "N1\t" << "N2\t" << "exp_moving"
                << "\t\t" << "Re = " << Re << "\tMesh: " << max_el << endl;

            double x = -0.65;
            double y = 0.65;

            double debug_x = x * cos(phi) - y * sin(phi);
            double debug_y = x * sin(phi) + y * cos(phi);

            int num_CV_for_cheсk = Find_element_for_point(debug_x, debug_y);

            marker.coord[0] = debug_x;
            marker.coord[1] = debug_y;

            marker.CV_marker = num_CV_for_cheсk;

            vectorMarker.push_back(marker);

        }

        /* Запись в файл */
        int write_step = 0.0;

        // Первые 50 у.е. по времени записываем часто, чтобы визуализировать результат в GIF, 
        // дальше записываем реже, чтобы не тратить много памяти
        if (_time_Flow_Evolution <= 50) write_step = 50;
        if (_time_Flow_Evolution > 50) write_step = 10000;

        if (Iter_Glob % write_step == 0 || Iter_Glob == 1)
        {
            /* Запись общего набора маркеров */
            int temp_time = Iter_Glob;
            ofstream Flow_Evo(_path + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_test(_path + "/Flow Evolution.DAT", ios_base::trunc);
            Flow_Evo << "time = " << (_time_Flow_Evolution + dt_m) 
                << "\tRe = " << Re << "\trotation = " << rotation << endl;
            Flow_Evo_test << "time = " << (_time_Flow_Evolution + dt_m) 
                << "\tRe = " << Re << "\trotation = " << rotation << endl;

            /* Запись наборов маркеров по подобластям */
            string path_section = _path + "/Section";
            CreateDirectoryA(path_section.c_str(), NULL);

            string path_new = _path + "/Section/Red";
            CreateDirectoryA(path_new.c_str(), NULL);
            ofstream Flow_Evo_red(path_new + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_red_test(path_new + "/Flow Evolution.DAT", ios_base::trunc);

            path_new = _path + "/Section/Black";
            CreateDirectoryA(path_new.c_str(), NULL);
            ofstream Flow_Evo_black(path_new + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_black_test(path_new + "/Flow Evolution.DAT", ios_base::trunc);

            path_new = _path + "/Section/Blue";
            CreateDirectoryA(path_new.c_str(), NULL);
            ofstream Flow_Evo_blue(path_new + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_blue_test(path_new + "/Flow Evolution.DAT", ios_base::trunc);

            path_new = _path + "/Section/Green";
            CreateDirectoryA(path_new.c_str(), NULL);
            ofstream Flow_Evo_green(path_new + "/Flow Evolution " + to_string(temp_time / 10) + ".DAT", ios_base::trunc);
            ofstream Flow_Evo_green_test(path_new + "/Flow Evolution.DAT", ios_base::trunc);

            if (!WallRotate) 
            {
                /* Параметр, который передается в бланикровку для поворота лопасти */
                t = _time_Flow_Evolution + dt_m;
                Blank_new(t);
            }

            for (const auto& marker : vectorMarker)
            {
                double x = marker.coord[0];
                double y = marker.coord[1];
                int CV = marker.CV_marker;

                if (WallRotate)
                {
                    /* Запись в файл в СК, когда крутится стенка */
                    Flow_Evo << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;
                    Flow_Evo_test << fixed << setprecision(6) << x << "\t" << y << "\t" << CV << "\t" << endl;
                }
                
                if (!WallRotate)
                {
                    //phi = omega_1 * _time_Flow_Evolution;
                    /* Перевод координат в СК, где крутится лопасть */
                    double debug_x = x * cos(phi) + y * sin(phi);
                    double debug_y = -x * sin(phi) + y * cos(phi);

                    /* Запись наборов маркеров по подобластям */
                    if (marker.color == "red") 
                    {
                        Flow_Evo_red << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                        Flow_Evo_red_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                    }                   

                    if (marker.color == "black") 
                    {
                        Flow_Evo_black << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                        Flow_Evo_black_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                    } 
                    
                    if (marker.color == "blue") 
                    {
                        Flow_Evo_blue << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                        Flow_Evo_blue_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                    }

                    if (marker.color == "green") 
                    {
                        Flow_Evo_green << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                        Flow_Evo_green_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                    }

                    Flow_Evo << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                    Flow_Evo_test << fixed << setprecision(6) << debug_x << "\t" << debug_y << "\t" << CV << "\t" << endl;
                }

                int debug = 0;
            }

            double debug = 0.0;
        }

        // Основный цикл
        for (auto& marker : vectorMarker)
        {
            double x = marker.coord[0], y = marker.coord[1];

            double r_point = sqrt(x * x + y * y);
            if (r_point > 1.0) {

                x = x / r_point * R1;
                y = y / r_point * R1;

            }

            double x_tmp_n, y_tmp_n;
            int CV = Find_element_for_point(x, y, marker.CV_marker);

            // Если маркер вышел за область моделирования или попал внутрь лопасти, 
            // то берем его старые координаты
            if (CV == -1) 
            {                                
                CV = marker.CV_marker;
            }  

            double U_x = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_x");
            double U_y = Section_value_MUSCL_Flow_Evo(x, y, CV, "U_y");

            x_tmp_n = x + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_x") * dt_m;
            y_tmp_n = y + Section_value_MUSCL_Flow_Evo(x + 0.5 * U_x * dt_m, y + 0.5 * U_y * dt_m, CV, "U_y") * dt_m;

            // Расчет интегральной характеристики
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

        // Запись интегральной характеристики
        if (Iter_Glob % 200 == 0 || Iter_Glob == 1)
        {
            ofstream Integral_Char(_path + "/Integral_Char.DAT", ios_base::app);
            double integral_char = (integral_char_N1 - integral_char_N2) / (integral_char_N1 + integral_char_N2);

            // Сглаживание интегральной характеристики путем расчета эксп. скользящей средней
            double alfa_exp = 0.01;
            double exp_moving_current = alfa_exp * integral_char + (1 - alfa_exp) * exp_moving_old;
            if (Iter_Glob == 1) exp_moving_current = integral_char;

            Integral_Char << _time_Flow_Evolution << "\t" << rotation << "\t" << integral_char << "\t" 
                << integral_char_N1 << "\t" << integral_char_N2 << "\t" << exp_moving_current << endl;

            exp_moving_old = exp_moving_current;
            double debug = 0.0;
        }
    }
}

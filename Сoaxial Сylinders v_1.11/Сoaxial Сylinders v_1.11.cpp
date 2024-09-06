#include "Main.h"
#include "Declaration of procedures.h"
#include "chrono"

int main()
{

    Iter_Glob = 0;
    Mesh_Init();
    Initial_Conditions();

    Section_value_MUSCL(xx_1, yy_1, "NULL");

    Redistricting1();
    Write();

    double test = 0.0;

    if (Start_Flow_Evolution == false)
    {
        do
        {
            Time();

            if (Variable_Speed)
            {
                Flow_Evolution_new("array"); //"line" или "array"

                // Отношение периода к амплитуде равнозначно с Камодой
                /*double debug = cos(2.0 * Pi * Pi * _time / 4.0);
                omega_1 = 0.5 * (1.0 - debug);*/

                // Период изменения скорости - один полный оборот (2*Pi)
                /*double debug = cos(_time);
                omega_1 = 0.5 * (1.0 - debug);*/

                // Знакоперменная скорость
                //double debug = cos(_time);
                //omega_1 = 2.0 / 3.0 * (0.5 - debug);

                // Старая скорость для сравнения с экспериментом Комоды
                /*double debug = cos(Pi / 2.0 + 2 * Pi * _time);
                omega_1 = debug;*/
                
                // Новая скорость для сравнения с экспериментом Комоды
                double debug = cos(2 * Pi * _time);
                omega_1 = Pi / 2.0 * (1.0 - debug);
            }

            Redistricting();
            Iter_Glob++;

            //for (int Iter = 0; Iter <= 100; Iter++)
            {

                Redistricting1();
                Calculation_Velocity_U();
                Redistricting1();
                Calculation_Pressure_P();
                Redistricting1();

            }

            Development();
            Write();        

            if (!Variable_Speed) if (_time > 25.0) break;

        } while (_time <= final_time  /*E_U > 1.0E-5*/);
                
        Write_End();
    }
        
    if (Start_Flow_Evolution == true)
    {
        auto start_time = chrono::high_resolution_clock::now();
        Redistricting1();
        double t = 0.0;

        do
        {
            Iter_Glob++;

            Flow_Evolution_new("array"); //"line" или "array"

            /* Параметр, который передается в бланикровку для поворота лопасти */
            t = _time_Flow_Evolution + dt_m;
            Blank_new(t);

            Time();

        } while (_time_Flow_Evolution <= final_time);

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::minutes>(end_time - start_time);
        cout << "Program execution time: " << duration.count() << " minutes" << std::endl;
    }

    // Необходимо ставить консоль после расчета на паузу при запуске через exe 
    system("pause");
}
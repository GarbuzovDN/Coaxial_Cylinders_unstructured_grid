#include "Main.h"
#include "Declaration of procedures.h"
#include "chrono"

int main()
{

    Iter_Glob = 0;
    Mesh_Init();
    Initial_Conditions();

    Section_value_MUSCL(xx_1, yy_1, "NULL");

    Redistricting_grads();
    Write();

    double test = 0.0;

    if (Start_Flow_Evolution == false)
    {
        do
        {
            Time();

            phi = omega_1 * _time_Flow_Evolution;

            if (Variable_Speed)
            {
                Flow_Evolution_new("array"); //"line" или "array"
                
                // Новая скорость для сравнения с экспериментом Комоды
                omega_1 = -Pi * Pi * sin(2 * Pi * _time);
                epselon = -2 * Pi * Pi * Pi * cos(2 * Pi * _time);
                phi = -Pi / 2.0 * (1 - cos(2 * Pi * _time));

                // Параметры для постоянной скорости
                //omega_1 = 1.0;
                //epselon = 0.0;
                //phi = omega_1 * _time_Flow_Evolution;
            }

            Redistricting_U();
            Iter_Glob++;

            //for (int Iter = 0; Iter <= 100; Iter++)
            {

                Redistricting_grads();
                Calculation_Velocity_U();
                Redistricting_grads();
                Calculation_Pressure_P();
                Redistricting_grads();

            }

            Development();
            Write();        

            if (!Variable_Speed) if (_time > 25.0) break;

        } while (/*_time <= final_time*/  E_U > 1.0E-5);
                
        Write_End();
    }
        
    if (Start_Flow_Evolution == true)
    {
        auto start_time = chrono::high_resolution_clock::now();
        Redistricting_grads();
        double t = 0.0;

        do
        {
            Iter_Glob++;
            phi = omega_1 * _time_Flow_Evolution;

            /* Параметр, который передается в бланикровку для поворота лопасти */
            Blank_new(_time_Flow_Evolution);

            Flow_Evolution_new("array"); //"line" или "array"                                
            Time();

        } while (_time_Flow_Evolution <= final_time);

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::minutes>(end_time - start_time);
        cout << "Program execution time: " << duration.count() << " minutes" << std::endl;
    }

    // Необходимо ставить консоль после расчета на паузу при запуске через exe 
    //system("pause");
}
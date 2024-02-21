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
            //Flow_Evolution("array"); //"line" или "array"

            Time();
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

            if (_time > 25.0) break;

        } while (/*_time <= final_time*/E_U > 0.00001);
                
        Write_End();
    }
        
    if (Start_Flow_Evolution == true)
    {
        auto start_time = chrono::high_resolution_clock::now();
        Redistricting1();

        do
        {
            Iter_Glob++;

            Flow_Evolution_new("line"); //"line" или "array"
            Time();

        } while (_time_Flow_Evolution <= final_time);

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << "Program execution time: " << duration.count() << " milliseconds" << std::endl;
    }

    // Необходимо ставить консоль после расчета на паузу при запуске через exe 
    //system("pause");
}
#include "Main.h"
#include "Declaration of procedures.h"

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

        } while (/*_time <= final_time*/E_U > 0.00001);

        Stream_Function();
        Write_End();
    }

    if (Start_Flow_Evolution == true)
    {
        do
        {
            //Redistricting();
            Iter_Glob++;

            Flow_Evolution("array"); //"line" или "array"
            Time();

        } while (_time <= final_time);
    }
}
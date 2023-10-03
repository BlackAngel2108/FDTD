#include "FDTD.h"

//void Start_test(Field& Test) {
//    double dx = 1;
//    double dy = 1;
//    int N_x = 10;
//    int N_y = 10;
//    double X_max = dx * N_x;
//    double Y_max = dy * N_y;
//    int N_t = 10;
//    double dt = 1.0 / c / 10.0 * dx;
//    std::cout << "X_max = " << X_max << " Y_max = " << Y_max << std::endl;
//    std::cout << "dx = " << dx << " dy = " << dy << std::endl;
//    std::cout << "dt = " << dt << " N_t = " << N_t << std::endl;
//}
void get_Net2(Field& fld, std::ofstream& fout) {
    for (int j = fld.get_N_y() - 1; j >= 0; j--) {
        for (int i = 0; i < fld.get_N_x(); i++) {
            fout << fld.Net_index(i, j).Ex;
            if (i == fld.get_N_x() - 1)
            {
                fout << std::endl;
            }
            else
            {
                fout << ";";
            }
        }
    }
    fout << std::endl << std::endl;
    for (int j = fld.get_N_y() - 1; j >= 0; j--) {
        for (int i = 0; i < fld.get_N_x(); i++) {
            fout << fld.Net_index(i, j).Ey;
            if (i == fld.get_N_x() - 1)
            {
                fout << std::endl;
            }
            else
            {
                fout << ";";
            }
        }
    }
    fout << std::endl << std::endl;
    for (int j = fld.get_N_y() - 1; j >= 0; j--) {
        for (int i = 0; i < fld.get_N_x(); i++) {
            fout << fld.Net_index(i, j).Ez;
            if (i == fld.get_N_x() - 1)
            {
                fout << std::endl;
            }
            else
            {
                fout << ";";
            }
        }
    }
    fout << std::endl << std::endl;
    for (int j = fld.get_N_y() - 1; j >= 0; j--) {
        for (int i = 0; i < fld.get_N_x(); i++) {
            fout << fld.Net_index(i, j).Bx;
            if (i == fld.get_N_x() - 1)
            {
                fout << std::endl;
            }
            else
            {
                fout << ";";
            }
        }
    }
    fout << std::endl << std::endl;
    for (int j = fld.get_N_y() - 1; j >= 0; j--) {
        for (int i = 0; i < fld.get_N_x(); i++) {
            fout << fld.Net_index(i, j).By;
            if (i == fld.get_N_x() - 1)
            {
                fout << std::endl;
            }
            else
            {
                fout << ";";
            }
        }
    }
    fout << std::endl << std::endl;
    for (int j = fld.get_N_y() - 1; j >= 0; j--) {
        for (int i = 0; i < fld.get_N_x(); i++) {
            fout << fld.Net_index(i, j).Bz;
            if (i == fld.get_N_x() - 1)
            {
                fout << std::endl;
            }
            else
            {
                fout << ";";
            }
        }
    }
    fout << std::endl << std::endl;
}
void get_test_Net(Field& fld) {
    std::ofstream test_fout;
    test_fout.open("../../PlotScript/OutFile.csv");
    //test_fout.open("OutFile.csv");
    get_Net2(fld,test_fout);
    test_fout.close();
}
node f(double x, double b) {
    node temp;
    temp.Ey = sin(2 * PI * (x) / b);
    temp.Bz = temp.Ey;
    temp.Bx = 0;
    temp.By = 0;
    temp.Ex = 0;
    temp.Ez = 0;
    return temp;
}// Функция вспомогательная, для задачи поля
int main() {
    double dx = 1;
    double dy = 1;
    int N_x = 10;
    int N_y = 10;
    double X_max = dx * N_x;
    double Y_max = dy * N_y;
    int N_t = 10;
    double dt = 1.0 / c / 10.0 * dx;
    Field Test(dx, dy, N_x, N_y, N_t);
    //Start();
    //Field Main;
    //Main.Start_test();
    Test.set_net(f, Test.get_X_max());
    Test.print_Net();
    std::cout << std::endl;
    //Tets.get_Net();
    get_test_Net(Test);
    Test.FDTD(Test.get_N_t());
    get_test_Net(Test);
    Test.print_Net();
    std::cout << std::endl;
    /* set_net(f);
     FDTD(15);
     print_Net();*/
}

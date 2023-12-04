#include "For_tests.h"
#define Ey_
#define Bz_
void Field::Start()
{
    /*std::cout<<"Enter X_max and Y_max "<<std::endl;
    std::cin>>X_max>>Y_max;
    std::cout << "Cell size "<<X_max<<" * "<<Y_max<<std::endl;*/
    /*std::cout << "Enter dx and dy " << std::endl;
    std::cin >> dx >> dy;*/
    std::cout << "ax = " << ax << " bx = " << bx << std::endl;
    std::cout << "ay = " << ay << " by = " << by << std::endl;
    std::cout << "Enter how many cells to divide into" << std::endl;
    std::cin >> N_x >> N_y;
    std::cout << "Enter T " << std::endl;
    std::cin >> T;
    dt = 1 / c / dx;
    dx = (bx - ax) / N_x;
    dy = (by - ay) / N_y;
    dt = 1 / c / dx;
    N_t = T / dt;
}

node f1(double x, double a, double b) {
    node temp;
    temp.Ey = sin(2 * PI * ((x - a) / (b - a)));
    temp.Bz = temp.Ey;
    temp.Bx = 0;
    temp.By = 0;
    temp.Ex = 0;
    temp.Ez = 0;
    return temp;
}// Функция вспомогательная, для задачи поля
node f_shifted(double a, double b, double x, double dx) {
    node temp;
    temp.Ey = sin(2 * PI * ((x - a) / (b - a)));
    temp.Bz = temp.Ey;
    temp.Bx = 0;
    temp.By = 0;
    temp.Ex = 0;
    temp.Ez = 0;
    return temp;
}// Функция вспомогательная, для задачи поля
double epsilon(Field& fd, double T, double a, double b) {
    double max_epsilon = 0;
    int j = 0;
    for (int i = 0; i < fd.get_N_x(); i++) {
        double temp = fabs((fd(i, j).Ey) - (sin(2 * PI * (i * fd.get_dx() - a - c * T) / (b - a))));
        if (temp > max_epsilon)
            max_epsilon = temp;
    }
    return max_epsilon;
}
void get_Net2(Field& fld, std::ofstream& fout) {
#ifdef Ex_
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
#endif
#ifdef Ey_
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
#endif
#ifdef Ez_
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
#endif
#ifdef Bx_
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
#endif
#ifdef By_
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
#endif
#ifdef Bz_
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
#endif
}
void get_x_net(Field& fld, std::ofstream& fout, double T) {
    for (int i = 0; i < fld.get_N_x(); i++) {
        fout << fld.get_dx() * i;
        if (i == fld.get_N_x() - 1)
        {
            fout << std::endl;
        }
        else
        {
            fout << ";";
        }
    }
    for (int i = 0; i < fld.get_N_x(); i++) {
        fout << sin(2 * PI * (i * fld.get_dx() - fld.get_ax() - c * T) / (fld.get_bx() - fld.get_ax())) << ";";
    }
    fout << std::endl;
    fout << std::endl;
}
void get_test_Net(Field& fld, std::string str, double T) {
    std::ofstream test_fout;
    test_fout.open(str);
    //test_fout.open("../../PlotScript/OutFile.csv");
    //test_fout.open("OutFile.csv");
    get_x_net(fld, test_fout, T);
    get_Net2(fld, test_fout);
    test_fout << epsilon(fld, T, fld.get_ax(), fld.get_bx());
    test_fout.close();
}
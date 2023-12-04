#pragma once


#include "FDTD.h"
//class For_tests

    double epsilon(Field& fd, double T, double a, double b);
    Field start();
    node f_shifted(double a, double b, double x, double dx);
    node f1(double x, double a, double b);
    void get_Net2(Field& fld, std::ofstream& fout);
    void get_x_net(Field& fld, std::ofstream& fout, double T);
    void get_test_Net(Field& fld, std::string str, double T);
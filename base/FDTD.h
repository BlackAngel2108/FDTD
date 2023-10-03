#pragma once

#include <iostream>
#include <vector>
#include "math.h"
#include < fstream >
//using namespace std;


const double c = 3e10;
const double PI = 3.14159265;

struct node {
    double Ex, Ey, Ez, Bx, By, Bz;
};
class Field {
public:

private:
    double dx, dy, dt;
    int N_x, N_y, N_t; //на сколько ячеек делим по Х и по Y и по времени
    double X_max;
    double Y_max;

    std::vector<node> Net;

public:
    Field(){};
    Field(double dx1, double dy1, int N_x1, int N_y1, int N_t1) {
        dx = dx1;
        dy = dy1;
        N_x = N_x1;
        N_y = N_y1;
        N_t = N_t1;
        X_max = dx * N_x;
        Y_max = dy * N_y;
        dt = 1 / c / dx;
    }
    node& Net_index(int i, int j){return Net[double(i) + j * N_x]; }
    void set_net(); // Задать сетку вручную
    void Start(); // Задать начальные значения
    void print_Net();

    void Maxwell(); //Реалицазия уранений максвелла
    void FDTD(int Num_t); //подсчет метода через Num_t секунд

    void change_N_t(int a) { N_t = a; }
    void change_dx(double a) {
        dx = a;
        X_max = dx * N_x;
    }
    void change_dy(double a) {
        dy = a; Y_max = dy * N_y;
    }
    void change_N_x(int a) {
        N_x = a;
        X_max = dx * N_x;
    }
    void change_N_y(int a) {
        N_y = a;
        Y_max = dy * N_y;
    }
    int get_N_t() { return N_t; }
    double get_X_max(){return X_max;}
    double get_Y_max(){return Y_max;}
    double get_N_x() { return N_x; }
    double get_N_y() { return N_y; }

    void get_Net(std::ofstream& fout); // запись в файл значений поля
    std::vector<node> get_Net(){return Net;}

    void set_net(node(*f)(double, double),double b); // задать сетку через функцию
};
    
    //void get_Net2(Field& fld, std::ofstream& fout); //Запись в файл значений сетки по компонентам

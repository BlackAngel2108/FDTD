#pragma once

#include <iostream>
#include <vector>
#include "math.h"
#include < fstream >
//using namespace std;


const double c = 3.*(1e10);
const double PI = 3.14159265;

struct node {
    double Ex, Ey, Ez, Bx, By, Bz;
};
class Field {
public:

private:
    double dx, dy, dt;
    double ax,bx,ay,by,T,t; 
    int N_x, N_y, N_t; //на сколько ячеек делим по Х и по Y и по времени
   // double X_max;
   // double Y_max;

    std::vector<node> Net;

public:
    Field(){};
    Field(double dx1, double dy1, int N_x1, int N_y1, int N_t1);
    Field(double ax1, double bx1, double ay1, double by1, int N_x1, int N_y1, double T1);
    Field(double ax1, double bx1, double ay1, double by1, int N_x1, int N_y1, double dt, double T1);
    //dt высчитывается автоматически с согласованием dx
    node& Net_index(int i, int j);
    node& operator() (int _i, int _j);
    void set_net(); // Задать сетку вручную
    void Start(); // Задать начальные значения
    void print_Net();

    void Maxwell(); //Реалицазия уранений максвелла
    void Maxwell_shifted();
    void FDTD(int Num_t); //подсчет метода через Num_t секунд
    void FDTD_shifted(int Num_t);

    void change_N_t(int a) { N_t = a; }
    void change_dx(double a);
    void change_dy(double a);

    int get_N_t() { return N_t; }
    double get_X_max(){return bx-ax;}//длина поля по X
    double get_Y_max(){return by-ay;}// длина поля по Y
    double get_ax() { return ax; }
    double get_bx() { return bx; }
    double get_ay() { return ay; }
    double get_by() { return by; }
    double get_dx() {return dx;}
    double get_T(){return T;}
    double get_dt() { return dt; }
    double get_t() { return t; }
    double get_N_x() { return N_x; }
    double get_N_y() { return N_y; }

    void get_Net(std::ofstream& fout); // запись в файл значений поля
    std::vector<node> get_Net(){return Net;}

    void set_net(node(*f)(double, double,double ),double a,double b); // задать сетку через функцию
    void set_net_shifted(node(*f)(double, double, double, double), double a, double b);
};

    //void get_Net2(Field& fld, std::ofstream& fout); //Запись в файл значений сетки по компонентам

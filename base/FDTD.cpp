
#pragma once

#include "FDTD.h"

Field::Field(double dx1, double dy1, int N_x1, int N_y1, int N_t1) {
    dx = dx1;
    dy = dy1;
    N_x = N_x1;
    N_y = N_y1;
    N_t = N_t1;
    bx = dx * N_x;
    by = dy * N_y;
    ax = 0.;
    ay = 0.;
    t=0;
    dt = 1. / c * dx/10.;
    T = dt * N_t;
}
Field::Field(double ax1, double bx1, double ay1, double by1, int N_x1, int N_y1, double T1) {
    //dt высчитывается автоматически с согласованием dx
    ax = ax1;
    bx = bx1;
    ay = ay1;
    by = by1;
    N_x = N_x1;
    N_y = N_y1;
    t=0;
    dx = (bx - ax) / N_x;
    dy = (by - ay) / N_y;
    dt = 1. / c * dx / 10.;
    T = T1;
    N_t = T / dt;
}
Field::Field(double ax1, double bx1, double ay1, double by1, int N_x1, int N_y1,double dt, double T1) {
    //dt высчитывается автоматически с согласованием dx
    ax = ax1;
    bx = bx1;
    ay = ay1;
    by = by1;
    N_x = N_x1;
    N_y = N_y1;
    t = 0;
    dx = (bx - ax) / N_x;
    dy = (by - ay) / N_y;
    T = T1;
    N_t = T / dt;
}
node& Field::Net_index(int i, int j) {
    int index = i + j * N_x;
    return Net[index];
}
node& Field::operator() (int _i, int _j)
{
    int index = _i + _j * N_x;
    return Net[index];
}
void Field::change_dx(double a) {
    dx = a;
    N_x = (bx - ax) / dx;
}
void Field::change_dy(double a) {
    dy = a;
    N_y = (by - ay) / dy;
}
void Field::set_net() {

    std::cout << "Enter initial conditions" << std::endl;
    int size=N_y*N_x;
    Net.resize(size);
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            std::cout << "x=" << i << " y=" << j << std::endl;
            std::cin >> (Net_index(i,j)).Ex >> Net_index(i, j).Ey >> Net_index(i, j).Ez 
            >> Net_index(i, j).Bx >> Net_index(i, j).By >> Net_index(i, j).Bz;
        }
    }

}

void Field::set_net(node(* f)(double, double,double),double a,double b) {
    int size = N_y * N_x;
    Net.resize(size);
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            Net_index(i,j) = f(i * dx,a, b);
        }
    }

}
void Field::set_net_shifted(node(*f)(double, double, double, double), double a, double b) {
    int size = N_y * N_x;
    Net.resize(size);
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            (*this)(i, j) = f(a, b, i * dx, dx);
        }
    }

}
void Field::Maxwell_shifted() {
    //double dt_2=dt;
    //dt=dt/2;

    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
            i_temp_1 = (i + 1) % N_x;
            i_temp_2 = (i - 1 + N_x) % N_x;

            j_temp_1 = (j + 1) % N_y;
            j_temp_2 = (j - 1 + N_y) % N_y;

            (*this)(i, j).Bx -= -c * dt / dy *
                ((*this)(i, j_temp_1).Ez - (*this)(i, j).Ez);
            (*this)(i, j).By += c * dt / dx *
                ((*this)(i_temp_1, j).Ez - (*this)(i, j).Ez);
            (*this)(i, j).Bz -= c * dt *
                (((*this)(i_temp_1, j).Ey - (*this)(i, j).Ey) / dx - ((*this)(i, j_temp_1).Ex - (*this)(i, j).Ex) / dy);
        }
    }
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
            i_temp_1 = (i + 1) % N_x;
            i_temp_2 = (i - 1 + N_x) % N_x;

            j_temp_1 = (j + 1) % N_y;
            j_temp_2 = (j - 1 + N_y) % N_y;

            (*this)(i, j).Ex += +c * dt / 2. / dy *
                ((*this)(i, j).Bz - (*this)(i, j_temp_2).Bz);
            (*this)(i, j).Ey -= -c * dt / 2. / dx *
                ((*this)(i, j).Bz - (*this)(i_temp_2, j).Bz);
            (*this)(i, j).Ez += c * dt / 2. *
                (((*this)(i, j).By - (*this)(i_temp_2, j).By) / dx -
                    ((*this)(i, j).Bx - (*this)(i, j_temp_2).Bx) / dy);
        }
    }
}
void Field::Maxwell() {
    //double dt_2=dt;
    //dt=dt/2;
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
            i_temp_1 = (i + 1) % N_x;
            i_temp_2 =( i - 1+N_x) %N_x;

            j_temp_1 = (j + 1) % N_y;
            j_temp_2 = (j - 1 + N_y) % N_y;

            Net_index(i,j).Ex = Net_index(i,j).Ex + c * dt / 2. / dy * 
                (Net_index(i,j_temp_1).Bz - Net_index(i,j_temp_2).Bz);
            Net_index(i,j).Ey = Net_index(i,j).Ey - c * dt / 2. / dx * 
                (Net_index(i_temp_1,j).Bz - Net_index(i_temp_2,j).Bz);
            Net_index(i,j).Ez = Net_index(i,j).Ez + c * dt / 2. * 
                ((Net_index(i_temp_1,j).By - Net_index(i_temp_2,j).By) / dx -
                    (Net_index(i,j_temp_1).Bx - Net_index(i,j_temp_2).Bx) / dy);
        }
    }
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
            i_temp_1 = (i + 1) % N_x;
            i_temp_2 = (i - 1 + N_x) % N_x;

            j_temp_1 = (j + 1) % N_y;
            j_temp_2 = (j - 1 + N_y) % N_y;

            Net_index(i,j).Bx = Net_index(i,j).Bx - c * dt / 2 / dy * 
                (Net_index(i, j_temp_1).Ez - Net_index(i, j_temp_2).Ez);
            Net_index(i,j).By = Net_index(i,j).By + c * dt / 2 / dx * 
                (Net_index(i_temp_1, j).Ez - Net_index(i_temp_2, j).Ez);
            Net_index(i,j).Bz = Net_index(i,j).Bz - c * dt / 2 * ((Net_index(i_temp_1, j).Ey - 
                Net_index(i_temp_2, j).Ey) / dx -(Net_index(i, j_temp_1).Ex - Net_index(i, j_temp_2).Ex) / dy);
        }
    }
}
void Field::get_Net(std::ofstream& fout) {
    //ofstream fout("results.txt", ios_base::app);

    for (int j = N_y - 1; j >= 0; j--) {
        for (int i = 0; i < N_x; i++) {
            fout << Net_index(i,j).Ex << " " << Net_index(i,j).Ey << " " << Net_index(i,j).Ez << " " << Net_index(i,j).Bx
                << " " << Net_index(i,j).By << " " << Net_index(i,j).Bz << "; ";
        }
        fout << std::endl;
    }
    fout << std::endl;
}

void Field::FDTD(int Num_t) {
    for (int i = 0; i < Num_t; i++) {
        Maxwell();
        t+=dt;
    }
}
void Field::FDTD_shifted(int Num_t) {
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
            i_temp_1 = (i + 1) % N_x;
            i_temp_2 = (i - 1 + N_x) % N_x;

            j_temp_1 = (j + 1) % N_y;
            j_temp_2 = (j - 1 + N_y) % N_y;

            (*this)(i, j).Ex += +c * dt / 2. / dy *
                ((*this)(i, j).Bz - (*this)(i, j_temp_2).Bz);
            (*this)(i, j).Ey -= -c * dt / 2. / dx *
                ((*this)(i, j).Bz - (*this)(i_temp_2, j).Bz);
            (*this)(i, j).Ez += c * dt / 2. *
                (((*this)(i, j).By - (*this)(i_temp_2, j).By) / dx -
                    ((*this)(i, j).Bx - (*this)(i, j_temp_2).Bx) / dy);
        }
    }
    for (int i = 0; i < Num_t; i++) {
        Maxwell_shifted();
        t += dt;
    }
}
void Field::print_Net() {
    for (int j = N_y - 1; j >= 0; j--) {
        for (int i = 0; i < N_x; i++) {
            std::cout << Net_index(i,j).Ex << " " << Net_index(i,j).Ey << " " << Net_index(i,j).Ez << " " << Net_index(i,j).Bx
                << " " << Net_index(i,j).By << " " << Net_index(i,j).Bz << "; ";
        }
        std::cout << std::endl;
    }
}


#pragma once

#include "FDTD.h"

void Field::set_net() {

    std::cout << "Enter initial conditions" << std::endl;
    Net.resize(N_y*N_x);
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            std::cout << "x=" << i << " y=" << j << std::endl;
            std::cin >> (Net_index(i,j)).Ex >> Net_index(i, j).Ey >> Net_index(i, j).Ez 
            >> Net_index(i, j).Bx >> Net_index(i, j).By >> Net_index(i, j).Bz;
        }
    }

}

void Field::set_net(node(* f)(double, double),double b) {
    Net.resize(N_y*N_x);
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            Net_index(i,j) = f(i * dx, b);
        }
    }

}
void Field::Maxwell() {
    for (int j = 0; j < N_y; j++) {
        for (int i = 0; i < N_x; i++) {
            int i_temp_1, i_temp_2, j_temp_1, j_temp_2;
            i_temp_1 = (i + 1) % N_x;
            i_temp_2 =( i - 1+N_x) %N_x;

            j_temp_1 = (j + 1) % N_y;
            j_temp_2 = (j - 1 + N_y) % N_y;

            Net_index(i,j).Ex = Net_index(i,j).Ex + c * dt / 2 / dy * 
                (Net_index(i,j_temp_1).Bz - Net_index(i,j_temp_2).Bz);
            Net_index(i,j).Ey = Net_index(i,j).Ey - c * dt / 2 / dx * 
                (Net_index(i_temp_1,j).Bz - Net_index(i_temp_2,j).Bz);
            Net_index(i,j).Ez = Net_index(i,j).Ez + c * dt / 2 * 
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

void Field::Start()
{
    /*std::cout<<"Enter X_max and Y_max "<<std::endl;
    std::cin>>X_max>>Y_max;
    std::cout << "Cell size "<<X_max<<" * "<<Y_max<<std::endl;*/
    std::cout << "Enter dx and dy " << std::endl;
    std::cin >> dx >> dy;
    std::cout << "Enter how many cells to divide into" << std::endl;
    std::cin >> N_x >> N_y;
    X_max = dx * N_x;
    Y_max = dy * N_y;
    std::cout << "X_max = " << X_max << " Y_max = " << Y_max << std::endl;

    std::cout << "Enter N_t " << std::endl;
    std::cin >> N_t;
    dt = 1 / c / dx;
}


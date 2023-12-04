#include "FDTD.h"
#include <gtest.h>
#include "For_tests.h"
#define Ey_
#define Bz_
TEST(FDTD, chart1) {
    int N = 100;// количество итераций
    Field Test(0.0, 1.0, 0.0, 1.0, 32, 1, 1e-11);
    //Test(ax,bx,ay,by,N_x,N_y,
    //Field Test(dx, dy, N_x, N_y, N_t);
    Test.set_net(f1, Test.get_ax(), Test.get_bx());
    //Test.print_Net();
    std::cout << std::endl;
    std::string str0 = "../../PlotScript/OutFile0.csv";
    get_test_Net(Test, str0, 0);
    //Test.FDTD(Test.get_N_t());
    Test.FDTD(N);
    std::string str100 = "../../PlotScript/OutFileT.csv";
    get_test_Net(Test, str100, Test.get_dt() * N);
    std::cout << Test.get_dt() * N;
    //Test.print_Net();

    Field Test_shifted(0.0, 1.0, 0.0, 1.0, 32, 1, 1e-11);

    Test_shifted.set_net_shifted(f_shifted, Test_shifted.get_ax(), Test_shifted.get_bx());
    //Test_shifted.print_Net();
    std::cout << std::endl;
    std::string str1 = "../../PlotScript/OutFile0_shifted.csv";
    get_test_Net(Test_shifted, str1, 0);
    Test_shifted.FDTD_shifted(N);
    std::string str10 = "../../PlotScript/OutFileT_shifted.csv";
    get_test_Net(Test_shifted, str10, Test_shifted.get_dt() * N);
    //std::cout << Test_shifted.get_dt() * N;

    std::cout << std::endl;
    std::cout << epsilon(Test, Test.get_dt() * N, Test.get_ax(), Test.get_bx());
    std::cout << std::endl;
    std::cout << epsilon(Test_shifted, Test_shifted.get_dt() * N, Test_shifted.get_ax(), Test_shifted.get_bx());
    ASSERT_NO_THROW(3 + 1);
}

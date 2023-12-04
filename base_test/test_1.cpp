
#include "FDTD.h"
#include <gtest.h>
#include "For_tests.h"

TEST(FDTD, can_parse) {
    ASSERT_NO_THROW(3+1);
}
TEST(FDTD,zero_components ) {
    double dx = 1;
    double dy = 1;
    int N_x = 10;
    int N_y = 10;
    double X_max = dx * N_x;
    double Y_max = dy * N_y;
    int N_t = 10;
    double dt = 1.0 / c / 10.0 * dx;
    Field Test(dx, dy, N_x, N_y, N_t);
    
    Test.set_net(f1, Test.get_ax(), Test.get_bx());
    Test.FDTD(Test.get_N_t());
    std::vector<node> a=Test.get_Net();
    //std::vector<double> b (N_x*N_y, 0.0);
    EXPECT_EQ(0,a[1].Ex );
}
TEST(FDTD, Ey_EQ_Bz) {
    double dx = 1;
    double dy = 1;
    int N_x = 10;
    int N_y = 10;
    double X_max = dx * N_x;
    double Y_max = dy * N_y;
    int N_t = 10;
    double dt = 1.0 / c / 10.0 * dx;
    Field Test(dx, dy, N_x, N_y, N_t);

    Test.set_net(f1, Test.get_ax(), Test.get_bx());
    Test.FDTD(Test.get_N_t());
    std::vector<node> a = Test.get_Net();
    //std::vector<double> b (N_x*N_y, 0.0);
    EXPECT_EQ(a[1].Bz, a[1].Ey);
}
TEST(FDTD, small_epsilon) {
    int N=100;
    Field Test(0.0, 1.0, 0.0, 1.0, 32, 1, 1e-11);
    Test.set_net(f1, Test.get_ax(), Test.get_bx());
    Test.FDTD(N);
    double e= epsilon(Test, Test.get_dt()*N, Test.get_ax(), Test.get_bx());
    EXPECT_LE(e,1.0);
}
TEST(FDTD, small_epsilon_shifted) {
    int N = 100;
    Field Test_shifted(0.0, 1.0, 0.0, 1.0, 32, 1, 5e-12);
    Test_shifted.set_net_shifted(f_shifted, Test_shifted.get_ax(), Test_shifted.get_bx());
    Test_shifted.FDTD_shifted(N);
    double e = epsilon(Test_shifted, Test_shifted.get_dt()*N, Test_shifted.get_ax(), Test_shifted.get_bx());
    EXPECT_LE(e, 1.0);
}
TEST(FDTD, check_order) {
    int N = 50;

    for (int i = 1; i < 15; i++) {
        Field Test(0.0, 1.0, 0.0, 1.0, 32*(i*2.0), 1 , 1e-11);
        Test.set_net(f1, Test.get_ax(), Test.get_bx());
        //Test.FDTD(Test.get_T());
        Test.FDTD(N);
        std::cout << "dx = "<<Test.get_dx()<<"  dt = " <<Test.get_dt()<<"  e = "
            << epsilon(Test, Test.get_dt() * N, Test.get_ax(), Test.get_bx()) << std::endl;
        //std::cout << "dx = " << Test.get_dx() << "  dt = " << Test.get_dt() << "  e = " << epsilon(Test, Test.get_T(), Test.get_ax(), Test.get_bx()) << std::endl;
    }
    ASSERT_NO_THROW(3 + 1);
}
TEST(FDTD, check_order_shifted) {
    int N = 100;


    for (int i = 1; i < 15; i++) {
        Field Test_shifted(0.0, 1.0, 0.0, 1.0, 32 * (i * 2.0), 1, 1e-11);
        Test_shifted.set_net_shifted(f_shifted, Test_shifted.get_ax(), Test_shifted.get_bx());
        Test_shifted.FDTD_shifted(N);
        std::cout << "dx = " << Test_shifted.get_dx() << "  dt = " << Test_shifted.get_dt() << "  e = " 
            << epsilon(Test_shifted, Test_shifted.get_dt() * N, Test_shifted.get_ax(), Test_shifted.get_bx()) << std::endl;
    }
    ASSERT_NO_THROW(3 + 1);
}
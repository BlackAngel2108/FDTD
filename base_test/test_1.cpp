
#include "FDTD.h"
#include <gtest.h>

TEST(FDTD, can_parse) {
    ASSERT_NO_THROW(3+1);
}
//TEST(FDTD,zero_components ) {
//    double dx = 1;
//    double dy = 1;
//    int N_x = 10;
//    int N_y = 10;
//    double X_max = dx * N_x;
//    double Y_max = dy * N_y;
//    int N_t = 10;
//    double dt = 1.0 / c / 10.0 * dx;
//    Field Test(dx, dy, N_x, N_y, N_t);
//    Test.FDTD(Test.get_N_t());
//    std::vector<node> a=Test.get_Net();
//    //std::vector<double> b (N_x*N_y, 0.0);
//    EXPECT_EQ(0,a[1].Ex );
//}


#include <iostream>
#include <gtest/gtest.h>
#include "ADT/Matrix.hpp"

using namespace phoenix;

class MatrixTest : public ::testing::Test {
protected:
    Matrix<double>m1;
    Matrix<double>m2;

    virtual void SetUp() {
        Matrix<double>m4(2,3);
        Matrix<double>m5(3, 2);
        m1 = m4;
        m2 = m5;

        m1(0, 0) = 1;
        m1(0, 1) = 2;
        m1(0, 2) = 3;
        m1(1, 0) = 4;
        m1(1, 1) = 5;
        m1(1, 2) = 6;

        m2 = {{7,8},{9,10},{11,12}};
    }
};

TEST_F(MatrixTest, Constructor) {
    EXPECT_EQ(m1.getRows(), 2);
    EXPECT_EQ(m1.getCols(), 3);
    EXPECT_EQ(m2.getRows(), 3);
    EXPECT_EQ(m2.getCols(), 2);
}

TEST_F(MatrixTest, IndexOperator) {
    m1(0, 0) = 1.0;
    m1(1, 2) = 2.5;
    EXPECT_EQ(m1(0, 0), 1.0);
    EXPECT_EQ(m1(1, 2), 2.5);
    EXPECT_EQ(m2(1, 0), 9);
    EXPECT_THROW(m2(5, 5), std::invalid_argument);
}

TEST_F(MatrixTest, UtilOperator) {
    EXPECT_EQ(m1.max(), 6);
    EXPECT_EQ(m1.maxposition(), 5);
    EXPECT_EQ(m1.size(), 6);
}

TEST_F(MatrixTest, Multiply) {
    auto m3 = m1 * m2;
    std::cout<<m3<<std::endl;
    EXPECT_EQ(m3.getRows(), 2);
    EXPECT_EQ(m3.getCols(), 2);
    EXPECT_EQ(m3(0, 0), 58);
    EXPECT_EQ(m3(0, 1), 64);
    EXPECT_EQ(m3(1, 0), 139);
    EXPECT_EQ(m3(1, 1), 154);
}

TEST_F(MatrixTest, Transpose) {
     Matrix<double> m3;
    m3 = m1.transpose();
    EXPECT_EQ(m3.getRows(), 3);
    EXPECT_EQ(m3.getCols(), 2);
    EXPECT_EQ(m3(0, 0), 1);
    EXPECT_EQ(m3(0, 1), 4);
    EXPECT_EQ(m3(1, 0), 2);
    EXPECT_EQ(m3(1, 1), 5);
    EXPECT_EQ(m3(2, 0), 3);
    EXPECT_EQ(m3(2, 1), 6);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

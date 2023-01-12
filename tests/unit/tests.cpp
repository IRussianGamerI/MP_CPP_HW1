#include "gtest/gtest.h"
#include "shared_ptr.h"

class A {
public:
    A() = default;

    virtual ~A() = default;

    virtual char whoami() {
        return 'A';
    }
};

class B : public A {
public:
    B() = default;

    ~B() override = default;

    char whoami() override {
        return 'B';
    }
};

TEST(testConstructors, testDefaultSimpleTypes) {
    smart_pointer::shared_ptr<int> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<double> sp2;
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<char> sp3;
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testDefaultComplexTypes) {
    smart_pointer::shared_ptr<std::string> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<std::vector<int>> sp2;
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<std::map<int, int>> sp3;
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testDefaultArray) {
    smart_pointer::shared_ptr<int[]> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<double[]> sp2;
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<char[]> sp3;
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testMultidimArray) {
    smart_pointer::shared_ptr<int[][3]> sp;
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<double[][3][5]> sp2;
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<char[2][3][5]> sp3;
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testNullptrSimpleTypes) {
    smart_pointer::shared_ptr<int> sp(nullptr);
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<double> sp2(nullptr);
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<char> sp3(nullptr);
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testNullptrComplexTypes) {
    smart_pointer::shared_ptr<std::string> sp(nullptr);
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<std::vector<int>> sp2(nullptr);
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<std::map<int, int>> sp3(nullptr);
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testNullptrArray) {
    smart_pointer::shared_ptr<int[]> sp(nullptr);
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<double[]> sp2(nullptr);
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<char[]> sp3(nullptr);
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testMultidimArrayNullptr) {
    smart_pointer::shared_ptr<int[][3]> sp(nullptr);
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);
    smart_pointer::shared_ptr<double[][3][5]> sp2(nullptr);
    EXPECT_EQ(sp2.get(), nullptr);
    EXPECT_EQ(sp2.use_count(), 0);
    smart_pointer::shared_ptr<char[2][3][5]> sp3(nullptr);
    EXPECT_EQ(sp3.get(), nullptr);
    EXPECT_EQ(sp3.use_count(), 0);
}

TEST(testConstructors, testSimpleCreation) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    EXPECT_EQ(*sp.get(), 5);
    EXPECT_EQ(sp.use_count(), 1);
    smart_pointer::shared_ptr<double> sp2(new double(5.5));
    EXPECT_EQ(*sp2.get(), 5.5);
    EXPECT_EQ(sp2.use_count(), 1);
    smart_pointer::shared_ptr<char> sp3(new char('a'));
    EXPECT_EQ(*sp3.get(), 'a');
    EXPECT_EQ(sp3.use_count(), 1);
}

TEST(testConstructors, testSimleCastCreation) {
    smart_pointer::shared_ptr<A> sp(new B);
    EXPECT_TRUE(sp.get() != nullptr);
    EXPECT_EQ(sp.use_count(), 1);
    EXPECT_EQ(sp->whoami(), 'B');
}

TEST(testConstructors, testSimpleArrayCreation) {
    auto array = new int[5];
    smart_pointer::shared_ptr<int[]> sp(array);
    EXPECT_TRUE(sp.get() != nullptr);
    EXPECT_EQ(sp.use_count(), 1);

    smart_pointer::shared_ptr<char[5]> sp1(new char[5]);
    EXPECT_TRUE(sp1.get() != nullptr);
    EXPECT_EQ(sp1.use_count(), 1);

    auto array2 = new double[2][5];
    smart_pointer::shared_ptr<double[2][5]> sp2(array2);
    EXPECT_TRUE(sp2.get() != nullptr);
    EXPECT_EQ(sp2.use_count(), 1);

    smart_pointer::shared_ptr<char[][5]> sp3(new char[2][5]);
    EXPECT_TRUE(sp3.get() != nullptr);
    EXPECT_EQ(sp3.use_count(), 1);
}

TEST(testConstructors, testCopySimpleTypes) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    smart_pointer::shared_ptr<int> sp2(sp);
    EXPECT_EQ(sp.get(), sp2.get());
    EXPECT_EQ(*sp.get(), 5);
    EXPECT_EQ(*sp2.get(), 5);
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
    smart_pointer::shared_ptr<double> sp3(new double(5.5));
    smart_pointer::shared_ptr<double> sp4(sp3);
    EXPECT_EQ(sp3.get(), sp4.get());
    EXPECT_EQ(*sp3.get(), 5.5);
    EXPECT_EQ(*sp4.get(), 5.5);
    EXPECT_EQ(sp3.use_count(), 2);
    EXPECT_EQ(sp4.use_count(), 2);
    smart_pointer::shared_ptr<char> sp5(new char('a'));
    smart_pointer::shared_ptr<char> sp6(sp5);
    EXPECT_EQ(sp5.get(), sp6.get());
    EXPECT_EQ(*sp5.get(), 'a');
    EXPECT_EQ(*sp6.get(), 'a');
    EXPECT_EQ(sp5.use_count(), 2);
    EXPECT_EQ(sp6.use_count(), 2);
}

TEST(testConstructors, testCopyClasses) {
    smart_pointer::shared_ptr<A> sp(new B);
    smart_pointer::shared_ptr<A> sp2(sp);
    EXPECT_EQ(sp.get(), sp2.get());
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
    smart_pointer::shared_ptr<A> sp3(sp2);
    EXPECT_EQ(sp.get(), sp3.get());
    EXPECT_EQ(sp2.get(), sp3.get());
    EXPECT_EQ(sp.use_count(), 3);
    EXPECT_EQ(sp2.use_count(), 3);
    EXPECT_EQ(sp3.use_count(), 3);
    EXPECT_EQ(sp3->whoami(), 'B');
}

TEST(testConstructors, testCopyArrays) {
    smart_pointer::shared_ptr<int[]> sp(new int[5]);
    smart_pointer::shared_ptr<int[]> sp2(sp);
    EXPECT_EQ(sp.get(), sp2.get());
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
    smart_pointer::shared_ptr<int[]> sp3(sp2);
    EXPECT_EQ(sp.get(), sp3.get());
    EXPECT_EQ(sp2.get(), sp3.get());
}

TEST(testConstructors, testCopyMultidimArrays) {
    smart_pointer::shared_ptr<int[][3]> sp(new int[2][3]);
    smart_pointer::shared_ptr<int[][3]> sp2(sp);
    EXPECT_EQ(sp.get(), sp2.get());
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
    smart_pointer::shared_ptr<int[][3]> sp3(sp2);
    EXPECT_EQ(sp.get(), sp3.get());
    EXPECT_EQ(sp2.get(), sp3.get());
}

TEST(testConstructors, testMoveSimple) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    auto remember = sp.get();
    smart_pointer::shared_ptr<int> sp2(std::move(sp));
    EXPECT_EQ(sp2.get(), remember);
    EXPECT_EQ(*sp2.get(), 5);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(testConstructors, testMoveClasses) {
    smart_pointer::shared_ptr<A> sp(new B);
    auto remember_address = sp.get();
    auto remember_whoami = sp->whoami();
    smart_pointer::shared_ptr<A> sp2(std::move(sp));
    EXPECT_EQ(sp2.get(), remember_address);
    EXPECT_EQ(sp2->whoami(), remember_whoami);
    EXPECT_EQ(sp2.use_count(), 1);
    EXPECT_EQ(sp2->whoami(), 'B');
}

TEST(testConstructors, testMoveArrays) {
    smart_pointer::shared_ptr<int[]> sp(new int[5]);
    auto remember_address = sp.get();
    smart_pointer::shared_ptr<int[]> sp2(std::move(sp));
    EXPECT_EQ(sp2.get(), remember_address);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(testOperators, testCopyAssignmentOperator) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    smart_pointer::shared_ptr<int> sp2(new int(6));
    sp2 = sp;
    EXPECT_EQ(sp.get(), sp2.get());
    EXPECT_EQ(*sp.get(), 5);
    EXPECT_EQ(*sp2.get(), 5);
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);

    smart_pointer::shared_ptr<int> empty;
    empty = sp;
    EXPECT_EQ(empty.get(), sp.get());
    EXPECT_EQ(*empty.get(), 5);
    EXPECT_EQ(empty.use_count(), 3);

    // test self assignment
    smart_pointer::shared_ptr<int> sp3(new int(7));
    sp3 = sp3;
    EXPECT_EQ(*sp3.get(), 7);
    EXPECT_EQ(sp3.use_count(), 1);

    // test cascading assignment
    sp = sp2 = sp3;
    EXPECT_EQ(sp.get(), sp3.get());
    EXPECT_EQ(sp2.get(), sp3.get());
    EXPECT_EQ(*sp.get(), 7);
    EXPECT_EQ(sp.use_count(), 3);
}

TEST(testOperators, testMoveAssignmentOperator) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    smart_pointer::shared_ptr<int> sp2(new int(6));
    auto remember_address = sp.get();
    auto remember_value = *sp;
    sp2 = std::move(sp);
    EXPECT_EQ(sp2.get(), remember_address);
    EXPECT_EQ(*sp2.get(), remember_value);
    EXPECT_EQ(sp2.use_count(), 1);

    smart_pointer::shared_ptr<int> empty;
    empty = std::move(sp2);
    EXPECT_EQ(empty.get(), remember_address);
    EXPECT_EQ(*empty.get(), remember_value);
    EXPECT_EQ(empty.use_count(), 1);

    // test self assignment
    smart_pointer::shared_ptr<int> sp3(new int(7));
    sp3 = std::move(sp3);
    EXPECT_EQ(*sp3.get(), 7);
    EXPECT_EQ(sp3.use_count(), 1);
}

TEST(testOperators, testDereferenceOperator) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    EXPECT_EQ(*sp, 5);
    *sp = 6;
    EXPECT_EQ(*sp, 6);

    smart_pointer::shared_ptr<int[]> sp2(new int[5]{1, 2, 3, 4, 5});
    EXPECT_EQ(*sp2, 1);

    smart_pointer::shared_ptr<int[][3]> sp3(new int[2][3]{{1, 2, 3},
                                                          {4, 5, 6}});
    EXPECT_EQ(**sp3, 1);
    EXPECT_EQ(*(*sp3 + 2), 3);
}

TEST(testOperators, testArrowOperator) {
    smart_pointer::shared_ptr<A> sp(new B);
    EXPECT_EQ(sp->whoami(), 'B');
}

TEST(testOperators, testIndexOperator) {
    smart_pointer::shared_ptr<int[]> sp(new int[5]{1, 2, 3, 4, 5});
    EXPECT_EQ(sp[0], 1);
    EXPECT_EQ(sp[1], 2);
    EXPECT_EQ(sp[2], 3);
    EXPECT_EQ(sp[3], 4);
    EXPECT_EQ(sp[4], 5);

    smart_pointer::shared_ptr<int[][3]> sp2(new int[2][3]{{1, 2, 3},
                                                          {4, 5, 6}});
    EXPECT_EQ(sp2[0][0], 1);
    EXPECT_EQ(sp2[0][1], 2);
    EXPECT_EQ(sp2[0][2], 3);
    EXPECT_EQ(sp2[1][0], 4);
    EXPECT_EQ(sp2[1][1], 5);
    EXPECT_EQ(sp2[1][2], 6);
}

TEST(testOperators, testBoolOperator) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    EXPECT_TRUE(sp);
    smart_pointer::shared_ptr<int> empty;
    EXPECT_FALSE(empty);
}

TEST(testMethods, testGet) {
    auto managed_value = new int(5);
    smart_pointer::shared_ptr<int> sp(managed_value);
    EXPECT_EQ(sp.get(), managed_value);

    auto managed_array = new int[5]{1, 2, 3, 4, 5};
    smart_pointer::shared_ptr<int[]> sp2(managed_array);
    EXPECT_EQ(sp2.get(), managed_array);
}

TEST(testMethods, testResetSimple) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    sp.reset();
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);

    sp.reset(new int(6));
    EXPECT_EQ(*sp.get(), 6);
    EXPECT_EQ(sp.use_count(), 1);

    smart_pointer::shared_ptr<int> empty;
    empty.reset(new int(7));
    EXPECT_EQ(*empty.get(), 7);
    EXPECT_EQ(empty.use_count(), 1);
}

TEST(testMethods, testResetArrays) {
    smart_pointer::shared_ptr<int[]> sp(new int[5]{1, 2, 3, 4, 5});
    sp.reset();
    EXPECT_EQ(sp.get(), nullptr);
    EXPECT_EQ(sp.use_count(), 0);

    sp.reset(new int[5]{6, 7, 8, 9, 10});
    EXPECT_EQ(sp[0], 6);
    EXPECT_EQ(sp[1], 7);
    EXPECT_EQ(sp[2], 8);
    EXPECT_EQ(sp[3], 9);
    EXPECT_EQ(sp[4], 10);

    sp.reset(sp.get());
    EXPECT_EQ(sp[0], 6);
    EXPECT_EQ(sp[1], 7);
    EXPECT_EQ(sp[2], 8);
    EXPECT_EQ(sp[3], 9);
    EXPECT_EQ(sp[4], 10);
}

TEST(testMethods, testUseCount) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    EXPECT_EQ(sp.use_count(), 1);
    smart_pointer::shared_ptr<int> sp2(sp);
    EXPECT_EQ(sp.use_count(), 2);
    EXPECT_EQ(sp2.use_count(), 2);
    sp.reset();
    EXPECT_EQ(sp.use_count(), 0);
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(testLogic, testUseCount) {
    smart_pointer::shared_ptr<int> sp(new int(5));
    EXPECT_EQ(sp.use_count(), 1);
    {
        smart_pointer::shared_ptr<int> sp2(sp);
        EXPECT_EQ(sp.use_count(), 2);
    }
    EXPECT_EQ(sp.use_count(), 1);

    smart_pointer::shared_ptr<int> sp3;
    EXPECT_EQ(sp3.use_count(), 0);
    {
        smart_pointer::shared_ptr<int> sp4(sp3);
        EXPECT_EQ(sp3.use_count(), 0);
        EXPECT_EQ(sp4.use_count(), 0);
    }
}

TEST(testMakeShared, testNotArray) {
    auto sp = smart_pointer::make_shared<int>(5);
    EXPECT_EQ(*sp, 5);
    EXPECT_EQ(sp.use_count(), 1);

    auto sp2 = smart_pointer::make_shared<A>();
    EXPECT_EQ(sp2->whoami(), 'A');
    EXPECT_EQ(sp2.use_count(), 1);
}

TEST(testMakeShared, testArraySizeN) {
    auto sp_arr = smart_pointer::make_shared<int[]>(5);
    EXPECT_NO_FATAL_FAILURE(sp_arr[4] = 1);
    EXPECT_EQ(sp_arr[4], 1);
    EXPECT_EQ(sp_arr.use_count(), 1);
}

TEST(testMakeShared, testArrayCompleteType) {
    auto sp_arr = smart_pointer::make_shared<int[2][3][5]>();
    EXPECT_NO_FATAL_FAILURE(sp_arr[1][2][4] = 1);
    EXPECT_EQ(sp_arr[1][2][4], 1);
    EXPECT_EQ(sp_arr.use_count(), 1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

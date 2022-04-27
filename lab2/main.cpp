#include "vector.h"

using namespace std;

#define OK 0;
#define dendl "\n\n"

int main()
{
    setbuf(stdout, NULL);

    size_t size = 5;

    cout << "\nVector initialization\n\n";
    Vector<int> obj_1(size);
    Vector<int> obj_2(size, 11);
    Vector<int> obj_3(obj_2);

    int *v = new int[size];
    Vector<int> obj_4(size, v);
    delete[] v;

    Vector<int> obj_5 = {1, 2, 3, 4, 5};

    cout << "obj_1: " << obj_1 << endl;
    cout << "obj_2: " << obj_2 << endl;
    cout << "obj_3: " << obj_3 << endl;
    cout << "obj_4: " << obj_4 << endl;
    cout << "obj_5: " << obj_5 << endl;

    cout << "\nVector initialization (float)\n";
    Vector<float> obj_f(size, 5.5);
    cout << "obj_f: " << obj_f << endl;

    cout << "\nVector initialization (double)\n";
    Vector<double> obj_d(size, 105.501);
    cout << "obj_d: " << obj_d << endl;

    cout << "\nArithmetical operations\n\n";

    cout << "Operator+: obj_2 + obj_5 = " << obj_2 + obj_5 << endl;
    cout << "Method sum: obj_2.sum(obj_5) = " << obj_2.sum(obj_5) << endl;
    cout << "Operator-: obj_2 - obj_5 = " << obj_2 - obj_5 << endl;
    cout << "Method sub: obj_2.sub(obj_5) = " << obj_2.sub(obj_5) << endl;
    cout << "Operator*: obj_2 * obj_5 = " << obj_2 * obj_5 << endl;
    cout << "Method mul: obj_2.mul(obj_5) = " << obj_2.mul(obj_5) << endl;
    cout << "Operator/: obj_2 / obj_5 = " << obj_2 / obj_5 << endl;
    cout << "Method div: obj_2.div(obj_5) = " << obj_2.div(obj_5) << dendl;

    cout << "Operator+: obj_2 + 2 = " << obj_2 + 2 << endl;
    cout << "Operator+: 2 + obj_2 = " << 2 + obj_2 << endl;
    cout << "Operator-: obj_2 - 2 = " << obj_2 - 2 << endl;
    cout << "Operator*: obj_2 * 2 = " << obj_2 * 2 << endl;
    cout << "Operator*: 2 * obj_2 = " << 2 * obj_2 << endl;
    cout << "Operator/: obj_2 / 2 = " << obj_2 / 2 << dendl;

    cout << "Operator+=: obj_2 += 2\n" << "obj_2: ";
    obj_2 += 2;
    cout << obj_2 << endl;
    cout << "Operator-=: obj_2 -= obj_5\n" << "obj_2: ";
    obj_2 -= obj_5;
    cout << obj_2 << dendl;

    cout << "Operator=: obj_2 = obj_5\n" << "obj_2: ";
    obj_2 = obj_5;
    cout << obj_2 << dendl;

    cout << "Comparison operations\n\n";

    Vector<int> obj_6 = {1, 2, 3};
    Vector<int> obj_7 = {1, 2, 3};
    Vector<int> obj_8 = {1, 2, 3, 4};
    Vector<int> obj_9 = {1, 2, 4};

    cout << "obj_6: " << obj_6 << endl;
    cout << "obj_7: " << obj_7 << endl;
    cout << "obj_8: " << obj_8 << endl;
    cout << "obj_9: " << obj_9 << dendl;

    cout << "(obj_6 == obj_6) = " << (obj_6 == obj_6) << endl;
    cout << "(obj_6 == obj_7) = " << (obj_6 == obj_7) << endl;
    cout << "(obj_6 == obj_8) = " << (obj_6 == obj_8) << endl;
    cout << "(obj_6 == obj_9) = " << (obj_6 == obj_9) << dendl;

    cout << "(obj_6 != obj_6) = " << (obj_6 != obj_6) << endl;
    cout << "(obj_6 != obj_7) = " << (obj_6 != obj_7) << endl;
    cout << "(obj_6 != obj_8) = " << (obj_6 != obj_8) << endl;
    cout << "(obj_6 != obj_9) = " << (obj_6 != obj_9) << dendl;

    cout << "(obj_6 is_equal obj_6) = " << (obj_6.is_equal(obj_6)) << endl;
    cout << "(obj_6 is_equal obj_7) = " << (obj_6.is_equal(obj_7)) << endl;
    cout << "(obj_6 is_equal obj_8) = " << (obj_6.is_equal(obj_8)) << endl;
    cout << "(obj_6 is_equal obj_9) = " << (obj_6.is_equal(obj_9)) << dendl;

    cout << "(obj_6 is_not_equal obj_6) = " << (obj_6.is_not_equal(obj_6)) << endl;
    cout << "(obj_6 is_not_equal obj_7) = " << (obj_6.is_not_equal(obj_7)) << endl;
    cout << "(obj_6 is_not_equal obj_8) = " << (obj_6.is_not_equal(obj_8)) << endl;
    cout << "(obj_6 is_not_equal obj_9) = " << (obj_6.is_not_equal(obj_9)) << dendl;

    cout << "Negating\n\n";

    Vector<int> obj_10 = {321, -123};

    cout << "obj_10: " << obj_10 << endl;
    obj_10 = -obj_10;
    cout << "-obj_10: " << obj_10 << endl;

    cout << "obj_10: " << obj_10 << endl;
    obj_10 = obj_10.neg();
    cout << "obj_10.neg(): " << obj_10 << endl;

    cout << "Operator[] and method at()\n\n";

    Vector<int> obj_11 = {321, -123, 8, 1, 2, 3};

    cout << "obj_11: " << obj_11 << endl;
    cout << "obj_11[1] = " << obj_11[1] << dendl;
    cout << "obj_11.at(1) = " << obj_11.at(1) << dendl;

    cout << "Mathematical operations\n\n";

    Vector<double> obj_12 = {-1, 2, 3};
    cout << "obj_12: " << obj_12 << endl;
    cout << "vector_length() = " << obj_12.vector_length() << endl;
    cout << "get_unit_vector() = " << obj_12.get_unit_vector() << dendl;

    Vector<double> obj_13 = {1, 2, 3};
    Vector<double> obj_14 = {4, 5, 6};
    cout << "obj_13: " << obj_13 << endl;
    cout << "obj_14: " << obj_14 << endl;
    cout << "scalar_mul: " << obj_13.scalar_mul(obj_14) << dendl;

    Vector<double> obj_15 = {1, 1, 0};
    Vector<double> obj_16 = {1, 0, 1};
    cout << "obj_15: " << obj_15 << endl;
    cout << "obj_16: " << obj_16 << endl;
    cout << "angle: " << obj_15.angle(obj_16) << dendl;

    Vector<double> obj_17 = {1, 2};
    Vector<double> obj_18 = {2, -1};
    cout << "obj_17: " << obj_17 << endl;
    cout << "obj_18: " << obj_18 << endl;
    cout << "are_orthogonal: " << obj_17.are_orthogonal(obj_18) << dendl;
    obj_17 = {3, -1};
    obj_18 = {7, 5};
    cout << "obj_17: " << obj_17 << endl;
    cout << "obj_18: " << obj_18 << endl;
    cout << "are_orthogonal: " << obj_17.are_orthogonal(obj_18) << dendl;

    obj_17 = {1, 2};
    obj_18 = {4, 8};
    cout << "obj_17: " << obj_17 << endl;
    cout << "obj_18: " << obj_18 << endl;
    cout << "are_collinear: " << obj_17.are_collinear(obj_18) << dendl;
    obj_18 = {5, 9};
    cout << "obj_17: " << obj_17 << endl;
    cout << "obj_18: " << obj_18 << endl;
    cout << "are_collinear: " << obj_17.are_collinear(obj_18) << dendl;

    Vector<double> obj_19 = {1.4, 3, 0, -2};
    cout << "obj_19: " << obj_19 << endl;
    cout << "get_unit_vector : " << obj_19.get_unit_vector() << dendl;

    Vector<int> a = {1, 2, 3, 4};
    Vector<double> b = {1.1, 2.2, 3.3, 4.4};

    cout << a << " + " << b << " = " << a + b << endl;

    return OK;
}

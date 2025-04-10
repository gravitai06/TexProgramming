#include <cmath>
#include <iostream>
using namespace std;

class vect {
  static int count;

 public:
  int dim, num;
  double* a;

  vect(int d) : dim(d), num(++count), a(new double[d]) {
    for (int i = 0; i < dim; i++) a[i] = i;
    cout << "Создан вектор " << num << endl;
  }

  ~vect() {
    delete[] a;
    cout << "Удален вектор " << num << endl;
  }

  vect(const vect& v) : dim(v.dim), num(++count), a(new double[v.dim]) {
    for (int i = 0; i < dim; i++) a[i] = v.a[i];
    cout << "Копирован вектор " << num << " из " << v.num << endl;
  }

  vect& operator=(const vect& v) {
    if (this != &v) {
      delete[] a;
      dim = v.dim;
      a = new double[dim];
      for (int i = 0; i < dim; i++) a[i] = v.a[i];
    }
    cout << "Присвоен вектор " << v.num << " в " << num << endl;
    return *this;
  }

  vect operator+(const vect& v) {
    vect r(dim);
    for (int i = 0; i < dim; i++) r.a[i] = a[i] + v.a[i];
    cout << "Сложение векторов " << num << " и " << v.num << endl;
    return r;
  }

  vect operator-(const vect& v) {
    vect r(dim);
    for (int i = 0; i < dim; i++) r.a[i] = a[i] - v.a[i];
    cout << "Вычитание векторов " << num << " и " << v.num << endl;
    return r;
  }

  vect operator-() {
    vect r(dim);
    for (int i = 0; i < dim; i++) r.a[i] = -a[i];
    cout << "Унарный минус вектора " << num << endl;
    return r;
  }

  vect operator*(double k) {
    vect r(dim);
    for (int i = 0; i < dim; i++) r.a[i] = a[i] * k;
    cout << "Умножение вектора " << num << " на " << k << endl;
    return r;
  }

  double operator*(const vect& v) {
    double s = 0;
    for (int i = 0; i < dim; i++) s += a[i] * v.a[i];
    cout << "Скалярное произведение векторов " << num << " и " << v.num << endl;
    return s;
  }

  double length() {
    double s = 0;
    for (int i = 0; i < dim; i++) s += a[i] * a[i];
    return sqrt(s);
  }

  void print() {
    cout << "Вектор " << num << ": ";
    for (int i = 0; i < dim; i++) cout << a[i] << " ";
    cout << endl;
  }
};
int vect::count = 0;

class matr {
  static int count;

 public:
  int dim, num;
  double* b;

  matr(int d) : dim(d), num(++count), b(new double[d * d]) {
    for (int i = 0; i < dim * dim; i++) b[i] = i;
    cout << "Создана матрица " << num << endl;
  }

  ~matr() {
    delete[] b;
    cout << "Удалена матрица " << num << endl;
  }

  matr(const matr& m) : dim(m.dim), num(++count), b(new double[dim * dim]) {
    for (int i = 0; i < dim * dim; i++) b[i] = m.b[i];
    cout << "Копирована матрица " << num << " из " << m.num << endl;
  }

  matr& operator=(const matr& m) {
    if (this != &m) {
      delete[] b;
      dim = m.dim;
      b = new double[dim * dim];
      for (int i = 0; i < dim * dim; i++) b[i] = m.b[i];
    }
    cout << "Присвоена матрица " << m.num << " в " << num << endl;
    return *this;
  }

  matr operator+(const matr& m) {
    matr r(dim);
    for (int i = 0; i < dim * dim; i++) r.b[i] = b[i] + m.b[i];
    cout << "Сложение матриц " << num << " и " << m.num << endl;
    return r;
  }

  matr operator-(const matr& m) {
    matr r(dim);
    for (int i = 0; i < dim * dim; i++) r.b[i] = b[i] - m.b[i];
    cout << "Вычитание матриц " << num << " и " << m.num << endl;
    return r;
  }

  matr operator-() {
    matr r(dim);
    for (int i = 0; i < dim * dim; i++) r.b[i] = -b[i];
    cout << "Унарный минус матрицы " << num << endl;
    return r;
  }

  matr operator*(double k) {
    matr r(dim);
    for (int i = 0; i < dim * dim; i++) r.b[i] = b[i] * k;
    cout << "Умножение матрицы " << num << " на " << k << endl;
    return r;
  }

  matr operator*(const matr& m) {
    matr r(dim);
    for (int i = 0; i < dim; i++)
      for (int j = 0; j < dim; j++) {
        r.b[i * dim + j] = 0;
        for (int k = 0; k < dim; k++)
          r.b[i * dim + j] += b[i * dim + k] * m.b[k * dim + j];
      }
    cout << "Умножение матриц " << num << " и " << m.num << endl;
    return r;
  }

  vect operator*(const vect& v) {
    vect r(dim);
    for (int i = 0; i < dim; i++) {
      r.a[i] = 0;
      for (int j = 0; j < dim; j++) r.a[i] += b[i * dim + j] * v.a[j];
    }
    cout << "Умножение матрицы " << num << " на вектор " << v.num << endl;
    return r;
  }

  void print() {
    cout << "Матрица " << num << ":\n";
    for (int i = 0; i < dim; i++) {
      for (int j = 0; j < dim; j++) cout << b[i * dim + j] << " ";
      cout << endl;
    }
  }
};
int matr::count = 0;

int main() {
  vect v1(3), v2(3);
  vect v3 = v1 + v2;
  v3.print();
  cout << "Длина: " << v3.length() << endl;

  matr m1(3), m2(3);
  matr m3 = m1 * m2;
  m3.print();

  vect v4 = m1 * v1;
  v4.print();

  return 0;
}

#include <cmath>
#include <iostream>

using namespace std;

class vect {
 public:
  int dim;
  double* b;
  int num;
  static int count;

  vect(int d) {
    dim = d;
    num = count++;
    b = new double[dim];
    for (int i = 0; i < dim; i++) {
      b[i] = i;
    }
    cout << "создан вектор " << num << " (размер = " << dim << ")" << endl;
  }

  ~vect() {
    cout << "удален вектор " << num << endl;
    delete[] b;
  }

  vect operator+(const vect& v) {
    cout << "операция сложение векторов " << num << " и " << v.num << endl;
    vect result(dim);
    for (int i = 0; i < dim; i++) {
      result.b[i] = b[i] + v.b[i];
    }
    return result;
  }

  vect operator-(const vect& v) {
    cout << "операция вычитание векторов " << num << " и " << v.num << endl;
    vect result(dim);
    for (int i = 0; i < dim; i++) {
      result.b[i] = b[i] - v.b[i];
    }
    return result;
  }

  vect operator-() {
    cout << "операция отрицания вектора " << num << endl;
    vect result(dim);
    for (int i = 0; i < dim; i++) {
      result.b[i] = -b[i];
    }
    return result;
  }

  vect operator*(double k) {
    cout << "операция умножения вектора " << num << " на " << k << endl;
    vect result(dim);
    for (int i = 0; i < dim; i++) {
      result.b[i] = b[i] * k;
    }
    return result;
  }

  vect& operator=(const vect& v) {
    cout << "операция присваивание вектора " << v.num << " в " << num << endl;
    if (this != &v) {
      delete[] b;
      dim = v.dim;
      b = new double[dim];
      for (int i = 0; i < dim; i++) {
        b[i] = v.b[i];
      }
    }
    return *this;
  }

  double operator*(const vect& v) {
    cout << "операция скалярное произведение векторов " << num << " и " << v.num
         << endl;
    double result = 0;
    for (int i = 0; i < dim; i++) {
      result += b[i] * v.b[i];
    }
    return result;
  }

  void print() const {
    cout << "Вектор " << num << ": ";
    for (int i = 0; i < dim; i++) {
      cout << b[i] << " ";
    }
    cout << endl;
  }
};

int vect::count = 1;

class matr {
 public:
  int num;
  int n, m;
  double** a;
  static int count;

  matr(int rows, int cols) {
    n = rows;
    m = cols;
    num = count++;
    a = new double*[n];
    for (int i = 0; i < n; i++) {
      a[i] = new double[m];
      for (int j = 0; j < m; j++) {
        a[i][j] = i * m + j;
      }
    }
    cout << "Создана Матрица " << num << " (" << n << "x" << m << ")" << endl;
  }

  ~matr() {
    cout << "удалена Матрица " << num << endl;
    for (int i = 0; i < n; i++) {
      delete[] a[i];
    }
    delete[] a;
  }

  matr operator+(const matr& mtr) {
    cout << "операция сложение матриц " << num << " и " << mtr.num << endl;
    matr result(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        result.a[i][j] = a[i][j] + mtr.a[i][j];
      }
    }
    return result;
  }

  matr operator-(const matr& mtr) {
    cout << "операция вычитание матриц " << num << " и " << mtr.num << endl;
    matr result(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        result.a[i][j] = a[i][j] - mtr.a[i][j];
      }
    }
    return result;
  }

  matr operator-() {
    cout << "операция обращение матрицы " << num << endl;
    matr result(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        result.a[i][j] = -a[i][j];
      }
    }
    return result;
    return *this * -1;
  }

  matr operator*(double k) {
    cout << "операция Умножение матрицы " << num << " на " << k << endl;
    matr result(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        result.a[i][j] = a[i][j] * k;
      }
    }
    return result;
  }

  matr& operator=(const matr& mtr) {
    cout << "операция присваивание матрицы " << mtr.num << " в " << num << endl;
    if (this != &mtr) {
      for (int i = 0; i < n; i++) {
        delete[] a[i];
      }
      delete[] a;
      n = mtr.n;
      m = mtr.m;
      a = new double*[n];
      for (int i = 0; i < n; i++) {
        a[i] = new double[m];
      }
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          a[i][j] = mtr.a[i][j];
        }
      }
    }
    return *this;
  }

  matr operator*(const matr& mtr) {
    cout << "операция умножение матриц " << num << " и " << mtr.num << endl;
    matr result(n, mtr.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < mtr.m; j++) {
        result.a[i][j] = 0;
        for (int k = 0; k < m; k++) {
          result.a[i][j] += a[i][k] * mtr.a[k][j];
        }
      }
    }
    return result;
  }

  vect operator*(const vect& v) {
    cout << "операция умножение матрицы " << num << " на вектор " << v.num
         << endl;

    if (m != v.dim) {
      cout << "Ошибка: матрица имеет " << m << ", а вектор — " << v.dim
           << " элементов." << endl;
      return vect(0);
    }

    vect result(n);
    for (int i = 0; i < n; i++) {
      result.b[i] = 0;
      for (int j = 0; j < m; j++) {
        result.b[i] += a[i][j] * v.b[j];
      }
    }
    return result;
  }

   void print() const {
    cout << "Матрица" << num << ":" << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << a[i][j] << " ";
      }
      cout << endl;
    }
  }
};

int matr::count = 1;

int main() {
  vect vec1(4), vec2(4);
  vec1.print();
  vec2.print();

  vect negVec = -vec2;
  negVec.print();

  vect scaledVec = vec1 * 3;
  scaledVec.print();

  double dot = vec1 * vec2;
  cout << "Скалярное произведение: " << dot << endl;

  vect vecSum = vec1 + vec2;
  vecSum.print();

  vect vecDiff = vecSum - vec1;
  vecDiff.print();

  vecSum = vec2;
  vecSum.print();

  matr mat1(3, 4), mat2(3, 4);
  mat1.print();
  mat2.print();

  matr negMat = -mat2;
  negMat.print();

  matr scaledMat = mat1 * 2;
  scaledMat.print();

  matr matSum = mat1 + mat2;
  matSum.print();

  matr matDiff = matSum - mat1;
  matDiff.print();

  matSum = scaledMat;
  matSum.print();

  vect matVecRes = mat2 * vec2;
  matVecRes.print();

  return 0;
}

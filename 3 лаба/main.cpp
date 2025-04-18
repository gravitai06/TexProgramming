#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Point {
 protected:
  double x, y;

 public:
  Point(double x_val = 0, double y_val = 0) : x(x_val), y(y_val) {}
  virtual ~Point() {}

  virtual void draw() const = 0;
  virtual void erase() const = 0;
  virtual void move(double dx, double dy) = 0;
  virtual void rotate(double angle_degrees) = 0;
};

class Line : public Point {
 protected:
  double x2, y2;

 public:
  Line(double x1, double y1, double x2, double y2)
      : Point(x1, y1), x2(x2), y2(y2) {}

  void draw() const override {
    cout << "Рисуем линию от (" << x << ", " << y << ") до (" << x2 << ", "
         << y2 << ")" << endl;
  }

  void erase() const override { cout << "Стираем линию" << endl; }

  void move(double dx, double dy) override {
    x += dx;
    y += dy;
    x2 += dx;
    y2 += dy;
  }

  void rotate(double angle_degrees) override {
    cout << "Поворот линии не реализован (упрощение)" << endl;
  }
};

class Parallelogram : virtual public Point {
 protected:
  double width, height;
  double angle;

 public:
  Parallelogram(double x, double y, double w, double h, double a)
      : Point(x, y), width(w), height(h), angle(a) {}

  void draw() const override {
    cout << "Рисуем параллелограмм с вершиной (" << x << ", " << y
         << "), шириной " << width << ", высотой " << height << ", углом "
         << angle << "°" << endl;
  }

  void erase() const override { cout << "Стираем параллелограмм" << endl; }

  void move(double dx, double dy) override {
    x += dx;
    y += dy;
  }

  void rotate(double angle_degrees) override {
    angle += angle_degrees;
    cout << "Повернули параллелограмм. Новый угол: " << angle << "°" << endl;
  }
};

class Rectangle : public Parallelogram {
 public:
  Rectangle(double x, double y, double w, double h)
      : Parallelogram(x, y, w, h, 90) {}

  void draw() const override {
    cout << "Рисуем прямоугольник с вершиной (" << x << ", " << y
         << "), шириной " << width << ", высотой " << height << endl;
  }

  void erase() const override { cout << "Стираем прямоугольник" << endl; }
};

class Rhombus : public Parallelogram {
 public:
  Rhombus(double x, double y, double diag1, double diag2)
      : Parallelogram(x, y, diag1, diag2, 60) {}

  void draw() const override {
    cout << "Рисуем ромб с вершиной (" << x << ", " << y << "), диагоналями "
         << width << " и " << height << endl;
  }

  void erase() const override { cout << "Стираем ромб" << endl; }
};

class Square : public virtual Parallelogram {
 public:
  Square(double x, double y, double side)
      : Point(x, y), Parallelogram(x, y, side, side, 90) {}

  void draw() const override {
    cout << "Рисуем квадрат с вершиной (" << x << ", " << y << "), сторона "
         << width << endl;
  }

  void erase() const override { cout << "Стираем квадрат" << endl; }

  void rotate(double angle_degrees) override {
    cout << "Квадрат повернут на " << angle_degrees
         << "° (но остался квадратом)" << endl;
  }
};

int main() {
  Point* shapes[5];

  shapes[0] = new Line(0, 0, 3, 4);
  shapes[1] = new Square(1, 1, 5);
  shapes[2] = new Rhombus(2, 2, 6, 6);
  shapes[3] = new Rectangle(4, 4, 5, 7);
  shapes[4] = new Parallelogram(5, 5, 6, 8, 70);

  for (int i = 0; i < 5; ++i) {
    shapes[i]->draw();
    shapes[i]->move(1, 1);
    shapes[i]->rotate(15);
    shapes[i]->erase();
    cout << "--------" << endl;
  }

  for (int i = 0; i < 5; ++i) {
    delete shapes[i];
  }

  return 0;
}

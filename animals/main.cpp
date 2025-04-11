#include <iostream>
using namespace std;

class Animal {
 private:
  int age;
  double weight;

 public:
  Animal(int a, double w) : age(a), weight(w) {}

  void eat() { set_weight(weight + 0.5); }
  void sleep() { set_weight(weight - 0.2); }

  void get_info() {
    cout << "Возраст: " << age << " лет\nВес: " << get_weight() << " кг"
         << endl;
  }

  int get_age() const { return age; }
  double get_weight() const { return weight; }
  void set_weight(double new_weight) { weight = new_weight; }
};

class Dog : public Animal {
 private:
  string breed;

 public:
  Dog(string b) : Animal(5, 20), breed(b) {}

  void bark() { cout << "Собака лает: Гав" << endl; }

  void show_breed() { cout << "Порода: " << breed << endl; }
};

class Fish : public Animal {
 private:
  string water_type;

 public:
  Fish(string wt) : Animal(6, 0.5), water_type(wt) {}

  void swim() {
    set_weight(get_weight() - 0.1);
    cout << "Рыба поплавала. Теперь ее вес: " << get_weight() << " кг" << endl;
  }

  void show_water_type() { cout << "Тип воды: " << water_type << endl; }
};

int main() {
  Dog dog("Амстафф");
  Fish fish("Пресная вода");

  dog.get_info();
  dog.show_breed();
  dog.bark();
  dog.eat();
  cout << "Собака поела. Ее вес: " << dog.get_weight() << " кг" << endl;

  fish.get_info();
  fish.show_water_type();
  fish.swim();
  fish.sleep();
  cout << "Рыба поспала. Ее вес: " << fish.get_weight() << " кг" << endl;

  return 0;
}

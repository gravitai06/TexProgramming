#include <iostream>
#include <string>

using namespace std;

class Car {
 public:
  string brand;
  int year;
  double price;
  Car* next;

  Car(string brand, int year, double price) {
    this->brand = brand;
    this->year = year;
    this->price = price;
    this->next = nullptr;
  }
};

class CarList {
 private:
  Car* head;

 public:
  CarList() { head = nullptr; }

  void addToBeginning(string brand, int year, double price) {
    Car* newCar = new Car(brand, year, price);
    newCar->next = head;
    head = newCar;
  }

  void addToEnd(string brand, int year, double price) {
    Car* newCar = new Car(brand, year, price);
    if (head == nullptr) {
      head = newCar;
      return;
    }
    Car* temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newCar;
  }

  void addAfter(string targetBrand, string brand, int year, double price) {
    Car* temp = head;
    while (temp != nullptr && temp->brand != targetBrand) {
      temp = temp->next;
    }
    if (temp != nullptr) {
      Car* newCar = new Car(brand, year, price);
      newCar->next = temp->next;
      temp->next = newCar;
    } else {
      cout << "Элемент с маркой " << targetBrand << " не найден." << endl;
    }
  }

  void addBefore(string targetBrand, string brand, int year, double price) {
    if (head == nullptr) {
      cout << "Список пуст." << endl;
      return;
    }
    if (head->brand == targetBrand) {
      addToBeginning(brand, year, price);
      return;
    }
    Car* temp = head;
    while (temp->next != nullptr && temp->next->brand != targetBrand) {
      temp = temp->next;
    }
    if (temp->next != nullptr) {
      Car* newCar = new Car(brand, year, price);
      newCar->next = temp->next;
      temp->next = newCar;
    } else {
      cout << "Элемент с маркой " << targetBrand << " не найден." << endl;
    }
  }

  void deleteElement(string targetBrand) {
    if (head == nullptr) {
      cout << "Список пуст." << endl;
      return;
    }
    if (head->brand == targetBrand) {
      Car* temp = head;
      head = head->next;
      delete temp;
      return;
    }
    Car* temp = head;
    while (temp->next != nullptr && temp->next->brand != targetBrand) {
      temp = temp->next;
    }
    if (temp->next != nullptr) {
      Car* toDelete = temp->next;
      temp->next = temp->next->next;
      delete toDelete;
    } else {
      cout << "Элемент с маркой " << targetBrand << " не найден." << endl;
    }
  }

  void printList() {
    Car* temp = head;
    while (temp != nullptr) {
      cout << "Марка: " << temp->brand << ", Год: " << temp->year
           << ", Цена: " << temp->price << endl;
      temp = temp->next;
    }
  }
};

int main() {
  CarList cars;

  cars.addToEnd("Toyota", 2020, 15000.0);
  cars.addToEnd("Honda", 2019, 14000.0);
  cars.addToBeginning("Ford", 2021, 16000.0);

  cout << "Список машин:" << endl;
  cars.printList();

  cars.addAfter("Toyota", "BMW", 2018, 20000.0);
  cout << "\nСписок после добавления BMW после Toyota:" << endl;
  cars.printList();

  cars.addBefore("Honda", "Audi", 2017, 18000.0);
  cout << "\nСписок после добавления Audi перед Honda:" << endl;
  cars.printList();

  cars.deleteElement("Toyota");
  cout << "\nСписок после удаления Toyota:" << endl;
  cars.printList();

  return 0;
}

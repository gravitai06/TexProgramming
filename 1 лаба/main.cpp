#include <iostream>
#include <string>

using namespace std;

struct Car {
  string brand;
  int year;
  double price;
  Car* next;
};

Car* addToBeginning(Car* head, string brand, int year, double price) {
  Car* newCar = new Car;
  newCar->brand = brand;
  newCar->year = year;
  newCar->price = price;
  newCar->next = head;
  return newCar;
}

Car* addToEnd(Car* head, string brand, int year, double price) {
  Car* newCar = new Car;
  newCar->brand = brand;
  newCar->year = year;
  newCar->price = price;
  newCar->next = nullptr;

  if (head == nullptr) {
    return newCar;
  }

  Car* temp = head;
  while (temp->next != nullptr) {
    temp = temp->next;
  }
  temp->next = newCar;
  return head;
}

void addAfter(Car* head, string targetBrand, string brand, int year,
              double price) {
  Car* temp = head;
  while (temp != nullptr && temp->brand != targetBrand) {
    temp = temp->next;
  }
  if (temp != nullptr) {
    Car* newCar = new Car;
    newCar->brand = brand;
    newCar->year = year;
    newCar->price = price;
    newCar->next = temp->next;
    temp->next = newCar;
  } else {
    cout << "Элемент с маркой " << targetBrand << " не найден." << endl;
  }
}

Car* addBefore(Car* head, string targetBrand, string brand, int year,
               double price) {
  if (head == nullptr) {
    cout << "Список пуст." << endl;
    return head;
  }

  if (head->brand == targetBrand) {
    return addToBeginning(head, brand, year, price);
  }

  Car* temp = head;
  while (temp->next != nullptr && temp->next->brand != targetBrand) {
    temp = temp->next;
  }
  if (temp->next != nullptr) {
    Car* newCar = new Car;
    newCar->brand = brand;
    newCar->year = year;
    newCar->price = price;
    newCar->next = temp->next;
    temp->next = newCar;
  } else {
    cout << "Элемент с маркой " << targetBrand << " не найден." << endl;
  }
  return head;
}

Car* deleteElement(Car* head, string targetBrand) {
  if (head == nullptr) {
    cout << "Список пуст." << endl;
    return head;
  }

  if (head->brand == targetBrand) {
    Car* temp = head;
    head = head->next;
    delete temp;
    return head;
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
  return head;
}

void printList(Car* head) {
  Car* temp = head;
  while (temp != nullptr) {
    cout << "Марка: " << temp->brand << ", Год: " << temp->year
         << ", Цена: " << temp->price << endl;
    temp = temp->next;
  }
}

int main() {
  Car* head = nullptr;

  head = addToEnd(head, "Toyota", 2020, 15000.0);
  head = addToEnd(head, "Honda", 2019, 14000.0);
  head = addToBeginning(head, "Ford", 2021, 16000.0);

  cout << "Список машин:" << endl;
  printList(head);

  addAfter(head, "Toyota", "BMW", 2018, 20000.0);
  cout << "\nСписок после добавления BMW после Toyota:" << endl;
  printList(head);

  head = addBefore(head, "Honda", "Audi", 2017, 18000.0);
  cout << "\nСписок после добавления Audi перед Honda:" << endl;
  printList(head);

  head = deleteElement(head, "Toyota");
  cout << "\nСписок после удаления Toyota:" << endl;
  printList(head);

  return 0;
}
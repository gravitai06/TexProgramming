#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Car {
 public:
  string brand;
  string model;
  int year;
  double price;
};

string carToString(const Car& c) {
  return c.brand + " " + c.model + " " + to_string(c.year) + " " +
         to_string(c.price);
}

Car stringToCar(const string& line) {
  Car c;
  istringstream iss(line);
  iss >> c.brand >> c.model >> c.year >> c.price;
  return c;
}

void saveToFile(const vector<Car>& cars, const string& filename) {
  ofstream file(filename);
  for (const auto& c : cars) {
    file << carToString(c) << "\n";
  }
}

vector<Car> loadFromFile(const string& filename) {
  vector<Car> cars;
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      cars.push_back(stringToCar(line));
    }
  }
  return cars;
}

void addCar(vector<Car>& cars) {
  Car c;
  cout << "Введите марку: ";
  cin >> c.brand;
  cout << "Введите модель: ";
  cin >> c.model;
  cout << "Введите год выпуска: ";
  cin >> c.year;
  cout << "Введите цену: ";
  cin >> c.price;
  cars.push_back(c);
}

void deleteCar(vector<Car>& cars) {
  cout << "Введите номер машины для удаления (1 - " << cars.size() << "): ";
  int idx;
  cin >> idx;
  if (idx >= 1 && idx <= (int)cars.size()) {
    cars.erase(cars.begin() + (idx - 1));
    cout << "Машина удалена.\n";
  } else {
    cout << "Неверный номер.\n";
  }
}

void printCars(const vector<Car>& cars) {
  cout << "Список машин:\n";
  cout << fixed << setprecision(0);
  for (int i = 0; i < (int)cars.size(); i++) {
    cout << (i + 1) << ": " << cars[i].brand << " " << cars[i].model
         << ", год: " << cars[i].year << ", цена: " << cars[i].price << "\n";
  }
}

void updateCar(vector<Car>& cars) {
  cout << "Введите номер машины для редактирования (1 - " << cars.size()
       << "): ";
  int idx;
  cin >> idx;
  if (idx < 1 || idx > (int)cars.size()) {
    cout << "Неверный номер.\n";
    return;
  }
  Car& c = cars[idx - 1];

  cout << "Редактирование машины #" << idx
       << " (оставьте пустым и нажмите Enter, чтобы пропустить поле):\n";

  cout << "Текущая марка: " << c.brand << "\nВведите новую марку: ";
  string input;
  cin.ignore();
  getline(cin, input);
  if (!input.empty()) c.brand = input;

  cout << "Текущая модель: " << c.model << "\nВведите новую модель: ";
  getline(cin, input);
  if (!input.empty()) c.model = input;

  cout << "Текущий год выпуска: " << c.year << "\nВведите новый год выпуска: ";
  getline(cin, input);
  if (!input.empty()) c.year = stoi(input);

  cout << "Текущая цена: " << c.price << "\nВведите новую цену: ";
  getline(cin, input);
  if (!input.empty()) c.price = stod(input);

  cout << "Машина обновлена.\n";
}

int main() {
  vector<Car> cars;
  const string filename = "cars.txt";

  cars = loadFromFile(filename);

  while (true) {
    cout << "\nМеню:\n";
    cout << "1. Показать все машины\n";
    cout << "2. Добавить машину\n";
    cout << "3. Удалить машину\n";
    cout << "4. Сохранить и выйти\n";
    cout << "5. Обновить машину\n";
    cout << "Выберите действие: ";

    int choice;
    cin >> choice;
    switch (choice) {
      case 1:
        printCars(cars);
        break;
      case 2:
        addCar(cars);
        break;
      case 3:
        deleteCar(cars);
        break;
      case 4:
        saveToFile(cars, filename);
        cout << "Данные сохранены. Выход.\n";
        return 0;
      case 5:
        updateCar(cars);
        break;

      default:
        cout << "Неверный выбор.\n";
    }
  }
}

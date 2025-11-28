#include <iostream>
#include <string>

using namespace std;

// Базовый класс
class Base {
public:
    // Конструктор по умолчанию
    Base() {
        cout << "Вызван конструктор Base()" << endl;
    }

    // Виртуальный деструктор
    virtual ~Base() {
        cout << "Вызван деструктор ~Base()" << endl;
    }

    // Обычный метод
    void SimpleMethod() {
        cout << "Вызван Base::SimpleMethod()" << endl;
    }

    // Виртуальный метод
    virtual void VirtualMethod() {
        cout << "Вызван Base::VirtualMethod()" << endl;
    }
};

// Класс-наследник
class Desc : public Base {
public:
    // Конструктор по умолчанию
    Desc() {
        cout << "Вызван конструктор Desc()" << endl;
    }

    // Деструктор
    ~Desc() override {
        cout << "Вызван деструктор ~Desc()" << endl;
    }

    // Переопределяем обычный метод (это перекрытие, hiding)
    void SimpleMethod() {
        cout << "Вызван Desc::SimpleMethod()" << endl;
    }

    // Переопределяем виртуальный метод
    void VirtualMethod() override {
        cout << "Вызван Desc::VirtualMethod()" << endl;
    }
};
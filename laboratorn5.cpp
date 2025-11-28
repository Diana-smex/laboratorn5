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

    // 2. Конструктор из указателя (переименуем чтобы не было конфликта)
    Base(Base* ptr) {
        cout << "Вызван конструктор Base(Base*)" << endl;
    }

    // 3. Конструктор  (это конструктор копирования)
    Base(Base& ref) {
        cout << "Вызван конструктор копирования Base(Base&)" << endl;
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
    // 2. Конструктор из указателя
    Desc(Desc* ptr) : Base(ptr) {
        cout << "Вызван конструктор Desc(Desc*)" << endl;
    }

    // 3. Конструктор 
    Desc(Desc& ref) : Base(ref) {
        cout << "Вызван конструктор копирования Desc(Desc&)" << endl;
    }

    // Деструктор
    ~Desc() override {
        cout << "Вызван деструктор ~Desc()" << endl;
    }

    // Переопределяем обычный метод 
    void SimpleMethod() {
        cout << "Вызван Desc::SimpleMethod()" << endl;
    }

    // Переопределяем виртуальный метод
    void VirtualMethod() override {
        cout << "Вызван Desc::VirtualMethod()" << endl;
    }
};
// Функции для экспериментов с передачей параметров
void func_by_value(Base obj) {
    cout << "--- ВНУТРИ func_by_value ---" << endl;
    obj.SimpleMethod();
    obj.VirtualMethod();
    cout << "--- КОНЕЦ func_by_value ---" << endl;
}

void func_by_pointer(Base* obj) {
    cout << "--- ВНУТРИ func_by_pointer ---" << endl;
    obj->SimpleMethod();
    obj->VirtualMethod();
    cout << "--- КОНЕЦ func_by_pointer ---" << endl;
}

void func_by_reference(Base& obj) {
    cout << "--- ВНУТРИ func_by_reference ---" << endl;
    obj.SimpleMethod();
    obj.VirtualMethod();
    cout << "--- КОНЕЦ func_by_reference ---" << endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    cout << "=== ЭКСПЕРИМЕНТ 1: Создание объектов ===" << endl;

    cout << "\n1. Создаем Base статически:" << endl;
    Base obj_base;

    cout << "\n2. Создаем Desc статически:" << endl;
    Desc obj_desc;

    cout << "\n3. Создаем Base динамически:" << endl;
    Base* ptr_base = new Base();

    cout << "\n4. Создаем Desc динамически:" << endl;
    Desc* ptr_desc = new Desc();

    cout << "\n=== ЭКСПЕРИМЕНТ 2: Вызов методов ===" << endl;

    cout << "\n--- Через объекты ---" << endl;
    cout << "obj_base.SimpleMethod(): "; obj_base.SimpleMethod();
    cout << "obj_base.VirtualMethod(): "; obj_base.VirtualMethod();

    cout << "obj_desc.SimpleMethod(): "; obj_desc.SimpleMethod();
    cout << "obj_desc.VirtualMethod(): "; obj_desc.VirtualMethod();

    cout << "\n--- Через указатели на свой класс ---" << endl;
    cout << "ptr_base->SimpleMethod(): "; ptr_base->SimpleMethod();
    cout << "ptr_base->VirtualMethod(): "; ptr_base->VirtualMethod();

    cout << "ptr_desc->SimpleMethod(): "; ptr_desc->SimpleMethod();
    cout << "ptr_desc->VirtualMethod(): "; ptr_desc->VirtualMethod();

    cout << "\n=== ЭКСПЕРИМЕНТ 3: Указатель базового класса на объект потомка ===" << endl;
    Base* ptr_base_to_desc = new Desc();
    cout << "ptr_base_to_desc->SimpleMethod(): "; ptr_base_to_desc->SimpleMethod();
    cout << "ptr_base_to_desc->VirtualMethod(): "; ptr_base_to_desc->VirtualMethod();

    cout << "\n=== Очистка динамической памяти ===" << endl;
    delete ptr_base;
    delete ptr_desc;
    delete ptr_base_to_desc;

    cout << "=== ЭКСПЕРИМЕНТ 4: Передача объектов в функции ===" << endl;

    cout << "\n--- Создаем объекты для экспериментов ---" << endl;
    Base base_obj;
    Desc desc_obj;

    cout << "\n--- 1. Передача Base по значению ---" << endl;
    func_by_value(base_obj);

    cout << "\n--- 2. Передача Desc по значению ---" << endl;
    func_by_value(desc_obj);  // ВНИМАНИЕ: здесь сработает конструктор копирования Base!

    cout << "\n--- 3. Передача Base по указателю ---" << endl;
    func_by_pointer(&base_obj);

    cout << "\n--- 4. Передача Desc по указателю ---" << endl;
    func_by_pointer(&desc_obj);

    cout << "\n--- 5. Передача Base по ссылке ---" << endl;
    func_by_reference(base_obj);

    cout << "\n--- 6. Передача Desc по ссылке ---" << endl;
    func_by_reference(desc_obj);

    cout << "\n=== Конец экспериментов ===" << endl;


    return 0;
}
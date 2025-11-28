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

    // Конструктор копирования (const версия)
    Base(const Base& other) {
        cout << "Вызван конструктор копирования Base(const Base&)" << endl;
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

    // Конструктор копирования (const версия)  
    Desc(const Desc& other) : Base(other) {
        cout << "Вызван конструктор копирования Desc(const Desc&)" << endl;
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

// Функции возврата объектов
Base return_by_value_static() {
    cout << "--- ВНУТРИ return_by_value_static ---" << endl;
    Base local_obj;
    cout << "--- ВОЗВРАЩАЕМ local_obj ---" << endl;
    return local_obj;  // Возврат по значению - создается копия!
}

Base* return_by_pointer_static() {
    cout << "--- ВНУТРИ return_by_pointer_static ---" << endl;
    Base local_obj;
    cout << "--- ВОЗВРАЩАЕМ &local_obj ---" << endl;
    return &local_obj;  // ОПАСНО! Возвращаем адрес локального объекта!
}

Base& return_by_reference_static() {
    cout << "--- ВНУТРИ return_by_reference_static ---" << endl;
    Base local_obj;
    cout << "--- ВОЗВРАЩАЕМ local_obj по ссылке ---" << endl;
    return local_obj;  // ОПАСНО! Возвращаем ссылку на локальный объект!
}

Base* return_by_pointer_dynamic() {
    cout << "--- ВНУТРИ return_by_pointer_dynamic ---" << endl;
    Base* dynamic_obj = new Base();
    cout << "--- ВОЗВРАЩАЕМ dynamic_obj ---" << endl;
    return dynamic_obj;  // БЕЗОПАСНО: объект в куче
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
    func_by_value(desc_obj);  

    cout << "\n--- 3. Передача Base по указателю ---" << endl;
    func_by_pointer(&base_obj);

    cout << "\n--- 4. Передача Desc по указателю ---" << endl;
    func_by_pointer(&desc_obj);

    cout << "\n--- 5. Передача Base по ссылке ---" << endl;
    func_by_reference(base_obj);

    cout << "\n--- 6. Передача Desc по ссылке ---" << endl;
    func_by_reference(desc_obj);

    cout << "\n";

    cout << "\n=== ЭКСПЕРИМЕНТ 5: Возврат объектов из функций ===" << endl;

    cout << "\n--- 1. Возврат по значению (static) ---" << endl;
    Base obj1 = return_by_value_static();

    cout << "\n--- 2. Возврат по указателю (static) - ОПАСНО! ---" << endl;
    Base* ptr1 = return_by_pointer_static();
  
    cout << "\n--- 3. Возврат по ссылке (static) - ОПАСНО! ---" << endl;
    Base& ref1 = return_by_reference_static();

    cout << "\n--- 4. Возврат по указателю (dynamic) - безопасно ---" << endl;
    Base* ptr2 = return_by_pointer_dynamic();
    cout << "Используем ptr2: ";
    ptr2->SimpleMethod();
    delete ptr2;  

    cout << "\n=== Конец эксперимента 5 ===" << endl;

    return 0;
}
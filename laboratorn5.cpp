#include <iostream>
#include <string>
#include <memory>
#include <vector>

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

    // Методы для проверки типа
    virtual string classname() const {
        return "Base";
    }

    virtual bool isA(const string& className) const {
        return className == "Base";
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

    // Переопределяем методы проверки типа
    string classname() const override {
        return "Desc";
    }

    bool isA(const string& className) const override {
        return (className == "Desc") || Base::isA(className);
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

// Функции для экспериментов с умными указателями
void unique_ptr_experiment() {
    cout << "\n--- UNIQUE_PTR эксперимент ---" << endl;

    cout << "Создаем unique_ptr:" << endl;
    unique_ptr<Base> uptr = make_unique<Base>();

    cout << "Используем unique_ptr:" << endl;
    uptr->SimpleMethod();

    cout << "Выходим из функции - автоматическое удаление!" << endl;
    
}

void shared_ptr_experiment() {
    cout << "\n--- SHARED_PTR эксперимент ---" << endl;

    cout << "Создаем shared_ptr:" << endl;
    shared_ptr<Base> sptr1 = make_shared<Base>();

    cout << "Копируем shared_ptr (счетчик ссылок увеличивается):" << endl;
    shared_ptr<Base> sptr2 = sptr1;

    cout << "Используем оба указателя:" << endl;
    sptr1->SimpleMethod();
    sptr2->SimpleMethod();

    cout << "Выходим из функции - автоматическое удаление когда счетчик = 0!" << endl;
}

void raw_pointer_problem() {
    cout << "\n--- ПРОБЛЕМА ОБЫЧНЫХ УКАЗАТЕЛЕЙ ---" << endl;

    cout << "Создаем динамический объект:" << endl;
    Base* raw_ptr = new Base();

    cout << "Используем объект:" << endl;
    raw_ptr->SimpleMethod();

    cout << "Выходим из функции - ПАМЯТЬ НЕ ОСВОБОЖДЕНА!" << endl;
}

// Функции для экспериментов с приведением типов
void dangerous_cast_example() {
    cout << "\n--- ОПАСНОЕ ПРИВЕДЕНИЕ ТИПОВ ---" << endl;

    Base* base_ptr = new Base();  // Это действительно Base

    // ОПАСНОЕ приведение - без проверки!
    Desc* desc_ptr = (Desc*)base_ptr;  // Принудительное приведение

    cout << "Опасное приведение выполнено: ";
    desc_ptr->SimpleMethod();  // Может привести к краху!

    delete base_ptr;
}

void safe_cast_example() {
    cout << "\n--- БЕЗОПАСНОЕ ПРИВЕДЕНИЕ ТИПОВ ---" << endl;

    // Случай 1: Base* на самом деле указывает на Desc
    Base* base_ptr1 = new Desc();

    cout << "1. Проверка через isA(): ";
    if (base_ptr1->isA("Desc")) {
        cout << "Это Desc! Можно безопасно привести" << endl;
        Desc* desc_ptr = dynamic_cast<Desc*>(base_ptr1);
        desc_ptr->SimpleMethod();
    }
    else {
        cout << "Это не Desc!" << endl;
    }

    // Случай 2: Base* действительно указывает на Base
    Base* base_ptr2 = new Base();

    cout << "2. Проверка через dynamic_cast: ";
    Desc* desc_ptr2 = dynamic_cast<Desc*>(base_ptr2);
    if (desc_ptr2) {
        cout << "Приведение успешно!" << endl;
        desc_ptr2->SimpleMethod();
    }
    else {
        cout << "Приведение НЕ удалось - это не Desc!" << endl;
    }

    delete base_ptr1;
    delete base_ptr2;
}

void classname_example() {
    cout << "\n--- ПРОВЕРКА ТИПА ЧЕРЕЗ classname() ---" << endl;

    Base* obj1 = new Base();
    Base* obj2 = new Desc();

    cout << "obj1->classname(): " << obj1->classname() << endl;
    cout << "obj2->classname(): " << obj2->classname() << endl;

    // проблема classname() то что надо сравнивать строки
    if (obj2->classname() == "Desc") {
        cout << "obj2 действительно Desc!" << endl;
    }

    delete obj1;
    delete obj2;
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

    cout << "\n=== ЭКСПЕРИМЕНТ 6: Умные указатели ===" << endl;

    unique_ptr_experiment();
    shared_ptr_experiment();
    raw_pointer_problem();

    cout << "\n=== Демонстрация передачи умных указателей ===" << endl;

    // unique_ptr нельзя копировать, но можно перемещать
    cout << "--- Перемещение unique_ptr ---" << endl;
    unique_ptr<Base> uptr1 = make_unique<Base>();
    cout << "Перемещаем uptr1 в uptr2:" << endl;
    unique_ptr<Base> uptr2 = move(uptr1);
    if (!uptr1) {
        cout << "uptr1 теперь пустой!" << endl;
    }

    // shared_ptr можно копировать
    cout << "--- Копирование shared_ptr ---" << endl;
    shared_ptr<Base> sptr1 = make_shared<Base>();
    cout << "Копируем sptr1 в sptr2:" << endl;
    shared_ptr<Base> sptr2 = sptr1;
    cout << "Оба указателя работают:" << endl;
    sptr1->SimpleMethod();
    sptr2->SimpleMethod();

    cout << "\n=== ЭКСПЕРИМЕНТ 7: Проверка типов ===" << endl;

    classname_example();
    safe_cast_example();


    cout << "\n=== Финальная демонстрация ===" << endl;

    // Создаем разные объекты в одном контейнере
    vector<Base*> objects;
    objects.push_back(new Base());
    objects.push_back(new Desc());
    objects.push_back(new Base());

    cout << "Обрабатываем объекты в контейнере:" << endl;
    for (Base* obj : objects) {
        cout << "Объект: " << obj->classname();

        // Безопасно работаем с Desc
        if (Desc* desc = dynamic_cast<Desc*>(obj)) {
            cout << " (это Desc!) -> ";
            desc->SimpleMethod();
        }
        else {
            cout << " (это Base) -> ";
            obj->SimpleMethod();
        }
    }

    // очищаем память
    for (Base* obj : objects) {
        delete obj;
    }

    cout << "\n=== ВСЕ ЭКСПЕРИМЕНТЫ ЗАВЕРШЕНЫ ===" << endl;

    return 0;
}
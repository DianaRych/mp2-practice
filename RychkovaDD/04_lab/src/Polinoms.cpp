#include "Polinoms.h"

// Обновление строкового представления полинома
void Polynomial::UpdateStringForm() {
    string result; // Строка для накопления результата
    terms.Reset(); // Начинаем обход с первого элемента списка мономов
    bool firstTerm = true; // Флаг первого члена (чтобы не ставить "+" перед первым членом)

    // Проходим по всем мономам полинома
    while (!terms.IsEnd()) {
        TMonom current = terms.GetCurrent()->key; // Получаем текущий моном
        double coeff = current.GetCoeff(); // Извлекаем коэффициент монома

        // Обрабатываем только ненулевые коэффициенты
        if (coeff != 0) {
            // Добавляем знак "+" перед положительными коэффициентами (кроме первого члена)
            if (!firstTerm && coeff > 0) {
                result += "+";
            }

            // Обработка коэффициента:
            // 1. Если коэффициент не 1/-1 или это свободный член (степень 0)
            if (coeff != 1 && coeff != -1 || current.GetDegree() == 0) {
                // Проверяем, целый ли коэффициент
                if (floor(coeff) == coeff) {
                    result += to_string((int)coeff); // Выводим как целое число
                }
                else {
                    result += to_string(coeff); // Выводим как дробное
                }
            }
            // 2. Если коэффициент -1, выводим только минус
            else if (coeff == -1) {
                result += "-";
            }
            // Для коэффициента 1 ничего не выводим (кроме случая, когда это свободный член)

            // Разбираем степень на составляющие x, y, z
            int degree = current.GetDegree();
            int x = degree / 100;       // Степень x (сотни)
            int y = (degree / 10) % 10; // Степень y (десятки)
            int z = degree % 10;        // Степень z (единицы)

            // Добавляем переменные x, y, z с их степенями
            if (x > 0) result += (x == 1) ? "x" : ("x^" + to_string(x));
            if (y > 0) result += (y == 1) ? "y" : ("y^" + to_string(y));
            if (z > 0) result += (z == 1) ? "z" : ("z^" + to_string(z));

            firstTerm = false; // Первый член уже обработан
        }
        terms.Next(); // Переходим к следующему моному
    }

    // Если строка пустая (все коэффициенты 0), возвращаем "0"
    polyString = result.empty() ? "0" : result;
}

// Добавление монома в полином
void Polynomial::AddTerm(const TMonom& term) {
    // Пропускаем мономы с нулевым коэффициентом
    if (term.GetCoeff() == 0) return;

    // Проверяем, есть ли уже моном с такой же степенью
    TNode<TMonom>* existing = terms.Search(term);

    if (!existing) {
        // Если монома с такой степенью нет, вставляем его в нужное место
        terms.Reset(); // Начинаем с начала списка
        bool inserted = false; // Флаг успешной вставки

        // Ищем место для вставки (список упорядочен по убыванию степеней)
        while (!terms.IsEnd()) {
            if (term.GetDegree() > terms.GetCurrent()->key.GetDegree()) {
                // Вставляем перед текущим элементом
                terms.InsertBefore(terms.GetCurrent()->key, term);
                inserted = true;
                break;
            }
            terms.Next();
        }

        // Если не нашли место в середине списка, добавляем в конец
        if (!inserted) {
            terms.InsertEnd(term);
        }
    }
    else {
        // Если моном с такой степенью уже есть, складываем коэффициенты
        double newCoeff = existing->key.GetCoeff() + term.GetCoeff();

        // Проверяем, не стал ли коэффициент нулевым после сложения
        if (fabs(newCoeff) > 1e-10) { // Сравнение с учетом погрешности
            // Создаем новый моном с суммой коэффициентов
            TMonom newTerm(newCoeff, term.GetDegree());
            // Удаляем старый моном и добавляем новый
            terms.DeleteByKey(existing->key);
            AddTerm(newTerm); // Рекурсивный вызов для правильного размещения
        }
        else {
            // Если коэффициент стал нулевым, удаляем моном
            terms.DeleteByKey(existing->key);
        }
    }
    // Обновляем строковое представление полинома
    UpdateStringForm();
}

// Вспомогательная функция для формирования строки вида "x^2y^3z"
string Polynomial::BuildTermString(int x, int y, int z) {
    string result;
    if (x > 0) result += (x == 1) ? "x" : ("x^" + to_string(x));
    if (y > 0) result += (y == 1) ? "y" : ("y^" + to_string(y));
    if (z > 0) result += (z == 1) ? "z" : ("z^" + to_string(z));
    return result;
}

// Конструкторы:

// Конструктор по умолчанию (создает нулевой полином)
Polynomial::Polynomial() : polyString("0") {}

// Конструктор из строки (например: "2x^2y-3y+z+5")
Polynomial::Polynomial(const string& input) {
    string termStr; // Буфер для накопления символов одного монома

    // Разбираем строку посимвольно
    for (char c : input) {
        // Если встретили '+' или '-' (начало нового монома)
        if ((c == '+' || c == '-') && !termStr.empty()) {
            TMonom term(termStr); // Создаем моном из накопленной строки
            AddTerm(term);        // Добавляем в полином
            termStr = "";         // Очищаем буфер
        }
        termStr += c; // Добавляем текущий символ в буфер
    }

    // Добавляем последний моном (если буфер не пуст)
    if (!termStr.empty()) {
        TMonom term(termStr);
        AddTerm(term);
    }
    // Формируем строковое представление полинома
    UpdateStringForm();
}

// Конструктор копирования
Polynomial::Polynomial(const Polynomial& other) {
    terms = other.terms;            // Копируем список мономов
    polyString = other.polyString;  // Копируем строковое представление
}

// Операторы сравнения:

// Проверка на равенство полиномов
bool Polynomial::operator==(const Polynomial& other) const {
    return terms == other.terms; // Сравниваем списки мономов
}

// Проверка на неравенство
bool Polynomial::operator!=(const Polynomial& other) const {
    return !(*this == other); // Отрицание оператора равенства
}

// Оператор присваивания
const Polynomial& Polynomial::operator=(const Polynomial& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        terms = other.terms;            // Копируем список мономов
        polyString = other.polyString;  // Копируем строковое представление
    }
    return *this;
}

// Методы дифференцирования:

// Дифференцирование по x
Polynomial Polynomial::DifferentiateX() const {
    Polynomial result; // Полином-результат
    terms.Reset();     // Начинаем обход с первого монома

    while (!terms.IsEnd()) {
        TMonom current = terms.GetCurrent()->key;
        int x = current.GetDegree() / 100; // Извлекаем степень x

        // Если степень x > 0, вычисляем производную
        if (x > 0) {
            // Новый коэффициент = старый * степень x
            // Новая степень = (x-1)*100 + остаток (для y и z)
            TMonom derived(current.GetCoeff() * x,
                (x - 1) * 100 + (current.GetDegree() % 100));
            result.AddTerm(derived);
        }
        terms.Next(); // Следующий моном
    }
    return result;
}

Polynomial Polynomial::DifferentiateY() const {
    Polynomial result;
    terms.Reset();

    while (!terms.IsEnd()) {
        TMonom current = terms.GetCurrent()->key;
        int degree = current.GetDegree();
        int y = (degree / 10) % 10; // Получаем степень y

        if (y > 0) {
            // Вычисляем новую степень:
            // - сохраняем степень x (первые две цифры)
            // - уменьшаем степень y на 1
            // - сохраняем степень z (последняя цифра)
            int new_degree = (degree / 100) * 100 + (y - 1) * 10 + (degree % 10);

            // Создаем новый моном с обновленным коэффициентом и степенью
            TMonom derived(current.GetCoeff() * y, new_degree);
            result.AddTerm(derived);
        }
        terms.Next();
    }
    return result;
}

// Дифференцирование по z
Polynomial Polynomial::DifferentiateZ() const {
    Polynomial result;
    terms.Reset();

    while (!terms.IsEnd()) {
        TMonom current = terms.GetCurrent()->key;
        int degree = current.GetDegree();
        int z = degree % 10; // Извлекаем степень z

        if (z > 0) {
            // Новый коэффициент = старый * степень z
            // Новая степень: уменьшаем степень z на 1, остальные оставляем без изменений
            int new_degree = (degree / 10) * 10 + (z - 1);
            TMonom derived(current.GetCoeff() * z, new_degree);
            result.AddTerm(derived);
        }
        terms.Next();
    }
    return result;
}

// Арифметические операции:

// Сложение с мономом
Polynomial Polynomial::operator+(const TMonom& term) const {
    Polynomial result(*this); // Копируем текущий полином
    result.AddTerm(term);     // Добавляем моном
    return result;
}

// Сложение с другим полиномом
Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result(*this); // Копируем текущий полином
    other.terms.Reset();      // Начинаем обход второго полинома

    // Добавляем все мономы второго полинома
    while (!other.terms.IsEnd()) {
        result.AddTerm(other.terms.GetCurrent()->key);
        other.terms.Next();
    }
    return result;
}

// Сложение с константой
Polynomial Polynomial::operator+(double constant) const {
    return *this + TMonom(constant, 0); // Создаем моном степени 0
}

// Вычитание монома (как сложение с отрицательным)
Polynomial Polynomial::operator-(const TMonom& term) const {
    return *this + TMonom(-term.GetCoeff(), term.GetDegree());
}

// Вычитание полинома
Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial result(*this);
    other.terms.Reset();

    // Добавляем все мономы второго полинома с отрицательными коэффициентами
    while (!other.terms.IsEnd()) {
        result.AddTerm(TMonom(-other.terms.GetCurrent()->key.GetCoeff(),
            other.terms.GetCurrent()->key.GetDegree()));
        other.terms.Next();
    }
    return result;
}

// Вычитание константы
Polynomial Polynomial::operator-(double constant) const {
    return *this + (-constant); // Сложение с отрицательной константой
}

// Умножение на скаляр
Polynomial Polynomial::operator*(double factor) const {
    Polynomial result;
    terms.Reset();

    // Умножаем каждый моном на скаляр
    while (!terms.IsEnd()) {
        TMonom scaled(terms.GetCurrent()->key.GetCoeff() * factor,
            terms.GetCurrent()->key.GetDegree());
        result.AddTerm(scaled);
        terms.Next();
    }
    return result;
}

// Умножение на моном
Polynomial Polynomial::operator*(const TMonom& term) const {
    Polynomial result;
    terms.Reset();

    // Умножаем каждый моном текущего полинома на заданный моном
    while (!terms.IsEnd()) {
        TMonom current = terms.GetCurrent()->key;
        // Коэффициенты перемножаем, степени складываем
        TMonom product(current.GetCoeff() * term.GetCoeff(),
            current.GetDegree() + term.GetDegree());
        result.AddTerm(product);
        terms.Next();
    }
    return result;
}

// Умножение полиномов
Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result;
    terms.Reset();

    // Каждый моном первого полинома умножаем на каждый моном второго
    while (!terms.IsEnd()) {
        other.terms.Reset();
        TMonom current = terms.GetCurrent()->key;

        while (!other.terms.IsEnd()) {
            TMonom otherCurrent = other.terms.GetCurrent()->key;
            TMonom product(current.GetCoeff() * otherCurrent.GetCoeff(),
                current.GetDegree() + otherCurrent.GetDegree());
            result.AddTerm(product);
            other.terms.Next();
        }
        terms.Next();
    }
    return result;
}

// Вычисление значения полинома в точке (x,y,z)
double Polynomial::operator()(double x, double y, double z) const {
    double result = 0.0;
    terms.Reset();

    // Суммируем значения всех мономов в заданной точке
    while (!terms.IsEnd()) {
        result += terms.GetCurrent()->key(x, y, z);
        terms.Next();
    }
    return result;
}

// Вывод полинома в поток
ostream& operator<<(ostream& os, const Polynomial& poly) {
    os << poly.polyString; // Просто выводим строковое представление
    return os;
}
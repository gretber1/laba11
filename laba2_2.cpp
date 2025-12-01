#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <limits>
#include <set>

enum CargoType { LIGHT = 1, MEDIUM, HEAVY };

std::string cargoTypeToString(CargoType type) {
    switch (type) {
        case LIGHT: return "Легкий груз";
        case MEDIUM: return "Средний груз";
        case HEAVY: return "Тяжелый груз";
        default: return "Неизвестно";
    }
}

double check_double(std::string s) {
    bool t = true;
    int k = 0;
    for (long long i = 0; i < s.size(); i++) {
        if (!isdigit(s[i]) and !(s[i] == '.') and !(i == 0 and s[i] == '-')) {
            t = false;
        }
        if (s[i] == '.') k++;
    }
    if (t) {
        if (k > 1 or stod(s) > 100000000) {
            t = false;
        }
    }
    while (std::cin.fail() || !t) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введено невозможное значение. Попробуйте снова: ";
        std::cin >> s;
        t = true;
        k = 0;
        for (long long i = 0; i < s.size(); i++) {
            if (!isdigit(s[i]) and !(s[i] == '.') and !(i == 0 and s[i] == '-')) {
                t = false;
            }
            if (s[i] == '.') k++;
        }
        if (t) {
            if (k > 1 or stod(s) > 100000000) {
                t = false;
            }
        }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return stod(s);
}

double check_int(std::string s) {
    bool t = true;
    for (long long i = 0; i < s.size(); i++) {
        if (!isdigit(s[i]) and !(i == 0 and s[i] == '-')) {
            t = false;
        }
    }
    if (t) {
        if (stoi(s) > 100000000) {
            t = false;
        }
    }
    while (std::cin.fail() || !t) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введено невозможное значение. Попробуйте снова: ";
        std::cin >> s;
        t = true;
        for (long long i = 0; i < s.size(); i++) {
            if (!isdigit(s[i]) and !(i == 0 and s[i] == '-')) {
                t = false;
            }
        }
        if (t) {
            if (stoi(s) > 100000000) {
                t = false;
            }
        }
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return stoi(s);
}

class Tariff {
private:
    CargoType type;
    double pricePerCubicMeter;
public:
    Tariff(CargoType t, double price) : type(t), pricePerCubicMeter(price) {}
    ~Tariff() {}

    CargoType getType() const { return type; }
    double getPrice() const { return pricePerCubicMeter; }

    void display() const {
        std::cout << cargoTypeToString(type)
                  << " — " << pricePerCubicMeter << " руб/м³\n";
    }
};

class Client {
private:
    int id;
    std::string name;
    static std::set<int> usedIds;
public:
    Client(int id, std::string name) {
        if (id <= 0) {
            std::cout << "ОЙ! ID клиента должен быть больше 0! Присваиваю ID = 1.\n";
            id = 1;
        }

        // Проверка: ID уникален
        if (usedIds.count(id)) {
            std::cout << "Опа! Такой ID клиента уже существует! Выбираю новый уникальный ID.\n";

            int newId = 1;
            while (usedIds.count(newId))
                newId++;

            id = newId;
            std::cout << "Новый уникальный ID: " << newId << std::endl;
        }

        usedIds.insert(id);

        this->id = id;
        this->name = name;
    }
    ~Client() {}

    int getId() const { return id; }
    std::string getName() const { return name; }

    void display() const {
        std::cout << "ID клиента: " << id << ", Имя: " << name << "\n";
    }
};

std::set<int> Client::usedIds;

class Order {
private:
    Client* client;
    Tariff* tariff;
    double volume;
    double totalPrice;
public:
    Order(Client* c, Tariff* t, double v)
        : client(c), tariff(t), volume(v) {
        totalPrice = volume * tariff->getPrice();
    }
    ~Order() {}

    Client* getClient() const { return client; }
    double getTotalPrice() const { return totalPrice; }

    void display() const {
        std::cout << "Клиент: " << client->getName()
                  << ", " << cargoTypeToString(tariff->getType())
                  << ", Объем: " << volume
                  << " м³, Сумма: " << totalPrice << " руб\n";
    }
};

class Company {
private:
    std::vector<Tariff> tariffs;
    std::vector<Client> clients;
    std::vector<Order> orders;
public:
    ~Company() {
        std::cout << "Очистка данных компании...\n";
    }

    void addTariff(CargoType type, double price) {
        tariffs.emplace_back(type, price);
    }

    void addClient(int id, const std::string& name) {
        clients.emplace_back(id, name);
    }

    Tariff* findTariff(CargoType type) {
        for (auto& t : tariffs)
            if (t.getType() == type)
                return &t;
        return nullptr;
    }

    Client* findClient(int id) {
        for (auto& c : clients)
            if (c.getId() == id)
                return &c;
        return nullptr;
    }

    void createOrder(int clientId, CargoType type, double volume) {
        Client* c = findClient(clientId);
        Tariff* t = findTariff(type);

        if (!c) {
            std::cout << "Ошибка: клиент не найден!\n";
            return;
        }
        if (!t) {
            std::cout << "Ошибка: тариф не найден!\n";
            return;
        }
        if (volume <= 0) {
            std::cout << "Ошибка: объем должен быть > 0!\n";
            return;
        }

        orders.emplace_back(c, t, volume);
        std::cout << "Заказ успешно добавлен!\n";
    }

    void showClientOrders(int clientId) const {
        bool found = false;
        for (const auto& o : orders) {
            if (o.getClient()->getId() == clientId) {
                o.display();
                found = true;
            }
        }
        if (!found)
            std::cout << "У клиента нет заказов.\n";
    }

    void showTotalRevenue() const {
        double sum = 0;
        for (const auto& o : orders)
            sum += o.getTotalPrice();
        std::cout << "Общая сумма всех заказов: " << sum << " руб\n";
    }

    void showTariffs() const {
        for (const auto& t : tariffs)
            t.display();
    }

    void showClients() const {
        for (const auto& c : clients)
            c.display();
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
    Company company;
    std::string choice_t;
    int choice;

    do {
        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1. Добавить тариф\n";
        std::cout << "2. Зарегистрировать клиента\n";
        std::cout << "3. Создать заказ\n";
        std::cout << "4. Показать заказы клиента\n";
        std::cout << "5. Показать все тарифы\n";
        std::cout << "6. Показать всех клиентов\n";
        std::cout << "7. Общая сумма заказов\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice_t;

        choice = check_int(choice_t);

        switch (choice) {
            case 1: {
                std::string type_t;
                std::string price_t;
                std::cout << "Выберите тип груза (1-легкий, 2-средний, 3-тяжелый): ";
                std::cin >> type_t;
                int type = check_int(type_t);
                std::cout << "Введите цену за м³: ";
                std::cin >> price_t;
                double price = check_double(price_t);

                if (price <= 0) {
                    std::cout << "Цена должна быть > 0!\n";
                    break;
                }

                company.addTariff(static_cast<CargoType>(type), price);
                break;
            }

            case 2: {
                int id;
                std::string id_t;
                std::string name;
                std::cout << "Введите ID клиента: ";
                std::cin >> id_t;
                id = check_int(id_t);
                std::cout << "Введите имя клиента: ";
                std::getline(std::cin, name);
                company.addClient(id, name);
                break;
            }

            case 3: {
                int id, type;
                std::string id_t, type_t, volume_t;
                double volume;
                std::cout << "Введите ID клиента: ";
                std::cin >> id_t;
                id = check_int(id_t);
                std::cout << "Введите тип груза (1-легкий, 2-средний, 3-тяжелый): ";
                std::cin >> type_t;
                type = check_int(type_t);
                std::cout << "Введите объем (м³): ";
                std::cin >> volume_t;
                volume = check_double(volume_t);
                company.createOrder(id, static_cast<CargoType>(type), volume);
                break;
            }

            case 4: {
                int id;
                std::string id_t;
                std::cout << "Введите ID клиента: ";
                std::cin >> id_t;
                id = check_int(id_t);
                company.showClientOrders(id);
                break;
            }

            case 5:
                company.showTariffs();
                break;

            case 6:
                company.showClients();
                break;

            case 7:
                company.showTotalRevenue();
                break;

            case 0:
                std::cout << "Выход из программы...\n";
                break;

            default:
                std::cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}

// чтобы большие числа не были и вот айди разные точно были, 
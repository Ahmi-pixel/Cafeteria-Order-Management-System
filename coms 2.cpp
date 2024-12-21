#include <iostream>
#include <string>
using namespace std;

const int MAX_MENU_ITEMS = 20;
const int MAX_CUSTOMERS = 100;
const int MAX_ORDERS = 100;
const int MAX_ORDER_ITEMS = 10;
const int MAX_CUSTOMIZATIONS = 5;

// MenuItem Class
class MenuItem {
private:
    int id;
    string name;
    double price;
    string category;
    bool isVegetarian;
    bool isVegan;
    bool isGlutenFree;
    int available;

public:
    MenuItem() {} // Default constructor

    MenuItem(int i, string n, double p, string cat, bool isVeg, bool isV, bool isGF, int avail) {
        id = i;
        name = n;
        price = p;
        category = cat;
        isVegetarian = isVeg;
        isVegan = isV;
        isGlutenFree = isGF;
        available = avail;
    }

    int getId() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    string getCategory() { return category; }
    int getAvailable() { return available; }
    void setPrice(double newPrice) { price = newPrice; }
    void setAvailable(int quantity) { available = quantity; }
    
    bool decreaseAvailable(int quantity) {
        if (available >= quantity) {
            available -= quantity;
            return true;
        }
        return false;
    }
};

// Customer Class
class Customer {
private:
    int id;
    string name;
    string contact;
    bool isVegetarian;
    bool isVegan;
    bool isGlutenFree;
    int loyaltyPoints;
    double totalSpent;

public:
    Customer() {} // Default constructor

    Customer(int i, string n, string cont, bool isVeg, bool isV, bool isGF) {
        id = i;
        name = n;
        contact = cont;
        isVegetarian = isVeg;
        isVegan = isV;
        isGlutenFree = isGF;
        loyaltyPoints = 0;
        totalSpent = 0;
    }

    int getId() { return id; }
    string getName() { return name; }
    int getPoints() { return loyaltyPoints; }
    void addPoints(double spent) {
        totalSpent += spent;
        loyaltyPoints += (int)(spent / 50); // 1 point per $50
    }
    void usePoints(int points) { loyaltyPoints -= points; }
};

// OrderItem Class
class OrderItem {
private:
    MenuItem* menuItem;
    int quantity;
    string customizations[MAX_CUSTOMIZATIONS];
    int numCustomizations;

public:
    OrderItem() {
        menuItem = nullptr;
        quantity = 0;
        numCustomizations = 0;
    }

    void setItem(MenuItem* item, int qty) {
        menuItem = item;
        quantity = qty;
    }

    MenuItem* getMenuItem() { return menuItem; }
    int getQuantity() { return quantity; }
    double getTotalPrice() { return menuItem->getPrice() * quantity; }
};

// Order Class
class Order {
private:
    int orderId;
    Customer* customer;
    OrderItem items[MAX_ORDER_ITEMS];
    int numItems;
    bool isPaid;
    double totalAmount;
    int pointsUsed;

public:
    Order(int id, Customer* cust) {
        orderId = id;
        customer = cust;
        numItems = 0;
        isPaid = false;
        totalAmount = 0;
        pointsUsed = 0;
    }

    void addItem(MenuItem* item, int quantity) {
        if (numItems < MAX_ORDER_ITEMS && item->decreaseAvailable(quantity)) {
            items[numItems].setItem(item, quantity);
            numItems++;
            calculateTotal();
        }
    }

    void calculateTotal() {
        totalAmount = 0;
        for (int i = 0; i < numItems; i++) {
            totalAmount += items[i].getTotalPrice();
        }
    }

    void applyLoyaltyPoints(int points) {
        if (points <= customer->getPoints()) {
            pointsUsed = points;
            totalAmount -= points;
            customer->usePoints(points);
        }
    }

    void processPayment() {
        isPaid = true;
        customer->addPoints(totalAmount);
    }

    double getTotalAmount() { return totalAmount; }
    bool getIsPaid() { return isPaid; }
    int getOrderId() { return orderId; }
    Customer* getCustomer() { return customer; }
};

// CafeteriaSystem Class
class CafeteriaSystem {
private:
    MenuItem menuItems[MAX_MENU_ITEMS];
    int numMenuItems;
    Customer customers[MAX_CUSTOMERS];
    int numCustomers;
    Order* orders[MAX_ORDERS];
    int numOrders;
    int nextOrderId;
    int nextCustomerId;

public:
    CafeteriaSystem() {
        numMenuItems = 0;
        numCustomers = 0;
        numOrders = 0;
        nextOrderId = 1;
        nextCustomerId = 1;
        initializeMenu();
    }

void initializeMenu() {
        // Vegetarian Items
        addMenuItem("Veggie Burger", 8.99, "Vegetarian", true, false, false, 25);
        addMenuItem("Veggie Wrap", 7.49, "Vegetarian", true, false, false, 20);
        addMenuItem("Grilled Cheese Sandwich", 5.99, "Vegetarian", true, false, false, 30);
        addMenuItem("Vegetable Stir Fry", 9.49, "Vegetarian", true, false, false, 18);

        // Vegan Items
        addMenuItem("Vegan Buddha Bowl", 10.99, "Vegan", true, true, false, 15);
        addMenuItem("Vegan Tacos", 8.49, "Vegan", true, true, false, 20);
        addMenuItem("Vegan Quinoa Salad", 9.29, "Vegan", true, true, false, 12);
        addMenuItem("Vegan Chili", 7.99, "Vegan", true, true, false, 25);

        // Gluten-Free Items
        addMenuItem("Gluten-Free Margherita Pizza", 11.49, "Gluten-Free", false, false, true, 10);
        addMenuItem("Grilled Chicken Salad", 10.99, "Gluten-Free", false, false, true, 18);
        addMenuItem("Gluten-Free Pancakes", 6.99, "Gluten-Free", false, false, true, 15);
        addMenuItem("Gluten-Free Pasta Primavera", 12.49, "Gluten-Free", false, false, true, 14);

        // Specialty Items
        addMenuItem("Classic Cheeseburger", 9.99, "Specialty", false, false, false, 20);
        addMenuItem("BBQ Pulled Pork Sandwich", 9.49, "Specialty", false, false, false, 15);
        addMenuItem("Chicken Caesar Wrap", 8.99, "Specialty", false, false, false, 25);
        addMenuItem("Grilled Salmon Plate", 13.49, "Specialty", false, false, false, 10);

        // Drinks
        addMenuItem("Iced Latte", 4.29, "Drinks", false, false, false, 30);
        addMenuItem("Fresh Fruit Smoothie", 5.99, "Drinks", true, true, true, 20);
        addMenuItem("Cappuccino", 3.49, "Drinks", false, false, false, 25);
        addMenuItem("Lemonade", 2.99, "Drinks", true, true, true, 35);
    }

    void addMenuItem(string name, double price, string category, 
                    bool isVeg, bool isVegan, bool isGF, int available) {
        if (numMenuItems < MAX_MENU_ITEMS) {
            menuItems[numMenuItems] = MenuItem(numMenuItems + 1, name, price, category, 
                                             isVeg, isVegan, isGF, available);
            numMenuItems++;
        }
    }

    void displayMenu() {
        cout << "\n=== CampusBites Menu ===\n";
        for (int i = 0; i < numMenuItems; i++) {
            cout << menuItems[i].getId() << ". " << menuItems[i].getName() 
                 << " - $" << menuItems[i].getPrice() 
                 << " (Available: " << menuItems[i].getAvailable() << ")\n";
        }
        cout << "\n";
    }

    Customer* registerNewCustomer() {
        string name, contact;
        char choice;
        bool isVeg, isVegan, isGF;

        cout << "\nEnter customer name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter contact number: ";
        getline(cin, contact);
        
        cout << "Are you vegetarian? (y/n): ";
        cin >> choice;
        isVeg = (choice == 'y' || choice == 'Y');
        
        cout << "Are you vegan? (y/n): ";
        cin >> choice;
        isVegan = (choice == 'y' || choice == 'Y');
        
        cout << "Do you require gluten-free food? (y/n): ";
        cin >> choice;
        isGF = (choice == 'y' || choice == 'Y');

        customers[numCustomers] = Customer(nextCustomerId++, name, contact, isVeg, isVegan, isGF);
        numCustomers++;
        return &customers[numCustomers - 1];
    }

    MenuItem* findMenuItem(int id) {
        for (int i = 0; i < numMenuItems; i++) {
            if (menuItems[i].getId() == id) {
                return &menuItems[i];
            }
        }
        return nullptr;
    }

    Order* createOrder(Customer* customer) {
        if (numOrders < MAX_ORDERS) {
            orders[numOrders] = new Order(nextOrderId++, customer);
            numOrders++;
            return orders[numOrders - 1];
        }
        return nullptr;
    }

    void placeOrder(Customer* customer) {
        Order* order = createOrder(customer);
        if (!order) {
            cout << "Cannot create more orders!\n";
            return;
        }

        int itemId, quantity;
        char more;
        do {
            displayMenu();
            cout << "Enter item ID to order: ";
            cin >> itemId;
            cout << "Enter quantity: ";
            cin >> quantity;

            MenuItem* item = findMenuItem(itemId);
            if (item && item->getAvailable() >= quantity) {
                order->addItem(item, quantity);
                cout << "Added to order: " << quantity << "x " << item->getName() << "\n";
            } else {
                cout << "Invalid item or insufficient quantity!\n";
            }

            cout << "Add more items? (y/n): ";
            cin >> more;
        } while (more == 'y' || more == 'Y');

        cout << "\nOrder Total: $" << order->getTotalAmount() << "\n";
        
        if (customer->getPoints() > 0) {
            cout << "You have " << customer->getPoints() << " loyalty points.\n";
            cout << "Enter points to use (0 for none): ";
            int points;
            cin >> points;
            order->applyLoyaltyPoints(points);
            cout << "New Total: $" << order->getTotalAmount() << "\n";
        }

        order->processPayment();
        cout << "Payment processed successfully!\n";
    }

    void generateDailyReport() {
        cout << "\n=== Daily Sales Report ===\n";
        double totalSales = 0;
        int totalOrders = 0;

        for (int i = 0; i < numOrders; i++) {
            if (orders[i]->getIsPaid()) {
                cout << "Order #" << orders[i]->getOrderId() 
                     << " - Customer: " << orders[i]->getCustomer()->getName()
                     << " - Amount: $" << orders[i]->getTotalAmount() << "\n";
                totalSales += orders[i]->getTotalAmount();
                totalOrders++;
            }
        }
        
        cout << "\nTotal Sales: $" << totalSales << "\n";
        cout << "Total Orders: " << totalOrders << "\n";
    }
};

int main() {
    CafeteriaSystem system;
    int choice;
    Customer* currentCustomer = nullptr;

    do {
        cout << "\n=== CampusBites Management System ===\n";
        cout << "1. Register New Customer\n";
        cout << "2. Display Menu\n";
        cout << "3. Place Order\n";
        cout << "4. Generate Daily Report\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentCustomer = system.registerNewCustomer();
                cout << "Customer registered successfully!\n";
                break;
            case 2:
                system.displayMenu();
                break;
            case 3:
                if (currentCustomer == nullptr) {
                    cout << "Please register customer first!\n";
                } else {
                    system.placeOrder(currentCustomer);
                }
                break;
            case 4:
                system.generateDailyReport();
                break;
            case 5:
                cout << "Thank you for using CampusBites!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
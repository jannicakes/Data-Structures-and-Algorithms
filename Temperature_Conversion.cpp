#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QListWidget>
#include <vector>
#include <string>

using namespace std; // Using namespace std here

const int MAX_ITEMS = 3;

struct MenuItem {
    int id;
    QString name; // Note that we're using QString for Qt compatibility
    double price;
    bool isAvailable;
};

struct CartItem {
    int id;
    QString name;
    double price;
};

struct Order {
    int orderID;
    double totalPrice;
    vector<CartItem> items; // Standard vector is fine here
};

class OrderSystemGUI : public QMainWindow {
    Q_OBJECT

public:
    OrderSystemGUI(QWidget *parent = nullptr) : QMainWindow(parent), nextOrderID(1) {
        // Central widget and layout setup
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        // Menu buttons
        QPushButton *addMenuItemBtn = new QPushButton("Add Menu Item", this);
        connect(addMenuItemBtn, &QPushButton::clicked, this, &OrderSystemGUI::addMenuItemDialog);
        
        QPushButton *displayMenuBtn = new QPushButton("Display Menu", this);
        connect(displayMenuBtn, &QPushButton::clicked, this, &OrderSystemGUI::displayMenu);

        // Cart buttons
        QPushButton *addToCartBtn = new QPushButton("Add to Cart", this);
        connect(addToCartBtn, &QPushButton::clicked, this, &OrderSystemGUI::addToCartDialog);
        
        QPushButton *removeFromCartBtn = new QPushButton("Remove from Cart", this);
        connect(removeFromCartBtn, &QPushButton::clicked, this, &OrderSystemGUI::removeFromCart);

        // Order buttons
        QPushButton *enqueueOrderBtn = new QPushButton("Place Order", this);
        connect(enqueueOrderBtn, &QPushButton::clicked, this, &OrderSystemGUI::enqueueOrder);
        
        QPushButton *dequeueOrderBtn = new QPushButton("Process Order", this);
        connect(dequeueOrderBtn, &QPushButton::clicked, this, &OrderSystemGUI::dequeueOrder);

        // Cart and Order displays
        cartDisplay = new QListWidget(this);
        orderDisplay = new QListWidget(this);

        // Adding widgets to the layout
        layout->addWidget(addMenuItemBtn);
        layout->addWidget(displayMenuBtn);
        layout->addWidget(addToCartBtn);
        layout->addWidget(removeFromCartBtn);
        layout->addWidget(enqueueOrderBtn);
        layout->addWidget(dequeueOrderBtn);

        layout->addWidget(new QLabel("Cart:", this));
        layout->addWidget(cartDisplay);
        
        layout->addWidget(new QLabel("Order Queue:", this));
        layout->addWidget(orderDisplay);

        setCentralWidget(centralWidget);
        updateDisplay();
    }

private slots:
    void addMenuItemDialog() {
        if (menu.size() >= MAX_ITEMS) {
            QMessageBox::warning(this, "Error", "Menu is full.");
            return;
        }

        bool ok;
        int id = QInputDialog::getInt(this, "Add Menu Item", "Enter ID:", 0, 0, 100, 1, &ok);
        if (!ok) return;

        QString name = QInputDialog::getText(this, "Add Menu Item", "Enter Name:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        double price = QInputDialog::getDouble(this, "Add Menu Item", "Enter Price:", 0, 0, 10000, 2, &ok);
        if (!ok) return;

        bool isAvailable = QInputDialog::getInt(this, "Add Menu Item", "Is Available? (1 for Yes, 0 for No):", 1, 0, 1, 1, &ok);
        if (!ok) return;

        menu.push_back({ id, name, price, isAvailable });
        updateDisplay();
    }

    void displayMenu() {
        QString menuText;
        for (const auto &item : menu) {
            menuText += QString("ID: %1 Name: %2 Price: Rs%3 Available: %4\n")
                .arg(item.id)
                .arg(item.name)
                .arg(item.price)
                .arg(item.isAvailable ? "Yes" : "No");
        }
        QMessageBox::information(this, "Menu", menuText.isEmpty() ? "Menu is empty." : menuText);
    }

    void addToCartDialog() {
        if (cart.size() >= MAX_ITEMS) {
            QMessageBox::warning(this, "Error", "Cart is full.");
            return;
        }

        bool ok;
        QString name = QInputDialog::getText(this, "Add to Cart", "Enter item name:", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        auto it = find_if(menu.begin(), menu.end(), [&name](const MenuItem &item) {
            return item.name == name && item.isAvailable;
        });

        if (it != menu.end()) {
            cart.push_back({ it->id, it->name, it->price });
            updateDisplay();
        } else {
            QMessageBox::warning(this, "Error", "Item not found or not available.");
        }
    }

    void removeFromCart() {
        if (cart.empty()) {
            QMessageBox::warning(this, "Warning", "Cart is empty.");
            return;
        }
        cart.pop_back();
        updateDisplay();
    }

    void enqueueOrder() {
        if (cart.empty()) {
            QMessageBox::warning(this, "Warning", "Cart is empty. Cannot place order.");
            return;
        }

        if (orderQueue.size() >= MAX_ITEMS) {
            QMessageBox::warning(this, "Error", "Order queue is full.");
            return;
        }

        double totalPrice = 0;
        for (const auto &item : cart) {
            totalPrice += item.price;
        }

        Order newOrder = { nextOrderID++, totalPrice, cart };
        orderQueue.push_back(newOrder);
        cart.clear();
        updateDisplay();
    }

    void dequeueOrder() {
        if (orderQueue.empty()) {
            QMessageBox::warning(this, "Warning", "No orders to process.");
            return;
        }

        Order order = orderQueue.front();
        orderQueue.erase(orderQueue.begin());

        QString orderDetails = QString("Order ID: %1\nTotal Price: Rs%2\n")
            .arg(order.orderID)
            .arg(order.totalPrice);

        for (const auto &item : order.items) {
            orderDetails += QString("ID: %1 Name: %2 Price: Rs%3\n").arg(item.id).arg(item.name).arg(item.price);
        }

        QMessageBox::information(this, "Processing Order", orderDetails);
        updateDisplay();
    }

    void updateDisplay() {
        cartDisplay->clear();
        for (const auto &item : cart) {
            cartDisplay->addItem(QString("ID: %1 Name: %2 Price: Rs%3").arg(item.id).arg(item.name).arg(item.price));
        }

        orderDisplay->clear();
        for (const auto &order : orderQueue) {
            orderDisplay->addItem(QString("Order ID: %1 Total Price: Rs%2").arg(order.orderID).arg(order.totalPrice));
        }
    }

private:
    vector<MenuItem> menu;
    vector<CartItem> cart;
    vector<Order> orderQueue;
    QListWidget *cartDisplay;
    QListWidget *orderDisplay;
    int nextOrderID;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OrderSystemGUI window;
    window.setWindowTitle("Order Processing System");
    window.resize(400, 600);
    window.show();

    return app.exec();
}


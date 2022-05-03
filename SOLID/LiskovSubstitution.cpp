#include <iostream>
#include <vector>
#include <memory>

struct Item 
{
    int id;
    Item(int _id) : id{_id} { }
};

struct Order
{
    std::vector<Item> items;    
    void add(const Item& item) { items.push_back(item); }
};

namespace before
{
class PaymentSystem
{
    int balance;
public:
    PaymentSystem (int _balance) : balance{_balance} { } 
    virtual int getBalance() {return balance;}
    virtual void pay(Order& order) = 0;
};
struct PaymentCash : public PaymentSystem
{
    int balance;
    PaymentCash (int _balance) : PaymentSystem{_balance}, balance{_balance} { } 
    virtual int getBalance() {return balance;} // !!!
    void pay(Order& order)
    {
        while(order.items.size())
        {
            std::cout << "cash=" << order.items.back().id << "\n";
            order.items.pop_back();
        } 
    }
};
struct PaymentCredit : public PaymentSystem
{
    void pay(Order& order)
    {
        while(order.items.size())
        {
            std::cout << "credit=" << order.items.back().id << "\n";
            order.items.pop_back();
        } 
    }
};
};
///////////////

namespace after
{
class PaymentSystem
{
    int balance;
public:
    PaymentSystem (int _balance) : balance{_balance} { } 
    virtual int getBalance() {return balance;}
    virtual void pay(Order& order) = 0;
};
struct PaymentCash : public PaymentSystem
{
    int balance;
    PaymentCash (int _balance) : PaymentSystem{_balance}, balance{_balance} { } 
    virtual int getBalance() {return balance;} // !!!
    void pay(Order& order)
    {
        while(order.items.size())
        {
            std::cout << "cash=" << order.items.back().id << "\n";
            order.items.pop_back();
        } 
    }
};
struct PaymentCredit : public PaymentSystem
{
    int balance;
    PaymentCredit (int _balance) : PaymentSystem{_balance}, balance{_balance} { } 
    virtual int getBalance() {return balance;} // !!!
    void pay(Order& order)
    {
        while(order.items.size())
        {
            std::cout << "credit=" << order.items.back().id << "\n";
            order.items.pop_back();
        } 
    }
};
};

int main()
{
    {
        std::cout << "before:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        before::PaymentCash payment{100};
        payment.pay(order);
        std::cout << payment.getBalance() << "\n";
    }

    {
        std::cout << "after1:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        after::PaymentCash cash{100};
        cash.pay(order);
        std::cout << cash.getBalance() << "\n";
    }
    
    {
        std::cout << "after2:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        std::unique_ptr<after::PaymentSystem> payment = std::make_unique<after::PaymentCash>(100);
        payment->pay(order);
        std::cout << payment->getBalance() << "\n";
    }

    {
        std::cout << "after3:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        std::unique_ptr<after::PaymentSystem> payment = std::make_unique<after::PaymentCredit>(100);
        payment->pay(order);
        std::cout << payment->getBalance() << "\n";
         
    }
}
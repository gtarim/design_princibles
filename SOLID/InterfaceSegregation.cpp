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
    virtual int getBalance() const = 0;
    virtual void pay(Order& order) = 0;
};
struct PaymentCash : public PaymentSystem
{
    int balance;
    PaymentCash (int _balance) : PaymentSystem{_balance}, balance{_balance} { } 
    int getBalance() const override {return balance;}
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
    int getBalance() const override {return balance;}
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
    virtual int getBalance() const = 0;
    virtual void pay(Order& order) = 0;
};
struct PaymentCash : public PaymentSystem
{
    int balance;
    PaymentCash (int _balance) : PaymentSystem{_balance}, balance{_balance} { } 
    int getBalance() const override {return balance;}
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
    int getBalance() const override {return balance;}
    void pay(Order& order)
    {
        while(order.items.size())
        {
            std::cout << "credit=" << order.items.back().id << "\n";
            order.items.pop_back();
        } 
    }
};
struct XBank : public PaymentCredit
{
    int balance;
    std::string cardType;
    XBank (int _balance) : PaymentCredit{_balance}, balance{_balance} {}
    void fee() { std::cout << "you have pay your credit card fee\n"; }
};
struct YBank : public PaymentCredit
{
    int balance;
    std::string cardType;
    YBank (int _balance) : PaymentCredit{_balance}, balance{_balance} {}
    void promotion() {std::cout << "you have got promotion 5% percent\n";}
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
        before::PaymentCredit payment{100};
        payment.pay(order);
    }

    {
        std::cout << "after1:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        after::XBank credit{100};
        credit.pay(order);
        credit.fee();
    }

    {
        std::cout << "after2:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        after::YBank credit{100};
        credit.pay(order);
        credit.promotion();
    }
}
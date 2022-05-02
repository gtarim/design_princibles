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
struct PaymentSystem
{
    void pay(Order& order)
    {
        while(order.items.size())
        {
            std::cout << order.items.back().id << "\n";
            order.items.pop_back();
        }
    }
};
};
///////////////

namespace after
{
struct PaymentSystem
{
    virtual void pay(Order& order) = 0;
};
struct PaymentCash : public PaymentSystem
{
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

int main()
{
    {
        std::cout << "before:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        before::PaymentSystem payment;
        payment.pay(order);
    }

    {
        std::cout << "after1:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        after::PaymentCash cash;
        cash.pay(order);
    }

    {
        std::cout << "after2:\n";
        Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        after::PaymentCredit credit;
        credit.pay(order);
    }
}
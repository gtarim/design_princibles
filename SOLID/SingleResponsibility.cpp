#include <iostream>
#include <vector>
#include <memory>

struct Item 
{
    int id;
    Item(int _id) : id{_id} { }
};

namespace before
{
class Order
{
    std::vector<Item> items;
public:
    void add(const Item& item) { items.push_back(item); }
    void pay() 
    {
        while(items.size())
        {
            std::cout << items.back().id << "\n";
            items.pop_back(); 
        }
    }
};
};

///////////////

namespace after
{
struct Order
{
    std::vector<Item> items;    
    void add(const Item& item) { items.push_back(item); }
};
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

int main()
{
    {
        std::cout << "before:\n";
        before::Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        order.pay();
    }

    ///////////////
    {
        std::cout << "after:\n";
        after::Order order;
        order.add(Item{10});
        order.add(Item{20});
        order.add(Item{30});
        after::PaymentSystem payment;
        payment.pay(order);
    }
}
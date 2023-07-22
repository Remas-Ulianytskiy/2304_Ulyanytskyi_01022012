#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Property {
private:
    double price;
    string name;
    string address;

public:
    Property(const string& address, const string& name, double price)
        : address(address), name(name), price(price) 
    {}

    double get_price() const   { return price; }
    string get_name() const    { return name; }
    string get_address() const { return address; }    
};

class Owner {
private:
    int id;
    double balance;
    string first_name, last_name;
    vector<Property*> properties;

public:
    Owner(int id, const string& first_name, const string& last_name, double balance)
        : id(id), first_name(first_name), last_name(last_name), balance(balance)
    {}

    void add_property(Property* property) { properties.push_back(property); }   

    void transfer_ownership(Owner& new_owner, Property* property, double transfer_amount)
    {
        auto it = find(properties.begin(), properties.end(), property);
        if (it != properties.end())
        {
            properties.erase(it);
            new_owner.add_property(property);

            if (transfer_amount > 0 && transfer_amount <= balance)
            {
                balance -= transfer_amount;
                new_owner.balance += transfer_amount;
            }
            else
                cout << "Not enough money for transfer!\n";
        }
    }

    void display_properties() {
        cout << "Properties owned by " << first_name << ' ' << last_name << ":\n";
        for (const Property* property : properties)
        {
            cout << "- " << property->get_price() << " (" << property->get_name();
            cout << "), Address: " << property->get_address() << endl;
        }
    }

    void display_balance()
    {
        cout << first_name << ' ' << last_name << " balance: " << balance << endl;
    }
};

int main() {
    double transfer_amount = 130345.2;

    Property property_1("12 Avenue", "House", 259234.47);
    Property property_2("47 Park Street", "Apartment", 145018.79);

    Owner owner_1(101, "Janna", "Dark", 500320);
    Owner owner_2(102, "Diana", "Smith", 320300.86);

    owner_1.add_property(&property_1);
    owner_2.add_property(&property_2);

    cout << "Before transfer:\n";
    owner_1.display_properties();
    owner_2.display_properties();
    owner_1.display_balance();
    owner_2.display_balance();
    
    owner_1.transfer_ownership(owner_2, &property_1, transfer_amount);

    cout << "\nTransfer amount: " << transfer_amount << endl;

    cout << "\nAfter transfer:\n";
    owner_1.display_properties();
    owner_2.display_properties();
    owner_1.display_balance();
    owner_2.display_balance();

    return 0;
}

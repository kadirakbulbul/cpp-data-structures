#include <iostream>    
#include <string>
#include <vector>

using namespace std;

enum class DiscountT{Amount,Percentage};  // enum for type safety


class Department {           
private:
    string id;
    string name;
    string descript;        //Data members for the whole project
    string address;
      

public:
    Department(string i, string n, string d, string a) {  
        id = i;
        name = n;
        descript = d;               //constructor
        address = a;
    }

    // getters and setters
    string getId() const {return id;}
    void setId(string i) {id = i;}

    string getName() const {return name;}
    void setName(string n) {name = n;}

    string getDescript() const {return descript;}
    void setDescript(string d) {descript = d;}

    string getAddress() const {return address;}
    void setAddress(string a) {address = a;}

};

class Product {   //Parent class
protected:
    string name;
    Department* department;
    double price;
    double discount;
    int quantity;
    DiscountT discountType;

public:
    Product(string n, Department* dep, double p, double d, int q, DiscountT dt) {
        name = n;  
        department = dep;
        price = p;
        discount = d;
        quantity = q;
        discountType = dt;
    }

    double GetEffectivePrice() {
        if (discountType == DiscountT::Amount)
            return price - discount;                    //Calculation for discount
        else
            return price - price * discount / 100;
    }

    double GetTotalPrice() {
        return GetEffectivePrice() * quantity;    //Calculates the price of the quantity
    }

    string getName() const { return name; }
};


class Service : public Product {  //child class
private:
    double duration;
    double rate;
    double rateDiscount;
    DiscountT rateDiscountType;

public:
    Service(string n, Department* dep,double p, double d, int q, DiscountT dt, double dur, double r, double rd, DiscountT rdt)
        : Product(n, dep, p, d, q, dt)   // calls Product constructor 
    {
        name = n;
        department = dep;
        duration = dur;
        rate = r;
        rateDiscount = rd;
        rateDiscountType = rdt;
    }

    double GetEffectiveRate() { 
        double effective;
        if (rateDiscountType == DiscountT::Amount)
            effective = rate - rateDiscount;
        else
            effective = rate - rate * rateDiscount / 100;

        if (effective < 0) return 0;
        return effective;
    }
    double GetTotalPrice() {
        double totalProduct = Product::GetTotalPrice();  
        double totalServiceRate = GetEffectiveRate() * duration;
        return totalProduct + totalServiceRate;
        
    }

};

int main(){
    vector<Department*> departments;
    vector<Product*> products;
    vector<Service*> services;

    // Departments
    Department* d1 = new Department("D1", "Electronics", "Electronics department", "Istanbul St. No: 12, Turkey");
    Department* d2 = new Department("D2", "Furniture", "Furniture department", "Ankara Blvd. 20, Turkey");
    Department* d3 = new Department("D3", "Books", "Books department", "Izmir Street");

    departments.push_back(d1);
    departments.push_back(d2);
    departments.push_back(d3);

    // Products
    Product* p1 = new Product("Robotistan Elektronic Set", d1, 750, 75, 2, DiscountT::Amount);
    Product* p2 = new Product("Oak Table", d2, 1200, 15, 1, DiscountT::Percentage);
    Product* p3 = new Product("Book Set", d3, 150, 0, 5, DiscountT::Amount);
    products.push_back(p1);
    products.push_back(p2);
    products.push_back(p3);

    // Services
    Service* s1 = new Service("Robotistan Set-up ", d1, 150, 10, 1, DiscountT::Amount, 2.5, 60.0, 10.0, DiscountT::Percentage);
    Service* s2 = new Service("Furniture Assembly", d2, 0, 0, 1, DiscountT::Amount, 3.0, 40.0, 5.0, DiscountT::Amount);
    Service* s3 = new Service("Book Delivery", d3, 0, 0, 1, DiscountT::Amount, 1.0, 15.0, 0.0, DiscountT::Amount);
    services.push_back(s1);
    services.push_back(s2);
    services.push_back(s3);

    // prints  products and prices (product:price)
    cout << "Products:" << endl;
    for (auto p : products) {
        cout << p->getName() << " : " << p->GetTotalPrice() << endl;
    }

    cout << "Services:" << endl;
    for (auto s : services) {
        cout << s->getName() << " : " << s->GetTotalPrice() << endl;
    }

    return 0;
}


    

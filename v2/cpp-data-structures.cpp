#include <iostream>    
#include <string>
#include <vector>

using namespace std;

enum class DiscountT{Amount,Percentage};  // enum for type safety


class Department {           
private:
    string id;
    string name;
    string descript;        //Data members for Depratment class
    string address;
      

public:
    Department(string i, string n, string des, string a) {  
        id = i;
        name = n;
        descript = des;               //constructor
        address = a;
    }

    // getters and setters
    string getId() const {return id;}
    void setId(string i) {id = i;}

    string getName() const {return name;}
    void setName(string n) {name = n;}

    string getDescript() const {return descript;}
    void setDescript(string des) {descript = des;}

    string getAddress() const {return address;}
    void setAddress(string a) {address = a;}

};

class İtem{   //new parent class
    public:
        virtual double GetTotalPrice() = 0;
        virtual ~İtem() {} // destructor for free memory 
};

class Product : public İtem{   // Product became a child class of İtem
protected:
    string id;
    string description;
    string name;
    Department* department;
    double price;
    double discount;
    int quantity;
    DiscountT discountType;

public:
    Product(string i,string des, string n, Department* dep, double p, double d, int q, DiscountT dt) {
        id = i;
        description = des;
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

    double GetTotalPrice() override {
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
    Service(string i,string des,string n, Department* dep,double p, double d, int q, DiscountT dt, double dur, double r, double rd, DiscountT rdt)
        : Product(i,des,n, dep, p, d, q, dt)   // calls Product constructor 
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
    double GetTotalPrice() override{
        double totalProduct = Product::GetTotalPrice();  
        double totalServiceRate = GetEffectiveRate() * duration;
        return totalProduct + totalServiceRate;
        
    }

};

int main(){
    vector<Department*> departments;
    vector<İtem*> İtems;

    // Departments
    Department* d1 = new Department("D1", "Electronics", "Electronics department", "Istanbul St. No: 12, Turkey");
    Department* d2 = new Department("D2", "Furniture", "Furniture department", "Ankara Blvd. 20, Turkey");
    Department* d3 = new Department("D3", "Books", "Books department", "Izmir Street");

    departments.push_back(d1);
    departments.push_back(d2);
    departments.push_back(d3);

    // Products
    Product* p1 = new Product("P1","Robotistan Electronic Set","Kit for Electronics", d1, 750, 75, 2, DiscountT::Amount);  //added id and description
    Product* p2 = new Product("P2","Oak Table","Table", d2, 1200, 15, 1, DiscountT::Percentage);
    Product* p3 = new Product("P3","Book Set","Book set", d3, 150, 0, 5, DiscountT::Amount);
    İtems.push_back(p1);
    İtems.push_back(p2);
    İtems.push_back(p3);

    // Services
    Service* s1 = new Service("S1","Setup Service","Robotistan Set-up ", d1, 150, 10, 1, DiscountT::Amount, 2.5, 60.0, 10.0, DiscountT::Percentage);   //added id and description
    Service* s2 = new Service("S2","Furniture Setup","Furniture Assembly", d2, 0, 0, 1, DiscountT::Amount, 3.0, 40.0, 5.0, DiscountT::Amount);
    Service* s3 = new Service("S3","Delivery","Book Delivery", d3, 0, 0, 1, DiscountT::Amount, 1.0, 15.0, 0.0, DiscountT::Amount);
    İtems.push_back(s1);
    İtems.push_back(s2);
    İtems.push_back(s3);

    // prints  products and prices (product:price)
    cout << "All Items:" << endl;

    double grandTotal = 0;

    for (auto item : İtems) {          //loop for calculating 
        cout << item->GetTotalPrice() << endl;
        grandTotal += item->GetTotalPrice();
    }

    cout << "Grand Total: " << grandTotal << endl;

    for (auto d : departments)
    delete d;

    for (auto   İtem : İtems)
    delete İtem;

    return 0;
}


    

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

class Item{   //parent class 
    public:
        virtual double GetTotalPrice() = 0;
        virtual string getName() const = 0; //added virtual class
        virtual ~Item() {} // destructor for free memory 
};

class Product : public Item{   
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

    string getName() const override { return name; } //added override 
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

void merge(vector<Item*>& items, int left, int mid, int right) { //merge logic
    vector<Item*> temp;  // temporary vector to hold merged elements

    int i = left;       // start of left subarray
    int j = mid + 1;    // start of right subarray

    while (i <= mid && j <= right) { // merge subarrays
        if (items[i]->GetTotalPrice() <= items[j]->GetTotalPrice()) {
            temp.push_back(items[i]);
            i++;
        } else {
            temp.push_back(items[j]);
            j++;
        }
    }

    while (i <= mid) { // copy any remaining elements from left subarray 
        temp.push_back(items[i]);
        i++;
    }

    while (j <= right) { // copy any remaining elements from right subarray
        temp.push_back(items[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++) { // copy sorted elements back to original array
        items[left + k] = temp[k];
    }
}

void mergeSort(vector<Item*>& items, int left, int right) { //sort logic
    if (left >= right) return;  

    int mid = left + (right - left) / 2; //finding the midpoint
    mergeSort(items, left, mid);         // sort left half
    mergeSort(items, mid + 1, right);    // sort right half
    merge(items, left, mid, right);      // merge sorted halves
}


int main(){
    vector<Department*> departments;
    vector<Item*> Items;

    // Departments
    Department* d1 = new Department("D1", "Electronics", "Electronics department", "Istanbul St. No: 12, Turkey");
    Department* d2 = new Department("D2", "Furniture", "Furniture department", "Ankara Blvd. 20, Turkey");
    Department* d3 = new Department("D3", "Books", "Books department", "Izmir Street");

    departments.push_back(d1);
    departments.push_back(d2);
    departments.push_back(d3);

    // Products
    Product* p1 = new Product("P1","Robotistan Electronic Set","Kit for Electronics", d1, 750, 75, 2, DiscountT::Amount); 
    Product* p2 = new Product("P2","Oak Table","Table", d2, 1200, 15, 1, DiscountT::Percentage);
    Product* p3 = new Product("P3","Book Set","Book set", d3, 150, 0, 5, DiscountT::Amount);
    Items.push_back(p1);
    Items.push_back(p2);
    Items.push_back(p3);

    // Services
    Service* s1 = new Service("S1","Setup Service","Robotistan Set-up ", d1, 150, 10, 1, DiscountT::Amount, 2.5, 60.0, 10.0, DiscountT::Percentage);   
    Service* s2 = new Service("S2","Furniture Setup","Furniture Assembly", d2, 0, 0, 1, DiscountT::Amount, 3.0, 40.0, 5.0, DiscountT::Amount);
    Service* s3 = new Service("S3","Delivery","Book Delivery", d3, 0, 0, 1, DiscountT::Amount, 1.0, 15.0, 0.0, DiscountT::Amount);
    Items.push_back(s1);
    Items.push_back(s2);
    Items.push_back(s3);

    // prints  products and prices 
    cout << "All Items:" << endl;

    double grandTotal = 0;
    for (auto item : Items)
        grandTotal += item->GetTotalPrice();
    

    // sort by total price using merge sort
    mergeSort(Items, 0, Items.size() - 1);

    // print sorted items
    cout << "Sorted Items (by Total Price):" << endl;
    for (auto item : Items) {
        cout << item->getName() << " - " << item->GetTotalPrice() << endl;
    }

    cout << "Grand Total: " << grandTotal << endl;

    for (auto d : departments)
    delete d;

    for (auto item : Items)
    delete item;

    return 0;
}


    
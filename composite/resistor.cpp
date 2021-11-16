#include <iostream>
#include <vector>
using namespace std;


class Circuit{
protected:
    int U, I;
    double R;

public:
    virtual double getResistance() const = 0;
};

class Single:public Circuit{
public:
    Single(int U,int I){
        this->U = U;
        this->I = I;
        this->R = U / I;
    }
    double getResistance() const override {
        return this->R;
    }
};
class Series:public Circuit{
private:
    vector<Circuit *> list;
public:
    void add(Circuit *circuit){
        this->list.push_back(circuit);
    }
    double getResistance() const override {
        double count = 0;
        for (Circuit *circuit : this->list)
            count += circuit->getResistance();
        return count;
    }
};
class Parallel:public Circuit{
private:
    vector<Circuit *> list;
public:
    void add(Circuit *circuit){
        this->list.push_back(circuit);
    }
    double getResistance() const override {
        double count = 0;
        for (Circuit *circuit : this->list)
            count += 1/circuit->getResistance();
        return 1/count;
    }
};
int main()
{
    Parallel *one = new Parallel();
    Single *two = new Single(40, 10);
    Single *three = new Single(40, 10);
    Single *four = new Single(40, 10);

    one->add(two);
    one->add(three);
    one->add(four);

    cout << one->getResistance() << endl;
    system("pause");
    return 0;
}

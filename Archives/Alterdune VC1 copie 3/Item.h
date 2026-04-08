#pragma once
#include <string>

class Player; // forward declaration

class Item {
private:
    std::string n; // name
    int v; // value
    int q; // quantity

public:
    Item(const std::string& n, int v, int q);

    std::string getN() const;
    int getV() const;
    int getQ() const;
    bool isAv() const;
    void useOn(Player& cible);
    void disp() const;
};

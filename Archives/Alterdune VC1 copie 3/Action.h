#include <string>
#include <vector>

class Action {
private:
    std::string i; // id
    std::string t; // texte
    int mi; // mercyImpact

public:
    Action(std::string i, std::string t, int mi) : i(i), t(t), mi(mi) {}

    std::string getI() const { return i; }
    std::string getT() const { return t; }
    int getMi() const { return mi; }
};
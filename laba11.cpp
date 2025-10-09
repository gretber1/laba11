#include <iostream>

using namespace std;

class Firma_gruzoperevozok{

public:
    string name;
    double tarif;
    double mass;
//    double money;
    Firma_gruzoperevozok(string name_f, double tarif_f, double mass_f) {
        if (!validateInput(name_f, tarif_f, mass_f)){
            name = "Unknown";
            tarif = 1.0;
            mass = 0.0;
            return;
        }
        name = name_f;
        tarif = tarif_f;
        mass = mass_f;
        return;
    };

    Firma_gruzoperevozok(){
        name = "Unknown";
        tarif = 1.0;
        mass = 0.0;
    };

    bool validateInput(string name_f, double tarif_f, double mass_f) {
        if (name_f.empty()) {
            cout << "Company name cannot be empty!" << endl;
            return false;
        }
        if (tarif_f <= 0 or tarif_f > 10000000) {
            cout << "Your tariff is bad. Make it possitive or not so big please." << endl;
            return false;
        }
        if (mass_f < 0 or mass_f > 1000000000) {
            cout << "I think your mass is fake... Make it possitive or 0 at least..." << endl;
            return false;
        }
        return true;
    }

    void getname() {
        cout << "Company name is: "+name+"! What a nice name!" << endl;
    };

    void gettariff() {
        cout << "Tariff per 1 ton for "+name+" is "+to_string(tarif)+" idk mb rubles" << endl;
    };

    void getmass() {
        cout << "Total tranported mass by "+name+" is "+to_string(mass)+" tons! Well done!" << endl;
    };

    void profit() {
        cout << name+"'s profit is "+to_string(mass * tarif)+" rubles" << endl;
    }
    void addmass(double mega_mass) {
        if (mega_mass <= 0) {
            cout << "Are you sure you transpotred negative mass?" << endl;
        }
        else if(mega_mass > 1000000){
            cout << "Nah, I don't trust you, make it less" << endl;
        }
        else {
            mass += mega_mass;
        }
    }

    void changename(string new_name) {
        if (new_name.empty()) {
            cout << "New name cannot be empty!" << endl;
            return;
        }
        name = new_name;
    }

};

int main() {
    Firma_gruzoperevozok Gruzovichkoff("Gruzovichkoff", 5000, 1000000);
        
//    Firma_gruzoperevozok A4;

    Gruzovichkoff.getname();
    Gruzovichkoff.gettariff();
    Gruzovichkoff.getmass();
    Gruzovichkoff.profit();
    Gruzovichkoff.addmass(5000);
    Gruzovichkoff.getmass();

//    A4.getname();

    return 0;
}
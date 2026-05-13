#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Sensor {
    int sensor_id;
    float sicaklik;
};

int main()
{
    long long int id;
    int N, E;
    float exSicaklik;
    Sensor s1;
    cout << "Please enter your student id: " << endl;
    cin >> id;
    N = id % 50;
    E = id % 100;

    fstream file;
    file.open("sensors.bin", ios::in | ios::out | ios::binary);
    
    if (!file.is_open()) {
        cout << "File couldn't open.";
        return 1;
    }

    file.seekg(N * sizeof(Sensor), ios::beg);
    file.read((char*)&s1, sizeof(Sensor));
    exSicaklik = s1.sicaklik;
    s1.sicaklik += E;
    file.close();

    fstream SText;
    SText.open(to_string(id) + "_Quiz5.txt", ios::out);
    SText << "Number: " << id << endl;
    SText << "Sensor Index Used in the Process: " << N << endl;
    SText << "First Temprature: " << exSicaklik << " -> New Temprature: " << s1.sicaklik << endl;
    SText.close();
    return 0;
}


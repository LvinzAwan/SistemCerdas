//Paulus Windi Kurniawan
//Teknik Komputer 2023
#include <iostream>
#include <string>
#include <cmath>
using namespace std; 

float FuzzySegitiga(float x, float a, float b, float c ) {
    if(x <= a || x >= c) return 0.0f;
    else if( x == b) return 1.0f;
    else if (x > a && x < b ) return (x - a) / (b - a);
    else if (x > b && x < c) return (c - x) / (c - b);
    else return 0.0f;
}

float FuzzyTrapesium(float x, float a, float b, float c, float d) {
    if (a == b) {
        if (x <= a) {
            return 1.0f; 
        } else if (x >= d) {
            return 0.0f; 
        } else if (x > c && x < d) {
            return (d - x) / (d - c); 
        } else {
            return 1.0f; 
        }
    } else if (c == d) {
        if (x <= a) {
            return 0.0f; 
        } else if (x >= c) {
            return 1.0f; 
        } else if (x > a && x < b) {
            return (x - a) / (b - a); 
        } else {
            return 1.0f; 
        }
    } else {
        if (x <= a || x >= d) {
            return 0.0f; 
        } else if (x >= b && x <= c) {
            return 1.0f; 
        } else if (x > a && x < b) {
            return (x - a) / (b - a); 
        } else {
            return (d - x) / (d - c); 
        }
    }
}

float defuzzifikasi(float NoBreak, float Soft, float Moderate, float Hard) {
    float total = NoBreak + Soft + Moderate + Hard;
    if (total == 0) return 0; 
    return (NoBreak * 0 + Soft * 25 + Moderate * 50 + Hard * 100) / total;
}

float hitungFuzzy(float distance, float speed){
    
    //Fuzzyfikasi Distance
    float Short    = FuzzyTrapesium(distance, 0, 0, 2, 6);
    float Medium   = FuzzySegitiga(distance, 2, 6, 10);
    float Long     = FuzzySegitiga(distance, 6, 10, 14);
    float VeryLong = FuzzyTrapesium(distance, 10, 14, 100000, 100000);

    //Fuzzyfikasi Speed
    float low      = FuzzyTrapesium(speed, 0, 0, 20, 40);
    float medium   = FuzzySegitiga(speed, 20,40, 60);
    float high     = FuzzyTrapesium(speed, 40, 60, 100000, 100000);

     //NoBreak
    float rule1 = min(low,Long);
    float rule2 = min(low,VeryLong);
    float rule3 = min(medium,VeryLong);

    //Soft
    float rule4 = min(low, Medium);
    float rule5 = min(medium, Long);
    float rule6 = min(high, VeryLong);

    //Moderate
    float rule7 = min(low, Short);
    float rule8 = min(medium, Medium);
    float rule9 = min(high, Long);

    //Hard
    float rule10 = min(medium, Short);
    float rule11 = min(high, Short);
    float rule12 = min(high, Medium);

    float agg_NoBreak = max(rule1, max(rule2, rule3));
    float agg_Soft    = max(rule4, max(rule5, rule6));
    float agg_Moderate= max(rule7, max(rule8, rule9));
    float agg_Hard    = max(rule10, max(rule11, rule12));
    
    return defuzzifikasi(agg_NoBreak, agg_Soft, agg_Moderate, agg_Hard);
}


int main() {
    float distance, speed, output;
    string breaking;
    while(true) {
    cout << "\nMasukkan distance / jarak dalam (meter) : ";
    cin >> distance;
    cout << "Masukkan speed / kecepatan dalam (km/h) : ";
    cin >> speed;

    output = hitungFuzzy(distance, speed);
    
    if (output == 0) breaking = "No Break";
    else if(output <= 25) breaking = "Soft";
    else if(output <= 50) breaking = "Moderate";
    else breaking = "Hard";

    cout << "Dengan distance " << distance 
      << " m dan speed " << speed 
      << " km/h  maka pengeriman yang dilakukan " << breaking 
      << " (" << output << ")" << endl;
    }
    
    return 0;
}
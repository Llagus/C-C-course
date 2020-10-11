#include <iostream>
#include <cmath>

using namespace std; 

double OkumuraHata (bool large_city, double f, double hb, double hm, double d){
    double L_dB; 
    double a_hm;
    const double f_llindar = 200.0;  

    if(large_city == true){
        if (f<=f_llindar){
            a_hm = 8.29*pow((log10(static_cast<double>(1.54*hm))),2)-1.1;
        } else{
            a_hm = 3.2*pow(log10(static_cast<double>(11.75*hm)),2)- 4.97;
        }
    }
    else{
        a_hm = 0.8 + (1.1*log10(f) - 0.7)*hm - 1.56* log10(f); 
    }
    L_dB = 69.55 + 26.16*log10(static_cast<double>(f)) - 13.82*log10(static_cast<double>(hb)) - a_hm + 
    (44.9-6.55*log10(static_cast<double>(hb)))*log10(static_cast<double>(d));

    return L_dB; 
}


int main(){
    double f, hb, hm, d, L_dB; 
    bool large_city; 
    cout<<"The Okumura-Hata model depends on 5 parameters:"<<endl
    <<"The size of the city.\nThe frequency.\nThe heigh of the transmisison antenna.\nThe heigh of the receiver antenna.\nThe distance between them.\n"<<endl
    <<"Introduce the values:"<<endl; 
    cout<<"The size of the city, [0] for small or medium-sized city and [1] for large-sized city: ";
    cin>>large_city;
    cout<<"The work frequency of the sistem in MHz is: ";  
    cin>>f; 
    cout<<"The heigh of the trasmissor antenna hb, in meters, is: ";
    cin>>hb; 
    cout<<"The heigh of the receiver antenna hm, in meters, is: ";
    cin>>hm; 
    cout<<"The distance between them d, in kilometers, is: "; 
    cin>>d;
     
    L_dB = OkumuraHata(large_city,f,hb,hm,d);
    cout<<"L(dB)= "<< L_dB << endl; 
    return 0; 
}
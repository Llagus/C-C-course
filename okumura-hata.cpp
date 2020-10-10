#include <iostream>
#include <cmath>

using namespace std; 

double OkumuraHata (double f, double hb, double hm, double d){
    double L_dB; 
    double a_hm;
    const double f_llindar = 200.0;  

    if (f<=f_llindar){
        a_hm = 8.29*pow((log10(static_cast<double>(1.54*hm))),2)-1.1;
    } else{
        a_hm = 3.2*pow(log10(static_cast<double>(11.75*hm)),2)- 4.97;
    }

    L_dB = 69.55 + 26.16*log10(static_cast<double>(f)) - 13.82*log10(static_cast<double>(hb)) - a_hm + 
    (44.9-6.55*log10(static_cast<double>(hb)))*log10(static_cast<double>(d));

    return L_dB; 
}


int main(){
    double f, hb, hm, d, L_dB; 
    cout<<"The Okumura-Hata model depends on 4 variables:"<<endl
    <<"The frequency.\nThe heigh of the transmisison antenna.\nThe heigh of the receiver antenna.\nThe distance between them.\n"<<endl
    <<"Introduce the values:"<<endl; 
    cout<<"The work frequency of the sistem in MHz is: ";  
    cin>>f; 
    cout<<"The heigh of the trasmissor antenna hb is: ";
    cin>>hb; 
    cout<<"The heigh of the receiver antenna hm is: ";
    cin>>hm; 
    cout<<"The distance between them d is: "; 
    cin>>d;
     
    L_dB = OkumuraHata(f,hb,hm,d);
    cout<<"L(dB)= "<< L_dB << endl; 
    return 0; 
}
#include <iostream>
using namespace std; 

class point {
    public: 
        point (double x, double y){
            this->x = x; 
            this->y = y; 
        }
        point (){
            this->x = 0.0;
            this->y = 0.0;
        }


        double getx()const{return this->x;}
        double gety()const{return this->y;} 
        void setvalue(double x, double y){this->x = x; this->y = y; } 

        point operator+ (point& p){
            point sum = point(p.getx()+this->x, p.gety()+this->y);
            return sum; 
        }
    private: 
        double x,y;
};
    ostream& operator<< (ostream& out, point& p){
    out<<"("<<p.getx()<<","<<p.gety()<<")"<<endl;
    return out; 
    }




//main program
int main() {
    point a = {3.5,2.0};
    point b = {1.5,2.5};
    point c = a+b; 
    point d ; 
    cout<<"a point is:"<<a<<"b point is: "<<b<<"the sum of bouth is:"<<c<<"d is the origin:"<<d;
    d.setvalue(a.getx(), b.gety()); 
    cout<<"and d now is: "<<d; 

    return 0;
}


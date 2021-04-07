class Pair {
public:
    double a,b;
    Pair(double x, double y) { a = x; b = y; }
    Pair(): a(0), b(0){}
};

class equalPair : public Pair{
    public:
        equalPair(double a, double b) {
            Pair(a,b);
            isequal = (a == b);
        }
    
    private: 
        bool isequal;
};

int main(){
    equalPair(1.0, 0.0);
    
    return 0; 
}
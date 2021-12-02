#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double crossProduct(double x1, double y1, double x2, double y2){
    return (x1*y2-y1*x2);
}

double distance1(double x1, double y1, double x2, double y2){
    double b = (x1*x2+y1*y2)/sqrt(x1*x1+y1*y1);
    double d = (x2*x2+y2*y2) - b*b;
    return (sqrt(d));
}
/*double distance2(double x111, double y111, double x222, double y222){

    return ((x111-x222)*(x111-x222)+(y111-y222)*(y111-y222));
}*/

int main() {

    ifstream file("in.txt");
    file.is_open();

    double x0, y0, x, y;

    file >> x0 >> y0;

    double x_r=0, x_l=0, y_r=0, y_l=0, l1=0, l2=0, var_r=0.00001, var_l=0.00001, k=0;

   while(!file.eof()){

        file >> x >> y;
        k = crossProduct(x0, y0, x, y);
        cout <<"k="<<k<< endl;
        cout <<"x="<<x<<" y="<<y<< endl;
        l1 = distance1(x0, y0, x, y);
        l2 = distance1(x0, y0, x, y);
        if (k <= 0){
            cout <<"l1="<<l1<< endl;
            if (l1>var_r){
                var_r = l1;
                x_r = x;
                y_r = y;
            }
        } else {
            cout <<"l2="<<l2<< endl;
            if (l2 > var_l) {
                var_l = l2;
                x_l = x;
                y_l = y;
            }
        }
        if (l2 <= var_l and l1 <= var_r){
            x_r = x;
            y_r = y;
        }
        l1 = 0;
        l2 = 0;
    }


    file.close();

    cout << "Leftmost: " << x_l << " " << y_l << endl;
    cout << "Rightmost: " << x_r << " " << y_r << endl;

    return 0;
}
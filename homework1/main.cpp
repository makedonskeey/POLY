#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

float crossProduct(float x1, float y1, float x2, float y2){
    return (x1*y2-y1*x2);
}

float distance1(float x1, float y1, float x2, float y2){
    float b = (x1*x2+y1*y2)/sqrt(x1*x1+y1*y1);
    float d = (x2*x2+y2*y2) - b*b;
    return (sqrt(d));
}
/*double distance2(double x111, double y111, double x222, double y222){

    return ((x111-x222)*(x111-x222)+(y111-y222)*(y111-y222));
}*/

int main() {

    ifstream file("in.txt");
    file.is_open();

    float x0, y0, x, y;

    file >> x0 >> y0;

    //file.close();


    float x_r=0,x_l=0,y_r=0,y_l=0;
    float l1=0, l2=0, var_r=0.0001, var_l=0.0001;
    float k=0;

   while(!file.eof()){

        file >> x >> y;
        k = crossProduct(x0, y0, x, y);
        //cout <<"k="<<k<< endl;
        //cout <<"x="<<x<<" y="<<y<< endl;
        l1 = distance1(x0, y0, x, y);
        l2 = distance1(x0, y0, x, y);
        if (k <= 0){
            //cout <<"l1="<<l1<< endl;
            if (l1>var_r){
                var_r = l1;
                x_r = x;
                y_r = y;
            }
        } else {
            //cout <<"l2="<<l2<< endl;
            if (l2 > var_l) {
                var_l = l2;
                x_l = x;
                y_l = y;
            }
        }
        if (l2 == 0 and l1 == 0){
            x_r = x;
            y_r = y;
        }
    }


    file.close();

    cout << "Leftmost: " << x_l << " " << y_l << endl;
    cout << "Rightmost: " << x_r << " " << y_r << endl;

    return 0;
}
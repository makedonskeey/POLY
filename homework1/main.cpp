#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int crossProduct(int x1, int y1, int x2, int y2){
    return (x1*y2-y1*x2);
}

float distance1(int x1, int y1, int x2, int y2){
    float a = static_cast<float>(x1*x2+y1*y2);
    float b = a/sqrt(x1*x1+y1*y1);
    float c = static_cast<float>(x2*x2+y2*y2);
    float d = c - b*b;
    return (sqrt(d));
}


int main() {

    ifstream file("in.txt");
    file.is_open();

    int x0, y0, x, y;

    file >> x0 >> y0;

    //float u0 = static_cast<float>(x0);
    //float v0 = static_cast<float>(y0);

    float l1, l2, lr1, lr2, var_r=0, var_l=0;
    int x_r1=0, x_l=0, y_r1=0, y_l=0, x_r2=0, y_r2=0, x_r=0, y_r=0, k;

   while(!file.eof()){

        file >> x >> y;

       //float u = static_cast<float>(x);
       //float v = static_cast<float>(y);

        k = crossProduct(x0, y0, x, y);

        //cout <<"k="<<k<< endl;
        //cout <<"x="<<x<<" y="<<y<< endl;

        if (k < 0){
            l1 = distance1(x0, y0, x, y);
            //cout <<"l1="<<l1<< endl;
            if (l1 >= var_r){
                var_r = l1;
                x_r1 = x;
                y_r1 = y;
            }
        } else if (k > 0) {
            l2 = distance1(x0, y0, x, y);
            //cout <<"l2="<<l2<< endl;
            if (l2 >= var_l) {
                var_l = l2;
                x_l = x;
                y_l = y;
            }
        } else {
            x_r2 = x;
            y_r2 = y;
        }

        lr1 = distance1(x0, y0, x_r1, y_r1);
        lr2 = distance1(x0, y0, x_r2, y_r2);

        if (lr1 > lr2){
            x_r = x_r1;
            y_r = y_r1;
        } else {
            x_r = x_r2;
            y_r = y_r2;
        }
    }


    file.close();

    cout << "Leftmost: " << x_l << " " << y_l << endl;
    cout << "Rightmost: " << x_r << " " << y_r << endl;

    return 0;
}
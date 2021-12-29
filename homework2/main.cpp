#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
        if(argc > 2){
            cout << "Too much arguments" << endl;
            exit(1);
        }else if(argc == 1){
            cout << "Not enough input arguments" << endl;
            exit(2);
        }
        //int main(int argc, char** argv) {
/*if (argc == 2){
        cout << "1st argument: "<< argv[1] << endl;
    } else {
        // аргументов нет или их больше чем мы ожидаем
    }*/
    ifstream file(argv[1]);

    int s = 1;

    double *X = new double [s];
    double *H = new double [s];
    double *Y = new double [s];



    file.is_open();

    double vx, vy, h0, x, h, t, t1, t2, x1, x2, g = 9.81;

    file >> h0;
    file >> vx >> vy;

    H[0] = h0;
    Y[0] = h0;
    X[0] = 0;

    int i = 1, k = 0;

    while (true) {

        s = s + 1;

        /*if (file.eof()){
            cout << i-1;
            break;
        }*/

        //cout << "vx=" << vx << endl;
        //cout << "vy=" << vy << endl;

        file >> x >> h;

        if ((x == double(NULL)) or (h == double(NULL))){
            cout << i-1 << endl;
            break;
        }

        //cout << "x=" << x << endl;
        //cout << "h=" << h << endl;

        X[i] = x;
        H[i] = h;

        t = abs( (X[i] - X[i-1] ) / vx);

        //cout << "t=" << t << endl;

        if (vx > 0) {
            Y[i] = Y[i-1] + vy * t - g * t * t / 2;
        } else {
            Y[i] = Y[i+1] + vy * t - g * t * t / 2;
        }

        //cout << "Y=" << Y[i] << endl;

        if (Y[i] <= 0){
            cout << i-1 << endl;
            break;
        }

        if (Y[i] > H[i]){

            if (vx > 0){
                i++;
            } else {
                i--;
            }
            vy = vy - g * t;

        } else {

            k = k + 1;
            vy = vy - g * t;

            if (k % 2 != 0){
                vx = - vx;
            } else {
                vx = vx;
            }

            t1 = vy / g - 0.5 * sqrt(4 * vy * vy / (g * g) + 8 * Y[i] / g);
            t2 = vy / g + 0.5 * sqrt(4 * vy * vy / (g * g) + 8 * Y[i] / g);

            //cout << "t1=" << t1 << endl;
            //cout << "t2=" << t2 << endl;

            x1 = X[i] + vx * t2;
            x2 = X[i] + vx * t1;

            //cout << "x1=" << x1 << endl;
            //cout << "x2=" << x2 << endl;

            if (x1 > x2){
                x1 = x2;
                x2 = x1;
            }

            if (vx > 0){
                if (x2 <= X[i+1]){
                    cout << i << endl;
                    break;
                } else {
                    i++;
                }
            } else {
                if (x1 >= X[i-1]){
                    cout << i-1 << endl;
                    break;
                } else {
                    i--;
                }
            }
        }
        //cout << "i=" << i << endl;
        /*if (i < 1) {
            cout << 0;
            check = true;
        }*/
        /*if (i < 1) {
            cout << 0;
            break;
        }*/
        if (file.eof()){
            cout << i-1 << endl;
            break;
        }

    }

    file.close();

    delete [] X;
    delete [] H;
    delete [] Y;

    return 0;
}
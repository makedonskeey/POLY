#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    if (argc == 2){
        cout << "1st argument: "<< argv[1] << endl;
    } else {
        // аргументов нет или их больше чем мы ожидаем
    }

    ifstream file(argv[1]);

    double *X = new double [1];
    double *H = new double [1];
    double *Y = new double [1];



    if (file.is_open()){

        double vx, vy, h0, x, h, t, t1, t2, x1, x2, g = 9.81;

        file >> h0;
        file >> vx >> vy;

        H[0] = h0;
        Y[0] = h0;
        X[0] = 0;

        int i = 1, k = 0;


        while (true) {

            if (file.eof()){
                cout << i-1;
                break;
            }

            file >> x >> h;

            //cout << "x=" << x << endl;
            //cout << "h=" << h << endl;

            X[i] = x;
            H[i] = h;

            t = abs( (X[i] - X[i-1] ) / vx);

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

                x1 = X[i] + vx * t2;
                x2 = X[i] + vx * t1;

                if (vx > 0){
                    if (x1 > x2){
                        if (x1 <= X[i+1]){
                            cout << i << endl;
                            break;
                        } else {
                            i++;
                        }
                    } else {
                        if (x2 <= X[i+1]){
                            cout << i << endl;
                            break;
                        } else {
                            i++;
                        }
                    }
                } else {
                    if (x1 > x2){
                        if (x2 >= X[i-1]){
                            cout << i-1 << endl;
                            break;
                        } else {
                            i--;
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
            }

            if (i < 1) {
                cout << 0;
                break;
            }


        }

    }

    delete [] X;
    delete [] H;
    delete [] Y;

    return 0;
}
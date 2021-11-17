#include <iostream>
#include <cmath>
#include <string>
#include <fstream>


using namespace std;

int main(int argc, char** argv)
{
    if (argc == 2){

        cout << "1st argument: "<< argv[1] << endl;
    } else {

        // аргументов нет или их больше чем мы ожидаем
    }

    ifstream file(argv[1]);
    int j=0;
    auto STR = new double[50];

    if (file.is_open()){
        //cout << "File is open" << endl;
        while(!file.eof()){
            double w;
            file >> w;
            STR[j] = w;
            j = j + 1;
        }
    } else {
        //cout << "File is not open" << endl;
    }

    double h0 = STR[0], v_x = STR[1], v_y = STR[2];
    double massiveX[(j-2)/2];
    for (int m = 2; m<=(j/2); m++){

        massiveX[m-1]=STR[2*m-1];
    }
    double massiveH[(j-2)/2];
    for (int u = 2; u<=(j/2); u++){

        massiveH[u-1]=STR[2*u];
    }
    massiveX[0]=0;
    massiveH[0]=h0;

    double g=9.81,x1,x2,t,t1,t2;
    int i = 1;

    bool check = false;
    auto Y = new double[10];
    Y[0] = h0;
    int k = 0;

    while (check == false)
    {

        t=abs((massiveX[i]-massiveX[i-1])/v_x);

        if (v_x>0){
            Y[i]=Y[i-1]+v_y*t-g*t*t/2;
        } else {
            Y[i]=Y[i+1]+v_y*t-g*t*t/2;
        }

        if (Y[i]<=0){
            cout << i-1 << endl;
            break;
        }

        if (Y[i]>massiveH[i]){

            if (v_x>0){
                i++;
            } else {
                i--;
            }
            v_y = v_y - g*t;

        } else {

            k=k+1;
            v_y=v_y-g*t;

            if (k % 2 != 0){
                v_x = -v_x;
            } else {
                v_x = v_x;
            }

            t1=v_y/g+0.5*sqrt(4*v_y*v_y/(g*g)+8*Y[i]/g);
            t2=v_y/g-0.5*sqrt(4*v_y*v_y/(g*g)+8*Y[i]/g);

            x1 = massiveX[i]+v_x*t1;
            x2 = massiveX[i]+v_x*t2;

            if (v_x>0){
                if (x1>x2){
                    if (x1<=massiveX[i+1]){
                        cout << i << endl;
                        check = true;
                    } else {
                        i++;
                    }
                } else {
                    if (x2<=massiveX[i+1]){
                        cout << i << endl;
                        check = true;
                    } else {
                        i++;
                    }
                }
            } else {
                if (x1>x2){
                    if (x2>=massiveX[i-1]){
                        cout << i-1 << endl;
                        check = true;
                    } else {
                        i--;
                    }
                } else {
                    if (x1>=massiveX[i-1]){
                        cout << i-1 << endl;
                        check = true;
                    } else {
                        i--;
                    }
                }
            }
            k=0;
        }

        if (i<1) {
            cout << 0;
            check = true;
        } else if (i>j/2){
            cout << i;
            check = true;
        } else {

        }

    }

    delete [] Y;
    delete [] STR;

    return 0;
}
#include <iostream>
#include <string>
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

    int w = 0;

    string path = "in.txt"; //путь к файлу

    ifstream fin;
    fin.open(path);

    string str;

    while(!fin.eof()) // Когда мы натолкнемся на конец файла, мы выйдем из цикла
    {
        fin >> str; //Считываем строки из файла
        w++;
    }

    fin.close();

    int u = w;

    fin.open(path);
    cout << " " << endl;

    int n= u/2;  // строки
    int m= 2;  // столбцы

    double vectorCoordinates[n][m];


    while(!fin.eof()) // Когда мы натолкнемся на конец файла, мы выйдем из цикла
    {

        for (int i = 0; i < n; i++)  // Заполняем массив
        {
            for (int j = 0; j < m; j++)
            {
                fin >> str; //Считываем строки из файла

                const char *c_inp = str.c_str();
                double res = atoi(c_inp);

                vectorCoordinates[i][j] = res;
            }
        }

    }
    fin.close();

    double x = vectorCoordinates[0][0];
    double y = vectorCoordinates[0][1];

    double x_r=0,x_l=0,y_r=0,y_l=0;
    double l1, l2, var=0;
    double k;
    for (int i = 1; i < n; i++){


        k = crossProduct(x,y, vectorCoordinates[i][0], vectorCoordinates[i][1]);
        //cout <<"k="<<k<< endl;

        if (k<0){

            l1 = distance1(x, y, vectorCoordinates[i][0], vectorCoordinates[i][1]);
            //cout <<"l1="<<l1<< endl;
            if (l1>var){
                var = l1;
                x_r = vectorCoordinates[i][0];
                y_r = vectorCoordinates[i][1];
            }
        } else {

            l2 = distance1(x, y, vectorCoordinates[i][0], vectorCoordinates[i][1]);
            //cout <<"l2="<<l2<< endl;
            if (l2>var){
                var = l2;
                x_l = vectorCoordinates[i][0];
                y_l = vectorCoordinates[i][1];
            }
        }
    }


    if (x_r==0 and y_r==0){
        cout << "There are not points on the right side" << endl;
        cout << "Leftmost: " << x_l << "," << y_l << endl;
    }
    else if (x_l==0 and y_l==0){
        cout << "There are not points on the left side" << endl;
        cout << "Rightmost: " << x_r << "," << y_r << endl;
    }
    else {
        cout << "Leftmost: " << x_l << "," << y_l << endl;
        cout << "Rightmost: " << x_r << "," << y_r << endl;
    }


    return 0;
}
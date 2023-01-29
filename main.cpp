#include <iostream>
#include <cmath>
#include <chrono>
#include <windows.h>
using namespace std;
int u_sign=0;
int u_sign_prev = 0;
bool hasChanged = false;
bool ishalf=false;
double B1[6];
double C1[6];
double B2[6];
double C2[6];
double A[6];
double coef_2pi50=6.283*0.6;
double gen=6.283*1.8;
double n_1 = 0;
double n_2 = 0;
auto timer_get_samples_1= std::chrono::steady_clock::now();
auto timer_get_samples_2= std::chrono::steady_clock::now();
int size_count=60;
int main() {
    auto begin = std::chrono::steady_clock::now();
    double ar_t[size_count][2];
    timer_get_samples_1= std::chrono::steady_clock::now();
    timer_get_samples_2= std::chrono::steady_clock::now();
    for(int i=0;i<size_count;i++){
        Sleep(100);
        double temp=((chrono::duration_cast<std::chrono::microseconds>(chrono::steady_clock::now() - begin).count())/1000000.0f);
        ar_t[i][0]=temp;
        ar_t[i][1]=sin(temp*gen);
        double u_sin=sin(temp*coef_2pi50);
        double u_straighten=sin(temp*gen);
        if (u_sin > 0){
            u_sign = 1;
        }
        else if (u_sin == 0){
            u_sign = 0;
        }else{
            u_sign = -1;
        }
        if (u_sign_prev != u_sign){
            hasChanged = true;
        }
        double temp1 =(((chrono::duration_cast<std::chrono::microseconds>(chrono::steady_clock::now() -timer_get_samples_1).count())/1000000.0f));
        double temp2 =(((chrono::duration_cast<std::chrono::microseconds>(chrono::steady_clock::now() -timer_get_samples_2).count())/1000000.0f));
        for (int t = 1;t <=5; t ++){
            double t_coef = double(t)* coef_2pi50;
            B1[t] += u_straighten * sin(t_coef *temp1);
            C1[t] += u_straighten * cos(t_coef *temp1);
            B2[t] += u_straighten * sin(t_coef *temp2);
            C2[t] += u_straighten * cos(t_coef *temp2);

        }
        if (hasChanged){
            if (ishalf){
                for (int f = 1; f <=5; f ++){
                    A[f]=(2.0f*sqrt((B1[f])*(B1[f]) +(C1[f])*(C1[f])))/n_1;
                }
                cout<<"*************************"<<endl;
                cout<<"A0  A1  A2  A3  A4  A5"<<endl;
                cout<<A[0]<<" "<<A[1]<<" "<<A[2]<<" "<<A[3]<<" "<<A[4]<<" "<<A[5]<<" "<<endl;
                n_1=0;
                timer_get_samples_1= std::chrono::steady_clock::now();
                for (int r = 0; r <=5; r ++){
                    B1[r] =0;
                    C1[r] =0;
                }
                ishalf= false;
            }else{
                for (int f = 1; f <=5; f ++){
                    A[f]=(2.0f*sqrt((B2[f])*(B2[f]) +(C2[f])*(C2[f])))/n_2;
                }
                cout<<"*************************"<<endl;
                cout<<"A0  A1  A2  A3  A4  A5"<<endl;
                cout<<A[0]<<" "<<A[1]<<" "<<A[2]<<" "<<A[3]<<" "<<A[4]<<" "<<A[5]<<" "<<endl;
                n_2=0;
                timer_get_samples_2= std::chrono::steady_clock::now();
                for (int r = 0; r <=5; r ++){
                    B2[r] =0;
                    C2[r] =0;
                }
                ishalf= true;
            }
            hasChanged = false;
        }
        u_sign_prev = u_sign;
        n_1++;
        n_2++;

    }

    cout<<"\n\n\n\n*************************"<<endl;
    for(int i=0;i<size_count;i++)
        cout<<ar_t[i][0]<<" "<<ar_t[i][1]<<endl;
    return 0;
}

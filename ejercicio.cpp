#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


template <class T>
void escribe(string archivo, T* datos, int n_dat){
  ofstream outfile;
  //abre el archivo.
  outfile.open(archivo);

  for (int i=0; i < n_dat; i++){
    outfile << datos[i] << endl;
  }
  //cierra el archivo.
  outfile.close(); 
}

void rk4 (double* v, double* x, double k, double m, double lambda, double h, int pasos);
double dx(double x, double k, double m, double lambda);
double dv(double v);

int main(){
    int lambda = 1;
    double k = 100;
    double m = 2;
    double h = 0.01;
    double x0 = 0;
    double xf = 10;
    int pasos = (xf-x0)/h;
    
    double* x = new double[pasos];
    double* v = new double[pasos];

    rk4(v,x,k,m,lambda,h,pasos);

    escribe("x.txt",x,pasos);
    escribe("v.txt",v,pasos);

    delete[] x;
    delete[] v;

    return 0;
}
double dx(double x, double k, double m, double lambda){
    return (-k/m)*pow(x,lambda);
}

double dv(double v){
    return v;
}

void rk4 (double* v, double* x, double k, double m, double lambda, double h, int pasos){
    x[0] = 1; //condiciones iniciales
    v[0] = 1;
    for(int i = 1; i< pasos; i++){
        double k10, k11, k20, k21, k30, k31, k40, k41;
    
        k10 = h*dv(v[i-1]);
        k11 = h*dx(x[i-1], k, m, lambda);
        
        k20 = h*dv(v[i-1] + k10/2);
        k21 = h*dx(x[i-1] + k11/2, k, m, lambda);

        k30 = h*dv(v[i-1] + k20/2);
        k31 = h*dx(x[i-1] + k21/2, k, m, lambda);

        k40 = h*dv(v[i-1] + k30);
        k41 = h*dx(x[i-1] + k31, k, m, lambda);
        

        x[i] = x[i-1] + (1.0/6.0)*(k10 + 2*k20 + 2*k30 + k40);
        v[i] = v[i-1] + (1.0/6.0)*(k11 + 2*k21 + 2*k31 + k41);
        cout << v[i] << "\t" << x[i] << endl;
    }
}
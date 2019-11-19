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
//sin friccion
void rk4 (double* v, double* x, double k, double m, double lambda, double h, int pasos);
//con friccion
void rk4 (double* v, double* x, double k, double m, double lambda, double h, double gamma, int pasos);
void euler(double* x, double* v, double h, double k, double m, double lambda, int pasos);
//con friccion
double dx(double x, double v, double gamma, double k, double m, double lambda);
//sin friccion
double dx(double x, double k, double m, double lambda);
double dv(double v);

int main(){
    int lambda = 1;
    double k = 100;
    double m = 2;
    double h = 0.01;
    double gamma = 5;
    double x0 = 0;
    double xf = 10;
    int pasos = (xf-x0)/h;
    
    double* x = new double[pasos];
    double* v = new double[pasos];

    euler(x,v,h,k,m,lambda,pasos);
    escribe("x.txt",x,pasos);
    escribe("v.txt",v,pasos);


    double* xrk4 = new double[pasos];
    double* vrk4 = new double[pasos];

    rk4(vrk4,xrk4,k,m,lambda,h,pasos);

    escribe("xrk4.txt",xrk4,pasos);
    escribe("vrk4.txt",vrk4,pasos);

    double* xrk4f = new double[pasos];
    double* vrk4f = new double[pasos];

    rk4(vrk4f,xrk4f,k,m,lambda,h,gamma,pasos);

    escribe("xrk4f.txt",xrk4f,pasos);
    escribe("vrk4f.txt",vrk4f,pasos);

    delete[] xrk4;
    delete[] vrk4;
    delete[] xrk4f;
    delete[] vrk4f;
    delete[] x;
    delete[] v;

    return 0;
}
double dx(double x, double k, double m, double lambda){
    return (-k/m)*pow(x,lambda);
}
double dx(double x, double v, double gamma, double k, double m, double lambda){
    return (-k/m)*pow(x,lambda) - gamma*v;
}
double dv(double v){
    return v;
}

void euler(double* x, double* v, double h, double k, double m, double lambda, int pasos){
    x[0] = 1; //condiciones iniciales
    v[0] = 1;

    for(int i=1; i<pasos; i++){
        x[i] = x[i-1] + h*dx(x[i-1],k,m,lambda); 
        v[i] = v[i-1] + h*dv(v[i-1]);
    }
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
    }
}

void rk4 (double* v, double* x, double k, double m, double lambda, double h, double gamma, int pasos){
    x[0] = 1; //condiciones iniciales
    v[0] = 1;
    for(int i = 1; i< pasos; i++){
        double k10, k11, k20, k21, k30, k31, k40, k41;
    
        k10 = h*dv(v[i-1]);
        k11 = h*dx(x[i-1], v[i-1], gamma, k, m, lambda);
        
        k20 = h*dv(v[i-1] + k10/2);
        k21 = h*dx(x[i-1] + k11/2, v[i-1] + k10/2, gamma, k, m, lambda);

        k30 = h*dv(v[i-1] + k20/2);
        k31 = h*dx(x[i-1] + k21/2, v[i-1] + k20/2, gamma, k, m, lambda);

        k40 = h*dv(v[i-1] + k30);
        k41 = h*dx(x[i-1] + k31, v[i-1] + k30, gamma, k, m, lambda);
        

        x[i] = x[i-1] + (1.0/6.0)*(k10 + 2*k20 + 2*k30 + k40);
        v[i] = v[i-1] + (1.0/6.0)*(k11 + 2*k21 + 2*k31 + k41);
    }
}
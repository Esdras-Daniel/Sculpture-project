#include "escultor.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){

    srand(time(NULL));

    int nz = 80, ny = 80, nx = 80;
    Escultor teste(nx,ny,nz);

    //Torre
    teste.SetColor(0.0,0.0,0,0); //Preto
    teste.PutEllipsoid(40,40,70,19,5,13);
    teste.CutEllipsoid(40,40,70,18,10,11);
    teste.CutBox(0,80,0,80,73,80);
    teste.PutBox(38,43, 38, 42, 0, 60);
    teste.PutBox(37,44, 37, 43, 0, 55);
    teste.PutBox(36,45, 36, 44, 0, 45);
    teste.PutBox(35,46, 35, 45, 0, 35);
    teste.PutBox(34,47, 34, 46, 0, 25);
    teste.PutBox(33,48, 33, 47, 0, 15);
    teste.PutBox(32,49, 32, 48, 0, 5);
    //Fim - Torre

    //Terreno
    teste.SetColor(0.845, 0.845, 0.845, 1.0);
    for(int y = 0; y <= ny; y+=10){
        for(int x = 0; x <= nx; x+=10){
            //cout << "teste" << endl;
            int z = (rand() % 5 + 1);
            teste.PutSphere(x, y, -z, 8);
        }
    }

    teste.PutBox(0, 80, 0, 80, 0, 1);


    //Olho
    teste.SetColor(1.0, 0.5, 0.0, 1.0); //Laranja
    teste.PutEllipsoid(40, 40, 70, 15, 5, 8);
    teste.PutEllipsoid(40, 40, 70, 18, 5, 3);
    teste.SetColor(1.0, 1.0, 0.0, 1.0); //Amarelo
    teste.PutEllipsoid(40, 40, 70, 12, 5, 7);
    teste.PutEllipsoid(40, 40, 70, 15, 5, 3);
    teste.SetColor(0.0, 0.0, 0.0, 1.0); //Preto
    teste.PutEllipsoid(40, 40, 70, 3, 5, 7);
    //Fim - Olho

    teste.WriteOFF();
    return 0;
}

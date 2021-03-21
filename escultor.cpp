#include "escultor.hpp"
#include <fstream>
#include <iomanip>
#include <cmath>

Escultor::Escultor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;
    // Aloca o espaço da matriz em um único vetor de voxel
    v = new voxel[(nx) * (ny) * (nz)];

    // Z = Altura, Y = Largura, X = Comprimento
    for (int z = 0; z < nz; z++){
        // Z inicia no primeiro plano e vai subindo
        for (int y = 0; y < ny; y++){
            // Y inicia na primeira "linha" (se visto de frente)
            for (int x = 0; x < nx; x++){
                // X acaba por ser cada voxel
                /* Essa configuração das multiplicações é assim pq ela que define que
                   Z são os planos, y as linha e x cada voxel*/
                v[z*(ny)*(nz) + y*(nz) + x].r = r;
                v[z*(ny)*(nz) + y*(nz) + x].g = g;
                v[z*(ny)*(nz) + y*(nz) + x].b = b;
                v[z*(ny)*(nz) + y*(nz) + x].a = a;
                v[z*(ny)*(nz) + y*(nz) + x].isOn = false;
            }
        }
    }
};

Escultor::~Escultor(){
    delete[] v;
};

void Escultor::SetColor(float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;

};

void Escultor::PutVoxel(int x0, int y0, int z0){
    v[z0*(ny)*(nz) + y0*(nz) + x0].r = r;
    v[z0*(ny)*(nz) + y0*(nz) + x0].g = g;
    v[z0*(ny)*(nz) + y0*(nz) + x0].b = b;
    v[z0*(ny)*(nz) + y0*(nz) + x0].a = a;
    v[z0*(ny)*(nz) + y0*(nz) + x0].isOn = true;

};

void Escultor::CutVoxel(int x0, int y0, int z0){
    v[z0*(ny)*(nz) + y0*(nz) + x0].isOn = false;
};


void Escultor::PutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int z = z0; z < z1; z++){
        for(int y = y0; y < y1; y++){
            for(int x = x0; x < x1; x++){
                 v[z*(ny)*(nz) + y*(nz) + x].r = r;
                 v[z*(ny)*(nz) + y*(nz) + x].g = g;
                 v[z*(ny)*(nz) + y*(nz) + x].b = b;
                 v[z*(ny)*(nz) + y*(nz) + x].isOn = true;
            }
        }
    }
};

void Escultor::CutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int z = z0; z < z1; z++){
        for(int y = y0; y < y1; y++){
            for(int x = x0; x < x1; x++){
                 v[z*(ny)*(nz) + y*(nz) + x].isOn = false;
            }
        }
    }
};

void Escultor::PutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if((float)pow((x-xcenter), 2) +
                   (float)pow((y-ycenter), 2) +
                   (float)pow((z-zcenter), 2) <= pow(radius, 2)){
                    v[z*(ny)*(nz) + y*(nz) + x].r = r;
                    v[z*(ny)*(nz) + y*(nz) + x].g = g;
                    v[z*(ny)*(nz) + y*(nz) + x].b = b;
                    v[z*(ny)*(nz) + y*(nz) + x].isOn = true;
                }
            }
        }
    }
};

void Escultor::CutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if((float)pow((x-xcenter), 2) +
                   (float)pow((y-ycenter), 2) +
                   (float)pow((z-zcenter), 2) <= pow(radius, 2)){
                    v[z*(ny)*(nz) + y*(nz) + x].isOn = false;
                }
            }
        }
    }
};

void Escultor::PutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if((float)(pow(x-xcenter, 2)/pow(rx, 2)) +
                   (float)(pow(y-ycenter, 2)/pow(ry, 2)) +
                   (float)(pow(z-zcenter, 2)/pow(rz, 2)) < 1){
                    v[z*(ny)*(nz) + y*(nz) + x].r = r;
                    v[z*(ny)*(nz) + y*(nz) + x].g = g;
                    v[z*(ny)*(nz) + y*(nz) + x].b = b;
                    v[z*(ny)*(nz) + y*(nz) + x].isOn = true;
                }
            }
        }
    }
};

void Escultor::CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if((float)(pow(x-xcenter, 2)/pow(rx, 2)) +
                   (float)(pow(y-ycenter, 2)/pow(ry, 2)) +
                   (float)(pow(z-zcenter, 2)/pow(rz, 2)) < 1){
                    v[z*(ny)*(nz) + y*(nz) + x].isOn = false;
                }
            }
        }
    }
};

void Escultor::WriteOFF(){
    ofstream arquivo;
    float lado = 0.5;
    int indicador;
    arquivo.open("C:\\Users\\Esdras Daniel\\Desktop\\tt.off"); //apaga o que tem no arquivo

    arquivo<<"OFF \n";
    int total_voxel = 0;
    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if(v[z*(ny)*(nz) + y*(nz) + x].isOn == true){
                    total_voxel++;
                }
            }
        }
    }

    arquivo << 8 * total_voxel << " " << 6 * total_voxel << " " << 0 << endl;

    // vertices
    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if(v[z*(ny)*(nz) + y*(nz) + x].isOn == true){

                    arquivo << x-lado << " " << y+lado << " " << z-lado << "\n"; // 0
                    arquivo << x-lado << " " << y-lado << " " << z-lado << "\n"; // 1
                    arquivo << x+lado << " " << y-lado << " " << z-lado << "\n"; // 2
                    arquivo << x+lado << " " << y+lado << " " << z-lado << "\n"; // 3
                    arquivo << x-lado << " " << y+lado << " " << z+lado << "\n"; // 4
                    arquivo << x-lado << " " << y-lado << " " << z+lado << "\n"; // 5
                    arquivo << x+lado << " " << y-lado << " " << z+lado << "\n"; // 6
                    arquivo << x+lado << " " << y+lado << " " << z+lado << "\n"; // 7
                }
            }
        }
    }
    total_voxel = 0;

    for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                if(v[z*(ny)*(nz) + y*(nz) + x].isOn == true){
                       indicador = total_voxel*8;
                       arquivo << fixed;

                       //Primeira face
                       arquivo << 4 << " " << indicador+0 << " " << indicador+3 << " " << indicador+2 << " " << indicador+1 << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].r << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].g << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].b << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].a << "\n";
                       //Segunda face
                       arquivo << 4 << " " << indicador+4 << " " << indicador+5 << " " << indicador+6 << " " << indicador+7 << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].r << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].g << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].b << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].a << "\n";
                       //Terceira face
                       arquivo << 4 << " " << indicador+0 << " " << indicador+1 << " " << indicador+5 << " " << indicador+4 << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].r << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].g << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].b << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].a << "\n";
                       //Quarta face
                       arquivo << 4 << " " << indicador+0 << " " << indicador+4 << " " << indicador+7 << " " << indicador+3 << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].r << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].g << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].b << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].a << "\n";
                       //Quinta face
                       arquivo << 4 << " " << indicador+3 << " " << indicador+7 << " " << indicador+6 << " " << indicador+2 << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].r << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].g << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].b << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].a << "\n";
                       //Sexta face
                       arquivo << 4 << " " << indicador+1 << " " << indicador+2 << " " << indicador+6 << " " << indicador+5 << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].r << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].g << setprecision(3) << " " << v[z*(ny)*(nz) + y*(nz) + x].b << " " << setprecision(3) << v[z*(ny)*(nz) + y*(nz) + x].a << "\n";

                       total_voxel++;
                }
            }
        }
    }

    arquivo.close();

};
/*for(int z = 0; z < nz; z++){
        for(int y = 0; y < ny; y++){
            for(int x = 0; x < nx; x++){
                cout << "--------------" << endl;
                cout << "R: " << v[z*(ny)*(nz) + y*(nz) + x].r << endl;
                cout << "G: " << v[z*(ny)*(nz) + y*(nz) + x].g << endl;
                cout << "B: " << v[z*(ny)*(nz) + y*(nz) + x].b << endl;
                cout << "A: " << v[z*(ny)*(nz) + y*(nz) + x].a << endl;
            }
        }
    }*/

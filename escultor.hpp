#ifndef ESCULTOR_HPP
#define ESCULTOR_HPP

#include <iostream>

using namespace std;

typedef struct {
    float r, g, b, a;
    bool isOn;
} voxel;

class Escultor{
private:
    voxel *v;
    float r, g, b, a;
    int nx, ny, nz;    //Dimensão do meu cubo
public:
    Escultor(int _nx, int _ny, int _nz);
    ~Escultor();
    void SetColor(float _r, float _g, float _b, float _a);
    void PutVoxel(int x0, int y0, int z0);
    void CutVoxel(int x0, int y0, int z0);
    void PutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void CutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void PutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void CutSphere(int xcenter, int ycenter, int zcenter, int radius);
    void PutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void CutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void WriteOFF();
};

#endif // ESCULTOR_HPP

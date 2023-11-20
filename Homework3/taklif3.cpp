#include <windows.h> // for XMVerifyCPUSupport
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

// Overload the  "<<" operators so that we can use cout to 
// output XMVECTOR and XMMATRIX objects.
ostream& XM_CALLCONV operator << (ostream& os, FXMVECTOR v)
{
    XMFLOAT4 dest;
    XMStoreFloat4(&dest, v);

    os << dest.x;
    return os;
}

ostream& XM_CALLCONV operator << (ostream& os, FXMMATRIX m)
{
    for (int i = 0; i < 4; ++i)
    {
        os <<"[" << round(XMVectorGetX(m.r[i])*100)/100 << "\t";
        os << round(XMVectorGetY(m.r[i])*100)/100<< "\t";
        os << round(XMVectorGetZ(m.r[i])*100)/100<< "\t";
        os << round(XMVectorGetW(m.r[i])*100)/100<<"]";
        os << endl;
        os << endl;
    }
    return os;
}

int main()
{
    //for (int i = 0; i < 16; i++) {
      //  float n;
       // cin >> n;
       // A[i] = n;
    //}
    // Check support for SSE2 (Pentium4, AMD K8, and above).
    if (!XMVerifyCPUSupport())
    {
        cout << "directx math not supported" << endl;
        return 0;
    }
    float a, b, c, d,e,f,g,h,i,j,k,l,m,n,o,p;
    for (int q = 1; q < 2; q++) {
        cin >> a;
        cin >> b;
        cin >> c;
        cin >> d;
        cin >> e;
        cin >> f;
        cin >> g;
        cin >> h;
        cin >> i;
        cin >> j;
        cin >> k;
        cin >> l;
        cin >> m;
        cin >> n;
        cin >> o;
        cin >> p;
    }
    
    XMMATRIX A(a, b, c, d,
        e, f, g, h,
        i, j, k, l,
        m, n, o, p);
    XMMATRIX B(1.0f,0.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        0.0f,0.0f,0.0f,1.0f);
    XMMATRIX O(p, -b, -c, -d,
        -e, k, -g, -h,
        -i, -j, f, -l,
        -m, -n, -o, a);
    XMMATRIX C = A * B;

    //XMMATRIX D = XMMatrixTranspose(A);
    XMMATRIX Q(a,e,i,m,b,f,j,n,c,g,k,o,d,h,l,p);
    XMMATRIX P = A + Q;
    XMMATRIX I = A - O;
    XMVECTOR det = XMMatrixDeterminant(A);

    float V=0.0f;

    V=(a*(f*(k*p-o*l)-g*(j*p-n*l)+h*(j*o-n*k)))-(b*(e*(k*p-o*l)-g*(i*p-m*l)+h*(i*o-m*k)))+(c*(e*(j*p-n*l)-f*(i*p-m*l)+h*(i*n-m*j)))-(d*(e*(j*o-k*n)-f*(i*o-m*k)+g*(i*n-m*j)));

    XMMATRIX E = XMMatrixInverse(&det, A);

    XMMATRIX F = A * E;

    cout << "A = " << endl << A << endl;
    cout << "B = " << endl << B << endl;
    cout << "C = A*B = " << endl << C << endl;
    cout << "D = transpose(A) = " << endl <<Q<<endl;
    cout << "P = plus(A+Q) = " << endl << P << endl;
    cout << "I = A-O = " << endl << I << endl;
    cout << "det = determinant(A) = " <<V<<endl;
    cout << "E = inverse(A) = " << endl << E << endl;
    cout << "F = A*E = " << endl << F << endl;

    return 0;
}
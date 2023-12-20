#pragma once

#include "d3dUtility.h"
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// 
IDirect3DDevice9* Device = 0;

// 
const int Width = 1080;
const int Height = 720;

// human settings
ID3DXMesh* Objects[17];
D3DMATERIAL9 Materials[17];
D3DXMATRIX Worlds[17];
ID3DXMesh* Wall[5];

//
static float plane_x = 20.0f;
static float plane_y = -7.4f;
static float plane_z = 20.0f;
// light's settings 
static bool lightEnable = true;
// font settings
ID3DXMesh* font_mesh = 0;
D3DXMATRIX result;

// images
IDirect3DTexture9* image_wall_tex = 0;
IDirect3DTexture9* wall_tex = 0;

// mirror
D3DMATERIAL9 mirror_material = d3d::WHITE_MTRL;
IDirect3DTexture9* mirror_texture = 0;

// vertex buffer
IDirect3DVertexBuffer9* VB = 0;
//
struct Vertex {
    //Vertex() {}

    Vertex(float x, float y, float z,
        float nx, float ny, float nz,
        float u, float v) {
        _x = x;
        _y = y;
        _z = z;
        _nx = nx;
        _ny = ny;
        _nz = nz;
        _u = u;
        _v = v;
    }

    float _x, _y, _z;
    float _nx, _ny, _nz;
    float _u, _v;

    static const DWORD FVF;
};

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

void CreateObjects() {
    // create the object !
    D3DXCreateBox(Device, 5.1f, 1.0f, 1.9f, &Objects[0], 0);//body
    D3DXCreateTorus(Device, 0.1f, 1.81f, 10,10, &Objects[1], 0);//head
    D3DXCreateSphere(Device, 0.25f, 20, 20, &Objects[2], 0);//eye 1
    D3DXCreateSphere(Device, 0.25f, 20, 20, &Objects[3], 0);//eye 2
    D3DXCreateCylinder(Device, 0.0f, 0.3f, 1.5f, 20, 20, &Objects[4], 0);//nose
    D3DXCreateCylinder(Device, 0.8f, 0.8f, 0.85f, 20, 20, &Objects[5], 0);//hat
    D3DXCreateBox(Device, 1.0f, 0.1f, 0.7f, &Objects[6], 0);//mouth
    D3DXCreateBox(Device, 5.0f, 3.4f, 1.8f, &Objects[7], 0);//body
    D3DXCreateBox(Device, 3.0f, 0.2f, 0.5f, &Objects[8], 0);//hand1
    D3DXCreateBox(Device, 3.0f, 0.2f, 0.5f, &Objects[9], 0);//hand2
    D3DXCreateBox(Device, 0.2f, 4.0f, 0.5f, &Objects[10], 0);//leg1
    D3DXCreateBox(Device, 0.2f, 4.0f, 0.5f, &Objects[11], 0);//leg2
    
    // Build world matrices - position the objects in world space.
    D3DXMatrixTranslation(&Worlds[0], 0.0f, -4.0f, 0.0f);//body
    D3DXMatrixTranslation(&Worlds[1], 0.0f, -2.65f, -0.91f);//head
    D3DXMatrixTranslation(&Worlds[2], 0.4f, -1.5f, -0.9f); //eye1
    D3DXMatrixTranslation(&Worlds[3], -0.4f, -1.5f, -0.9f);//eye2
    D3DXMatrixTranslation(&Worlds[4], 0.0f, -1.9f, -0.9f);//nose
    D3DXMatrixTranslation(&Worlds[5], 0.0f, 1.05f, 0.0f);//hat
    D3DXMatrixTranslation(&Worlds[6], 0.0f, -2.1f, -0.9f);//mouth
    D3DXMatrixTranslation(&Worlds[7], 0.0f, -2.7f, 0.0f);//body
    D3DXMatrixTranslation(&Worlds[8], -3.5f, -2.0f, 0.0f);//hand1
    D3DXMatrixTranslation(&Worlds[9], 3.5f, -2.0f, 0.0f);//hand1
    D3DXMatrixTranslation(&Worlds[10], -1.5f, -5.0f, 0.0f);//leg1
    D3DXMatrixTranslation(&Worlds[11], 1.5f, -5.0f, 0.0f);//leg2

    // Setup the object's materials.
    Materials[0] = d3d::BLACK_MTRL;//body
    Materials[1] = d3d::WHITE_MTRL;//head
    Materials[2] = d3d::BLACK_MTRL;//eye1
    Materials[3] = d3d::BLACK_MTRL;//eye2
    Materials[4] = d3d::YELLOW_MTRL;//nose
    Materials[5] = d3d::RED_MTRL;//hat
    Materials[6] = d3d::WHITE_MTRL;//mouth
    Materials[7] = d3d::GREEN_MTRL;//body
    Materials[8] = d3d::GREEN_MTRL;//hand1
    Materials[9] = d3d::GREEN_MTRL;//hand2
    Materials[10] = d3d::BLUE_MTRL;//leg1
    Materials[12] = d3d::WHITE_MTRL;//leg2
    Materials[13] = d3d::BLUE_MTRL;
    Materials[14] = d3d::BLUE_MTRL;
    Materials[15] = d3d::GREEN_MTRL;
    Materials[16] = d3d::RED_MTRL;

    //Worlds[9] = PositionFinder(3, 0, new float[] {-2.85f, -2.5f, 0.0f}, 3.14 / 2, 0, "x", "y");//hand1
    //Worlds[10] = PositionFinder(3, 0, new float[] {+2.85f, -2.5f, 0.0f}, 3.14 / 2, 0, "x", "y");//hand2
    //Worlds[11] = PositionFinder(3, 0, new float[] {-1.2f, -5.8f, 0.0f}, 3.14 / 2, 0, "x", "x");//leg
    //Worlds[12] = PositionFinder(3, 0, new float[] {1.2f, -5.8f, 0.0f}, 3.14 / 2, 0, "x", "x");//leg
}
void CreatWall(){
    D3DXCreateBox(Device, 0.1f, 100.0f, 100.0f, &Wall[0], 0);//left
    D3DXCreateBox(Device, 0.1f, 100.0f, 100.0f, &Wall[1], 0);//right
    D3DXCreateBox(Device, 100.0f, 0.1f, 100.0f, &Wall[2], 0);//up
    D3DXCreateBox(Device, 100.0f, 0.1f, 100.0f, &Wall[3], 0);//down
    D3DXCreateBox(Device, 100.0f, 100.0f, 0.1f, &Wall[4], 0);//back


    //
    D3DXMatrixTranslation(&Worlds[12], -15.0f, 0.0f, 0.0f);//left
    D3DXMatrixTranslation(&Worlds[13], 15.0f, 0.0f, 0.0f);//right
    D3DXMatrixTranslation(&Worlds[14], 0.0f, 15.0f, 0.0f);//up
    D3DXMatrixTranslation(&Worlds[15], 0.0f, -9.0f, 0.0f);//down
    D3DXMatrixTranslation(&Worlds[16], 0.0f, 0.0f, 15.0f);//back
    //

}
// function for setting light
void Light() {
    // Set up a directional light.
    D3DXVECTOR3 dir(2.0f, 2.0f, 2.0f);
    D3DXCOLOR c;

    // change light color
    c = d3d::WHITE;

    D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

    // Set and Enable the light.
    Device->SetLight(0, &dirLight);
    Device->LightEnable(0, lightEnable);

    // Set lighting related render states.
    Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
    Device->SetRenderState(D3DRS_SPECULARENABLE, false);

    // Set the projection matrix.
    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(
        &proj,
        D3DX_PI * 0.25f, // 45 - degree
        (float)Width / (float)Height,
        1.0f,
        1000.0f);

    Device->SetTransform(D3DTS_PROJECTION, &proj);
}

void Cleanup() {
    d3d::Release<IDirect3DVertexBuffer9*>(VB);

    for (int i = 0; i < 12; i++)
        d3d::Release<ID3DXMesh*>(Objects[i]);
    for (int j = 0; j < 5; j++)
        d3d::Release<ID3DXMesh*>(Wall[j]);
}
// function to render the shadow
void RenderShadow() {
    Device->SetRenderState(D3DRS_STENCILENABLE, true);
    Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
    Device->SetRenderState(D3DRS_STENCILREF, 0x0);
    Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
    Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
    Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR); // increment to 1

    // position shadow
    D3DXVECTOR4 lightDirection(2.0f, 2.0f, 2.0f, 0.0f);
    D3DXPLANE groundPlane(0.0f, 1.0f, 0.0f, 0.0f);

    D3DXMATRIX W, S;
    D3DXMATRIX tra = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            plane_y, plane_y, plane_y, 1.0f
    };

    D3DXMatrixShadow(
        &S,
        &lightDirection,
        &groundPlane);

    S *= tra;

    int object_index;

    // alpha blend the shadow
    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    D3DMATERIAL9 mtrl = d3d::InitMtrl(d3d::BLACK, d3d::BLACK, d3d::BLACK, d3d::BLACK, 0.0f);
    mtrl.Diffuse.a = 0.5f; // 50% transparency.

    // Disable depth buffer so that z-fighting doesn't occur when we render the shadow on top of the floor.
    Device->SetRenderState(D3DRS_ZENABLE, false);

    for (int i = 0; i < 12; i++) {
        W = Worlds[i] * S;
        Device->SetTransform(D3DTS_WORLD, &W);
        Device->SetMaterial(&mtrl);
        Objects[i]->DrawSubset(0);
    }

    Device->SetRenderState(D3DRS_ZENABLE, true);
    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
    Device->SetRenderState(D3DRS_STENCILENABLE, false);
}

// function to render the mirror
void RenderMirror() {
    Device->SetRenderState(D3DRS_STENCILENABLE, true);
    Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
    Device->SetRenderState(D3DRS_STENCILREF, 0x1);
    Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
    Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
    Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

    // disable writes to the depth and back buffers
    Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
    Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

    // draw the mirror to the stencil buffer
    Device->SetStreamSource(0, VB, 0, sizeof(Vertex));
    Device->SetFVF(Vertex::FVF);
    Device->SetMaterial(&mirror_material);
    Device->SetTexture(0, mirror_texture);

    D3DXMATRIX I;
    D3DXMatrixIdentity(&I);
    Device->SetTransform(D3DTS_WORLD, &I);
    Device->DrawPrimitive(D3DPT_TRIANGLELIST, 30, 2);

    // re-enable depth writes
    Device->SetRenderState(D3DRS_ZWRITEENABLE, true);

    // only draw reflected to the pixels where the mirror was drawn to.
    Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
    Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

    // position reflection
    D3DXMATRIX W;
    D3DXMATRIX ref = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, -1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    };

    D3DXMATRIX tra = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, plane_z , 1.0f
    };

    ref *= tra;

    // clear depth buffer and blend the reflected teapot with the mirror
    Device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
    Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
    Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

    // find the exact reflection in mirror
    W = Worlds[0] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[0]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[0]->DrawSubset(0);

    W = Worlds[1] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[1]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[1]->DrawSubset(0);

    W = Worlds[5] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[5]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[5]->DrawSubset(0);

    W = Worlds[6] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[6]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[6]->DrawSubset(0);

    W = Worlds[8] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[8]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[8]->DrawSubset(0);

    W = Worlds[9] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[9]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[9]->DrawSubset(0);

    W = Worlds[10] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[10]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[10]->DrawSubset(0);

    W = Worlds[11] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[11]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[11]->DrawSubset(0);

    W = Worlds[12] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[12]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[12]->DrawSubset(0);

    W = Worlds[13] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[13]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[13]->DrawSubset(0);

    W = Worlds[14] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[14]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[14]->DrawSubset(0);

    W = Worlds[15] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[15]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[15]->DrawSubset(0);

    W = Worlds[16] * ref;
    Device->SetTransform(D3DTS_WORLD, &W);
    Device->SetMaterial(&Materials[16]);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    Objects[16]->DrawSubset(0);
    // Restore render states.
    Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
    Device->SetRenderState(D3DRS_STENCILENABLE, false);
    Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
// Display
bool Display(float timeDelta) {
    // variables for keeping the position of the camera
    static float pos_x = 0.0f;
    static float pos_y = 0.0f;
    static float pos_z = -20.0f;

    // variables for keeping the position of the target
    static float target_x = 0.0f;
    static float target_y = -4.0f;
    static float target_z = 0.0f;
    if (Device) {
        // setting camera
        D3DXVECTOR3 position(pos_x, pos_y, pos_z);
        D3DXVECTOR3 target(target_x, target_y, target_z);
        D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
        D3DXMATRIX V;
        D3DXMatrixLookAtLH(&V, &position, &target, &up);

        Device->SetTransform(D3DTS_VIEW, &V);

        // Draw the scene:
        Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0xffffffff, 1.0f, 0L);
        Device->BeginScene();
        //RenderScene();

        // set material and world matrix for ith object, then render the ith object.
        for (int i = 0; i < 12; i++) {
            Device->SetTransform(D3DTS_WORLD, &Worlds[i]);
            Device->SetMaterial(&Materials[i]);
            Objects[i]->DrawSubset(0);
        }
        for (int j = 0; j < 5; j++) {
            Device->SetTransform(D3DTS_WORLD, &Worlds[12+j]);
            Device->SetMaterial(&Materials[12+j]);
            Wall[j]->DrawSubset(0);
        }

        // shadow
        RenderShadow();

        // mirror
        //RenderMirror();

        // draw font and name, set material and world matrix
        Device->SetTransform(D3DTS_WORLD, &result);
        Device->SetMaterial(&d3d::RED_MTRL);
        //font_mesh->DrawSubset(0);

        Device->EndScene();
        Device->Present(0, 0, 0, 0);
    }
    return true;
}
bool Setup() {
    //creating objects
    CreateObjects();
    CreatWall();
    // create floor and wall
    //CreateHouse();

    // create font and name
    //createName();

    // set and enable light
    Light();

    // load the image to texture
    D3DXCreateTextureFromFileA(Device, ".\\image.png", &image_wall_tex);
    D3DXCreateTextureFromFileA(Device, ".\\image.png", &wall_tex);
    D3DXCreateTextureFromFileA(Device, ".\\ice.bmp", &mirror_texture);

    return true;
}
// WndProc
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        ::PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            ::DestroyWindow(hwnd);
        break;
    }

    return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

// WinMain
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {

    if (!d3d::InitD3D(hinstance, Width, Height, true, D3DDEVTYPE_HAL, &Device)) {
        ::MessageBox(0, (LPCWSTR)"InitD3D() - FAILED", 0, 0);
        return 0;
    }

    if (!Setup()) {
        ::MessageBox(0, (LPCWSTR)"Setup() - FAILED", 0, 0);
        return 0;
    }

    d3d::EnterMsgLoop(Display);

    Cleanup();
    Device->Release();

    return 0;
}






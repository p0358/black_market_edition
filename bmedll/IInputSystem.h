#pragma once

class IInputSystem
{
public:
    struct VTable
    {
        void* unknown[1];
    };

    VTable* m_vtable;
    unsigned char unknown[0x16A8];
    int32_t m_analogDeltaX;
    int32_t m_analogDeltaY;
};
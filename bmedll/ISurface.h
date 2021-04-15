#pragma once

class ISurface
{
public:
    struct VTable
    {
        void* unknown1[61];
        void(*SetCursor) (ISurface* surface, unsigned int cursor);
        bool(*IsCursorVisible) (ISurface* surface);
        void* unknown2[11];
        void(*UnlockCursor) (ISurface* surface);
        void(*LockCursor) (ISurface* surface);
    };

    VTable* m_vtable;
};
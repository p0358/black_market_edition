#pragma once
#include "pch.h"

class FileStreamWrapper
{
private:
    FILE* m_file;

public:
    FileStreamWrapper(const char* filename, const char* mode, FILE* oldStrea);
    ~FileStreamWrapper();
};

class WindowsConsole
{
public:
    WindowsConsole();
    ~WindowsConsole();
};

class Console
{
private:
    WindowsConsole m_winConsole;
    FileStreamWrapper m_conOut;
    FileStreamWrapper m_conIn;

public:
    Console();
    ~Console();
};
/*
@Author:  nonrk
@Date:    2016/06/10
@File:    interface.cpp
@Use:     dll export interface
@Ver:     0.100
*/
#include "stdafx.h"
#include "kernel.h"
#include "Interface.h"

// Provides a base class pointer to a derived object by exporting the function form
extern "C" __declspec(dllexport) Interface* Export(void)
{
	return (Interface*)new Kernel();
}
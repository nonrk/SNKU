/*
@Author:  nonrk
@Date:    2016/06/09
@File:    kernel.h
@Use:     dll export inheritance interface class
@Ver:     0.100
*/
#pragma once
#include "Interface.h"
#include "stdafx.h"
class Kernel :public Interface
{
public:
	Kernel();
	virtual ~Kernel();
	virtual const char* NeuronID();//test fun
private:
	//Add your variables here
};
/*
@Author:  nonrk
@Date:    2016/06/09
@File:    kernel.cpp
@Use:     dll export inheritance interface class
@Ver:     0.100
*/
#include"stdafx.h"
#include"kernel.h"
#include "NeuronBase.h"

Kernel::Kernel()
{
	return;
}

Kernel::~Kernel()
{
	return;
}
/*test fun*/
const char* Kernel::NeuronID()
{
	NeuronBase nb;
	return nb.activeNeuron().c_str();
}

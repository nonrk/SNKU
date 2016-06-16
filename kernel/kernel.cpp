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
const char *Kernel::NeuronID()
{
	char* data;
	vector<int> rep;
	
	NeuronBase nb;
	rep=nb.activeNeuron();
	for (int i=0;i<rep.size();i++)
	{
		char temp[11];
		itoa(rep[i], temp, 10);
		strcpy(data, temp);
		delete[] temp;
	}
	return data;
}

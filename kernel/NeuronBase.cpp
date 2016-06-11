/*
@Author:  nonrk
@Date:    2016/06/11
@File:    NeuronBase.cpp
@Use:     NeuronBase class
@Ver:     0.100
*/
#include "stdafx.h"
#include "NeuronBase.h"


NeuronBase::NeuronBase()
{
}


NeuronBase::~NeuronBase()
{
}
const char *NeuronBase::ActiveNeuron()
{
	int n_int = 2;
	const char *R;
	char int2char[22];
	memset(int2char, '\0', sizeof(int2char));
	_itoa_s(n_int, int2char, 10);
	NeuronData N;
	N.Init(int2char);
	R=N.n_Id;
	return N.n_Id;
}
/*
@Author:  nonrk
@Date:    2016/06/11
@File:    NeuronBase.h
@Use:     NeuronBase class
@Ver:     0.102
*/
#pragma once
#include "stdafx.h"
#include "md5.h"
using namespace std;
class NeuronBase
{
public:
	NeuronBase();
	~NeuronBase();

public:
	vector<int> activeNeuron();//test function
	vector<int> createNeuron();
};


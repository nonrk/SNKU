/*
@Author:  nonrk
@Date:    2016/06/11
@File:    NeuronBase.h
@Use:     NeuronBase class
@Ver:     0.100
*/
#pragma once
#include <stdlib.h>
#include "stdio.h"
#include "md5.h"
#define M 2000//定义神经元最大输入量
#define OFFSET 1
class NeuronBase
{
public:
	struct NeuronData{
		const char  *n_Id;//神经元网络ID
		int         x_input;//初始接入量
		char        *x_outputId;//初始输出入神经元ID
		double      *w_input;//输入权值
		double      a_output;//输出
		void Init(const char *id)
		{
			x_input = 1;
			CMd5 md5;
			n_Id       = md5.md5(id);
			x_outputId = new char[x_input];
			w_input    = new double[x_input];
			a_output   = 0;
		}
		~NeuronData() {//释放
			delete[]x_outputId;
			delete[]w_input;
		}
		};
	NeuronBase();
	~NeuronBase();
public:
	const char *ActiveNeuron();
};


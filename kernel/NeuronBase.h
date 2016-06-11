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
#define M 2000//������Ԫ���������
#define OFFSET 1
class NeuronBase
{
public:
	struct NeuronData{
		const char  *n_Id;//��Ԫ����ID
		int         x_input;//��ʼ������
		char        *x_outputId;//��ʼ�������ԪID
		double      *w_input;//����Ȩֵ
		double      a_output;//���
		void Init(const char *id)
		{
			x_input = 1;
			CMd5 md5;
			n_Id       = md5.md5(id);
			x_outputId = new char[x_input];
			w_input    = new double[x_input];
			a_output   = 0;
		}
		~NeuronData() {//�ͷ�
			delete[]x_outputId;
			delete[]w_input;
		}
		};
	NeuronBase();
	~NeuronBase();
public:
	const char *ActiveNeuron();
};


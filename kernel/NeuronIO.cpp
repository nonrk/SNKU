#include "stdafx.h"
#include "NeuronIO.h"
#include "NeuronBase.h"


NeuronIO::NeuronIO()
{
}
NeuronIO::~NeuronIO()
{
}
double NeuronIO::neuronOutCount(double *weightData,int weightNum)
{
	double W=0.0;
	for (int i=0;i<weightNum;i++)
	{
		W+=weightData[i];
	}
	return (1 / (1 + exp(W)));//·µ»ØÊä³öÖµ
}
void NeuronIO::contentNeuron()
{

}
void NeuronIO::listenPort(char *nId)
{

}
void NeuronIO::changeNeuronWeight()
{

}
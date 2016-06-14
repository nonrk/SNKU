#pragma once
class NeuronIO
{
public:
	NeuronIO();
	~NeuronIO();
public:
	double     neuronOutCount(double *weightData,int weightNum);
	void       contentNeuron();//content
	void       listenPort(char *nId);//listen other neuron link
	void       changeNeuronWeight();//change neuron weight

};

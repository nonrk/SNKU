/*
@Author:  nonrk
@Date:    2016/06/11
@File:    NeuronBase.cpp
@Use:     NeuronBase class
@Ver:     0.105
*/
#include "stdafx.h"
#include "NeuronBase.h"

#define M         2000//def neuron max number
#define OFFSET    1
#define TDN(name) TDN##name
#define TDH(name) TDH##name
#define UM_MSG1   WM_USER+1
#define UM_MSG2   WM_USER+2 
NeuronBase::NeuronBase()
{
}


NeuronBase::~NeuronBase()
{
}
string NeuronBase::activeNeuron()
{
	//return createNeuron(1,1);
}
int getvecIndex(vector<DWORD>vec, DWORD val)//get vector index
{
	
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		DWORD s = vec[i];
		if (s == val)
		{
			return i;
			break;
		}
	}
	return -1;
}
string NeuronBase::createNeuron(int startNum,int ioNum)
{
	//int n_int = startNum;
	//char int2char[22];
	//memset(int2char, '\0', sizeof(int2char));
	//_itoa_s(n_int, int2char, 10);
	//NeuronData N;
	//N.Init(int2char,0.6, ioNum);
	//if (N.n_Id !="")
	//	return N.n_Id;
	//else

		return "0";
}
//def neuron struct
struct NeuronData {
	DWORD           n_Id;    //neuron thread ID
	string          n_md5Id; //MD5 encode neuron ID
	double          n_time;  //neuron Information integration unit:ms
	double          w_val;   //neuron threshold (-1<w_val<1)
	vector<DWORD>   n_exId;  //out neuron ID
	vector<DWORD>   n_imId;  //input neuron ID
	vector<double>  w_imVal; //input weight
	double          n_exVal; //neuron out val (-1<n_exval<1) 
	int             n_Max;   //neuron max link val
	//Init function
	void Init(double th, int ioNum)
	{
		n_time  = 1;
		n_exVal = 0;
		w_val   = th;
		n_Max   = ioNum;
		n_exId.reserve(ioNum);
		n_imId.reserve(ioNum);
		w_imVal.reserve(ioNum);
	}
	~NeuronData() {

		n_exId.clear();
		n_imId.clear();
		w_imVal.clear();
		vector<DWORD>(n_exId).swap(n_exId);
		vector<DWORD>(n_imId).swap(n_imId);
		vector<double>(w_imVal).swap(w_imVal);
	}
	//insert IO neuron ID
	void insertId(int ex,DWORD eId)
	{
		switch (ex)
		{
		case 0:
			n_imId.push_back(eId);
			break;
		case 1:
			n_exId.push_back(eId);
			break;
		case 9:
			w_imVal.push_back(eId);
			break;
		default:
			break;
		}
	}
	//update neuron weight
	void updateWeight(vector<DWORD>vec,DWORD nId, double nw)
	{
		int vp=getvecIndex(vec, n_Id);
		vec[vp] = nw;
	}

};
//def input neuron msg struct
typedef struct __INPUT_NEURON_DATA
{
	int nMaxNum;
	DWORD tId;
}IND;

HANDLE g_hMutex = NULL;
//
DWORD WINAPI neuronThread(LPVOID tID)
{
	DWORD dwId = *(DWORD *)tID;
	//Init neuron
	NeuronData N;
	N.n_Id = dwId;
	N.Init(0.6, 3);
	//CMd5 md5;
	//N.n_md5Id = md5.md5(dwId);
	DWORD i = 0;
	TCHAR *p;
	char strTmp[100];
	
	//test neuron send msg
	while (TRUE)
	{
		Sleep(1000);
		p = new TCHAR[10];
		//sprintf(strTmp, "Neuron Send Msg %d %x Neuron ID:%u", i++, p, dwId);
		PostThreadMessage(dwId, UM_MSG1, (WPARAM)strTmp, (LPARAM)p);
		//delete []p;  
	}
	return 0L;
}
void NeuronBase::createThread(int td_num)
{
	//create mutex
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	//
	DWORD tId = GetCurrentThreadId();
	//create neuron thread
	for (int i = 0; i < td_num; i++)
	{
		IND TDN(i);
		TDN(i).tId = tId;

		HANDLE TDH(i) = CreateThread(NULL, 0, &neuronThread, &TDN(i), 0, NULL);
		CloseHandle(TDH(i));
		WaitForSingleObject(g_hMutex, INFINITE);
		Sleep(100);
		//release
		ReleaseMutex(g_hMutex);
	}
	//test receive msg
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		switch (msg.message)
		{
		case UM_MSG1:
		case UM_MSG2:
			//printf("msg:0x%x \t%x \t%s0\n", msg.message, msg.lParam, msg.wParam); 
			//delete[](TCHAR *)msg.lParam;
			break;
		default:
			printf("Unknown msg:0x%x\n", msg.message);
			break;
		}
		Sleep(1);
	}
}
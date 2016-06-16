/*
@Author:  nonrk
@Date:    2016/06/11
@File:    NeuronBase.cpp
@Use:     NeuronBase class
@Ver:     0.106
*/
#include "stdafx.h"
#include "NeuronBase.h"
#include<process.h>
#define M         2000//def neuron max number
#define UM_MSG   WM_USER+1

HANDLE hStartEvent;
NeuronBase::NeuronBase(){}
NeuronBase::~NeuronBase(){}
vector<int>  NeuronBase::activeNeuron()
{
	return createNeuron();
}
//def neuron struct
struct NeuronData {
	DWORD           n_Id;    //neuron thread ID
	//string          n_md5Id; //MD5 encode neuron ID
	double          n_time;  //neuron Information integration unit:ms
	double          w_val;   //neuron threshold (-1<w_val<1)
	vector<DWORD>   n_exId;  //out neuron ID
	vector<DWORD>   n_imId;  //input neuron ID
	vector<double>  w_imVal; //input weight
	int             n_Max;   //neuron max link val
	//Init function
	void Init(double th, int ioNum)
	{
		n_time  = 1;
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

};
HANDLE            g_tEvent;   //synchronization
CRITICAL_SECTION  g_tCritial;
//get vector index in val
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
//rand weight or threshold -1 to 1
double getRand()
{
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);
	srand(sys_time.wMilliseconds);
	int r = rand() % 2000;
	double rv = r / 1000.0 - 1;
	return rv;
}
//is new link?
int isNewLink(DWORD nId,vector<DWORD>vec)
{
	vector <DWORD>::iterator iter;
	iter = find(vec.begin(), vec.end(), nId);
	int result = iter ==vec.end() ? 0 : 1;
	return result;
}
//calculation out val
double outSum(vector<double>vecw, vector<double>vecim)
{
	int tp = vecw.size();
	double s = 0.0;
	for (int i=0;i<tp;i++)
	{
		s += vecw[i] * vecim[i];
	}
	return s;
}
//send between of neuron msg
bool sendMsg(DWORD myid,double exval,vector<DWORD>veei)
{
	for (unsigned int i=0;i<veei.size();i++)
	{
		if (!PostThreadMessage(veei[i], UM_MSG, (WPARAM)exval, (LPARAM)myid))
		{
			printf("post %d message failed,errno:%d\n",i, ::GetLastError());
		}
	}
	
	return true;
}
//update weight
void updateWeight(DWORD imId,vector<DWORD>veci,vector<double>vecw) 
{
	int nowId = getvecIndex(veci, imId);
	double wcv = 0.001;
	for (unsigned int i=0;i<veci.size();i++)
	{
		if (veci[i]==imId)
		{
			vecw[i] = vecw[i] + wcv;
		}
		else
		{
			vecw[i] = vecw[i] + wcv;
		}
		

	}
}
//neuron 
unsigned __stdcall neuronThread(void *Data)
{
	//DWORD   dwId   = *(DWORD *)Data;
	vector <double> t_weight;
	vector <double> t_outval;
	DWORD   nId    = GetCurrentThreadId();
	int     otNum  = 0;
	//Init neuron
	NeuronData N;
	N.n_Id         = nId;
	N.Init(getRand(), 3);
	//CMd5 md5;
	//N.n_md5Id = md5.md5(dwId);
	//test neuron send msg
	DWORD tId = GetCurrentThreadId();

	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
		if (!SetEvent(hStartEvent)) //set thread start event 
		{
			printf("set start event failed,err:%d\n", ::GetLastError());
			return 1;
		}

	while (true)
	{
		if (otNum == 10)
		{
			double exout = 0.0;
			int    ps    = 0;
			exout = 2.0 / (1.0 + exp(-outSum(t_weight, t_outval))) - 1.0;
			sendMsg(N.n_Id,exout,N.n_exId);
			t_weight.clear();
			vector<double>(t_weight).swap(t_weight);
			t_outval.clear();
			vector<double>(t_outval).swap(t_outval);
			otNum = 0;
		}
		if (GetMessage(&msg, 0, 0, 0)) //get msg from message queue
		{
			switch (msg.message)
			{
			case UM_MSG:
				if (isNewLink(msg.wParam,N.n_imId)==1)
				{
					N.n_imId.push_back(msg.lParam);
					N.w_imVal.push_back(getRand());
				}
				t_weight.push_back(N.w_imVal[getvecIndex(N.n_imId, msg.wParam)]);
				t_outval.push_back(msg.lParam);
				updateWeight(msg.lParam, N.n_imId, N.w_imVal);
				otNum++;
				break;
			default:
				break;
			}
		}
		::Sleep(10);
	}
	return 0;
}
//create neuron
vector<int> NeuronBase::createNeuron()
{
	unsigned tId[M];//test data
	vector<int> data;

	g_tEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	InitializeCriticalSection(&g_tCritial);

	HANDLE  handle[M];
	int i = 0;
	while (i < M)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, neuronThread, &i, 0, &tId[i]);
		WaitForSingleObject(g_tEvent, INFINITE); 
		data.push_back(tId[i]);
	}
	WaitForMultipleObjects(M, handle, TRUE, INFINITE);
	CloseHandle(g_tEvent);
	DeleteCriticalSection(&g_tCritial);
	return data;

}
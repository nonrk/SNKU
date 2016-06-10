/*
@Author:  nonrk
@Date:    2016/06/09
@File:    kernel.cpp
@Use:     dll export inheritance interface class
@Ver:     0.100
*/
#include"stdafx.h"
#include"kernel.h"

Kernel::Kernel()
{
	return;
}

Kernel::~Kernel()
{
	return;
}
/*test fun*/
int Kernel::ShowMsg()
{
	int a = 10;
	int b = 33;
	int c = a + b;
	return c;
}

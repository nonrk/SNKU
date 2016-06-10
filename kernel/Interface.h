/*
@Author:  nonrk
@Date:    2016/06/10
@File:    interface.h
@Use:     dll export interface
@Ver:     0.100
*/
#pragma once
class Interface
{
public:
	/*
	Declares a member function to be a pure virtual function.
	Add you function to here.
	*/
	virtual int ShowMsg() = 0; // test fun
	virtual ~Interface() {};// A virtual destructor of the abstract class
};
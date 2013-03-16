//Uncopyable.h - a simple abstract class that disallows any inheriting classes to be copied via a 
//copy constructor or an assignment operator
//last modified: 01/11/2013
#pragma once

class Uncopyable{
public:
	Uncopyable(){};
private:
	Uncopyable(Uncopyable& rhs);
	Uncopyable& operator=(Uncopyable& rhs);};
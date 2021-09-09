#include "stream_box.h"


bool_box::bool_box()
{
	this->command = false;
	this->boarding = false;
	this->leave = false;
	this->enter = false;
}

void bool_box::set_command(bool val)
{
	this->command = val;
}

void bool_box::set_boarding(bool val)
{
	this->boarding = val;
}

void bool_box::set_leave(bool val)
{
	this->leave = val;
}

void bool_box::set_enter(bool val)
{
	this->enter = val;
}

bool bool_box::get_boarding()
{
	return this->boarding;
}

bool bool_box::get_leave ()
{
	return this->leave;
}

bool bool_box::get_enter()
{
	return this->enter;
}

bool bool_box::get_command()
{
	return this->command;
}

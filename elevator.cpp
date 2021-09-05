#include "elevator.h"
#include <string>

elevator::elevator(int capacity,int count_of_floors)
{
	this->end_of_emulation = false;
	this->goUp = false;
	this->goDown = false;
	this->capacity = capacity;
	this->people_in_elevator = 0;
	this->count_of_floors = count_of_floors;
	this->current_floor = 1;
	this->target_floors = new std::vector<int>(0);
	this->floor_calls = new std::vector<int>(0);
}

void elevator::set_capacity(int kol)
{
	this->capacity = kol;
}

void elevator::set_count_of_floors(int kol)
{
	this->count_of_floors = kol;
}

void elevator::set_end_of_emulation(bool val)
{
	this->end_of_emulation = val;
}

void elevator::set_people_in_elevator(int kol)
{
	this->people_in_elevator = kol;
}

void elevator::set_goUp(bool flag)
{
	this->goUp = flag;
}

void elevator::set_goDown(bool flag)
{
	this->goDown = flag;
}

void elevator::set_current_floor(int number)
{
	this->current_floor = number;
}

void elevator::add_target_floor(int number)
{
	this->target_floors->push_back(number);
}

void elevator::remove_target_floor(int position)
{
	if (position == -1)
	{
		this->target_floors->resize(0);
	}
	else
	{
		this->target_floors->erase(this->target_floors->begin() + position);
	}
}

void elevator::add_floor_calls(int number)
{
	this->floor_calls->push_back(number);
}

void elevator::remove_floor_calls(int position)
{
	this->floor_calls->erase(this->floor_calls->begin() + position);
}

int elevator::get_count_of_floors()
{
	return this->count_of_floors;
}

int elevator::get_capacity()
{
	return this->capacity;
}

std::string elevator::get_message()
{
	std::string s1 = std::to_string(this->current_floor);
	std::string s2 = std::to_string(this->people_in_elevator);
	if (this->goUp)
	{
		return "Cabin on floor : " + s1 + ". People in elevator : " + s2 + ". Going up. <Press any key to enter new command>\n";
	}
	else if (this->goUp)
	{
		return "Cabin on floor : " + s1 + ". People in elevator : " + s2 + ". Going down. <Press any key to enter new command>\n";
	}
	else if ((this->target_floors->size() !=0) or (this->floor_calls->size() != 0))
	{
		return "Cabin on floor : " + s1 + ". Stopped. People in elevator : " + s2 + ". Capacity : " + std::to_string(this->capacity) + ". Doors opened.\n";
	}
	else
	{
		return "Cabin on floor : " + s1 + ". Stopped. People in elevator : " + s2 + ". Capacity : " + std::to_string(this->capacity) + ". Doors closed.\n";
	}
}

bool elevator::get_end_of_emulation()
{
	return this->end_of_emulation;
}

bool elevator::get_status()
{
	return ((this->goUp) or (this->goDown));
}

int elevator::get_current_floor()
{
	return this->current_floor;
}

int elevator::get_target_floor()
{
	return this->target_floors->at(0);
}

int elevator::get_step()
{
	if (this->goUp)
	{
		return 1;
	}
	else if (this->goDown)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int elevator::get_floor_call()
{
	return this->floor_calls->at(0);
}

int elevator::get_people_in_elevator()
{
	return this->people_in_elevator;
}

int elevator::get_kol_of_target_floors() 
{
	return this->target_floors->size();
}

int elevator::get_kol_of_floor_calls()
{
	return this->floor_calls->size();
}

int elevator::get_is_target_floor(int floor) 
{
	int position = 0;
	bool flag = false;
	int size = this->target_floors->size();
	while (position < size)
	{
		if (this->target_floors->at(position) == floor)
		{
			flag = true;
			break;
		}
		position++;
	}
	if(flag)
	{
		return position;
	}
	else
	{
		return -1;
	}
}

int elevator::get_is_floor_call(int floor)
{
	int position = 0;
	bool flag = false;
	int size = this->floor_calls->size();
	while (position < this->floor_calls->size())
	{
		if (this->floor_calls->at(position) == floor)
		{
			flag = true;
			break;
		}
		position++;
	}
	if (flag)
	{
		return position;
	}
	else
	{
		return -1;
	}
}

elevator::~elevator()
{
	delete this->floor_calls;
	delete this->target_floors;
}
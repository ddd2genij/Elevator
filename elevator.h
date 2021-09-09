#ifndef elevator_H
#define elevator_H
#include <iostream>
#include <vector>

class elevator
{
private:
	bool goUp;
	bool goDown;
	bool end_of_emulation;


	int capacity;
	int people_in_elevator;
	int count_of_floors;
	int current_floor;
	int first_priority_floor; //target of movement

	std::vector<int>*  target_floors; //first priority queue(peressing in cabin)
	std::vector<int>* floor_calls;  //second priority queue(peressing on floors)
	std::string status_door;

public:
	elevator(int,int);

	void set_status_door(std::string);
	void set_first_priority_floor(int); //if isnt anyting calls 0;
	void set_capacity(int);
	void set_count_of_floors(int);
	void set_end_of_emulation(bool);
	void set_people_in_elevator(int);
	void set_goUp(bool);
	void set_goDown(bool);
	void set_current_floor(int);
	void add_target_floor(int);
	void remove_target_floor(int); // if recieved -1 array is cleared.
	void add_floor_calls(int);
	void remove_floor_calls(int); 
	
	int get_first_priority_floor();
	bool get_end_of_emulation();
	int get_count_of_floors();
	int get_kol_of_target_floors();
	int get_kol_of_floor_calls();
	int get_capacity();
	int get_people_in_elevator();
	std::string get_message();		/*Pattern of message:1) Cabin on floor: N1. People in elevator: N2. Going up/down.<Press any key to enter new command>
														 2) Cabin on floor: N1. Stopped. People in elevator: N2. Capacity: N3. Doors opened.*/
	bool get_status();
	int get_step();
	int get_current_floor();
	int get_target_floor(); //first from list of target_floors
	int get_floor_call();	//first from list of floor_calls
	int get_is_target_floor(int);	// -1 if not target otherwise position in queue
	int get_is_floor_call(int);		// -1 if not target otherwise position in queue

	~elevator();
};
#endif

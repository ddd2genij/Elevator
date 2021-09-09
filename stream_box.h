#ifndef stream_box_H
#define stream_box_H

class bool_box 
{
private:
	bool command;
	bool boarding;
	bool leave;
	bool enter;

public:
	bool_box(); // default all of parameters are false

	void set_command(bool);
	void set_leave(bool);
	void set_enter(bool);
	void set_boarding(bool);

	bool get_leave();
	bool get_enter();
	bool get_command();
	bool get_boarding();
};

#endif


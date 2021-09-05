#include <iostream>
#include <Windows.h>
#include <locale.h>
#include <string>
#include <exception>
#include <thread>
#include "elevator.h"

elevator movement_parameters{ 0,0 };

void greetings();
int get_property_number(std::string);
int get_property_number(std::string, int,int, std::string, std::string);
void get_commad_from_terminal();
void boarding_to_elevator();
void elevator_step();


void boarding_to_elevator()
{
    std::cout << movement_parameters.get_message();
    int current_amount = movement_parameters.get_people_in_elevator();
    std::cout << " Amount of people who left the elevator:\n ";
    int leaved_people = get_property_number(" Entered symbol isn't a number. Please try again.\n", 0, current_amount, " Amount of people can't be negative. Please try again.\n", " Number exceeds amount of people in the elvator. Please try again.\n");
    std::cout << "Amount of people who enetered the elevator:\n ";
    int entered_people = get_property_number(" Entered symbol isn't a number. Please try again.\n", 0, movement_parameters.get_capacity() - (current_amount - leaved_people), " Amount of people can't be negative. Please try again.\n", " Amount of people can't exceeds Capacity. Please try again.\n");
    movement_parameters.set_people_in_elevator(current_amount - leaved_people + entered_people);
    if (current_amount - leaved_people + entered_people) 
    {
        movement_parameters.remove_target_floor(-1); //Removal all of clicks in cabine as the elevator is empty
    }
    std::cout << movement_parameters.get_message();
}

void elevator_step()
{
    movement_parameters.set_goDown(false);
    movement_parameters.set_goUp(false);

    int current_floor = movement_parameters.get_current_floor();
    int position_in_queue_cabin = movement_parameters.get_is_target_floor(current_floor);
    int position_in_queue_floor = movement_parameters.get_is_floor_call(current_floor);
    bool loading_flag = false;

    if (position_in_queue_cabin != -1)
    {
        movement_parameters.remove_target_floor(position_in_queue_cabin);
        loading_flag = true;
    }
    if (position_in_queue_floor != -1)
    {
        movement_parameters.remove_floor_calls(position_in_queue_floor);
        loading_flag = true;
    }

    if (loading_flag)
    {
        boarding_to_elevator();
    }

    int target_floor = 1;

    if (movement_parameters.get_kol_of_target_floors() == 0)
    {
        if (movement_parameters.get_kol_of_floor_calls() != 0)
        {
            target_floor = movement_parameters.get_floor_call();
        }
    }
    else
    {
        target_floor = movement_parameters.get_target_floor();
    }

    if ((current_floor - target_floor) > 0)
    {
        movement_parameters.set_goDown(true);
        std::cout << movement_parameters.get_message();
    }
    else if ((current_floor - target_floor) < 0)
    {
        movement_parameters.set_goUp(true);
        std::cout << movement_parameters.get_message();
    }
}

void get_commad_from_terminal()
{
    std::string string_command;
    /*
    std::thread t1([&]() { std::cin >> string_command; });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    t1.detach();
    */
    std::cin >> string_command;
    if (string_command[0] == '*')
    {
        return;
    }
    char command = string_command[0];
    if ((command != 'F') and (command != 'C') and (command != 'Q'))
    {
        std::cout << " Invalid command name. Please try again.\n";
        return;
    }
    else 
    {
        try
        {
            if (command == 'Q')
            {
                movement_parameters.set_end_of_emulation(true);
                return;
            }
            int number = std::stoi(string_command.substr(1));
            if (number > movement_parameters.get_count_of_floors())
            {
                std::cout << " Impossibility of implimentation. Exceeds amount of floors in house. Please try again.\n";
                return;
            }
            if (number < 1)
            {
                std::cout << " Number of floor can't be negative. Please try again.\n";
                return;
            }
            if (command == 'F')
            {
                if (movement_parameters.get_is_floor_call(number)==-1)
                {
                    movement_parameters.add_floor_calls(number);
                    return;
                }
            }
            if (command == 'C')
            {
                if (movement_parameters.get_people_in_elevator() != 0)
                {
                    if (movement_parameters.get_is_target_floor(number)==-1)
                    {
                        movement_parameters.add_target_floor(number);
                        return;
                    }
                }
                else 
                {
                    std::cout << " Impossibility of implimentation. Elevator is empty. Please try again.\n";
                    return;
                }
            }
        }
        catch (std::exception e)
        {
            std::cout << " Invalid command name. Please try again.\n";
            return;
        }
    }
}

int get_property_number(std::string message_exception_string, int low, int high, std::string message_low, std::string message_high)
{
    std::string number_string;
    int number;
    bool seccessful_reading = false;
    while (not seccessful_reading)
    {
        try
        {
            std::cin >> number_string;
            number = std::stoi(number_string);
            if (number < low) 
            {
                std::cout << message_low;
            }
            else if (number > high)
            {
                std::cout << message_high;
            }
            else 
            {
                seccessful_reading = true;
            }
        }
        catch (std::exception e)
        {
            std::cout << message_exception_string;
        }
    }
    return number;
}

int get_property_number(std::string message) 
{
    std::string number_string;
    int number;
    bool seccessful_reading = false;
    while (not seccessful_reading)
    {
        try
        {
            std::cout << message;
            std::cin >> number_string;
            number = std::stoi(number_string);
            seccessful_reading = true;
        }
        catch (std::exception e)
        {
            std::cout << "Please enter property number\n";
        }
    }
    return number;
}

void greetings() 
{
    std::cout << "\t ...\n";
    std::cout << "Hello. It is an elevator emulator program.\n";
    std::cout << "Elevator start position is 1 floor\n";
    std::cout << "To call on the floor, enter F and floor number(F5)\n";
    std::cout << "To call from cabin, enter c and floor number(C5)\n";
    std::cout << "Below is a fragment of a session with the program:\n" << "\n";
    std::cout << "\t ...\n";
    std::cout << "\t >>F1 call on Floor 01 \n ";
    std::cout << "\t Cabin on floor 3. People in elevator: 1. Going down. <Press any key to enter new command>\n";
    std::cout << "\t >>F7 call on Floor 01 \n ";
    std::cout << "\t Cabin on floor 2. People in elevator: 1. Going down <Press any key to enter new command>\n";
    std::cout << "\t Cabin on floor 1 Stopped. People in elevator: 1. Doors opened.\n";
    std::cout << "\t Amount of people who left the elevator:\n ";
    std::cout << "\t >>5\n";
    std::cout << "\t Number exceeds amount of people in the elvator. Please try again.\n";
    std::cout << "\t >>a\n";
    std::cout << "\t Entered symbol isn't a number. Please try again.\n";
    std::cout << "\t >>-5\n";
    std::cout << "\t Amount of people can't be negative. Please try again.\n";
    std::cout << "\t >>1\n";
    std::cout << "\t Amount of people who enetered the elevator:\n ";
    std::cout << "\t >>6\n";
    std::cout << "\t Amount of people can't exceeds Capacity. Please try again.\n";
    std::cout << "\t >>0 /Emty elevator start to floor 7\n";
    std::cout << "\t Lift Cabin on floor 1. People in elevator: 0. Going up. <Press any key to enter new command>\n";
    std::cout << "\t >>А7\n";
    std::cout << "\t Invalid command name. Please try again.\n";
    std::cout << "\t Cabin on floor 2. People in elevator: 0. Going up <Press any key to enter new command>\n";
    std::cout << "\t >>C7\n";
    std::cout << "\t Impossibility of implimentation. Elevator is empty. Please try again.\n";
    std::cout << "\t Cabin on floor 3. People in elevator: 0. Going up <Press any key to enter new command>\n";
    std::cout << "\t >>F791649\n";
    std::cout << "\t Impossibility of implimentation. Exceeds amount of floors in house. Please try again.\n";
    std::cout << "\t Cabin on floor 4. People in elevator: 0. Going up <Press any key to enter new command>\n";
    std::cout << "\n";
    std::cout << "\t etc...";
    std::cout << "\n";
}

int main()
{
    //SetConsoleOutputCP(CP_UTF8);
    //setlocale(LC_ALL, "Russian");
    greetings();

    int count, capacity;
    bool default_position = true;
    count = get_property_number("Please enter count of floors\n");
    capacity = get_property_number("Please enter capacity of elevator\n");

    movement_parameters.set_capacity(capacity);
    movement_parameters.set_count_of_floors(count);
    
    while (!movement_parameters.get_end_of_emulation()) 
    {
        get_commad_from_terminal();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (movement_parameters.get_status())
        {
            default_position = true;
            int current_floor = movement_parameters.get_current_floor() + movement_parameters.get_step();
            movement_parameters.set_current_floor(current_floor);
        }
        else if (default_position)
        {
            std::cout << "Stopped on floor 1. Wating for a call\n";
            default_position = false;
        }
        elevator_step();
    }
}


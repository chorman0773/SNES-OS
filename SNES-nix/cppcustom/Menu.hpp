#ifndef Menu_hpp_2018_02_22_8_50
#define Menu_hpp_2018_02_22_8_50
#pragma once
#include <iostream>
#include <string>
extern "C"{
#include <conio.h>
};
#include <vector>




using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

/*
	Pulled Menuing code from one I wrote for Revised Treasure Island for C++
	I guarentee this code belongs to me.
	Updated menuing to use std::vector rather than dynamic array (update 2018-02-22)
*/
class Menu{

private:
	//Menu values. Controls how the menu operates and displays but are mostly static
	string name;
	vector<string> options;
	int num;
	bool wraps;
	string terminalOpt;
	int optCount;
	
	//Menu state, which can control the menuing system.
	bool hasTerminalOpt;
	bool showTerminalOpt;
	int selection;

	//Menu control system, which prevent mutation
	bool lock;
	bool requiresInit;

	void updateOptCounts();

public:
	void init();
	Menu(string name, string options[], int num, bool wrapping);
	Menu(string name, string options[], int num);
	Menu(string name);
	Menu(string name, bool wrapping);
	Menu();

	void loadOptions(string options[],int num);
	void loadOptions(vector<string> options);
	
	void selectionIncrease();
	void selectionDecrease();
	void drawVertical();

	int getSelection();
	void addOption(string option);
	void removeOption(int opt);
	void setTerminalOption(string endOption);
	bool isTerminalOption();
	void startMenu();
	void endMenu();

	void setTerminalOptionVisibility(bool visibility);
	void clearOptions();
};

class ActionListener{
public:
	virtual bool onAction(int& code) = 0;
};

/**
	Draws a Menu on the screen. The menu is mostly seemless (some flickering) but will advance if the input is up, down, w, or s and chooses the selection on Enter
*/
int menu(Menu& m);

/**
	Draws a Menu on the screen. The menu is mostly seemless (some flickering) but will advance if the input is up, down, w, or s and chooses the selection on Enter
*/
int menu(Menu& m,ActionListener& extra);


bool confirm(string text,bool invert = false);
bool secureConfirm(string text);

#endif
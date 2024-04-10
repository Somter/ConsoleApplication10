// ConsoleApplication10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>	
#include <string>	
using namespace std;  

class Transport;	

class AbstractMediator
{
public:
	virtual void Register(Transport* transport) abstract;	
	virtual void Send(string from, string to, string message) abstract;	
};	

class Mediator : public AbstractMediator	
{
	map<string, Transport*> transports;
public:
	void Register(Transport* transport)	
	{
		auto res = transports.find(transport->GetName());		
		if (res == transports.end())	
		{
			transports[transport->GetName()] = transport;
		}	
		transport->SetChatroom(this);			
	}	
	void Send(string from, string to, string message) override 
	{
		Transport* transport = transports[to];		
		if (transport != nullptr)
		{
			transport->Receive(from, message);	
		}
	}
};


class Transport 
{
	AbstractMediator* mediator;	
	string name;
public:
	Transport(string n)
	{
		this->name = n;
	}
	string GetName() 
	{
		return name;
	}
	void SetName(string n) 
	{
		this->name = n;	
	}
	AbstractMediator* GetMediator()
	{
		return mediator;
	}
	void SetChatroom(AbstractMediator* mediator)
	{
		this->mediator = mediator;	
	}
	void Send(string to, string message)
	{
		mediator->Send(name, to, message);	
	}
	virtual void Receive(string from, string message)	
	{
		cout << from << " to " << name << ": '" << message << "'" << endl;	
	}
};

class Airplane : public Transport
{
public:
	Airplane(string name) : Transport(name) {}		
	void Receive(string from, string message) override
	{
		cout << "To a Airplane: ";	
		Transport::Receive(from, message);	
	}
};
	
class Helicopter : public Transport
{
public:
	Helicopter(string name) : Transport(name) {}		
	void Receive(string from, string message) override
	{

		cout << "To a Helicopter: ";
		Transport::Receive(from, message);		
	}
};

class FlyingSaucer : public Transport	
{
public:
	FlyingSaucer(string name) : Transport(name) {}	
	void Receive(string from, string message) override
	{

		cout << "To a Flying saucer: ";		
		Transport::Receive(from, message);	
	}
};

void registration(AbstractMediator* chatroom, Transport* participants[], int size);
void chat(Transport* transports, string to, string message);


int main()
{
	AbstractMediator* chatroom = new Mediator();

	Transport* transports[5] = {	
		new Airplane("George"),
		new Airplane("Paul"),
		new Helicopter("Ringo"),
		new Helicopter("John"),
		new FlyingSaucer("Yoko")	
	};
	registration(chatroom, transports, 5);	

	chat(transports[4], "John", "Hi John!");
	chat(transports[1], "Ringo", "All you need is love");
	chat(transports[2], "George", "My sweet Lord");
	chat(transports[1], "John", "Can't buy me love");
	chat(transports[3], "Yoko", "My sweet love");

	delete chatroom;
	for (int i = 0; i < 5; i++)
		delete transports[i];	

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

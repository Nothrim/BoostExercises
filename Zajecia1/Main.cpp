// Zajecia1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "TworzenieWatkow.h"
#include "Synchronizacja.h"
#include "ZmienneWarunkowe.h"
#include "Monitor.h"
#include "Consumer.h"
#include "Producer.h"
#include "Kolej.h"
int main()
{
	//Calka z sinusa
	cout << "CALKA Z SINUSA" << endl;
	double result = 0.0;
	TworzenieWatkow calka(0, M_PI, &result);
	boost::thread thread(calka);
	cout << "Hardware concurrency: " << boost::thread::hardware_concurrency
		<< endl;
	cout << "Thread ID" << thread.get_id() << endl;
	thread.join();
	cout << "result" << result << endl;
	cout << "DONE!";
	getchar();
	//-------------------------------------
	//Synchronizacja
	cout << "SYNCHRONIZACJA" << endl;
	mutex characterMutex;
	string lancuch;
	lancuch.resize(CHARACTERS_TO_WRITE);
	thread_group threads;
	for (unsigned int i = 0; i < NUMBER_OF_THREADS; ++i)
		threads.create_thread(Watek('a'+i,lancuch,characterMutex));
	threads.join_all();
	cout << lancuch << endl;
	cout << "DONE!";
	getchar();
	//----------------------------------------
	//Zmienne warunkowe
	cout << "ZMIENNE WARUNKOWE"<<endl;
	mutex dataMutex;
	Monitor<char>container(dataMutex);
	thread_group conditional;
	mutex consoleMutex;
	for (int i = 0; i < 5; i++) {
		conditional.create_thread(Consumer(container,i,consoleMutex));
		conditional.create_thread(Producer(container,i,consoleMutex));
	}
	conditional.join_all();
	cout << "DONE!";
	getchar();
	//------------------------------------
	//Pociagi/semafory
	cout << "STACJA KOLEJOWA"<<endl;
	Peron p1("p1"), p2("p2"), p3("p3");
	Train tr1 = Train("T1", p2, p1);
	boost::thread t1(tr1);
	boost::thread t2(Train("T2", p2, p3));
	boost::thread t3(Train("T3", p2, p1));
	boost::thread t4(Train("T4", p2, p3));
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout << "DONE";
	getchar();
    return 0;
}


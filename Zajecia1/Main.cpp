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
#include "Philosophers.h"
#include "Exam.h"
#include "SmolkaExam.h"
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
	cout << "DONE"<<endl;
	getchar();
	cout << "FILOZOFOWIE" << endl;
	Semafor eating(PHILOSOPHERS - 1);

	Fork* forks[5];
	thread_group philosophers;
	for (int i = 0; i<PHILOSOPHERS; i++)
	{
		forks[i] = new Fork(i);
	}
	for (int i = 0; i<PHILOSOPHERS; i++)
	{
		philosophers.create_thread(Philosopher(i, forks[i], forks[(i + (PHILOSOPHERS -1)) % PHILOSOPHERS], eating));
	}
	philosophers.join_all();
	cout << "DONE"<<endl;
	getchar();
	cout << "TASK 1" << endl;
	mutex tConsoleMutex;
	Task1 taskOne(tConsoleMutex,0);
	Task1 taskTwo(tConsoleMutex,1);
	boost::thread th1(taskOne);
	boost::thread th2(taskTwo);
	th1.join();
	th2.join();
	cout << "DONE" << endl;
	getchar();
	cout << "TASK 2" << endl;
	boost::mutex task2Mutex;
	Task2 task2DataGenerator(100);
	boost::thread task2Thread(task2DataGenerator);
	boost::unique_lock<mutex>task2Lock(task2Mutex);
	task2DataGenerator.task2isGeneratingData->wait(task2Lock);
	for (int i = 0; i < 100; i++)cout << task2Array[i] << endl;
	cout << "DONE" << endl; 
	getchar();
	cout << "TASK 3" << endl;
	thread_group task3Group;
	Semafor task3Semafor(1);
	Semafor task3Max3ThreadsSemafor(3);
	for (int i = 0; i < 10; i++) {
		task3Group.create_thread(Task3(task3Max3ThreadsSemafor,task3Semafor,i));
	}
	task3Group.join_all();
	cout << "DONE" << endl;
	getchar();
	cout << "SMOLKA EXAM"<<endl;
	cout << "TASK 1"<<endl;
	boost::mutex sConsoleMutex;
	STask1 st1(sConsoleMutex);
	STask1 st2(sConsoleMutex);
	boost::thread sTask1Thread(st1);
	boost::thread sTask1Thread2(st2);
	sTask1Thread.join();
	sTask1Thread2.join();
	cout << "DONE" << endl;
	getchar();
	cout << "TASK 2" << endl;
	sN = 75;
	boost::thread sTask2Thread(sTask2);
	boost::mutex sTask2Mutex;
	boost::unique_lock<mutex>sTask2Lock(sTask2Mutex);
	sTask2Condition.wait(sTask2Lock);
	for (int i = 0; i < 75; i++) {
		cout<< sTask2Array[i]<<endl;
	}
	getchar();
    return 0;
}


/*
 * Thread.h
 *
 *  Created on: Dec 20, 2014
 *      Author: root
 */

#ifndef GWEN_THREAD_H_
#define GWEN_THREAD_H_

#include <set>
#include <pthread.h>

struct event;
struct event_base;

#define SIGHUP  			1
#define SIGINT  			2
#define SIGQUIT 			3
#define SIGILL  			4
#define SIGTRAP 			5
#define SIGABRT 			6
#define SIGBUS  			7
#define SIGFPE  			8
#define SIGKILL 			9
#define SIGUSR1 			10
#define SIGSEGV 			11
#define SIGUSR2 			12
#define SIGPIPE 			13
#define SIGALRM 			14
#define SIGTERM 			15
#define SIGCHLD 			17
#define SIGCONT 			18
#define SIGSTOP 			19
#define SIGTSTP 			20
#define SIGTTIN 			21
#define SIGTTOU 			22
#define SIGURG  			23
#define SIGXCPU 			24
#define SIGXFSZ 			25
#define SIGVTALRM   		26
#define SIGPROF 			27
#define SIGWINCH			28
#define SIGIO   			29
#define SIGPWR  			30
#define SIGSYS  			31

#define SIGNAL_OFFSET   	20
#define SIGNAL_MAXVAL   	32

// Signal to turn server on
#define SIGNAL_SVC_ON   	SIGNAL_OFFSET + 1
// Signal to turn server off
#define SIGNAL_SVC_OFF  	SIGNAL_OFFSET + 2
// Signal to quit server
#define SIGNAL_QUIT 		SIGNAL_OFFSET + 3
// Signal to turn logger on
#define SIGNAL_LOG_ON   	SIGNAL_OFFSET + 4
// Signal to turn logger off
#define SIGNAL_LOG_OFF  	SIGNAL_OFFSET + 5


#define PROCESS_GAME_GATE  1
#define PROCESS_GAME_SCENE 2

namespace Easy
{
class Buffer;

typedef int (*START_LOOP_FUNC)(void *arg);

class Thread
{
public:
	Thread(void);
     ~Thread(void);

    static void* threadCallback(void *arg);

    int threadIndex(int index = -1);

    int start(void);
    int wait(void);
    int signal(int sig);

    int runStartLoop(void);

protected:
    START_LOOP_FUNC start_loop_;
    void *loop_ptr_;
    pthread_t tid_;

    int thread_index_;
};

class EventBaseThread: public Thread
{
	typedef std::set<event *> SignalEventSet;
public:
	EventBaseThread(void);
	virtual ~EventBaseThread(void);

	event_base *eventBase(void);

	void closeSec(int sec);

	virtual int signalCallBack(int sig);

	void registeSignal(int sig);

	int startSignalLoop(void);

private:
	static void eventCallback(int fd, short which, void *arg);
	static int startSignalLoop(void *arg);

private:
	struct event_base *base_;
	SignalEventSet sig_set_;
	int close_sec_;
};

}
#endif /* GWEN_THREAD_H_ */

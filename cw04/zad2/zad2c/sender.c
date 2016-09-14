#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int received;
int loop;

void handler(int signal){
	if(signal == SIGRTMIN+SIGUSR1){
		received++;
	}else if(signal == SIGRTMIN+SIGUSR2){
		loop = 0;
	}
}

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Two arguments needed\n");
		return -1;
	}

	int signals = atoi(argv[1]);
	int pid = atoi(argv[2]);
	received = 0;
	loop = 1;

	signal(SIGRTMIN+SIGUSR2, handler);
	signal(SIGRTMIN+SIGUSR1, handler);

	for(int i = 0; i < signals; i++){
		kill(pid, SIGRTMIN+SIGUSR1);
	}


	kill(pid, SIGRTMIN+SIGUSR2);

	while(loop);

	printf("Sent by sender: %d\n", signals);
	printf("Sent back to sender by receiver: %d\n", received);

	return 0;
}



// -------------------- VARIABLES --------------------
int queueLength = 64; // May be resized, if exceded.
int processCount = 0; // Incremented with each input.
// ---------------------------------------------------


// -------------------- CONSTANTS --------------------
int const TIME_QUANTUM = 2; // Fixed time quantum.
int const INCREASE_FACTOR = 2; // Factor by which queue length increases.
// ---------------------------------------------------


// Allocate memory to new process and initialise it.
Process *newProcess(int burstTime, int arrivalTime) {

    // Allocating memory for a process, if available.
    Process *p = (Process *) malloc(sizeof(Process));
    if(p == NULL) {
        return NULL;
    }

    // Set the burst time, pId and return the value.
    p->pId = processCount++;
    p->burstTime = burstTime;
    p->arrivalTime = arrivalTime;
    return p;
}


// Check if input string contains all integers.
// Return true if all digits, false if not.
bool isInt(char* input) {
  for(int i = 0; i < strlen(input); i++) {
    if(!isdigit(input[i])) {
      return false;
    }
  }
  return true;
}


// Ensure all inputs to the program are integers.
bool verifyAllInputsInt(int argc,  char **argv) {

    // check all int 
    for(int i = 1; i < argc; i++) {
      if(!isInt(argv[i])) {
        printf("(ERROR) All inputs need to be integers");
        return false;
      }
    }
    return true;

}


bool isEvenNumberOfArguments(int argc) {
    return (argc - 1) % 2 != 0;
}


// Checks if the current process is ready to be discarded from waiting queue.
// If arrival time meets the current time, process gets removed and added to the processing queue.
void addWaitingNode(LinkedList *waitingQueue, LinkedList *processQueue, int timeElapsed) {

    Node *candidateNode = peek_head_linked_list(waitingQueue);
    while(candidateNode && candidateNode->process->arrivalTime <= timeElapsed) {
        candidateNode = remove_head_linked_list(waitingQueue);
        append_linked_list(processQueue, candidateNode->process);
        printf("\nNode (ID: %d) is added from the waiting queue\n",
                candidateNode->process->pId);
        printf("Time elapsed: %d\n", candidateNode->process->arrivalTime);
        candidateNode = peek_head_linked_list(waitingQueue);
    }
}



// -------------------- PRINTING STUFF --------------------


/**
 *  Prints all the information about the process once it finishes executing.
 * */
void printProcessInfo(Process *process) {
    printf("    - Completion time: (%d)\n", process->completionTime);
    printf("    - Turn-around time: (%d)\n", process->turnAroundTime);
    printf("    - Waiting time: (%d)\n", process->waitingTime);
    printf("    - Burst time: (%d)\n", process->burstTime);
    printf("    - Arrival time: (%d)\n", process->arrivalTime);
    printf("    - Time Spent Processing: (%d)\n", process->timeSpentProcessing);
}


/**
 * Prints information on how to use the program, if user uses wrong CMD arguments. 
 * */
void printGuidelines() {
    printf("(ERROR) Invalid parameters.\n");
    printf("Should be in the format of { (Burst time 1) (Arrival time 1) (Burst time 2) (Arrival time 2) ... }\n");
    printf("For example: RR 54 32 2 32 12 2\n");
    printf("Or FCFS 54 32 2 32 12 2\n");
}


/**
 * Prints detailed about every process that has been executed.
 * Processes are ordered the way they have been terminated.
 * */
void printProcessTable(LinkedList *completedQueue) {

    printf("\n+-------------------------------------------------------------------------------------+\n");
    printf("|                                  Executed Processes                                 |\n");
    printf("+-----+-----------------+--------------+------------------+------------+--------------+\n");
    printf("|  ID | Waiting Time    | Completion Time | Turn-Around Time | Burst Time | Arrival Time |\n");

    // The following line will be used to separate processes from each other.
    char line[] = "+-----+-----------------+--------------+------------------+------------+--------------+\n";
    printf("%s", line);

    while(!linked_list_empty(completedQueue)) {
        Node *node = remove_head_linked_list(completedQueue);
        printf("|%5d|%14d|%17d|%18d|%12d|%14d|\n",
                node->process->pId, node->process->waitingTime,
                node->process->completionTime, node->process->turnAroundTime,
                node->process->burstTime, node->process->arrivalTime);
        printf("%s", line);
    }    

}

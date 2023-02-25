int proc = 1;
int simul = 1;
int time_limit = 1;

int seconds = 0;
int nanoseconds = 0;


void child();
void parent();
void print_process_table();
void increment_clock();
void check_if_child_has_terminated();
void possibly_launch_new_child();
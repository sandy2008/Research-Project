/*******************************/
/*  sucheduling problem 2010   */
/*   support hedder file       */
/*******************************/

void check_arg(int, char **);
void input(int, char **);
void output(char **);

#define MEMORY_OVER_ERROR \
        fputs("Memory Over!", stderr); \
	abort()

/*input data*/
int total_pe;
int total_task;

struct _task
{
    int no;
    int cost;
    int total_pre;
    int *pre;
} *task;

/*output data*/
int total_cost;

struct _pe
{
    int *task_no;
    int *task_cost;
} *pe;

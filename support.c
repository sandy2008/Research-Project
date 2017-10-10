#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"

#define data_size 11

int gnt_size;

int get_data(FILE *fp)
{
    int i;
    char buff[data_size+1];

    for (i = 0; i < data_size; i++) {
	buff[i] = fgetc(fp);
    }
    buff[data_size] = 0;

    return atoi(buff);
}

void check_arg(int argc, char *argv[])
{
    int length;
    char *check;

    if (argc != 4) {
	fprintf(stderr, "err\n");
	fprintf(stderr, "usage: ./sche2010 PE_NUM input_file output_file\n");
	abort();
    }

    length = strlen(argv[2]);
    check = strstr(argv[2] + length - 4, ".stg");
    if (check == NULL) {
	fprintf(stderr, "err\n");
	fprintf(stderr, "input file name must be \".stg\" file.\n");
	abort();
    }

    length = strlen(argv[3]);
    check = strstr(argv[3] + length - 4, ".gnt");
    if (check == NULL) {
	fprintf(stderr, "err\n");
	fprintf(stderr, "output file name must be \".gnt\" file.\n");
	abort();
    }
}

void input(int argc, char *argv[])
{
    char *filename;
    FILE *fp;
    int i,j;

/* total pe */
    total_pe = atoi(argv[1]);

/* file open */
    filename = argv[2];
    fp = fopen(filename, "r");
    if (fp == 0) {
	fprintf(stderr, "File is not found\n");
	abort();
    }
/* total task */
    total_task = get_data(fp) + 2;
    while (fgetc(fp) != '\n');

    task = (struct _task *) malloc(sizeof(struct _task) * total_task);
    if (task == NULL) {
	MEMORY_OVER_ERROR;
    }

/* task */
    for (i = 0; i < total_task; i++) {
/* no */
	task[i].no = get_data(fp);
/* cost */
	task[i].cost = get_data(fp);
/* npre */
	task[i].total_pre = get_data(fp);

/* malloc */
	task[i].pre = (int *) malloc(sizeof(int) * task[i].total_pre);

	for (j = 0; j < task[i].total_pre; j++) {
/* pre */
	    task[i].pre[j] = get_data(fp);
	    
	}
	while (fgetc(fp) != '\n');
    }
    fclose(fp);

    pe = (struct _pe *)malloc(sizeof(struct _pe) * total_pe);
    if (pe == NULL) {
	MEMORY_OVER_ERROR;
    }

    gnt_size = total_task ;
    for (i = 0; i < total_pe; i++) {
	pe[i].task_no = (int *)malloc(sizeof(int) * gnt_size);
	if (pe[i].task_no == NULL) {
	    MEMORY_OVER_ERROR;
	}
	pe[i].task_cost = (int *)malloc(sizeof(int) * gnt_size);
	if (pe[i].task_cost == NULL) {
	    MEMORY_OVER_ERROR;
	}
    }
    
    /* initialize */
    total_cost = 0;
    for (i = 0; i < total_pe; i++) {
	for (j = 0; j < gnt_size; j++) {
	    pe[i].task_no[j] = 0;
	    pe[i].task_cost[j] = 0;
	}
    }

}

void output(char *argv[])
{
    FILE *fp;
    int cost;
    int i,j;

    fp = fopen(argv[3], "w");
    if(fp == NULL){
	printf("Output FIlE Open  error!\n");
	abort();
    }
    
    fprintf(fp, "%d\n", total_pe);
    fprintf(fp, "1\n");
    for (i = 0; i < total_pe; i++) {
	fprintf(fp, "PE %d\n", i+1);
    }
    fprintf(fp, "%d\n", total_cost);

    for(i = 0; i < total_pe; i++){

/*output task*/
	cost = 0;
	for (j = 0; j < gnt_size; j++) {
	    if(pe[i].task_no[j] < 0)
		fprintf(fp, "%7d%7d\n", 0, pe[i].task_cost[j]);
	    else
		fprintf(fp, "%7d%7d\n", pe[i].task_no[j], pe[i].task_cost[j]);
	    cost += pe[i].task_cost[j];
	    if (cost >= total_cost)
		break;
	}
    }

    fprintf(fp, "\"%d\"\n", total_cost);
    fclose(fp);
}

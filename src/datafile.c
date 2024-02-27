#include "datafile.h"
#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_errno.h>


void count_rows_cols(const char *filename, int *rows, int *cols){
    FILE *file = fopen(filename, "r");
    if (!file){
        perror("Unable to open the file");
        log_err("Unable to open file: name = %s ", filename);
        exit(1);
    }

    char buffer[1024];
    int row_count = 0;
    int col_count =0;

    while(fgets(buffer, 1024, file)){
        row_count++;
        if (row_count == 1){
            char *token = strtok(buffer, ",");
            while (token){
                col_count++;
                token = strtok(NULL, ",");
            }
        }
    }
    fclose(file);

    *rows = row_count;
    *cols = col_count;
    if(row_count != col_count){
        log_err("Not a square matrix: row:column =  %d:%d name = %s ", row_count, col_count, filename);
    }

}

void load_data(const char *filename, gsl_matrix *m){
    FILE *file = fopen(filename, "r");
    if(!file){
        perror("Unable to open the file");
        log_err("Unable to open file: name = %s ", filename);
        exit(1);
    }

    int row = 0; 
    char buffer[1024];

    while (fgets(buffer, 1024, file)){
        int col = 0;
        char *value = strtok(buffer, ",");
        while (value){
            gsl_matrix_set(m, row, col, atof(value));
            value = strtok(NULL, ",");
            col++;
        }
        row++;
    }
    fclose(file);
}
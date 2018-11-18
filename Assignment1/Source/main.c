#include <stdio.h>
#include <stdlib.h>

int printResult(int tempr, int index, int tempc,int multiplication,FILE *output){

    fprintf(output,"%d,%d:%d\n",tempr+index,tempc+index,multiplication); /*Writing the results to the output file */
}

int newMatrix(int **map,int **matrix,int counter,int tempr, int tempc){
    int i = 0; /*Defining an integer value for the FOR loop*/
    int j = 0;
    for (i = 0; i < counter ; i++) {
        for (j=0; j< counter;j++) {
            matrix[i][j] = map[i+tempr][j+tempc]; /*Reproduce the matrix for the comparison*/
        }
    }
}

int findTreasure(int **map,int **matrix ,int **keymap,int counter,int tempr,int tempc,FILE *output){

    int index = counter/2; /*Defining an integer for finding the middle index of the results*/
    int multiplication = 0; /*Defining an integer for the multiplication result*/
    int finalresult = 0; /*Defining an integer for the final result*/
    int i = 0;
    int j = 0;

    for (i = 0; i < counter ; ++i) {
        for (j = 0; j < counter ; ++j) {
            multiplication += (matrix[i][j]) * (keymap [i][j]); /*Doing the multiplication between the matrix and the keymap*/
        }
    }

    finalresult = (multiplication % 5); /*Doing the mod operation for getting the final result*/

    if(finalresult == 0){  /*If it is 0 we found the treasure and finish the recursion*/

        printResult(tempr,index,tempc,multiplication,output);

    }
    else if (finalresult == 1){  /*If it is 1 go up*/

        if(matrix[0][0] == 0 && matrix[0][1] == 0 && matrix[0][2] == 0){ /*Looking to the upside indexes for the sides*/

            printResult(tempr,index,tempc,multiplication,output);

            tempr += counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);

        }

        else{ /*Matrix goes up and call function again*/
            printResult(tempr,index,tempc,multiplication,output);

            tempr -= counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);
        }
    }
    else if (finalresult == 2){ /*If the result is 2 go down*/

        if(matrix[counter-1][0] == 0 && matrix[counter-1][1] == 0 && matrix[counter-1][2] == 0) { /*Looking to the downside indexes for the sides*/
            printResult(tempr,index,tempc,multiplication,output);

            tempr -= counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output); /*Recursive function*/
        } else{/*Matrix goes down*/
            printResult(tempr,index,tempc,multiplication,output);

            tempr += counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);
        }
    }
    else if (finalresult == 3){ /*If the result is 3 go right*/

        if(matrix[0][counter-1] == 0 && matrix[1][counter-1] == 0 && matrix[2][counter-1] == 0) { /*Looking to the rightside indexes for the sides*/
            printResult(tempr,index,tempc,multiplication,output);

            tempc -= counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);
        } else{/*Matrix goes right*/
            printResult(tempr,index,tempc,multiplication,output);

            tempc += counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);
        }
    }
    else if (finalresult == 4){/*If the result is 4 go left*/

        if(matrix[0][0] == 0 && matrix[1][0] == 0 && matrix[2][0] == 0) {/*Looking to the leftside indexes for the sides*/
            printResult(tempr,index,tempc,multiplication,output);

            tempc += counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);
        } else{/*Matrix goes left*/
            printResult(tempr,index,tempc,multiplication,output);

            tempc -= counter;

            newMatrix(map,matrix,counter,tempr,tempc);

            findTreasure(map,matrix,keymap,counter,tempr,tempc,output);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    int row,column,keysize,i,j,keymatrixsize;
    int tempr = 0; /*Defining an integer for the temporary map row value*/
    int tempc = 0; /*Defining an integer for the temporary map column value*/

    sscanf(argv[1],"%dx%d",&row,&column); /*Taking the map size from the commandline argument */

    keysize = atoi(argv[2]); /*Taking the key size from the commandline argument */

    FILE *mapmatrixfile; /*Creating a file pointer for the mapmatrix*/
    FILE *keymatrixfile;/* Creating a file pointer for the keymatrix*/
    FILE *outputfile; /* Creating a file pointer for the output file*/

    mapmatrixfile = fopen(argv[3], "r"); /*Taking the map values from the commandline argument */
    keymatrixfile = fopen(argv[4], "r"); /*Taking the key map values from the commandline argument */
    outputfile = fopen(argv[5], "w"); /*Taking the output file from the commandline argument */

    int **keymap = (int**)malloc(row * sizeof(int *));  /*Reserving RAM for the key map */
    for (i = 0; i < row; i++) {
        keymap[i] = (int*)malloc(column * sizeof(int *));
    }

    int **map = (int**)malloc(row * sizeof(int *)); /*Reserving RAM for the map matrix*/
    for (i = 0; i < row; i++) {
        map[i] = (int*)malloc(column * sizeof(int *));
    }

    keymatrixsize = 0;
    for (i = 0; i < keysize ; i++) {  /*Giving the values of the keymap from the keymatrixfile */
        for (j=0; j< keysize;j++){
            fscanf(keymatrixfile,"%d",&keymap[i][j]);
        }
        keymatrixsize++;

    }

    for (i = 0; i < row ; i++) {  /*Giving the values of the map matrix from the mapmatrixfile*/
        for (j=0; j< column;j++){
            fscanf(mapmatrixfile,"%d",&map[i][j]);
        }
    }

    int **matrix = (int**)malloc(row * sizeof(int *)); /*Reserving RAM for the comparison matrix*/
    for (i = 0; i < keymatrixsize; i++) {
        matrix[i] = (int *) malloc(column * sizeof(int *));
    }

    for (i = 0; i < keymatrixsize ; i++) { /*Giving the values of the matrix from the mapmatrix */
        for (j=0; j< keymatrixsize;j++) {
            matrix[i][j] = map[i][j];
        }
    }

    findTreasure(map,matrix,keymap,keymatrixsize,tempr,tempc,outputfile);

    fclose(outputfile); /*Closing the output file */
    fclose(mapmatrixfile); /*Closing the mapmatrix file */
    fclose(keymatrixfile); /*Closing the keymatrix file */
    free(map); /*Free space from the RAM */
    free(matrix); /*Free space from the RAM */
    free(keymap); /*Free space from the RAM */
    return 0;
}
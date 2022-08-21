/**
 * @author Jerin John
 * @date   April 14, 2022
 * C Program designed to simulate disk scheduling algorithms
**/

#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

char * mmapfptr;

#define CYLINDERS   20
#define MIN         0
#define MAX         299

int requests[CYLINDERS];
int sorted_requests[CYLINDERS];

int main(int argc, char const *argv[]){    
    //Checks if the number of Inputs is correct or not.
    if (argc != 3){
        printf("Incorrect number of Arguments\n");
        return -1;
    }

    //Parse the input and store it in appropriate values.
    int head = atoi(argv[1]);
    const char *direction = argv[2];
    
    //Reads the Binary Files and stores the value within an Integer Array.
    FILE *input = fopen("request.bin","rb");
    fread(requests,sizeof(requests),1,input);
    fclose(input);

    //Created a sorted request array:
    for(int a = 0; a < CYLINDERS; a++){
        sorted_requests[a] = requests[a];
    }

    for(int s = 1; s < CYLINDERS; s++){
        int key = sorted_requests[s];
        int t = s - 1;
        while(t >= 0 && sorted_requests[t] > key){
            sorted_requests[t+1] = sorted_requests[t];
            t  =  t - 1;    
        }
        sorted_requests[t + 1] = key;
    }


    printf("Total requests = %i \n", CYLINDERS);
    printf("Initial Haad Position = %i \n", head);
    printf("Direction of Head = %s \n", direction);
    // ********************************************************************************
    // FCFS 
    int total_fcfs = 0;
    int head_fcfs = head;
    printf("\nFCFS DISK SCHEDULING ALGORITHM \n \n");
    for(int i = 0; i < CYLINDERS; i++){
        total_fcfs += abs(head_fcfs - requests[i]);
        head_fcfs = requests[i];
        printf("%i ,", head_fcfs);
    }
    printf("\n \nFCFS - Total Head Movements = %i \n",total_fcfs);
    // ********************************************************************************
    // SSTF 
    int total_sstf = 0;
    int head_sstf = head;
    int used[CYLINDERS] = {0};
    int min_p = 0;
    printf("\nSSTF DISK SCHEDULING ALGORITHM\n \n");
    for(int i = 0; i < CYLINDERS; i++){
        int min = -1;
        for(int j = 0; j < CYLINDERS; j++){
            if(used[j] == 0){
                if (min == -1){
                    min = abs(head_sstf - requests[j]);
                    min_p = j;
                }
                else if (abs (head_sstf - requests[j]) < min) {
                    min = abs(head_sstf - requests[j]);
                    min_p = j;
                }
            }
        }      
        if(min != -1){
            total_sstf += min;
            head_sstf = requests[min_p];
            used[min_p] = 1;
            printf("%i ,", head_sstf);
        }
    }
    printf("\n \nSSTF - Total Head Movements = %i \n",total_sstf);
    // ********************************************************************************
    // SCAN 
    int total_scan = 0;
    int left[CYLINDERS] = {0};
    int right[CYLINDERS] = {0};
    int t1 = 0;
    int t2 = 0;
    int t2_c = 0;
    int t1_c = 0;
    int head_scan = head; 
    int cond = 0;
    int dir = -1;
    printf("\nSCAN DISK SCHEDULING ALGORITHM\n \n");
    if (strcmp("LEFT",direction) != 0 ){
        dir = 1;
    }
    for(int i = 0; i < CYLINDERS; i++){
        int temp = sorted_requests[i];
        if(temp < head_scan){
            left[t1] = temp;
            t1+= 1;
            t1_c = t1 - 1;
        } else if (temp > head_scan) {
            right[t2] = temp;
            t2+= 1;
        }
    }
    printf("%i ,", head_scan);
    for (int i = 0; i < CYLINDERS -1  ; i++){
        if(dir == -1){
            total_scan += abs(head_scan - left[t1_c]);
            head_scan = left[t1_c];
            t1_c = t1_c - 1;
            t1 = t1 - 1;
            printf("%i ,", head_scan);
            if(cond == 0 && t1 == 0){
                total_scan += abs(head_scan - 0);
                head_scan = 0;
                dir = 1;
                cond = 1;
            }
        }
        else if (dir == 1){
            total_scan += abs(head_scan - right[t2_c]);
            head_scan = right[t2_c];
            if (t2_c < (t2-1)){
                t2_c += 1;
            }
            printf("%i ,", head_scan);
            if (cond == 0 && t2_c == (t2 - 1)){
                cond = 1;
                dir = -1;
                total_scan += abs(head_scan - right[t2_c]);
                head_scan = right[t2_c];
                total_scan += abs(head_scan - 299);
                printf("%i ,", head_scan);
                head_scan = 299;
                i = i + 1;
            }
        }
    }

    printf("\n \nSCAN - Total Head Movements = %i \n",total_scan);  





    // ********************************************************************************
    // C-SCAN
    int total_sc = 0;
    int left_sc[CYLINDERS] = {0};
    int right_sc[CYLINDERS] = {0};
    int t1_sc = 0;
    int t2_sc = 0;
    int head_sc = head; 
    int dir_sc = -1;
    int dir_factor = -1;
    printf("\nC-SCAN DISK SCHEDULING ALGORITHM\n \n");
    if (strcmp("LEFT",direction) != 0 ){
        dir_sc = 1;
    }
    for (int i = 0; i < CYLINDERS; i++){
        int temp = sorted_requests[i];
        if(temp < head_sc){
            left_sc[t1_sc] = temp;
            t1_sc += 1;
        } else if (temp > head_sc){
            right_sc[t2_sc] = temp;
            t2_sc += 1;
        }
    }
    printf("%i ,", head_sc);
    if(dir_sc == -1){
        for(int li = (t1_sc); li > 0; li = li - 1){
            total_sc += abs(head_sc - left_sc[li - 1]);
            head_sc = left_sc[li -1];
            if (li == 1){
                printf("%i ,", head_sc);
                total_sc += abs(head_sc - MIN);
                head_sc = MIN;
            }
            else {
                printf("%i ,", head_sc);
            }
        }
        total_sc += abs(head_sc - MAX);
        head_sc = MAX;
        for(int li = (t2_sc); li > 0; li = li - 1){
            total_sc += abs(head_sc - right_sc[li - 1]);
            head_sc = right_sc[li -1];
            printf("%i ,", head_sc);
        }
    }

    if(dir_sc == 1){
        for(int li = 0; li < t2_sc; li++){
            total_sc += abs(head_sc - right_sc[li]);
            head_sc = right_sc[li];
            if (li == t2_sc - 1){
                printf("%i ,", head_sc);
                total_sc += abs(head_sc - MAX);
                head_sc = MAX;
            }
            else {
                printf("%i ,", head_sc);
            }
        }
        total_sc += abs(head_sc - MIN);
        head_sc = MIN;
        for(int li = 0; li < t1_sc; li++){
            total_sc += abs(head_sc - left_sc[li]);
            head_sc = left_sc[li];
            printf("%i ,", head_sc);
        }
    }
    printf("\n \nC-SCAN - Total Head Movements = %i \n",total_sc);   
    // ********************************************************************************
    // LOOK 
    int total_l = 0;
    int left_l[CYLINDERS] = {0};
    int right_l[CYLINDERS] = {0};
    int lt1 = 0;
    int lt2 = 0;
    int lt2_c = 0;
    int lt1_c = 0;
    int lhead_scan = head; 
    int lcond = 0;
    int ldir = -1;
    printf("\nLOOK DISK SCHEDULING ALGORITHM\n \n");
    if (strcmp("LEFT",direction) != 0 ){
        ldir = 1;
    }
    for(int i = 0; i < CYLINDERS; i++){
        int temp = sorted_requests[i];
        if(temp < lhead_scan){
            left_l[lt1] = temp;
            lt1+= 1;
            lt1_c = lt1 - 1;
        } else if (temp > lhead_scan) {
            right_l[lt2] = temp;
            lt2+= 1;
        }
    }
    printf("%i ,", lhead_scan);
    for (int i = 0; i < CYLINDERS -1  ; i++){
        if(ldir == -1){
            total_l += abs(lhead_scan - left_l[lt1_c]);
            lhead_scan = left_l[lt1_c];
            lt1_c = lt1_c - 1;
            lt1 = lt1 - 1;
            printf("%i ,", lhead_scan);
            if(lcond == 0 && lt1 == 0){
                //total_l += abs(lhead_scan - 0);
                //lhead_scan = 0;
                ldir = 1;
                lcond = 1;
            }
        }
        else if (ldir == 1){
            total_l += abs(lhead_scan - right_l[lt2_c]);
            lhead_scan = right_l[lt2_c];
            if (lt2_c < (lt2-1)){
                lt2_c += 1;
            }
            printf("%i ,", lhead_scan);
            if (lcond == 0 && lt2_c == (lt2 - 1)){
                lcond = 1;
                ldir = -1;
                total_l += abs(lhead_scan - right[lt2_c]);
                lhead_scan = right_l[lt2_c];
                //total_l += abs(lhead_scan - 299);
                printf("%i ,", lhead_scan);
                //lhead_scan = 299;
                i = i + 1;
            }
        }
    }

    printf("\n \nLOOK - Total Head Movements = %i \n",total_l);  


    // ********************************************************************************
    // C-LOOK

    int cltotal_sc = 0;
    int clleft_sc[CYLINDERS] = {0};
    int clright_sc[CYLINDERS] = {0};
    int clt1_sc = 0;
    int clt2_sc = 0;
    int clhead_sc = head; 
    int cldir_sc = -1;
    printf("\nC-LOOK DISK SCHEDULING ALGORITHM\n \n");
    if (strcmp("LEFT",direction) != 0 ){
        cldir_sc = 1;
    }
    for (int i = 0; i < CYLINDERS; i++){
        int temp = sorted_requests[i];
        if(temp < clhead_sc){
            clleft_sc[clt1_sc] = temp;
            clt1_sc += 1;
        } else if (temp > clhead_sc){
            clright_sc[clt2_sc] = temp;
            clt2_sc += 1;
        }
    }
    printf("%i ,", clhead_sc);
    if(cldir_sc == -1){
        for(int li = (t1_sc); li > 0; li = li - 1){
            cltotal_sc += abs(clhead_sc - clleft_sc[li - 1]);
            clhead_sc = clleft_sc[li -1];
            printf("%i ,", clhead_sc);
        }
        for(int li = (t2_sc); li > 0; li = li - 1){
            cltotal_sc += abs(clhead_sc - clright_sc[li - 1]);
            clhead_sc = clright_sc[li -1];
            printf("%i ,", clhead_sc);
        }
    }

    if(cldir_sc == 1){
        for(int li = 0; li < clt2_sc; li++){
            cltotal_sc += abs(clhead_sc - clright_sc[li]);
            clhead_sc = clright_sc[li];
            printf("%i ,", clhead_sc);
        }
        for(int li = 0; li < clt1_sc; li++){
            cltotal_sc += abs(clhead_sc - clleft_sc[li]);
            clhead_sc = clleft_sc[li];
            printf("%i ,", clhead_sc);
        }
    }
    printf("\n \nC-LOOK - Total Head Movements = %i \n",cltotal_sc);  

    // ********************************************************************************
    return 0;
}

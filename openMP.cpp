#include <iostream>
#include <omp.h>
#include <stdio.h>

using namespace std;

//explanation and examples of usage of OpenMP directives

int main() {

    cout << "set the number of threads: ";
    int threads = 0;
    cin >> threads;
    omp_set_num_threads(threads);
    #pragma omp parallel //parallelize block randomly
    {
        #pragma omp for //parallelize for loop by assinging threads in order
        for (int i = 0; i < 10; i++) {
            printf(" \n Thread %d handles iteration %d\n", 
                    omp_get_thread_num(), i);
        }

        #pragma omp barrier //this makes sure that all 
                            //threads finish the loop before proceeding

    }

    cout << "\n If you use less threads than there are iterations " <<
            "each thread will handle more iterations like 5 for 10 " <<
            "thread 0 handles iteration 0 and 1 " <<
            "thread 4 handles iteration 8 and 9\n";

    cout << "moving on to print hello world, another for loop, " <<
            "and hola mundo\n";
    cout << "\nNowait applied after hello world. " <<
            "Thread is free to continue other tasks and does not "<<
            "wait for all the others to finish in hello world\n";
    #pragma omp parallel
    {
        
        int ID = omp_get_thread_num();
        
        //printing parallelized hello world 
        
        printf("\nHello(%d)", ID);
        #pragma omp master //makes line below handled only once
                                   //by the master thread (0)
        printf("\n (master) World(%d)\n", ID);
       
        //for loop 
        #pragma omp for nowait //allows threads to contiue rather than waiting
        for (int i = 0; i < 5; i++) {
            printf("\nThread %d moved on to handle iteration %d\n", ID, i);
        }
        
        //printing parallelized hola mundo
        printf("\nhola(%d)", ID);

        #pragma omp single //makes line below handled only once
                           //by any single thread 
        printf("\n(single) mundo(%d)\n", ID);
    
    }

    //now using sectioning
    cout << "\n \n ***Now using sectioning***\n";
    cout << "   This is where an individual thread handles " <<
            "everything within a section block\n";
    #pragma omp parallel
    {

        int ID = omp_get_thread_num();
        
        #pragma omp sections
        {
            #pragma omp section
            {
            //printing parallelized hello world
                printf("\nHello(%d)", ID);
                printf("\nWorld(%d)\n", ID);
            }
            
            #pragma omp section
            {
                //for loop
                for (int i = 0; i < 5; i++) {
                printf("\nThread %d moved on to handle iteration %d\n", ID, i);
                }   
            }

            #pragma omp section
            {
                //printing parallelized hola mundo
                printf("\nhola(%d)", ID);
                printf("\nmundo(%d)\n", ID);
            }
    
        }
    }

    return 0;
}


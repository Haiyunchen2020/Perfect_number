//================================================================================
// Description : To check whether a number is a perfect number with multiprecesses
//================================================================================


#include <cstdio>
#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
#include <atomic>

using namespace std;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


/*Return Values*/
static const int PERFECT = 0;
static const int IMPERFECT = 1;
static const int FAILURE = -1;

static long long sum = 1ll;
atomic<bool> gotans (false);
vector<long long> factorList;

typedef struct{
    long long number;
    long long higher;
    long long lower;
} parameters;

void print_help(const char *progname){
    fprintf(stderr, "Usage: %s <NUMBER> <NUM_WORKERS>"
		"\nNUMBER: an integer greater than 1."
		"\nNUM_WORKERS: the number of worker threads (must be greater than 0).\n",
		progname);
}

void print_factorList(){
    cout << "FactorList: {";
    for (size_t i = 0; i < factorList.size() -1; i++)
    {
        cout << factorList[i] << ", " ;
    }
    cout << factorList[factorList.size() -1] << "}" << endl;
    
}

static void* sum_divisor_worker(void * param);

int main(int argc, char *argv[]) {
	auto start = chrono::high_resolution_clock::now();

    /*Check command line arguments validity*/
    long long number = stoll(argv[1]);
	int nthreads = stoi(argv[2]);
    if(argc < 3 || number < 2 || nthreads < 1 ){
            print_help(argv[0]);
            return FAILURE;
    }

    /* 1.  divide the work load to nthreads */
	/* 1.1 allocate variables to hold the information about work load */
	long long *higher = new long long[nthreads];
	long long *lower  = new long long[nthreads];

	/* 1.2 compute the amount of work load for each thread */
	long long load = number / nthreads;
	if (load == 0ll) load = 1ll;

	/* 1.3 divide the work load (from high to low) */
	higher[0] = number - 1ll;
	for (int i = 0; i < nthreads; i ++) {
		lower[i] = higher[i] - load;
		if (lower[i] < 1ll || i == nthreads - 1) {
            lower[i] = 1;
        }
		if (i < nthreads - 1) {
            higher[i+1] = lower[i];
        }
	}

    /*First, add the value '1' to the factorList, as it is always a factor of any number.*/
    factorList.push_back(1);

    pthread_t threads[nthreads];
    for (int i = 0; i < nthreads; i++)
    {
        parameters *data = (parameters *) malloc(sizeof(parameters));
        data->number =number;
        data->higher = higher[i];
        data->lower = lower[i];
        pthread_create(&threads[i],NULL,sum_divisor_worker,data);
    }

    for (int i = 0; i < nthreads; i++)
    {
        /*Check if sum so far exceeds the given number, if so, the program ends.*/
        if(gotans){
            print_factorList();
            cout << "Sum: " << sum << endl;
            cout << "The number is imperfect." << endl;
            auto finish = chrono::high_resolution_clock::now();
            cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns\n";
            return IMPERFECT;
        }
        pthread_join(threads[i],NULL);
    }
    
    /*If the final sum is not greater than the number, check if the sum matches the number.*/
    if(sum == number){
        print_factorList();
        cout << "Sum: " << sum << endl;
        cout << "The number is perfect." << endl;
        auto finish = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns\n";
        return PERFECT;
    }
    else{
        print_factorList();
        cout << "Sum: " << sum << endl;
        cout << "The number is imperfect." << endl;
        auto finish = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns\n";
        return IMPERFECT;
    }
}

static void * sum_divisor_worker(void * param){
        parameters *params = (parameters * ) param;
        for (long long divisor = params->higher; !gotans && divisor > params->lower; divisor --) {
        	if (params->number % divisor == 0) {
        	    pthread_mutex_lock(&mtx);

                factorList.push_back(divisor);
            	sum += divisor;

            	pthread_mutex_unlock(&mtx);
            }
            if (sum > params->number) {
                gotans = true;
                pthread_exit(NULL);
            }

        }
        pthread_exit(NULL);
}
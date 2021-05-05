#include <stdio.h>

int hystUP[] = {0, 15, 40, 65, 90};
int hystDN[] = {0, 10, 35, 60, 85};
int histHyst = -1;

int hysteresis(unsigned int input_percent){
	int idx = -1;

	unsigned int hystSize = sizeof(hystUP) / sizeof(int);

	if(histHyst >= 0) {
        if((input_percent >= hystDN[histHyst]) && (input_percent < hystUP[histHyst])) {
            return histHyst;
        }
	}

	for(int i=0; i<hystSize; i++){
	    if(input_percent >= hystUP[i]){
	        idx = i;
	        histHyst = i;
	    }
	}

	return idx;
}

int testSeq[] = {1, 9, 20, 10, 9, 25, 39, 40, 35, 42, 34};

int testMax = 99;

int main(int argc, char *argv[]){

	unsigned int testSize = sizeof(testSeq) /sizeof(int);

    setbuf(stdout, 0);

	printf("\npredefined: ");
	for(int i=0; i < testSize; i++){
		printf("\nfor %d hyst = %d ", testSeq[i], hysteresis(testSeq[i]));
	}

	printf("\nascending: ");
	for(int i=0; i < testMax; i++){
		printf("hyst(%d) = %d ", i, hysteresis(i));
	}

	printf("\nascending with fallback: ");
	int prevHyst = 0, fallback=8;
    for(int i=0; i < testMax; i++){
        int hyst = hysteresis(i);
        printf("hyst(%d) = %d ", i, hyst);
        if((hyst != prevHyst)){
            i-=fallback;
            fallback--;
        }
        prevHyst = hyst;
    }

    printf("\ndescending: ");
    for(int i=testMax; i > 0; i--){
        printf("hyst(%d) = %d ", i, hysteresis(i));
    }

    printf("\ndescending with fallback: ");
    prevHyst = 0, fallback=8;
    for(int i=testMax; i > 0; i--){
        int hyst = hysteresis(i);
        printf("hyst(%d) = %d ", i, hyst);
        if((hyst != prevHyst)){
            i+=fallback;
            fallback--;
        }
        prevHyst = hyst;
    }

    printf("\n");
	return 0;
}

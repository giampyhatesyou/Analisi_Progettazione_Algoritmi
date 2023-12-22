#include <stdio.h>
#include <stdlib.h>

int power_mod(int base, int exponent, int modulus) {
    int res = 1;
    for(int i = 0; i < exponent; i++) {
        res = (res * base) % modulus;
    }
    return res;
}


int mcd(int a, int b) {
    int resto;

    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

int ordine(int m) {
    int count = 0;
    for(int a=2; a<m; a++) {
        if(mcd(a,m) == 1)
            count++;
    }
    return count;
}

void MCPrimalityTest(int n) {
    int s = 0;
    int q = n - 1;

    while (q % 2 == 0) {
        s++;
        q = q / 2;
    }

    int* bugiardi = NULL;
    int bugiardicount = 0;

    for (int a = 2; a < n - 1; a++) {
        int x = power_mod(a, q, n);

        if (x == 1 || x == n - 1) {
            bugiardi = (int*)realloc(bugiardi, (bugiardicount + 1) * sizeof(int));
            bugiardi[bugiardicount++] = a;
            continue;
        }

        for (int i = 0; i < s; i++) {
            x = power_mod(x, 2, n);
            if (x == n - 1) {
                bugiardi = (int*)realloc(bugiardi, (bugiardicount + 1) * sizeof(int));
                bugiardi[bugiardicount++] = a;
                break;
            }
        }
    }

    printf("falsi testimoni per %d:\n", n);
    for (int i = 0; i < bugiardicount; i++) {
        printf("%d ", bugiardi[i]);
    }
    printf("\n");

    free(bugiardi);

    float falsi = (float)bugiardicount / n;
    falsi = falsi * 100;
    printf("\Frazione dei falsi testimoni testimoni per %d: %d / %d = %f%\n", n, bugiardicount, n, falsi);
    printf("Ordine per %d: %d\n", n, ordine(n));


    if ((falsi / 100) < 0.5) {
        printf("%d è composto\n", n);  // La frazione di testimoni non è maggiore del 50%
    } else {
        printf("%d è probabilmente primo\n", n);  // La frazione di testimoni è maggiore del 50%
    }
}

int main() {
    int n[3] = {999, 1003, 1027};  // Esempio di numero composto dispari

    printf("TEST PER NUMERI COMPOSTI DISPARI \n");

	for(int i=0; i<3; i++) {
		printf("Analisi dei ", n[i]);
		MCPrimalityTest(n[i]);
		printf("\n\n");
	}

    return 0;
}

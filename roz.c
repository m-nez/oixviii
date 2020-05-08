#include <stdio.h>

#define IDX(x) (x - 'a')

int main(int argc, char** argv) {
    int n;
    scanf("%d", &n);
    char word[n+1];
    scanf("%s", word);

    int n_letters = 26;
    int current[n_letters][n_letters];
    int beg[n_letters][n_letters];
    int end[n_letters][n_letters];
    int max[n_letters][n_letters];
    int maxbeg[n_letters][n_letters];
    int maxend[n_letters][n_letters];
    int letters_present[n_letters];

    for (int i = 0; i < n_letters; ++i) {
        for (int j = 0; j < n_letters; ++j) {
            current[i][j] = 0;
            maxbeg[i][j] = 0;
            maxend[i][j] = 0;
            beg[i][j] = 0;
            end[i][j] = 0;
            max[i][j] = 0;
        }
        letters_present[i] = 0;
    }

    int idx;
    idx = IDX(word[0]);
    letters_present[idx] = 1;
    for (int i = 0; i < n_letters; ++i) {
        current[idx][i]++;
        current[i][idx]--;
        max[idx][i]++;
        max[i][idx]--;
    }

    for (int i = 1; i < n; ++i) {
        idx = IDX(word[i]);
        letters_present[idx] = 1;
        for (int j = 0; j < n_letters; ++j) {
            if (current[idx][j] < 0) {
                current[idx][j] = 1;
                beg[idx][j] = i;
            } else {
                current[idx][j]++;
            }
            current[j][idx]--;
            if (current[idx][j] >= max[idx][j]) {
                max[idx][j] = current[idx][j];
                maxend[idx][j] = i;
                maxbeg[idx][j] = beg[idx][j];
            }
        }
    }

    int argmax_i = -10;
    int argmax_j = -10;
    int total_max = -10;


    for (int i = 0; i < n_letters; ++i) {
        for (int j = 0; j < n_letters; ++j) {
            int ok = 0;
            for (int k = maxbeg[i][j]; k <= maxend[i][j]; ++k) {
                if (IDX(word[k]) == j) {
                    ok = 1;
                    break;
                }
            }
            if (!ok) {
                max[i][j]--;
            }
            if (max[i][j] > total_max && i != j && letters_present[j]) {
                argmax_i = i;
                argmax_j = j;
                total_max = max[i][j];
            }
        }
    }
    if (total_max < 0) {
        total_max = 0;
    }
    printf("%d\n", total_max);
}

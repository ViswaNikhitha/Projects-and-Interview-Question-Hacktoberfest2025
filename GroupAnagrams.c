#include <stdlib.h>
#include <string.h>

int cmpChar(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

char *sortedKey(const char *s) {
    int len = strlen(s);
    char *key = (char *)malloc(len + 1);
    strcpy(key, s);
    qsort(key, len, sizeof(char), cmpChar);
    return key;
}

char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    char ***result = (char ***)malloc(sizeof(char **) * strsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * strsSize);
    char **keys = (char **)malloc(sizeof(char *) * strsSize);
    int groupCount = 0;

    for (int i = 0; i < strsSize; i++) {
        char *key = sortedKey(strs[i]);
        int found = 0;
        for (int j = 0; j < groupCount; j++) {
            if (strcmp(keys[j], key) == 0) {
                int col = (*returnColumnSizes)[j];
                result[j] = (char **)realloc(result[j], sizeof(char *) * (col + 1));
                result[j][col] = strs[i];
                (*returnColumnSizes)[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            keys[groupCount] = key;
            result[groupCount] = (char **)malloc(sizeof(char *));
            result[groupCount][0] = strs[i];
            (*returnColumnSizes)[groupCount] = 1;
            groupCount++;
        } else {
            free(key);
        }
    }

    *returnSize = groupCount;
    return result;
}

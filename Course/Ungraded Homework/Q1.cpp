#include <iostream>

using namespace std;

struct TweetData {

    int size = 0;
    char **keyWords = new char* [1];
    int **IDs = new int* [1];

};

int strlen(char *str) {

    int length = 0;

    for (; str[length] != '\0'; length++);

    return length;
}

bool strcmp(char *str1, char *str2) {
    
    for (int i = 0; str1[i] != '\0'; i++)
        if (str1[i] != str2[i])
            return false;

    return true;

}

void strcpy(char *str1, char *str2, int len) {

    for (int i = 0; i < len; i++)
        str1[i] = str2[i];

    str1[len] = '\0';

}

TweetData createIndex(char **tweets, int n) {

    TweetData data;

    for (int i = 0; i < n; i++) {

        int start = 0;

        for (int j = 0; ; j++)
            if (tweets[i][j] == ' ' || tweets[i][j] == '\0') {

                int indexID = -1;

                for (int k = 0; (indexID == -1) && (k < data.size); k++)
                    if (strcmp(data.keyWords[k], tweets[i] + start))
                        indexID = k;

                if (indexID == -1) {
                    
                    char **tempArray = new char* [++data.size];
                    int **tempID = new int* [data.size];

                    for (int k = 0; k < data.size - 1; k++) {
                        tempID[k] = data.IDs[k];

                        tempArray[k] = new char [strlen(data.keyWords[k]) + 1] {};
                        strcpy(tempArray[k], data.keyWords[k], strlen(data.keyWords[k]));
                    }

                    delete[] data.keyWords;
                    delete[] data.IDs;

                    data.keyWords = tempArray;
                    data.IDs = tempID;

                    data.keyWords[data.size - 1] = new char [j - start + 1] {};
                    data.IDs[data.size - 1] = new int [2] {i + 1, -1};

                    strcpy(data.keyWords[data.size - 1], tweets[i] + start, j - start);

                } else if (indexID != -1) {

                    int subArrayLength = 0;
                    for (; data.IDs[indexID][subArrayLength] != -1; subArrayLength++);
                    subArrayLength++;

                    if (data.IDs[indexID][subArrayLength - 2] != (i + 1)) {

                        int *IDSubArray = new int [subArrayLength + 1];

                        for (int k = 0; k < subArrayLength; k++)
                            IDSubArray[k] = data.IDs[indexID][k];

                        IDSubArray[subArrayLength - 1] = i + 1;
                        IDSubArray[subArrayLength] = -1;

                        delete[] data.IDs[indexID];
                        data.IDs[indexID] = IDSubArray;

                    }

                }

                if (tweets[i][j] == '\0')
                    break;

                start = j + 1;

            }

    }

    return data;

}

int main() {

    int n;
    char **tweets;
    TweetData data;

    cout << "Enter Number of Tweets: ";
    cin >> n;
    cin.ignore();
    cout << endl;

    tweets = new char* [n];

    for (int i = 0; i < n; i++) {

        int length = 1;
        tweets[i] = new char [1] {};

        cout << "Enter Tweet " << i + 1 << ": ";

        for (; ; length++) {

            char *temp = new char [length + 1] {};

            tweets[i][length - 1] = cin.get();
            strcpy(temp, tweets[i], length);

            delete[] tweets[i];
            tweets[i] = temp;

            if (tweets[i][length - 1] == '\n') {
                tweets[i][length - 1] = '\0';
                break;
            }

        }

    }

    cout << endl;

    data = createIndex(tweets, n);

    for (int i = 0; i < data.size; i++) {

        cout << "Key Word: " << data.keyWords[i] << endl;
        cout << "Tweets: ";

        for (int j = 0; data.IDs[i][j] != -1; j++)
            cout << data.IDs[i][j] << " ";

        cout << endl << endl;

    }

    for (int i = 0; i < data.size; i++)
        delete[] data.keyWords[i], delete[] data.IDs[i];

    for (int i = 0; i < n; i++)
        delete[] tweets[i];

    delete[] tweets;
    delete[] data.keyWords;
    delete[] data.IDs;

    return 0;

}
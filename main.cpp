//#define DEBUG_PRINT;

#include <iostream>

const int BITMAP  = 8;
const int MAX_MESSAGE_LENGTH = BITMAP * 2000;
const int CHUNK_SIZE = 512;
const int MESSAGE_SCHEDULE_ARRAY_SIZE = 2048;
const int MSA_WORD_SIZE = 32;

const unsigned int INITIAL_HASH_VALUES[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

const unsigned int ROUNDING_CONSTANTS[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int pow2(int a) {
    int result = 1;
    for(int i = 0; i < a; i++) {
        result *= 2;
    }
    return result;
}

char* addArr(const char arr1[], const char arr2[]) {
    char* newBits = new char[MSA_WORD_SIZE], leftover = '0';
    for(int i = MSA_WORD_SIZE - 1; i >= 0; i--) {
        if(arr1[i] == '1') {
            if(arr2[i] == '1') {
                if(leftover == '1') {
                    newBits[i] = '1';
                    leftover = '1';
                }
                else {
                    newBits[i] = '0';
                    leftover = '1';
                }
            }
            else {
                if(leftover == '1') {
                    newBits[i] = '0';
                    leftover = '1';
                }
                else {
                    newBits[i] = '1';
                    leftover = '0';
                }
            }
        }
        else {
            if(arr2[i] == '1') {
                if(leftover == '1') {
                    newBits[i] = '0';
                    leftover = '1';
                }
                else {
                    newBits[i] = '1';
                    leftover = '0';
                }
            }
            else {
                if(leftover == '1') {
                    newBits[i] = '1';
                    leftover = '0';
                }
                else {
                    newBits[i] = '0';
                    leftover = '0';
                }
            }
        }
    }


    return newBits;
}

char* andArr(const char arr1[], const char arr2[]) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = 0; i < MSA_WORD_SIZE; i++) {
        newBits[i] = arr1[i] == '1' && arr2[i] == '1' ? '1' : '0';
    }
    return newBits;
}

char* notArr(const char arr[]) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = 0; i < MSA_WORD_SIZE; i++) {
        newBits[i] = arr[i] == '0' ? '1' : '0';
    }
    return newBits;
}

char* xorArr(const char arr1[], const char arr2[]) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = 0; i < MSA_WORD_SIZE; i++) {
        if(arr1[i] == '0') {
            if(arr2[i] == '0') {
                newBits[i] = '0';
            }
            else {
                newBits[i] = '1';
            }
        }
        else {
            if(arr2[i] == '0') {
                newBits[i] = '1';
            }
            else {
                newBits[i] = '0';
            }
        }
    }
    return newBits;
}

char* rightShift(const char bits[], const int start, const int times) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = 0; i < times; i++) {
        newBits[i] = '0';
    }
    for(int i = times; i < MSA_WORD_SIZE; i++) {
        newBits[i] = bits[start + i - times];
    }
    return newBits;
}

char* rightRotate(const char bits[], const int start, const int times) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = 0, end = start + MSA_WORD_SIZE; i < times; i++) {
        newBits[i] = bits[end - times + i];
    }
    for(int i = times; i < MSA_WORD_SIZE; i++) {
        newBits[i] = bits[start + i - times];
    }
    return newBits;
}

void print(const char bits[], const int count, const int spacing, const int newline, const bool indexing) {
    for(int i = 0, counter = 0; i < count; i++) {
        if(indexing && i % (newline * spacing) == 0) {
            std::cout << "w" << counter << " " << (counter < 10 ? " " : "");
            counter++;
        }
        std::cout << bits[i];
        if(newline != 0 && (i + 1) % (newline * spacing) == 0) {
            std::cout << std::endl;
        }
        else {
            if(spacing > 0 && (i + 1) % spacing == 0) {
                std:: cout << " ";
            }
        }
    }
    std::cout << std::endl;
}

void print(const char bits[], const int start, const int end) {
    for(int i = start; i < end; i++) {
        std::cout << bits[i];
    }
    std::cout << std::endl;
}

void printHashVar(const char arr[]) {
    for(int i = 0; i < MSA_WORD_SIZE; i += 4) {
        int number = ((arr[i] - '0') * pow2(3)) + ((arr[i + 1] - '0') * pow2(2)) + ((arr[i + 2] - '0') * pow2(1)) + (arr[i + 3] - '0');
        if(number < 10) {
            std::cout << (char)(number + '0');
        }
        else {
            std::cout << (char)(number - 10 + 'a');
        }
    }
}

char *intToBinaryChar(unsigned int value) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = MSA_WORD_SIZE - 1; i >= 0; i--) {
        newBits[i] = (char)((value % 2) + '0');
        value /= 2;
    }
    return newBits;
}

char *extractWord(const char messageSchedule[], int ind) {
    char* newBits = new char[MSA_WORD_SIZE];
    for(int i = 0; i < MSA_WORD_SIZE; i++) {
        newBits[i] = messageSchedule[(ind * MSA_WORD_SIZE) + i];
    }
    return newBits;
}

char *copyCharArr(const char arr1[], int length) {
    char* newBits = new char[length];
    for(int i = 0; i < length; i++) {
        newBits[i] = arr1[i];
    }
    return newBits;
}

void moveArr(char arr1[], const char arr2[], int length) {
    for(int i = 0; i < length; i++) {
        arr1[i] = arr2[i];
    }
}

void fillMessageBlock(const char text[], char messageBlock[], int &length) {
    length = 0;
    for(int i = 0; text[i] != '\0'; i++) {
        unsigned int charDec = (int)text[i];
        int temp = ((i+1) * BITMAP) - 1;
        do {
            messageBlock[temp] = (char)((charDec % 2) + '0');
            charDec /= 2;
            temp--;
            length++;
        } while(charDec != 0);
        while(temp >= (i * BITMAP)) {
            messageBlock[temp] = '0';
            temp--;
            length++;
        }
    }
    int charsBinaryCount = length;
    messageBlock[length++] = '1';

    while((length+64) % CHUNK_SIZE != 0) {
        messageBlock[length++] = '0';
    }

    for(int i = 0; i < 64; i++) {
        messageBlock[length++] = '0';
    }

    for(int tempInd = length-1; charsBinaryCount != 0; charsBinaryCount /= 2, tempInd--) {
        messageBlock[tempInd] = (char)((charsBinaryCount % 2) + '0');
    }
}

void fillMessageScheduleArray(const char messageBlock[], const int messageBlockLength, char messageSchedule[]) {
    char *h0 = intToBinaryChar(INITIAL_HASH_VALUES[0]), *h1 = intToBinaryChar(INITIAL_HASH_VALUES[1]),
    *h2 = intToBinaryChar(INITIAL_HASH_VALUES[2]), *h3 = intToBinaryChar(INITIAL_HASH_VALUES[3]),
    *h4 = intToBinaryChar(INITIAL_HASH_VALUES[4]), *h5 = intToBinaryChar(INITIAL_HASH_VALUES[5]),
    *h6 = intToBinaryChar(INITIAL_HASH_VALUES[6]), *h7 = intToBinaryChar(INITIAL_HASH_VALUES[7]);

    for(int i = 0; i < messageBlockLength / CHUNK_SIZE; i ++) {
        for(int j = 0; j < CHUNK_SIZE; j++) {
            messageSchedule[j] = messageBlock[(i * CHUNK_SIZE) + j];
        }
        for(int j = CHUNK_SIZE; j < MESSAGE_SCHEDULE_ARRAY_SIZE; j++) {
            messageSchedule[j] = '0';
        }
        for(int j = 16; j < 64; j++) {
            char *sigma0 = xorArr(
                    xorArr(
                            rightRotate(messageSchedule, (j - 15) * MSA_WORD_SIZE, 7),
                            rightRotate(messageSchedule, (j - 15) * MSA_WORD_SIZE, 18)
                    ),
                    rightShift(messageSchedule, (j - 15) * MSA_WORD_SIZE, 3)
            );

            char *sigma1 = xorArr(
                    xorArr(
                            rightRotate(messageSchedule, (j - 2) * MSA_WORD_SIZE, 17),
                            rightRotate(messageSchedule, (j - 2) * MSA_WORD_SIZE, 19)
                    ),
                    rightShift(messageSchedule, (j - 2) * MSA_WORD_SIZE, 10)
            );

            char *wA = new char[MSA_WORD_SIZE];
            char *wB = new char[MSA_WORD_SIZE];
            for(int k = 0; k < MSA_WORD_SIZE; k++) {
                wA[k] = messageSchedule[((j - 16) * MSA_WORD_SIZE) + k];
                wB[k] = messageSchedule[((j - 7) * MSA_WORD_SIZE) + k];
            }

            char *result = addArr(addArr(addArr(wA, sigma0), wB), sigma1);

            for(int k = 0; k < MSA_WORD_SIZE; k++) {
                messageSchedule[(j * MSA_WORD_SIZE) + k] = result[k];
            }

            delete[] sigma0; delete[] sigma1; delete[] wA; delete[] wB; delete[] result;
        }
        char *a = copyCharArr(h0, MSA_WORD_SIZE), *b = copyCharArr(h1, MSA_WORD_SIZE),
        *c = copyCharArr(h2, MSA_WORD_SIZE), *d = copyCharArr(h3, MSA_WORD_SIZE),
        *e = copyCharArr(h4, MSA_WORD_SIZE), *f = copyCharArr(h5, MSA_WORD_SIZE),
        *g = copyCharArr(h6, MSA_WORD_SIZE), *h = copyCharArr(h7, MSA_WORD_SIZE);
        for(int q = 0; q < MESSAGE_SCHEDULE_ARRAY_SIZE / MSA_WORD_SIZE; q++) {
            char *sum0 = xorArr(xorArr(rightRotate(a, 0, 2), rightRotate(a, 0, 13)), rightRotate(a, 0, 22));
            char *sum1 = xorArr(xorArr(rightRotate(e, 0, 6), rightRotate(e, 0, 11)), rightRotate(e, 0, 25));
            char *majority = xorArr(xorArr(andArr(a, b), andArr(a, c)), andArr(b, c));
            char *choice = xorArr(andArr(e, f), andArr(notArr(e), g));
            char *temp1 = addArr(
                    addArr(
                            addArr(
                                    addArr(h, sum1),
                                    choice),
                            intToBinaryChar(ROUNDING_CONSTANTS[q])
                    ),
                    extractWord(messageSchedule, q)
            );
            char *temp2 = addArr(sum0, majority);
            //    std::cout << "sum0: "; print(sum0, 32, 0, 0, 0);
            //    std::cout << "sum1: "; print(sum1, 32, 0, 0, 0);
            //    std::cout << "maj: "; print(majority, 32, 0, 0, 0);
            //    std::cout << "ch: "; print(choice, 32, 0, 0, 0);
            //    std::cout << "temp1: "; print(temp1, 32, 0, 0, 0);
            //    std::cout << "temp2: "; print(temp2, 32, 0, 0, 0);

            moveArr(h, g, MSA_WORD_SIZE);
            moveArr(g, f, MSA_WORD_SIZE);
            moveArr(f, e, MSA_WORD_SIZE);
            e = addArr(d, temp1);
            moveArr(d, c, MSA_WORD_SIZE);
            moveArr(c, b, MSA_WORD_SIZE);
            moveArr(b, a, MSA_WORD_SIZE);
            a = addArr(temp1, temp2);

            delete[] sum0; delete[]sum1; delete[] majority; delete[] choice; delete[] temp1; delete[] temp2;
        }
        h0 = addArr(h0, a);
        h1 = addArr(h1, b);
        h2 = addArr(h2, c);
        h3 = addArr(h3, d);
        h4 = addArr(h4, e);
        h5 = addArr(h5, f);
        h6 = addArr(h6, g);
        h7 = addArr(h7, h);

        delete[] a; delete[] b; delete[] c; delete[] d; delete[] e; delete[] f; delete[] g; delete[] h;
    }

    printHashVar(h0);
    printHashVar(h1);
    printHashVar(h2);
    printHashVar(h3);
    printHashVar(h4);
    printHashVar(h5);
    printHashVar(h6);
    printHashVar(h7);
    std::cout << std::endl;

    delete[] h0; delete[] h1; delete h2; delete[] h3; delete[] h4; delete[] h5; delete[] h6; delete[] h7;
}

void printSHA(const char text[]) {
    int messageBlockLength;
    char* messageBlock = new char[MAX_MESSAGE_LENGTH];

    fillMessageBlock(text, messageBlock, messageBlockLength);
    char messageSchedule[MESSAGE_SCHEDULE_ARRAY_SIZE];

//    std::cout << "messageBlockLength: " << messageBlockLength << std::endl;
//    print(messageBlock, messageBlockLength, 512, 512, false);
    fillMessageScheduleArray(messageBlock, messageBlockLength, messageSchedule);

//    print(messageSchedule, MESSAGE_SCHEDULE_ARRAY_SIZE, MSA_WORD_SIZE, 1, true);

    delete[] messageBlock;
}

int main() {
    char text[MAX_MESSAGE_LENGTH];
    std::cin.getline(text, MAX_MESSAGE_LENGTH);
//    char text[] = {"mEjHl9M144giSnyzSUtsmEjHl9M144giSnyzSUts4giSnyzSUtsSUtdd"};
    printSHA(text);
    return 0;
}
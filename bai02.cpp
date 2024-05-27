#include <iostream>
#include <stdio.h>

using namespace std;

class myexception: public exception{
    virtual const char* what() const throw(){
        return "could not memory allocation";
    }
} myex;

class myexception1: public exception{
    virtual const char* what() const throw(){
        return "could not read file";
    }
} myex1;

class myexception2: public exception{
    virtual const char* what() const throw(){
        return "could not write file";
    }
} myex2;

struct Player {
    char playerId [20];
    int HP ;
    int MP ;
    int gold ;
};

Player * inputPlayerList ( int & n ) {
    cout << "enter quantity player is ";
    cin >> n;

    Player* playerList = new (nothrow) Player [n];

    if (!playerList){
        throw myex;
    }

    for (int i = 0; i < n; i++){
        cout << "Enter ID player: ";
        cin >> playerList[i].playerId;
        cout << "enter HP player: ";
        cin >> playerList[i].HP;
        cout << "Enter MP player: ";
        cin >> playerList[i].MP;
        cout << "enter gold player: ";
        cin >> playerList[i].gold;
    }

    return playerList;
}

void savePlayerList ( const char * fileName , Player * playerList , int n ) {
    FILE* wF = fopen(fileName, "wb");

    if(!wF){ 
        throw myex2;
    }

    fwrite(&n, sizeof(int), 1, wF);
    fwrite(playerList, sizeof(Player) * n, 1, wF);

    fclose(wF);
    wF = nullptr;
}

Player * loadPlayerList ( const char * fileName , int & n ) {
    FILE* rF = fopen(fileName, "rb");

    if(!rF){ 
        throw myex1;
    }

    fread(&n, sizeof(int), 1, rF);

    Player* playerList = new (nothrow) Player [n];

    if (!playerList){
        throw myex;
    }

    fread(playerList, sizeof(Player) * n, 1, rF);

    fclose(rF);
    rF = nullptr;

    return playerList;
}

int * maxSlainPossible ( Player * playerList , int n ) {
    int* maxSlain = new (nothrow) int [n] {0};

    if (!maxSlain){
        throw myex;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (playerList[i].HP > playerList[j].HP && playerList[i].MP > playerList[j].MP){
                maxSlain[i]++;
            }
        }
    }

    return maxSlain;
}

void writeWinnerList ( const char * winnerFile , Player * playerList , int n ) {
    int* maxSlain = maxSlainPossible(playerList, n);
    int max = 0;
    int count = 1;
    int pos = -1;

    int* tmp = new (nothrow) int [n] {0};

    if (!tmp){
        throw myex;
    }

    FILE* wF = fopen(winnerFile, "wb");

    if (!wF){
        throw myex2;
    }

    for (int i = 0; i < n; i++){
        if (max < playerList[i].gold * maxSlain[i]){
            max = playerList[i].gold * maxSlain[i];
            pos = i;
        }
    }

    for (int i = 0; i < n; i++){
        if (max == playerList[i].gold * maxSlain[i] && pos != i){
            count++;
            tmp[i] = 1;
        }
    }

    fwrite(&count, sizeof(int), 1, wF);

    for (int i = 0; i < n; i++){
        if (tmp[i] == 1 && pos != i){
            fwrite(&playerList[i], sizeof(Player), 1, wF);
        }
    }

    delete[] maxSlain;
    maxSlain = nullptr;

    delete[] tmp;
    tmp = nullptr;

    fclose(wF);
    wF = nullptr;
}

int main () {
    return 0;
}
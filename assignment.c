//
// Assignment – Cody MacDonald
//
#include <time.h>

struct patient {
    int ID;
    char fullName[32];
    int age;
    float weightKG;
    float heightM;
    char notes[128];
    time_t admissionTime;
};

struct database{
    struct patient patients[64];
    int numPatients;
};

int main(){

    return 0;
}
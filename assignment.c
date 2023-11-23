//
// Assignment – Cody MacDonald
//
#include <stdio.h>
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

//Function Prototypes
struct database add_patient(struct database database);
void display_patient(struct database database);

int main(){
    struct database SouthLake;

    SouthLake = add_patient(SouthLake);
    SouthLake = add_patient(SouthLake);

    return 0;
}

struct database add_patient(struct database database){
    // Adding ID
    printf("Patient ID: ");
    scanf("%d", &database.patients[database.numPatients].ID);
    while(getchar() != '\n'); // Buffer Clear

    // Adding Full Name
    printf("Patient Full Name: ");
    scanf(" %[^\n]", &database.patients[database.numPatients].fullName[0]);
    while(getchar() != '\n'); // Buffer Clear

    // Adding Age
    printf("Patient Age: ");
    scanf("%d", &database.patients[database.numPatients].age);
    while(getchar() != '\n'); // Buffer Clear

    // Adding Weight (Kg)
    printf("Patient Weight (Kg): ");
    scanf("%f", &database.patients[database.numPatients].weightKG);
    while(getchar() != '\n'); // Buffer Clear

    // Adding Height (m)
    printf("Patient Height (m): ");
    scanf("%f", &database.patients[database.numPatients].heightM);
    while(getchar() != '\n'); // Buffer Clear

    // Adding Notes
    printf("Patient Notes: ");
    scanf(" %[^\n]", &database.patients[database.numPatients].notes[0]);
    while(getchar() != '\n'); // Buffer Clear

    // Adding Admittance Time
    database.patients[database.numPatients].admissionTime = time(NULL); // Stores a time (seconds?) but not in a readable format

    // Incrementing number of patients in database
    database.numPatients++;

    return database;
}
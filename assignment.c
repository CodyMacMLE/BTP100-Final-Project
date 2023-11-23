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
    struct database SouthLake=
                { { {10, "Edmond Honda", 33, 137, 1.85, "Patient came complaining about pain in his lower abdomen.", 1698160342},
                {20, "Chun Li", 28, 62, 1.70, "Patient came complaining about heart palpitations.", 1698430342},
                {30, "Dhalsim", 41, 48, 1.76, "Patient has had a fever for the past three days.", 1698340342} ,
                {40, "Ryu", 31, 76, 1.80, "Patient has not had a bowel movement in the past 6 days.", 1698250342}
                },
              4 };

    SouthLake = add_patient(SouthLake);

    display_patient(SouthLake);

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

void display_patient(struct database database){
    int patientID;
    int patientIndex;

    // Asking user what patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);
    while(getchar() != '\n'); // Buffer Clear

    // Iterating through patient IDs in database until match and saving index in PatientIndex
    for (int i = 0; i < database.numPatients; i++) {
        if(patientID == database.patients[i].ID){
            patientIndex = i;
        }
    }

    // Displaying Patient
    printf("Patient Information\n");
    printf("Patient ID: %d\n", database.patients[patientIndex].ID);
    printf("Patient Name: %s\n", database.patients[patientIndex].fullName);
    printf("Patient Age: %d\n", database.patients[patientIndex].age);
    printf("Patient Weight (Kg): %.2f\n", database.patients[patientIndex].weightKG);
    printf("Patient Height (m): %.2f\n", database.patients[patientIndex].heightM);
    printf("Patient Notes: %s\n", database.patients[patientIndex].notes);
    printf("Patient Admittance Time: %s\n", ctime(&database.patients[patientIndex].admissionTime));
}
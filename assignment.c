//
// Assignment – Cody MacDonald
//
#include <stdio.h>
#include <time.h>
#include <string.h>

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
void clear_buffer();
struct database add_patient(struct database database);
void display_patient(struct database database);
int check_ID(int patientID, struct database database); // flag: 1 if retrieved, 0 if failed
int get_Patient_Index(int patientID, struct database database);
struct database add_notes(struct database database);
int save_database(struct database database, const char file_name[]); // flag: 1 if saved, 0 if failed
int retrieve_database(struct database *database, const char file_name[]); // flag: 1 if retrieved, 0 if failed
int remove_patient(struct database *database); // flag: 1 if removed, 0 if failed
void display_patients_by_admission_date(struct database database);
void print_patient(struct database database, int index);

int main(){
    int menuFlag = 1;
    int menuSelection;
    int saveFlag;
    int retrieveFlag;
    int deleteFlag;
    //struct database SouthLake;

    struct database SouthLake=
                {{  {10, "Edmond Honda", 33, 137, 1.85, "Patient came complaining about pain in his lower abdomen.", 1698160342},
                            {20, "Chun Li", 28, 62, 1.70, "Patient came complaining about heart palpitations.", 1698430342},
                            {30, "Dhalsim", 41, 48, 1.76, "Patient has had a fever for the past three days.", 1698340342} ,
                            {40, "Ryu", 31, 76, 1.80, "Patient has not had a bowel movement in the past 6 days.", 1698250342}},
                  4};

    printf("------------------------------------------\n");
    printf("Welcome to the Southlake Hospital Database\n");
    do {
        // Printing Menu + User Input
        printf("------------------------------------------\n");
        printf("1) Add a Patient\n2) Display a Patient\n"
               "3) Add Patient Note\n4) Remove Patient\n"
               "5) Sort & Display by Admission Time\n6) Retrieve Database\n"
               "7) Save Database\n7) Close Database\n"
               "Enter Option: ");
        scanf("%d", &menuSelection);
        clear_buffer();
        printf("------------------------------------------\n");

        // Menu Options
        switch (menuSelection) {
            case 1:
                SouthLake = add_patient(SouthLake);
                break;
            case 2:
                display_patient(SouthLake);
                break;
            case 3:
                SouthLake = add_notes(SouthLake);
                break;
            case 4:
                deleteFlag = remove_patient(&SouthLake);
                if(deleteFlag){
                    printf("Patient successfully deleted\n");
                }
                break;
            case 5:
                display_patients_by_admission_date(SouthLake);
                break;
            case 6:
                retrieveFlag = retrieve_database(&SouthLake, "southlake.csv");
                if(retrieveFlag){
                    printf("Database successfully retrieved\n");
                } else {
                    printf("Error: Database could not be retrieved\n");
                }
                break;
            case 7:
                saveFlag = save_database(SouthLake, "southlake.csv");
                if(saveFlag){
                    printf("Database saved successfully\n");
                } else {
                    printf("Error: Database could not be saved\n");
                }
                break;
            case 8:
                printf("Closing Southlake Database");
                menuFlag = 0;
                break;
            default:
                printf("Error: Not a Valid Option (Please Enter an Integer)\n");
        }
    } while(menuFlag);

    return 0;
}

struct database add_patient(struct database database){
    int checkIDflag = 1;
    if (database.numPatients < 64){
        // Adding ID
        do {
            printf("Patient ID: ");
            scanf("%d", &database.patients[database.numPatients].ID);
            clear_buffer(); // Buffer Clear
            checkIDflag = check_ID(database.patients[database.numPatients].ID, database); // Checking if ID exists
            if (checkIDflag == 1){
                printf("Error: Another patient has inputted ID\n");
            }

        } while (checkIDflag == 1); // Exits when unique ID has been entered

        // Adding Full Name
        printf("Patient Full Name: ");
        scanf(" %[^\n]", &database.patients[database.numPatients].fullName[0]);
        clear_buffer();

        // Adding Age
        printf("Patient Age: ");
        scanf("%d", &database.patients[database.numPatients].age);
        clear_buffer();

        // Adding Weight (Kg)
        printf("Patient Weight (Kg): ");
        scanf("%f", &database.patients[database.numPatients].weightKG);
        clear_buffer();

        // Adding Height (m)
        printf("Patient Height (m): ");
        scanf("%f", &database.patients[database.numPatients].heightM);
        clear_buffer();

        // Adding Notes
        printf("Patient Notes: ");
        scanf(" %[^\n]", &database.patients[database.numPatients].notes[0]);
        clear_buffer();

        // Adding Admittance Time
        database.patients[database.numPatients].admissionTime = time(NULL); // Stores a time (seconds?) but not in a readable format

        // Incrementing number of patients in database
        database.numPatients++;
    }
    else {
        printf("Error: Database has reached max size\n");
    }

    return database;
}

void display_patient(struct database database){
    int patientID;
    int patientIndex;
    int checkIDflag = 0;

    // Asking user what patient ID
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);
    clear_buffer();

    // Using Check_ID to see if ID exists
    checkIDflag = check_ID(patientID, database);
    if(checkIDflag == 1){ // If ID exists
        // Translating ID to Index
        patientIndex = get_Patient_Index(patientID, database);
        // Displaying Patient
        print_patient(database, patientIndex);
    } else { // If ID does not exist
        printf("Error: Patient does not exist with ID %d\n", patientID);
    }
}

int check_ID(int patientID, struct database database){
    int flag = 0;
    for (int i = 0; i < database.numPatients; i++) {
        if(patientID == database.patients[i].ID){
            flag = 1;
        }
    }
    return flag;
}

int get_Patient_Index(int patientID, struct database database){
    int patientIndex;
    for (int i = 0; i < database.numPatients; i++) {
        if(patientID == database.patients[i].ID){
            patientIndex = i;
        }
    }
    return patientIndex;
}

struct database add_notes(struct database database){
    int patientID;
    char tempNote[128] = "; ";

    printf("Enter Patient ID: ");
    scanf("%d", &patientID); // Receiving Patient ID
    clear_buffer();

    if(check_ID(patientID, database)){
        int patientIndex = get_Patient_Index(patientID, database);
        strcat(database.patients[patientIndex].notes, tempNote);
        printf("Enter Patient Note: ");
        scanf(" %[^\n]", tempNote);
        clear_buffer();
        strcat(database.patients[patientIndex].notes, tempNote);

    } else {
        printf("Patient does not exist with ID of %d\n", patientID);
    }

    return database;
}

int save_database(struct database database, const char file_name[]){
    int flag = 0;
    FILE *pF = NULL;
    pF = fopen(file_name, "w");
    if(pF != NULL){
        fprintf(pF, "%d\n", database.numPatients);
        for (int i = 0; i < database.numPatients; ++i) {
            fprintf(pF, "%d,%s,%d,%f,%f,%s,%ld\n",
                database.patients[i].ID,
                database.patients[i].fullName,
                database.patients[i].age,
                database.patients[i].weightKG,
                database.patients[i].heightM,
                database.patients[i].notes,
                database.patients[i].admissionTime);
        }
        fclose(pF);
        flag = 1;
    } else {
        flag = 0;
    }
    return flag;
}

int retrieve_database(struct database *database, const char file_name[]) {
    int i = 0;
    int flag = 0;
    FILE *pF = NULL;
    pF = fopen(file_name,"r");
    if (pF != NULL) {
        fscanf(pF, "%d\n", &database->numPatients);
        while (fscanf(pF, "%d,%[^,],%d,%f,%f,%[^,],%ld\n",
                      &database->patients[i].ID,
                      database->patients[i].fullName,
                      &database->patients[i].age,
                      &database->patients[i].weightKG,
                      &database->patients[i].heightM,
                      database->patients[i].notes,
                      &database->patients[i].admissionTime) != EOF)
        {
            i++;
        }
        flag = 1;
    }
    fclose(pF);
    return flag;
}

void clear_buffer(){
    while (getchar() != '\n');
}

int remove_patient(struct database *database){
    int flag = 0;
    int patientID;
    int patientIndex;

    printf("Enter Patient ID: ");
    scanf("%d", &patientID);
    clear_buffer();

    if(check_ID(patientID, *database)){
        patientIndex = get_Patient_Index(patientID, *database);

        // Starting at Patient index move (patient index++) into patient index
        for (int i = patientIndex; i < (database->numPatients - 1); ++i) {
            database->patients[i].ID = database->patients[i+1].ID;
            memset(database->patients[i].fullName,0,strlen(database->patients[i].fullName));
            strcpy(database->patients[i].fullName, database->patients[i+1].fullName);
            database->patients[i].age = database->patients[i+1].age;
            database->patients[i].weightKG = database->patients[i+1].weightKG;
            database->patients[i].heightM = database->patients[i+1].heightM;
            memset(database->patients[i].notes,0,strlen(database->patients[i].notes));
            strcpy(database->patients[i].notes, database->patients[i+1].notes);
            database->patients[i].admissionTime = database->patients[i+1].admissionTime;
        }

        // Updating numPatients
        database->numPatients--;

        // Clearing Last Index
        database->patients[database->numPatients].ID = 0;
        memset(database->patients[database->numPatients].fullName,0, strlen(database->patients[database->numPatients].fullName));
        database->patients[database->numPatients].age = 0;
        database->patients[database->numPatients].weightKG = 0;
        database->patients[database->numPatients].heightM = 0;
        memset(database->patients[database->numPatients].notes,0, strlen(database->patients[database->numPatients].notes));
        database->patients[database->numPatients].admissionTime = 0;

        flag = 1;
    }
    else {
        printf("Error: Patient with id %d does not exist\n", patientID);
    }
    return flag;
}

void display_patients_by_admission_date(struct database database){
    struct patient temp;

    // Bubble Sort
    for (int i = 0; i < database.numPatients; ++i) {
        // Checking if left is greater than right index
        for (int j = 0; j < (database.numPatients - 1); ++j) {
            if (database.patients[j].admissionTime > database.patients[j + 1].admissionTime) {
                // Moving greater to temp
                temp.ID = database.patients[j].ID;
                memset(temp.fullName,0, strlen(temp.fullName));
                strcpy(temp.fullName,database.patients[j].fullName);
                temp.age = database.patients[j].age;
                temp.weightKG = database.patients[j].weightKG;
                temp.heightM = database.patients[j].heightM;
                memset(temp.notes,0, strlen(temp.notes));
                strcpy(temp.notes,database.patients[j].notes);
                temp.admissionTime = database.patients[j].admissionTime;

                // Moving less than into left index
                database.patients[j].ID = database.patients[j + 1].ID;
                memset(database.patients[j].fullName,0, strlen(database.patients[j].fullName));
                strcpy(database.patients[j].fullName, database.patients[j + 1].fullName);
                database.patients[j].age = database.patients[j + 1].age;
                database.patients[j].weightKG = database.patients[j + 1].weightKG;
                database.patients[j].heightM = database.patients[j + 1].heightM;
                memset(database.patients[j].notes,0, strlen(database.patients[j].notes));
                strcpy(database.patients[j].notes, database.patients[j + 1].notes);
                database.patients[j].admissionTime = database.patients[j + 1].admissionTime;

                // Moving greater than from temp into right index
                database.patients[j + 1].ID = temp.ID;
                memset(database.patients[j + 1].fullName,0, strlen(database.patients[j + 1].fullName));
                strcpy(database.patients[j + 1].fullName,temp.fullName);
                database.patients[j + 1].age = temp.age;
                database.patients[j + 1].weightKG = temp.weightKG;
                database.patients[j + 1].heightM = temp.heightM;
                memset(database.patients[j + 1].notes,0, strlen(database.patients[j + 1].notes));
                strcpy(database.patients[j + 1].notes,temp.notes);
                database.patients[j + 1].admissionTime = temp.admissionTime;
            }
        }
    }

    // Displaying patients from earliest admission time to latest
    for (int i = 0; i < database.numPatients; ++i) {
        // Displaying Patient
        print_patient(database, i);
    }
}

void print_patient(struct database database, int index){
    printf("----------\n");
    printf("Patient %d\n", index + 1);
    printf("----------\n");
    printf("Patient ID: %d\n", database.patients[index].ID);
    printf("Patient Name: %s\n", database.patients[index].fullName);
    printf("Patient Age: %d\n", database.patients[index].age);
    printf("Patient Weight (Kg): %.2f\n", database.patients[index].weightKG);
    printf("Patient Height (m): %.2f\n", database.patients[index].heightM);
    printf("Patient Notes: %s\n", database.patients[index].notes);
    printf("Patient Admittance Time: %s", ctime(&database.patients[index].admissionTime));
}
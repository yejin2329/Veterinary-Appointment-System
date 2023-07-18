/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Jenny Kim
Student ID#: 139787220
Email      : ykim314@myseneca.ca
Section    : NMM
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////


// Function to classify the values
void classify(struct Appointment appointment[], int max) {
    int i = 0, j = 0;
    struct Appointment schedule;

   
    while(i<max){

        appointment[i].time.min = (appointment[i].date.year * 12 * 30 * 24 * 60) + (appointment[i].date.month * 30 * 24 * 60) + (appointment[i].date.day * 24 * 60) + (appointment[i].time.hour * 60) + appointment[i].time.min;
        i++;
    }

   
    i = max - 1;

    while(i>0){

        for (j = 0; j < i; j++){

            if (appointment[j].time.min > appointment[j + 1].time.min){

                schedule = appointment[j];
                appointment[j] = appointment[j + 1];
                appointment[j + 1] = schedule;
            }
        }

        i--;
    }

   //To convert total minutes to minutes
    for (i = 0; i < max; i++) {
        appointment[i].time.min = appointment[i].time.min - (appointment[i].date.year * 12 * 30 * 24 * 60) - (appointment[i].date.month * 30 * 24 * 60) - (appointment[i].date.day * 24 * 60) - (appointment[i].time.hour * 60);
    }

}




// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
    int i=0, record = 0;

    if (fmt == FMT_TABLE) {

        displayPatientTableHeader();
    }

    while(i<max){

        if (patient[i].patientNumber != 0) {

            displayPatientData(&patient[i], fmt);
            record = 1;
        }
        i++;
    }

    if (!record) {

        printf("*** No records found ***\n\n");
    }

    putchar('\n');
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {
    int selection = 0;
    int exit = 1;

    while (exit) {

        printf("Search Options");
        printf("\n==========================");
        printf("\n1) By patient number");
        printf("\n2) By phone number");
        printf("\n..........................");
        printf("\n0) Previous menu");
        printf("\n..........................");
        printf("\nSelection: ");
        scanf("%d", &selection);

        clearInputBuffer();

        if (selection == 0) {
            exit = 0;
        }

        else if (selection == 1) {
            putchar('\n');
            searchPatientByPatientNumber(patient, max);
            putchar('\n');
            suspend();
        }

        else if (selection == 2) {
            putchar('\n');
            searchPatientByPhoneNumber(patient, max);
            putchar('\n');
            suspend();

        }

    }
    putchar('\n');
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
    int i = 0, selection = 0, index = 0, number = 0;
    

    while(i<max && selection ==0){

        selection = 0;
        if (patient[i].patientNumber == 0){
            index = i;
            selection = 1;
        }

        i++;
    }

    if (selection == 0){
        printf("ERROR: Patient listing is FULL!\n\n");
    }

    else{
      
        number = nextPatientNumber(patient, max);
        patient[index].patientNumber = number;
        inputPatient(&patient[index]);

        printf("*** New patient record added ***\n\n");
    }
}



// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {
    int input_number = 0, index = 0;

    printf("Enter the patient number: ");
    scanf("%d", &input_number);

    clearInputBuffer();

    index = findPatientIndexByPatientNum(input_number, patient, max);

    if (index == -1) {

        putchar('\n');
        printf("ERROR: Patient record not found!");
    }

    else {

        putchar('\n');
        menuPatientEdit(&patient[index]);
    }


}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {
    int input_number = 0, index = 0;
    char selection = 0, character = 0;

    printf("Enter the patient number: ");
    scanf("%d", &input_number);
    putchar('\n');

    
    if (findPatientIndexByPatientNum(input_number, patient, max) != -1) {
        index = findPatientIndexByPatientNum(input_number, patient, max);

        printf("Name  : %s\n", patient[index].name);
        printf("Number: %05d\n", patient[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)", patient[index].phone.description);
        printf("\n\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");

        int flag = 1;

        do {
            scanf(" %c%c", &selection, &character);

            if ((selection == 'n' || selection == 'N') && (character == '\n')) {

                printf("Operation aborted.\n\n");
                flag = 0;
                clearInputBuffer();
            }
            else if ((selection == 'y' || selection == 'Y') && (character == '\n')) {
             
                patient[index].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                flag = 0;
            }
            else {
                clearInputBuffer();
                printf("ERROR: Character must be one of [yn]: ");
            }
        } while (flag);
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data) {
    int i = 0, j = 0;

   //using classify function 
    classify(data->appointments, data->maxAppointments);

 
    //To display the patients
    displayScheduleTableHeader(NULL, 1);

    while(i<data->maxAppointments){

        for (j = 0; j < data->maxPatient; j++) {

            if(data->patients[j].patientNumber && data->appointments[i].patientNumber){

                if(data->patients[j].patientNumber== data->appointments[i].patientNumber){

                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
        i++;
    }

    putchar('\n');
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {
    int i = 0, j = 0;
    int last_day = 31;
    struct Date info;

   //Get year input
    printf("Year        : ");

    info.year = inputIntPositive();

   //Get month input
    printf("Month (1-12): ");

    info.month = inputIntRange(1, 12);

   //Get day input
    printf("Day (1-");

    if (info.month == 4 || info.month == 9 || info.month == 11) {
        last_day = 30;
    }
    if (info.month == 2) {
        last_day = 28;
    }
    if (info.year % 4 == 0 && info.month == 2) {
        last_day = 29;
    }

    printf("%d)  : ", last_day);
    info.day = inputIntRange(1, last_day);
    putchar('\n');

    // Use classify function 
    classify(data->appointments, data->maxAppointments);

    // To display the patients
    displayScheduleTableHeader(&info, 0);

    for (i = 0; i < data->maxAppointments; i++) {

        for (j = 0; j < data->maxPatient; j++) {

            if (data->appointments[i].patientNumber && data->patients[j].patientNumber) {

                if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {

                    if (data->appointments[i].date.year == info.year && data->appointments[i].date.month == info.month && data->appointments[i].date.day == info.day) {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }

    putchar('\n');

}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients) {
   
    int input_number=0, index=0;
    int slotNotAvailable = 1;
    int last_day = 31;
    
    //Create temporary structure inside this function
    
    struct Time time;
    struct Date date;
    


    // Taking the patient number as input
    printf("Patient Number: ");

    input_number = inputIntPositive();
    index = findPatientIndexByPatientNum(input_number, pt, maxPatients);

    if (index >= 0) {
        while (slotNotAvailable)
        {
            // Taking the year as input
            printf("Year        : ");
            date.year = inputIntPositive();

            // Taking the month as input
            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            // Taking the day as input
            printf("Day (1-");
            if (date.month == 2) {
                last_day = 28;
            }

            else if (date.month == 4 || date.month == 9 || date.month == 11) {
                last_day = 30;
            }
           
            else if (date.year % 4 == 0 && date.month == 2) {
                last_day = 29;
            }

            printf("%d)  : ", last_day);
            date.day = inputIntRange(1, last_day);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            //To check timeslot available
            if (availableTimeSlot(date, time, app, maxAppointments)) {

                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else {
                while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.min > 0) || (time.min % MINUTE_INTERVAL != 0)) {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                    printf("Hour (0-23)  : ");

                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }

                slotNotAvailable = 0;
            }
        }

       //For next available time slot
        index = nextSlotAvailable(app, maxAppointments);
        app[index].date = date;
        app[index].time = time;
        app[index].patientNumber = input_number;

        printf("\n*** Appointment scheduled! ***\n\n");
    }

    else {

        printf("\nERROR: Patient record not found!\n\n");
    }

    return;
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients) {
  
    int input_number, last_day = 0, index=0, new=0;
    struct Date date;
    
    
    printf("Patient Number: ");

    input_number = inputIntPositive();
    index = findPatientIndexByPatientNum(input_number, pt, maxPatients);

    if (index >= 0) {
        // Take year input
        printf("Year        : ");
        date.year = inputIntPositive();

        // Take month input
        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        // Take day input
        printf("Day (1-");

        if (date.month == 2) {
            last_day = 28;
        }

        if (date.month == 4 || date.month == 9 || date.month == 11) {
            last_day = 30;
        }
     
        if (date.year % 4 == 0 && date.month == 2) {
            last_day = 29;
        }
        printf("%d)  : ", last_day);
        date.day = inputIntRange(1, last_day);

        new = appointmentValidation(input_number, date, app, maxAppointments);

        if (new >= 0) {
            putchar('\n');

            displayPatientData(&pt[index], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') {

                app[new].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }

            else {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int input_number = 0, number = 0;

    printf("Search by patient number: ");
    scanf("%d", &input_number);

    clearInputBuffer();

    number = findPatientIndexByPatientNum(input_number, patient, max);

    if (number == -1) {

        putchar('\n');
        puts("*** No records found ***");


    }

    else {

        putchar('\n');
        displayPatientData(&patient[number], 1);
    }


}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i = 0, display = 0;
    char phone[11] = { 0 };

    printf("Search by phone number: ");

    inputCString(phone, 10, 10);
    putchar('\n');
    displayPatientTableHeader();

    for (i = 0; i < max; i++) {

        if (strcmp(phone, patient[i].phone.number) == 0) {
            displayPatientData(&patient[i], FMT_TABLE);

            display++;
        }
    }
    if (display == 0) {

        putchar('\n');
        puts("*** No records found ***");
    }
}


// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
    int i = 0, patient_max = 0, patient_info = 0;

    patient_max = patient[0].patientNumber;

    while (i < max) {

        if (patient_max < patient[i].patientNumber) {

            patient_max = patient[i].patientNumber;
        }

        i++;
    }


    patient_info = patient_max + 1;

    return patient_info;
}


// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patient_number, const struct Patient patient[], int max) {
    int i = 0, value = 0, compare = 0;

    while (i < max) {
        if (patient_number == patient[i].patientNumber) {

            compare = 1;
        }

        i++;
    }

    if (compare != 0) {

        for (i = 0; i < max && patient[i].patientNumber != patient_number; i++) {

            value = i + 1;
        }
    }

    else {

        value = -1;
    }

    return value;
}

// To check next available timeslot
int availableTimeSlot(struct Date date, struct Time time, struct Appointment* appointment, int max) {
    int i=0, available = 0;

    for (i = 0; i < max; i++) {
       
        if (date.year == appointment[i].date.year && date.month == appointment[i].date.month && date.day == appointment[i].date.day && time.hour == appointment[i].time.hour && time.min == appointment[i].time.min) {
           
            available = 1;
        }
    }

    return available;
}

// To check when is next available slot for appointment 
int nextSlotAvailable(struct Appointment* appointment, int max) {
    int i = 0, next_available = 0;

    while (next_available == 0 && i < max) {

        if (appointment[i].patientNumber < 1) {

            next_available = 1;
        }
        i++;
    }
    return i;
}

// To check if it's valid appointment
int appointmentValidation(int patientNumber, struct Date date, struct Appointment* appointment, int max) {
    int i = 0, validation = 0;

    while (validation == 0 && i < max){
        if ((appointment[i].patientNumber == patientNumber) && (appointment[i].date.day == date.day) && (appointment[i].date.month == date.month) && (appointment[i].date.year == date.year)) {
            validation = 1;
        }

        i++;
    }
    return i - 1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {

    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : ");

    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {
    int selection = 0;
    char inputNumber[PHONE_LEN + 1];

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");

    selection = inputIntRange(1, 4);

    putchar('\n');

    switch (selection){

    case 1:
       
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputNumbers(inputNumber, 10, 10);
        strcpy(phone->number, inputNumber);

        putchar('\n');

        break;

    case 2:
      
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputNumbers(inputNumber, 10, 10);
        strcpy(phone->number, inputNumber);

        putchar('\n');

        break;

    case 3:
     
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputNumbers(inputNumber, 10, 10);
        strcpy(phone->number, inputNumber);

        putchar('\n');

        break;

    case 4:
        
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        *phone->number = '\0';

        break;
    }
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max) {
    
    int i = 0;

    // To open the file
    FILE* fp;
    fp = fopen(datafile, "r");

    
    if (fp != '\0') {

        i = 0;
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber,
            patients[i].name,
            patients[i].phone.description,
            patients[i].phone.number) != EOF)

        {
            i++;

            if (i >= max)

                break;
        }

        // To close the file
        fclose(fp);
    }

    else {

        printf("ERROR: File could not be read\n");
    }

  
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) {
    int i=0, number = 0;

    //To open the file
    FILE* fp;
    fp = fopen(datafile, "r");

   
    if (fp != '\0') {

        for (i = 0; i < max && !feof(fp); i++) {
        
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);

            
            if (!feof(fp)) {

                number++;
            }
        }

        // To close the file
        fclose(fp);
    }

    else {

        printf("ERROR: File could not be read\n");
    }

  
    return number+1;
}
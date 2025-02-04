/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Sean Muniz
Student ID#: 102411188
Email      : smuniz@myseneca.ca
Section    : BTP 100 NAA
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>



// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
#include <string.h>


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

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
void menuMain(struct ClinicData* data) /*accepts an address of a struct that is of type
                                        ClinicData. This means address gets passed so data
                                        can be modified*/
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
            menuPatient(data->patients, data->maxPatient);/*arrow notation is used because an address
                                                            got passed into the function. Address is not 
                                                            used because access to the whole array is needed*/
            break;
        case 2:
            menuAppointment(data); //only passing value so during the compiling 
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)/*Accepts array of structs of type Patient. 
                                                    Since access to the whole array is needed, an
                                                    address is not passed. */
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
            displayAllPatients(patient, max, FMT_TABLE);/*patient gets passed because it needs access to 
                                                        the entire array. */
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
void menuPatientEdit(struct Patient* patient) /*This accepts an address because it needs to modfiy 
                                                the data that is stored at the specified address and
                                                index that was passed into the function. */ 
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);/*arrow notation being used. 
                                                This means that the values that are stored at these 
                                                pointers are being printed.*/
        
        displayFormattedPhone(patient->phone.number);/* the reason the address sign is not used here
                                                    is because it was already passed into the menuPatientEdit
                                                    function call. So it is just referencing the address that is
                                                    already passed. */
        
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
            printf("\nPatient record updated!\n\n");
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
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, display = 0;

    for (i = 0; i < max && display == 0; i++)
    {
        if (patient[i].patientNumber != 0) /*checks to see if there is eligible
                                            data to display. Also note that a valye is passed since
                                            dot notation is used. This is because access to the entire is
                                            needed in order to iterate through the whole array. */
        {
            display =1; /* -if there is eligible data to display, display 
                            gets initialized to 1.
                           - this will also break out of the loop.*/
        }
    }

    if (display ==0) //This means that there is no data to display.
    {
        printf("*** No records found ***\n");
    }
    else 
    {
        displayPatientTableHeader();
        for (i = 0; i < max ; i++)
        {
            if (patient[i].patientNumber != 0)
            {
                displayPatientData(&patient[i], fmt);
            }
        }
        printf("\n");
    }
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) /*again, this needs access to the 
                                                                entire array. Hence why it accepts 
                                                                a pointer to the first element of 
                                                                the array.*/
{
    int searchOption;
    
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        
        searchOption = inputIntRange(0, 2);
        
        switch(searchOption)
        {
            case 1: 
                searchPatientByPatientNumber(patient, max);
                suspend();
                break;

            case 2: 
                searchPatientByPhoneNumber(patient, max);
                clearInputBuffer();
                suspend();
                break;
        }
            
    }while(searchOption);
    
    printf("\n");
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)/*accepts array of patients. This is because 
                                                    it needs access to the entire patients array in 
                                                    order to make sure it exists. */
{
    int saveIndex =-1, i;

    for (i = 0; i< max && saveIndex == -1; i++)
    {
        if (patient[i].patientNumber == 0)/*This checks the patient struct array to see
                                            if there is a patient number that is equal to 0*/
        {
            saveIndex = i;
        }
    }
   if(saveIndex == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else 
    {
        patient[saveIndex].patientNumber = nextPatientNumber(patient, max);/*next patient number 
                                                    function needs access to the whole array to 
                                                    determine the next patient number */
    
        inputPatient(&patient[saveIndex]);/*This function takes an address of type Patient
                                            it needs the address because it has to modify the data 
                                            that is stored in the index of that patient array. */
        printf("\n*** New patient record added ***\n\n");
    }
}    

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)/*This accepts an array of structs that is of    
                                                    of type  patient*/
{
    int patientNumber;
    int exists;
   
    printf("Enter the patient number: ");
   
    patientNumber = inputIntPositive();
   
    exists = findPatientIndexByPatientNum(patientNumber, patient, max);
   
    if (exists >= 0)
    {
        printf("\n");
        menuPatientEdit(&patient[exists]);
    }
    else 
    {
        printf("\nERROR! Patient record not found!\n\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNumber; 
    int exists;

    char removeOption;
   // char validOptions[] ={'y', 'n'};
    
    printf("Enter the patient number: ");

    patientNumber = inputIntPositive();
    
    exists = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (exists >= 0)
    {
        printf("\n");
        displayPatientData(&patient[exists], FMT_FORM);/*In order to display the patient data that is 
                                        stored at the saved index, you need to pass the address and its
                                        index.*/
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        removeOption = inputCharOption("yn");

        if (removeOption =='y')
        {
            patient[exists].patientNumber =0;/*dot notation is used. This means that it is referring 
                                                to a value. However since the index is specefied, only 
                                                the data that is stored at that addressgets initialized 
                                                to 0.*/
            patient[exists].name[0] = '\0';
            patient[exists].phone.description[0] = '\0';
            patient[exists].phone.number[0] ='\0';
            printf("Patient record has been removed!\n\n");
        }
        else if (removeOption == 'n')
        {
            printf("Operation aborted.\n\n");
        }
    }
    else 
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(const struct ClinicData data[])
{
    int j =0, i = 0; //appCount = 0, petNum =0; 
    
    //petNum = importPatients("patientData.txt", data->patients, MAX_PETS);
    
    //appCount = importAppointments("appointmentsData.txt", data->appointments, MAX_APPOINTMENTS);
    
   bubbleSort(data->appointments, data->maxPatient);
   
   displayScheduleTableHeader(&data->appointments->date, 1);
   
   for (i = 0 ; i < data->maxAppointments; i++)
   {
        for (j = 0 ; j < data->maxPatient ; j++)
        {
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber )
            {
                
                displayScheduleData(&data->patients[j], &data->appointments[i], 1);
            }
        }
   }
    //i = 0;
    //j = 0;
    //appCount = 0;
    //petNum =0;
   printf("\n");  
  
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(const struct ClinicData data[])
{
    int i, j; //appCount =0, petNum =0; 
    int year;
    int month;
    int day; 

    getDate(&year, &month, &day);

    bubbleSort(data->appointments, data->maxPatient);/* we do not use the & operator because there*/
    
    data->appointments->date.year = year;
    data->appointments->date.month = month;
    data->appointments->date.day = day;
    putchar('\n');
    displayScheduleTableHeader(&data->appointments->date, 0);
    for (i = 0 ; i < data->maxAppointments ; i++)
    {
        if (data->appointments[i].date.year == year && 
            data->appointments[i].date.month ==month && 
            data->appointments[i].date.day == day)
        {
            for (j = 0 ; j < data->maxPatient; j++)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                }
            }
        }
    }
    printf("\n");
    
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment appointments[], //points to array of type Appointments
                    int maxAppointments, 
                    struct Patient patients [], //points to array of type Patients
                    int maxPatient)
{
    int i =0, exit = 0;
    int year =0; 
    int patientNumber =0;
    int month =0; 
    int day =0; 
    int hour; 
    int minute;
    int validDateAndTime = 0, validTime;
    int errorDateAndTime = 0, errorTime = 0, saveIndex; 
    //int saveIndex;

    //checks to see if there is an empty slot for an appointment
    //==========================================================                 
    for (i = 0 ; i < maxAppointments && exit == 0 ; i++)
    {
        if (appointments[i].patientNumber < 1)
        {
            saveIndex = i;
            exit = 1;//initialization means that appointment can be added. 
        }
    }
    //==========================================================
    if (exit == 1)
    {
        validatePatientNumber(&patientNumber, MAX_PETS, patients);/*RAISE QUESTION WITH CRIS*/

        while (validDateAndTime == 0)
        {
            getDate(&year, &month, &day);
            //do while loop goes here. validates hour and minute 
            //validating the range and minute is multiple of 30. 
            validTime = 0;
            do
            {
                printf("Hour (0-23)  : ");
                hour = inputIntRange(MIN_HOUR, MAX_HOUR);

                printf("Minute (0-59): ");
                minute = inputIntRange(MIN_MINUTE, MAX_MINUTE);

                errorTime = 0;             
                //for when appointment (time) is not available. 
                for (i = 0 ; i < maxAppointments ; i++)
                {
                    if (hour > CLINIC_CLOSING_H || hour < CLINIC_OPENING_H)
                    {
                        errorTime++;
                    }
                    else if(minute % TIME_INTERVAL != 0)
                    {
                        errorTime++;
                    }
                    else if (hour == CLINIC_CLOSING_H && minute > MIN_MINUTE)
                    {
                    errorTime++;
                     }
                }
                if (errorTime != 0)
                {
                    printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                }
                else 
                {
                    validTime = 1;
                }
            }while (validTime == 0);

            errorDateAndTime = 0;
            for (i = 0 ; i< maxAppointments ; i++)
            {
                if (appointments[i].date.year == year &&
                    appointments[i].date.month == month &&
                    appointments[i].date.day == day &&
                    appointments[i].time.hour == hour && 
                    appointments[i].time.min == minute)
                {
                    errorDateAndTime++;
                }
            }
            if (errorDateAndTime != 0)
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else
            {
                validDateAndTime = 1;
            }
         } 
        appointments[saveIndex].patientNumber = patientNumber;
        appointments[saveIndex].date.year = year; 
        appointments[saveIndex].date.month = month;
        appointments[saveIndex].date.day = day;
        appointments[saveIndex].time.hour = hour;
        appointments[saveIndex].time.min = minute;
        printf("\n*** Appointment scheduled! ***\n\n");        
    }
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment appointments[], 
                    int maxAppointments, 
                    struct Patient patients [],
                    int maxPatient)
{
    int patientNumber;
    int saveIndex, saveAppointmentIndex;
    int valid;
    int i = 0;
    int day = 0, month = 0, year =0;
    char removeOption;
    char validOptions[] = {'y', 'n'};
    
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    valid =0;
    for (i = 0 ; i < maxPatient &&valid == 0 ; i++)
    {
        if (patientNumber == patients[i].patientNumber)
        {
            valid = 1;
            saveIndex =i;
        }
    }
    if (valid == 1)
    {
        getDate(&year, &month, &day);
        printf("\n");
        displayPatientData(&patients[saveIndex],FMT_FORM );

        printf("Are you sure you want to remove this appointment (y,n): ");
        removeOption = inputCharOption(validOptions);

        if (removeOption == 'y')
        {
           for (i = 0 ; i < maxAppointments ; i++)
           {
                if (appointments[i].date.year == year && 
                    appointments[i].date.month == month && 
                    appointments[i].date.day == day && 
                    appointments[i].patientNumber == patientNumber)
                {
                    saveAppointmentIndex = i;
                }
           }
           appointments[saveAppointmentIndex].date.year = 0; 
            appointments[saveAppointmentIndex].date.month  = 0; 
            appointments[saveAppointmentIndex].date.day =0; 
            appointments[saveAppointmentIndex].patientNumber =0;
            printf("\nAppointment record has been removed!\n\n");

        }
        else 
        {
            printf("Operation aborted.\n\n");
            clearInputBuffer();
        }

    }
    else 
    {
        printf("ERROR: Patient record not found!\n\n");
    }
  
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientRecord;
    int exists;
    
    printf("\nSearch by patient number: ");

    patientRecord = inputIntPositive();

    exists = findPatientIndexByPatientNum(patientRecord, patient/*we are passing 
                                        the array of type Patient in here. Since the function
                                        is searching for a patient number, it needs access to the
                                        whole array.*/, max);

    if (exists >= 0)
    {
        printf("\n");
        displayPatientData(&patient[exists], FMT_FORM);
        printf("\n");
    }
    else 
    {
        printf("\n*** No records found ***\n\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char phoneNumber[PHONE_LEN +1]; 
    int i; 
    int exists =0;

    printf("\nSearch by phone number: ");
    inputCString(phoneNumber, PHONE_LEN, PHONE_LEN); /*no need to initialize phoneNumber to result of function since
                                                            it is being passed as an argument.*/

    for (i = 0; i < max ; i++)/* this checks to see if there is a matching phone number.*/
    {
        if (strcmp(phoneNumber,patient[i].phone.number)== 0) /*REMEMBER that strcmp() returns 0 if both strings
                                                                are the same. Don't confuse the 0 with false. */
        {
            exists++;
        }
    }
    if (exists ==0)
    {
        printf("\n");
        displayPatientTableHeader();
        printf("\n*** No records found ***\n");
    }
    else 
    {
        printf("\n");
        displayPatientTableHeader();
        for (i = 0; i < max ; i++)
        {
            if(strcmp(phoneNumber,patient[i].phone.number)==0)/*REMEMBER that strcmp() returns 0 if both strings
                                                                are the same. Don't confuse the 0 with false. */
            {
                displayPatientData(&patient[i], FMT_TABLE);
            }
        }
    }
    putchar('\n');
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int largestPatNum = patient[0].patientNumber;
    int i;

    for (i =0; i < max ; i++)
    {
        if (patient[i].patientNumber > largestPatNum)
        {
            largestPatNum = patient[i].patientNumber;
        }
    }
    largestPatNum++;
    return largestPatNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)/*acceots an array of 
                                                            structs that is of type Patient accepts
                                                            array because it needs access to the whole 
                                                            array in order to loop through it.*/
                                 {
                                    int i;
                                    int index = -1;

                                    for (i = 0; i < max && index == -1; i++)
                                    {
                                        if (patient[i].patientNumber == patientNumber)
                                        {
                                            index =i;
                                        }
                                    }
                                    return index;
                                
                                 }
//Bubble sort 
void bubbleSort(struct Appointment appoints[], int itemCount) //sort from least to greatest. 
/*since this is point to an array of structs that has no data, you only pass the pointer and not the address because there 
is nothing in it. */
{
    int i, j; 
    struct Appointment temp;

    for (i = itemCount -1 ; i > 0 ; i--)
    {
        for (j = 0 ; j < i ; j++)
        {
            if (appoints[j].date.year > appoints[j +1].date.year) /*checks to see the next index is bigger
                                                                    than the current index*/
            {
                temp = appoints[j]; /*data in current index gets assigned to temp*/
                appoints[j] = appoints[j+1];/*data in next index gets assigned to current index*/
                appoints[j+1] = temp;/*data from current index gets stored in next index*/

                /* essentially, if the data in the current index is greater than the data in the next index, 
                    the data gets swapped. now the data in the current index is less than the data in the next index.*/
            }
            if (appoints[j].date.year == appoints[j+1].date.year &&
                appoints[j].date.month > appoints[j+1].date.month)
            {
                temp = appoints[j];
                appoints[j] = appoints[j+1];
                appoints[j+1] = temp;
            }
            if (appoints[j].date.year == appoints[j+1].date.year &&
                appoints[j].date.month == appoints[j+1].date.month &&
                appoints[j].date.day > appoints[j+1].date.day )
            {
                temp = appoints[j];
                appoints[j] = appoints[j+1];
                appoints[j+1] = temp;
            }
            if (appoints[j].date.year == appoints[j+1].date.year &&
                appoints[j].date.month == appoints[j+1].date.month &&
                appoints[j].date.day == appoints[j+1].date.day &&
                appoints[j].time.hour > appoints[j+1].time.hour)
            {
                temp = appoints[j];
                appoints[j] = appoints[j+1];
                appoints[j+1] = temp;
            }
            if (appoints[j].date.year == appoints[j+1].date.year &&
                appoints[j].date.month == appoints[j+1].date.month &&
                appoints[j].date.day == appoints[j+1].date.day &&
                appoints[j].time.hour == appoints[j+1].time.hour &&
                appoints[j].time.min > appoints[j+1].time.min)
            {
                temp = appoints[j];
                appoints[j] = appoints[j+1];
                appoints[j+1] = temp;
            }
        }
    }
}

int determineLeapYear(int year)
{
    if ((year % 4 ==0 && year % 100 != 0)||
        (year % 400 == 0))
        {
            return 1; 
        }
    else 
    {
        return 0;
    }
}

int getDate(int *year, int *month, int *day)
{
    int leapYear;
    int inputYear, inputMonth, inputDay;

    printf("Year        : ");
    inputYear =inputIntRange(CURRENT_YEAR, MAX_YEAR);
                                    
    printf("Month (1-12): ");
    inputMonth = inputIntRange(FIRST_MONTH, LAST_MONTH);

    if (inputMonth == FIRST_MONTH || inputMonth == 3 || 
        inputMonth == 5 || inputMonth == 7 || 
        inputMonth == 10 || inputMonth == LAST_MONTH)
    {
        printf("Day (1-31)  : ");
        inputDay =inputIntRange(1, 31);
    }
    else if(inputMonth == 9 || inputMonth == 4 ||
            inputMonth == 6 || inputMonth == 11)
    {
        printf("Day (1-30)  : ");
        inputDay =inputIntRange(1,30);
    }
    else if(inputMonth ==2)
    {
        leapYear = determineLeapYear(inputYear);

        if (leapYear == 1)
        {
            printf("Day (1-29)  : ");
            inputDay =inputIntRange(1, 29);
        }
        else 
        {
            printf("Day (1-28)  : ");
            inputDay = inputIntRange(1, 28);
        }
    }
    if (year != NULL && month != NULL && day != NULL)
    {
        *year = inputYear;
        *month = inputMonth;
        *day = inputDay;
    }
    return inputYear;
    return inputMonth;
    return inputDay;
}
int validatePatientNumber(int* patientNumber, int maxPatient, struct Patient patients[])
{
    int inputPatientNumber; 
    int patientExists;
    int i;
    do
        {
            patientExists = 0;
            printf("Patient Number: ");
            inputPatientNumber =inputIntPositive();
            //while loop for validating if the date/time is taken or not.
            for (i = 0 ; i < maxPatient &&patientExists ==0 ; i++)
            {
                if (patients[i].patientNumber == inputPatientNumber)
                {
                    patientExists =1;     
                }
            }
            if (patientExists == 0)
            {
                printf("\nERROR: Patient record not found!\n\n");
            }

    } while(patientExists == 0);
    
    if (patientNumber != NULL)
        *patientNumber = inputPatientNumber;

    return inputPatientNumber;
}
//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)/*accepts address of type Patient*/
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    
    printf("Number: %05d\n",patient->patientNumber);/*arrow notation means that this is an address.*/
    
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);/*This accepts an address of type Patient so that 
                                                the name can be modified.*/
    printf("\n");

    inputPhoneData(&patient->phone);/*Since the patient phone number needs to be added/modified it needs
                                    to access an address. */
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)/*again this is accepting an address. This means that it needs
                                        to modify/add information to the Arry of structs that is of type
                                        Phone.*/
{
    int selection;
  
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");

    printf("Selection: ");
    selection = inputIntRange(1, 4);
    
    switch (selection) 
    {
        case 1:
            strcpy(phone->description, "CELL");/*Again you use arrow notation when you are working with
                                                a pointer to a specific address.*/
            printf("\nContact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            clearInputBuffer();
          
            break;

        case 2:
            strcpy(phone->description, "HOME");
            printf("\nContact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            clearInputBuffer();
       
            break;

        case 3:
            strcpy(phone->description, "WORK");
            printf("\nContact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            clearInputBuffer();
            break;

        case 4:
            strcpy(phone->description, "TBD");
            strcpy(phone->number, "");
            break;
    }
}
//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i;
    int totalNumPatients =0; 
    FILE *fp = NULL;

    fp = fopen("patientData.txt", "r");

    if (fp != NULL)
    {
        for (i = 0 ; i < max &&!feof(fp); i++)
        {
            fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, 
                                                    &patients[i].name[0], 
                                                    &patients[i].phone.description[0],
                                                    &patients[i].phone.number[0]);

        }
        totalNumPatients = i;
        fclose(fp);
        return totalNumPatients;   
    }
    else 
    {
        return totalNumPatients;
    }
}
// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int totalNumAppointments =0;
    int i;
    FILE *fp = NULL; 

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        i =0;
        while (i < max && fscanf(fp, "%d, %d, %d, %d, %d, %d",&appoints[i].patientNumber, &appoints[i].date.year,  
                                                &appoints[i].date.month, &appoints[i].date.day, 
                                                &appoints[i].time.hour, &appoints[i].time.min) == 6)
        {
           i++;
        }
        totalNumAppointments =i;
        fclose(fp);
        return totalNumAppointments;
    }
    else 
    {
        return totalNumAppointments;
    }
}
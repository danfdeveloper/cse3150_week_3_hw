#include <iostream>
#include <cstring> // for strlen, strcpy
#include <string>
#include "starter_main.h"

// TODO: function prototypes
void addStudent(char *name, double gpa, char *names[], double gpas[], int &size, int capacity);
void updateGPA(double *gpaPtr, double newGpa);
void printStudent(const char *name, const double &gpa);
double averageGPA(const double gpas[], int size);

// TODO: implement addStudent
void addStudent(char *name, double gpa, char *names[], double gpas[], int &size, int capacity)
{
    if (size < capacity)
    {
        names[size] = new char[std::strlen(name) + 1];
        std::strcpy(names[size], name);
        gpas[size] = gpa;
        size++;
    }
    else
    {
        throw "List full";
    }
}

// TODO: implement updateGPA
void updateGPA(double *gpaPtr, double newGpa)
{
    if (gpaPtr == nullptr)
    {
        throw "ERROR: Pointer to GPA is null!";
    }
    else
    {
        *gpaPtr = newGpa;
    }
}

// TODO: implement printStudent
void printStudent(const char *name, const double &gpa)
{
    std::cout << "Name: " << name << ", GPA: " << gpa << std::endl;
}

// TODO: implement averageGPA
double averageGPA(const double gpas[], int size)
{
    if (size <= 0)
    {
        throw "ERROR: No students!";
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += gpas[i];
    }
    return sum / size; // already checked for size = 0 so this is fine
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: ./program <capacity>" << std::endl;
        return 1;
    }

    int capacity = std::stoi(argv[1]);
    char *names[capacity];
    double gpas[capacity];
    int size = 0;

    int choice;
    do
    {
        std::cout << "Menu:\n";
        std::cout << "1. Add student\n";
        std::cout << "2. Update GPA\n";
        std::cout << "3. Print all students\n";
        std::cout << "4. Compute average GPA\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        std::cin.ignore();
        switch (choice)
        {
        case 1:
        {
            // TODO: implement menu logic

            std::cout << "What is the student's name?" << std::endl;
            std::string name_input;
            std::getline(std::cin, name_input);

            std::cout << "What is the student's GPA? (4.0, 3.5, etc.)" << std::endl;
            std::string GPA_input;
            std::getline(std::cin, GPA_input);

            try
            {
                double GPA_input_d = std::stod(GPA_input);
                addStudent(const_cast<char *>(name_input.c_str()), GPA_input_d, names, gpas, size, capacity);
                std::cout << "You added a student!" << std::endl;
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
            }
            break;
        }
        case 2:
        {
            // TODO: implement menu logic
            if (size == 0)
            {
                std::cout << "No students!" << std::endl;
                break;
            }
            std::string name_input;
            double newGpa;

            std::cout << "Index of student to update?";
            int index = -1;
            std::cin >> index;
            std::cin.ignore();

            if (index < 0 || index >= size)
            {
                std::cout << "Bad index!" << std::endl;
                break;
            }

            std::cout << "Current GPA: " << gpas[index] << std::endl;
            std::cout << "Enter new GPA: ";
            std::cin >> newGpa;
            std::cin.ignore();

            try
            {
                updateGPA(&gpas[index], newGpa);
                std::cout << "GPA updated successfully!" << std::endl;
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
            }
            break;
        }

        case 3:
        {
            // TODO: implement menu logic
            if (size == 0)
            {
                std::cout << "No students!" << std::endl;
            }
            else
            {
                std::cout << "Students list:" << std::endl;
                for (int i = 0; i < size; i++)
                {
                    printStudent(names[i], gpas[i]);
                }
            }
            break;
        }
        case 4:
        {
            // TODO: implement menu logic
            try
            {
                double average = averageGPA(gpas, size);
                std::cout << "Average GPA: " << average << std::endl;

                int roundedAvg = static_cast<int>(average + 0.5);
                std::cout << "Integer average: " << roundedAvg << std::endl;
            }
            catch (const char *msg)
            {
                std::cout << msg << std::endl;
            }
            break;
        }

        case 5:
        {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        default:
        {
            std::cout << "Invalid choice" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }
        }
    } while (choice != 5);

    // TODO: free memory
    for (int i = 0; i < size; i++)
    {
        if (names[i] != nullptr)
        {
            delete[] names[i];
            names[i] = nullptr;
        }
    }
    return 0;
}

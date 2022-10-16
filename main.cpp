#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

struct node
{
    struct node *link;
    string phone;
    string name, addr;
} *header = NULL;

int insertc(string ph, string namec, string add)
{
    int i;
    struct node *n, *p, *q;
    n = (struct node *)malloc(sizeof(struct node));
    n->phone = ph;
    n->name = namec;
    n->addr = add;

    n->link = NULL;
    if (header == NULL)
    {
        header = n;
        return 1;
    }
    q = NULL;
    p = header;
    while (p != NULL)
    {
        if (p->phone == ph)
        {
            printf("\n**** SAME NUMBER IS ALREADY EXIST PLZ CHECK AGAIN ****");
            return 0;
        }
        p = p->link;
    }
    p = header;
    if ((p->name).compare(n->name) > 0)
    {
        n->link = header;
        header = n;
        return 1;
    }

    if ((p->name).compare(n->name) <= 0)
    {
        while ((p->name).compare(n->name) <= 0)
        {
            q = p;
            if (p->link != NULL)
            {
                p = p->link;
            }
            else
            {
                break;
            }
        }
        if (q->link != NULL)
        {
            n->link = q->link;
            q->link = n;
        }
        else
        {
            q->link = n;
        }
    }

    return 1;
}

void deletec(string namec)
{
    struct node *p, *q;
    string name, ph, address;

    if (header == NULL)
    {
        printf("\n***** NO CONTACTS FOR DELETE *****");
        return;
    }
    q = NULL;
    p = header;

    ifstream myFile;
    myFile.open("phoneRecord.txt");

    ofstream otherFile;
    otherFile.open("temp.txt");

    getline(myFile >> ws, ph);
    getline(myFile >> ws, name);
    getline(myFile >> ws, address);

    while (!myFile.eof())
    {
        if (namec != name)
        {
            otherFile << ph;
            otherFile << endl;
            otherFile << name;
            otherFile << endl;
            otherFile << address;
            otherFile << endl;
        }

        getline(myFile >> ws, ph);
        getline(myFile >> ws, name);
        getline(myFile >> ws, address);
    }

    myFile.close();
    otherFile.close();

    remove("phoneRecord.txt");
    rename("temp.txt", "phoneRecord.txt");

    if ((p->name).compare(namec) == 0)
    {
        header = p->link;
        cout << "\n****** Contact named " << p->name << " is deleted ******";
        return;
    }
    while (p != NULL)
    {
        if ((p->name).compare(namec) == 0)
        {
            q->link = p->link;
            cout << "\n****** Contact named " << p->name << " is deleted ******";
            return;
        }
        q = p;
        p = p->link;
    }
    printf("\n********* Such contact not found *********");
}

void editInFile(string namec, string ename, string eph, string eaddress, int choice)
{
    string name, ph, address;

    ifstream myFile;
    myFile.open("phoneRecord.txt");

    ofstream otherFile;
    otherFile.open("temp.txt");

    getline(myFile >> ws, ph);
    getline(myFile >> ws, name);
    getline(myFile >> ws, address);

    while (!myFile.eof())
    {
        if (namec != name)
        {
            otherFile << ph;
            otherFile << endl;
            otherFile << name;
            otherFile << endl;
            otherFile << address;
            otherFile << endl;
        }
        else
        {
            if (choice == 1)
            {
                otherFile << ph;
                otherFile << endl;
                otherFile << ename;
                otherFile << endl;
                otherFile << address;
                otherFile << endl;
            }
            else if (
                choice == 2)
            {
                otherFile << eph;
                otherFile << endl;
                otherFile << name;
                otherFile << endl;
                otherFile << address;
                otherFile << endl;
            }
            else
            {
                otherFile << ph;
                otherFile << endl;
                otherFile << name;
                otherFile << endl;
                otherFile << eaddress;
                otherFile << endl;
            }
        }

        // myFile >> ph;
        // myFile >> name;
        // myFile >> address;

        getline(myFile, ph);
        getline(myFile, name);
        getline(myFile, address);
    }

    myFile.close();
    otherFile.close();

    remove("phoneRecord.txt");
    rename("temp.txt", "phoneRecord.txt");
}

int editByName(string namec, string ename, string eph, string eaddress, int choice)
{
    struct node *p, *q;

    if (header == NULL)
    {
        printf("\n***** NO CONTACTS FOR EDIT *****");
        return 0;
    }
    q = NULL;
    p = header;

    if ((p->name).compare(namec) == 0)
    {

        if (choice == 1)
        {
            p->name = ename;
        }
        else if (choice == 2)
        {
            p->phone = eph;
        }
        else
        {
            p->addr = eaddress;
        }
        return 1;
    }
    while (p != NULL)
    {

        if ((p->name).compare(namec) == 0)
        {
            if (choice == 1)
            {
                p->name = ename;
            }
            else if (choice == 2)
            {
                p->phone = eph;
            }
            else
            {
                p->addr = eaddress;
            }
            return 1;
        }

        q = p;
        p = p->link;
    }
    printf("\n******Such contact not found******");
    return 0;
}

int searchname(string names)
{
    struct node *p;
    if (header == NULL)
    {
        printf("\t\t*****NO CONTACTS AVAILABLE*****");
        return 0;
    }
    p = header;

    if ((p->name).compare(names) == 0)
    {
        cout << "\n****************************\nName--> " << p->name;
        cout << "\nPhone no--> " << p->phone;
        cout << "\nAddress--> " << p->addr << "\n****************************\n";
        return 1;
    }

    while (p != NULL)
    {
        if ((p->name).compare(names) == 0)
        {
            cout << "\n****************************\nName--> " << p->name;
            cout << "\nPhone no--> " << p->phone;
            cout << "\nAddress--> " << p->addr << "\n****************************\n";
            return 1;
        }
        p = p->link;
    }
    printf("\n***** NO match found *****");
    return 0;
}

void searchno(string num)
{
    struct node *p;
    if (header == NULL)
    {
        printf("\t\t*****NO CONTACTS AVAILABLE*****");
        return;
    }
    p = header;
    if (p->phone == num)
    {
        cout << "\n****************************\nName--> " << p->name;
        cout << "\nPhone no--> " << p->phone;
        cout << "\nAddress--> " << p->addr << "\n****************************\n";
        return;
    }

    while (p != NULL)
    {
        if (p->phone == num)
        {
            cout << "\n****************************\nName--> " << p->name;
            cout << "\nPhone no--> " << p->phone;
            cout << "\nAddress--> " << p->addr << "\n****************************\n";
            return;
        }
        p = p->link;
    }
    printf("***** NO match found *****");
}

void traversec()
{
    struct node *p;
    string name;
    if (header == NULL)
    {
        // cout << endl;
        cout << "\n************ No Contacts Available ************\n";
        return;
    }
    printf("\n\n\t*******************************\n\t\tLIST OF CONTACTS\n\t*******************************");
    printf("\n\nNAME\t\t\tPHONE NO\t\tADDRESS\n");
    p = header;
    while (p != NULL)
    {
        name = p->name;
        name.resize(20, ' ');
        cout << "\n"
             << name << "\t" << p->phone << "\t\t" << p->addr;
        p = p->link;
    }
}

int main()
{
    int ch, i, n, ch2, counter = 0, result;
    string namec;
    string address;
    string ph, line;
    fstream fio;
    fstream fio1;
    fio1.open("phoneRecord.txt", ios::in);

    while (fio1)
    {
        getline(fio1, line);

        if (counter == 0)
        {
            ph = line;
        }
        else if (counter == 1)
        {
            namec = line;
        }
        else
        {
            address = line;
            insertc(ph, namec, address);
            counter = -1;
        }

        counter++;
    }

    fio1.close();

    printf("\n****************** WELCOME TO PHONEBOOK ******************");
    do
    {
        printf("\n\n=======================\n[1] Add a contact\n[2] Delete a contact\n[3] Search for contact\n[4] Edit a contact\n[5] List all contact\n=======================\nEnter your choice--> ");
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            fio.open("phoneRecord.txt", ios::out | ios::in | ios::app);
            cout << "\nEnter the name--> ";

            getline(cin >> ws, namec);
            cout << "Enter the number--> ";

            getline(cin >> ws, ph);
            cout << "Enter the address--> ";

            getline(cin >> ws, address);
            result = insertc(ph, namec, address);

            if (result == 1)
            {
                fio << ph << "\n"
                    << namec << "\n"
                    << address << "\n";
            }

            fio.close();

            break;
        }
        case 2:
            printf("\nEnter the name want to delete--> ");
            getline(cin >> ws, namec);
            deletec(namec);
            break;

        case 3:
            printf("\n[1] Search by Name\n[2] search by Number\n\nEnter your choice--> ");
            scanf("%d", &ch2);
            switch (ch2)
            {
            case 1:
                printf("\nEnter the name--> ");
                getline(cin >> ws, namec);
                searchname(namec);
                break;

            case 2:
                printf("\nEnter the number--> ");
                getline(cin >> ws, ph);
                searchno(ph);
            }
            break;
        case 4:
        {
            // fio.close();
            printf("\nEnter the name of contact you want to edit--> ");
            // cin >> namec;
            getline(cin >> ws, namec);
            result = searchname(namec);

            if (result)
            {

                string ename, eph, eaddress;
                int choice;

                printf("\n[1] Edit the name\n");
                printf("[2] Edit the number\n");
                printf("[3] Edit the address\n\nEnter your choice--> ");
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    printf("Enter the name---> ");
                    getline(cin >> ws, ename);
                    editByName(namec, ename, "", "", choice);
                    editInFile(namec, ename, "", "", choice);
                    break;
                }
                case 2:
                {
                    printf("Enter the number---> ");
                    getline(cin >> ws, eph);
                    editByName(namec, "", eph, "", choice);
                    editInFile(namec, "", eph, "", choice);
                    break;
                }
                case 3:
                {
                    printf("Enter the address---> ");
                    getline(cin >> ws, eaddress);
                    editByName(namec, "", "", eaddress, choice);
                    editInFile(namec, "", "", eaddress, choice);
                    break;
                }
                default:
                    printf("Invalid Choice---> ");
                    break;
                }
            }

            break;
        }
        case 5:
            traversec();
            break;

        default:
            printf("\nInvalid choice");
            fio.close();
        }

    } while (ch >= 1 && ch <= 5);

    return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Programm: Kostenvoranschlag fuer Malerarbeiten

// Struct


struct coustomer {
    char name[50];       // Kundenname
    char tel[20];        // telefonnummer
    int quantities;      // Anzahl der Raeume
    float meter[30];     // Flaeche jede Raume
    float sumMeter;      // gesamtfläche
    float price;         // Preis pro quadratmeter
};


// Funktionsdeklaration


void addCoustomer(int* count, struct coustomer coustomers[]);
void costEstimate(int count, struct coustomer coustomers[]);
void showCoustomer(int count, struct coustomer coustomers[]);
void menu(struct coustomer coustomers[]);

// ===========================================================
// Hauptfunktion
// ===========================================================

int main() {

    struct coustomer coustomers[30];

    menu(coustomers);

    return 0;
}

// ===========================================================
// Kunde hinzufuegen
// ===========================================================

void addCoustomer(int* count, struct coustomer coustomers[]) {
    int result;
    /* int result2;
     int result3;*/

     // Pruefen, ob bereits 30 Kunden gespeichert sind
    if (*count >= 30) {
        printf("Die maximale Anzahl von Kunden ist 30.\n");
        return;
    }

    printf("\n========== Kunden hinzufuegen ==========\n");

    // Name eingeben
    printf("Name: ");
    scanf_s(" %49[^\n]", coustomers[*count].name, 50);

    // Pruefen, ob der Name leer ist
    if (coustomers[*count].name[0] == '\0') {
        printf("Der Name darf nicht leer sein!\n");
        return;
    }

    // Prufen, ob der Name eine Zahl enthelt
    for (int i = 0; coustomers[*count].name[i] != '\0'; i++) {

        if (isdigit(coustomers[*count].name[i])) {
            printf("Der Name darf keine Zahlen enthalten!\n");
            return;
        }
    }

    // Telefonnummer eingeben
    printf("Telefonnummer: ");
    scanf_s(" %19[^\n]", coustomers[*count].tel, 20);

    // Anzahl der Raume eingeben
    do {
        printf("Anzahl der Raeume: ");
        result = scanf_s("%d", &coustomers[*count].quantities);

        if (coustomers[*count].quantities < 1) {
            printf("es muss min ein raum 1 sein.\n");
        }
        if (result != 1) {
            printf("Bitte geben Sie eine zahl ein:\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }


    } while (coustomers[*count].quantities < 1);

    // Gesamtflache am anfang auf 0 setzen
    coustomers[*count].sumMeter = 0;

    // Fläche jede raume eingeben
    for (int i = 0; i < coustomers[*count].quantities; i++) {

        do {
            printf("Flache von raum %d in m2: ", i + 1);
            result = scanf_s("%f", &coustomers[*count].meter[i]);

            if (coustomers[*count].meter[i] <= 0) {
                printf("Die Fläche muss groesser als 0 sein.\n");
            }
            if (result != 1) {
                printf("bitte geben sie eine zahl ein:\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }

        } while (coustomers[*count].meter[i] <= 0);

        // Flaeche zur Gesamtfläche addieren
        coustomers[*count].sumMeter =
            coustomers[*count].sumMeter +
            coustomers[*count].meter[i];
    }

    // Preis eingeben
    do {
        printf("Preis pro meter: ");
        result = scanf_s("%f", &coustomers[*count].price);

        if (coustomers[*count].price < 0) {
            printf("Der Preis darf nicht unter 0 sein.\n");
        }
        if (result != 1) {
            printf("Bitte geben Sie eine zahl ein:\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

    } while (coustomers[*count].price < 0);

    // Anzahl der Kunden erhoehen
    *count = *count + 1;

    printf("Kunde wurde erfolgreich gespeichert.\n");
}

// ===========================================================
// Kostenvoranschlag berechnen
// ===========================================================

void costEstimate(int count, struct coustomer coustomers[]) {

    if (count == 0) {
        printf("\n wurde noch keine Kunden gespeichert.\n");
        return;
    }

    printf("========== Kostenvoranschlag ==========\n");

    for (int i = 0; i < count; i++) {

        float totalPrice;
        float discount = 0;//rabat

        // Gesamtpreis berechnen
        totalPrice =
            coustomers[i].sumMeter *
            coustomers[i].price;

        // Rabatt berechnen
        if (coustomers[i].sumMeter >= 100) {
            discount = 10;
        }
        else if (coustomers[i].sumMeter >= 50) {
            discount = 5;
        }

        // Rabatt abziehen
        totalPrice =
            totalPrice -
            (totalPrice * discount / 100);

        printf("\nKunde: %s\n", coustomers[i].name);
        printf("Gesamtfläche: %.2f m2\n", coustomers[i].sumMeter);
        printf("Preis pro m: %.2f \n", coustomers[i].price);
        printf("Rabatt: %.0f\n", discount);
        printf("Gesamtpreis: %.2f\n", totalPrice);
    }
}

// ===========================================================
// kunden anzeigen
// ===========================================================

void showCoustomer(int count, struct coustomer coustomers[]) {

    if (count == 0) {
        printf("\nEs wurden noch keine Kunden gespeichert.\n");
        return;
    }

    printf("\n========== Kundendaten ==========\n");

    for (int i = 0; i < count; i++) {

        printf("\nKunde %d\n", i + 1);

        printf("name: %s\n", coustomers[i].name);
        printf("telefonnummer: %s\n", coustomers[i].tel);
        printf("anzahl der Raeume: %d\n", coustomers[i].quantities);

        // jede raumflache anzeigen
        for (int j = 0; j < coustomers[i].quantities; j++) {

            printf("raum %d: %.2f m\n",
                j + 1,
                coustomers[i].meter[j]);
        }

        printf("gesamtflache: %.2f m\n",
            coustomers[i].sumMeter);

        printf("preis pro meter: %.2f \n",
            coustomers[i].price);
    }
}

// ===========================================================
// Menu
// ===========================================================

void menu(struct coustomer coustomers[]) {

    int selection;
    int result;
    int count = 0;

    do {

        printf("\n====================================\n");
        printf("          angebot\n");
        printf("====================================\n");

        printf("1. Kunden einfuegen\n");
        printf("2. Angebot berechnen\n");
        printf("3. Kunden anzeigen\n");
        printf("4. Programm beenden\n");

        printf("Ihre Auswahl: ");

        result = scanf_s("%d", &selection);

        // Pruefen, ob eine Zahl eingegeben wurde
        if (result != 1) {

            printf(" geben Sie eine Zahl von 1 - 4 ein.\n");

            int c;

            while ((c = getchar()) != '\n' && c != EOF);

            continue;
        }

        switch (selection) {

        case 1:
            addCoustomer(&count, coustomers);
            break;

        case 2:
            costEstimate(count, coustomers);
            break;

        case 3:
            showCoustomer(count, coustomers);
            break;

        case 4:
            printf("Programm wird beendet!\n");
            break;

        default:
            printf("Ungueltige Auswahl!\n");
        }

    } while (selection != 4);
}


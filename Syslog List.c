#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SYSLOG_FILE "/var/log/syslog" // Syslog dosya yolu

// Syslog mesajlarýný tutacak düðüm yapýsý
struct LogNode {
    char message[512];  // Syslog mesajý
    char timestamp[64]; // Zaman damgasý
    struct LogNode* next; // Bir sonraki düðüm
};

// Baðlý liste için baþlangýç düðümü
struct LogNode* head = NULL;

// Zaman damgasý oluþturma fonksiyonu
void getTimestamp(char* buffer, int size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Yeni log ekleme fonksiyonu
void addLog(const char* message) {
    struct LogNode* newNode = (struct LogNode*)malloc(sizeof(struct LogNode));
    if (newNode == NULL) {
        printf("Bellek tahsis hatasi!\n");
        return;
    }
    strcpy(newNode->message, message);
    getTimestamp(newNode->timestamp, sizeof(newNode->timestamp));
    newNode->next = head;
    head = newNode;
}

// Syslog dosyasýndan loglarý oku ve baðlý listeye ekle
void readSyslog() {
    FILE* file = fopen(SYSLOG_FILE, "r");
    if (file == NULL) {
        perror("Syslog dosyasi acilamadi");
        return;
    }
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // Yeni satýr karakterini kaldýr
        addLog(buffer);
    }
    fclose(file);
}

// Tüm loglarý listeleme fonksiyonu
void printLogs() {
    struct LogNode* temp = head;
    printf("\n--- Syslog Kayitlari ---\n");
    while (temp != NULL) {
        printf("[%s] %s\n", temp->timestamp, temp->message);
        temp = temp->next;
    }
}

// Baðlý listeyi temizleme fonksiyonu
void clearLogs() {
    struct LogNode* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Tum loglar temizlendi!\n");
}

int main() {
    printf("Syslog dosyasindan gunlukler okunuyor...\n");
    readSyslog();
    printLogs();
    clearLogs();
    return 0;
}

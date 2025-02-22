# Syslog Kayıtlarının Bağlı Liste ile Gösterimi

## Proje Açıklaması
Bu proje, **Linux işletim sistemindeki syslog kayıtlarını** okumak ve bağlı liste (linked list) veri yapısını kullanarak saklamak için geliştirilmiştir. **Syslog dosyasındaki veriler okunur, bellekte dinamik olarak saklanır ve ekrana yazdırılır.**

## Kullanılan Veri Yapısı
Proje, **tek yönlü bağlı liste (singly linked list)** veri yapısını kullanmaktadır.
- **Neden Tek Yönlü Bağlı Liste?**
  - Syslog verileri **sadece eklenir ve sıralı olarak okunur**, bu nedenle çift yönlü bağlı listeye gerek yoktur.
  - Hafıza kullanımı daha verimlidir.
  - Yeni loglar **liste başına eklenir**, böylece en güncel kayıtlar en önce görünür.

## Projenin Çalışma Mantığı
1. **Syslog dosyası (`/var/log/syslog`) okunur** ve her satır bir bağlı liste düğümü olarak saklanır.
2. **Zaman damgası eklenir**, böylece her log kaydı ile birlikte görüntülenir.
3. Kullanıcı **logları ekrana yazdırabilir** veya **belleği temizleyebilir**.

## Dosya ve Fonksiyon Açıklamaları
| Fonksiyon | Açıklama |
|-----------|----------|
| `addLog(const char* message)` | Yeni bir syslog mesajını bağlı listeye ekler. |
| `getTimestamp(char* buffer, int size)` | Günlük kaydı için zaman damgası oluşturur. |
| `readSyslog()` | `/var/log/syslog` dosyasından verileri okuyarak bağlı listeye ekler. |
| `printLogs()` | Bağlı listedeki tüm syslog kayıtlarını ekrana yazdırır. |
| `clearLogs()` | Bağlı listeyi temizler ve belleği boşaltır. |

## Kullanım Talimatları
### 1. **Derleme**
Aşağıdaki komut ile programı derleyebilirsiniz:
```bash
gcc syslog_linked_list.c -o syslog_reader
```

### 2. **Çalıştırma**
Programı çalıştırmak için:
```bash
./syslog_reader
```
_(Sistem loglarını okumak için süper kullanıcı yetkileri gerekebilir. Eğer izin hatası alırsanız `sudo ./syslog_reader` komutunu kullanın.)_

## Örnek Çıktı
```
Syslog dosyasından günlükler okunuyor...

--- Syslog Kayıtları ---
[2025-02-21 15:45:12] System boot completed.
[2025-02-21 15:47:03] User login successful.
[2025-02-21 15:50:22] Network interface eth0 up.

Tüm loglar temizlendi!
```

## Gereksinimler
- Linux işletim sistemi
- C derleyicisi (GCC önerilir)
- `/var/log/syslog` dosyasına okuma izni

## Notlar
- Program sadece **Linux** sistemlerde çalışır.
- `/var/log/syslog` dosyası yoksa veya okunamazsa, hata mesajı gösterilir.
- **Bağlı liste kullanımı sayesinde** bellek verimli bir şekilde yönetilir.

## Lisans
Bu proje açık kaynak olup, herkes tarafından geliştirilebilir ve paylaşılabilir.


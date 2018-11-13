Eseguire i test dell'applicazione
=================================

Stampa informazioni eseguibile
------------------------------

### Nessun parametro

Lanciare `SHM-Storehouse`

Risultato: stamperà le informazioni sui parametri


Esegue il parsing di file JSON errati
-------------------------------------

### Parametro -f - test 1

Lanciare `SHM-Storehouse -f requests/not_valit_json_message.json`

Risultato: il file di log conterrà

### Parametro -f - test 2

Lanciare `SHM-Storehouse -f requests/valid_json_message_but_not_array.json`

Risultato: il file di log conterrà

### Parametro -f - test 3

Lanciare `SHM-Storehouse -f requests/valid_json_message_but_empty_array.json`

Risultato: il file di log conterrà

### Parametro -f - test 4

Lanciare `SHM-Storehouse -f requests/valid_json_message.json`

Risultato: il file di log conterrà


Lancia l'applicazione come demone
---------------------------------

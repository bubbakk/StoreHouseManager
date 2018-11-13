
Questo documento descrive le richieste che si posso fare a questo server.

Connessione al server
=====================

La connessione a questo server avviene sulla porta 12000 (definita in main.cpp
con la direttiva #define `TCP_port 12000`).

Il pacchetto di richieste standard (base) è definito nel file <protocol.md>.

Ciò che cambia tra un pacchetto e l'altro è il campo `"request"` che assume i valori della richiesta (es: "add a new object", "place an object", ...)


Add a new object
----------------

Questa richiesta crea un nuovo oggetto secondo i dati inviati nel pacchetto.

Esempio di pacchetto:
```
{
  "request": "add a new object",
  "objectType": "cylinder",
  "barCodes": [{
    "type": "code128",
    "code": "ABCD-12345.ciao$#"
  }],
  "arrivalTimestamp": 1539783454,
  "readableArrivalDateTime": "Wed, 17 Oct 2018 13:33:59 GMT",
  "size": {
    "height": 250,
    "radius": 235
  }
}
```

I campi in dettaglio:

|                           |Descrizione                            |Varori possibili / esempio   |
|---------------------------|---------------------------------------|-----------------------------|
|`objectType`               |tipo di oggetto da creare              |`"cylinder"`, `"box"`        |
|`barCodes`                 |codici a barre presenti sull'etichetta |vedi dettaglio formato       |
|`arrivalTimestamp`         |timestamp locale di arrivo             |1539783454                   |
|`readableArrivalTimestamp` |orario locale di arrivo leggibile      |Wed, 17 Oct 2018 13:33:59 GMT|
|`size`                     |dimensioni dell'oggetto                |vedi dettaglio formato       |

L'oggetto `barCodes` è un array con questa struttura:

L'oggetto `size` è un oggetto con differente struttura in base ai valori del campo `"objectType"`.
Se `"objectType"` è `"cylinder"` avrà questa struttura:

|Nome campo |Tipo  |Descrizione                    |
|-----------|------|-------------------------------|
|`"height"` |intero|altezza espresso in centimetri |
|`"radius"` |intero|raggio espresso in centimetri  |

Se `"objectType"` è `"box"` avrà questa struttura:

|Nome campo |Tipo  |Descrizione                       |
|-----------|------|----------------------------------|
|`"width"`  |intero|larghezza espressa in centimetri  |
|`"depth"`  |intero|profondità espressa in centimetri |
|`"height"` |intero|altezza espressa in centimetri    |

Quando 
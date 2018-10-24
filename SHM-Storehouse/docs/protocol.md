# Communication protocol
After initializing a TCP connection to server you have to send commands in a strict good format.

The communication starts with a `SHM_MSG_STA` and closes with `SHM_MSG_STO`. The last command does not close the connection, but only the message. Once the message is closed, the application starts to process it.

# Generic format

[TODO] PLEASE explain

[{
  "hostRequestData": {
    "IPAddress": "192.168.0.0",
    "hostName": "darkStellar",
    "applicationName": "SHM autopilot",
    "applicationPID": 1234,
    "UTCTimestamp": 1234567,
    "localTimestamp": 1234567,
    "readableLocalDateTime": "19 Luglio 2019, 17:15 15s",
    "messageType": "action",
    "data": {
      "request": "add object",
      "objectType": "cylinder"
      "weight": 1200000,
      "barCodes": [{
        "type": "code128",
        "code": "ABCD-12345.ciao$#"
        "tag": "main barcode"                ???
      }],
      "arrivalTimestamp": 1539783454,
      "readableArrivalDateTime": "Wed, 17 Oct 2018 13:33:59 GMT",
      "size": {
        "height": 2500,
        "radius": 2350
      }
    }
  }
},{
...
}]

## Available commands
Each request has its own fields and specific meaning.

### Add a new object in the storehouse

"request" = "create a new obect"

other fields:

```
    "objectType": "cylinder"
    "barCodes"
```

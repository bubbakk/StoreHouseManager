Communication protocol
======================

After connecting to TCP server, the client have to send the right commands in a
strict correct format.

The communication starts with a `SHM_MSG_STA` and closes with `SHM_MSG_STO`.
The last command does not close the connection, but only the message. Once the
message is closed, the application starts to process it.

There are other commands such: `HELLO` or `HELO`, `HELP`, `BYE` or `QUIT`.

TOC

* [generic request format](#Generic-request-format)
* [generic reply format](#Generic-reply-format)
* [implemented requests](#implemented-requests):
  * [Add a new object](#Add-a-new-object)
  * [Set object location](#Set-object-location)
  * [Set object status](#Set-object-status)

Generic request format
----------------------

[TODO] explain format / fields

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
      ...specific application data format...
    }
  }
},{
...
}]


Generic reply format
--------------------

[TODO] explain format / fields

```
{
  "serverReplyData": {
    "requestReferenceID": "1234-1234567",
    "applicationPID": 1234,
    "UTCTimestamp": 1234567,
    "localTimestamp": 1234567,
    "readableLocalDateTime": "19 Luglio 2019, 17:15 15s",
    "data": {
    }
  }
}
```

Implemented requests
--------------------

Each request has its own fields, and each field a specific meaning.

Available commands are:

 * [add a new object](#Add-a-new-object): create an instance of an object and
   it to the warehouse
 * [set location](#Set-location): set the location for an existing object
 * [object moving]
 * [object under processing]
 * [find object]


### Add a new object

**Request example file**: [add_a_new_object.json](../requests/test/add_a_new_object.json)

**`"hostRequestData.data.request"`** = `"add a new object"`

**Description**: this request **creates a new object** according to its type
(a cylinder, a box, ...) and **adds it to WareHouse** data storage.

**Required fields**:

 * **request**: `add a new object`
 * **objectType**: `cylinder`
 * **barCodes**: at least one element array
   * **type**: barcode type
   * **code**: code

`warehouseMajordomo::dispatchRequests` implementation sequence:
 * new object is created
 * created object is added to warehouse data storage
 * reply is sent

**Reply**: **da aggiungere**


### Set object location

**Request example file**: [set_object_location.json](../requests/test/add_a_new_object.json)

**`"hostRequestData.data.request"`** = `set object location`

**Description**: this request sets the actual location to object

**Required fields**:

 * **request**: `set object location`
 * **barcode**: unique barcode product
 * **location**: new position to set (measures in centimeters)
   * **X**: X axis relative to warehouse origin
   * **Y**: Y axis relative to warehouse origin
   * **Z**: height

`warehouseMajordomo::dispatchRequests` sequence:



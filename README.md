# my FTP

```
All the standard C library is authorized except recv , send and allsystemcallsthatmake
a socket non-blocking.
```
The goal of this project is to create a **FTP server**.
You MUST implement the given protocol (bonuses must be RFC959 compliant).
You MUST implement request sequences that are explained in the protocol (more information could be find in RFC959).
The network communication will be achieved through the use of TCP sockets.


## SERVER

```
∼/B-NWP-400> ./myftp –help
USAGE:  ./myftp port path
        port is the port number on which the server socket listens
        path is the path to the home directory for the Anonymous user
```
The server MUST be able to handle several clients at the same time by using **select** for command management and **fork** for data transfer.

```
A good use of select is expected for both reading and writing on sockets.
Any bad use of select would cause point loss
```
The server MUST have an authentication with an _Anonymous_ account and an empty password.

Data transfers MUST use _active_ or _passive_ mode, as explained in the bootstrap.

(Use the given program to see if your connection sequence is available.)

```
The given testing program does only test your connection sequence, it does not test the good implementation of buffer management
```
You can install a FTP server such as **proftpd** or **vsftpd** on your machine to understand how it works.


## BONUSES

Here is a list of my bonuses:

- a different home directory for each use account
- total compliance with the RFC

## FINAL MARK

### MARK: 31 / 33 (93.9%)

- Preliminaries (3 / 3)
- Error management (2 / 2)
- Architecture (1 / 1)
- Buffer management (1 / 1)
- Authentication (2 / 2)
- Working directory (7 / 7)
- Various tests (4 / 4)
- Directory Listing (2 / 3)
- Downloading file (4 / 4)
- Deleting file (4 / 4)
- Uploading file (1 / 2)
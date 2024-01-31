# socket-program-for-remote-file-copying

**Problem Statement :**

Implement a basic socket program for remote file copying between a client and a server. The
server should be able to receive a file from the client and save it to a specified directory. The
client, on the other hand, should be able to send a local file to the server. Consider handling
possible errors, such as file not found and permission issues.
Provide a sample demonstration by copying a text file from the client to the server and vice
versa. Your implementation should be able to handle files of varying sizes

**How to Run**

1) Open two terminals one for server and another for client
2) Compile both server.c and client.c files by : gcc client.c -o client and gcc server.c -o server
3) We need to create a folder named client_files and inside it a sample.txt file (which we are going to copy)
4) After running the server , a folder named received_files , will be created and a text file inside it will be made and the data will be copied from sample.txt file.

**Screenshots**

![photo_2024-01-31_10-42-14](https://github.com/sangdeepganvir/socket-program-for-remote-file-copying/assets/41817210/ded17915-73f1-4656-b4e0-25d5460fbfb1)
![photo_2024-01-31_10-42-17](https://github.com/sangdeepganvir/socket-program-for-remote-file-copying/assets/41817210/f3a6231f-623b-4eae-93f9-adb688e80f1f)
![photo_2024-01-31_10-42-21](https://github.com/sangdeepganvir/socket-program-for-remote-file-copying/assets/41817210/3e41f28b-bb6b-4fac-aabf-204245384243)
![photo_2024-01-31_10-42-24](https://github.com/sangdeepganvir/socket-program-for-remote-file-copying/assets/41817210/245a73b5-bdb6-48bd-8a0f-856a62ab6dca)

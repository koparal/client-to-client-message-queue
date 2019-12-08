#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct msg_buffer {
   long msg_type;
   char msg_from[20];
   char msg_to[20];
   char sender_name[20];
   char receiver_name[20];
   char msg[100];
} message;

main() {

   key_t my_key;
   int msg_id;
   
   //get sender name from user
   printf("Write Message Sender Name : ");
   fgets(message.sender_name, 100, stdin);
   
   //get receiver name from user	
   printf("Write Message Receiver Name : ");
   fgets(message.receiver_name, 100, stdin);
   
   //create unique key usign receiver name	
   my_key = ftok(message.receiver_name, 65);

   //create message queue
   msg_id = msgget(my_key, 0666 | IPC_CREAT);

   message.msg_type = 1;
   
   //get message from user
   printf("Write Message : ");
   fgets(message.msg, 100, stdin);
   
   //send message 
   msgsnd(msg_id, &message, sizeof(message), 0);

   printf("Message sent successfully. \nMessage is : %s \n", message.msg);

}

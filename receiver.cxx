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
	
   //get receiver name from user	
   printf("Write Message Receiver Name : ");
   fgets(message.sender_name, 100, stdin);

   //create unique key usign sender name
   my_key = ftok(message.sender_name, 65); 
   msg_id = msgget(my_key, 0666 | IPC_CREAT); 

   //get receive message from message queue
   msgrcv(msg_id, &message, sizeof(message), 1, 0); 
   
   printf("Received Message from : %s \nMessage is : %s", message.sender_name,message.msg);

   msgctl(msg_id, IPC_RMID, NULL);

   return 0;
}

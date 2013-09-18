#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "boxes.h"

void function_f(unsigned int x, unsigned int y, int flag, int y1, int y2);

unsigned int X[8], Y[8];
int j;

int main(int argc, char *argv[])
{

   const int numStages = 9;

   char message[120], test[17], byte[2];
   long  KM;
   int i, k, position = 0, round = 0, length, mlength, charCount = 0, endFlag = 0;
   unsigned int ui, R[numStages], K[(2 * numStages) + 1][8];

   // Check for key
   if(argc < 2) {
	  printf("Error!! No key given!\n");
   } else {
	  KM = strtol(argv[1], NULL, 16);
	  printf("Key accepted!");

	  // Grab message
	  printf("Please enter your message:\n");

	  fgets(message, 120, stdin);
//      printf("Your message:%s\n", message);  

   }

   // Safer algorithm (9 stages)

   // Generate stage keys

   strcpy(test, argv[1]);
   length = strlen(test) - 1;
   i = 0;
   while(position <= length) {
//	  printf("test:%s\n", test);
	  byte[0] = test[position];
	  byte[1] = test[position + 1];
//	  printf("byte:%s\n", byte); 
 
//	  for(i = 0; i < numStages; i++) {
      R[i] = strtol(byte, NULL, 16);
//	  printf("R[%d]:%d\n", i, R[i]);
      


//	  }

//	  memcpy(&ui, &byte, sizeof (ui));
//	  printf("%x\n", ui);
//	  printf("%x\n", byte);
//	  test /= 0x100;
//	  test[length] = '\0';
//	  test[length - 1] = '\0';
	  position += 2;
	  i++;
   }

   // R[8]
   R[8] = R[0] ^ R[1] ^ R[2] ^ R[3] ^ R[4] ^ R[5] ^ R[6] ^ R[7];
//   printf("R[8]:%d\n", R[8]);

   for(i = 0; i < 8; i++) {
      K[0][i] = R[i];
   }

   for(i = 1; i <= ((2 * numStages) + 1); i++) {
      for(j = 0; j < numStages; j++) {
         // Rotation
         R[j] = R[j] << 3;
	  }

      for(j = 0; j < numStages - 1; j++) {
         K[i][j] = (R[(i + j) % 9] + B[i][j]) % 256;
	  }
   }


   // Stage

   // Break up message in  8-byte blocks
   mlength = strlen(message) - 1;
//   printf("Message length:%d\n", mlength);


   while(mlength > 0) {

      for(i = 0; i < 8; i++) {
   	     if(endFlag) {
            X[i] = 0;
	     } else if(message[charCount] == '\0') {
		    endFlag = 1;
            X[i] = 0; 
	     } else {
            X[i] = message[charCount];
		    charCount++;
	     }
      }

      for(i = 0; i < 8; i++) {
   //	  printf("X[%d]:%d Hex:%x\n", i, X[i], X[i]);
      }

      while(round < numStages) {

         // A
         for(j = 0; j < 8; j++) {
	        if(j == 0 || j == 3 || j == 4 || j == 7) {
		       X[j] = X[j] ^ K[2 * round][j];
	        } else {
		       X[j] = (X[j] + K[2 * round][j]) % 256;
	        }
         }

         // B
         for(j = 0; j < 8; j++) {
            if(j == 0 || j == 3 || j == 4 || j == 7) {
	           X[j] = S[X[j]];
	        } else {
		       X[j] = SI[X[j]];
	        }
         }
   
		 // C
         for(j = 0; j < 8; j++) {
            if(j == 0 || j == 3 || j == 4 || j == 7) {
	           X[j] = (X[j] + K[(2 * round) + 1][j]) % 256;
	        } else {
		       X[j] = X[j] ^ K[(2 * round) + 1][j];
	        }
         }

         // D
         for(j = 0; j < 8; j++) {
	        if(j == 0 || j == 2 || j == 4 || j == 6) {
		       function_f(X[j], X[j + 1], 0, 0, 0);
            }
         }

         // E
         function_f(X[0], X[2], 1, 0, 1); 
         function_f(X[4], X[6], 1, 2, 3);
         function_f(X[1], X[3], 1, 4, 5);
         function_f(X[5], X[7], 1, 6, 7);

         for(j=0; j < 8; j++) {
            X[j] = Y[j];
         }

         // F
         function_f(X[0], X[2], 1, 0, 1);
         function_f(X[4], X[6], 1, 2, 3);
         function_f(X[1], X[3], 1, 4, 5);
         function_f(X[5], X[7], 1, 6, 7);

         for(j=0; j < 8; j++) {
            X[j] = Y[j];
         }

         round++; 

        printf("Round:%d\n", round);
      for(i = 0; i < 8; i++) {
			   printf("%d", X[i]);
					 }

printf("\n");
      }

      for(j = 0; j < 8; j++) {
         if(j == 0 || j == 3 || j == 4 || j == 7) {
	        X[j] = X[j] ^ K[2 * round][j];
	     } else {
		    X[j] = (X[j] + K[2 * round][j]) % 256;
	     }
      }
/*
      for(i = 0; i < 8; i++) {
         printf("X[%d]:%d Hex:%x\n", i, X[i], X[i]);
      }
*/
      mlength -= 8;

      for(i = 0; i < 8; i++) {
	     printf("%x", X[i]);
      }

      printf(" ");

   }

//   round = 0;

   printf("\n");
   return 0;
}

void function_f(unsigned int x, unsigned int y, int flag, int y1, int y2) {
   if(flag == 0) {
      X[j] = ((2 * x) + y) % 256;
      X[j + 1] = (x + y) % 256;
   }

   if(flag == 1) {
      Y[y1] = ((2 * x) + y) % 256;
	  Y[y2] = (x + y) % 256;
   }
}


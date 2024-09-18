#include <stdio.h>

int main() {
    char message[100], ch;
    int key, i = 0, choice;

    printf("Enter the text (only uppercase and lowercase letters): ");
    fgets(message, sizeof(message), stdin); 

    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    printf("Enter the choice: 1 for Encrypted, 2 for Decrypted: ");
    scanf("%d", &choice);

    if(choice == 1) {
        while(message[i] != '\0') {
            ch = message[i];
            if(ch >= 'A' && ch <= 'Z') {
                ch = (ch - 'A' + key) % 26 + 'A';
            } else if(ch >= 'a' && ch <= 'z') {
                ch = (ch - 'a' + key) % 26 + 'a';
            }
            message[i] = ch;
            i++;
        }
        printf("The encrypted message is: %s\n", message);
    } else if(choice == 2) {
    
        i = 0; 
        while(message[i] != '\0') {
            ch = message[i];
            if(ch >= 'A' && ch <= 'Z') {
                ch = (ch - 'A' - key + 26) % 26 + 'A'; 
            } else if(ch >= 'a' && ch <= 'z') {
                ch = (ch - 'a' - key + 26) % 26 + 'a';
            }
            message[i] = ch;
            i++;
        }
        printf("The decrypted message is: %s\n", message);
    }

    return 0;
}

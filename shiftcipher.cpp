#include <iostream>

namespace ShiftCipher {
    const int ASCII_CODE_LC=97;
    const int ASCII_CODE_UC=65;


    bool rangeOfAscii(char karakter, int code) {
        return (
            (karakter-code) >= 0
            &&
            (karakter-code) <= 25
        );
    }

    std::string enkripsi(std::string text="abc", int key=1) {
        std::string ans="";

        for(char ch: text) {
            if(rangeOfAscii(ch,ASCII_CODE_LC)) { 
                ch = (((ch-ASCII_CODE_LC)+key)%26)+ASCII_CODE_LC;
            } else if(rangeOfAscii(ch,ASCII_CODE_UC)) { 
                ch = (((ch-ASCII_CODE_UC)+key)%26)+ASCII_CODE_UC;
            }
            ans.push_back(ch);
        }

        return ans;
    }

 
    std::string dekripsi(std::string text="abc", int key=1) {
        std::string ans="";

        for(char ch: text) {
            if(rangeOfAscii(ch,ASCII_CODE_LC)) { 
                ch -= (ASCII_CODE_LC + key);
                ch = (ch < 0) ? ch+26 : ch; 
                ch = (ch%26)+ASCII_CODE_LC;
            } else if(rangeOfAscii(ch,ASCII_CODE_UC)) { 
                ch -= (ASCII_CODE_UC + key);
                ch = (ch < 0) ? ch+26 : ch; 
                ch = (ch%26)+ASCII_CODE_UC;
            }
            ans.push_back(ch);
        }

        return ans;        
    }
};

int main() {
    system("cls");
    bool running=true; 

    while(running) {
        int choose=1;


        printf("\nMENU\n");
        printf("1. Enkripsi\n");
        printf("2. Dekripsi\n");
        printf("3. Exit\n");
        std::cout << "Pilihan: "; std::cin >> choose; std::cin.ignore();

        std::string plaintext="";
        int key=1;

        switch(choose) {
            case 1: 
                std::cout << "Text: "; std::getline(std::cin,plaintext);
                std::cout << "Key: "; std::cin >> key;
                std::cout << "Encryption = " << ShiftCipher::enkripsi(plaintext,key) << "\n";
                break;
                
            case 2: 
                std::cout << "Text: "; std::getline(std::cin,plaintext);
                std::cout << "Key: "; std::cin >> key;
                std::cout << "Decryption = " << ShiftCipher::dekripsi(plaintext,key) << "\n";
                break;

            case 3: 
                system("cls");
                printf("Cabut gih\n");
                system("pause");
                running=false;
                break;

            default:
                printf("SALAH INPUTAN!\n");
                system("pause");
                break;
        }
    }
}
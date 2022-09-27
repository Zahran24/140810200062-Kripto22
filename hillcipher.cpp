#include <iostream>
#include<bits/stdc++.h>
using namespace std ;
 
int key[3][3] ; //Kunci global batas ordo matriks
 
int mod26(int a) //Modulo
{
    return a >= 0 ? (a%26) : 26-(abs(a)%26) ; 
}
 
// Determinan Matriks
int findDet(int m[3][3] , int n)
{
    int det;
    if(n == 2) // Jika ordo matriks = 2
    {
        det = m[0][0] * m[1][1] - m[0][1]*m[1][0] ;
    }
    else det = 0 ; // Invalid 
    return mod26(det);
}
 
int findDetInverse(int S , int D = 26) // Cari invers matriks
 
// S = Sisa / determinan
{
    int i = 0 ;
    int p[100] = {0,1};
    int q[100] = {0} ; // hasil bagi
 
    while(S!=0) // jika sisa tidak sama dengan 0
    {
        q[i] = D/S ;
        int oldD = D ;
        D = S ;
        S = oldD%S ;
        if(i>1)
        {    
            p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
        } 
        i++ ;
    }
    if (i == 1) return 1;
    else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
}
int gcd(int m, int n){
    if (n > m)
        swap(m,n);
    
    do{
        int temp = m % n;
        m = n;
        n = temp;
    } while (n != 0);
    
    return m;
}
 
void multiplyMatrices(int a[1000][3] , int a_rows , int a_cols ,  int b[1000][3] , int b_rows , int b_cols , int res[1000][3])
{
    for(int i=0 ; i < a_rows ; i++)
    {
        for(int j=0 ; j < b_cols ; j++)
        {
            for(int k=0 ; k < b_rows ; k++)
            {
                res[i][j] += a[i][k]*b[k][j] ;
            }
            res[i][j] = mod26(res[i][j]) ;
        }
    }
}
void findKey(){
    //deklarasi
    string plainteks,cipherteks;
    int key[2][2],det,detInv,adj[2][2],plainteksInv[2][2],plainMatriks[2][2],cipMatriks[2][2],counter;
    int p,c;
    int transpose[2][2];
    
    //input plainteks
    cout << "Masukkan Plainteks : ";
    cin.ignore();
    getline(cin,plainteks);
    
    //assign plainteks ke plainMatriks
    counter = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            p = toupper(plainteks[counter]) - 65;
            plainMatriks[i][j] = p;
            counter++;
        }
    }
    
    //input cipherteks
    cout << "Masukkan Cipherteks : ";
    getline(cin,cipherteks);
    
    //assign cipherteks ke cipMatriks
    counter = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            c = toupper(cipherteks[counter]) - 65;
            cipMatriks[i][j] = c;
            counter++;
        }
    }
    
    // determinan
    det = (plainMatriks[0][0] * plainMatriks[1][1]) - (plainMatriks[0][1] * plainMatriks[1][0]);
    if(gcd(det,26)==1){
        // inverse determinan mod 26
        detInv = findDetInverse(det, 26);
        
        //adjoin
        adj[0][0] = plainMatriks[1][1];
        adj[0][1] = (-1)*plainMatriks[0][1];
        adj[1][0] = (-1)*plainMatriks[1][0];
        adj[1][1] = plainMatriks[0][0];
        
        //hitung matriks invers plainteks
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                plainteksInv[i][j] = detInv * adj[i][j];
                if(plainteksInv[i][j] < 0){
                    plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
                }else{
                    plainteksInv[i][j] = plainteksInv[i][j];
                    plainteksInv[i][j] = plainteksInv[i][j] % 26;
                }
            } 
        }
        
        //Search key
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                key [i][j] = 0;
                for(int k = 0; k < 2; k++){
                    key [i][j] += (plainteksInv[i][k] * cipMatriks[k][j]);
                }
                key [i][j] %= 26;
            }
        }
        
 
        for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            transpose[j][i] = key[i][j];
            }
        }
    
        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                cout << (transpose[i][j]) << "\t";
            }
            cout <<endl;
        }       
    }else{
        cout << "Determinan Error " << endl;
        cout << "Key tidak ditemukan" << endl << endl;
    }
 
}
/* Invers = (matriks * det Invers) mod 26 */
/* cari Invers(matriks , order_of_matriks , result_matriks) */
void findInverse(int m[3][3] , int n , int m_inverse[3][3] )
{
    int adj[3][3] = {0};
 
    int det = findDet(m , n); // ini menggunakan fungsi findDet(matriks , order_of_matriks)
    int detInverse = findDetInverse(det);
 
    if(n==2) //jika ordo matriks 2 x 2
    {
        adj[0][0] = m[1][1];
        adj[1][1] = m[0][0];
        adj[0][1] = -m[0][1];
        adj[1][0] = -m[1][0];
    }
 
    for(int i=0; i<n ; i++)
    {
        for(int j=0; j<n ; j++)
        {
            m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;
        }
    }
}
 
// C = PK
string encryplaint(string plaint, int n)
{
    int P[1000][3] = {0} ; // plain text
    int C[1000][3] = {0} ; // cipher text
    int plaintIter = 0  ;
 
    while(plaint.length()%n != 0)
    {
        plaint += "a" ;  // digunakan jika plaintext di module dengan matriks != 0
    }
    int row = (plaint.length())/n; // jumlah baris dalam plaintext
 
    for(int i=0; i<row ; i++)
    {
        for(int j=0; j<n; j++)
        {
            P[i][j] = plaint[plaintIter++]-'a' ;
        }
    }
 
    // perkalian matriks(mat_a , row_a , col_a , mat_b, row_b, col_b , mat_result)
    multiplyMatrices(P, row , n , key , n , n , C) ;
 
    string ciphert = "" ;
    for(int i=0 ; i<row ; i++)
    {
        for(int j=0 ; j<n ;j++)
        {
            ciphert += (C[i][j] + 'a');
        }
    }
    return ciphert ;
}
 
// P = C*(k_inverse)
string decryplaint(string ciphert, int n)
{
    int P[1000][3] = {0} ; // plaintext
    int C[1000][3] = {0} ; // cipher text
    int ciphertIter = 0 ;
 
    int row = ciphert.length()/n; // banyak baris chipertext
 
    for(int i=0; i<row ; i++)
    {
        for(int j=0; j<n; j++)
        {
            C[i][j] = ciphert[ciphertIter++]-'a' ;
        }
    }
 
    int k_inverse[3][3] = {0};
    /* Inverse(matriks , order_of_matriks , result_matriks) */
    findInverse(key, n , k_inverse);
 
    /* Perkalian Matriks(mat_a , row_a , col_a , mat_b, row_b, col_b , mat_result) */
    multiplyMatrices(C, row , n , k_inverse , n , n , P) ;
 
    string plaint = "" ;
    for(int i = 0 ; i<row ; i++)
    {
        for(int j=0 ; j<n ; j++)
        {
            plaint += (P[i][j] + 'a');
        }
    }
    return plaint ;
}
 
int main(void)
{
    bool menuAciphertive = true;
    string plaint, ciphert;
    int n ;
    int pilih;
 
    while(menuAciphertive){
        cout << "Menu : " <<endl;
        cout << "1. Enkripsi" <<endl;
        cout << "2. Dekripsi" <<endl;
        cout << "3. Find Key" <<endl;
        cout << "4. Quit" <<endl;
        cout << "Pilih Menu : "; cin >> pilih;
        switch(pilih){
            case 1:
                    cout << "Masukkan kata   : " ;
                    cin >> plaint;
                    
                    cout << "Masukkan ordo matriks harus 2 x 2 : ";
                    cin >> n ;
 
                    for(int i=0; i<n; i++)
                    {
                        for(int j=0; j<n; j++)
                        {
                            cout<<"Masukkan matriks : "; cin >> key[i][j];
                        }
                    }
 
                    cout << "\nPlaintext  : " << plaint << endl;
 
                    ciphert = encryplaint(plaint, n) ;
                    cout << "Hasil Enkripsi : " << ciphert << endl;
                    break;
            case 2:
                    cout << "Masukkan kata   : " ;
                    cin >> ciphert;
                    
                    cout << "Masukkan ordo matriks harus 2 x 2 : ";
                    cin >> n ;
 
                    for(int i=0; i<n; i++)
                    {
                        for(int j=0; j<n; j++)
                        {
                            cout<<"Masukkan matriks : "; cin >> key[i][j];
                        }
                    }
 
                    cout << "\nChipertext  : " << ciphert << endl;
                    cout << "Hasil Dekripsi : " << decryplaint(ciphert, n)<< endl;
                    break;
            case 3:
                    cout<<endl;
                    findKey();
                    break;
            default:
                    cout << "\nInvalid Input" <<endl;
                    break;
        }
    }
}
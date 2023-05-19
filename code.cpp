#include <iostream>  

#include <vector>  

#include <string>  

#include <sstream> 

using namespace std;  

vector<int> divcadena(const string& string1, char delimitador) {

    // Vector para almacenar los enteros resultantes
    
    vector<int> resultado; 
 
// Objeto istringstream para dividir la cadena en subcadenas

    istringstream iss(string1);
 
    string t;

// Se itera sobre cada subcadena separada por el delimitador
 
    while (getline(iss, t, delimitador)) {
        
// Convierte la subcadena a entero y la agrega al vector

        resultado.push_back(stoi(t)); 
    }

// Devuelve el vector de enteros resultante

    return resultado; 
}

string puertadeenlace(const string& ip, const string& mascsubred) {
  
// Divide la dirección IP en octetos

vector<int> octetoip = divcadena(ip, '.'); 

// Divide la máscara de subred en octetos

    vector<int> octetomasc = divcadena(mascsubred, '.'); 

// Vector para almacenar los octetos correspondientes a la red

 vector<int> redOctetos; 

// Realiza una operación de bits AND entre cada octeto de la IP y la máscara de subred

    for (size_t i = 0; i < octetoip.size(); i++) {

// Calcula el octeto correspondiente a la red

        int octetored = octetoip[i] & octetomasc[i]; 

// Agrega el octeto al vector de redOctetos

        redOctetos.push_back(octetored); 

    }

// Objeto ostringstream para construir la cadena de la puerta de enlace

    redOctetos.back() += 1;

// Objeto ostringstream para construir la cadena de la puerta de enlace

    ostringstream puertaenlace; 

// Concatena los octetos de la red con puntos para formar la cadena de la puerta de enlace

    for (size_t i = 0; i < redOctetos.size(); i++) {

        // Agrega el octeto al ostringstream
        
        puertaenlace << redOctetos[i]; 

        if (i < redOctetos.size() - 1) {

            // Agrega un punto si no es el último octeto

            puertaenlace << "."; 

        }

    }

// Devuelve la cadena de la puerta de enlace

    return puertaenlace.str(); 

    
}


// Función para convertir la mascara de subred y la ip en binario 

string binario(const string& mascsubred) {  

// variable donde se va a almacenar la ip en binario
    string Ipbinario1;  

// variable para almacenar el numero que se encuentra en cada byte
    int n = 0;  

// variable para contar los puntos de la ip
    int octetopunto = 0;  

// recorrer caracter a caracter la variable de mascara de subred introducida por el usuario 

    for (char caract : mascsubred) {  

// Declaramos una variable tipo numerica igualandola a 128, debido a que 128 es el mayor bit ( 2*7 )

    int bits = 128;
    
// Hasta que no hay un "." en el string de ip lo que hace es saber el numero que existe en la ip es decir :  

// n = n * 10 + (caract - '0'); es decir si la ip es 192.168.33.45, recorre hasta el primer "." haciendo esto:  

// n = 0 *10 + (1 - '0') = 1, n = 1 *10 + (9 - '0') = 19, n = 19 *10 + (2 - '0')= 192    
    
        if (caract != '.') {  

            n = n * 10 + (caract - '0');  

 // Cuando el caracter deja de ser un "." lo que hace es lo siguiente: 

        } else {  

// el bucle lo que hace es completar el byte con 8 bits, es decir, la conversión a binario de cada byte   

          for (int i = 0; i < 8; i++) {  

// combrobando si el numero n (el numero que haya antes del ·.·) es mayor que los bits {128;64;32;16;8;4;2;1}, se almacena un '1' en la variable Ipbinario1, y restandole a n el bit que corresponda al bucle
if (n >= bits) {  

Ipbinario1 += '1'; 

n -= bits;  

}  

// y si n no es mayor que bits se almacena un "0" en la variable Ipbinario1

else {  

Ipbinario1 += '0';  

}  

// Se dividen entre 2 los bits para almacenar el siguiente caracter del byte  
bits = bits / 2;  

}  
// se iguala n a 0 para el siguiente byte

n=0;

// Si la variable que se va sumando 1 cada vez que se encuentra un punto es menor que 3 en este caso pq la variable empieza en 0, a Ipbinario1 se le almacena un "." 
            if (octetopunto < 3) {  

  

                Ipbinario1 += '.';  

  

            }  

  
// sumar un 1 a la variable octetopunto
            octetopunto++;  

  

        }  

  

    }  

// En esta parte volvemos ha hacer lo mismo pero para el último byte ya que no hay ningún "." destrás de el

int bits = 128;  

for (int i = 0; i < 8; i++) {  

if (n >= bits) {  

Ipbinario1 += '1'; 

 n -= bits; 

 }  

else {  

Ipbinario1 += '0'; 

 }  

bits = bits / 2; 

 } 

    return Ipbinario1;

}


// Funcion para sacar la primera ip disponible en binario 

string binarioidred(const string& ip, const string& mascsubred) {  
    
    string primeraIP;  

// En estas variables tipo string almacenaremos la ip en binario y la mascara de subred en binario. 

    string ipBinario = binario(ip);  

    string mascsubredBinario = binario(mascsubred);  

// operación "AND" entre la IP y la máscara de subred  

// 32 bits + 3 puntos hacen un bucle que se recorra 35 veces 

    for (int i = 0; i < 35; i++){  

// Este if sirve para cuando haya un "." tanto en la ip en binario como la mascara de subred en binario poner en la primera ip en binario un "." 

        if (ipBinario[i] == '.' || mascsubredBinario[i] == '.'){  

            primeraIP += '.';  

        }  

    // En el caso de que no metemos en un else, un if que compruebe si en la ip en binario y en la mascara de sub red binario hay un 1  

    // en la primera ip en binario se almacene un 1 y sino que almacene un 0.  

        else{  

            if (ipBinario[i] == '1' && mascsubredBinario[i] == '1'){  

                primeraIP += '1'; 

            } 

            else{  
                
                primeraIP += '0';  

            }  

        }  

    }  

    return primeraIP;  
    
}  

// Iniciamos el programa
int main() {  

// Declaramos variables para almacenar la ip en decimal, la mascara de subred y los casos para el tcpdump

    string ip;  
    string mascsubred;  
    int caso; 

// Introducir IP

    cout << "Introduce la IP: ";  
    
    cin >> ip;  

// Introducir la mascara de subred  

    cout << "Introduce la máscara de subred: ";  

    cin >> mascsubred;  

    cout << endl;  

// Almacenar los valores en binario en unja variable tipo string
    string Ipbinario = binario(ip);  

    string Ipbinario1 = binario(mascsubred);  

// Almacenarlas en punteros

    string* ipbinario = &Ipbinario;  

  

    string* mascbinario = &Ipbinario1;  

// Sacarlas por pantalla  

    cout << "La IP en binario es: " << *ipbinario << endl;  

    cout << "Y la máscara de subred es: " << *mascbinario << endl;  

// Guardar el resultado de el id de red en binario  

    string idred0 = binarioidred(ip, mascsubred);  

// Almacenarlo en un puntero

string* idred = &idred0; 

//Sacarla por pantalla

    cout << "El id de red es: " << *idred << endl;  

// Guardar el resultado de la puerta de enlace en una variable llamada puertaenlace

   string puertaenlace = puertadeenlace(ip, mascsubred); 

// Almacenarla en un puntero

   string* puertaenlaceptr = &puertaenlace; 
   
       cout << endl;  

    cout << endl;  
   
// Sacarla por pantalla

    cout << "La dirección de la puerta de enlace es: " << *puertaenlaceptr << endl; 

    cout << endl;  

    cout << endl;  

// Sacar por pantallas los casos del tcpdump

        cout<<"Caso 1: ICMP"<<endl; 

    cout<<"Caso 2: HTTP"<<endl; 

    cout<<"Caso 3: TCP"<<endl; 

cout<<"¿En cual caso quieres abrir el tcpdump?"<<endl; 

cin>>caso; 

//Abre el tcpdump con su caso correspondiente

switch(caso){ 

    case 1: 

        cout<<endl; 

        cout<<"ICMP maneja los mensajes de error y control para IP. Este protocolo permite a las pasarelas y los sistemas principales enviar informes de problemas a la máquina que envía un paquete."<<endl; 

        cout<<"ICMP se encuentra en la capa de red en el modelo OSI y en la de Internet del modelo TCP/IP"<<endl; 

        cout<<"Esnifando..."<<endl; 

        system("ifconfig"); 

        system("tcpdump icmp");

        break; 

    case 2: 

        cout<<endl; 

        cout<<"HTTP, es el nombre de un protocolo el cual nos permite realizar una petición de datos y recursos, como pueden ser documentos HTML."<<endl; 

        cout<<"HTTP se encuentra en la capa de Aplicación en el modelo OSI y también en el modelo TCP/IP"<<endl; 

        cout<<"Esnifando..."<<endl; 

         system("tcpdump tcp port http");

        break; 

        case 3: 

        cout<<endl; 

        cout<<"El protocolo TCP es el encargado de proporcionar un servicio de comunicación punto a punto entre dos host. Este protocolo de cuarto nivel está orientado a conexión en la capa de transporte y funciona a través de la conexión mutua entre cliente y servidor."<<endl; 

        cout<<"TCP se encuentra en la capa de Transporte en el modelo OSI y también en el modelo TCP/IP"<<endl; 

        cout<<"Esnifando..."<<endl; 

         system("tcpdump tcp");

        break; 

} 

return 0;  

} 

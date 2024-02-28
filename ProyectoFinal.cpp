#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>//iftream-oftream
#include<sstream>//convertir lineas a stream
using namespace std;

string NOMBRE_ARCHIVO = "CajeroAutomatico.txt";

//Estructura de cliente

struct cliente
{
    string NOMBRE;
    int USUARIO;
    int PIN;
    string CBU;
    string ALIAS;
    string DNI;
    float BALANCE;   
};
const int maxclientes = 50;
cliente lista[maxclientes];

void EscribirArchivo(int cantidadclientes);
void LeerArchivo(int &cantidadclientes);
bool LeerUsuario(int &usuario,int cantidadclientes);
bool IngresarPIN(int usuario, int cantidadclientes);
void Menu();
void ConsultarBalance(int cantidadclientes, int &usuario);
void Depositar(int cantidadcliente, int usuario);
void Retirar(int cantidadcliente, int usuario);
void Transferir(int cantidadclientes, int usuario, string cbu);

int cantidadclientes = 0;

int main()
{
    int usuario;
    string cbu;
    LeerArchivo(cantidadclientes);
    cout<<"BIENVENIDO AL BANCO NACION"<<endl;
    cout<<endl;

    if (!LeerUsuario(usuario, cantidadclientes))
    {
        cout<<"Usuario Incorrecto, retire su tarjeta y vuelva a intentarlo en 24 hs"<<endl;
    }
    else if(!IngresarPIN(usuario, cantidadclientes))
    {
        cout<<"PIN incorrecto, retire su tarjeta y vuelva a intentarlo en 24hs "<<endl;
    }
    else
    {
        int opcion;
        do
        {
            Menu();
            cout<<endl;
            cout<<"Ingrese una opcion: ";
            cin>>opcion;
            cout<<endl;

            switch(opcion)
            {
                case 1:
                ConsultarBalance(cantidadclientes, usuario);

                break; 

                case 2:
                Depositar(cantidadclientes, usuario);
                break;
                
                case 3:
                Retirar(cantidadclientes, usuario);
                break;

                case 4:
                Transferir(cantidadclientes,usuario, cbu);
                break;

                case 5:
                cout<<"Salir "<< endl;
                break;

                default:
                cout<<"La opcion ingresada es incorrecta "<<endl;
                break;
                
            }

        }while(opcion!=5);
    }

    return 0;

}

void EscribirArchivo(int cantidadclientes)
{   
    ofstream archivo(NOMBRE_ARCHIVO, ios::out);// Abrimos en archivo

    if (archivo.is_open()) //comprobamos si el archivo se pudo abrir correctamente
    {
        string linea;

        for (int i = 0; i < cantidadclientes; i++)
        {
            string delimitador = ",";

            archivo << lista[i].NOMBRE << delimitador;
            archivo << lista[i].USUARIO << delimitador;
            archivo << lista[i].PIN<< delimitador;
            archivo << lista[i].CBU << delimitador;
            archivo << lista[i].ALIAS << delimitador;
            archivo << lista[i].DNI << delimitador;
            archivo << lista[i].BALANCE << endl;
        }
        archivo.close();//liberamos espacio de memoria
    }
    else
    {
        cout << "No se pudo abrir el archivo\n";
    }
}

void LeerArchivo(int &cantidadclientes)
{
    try
    {
            ifstream archivo(NOMBRE_ARCHIVO, ios::in | ios::binary);
            string linea;
            char delimitador = ',';
            if (archivo.is_open())
            { 
                //getline(archivo, linea); //extraemos la primer linea linea del archivo, la funcion getline pertenece a la clase iftream
            
                while(getline(archivo, linea))//leemos el archivo hasta el final
                {
                    
                    string nuevo;

                    stringstream stream (linea);//convertir cadena del archivo a stream
                    char delimitador = ',';
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].NOMBRE = nuevo; 
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].USUARIO = stoi(nuevo);//sino paso la lista por cada uno no me guada los datos en el arreglo
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].PIN = stoi(nuevo);
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].CBU = nuevo;
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].ALIAS = nuevo;
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].DNI = nuevo;
                    getline(stream, nuevo, delimitador);
                    lista[cantidadclientes].BALANCE = stof(nuevo);
                
                    // cout<<"--------------------------------"<<endl;
                    // cout<<" NOMBRE: "<< lista[cantidadclientes].NOMBRE <<endl;
                    // cout<<" USUARIO: "<< lista[cantidadclientes].USUARIO <<endl;
                    // cout<<" PIN: "<< lista[cantidadclientes].PIN <<endl;
                    // cout<<" CBU: "<< lista[cantidadclientes].CBU <<endl;
                    // cout<<" ALIAS: "<< lista[cantidadclientes].ALIAS <<endl;
                    // cout<<" DNI: "<< lista[cantidadclientes].DNI <<endl;
                    // cout<<" BALANCE: "<< lista[cantidadclientes].BALANCE <<endl;
                    // cout<<"--------------------------------"<<endl<<endl;

                    cantidadclientes++;

                }

                archivo.close();
            }
            else
            {
                cout<<"error "<<endl;
            }
    }    
    catch(exception e)
    {
        cout<<"error "<< e.what() << '\n';
    }
}
 
void Menu()
{
    cout<<"\n "<<endl;
    cout<<"***MenuCajero****"<<endl;
    cout<<"     1 - Balance "<<endl;
    cout<<"     2 - Deposito "<<endl;
    cout<<"     3 - Retiro "<<endl;
    cout<<"     4 - transferir "<<endl;
    cout<<"     5 - Salir"<< endl;
    cout<<"*********"<<endl<<endl;
}

bool LeerUsuario(int &usuario,int cantidadclientes)
{
    int contador=0;
    bool usuarioValido = false;
    do
    {
        cout<<"Ingrese su numero de usuario por favor: ";
        cin>>usuario;
        cout<<endl;

        for(int i=0; i<cantidadclientes; i++)
        {    
            if(usuario==lista[i].USUARIO)
            {
                usuarioValido = true; 
            }
        }    
        if(!usuarioValido)
        {
            cout<<"Usuario incorrecto"<<endl;
            contador++;
        }

    }while(!usuarioValido && contador<3);

    if(!usuarioValido)//Usuario sigue en false entra y da el mensaje
    {
        cout<<"Usuario incorrecto, retire su tarjeta por favor y vuelva a intertarlo en 24 hs"<<endl;
    }
    
    return usuarioValido; 
}

bool IngresarPIN(int usuario, int cantidadclientes)
{
    int opcion, PIN, contador=0;
    bool PINvalido = false;
    do
    {
        cout<<"Ingrese su PIN por favor: ";
        cin>>PIN;
        cout<<endl;

        for(int i=0; i<cantidadclientes;i++)
        {     
            if(usuario == lista[i].USUARIO && PIN==lista[i].PIN)
            {
                cout<<"Bienvenido!!"<< endl;
                PINvalido = true;            
            }
        
        }    
        if(!PINvalido)
        {
            cout<<"Pin incorrecto"<<endl;
            contador++;
        }

    }while(!PINvalido && contador<3);
    
    if(!PINvalido)
    {
        cout<<"PIN incorrecto, retire su tarjeta por favor y vuelva a intertarlo en 24 hs"<< endl;
    }
    
    return PINvalido;
   
}

void ConsultarBalance(int cantidadclientes, int &usuario)
{
    cliente persona;

    for (int i = 0; i < cantidadclientes; i++)
    {
        if (usuario==lista[i].USUARIO)
        {
            persona=lista[i];
        }
        cout<<"\n";
    }
    cout<<"El saldo actual de su cuenta es de: " << persona.BALANCE<<endl;
      
}

void Depositar(int cantidadclientes, int usuario)
{
    cliente datos;
    int opcion, indice;
    float DepositoEf, DepositoCh;
    bool encontrado = false;
    do
    {
        cout<<"\t ***Opciones de Depositos***"<<endl;
        cout<<"\t        1 - Depositar Efectivo "<<endl;
        cout<<"\t        2 - Depositar Cheques "<<endl;
        cout<<"\t        3 - Salir "<<endl;
        cout<<"\t *************"<<endl;
        cout<<"\n";
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cout<<endl;
        
        if(opcion==1)
        {   
            cout<<"\n"; 
            cout<<"Ingrese la suma a depositar por favor: ";
            cin>>DepositoEf;            
            
            for (int i = 0; i < cantidadclientes; i++)
            {
                if (usuario==lista[i].USUARIO)
                {
                    datos=lista[i];
                    indice = i;
                    encontrado=true;
                }    
            }

            if (encontrado)
            {
                datos.BALANCE=datos.BALANCE+DepositoEf;
                lista[indice]=datos;
                EscribirArchivo(cantidadclientes);
                cout<<endl;
                //cout<<"El saldo actual de su cuenta en " << datos.BALANCE<<endl;
            }
            else
            {
                cout<<"El deposito no se pudo realizar con exito"<<endl;
            }
        }    
        
        if(opcion==2)
        {
            cout<<"Ingrese el importe del cheque a depositar por favor: ";
            cin>>DepositoCh;
            
            for (int i = 0; i < cantidadclientes; i++)
            {
                if (usuario==lista[i].USUARIO)
                {
                    datos=lista[i];
                    indice = i;
                    encontrado=true;
                }    
            }
            if (encontrado)
            {
                datos.BALANCE=datos.BALANCE+DepositoCh;
                lista[indice]=datos;
                EscribirArchivo(cantidadclientes);
                cout<<endl;
                //cout<<"El saldo actual de su cuenta en " << datos.BALANCE<<"\n";
            }
        
            else
            {
                cout<<"El deposito no se pudo realizar con exito"<<endl;
            }
        }    
        
    }while(opcion!=3);

}

void Retirar(int cantidadclientes, int usuario)
{
    cliente persona;
    int opcion, pos;
    int TotalExtraccion=0;
    int Retirofinal=0;
    bool encontrado=false;
    float saldo;
    
    for (int i = 0; i < cantidadclientes; i++)
    {
        if (usuario==lista[i].USUARIO)
        {
            persona=lista[i];
            pos=i;
            encontrado=true;   
        }
    }
    if (encontrado)
    {
        saldo=persona.BALANCE;
    }
    
    do
    {
        
        cout<<"\t *****Opciones de Retiro*****"<<endl;
        cout<<"\t        1 - Retirar $5000 "<<endl;
        cout<<"\t        2 - Retirar $10000 "<<endl;
        cout<<"\t        3 - Retirar $20000 "<<endl;
        cout<<"\t        4 - Retirar $30000 "<<endl;
        cout<<"\t        5 - Retirar $40000 "<<endl;
        cout<<"\t        6 - Retirar $50000 "<<endl;
        cout<<"\t        7 - Ingrese el monto a retirar "<<endl;
        cout<<"\t        8 - Salir "<<endl;
        cout<<"\t **************"<<endl;
        cout<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;
        cout<<endl;

        switch (opcion)
        {
            case 1:

                if (TotalExtraccion+5000<=70000)
                {
                    if (5000>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $5000, gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-5000;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=5000;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;

            case 2:

                 if (TotalExtraccion+10000<=70000)
                {
                    if (10000>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $10000, gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-10000;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=10000;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;

            case 3:
                
                if (TotalExtraccion+20000<=70000)
                {
                    if (20000>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $20000, gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-20000;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=20000;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;

            case 4:

                 if (TotalExtraccion+30000<=70000)
                {
                    if (30000>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $30000, gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-30000;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=30000;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;

            case 5:
                 if (TotalExtraccion+40000<=70000)
                {
                    if (40000>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $40000, gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-40000;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=40000;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;

            case 6:
                 if (TotalExtraccion+50000<=70000)
                {
                    if (50000>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $50000, gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-50000;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=50000;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;
                
            case 7: 
                
                cout<<"Ingrese el monto que desea retirar ";
                cin>>Retirofinal;

                if (TotalExtraccion+Retirofinal<=70000)
                {   
                    if (Retirofinal>saldo)
                    {
                        cout<<"Transaccion invalida, fondos insuficientes en la cuenta "<<endl;
                    }
                    else
                    {
                        cout<<"Usted ha retirado $ "<<Retirofinal<<", gracias por utilizar nuestros servicios "<<endl;    
                        persona.BALANCE=saldo-Retirofinal;
                        lista[pos]=persona;
                        EscribirArchivo(cantidadclientes);
                        cout<<endl;
                        TotalExtraccion+=Retirofinal;
                    }
                }
                else
                {
                    cout<<"Usted ha suparado el limite de extraccion diario "<<endl;
                }
                cout<<endl; 
                break;

            case 8:
                cout<<"Saliendo!!, gracias por utilizar nuestros servicios"<<endl;    
                break;

            default:
                cout<<"La opcion ingresada es incorrecta "<<endl;
                break;
        }
     
    } while (opcion!=8);
    cout << "Usted ha retirado en total: " << TotalExtraccion << endl;
}

void Transferir(int cantidadclientes, int usuario, string cbu)
{
    cliente personsali, persondestino;
    int opcion, indice, pos, saldo;
    float transfpro, transfter;
    bool encontrado = false, bandera=false;
    
    for(int i = 0; i < cantidadclientes; i++)
    {
        if (usuario==lista[i].USUARIO)
        {
            personsali=lista[i];
            indice = i;
            encontrado=true;
        }
        
    }
    if(encontrado)
    {
        saldo=personsali.BALANCE;
    }
        // cout<<endl;
        // cout<<"*****Opciones de Transferencia*****"<<endl;      Dejo comentario de como se penso en un principio el codigo, pero creemos que habia que crear un nuevo archivo txt
        // cout<<"      1 - Transferencia a cuenta propia"<<endl;
        // cout<<"      2 - Transferencia a cuenta de terceros"<<endl;
        // cout<<"      3 - Salir"<<endl<<endl;
        // cout<<"Ingrese una opcion: ";
        // cin>>opcion; 
        // cout<<endl;

    do
    {
        cout<<"Ingrese numero de cuenta o cbu de destino, o ingrese 0 para salir "<<endl;
        cin>>cbu;
        cout << endl;

        if (cbu!="0")
        {

            for (int i = 0; i < cantidadclientes; i++)
            {
                if (cbu==lista[i].CBU)
                {
                    bandera = true;
                    cout<<"Indique el monto que desea transferir ";
                    cin>>transfter;
                    cout << endl;

                    if (transfter>saldo)
                    {
                        cout<<"Transaccion invalida, no posee los fondos suficientes en su cuenta "<<endl;
                    }
                    else
                    {
                        personsali.BALANCE -= transfter;
                        lista[indice]=personsali;
                        persondestino = lista[i];
                        pos = i;
                        persondestino.BALANCE += transfter;
                        lista[pos]=persondestino;
                        EscribirArchivo(cantidadclientes);
                    }
                }
                
            }
            if(!bandera)
            {
            cout<<"Numero de cuenta o cbu inexistente "<< endl;
            }
        }    

    }while(!bandera&&cbu!="0");
    
}

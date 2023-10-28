
#ifndef USER_H
#define USER_H

#define CAPACITY 20

typedef struct 
{
    STRING nama;
    STRING password;
    PROFIL profil;

}
USER;

typedef struct
{
    USER contents[CAPACITY];
}
USERS;

void createUser();





#endif

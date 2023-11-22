#include <stdio.h>
#include "draft.h"

Draft ContainerDraft[20];

AddressDraft newDraft(STRING content)
{
    AddressDraft new = (AddressDraft)malloc(sizeof(DraftNode));
    if (new != NULL){
        copyString(&CONTENTDRAFT(new), content);
        TIMEDRAFT(new) = getCurrentDATETIME();
        NEXTDRAFT(new) = NULL;
    }
    return new;
}

void createDraft(Draft * draft)
{
    TOPDRAFT(*draft) = NULL;
}

boolean isEmptyDraft(Draft draft)
{
    return TOPDRAFT(draft) == NULL;
}

void pushDraft(Draft *draft, STRING content)
{
    AddressDraft new = newDraft(content);
    if (new != NULL){
        NEXTDRAFT(new) = TOPDRAFT(*draft);
        TOPDRAFT(*draft) = new;
    }
}
void popDraft(Draft *draft, AddressDraft *outDraft)
{
    *outDraft = TOPDRAFT(*draft);
    TOPDRAFT(*draft) = NEXTDRAFT(TOPDRAFT(*draft));
    NEXTDRAFT(*outDraft) = NULL;
}

void createContainerDraft()
{
    for (int i = 0; i < 20; i++){
        createDraft(&ContainerDraft[i]);
    }
}

void BUAT_DRAFT(int currentID, ListKicau *lk)
{
    STRING content;
    do {
        printf("Masukkan draf:\n");
        readKicauan();
        if (!VALID) {
            printf("\nWalawe, draf Anda tidak sesuai. Isi draf tidak boleh berisi karakter spasi atau newline saja.\n\n");
        }
    } while (!VALID);
    copyString(&content, string);
    printf("Apakah Anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n");
    do {
        readString();
        if (!isWordEqual(string, "HAPUS") && !isWordEqual(string, "SIMPAN") && !isWordEqual(string, "TERBIT")){
            printf("Input Anda tidak sesuai. Masukkan input yang sesuai, ya.\n");
        }
    }while (!isWordEqual(string, "HAPUS") && !isWordEqual(string, "SIMPAN") && !isWordEqual(string, "TERBIT"));
    if (isWordEqual(string, "HAPUS")){
        printf("\nDraf telah berhasil dihapus!\n\n");
    } else if (isWordEqual(string, "SIMPAN")){
        pushDraft(&ContainerDraft[currentID], content);
        printf("\nDraf telah berhasil disimpan!\n\n");
    } else {
        KICAU newKicau;
        createKicau(lk, USER(UserList, currentID), content);
        
    }

}
void LIHAT_DRAFT(int currentID);
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

void displayDraft(Draft draft)
{
    printf("| ");
    displayDATETIME(TIMEDRAFT(draft));
    printf("| ");
    displayString(CONTENTDRAFT(draft));
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
        createKicau(lk, USER(UserList, currentID), content);
        printf("Selamat! Draf kicauan telah berhasil diterbitkan!\nDetil kicauan:\n");
        displayKicau(KICAU(*lk, NEFF(*lk)-1));
        printf("\n");
    }

}
void LIHAT_DRAFT(int currentID, ListKicau *lk)
{
    if (isEmptyDraft(ContainerDraft[currentID])){
        printf("Walawe, Anda belum memiliki draf apapun! Buat dulu ya :D\n\n");
        return;
    }
    AddressDraft d = TOPDRAFT(ContainerDraft[currentID]);
    printf("Ini draft terakhir Anda:\n");
    displayDraft(d);
    do{
        printf("Apakah Anda ingin mengubah, menghapus, atau menerbitkan draft ini? (KEMBALI jika ingin kembali)\n");
        readString();
        if (!isWordEqual(string, "HAPUS") && !isWordEqual(string, "UBAH") && !isWordEqual(string, "TERBIT") && !isWordEqual(string, "KEMBALI")){
            printf("Command yang Anda masukkan tidak sesuai. Masukkan command yang sesuai.\n\n");
        }
    } while (!isWordEqual(string, "HAPUS") && !isWordEqual(string, "UBAH") && !isWordEqual(string, "TERBIT") && !isWordEqual(string, "KEMBALI"));
    if (isWordEqual(string, "HAPUS")){
        AddressDraft temp;
        popDraft(&ContainerDraft[currentID], &temp);
        free(temp);
        printf("Draft telah berhasil dihapus!\n\n");
    } else if (isWordEqual(string, "UBAH")){
        AddressDraft temp;
        popDraft(&ContainerDraft[currentID], &temp);
        free(temp);
        STRING content;
        do {
            printf("Masukkan draf yang baru:\n");
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
            createKicau(lk, USER(UserList, currentID), content);
            printf("Selamat! Draf kicauan telah berhasil diterbitkan!\nDetil kicauan:\n");
            displayKicau(KICAU(*lk, NEFF(*lk)-1));
            printf("\n");
        }
    } else if (isWordEqual(string, "TERBIT")){
        AddressDraft temp;
        popDraft(&ContainerDraft[currentID], &temp);
        STRING content;
        copyString(&content, CONTENTDRAFT(temp));
        free(temp);
        createKicau(lk, USER(UserList, currentID), content);
        printf("Selamat! Draf kicauan telah berhasil diterbitkan!\nDetil kicauan:\n");
        displayKicau(KICAU(*lk, NEFF(*lk)-1));
        printf("\n");
    }
}
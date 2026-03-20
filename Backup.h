#ifndef BACKUP_H_INCLUDED
#define BACKUP_H_INCLUDED

class Backup {
public:
    void crearBackupGeneral();
    void restaurarBackupGeneral();

private:
    bool copiarArchivo(const char* origen, const char* destino);
};


#endif // BACKUP_H_INCLUDED

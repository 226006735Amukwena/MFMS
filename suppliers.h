#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <stdio.h>

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);

int  findSupplierById(int id);
int  getSupplierCount(void);
void printSupplierTable(FILE *out);

/* Persistence (Week 10) */
int saveSuppliers(const char *path);
int loadSuppliers(const char *path);

#endif

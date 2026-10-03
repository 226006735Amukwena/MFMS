#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <stdio.h>
// costants for maximum lengths of supplier data fields//
void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);
//void printSupplierTable(FILE *out);
int  findSupplierById(int id);
int  getSupplierCount(void);
void printSupplierTable(FILE *out);
//void printSupplierHeader(FILE *out);
int saveSuppliers(const char *path);
int loadSuppliers(const char *path);

#endif

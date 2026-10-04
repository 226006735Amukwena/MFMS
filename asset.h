#ifndef Assets_H
#define Assets_H
#define MAX_ASSETS 50
#define TYPE_LEN 50
#define CONDITION_LEN 50

#ifndef NAME_LEN
#define NAME_LEN 60
#endif
#ifndef DEPT_LEN
#define DEPT_LEN 30
#endif

extern int assetID[MAX_ASSETS];
extern char assetName[MAX_ASSETS][NAME_LEN];
extern char assetType[MAX_ASSETS][TYPE_LEN];
extern float purchaseValue[MAX_ASSETS];
extern char department[MAX_ASSETS][DEPT_LEN];
extern char condition[MAX_ASSETS][CONDITION_LEN];

extern int count;
void addAsset(void);
void  assetDisplay(void);
void searchAsset(void);
void choice(void);

#endif

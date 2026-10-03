#ifndef Assets_H
#define Assets_H
#define MAX_ASSETS 50
#define NAME_LEN 50
#define TYPE_LEN 50
#define DEPT_LEN 50
#define CONDITION_LEN 50

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

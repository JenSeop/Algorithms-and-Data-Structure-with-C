#ifndef ___Member
#define ___Member

// Struct of Member
typedef struct {
  int no;         //num
  char name[20];  // name
} Member;

#define MEMBER_NO 1     // no with num
#define MEMBER_NAME 2   // name with name

// compare member num
int MemberNoCmp(const Member *x, const Member *y);

// compare member name
int MemberNameCmp(const Member *x, const Member *y);

// print member no \n
void PrintMember(const Member *x);

// print member yes \n
void PrintLnMember(const Member *x);

// read member data
Member ScanMember(const char *message, int sw);

#endif
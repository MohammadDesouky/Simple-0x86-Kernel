#ifndef CU_FOS_OS_MEMORY
#define CU_FOS_OS_MEMORY


char * CopyMemory(char * Source, char * Destination,unsigned Length);
void * MemorySetToValueByte(void * Destination, char Value,int Times);
void * MemorySetToValue2Bytes(void *  Destination,unsigned short Value, int Times);
void EnableA20();
#endif

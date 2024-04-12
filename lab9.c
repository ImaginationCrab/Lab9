#include <stdio.h>
#include <stdlib.h>
#define tableSize 50
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType record;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	return x%tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		if(pHashArray[i].record.name!=NULL){
			printf("\t%d %c %d\n", pHashArray[i].record.id, pHashArray[i].record.name, pHashArray[i].record.order);
		}
		if(pHashArray[i].next!=NULL){
			struct HashType* head = pHashArray[i].next;
			while(head->next!=NULL){
				printf("\t%d %c %d\n", head->record.id, head->record.name, head->record.order);
				head = head->next;
			}
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	struct HashType arr[50];
	for(int i = 0 ;i<50;i++){
		arr[i].record.name = NULL;
		arr[i].next =NULL;
	}
	for(int i = 0;i<recordSz;i++){
		int h = hash(pRecords[i].id);
		if(arr[h].record.name ==NULL){
			arr[h].record = pRecords[i];
		}else{
			struct HashType* new = (struct HashType*)calloc(1,sizeof(struct HashType));
			struct HashType* temp = arr[h].next;
			new->record = pRecords[i];
			if(arr[h].next==NULL){
				arr[h].next = new;
			}else{
				while(temp!=NULL&&temp->next!=NULL){
				temp = temp->next;	
				}
				if(temp!=NULL){
					temp->next = new;
				}else{
					temp = new;
				}
			}
		}
	}
	displayRecordsInHash(arr,50);
	
}
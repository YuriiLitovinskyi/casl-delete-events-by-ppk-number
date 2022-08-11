#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include <stdbool.h>


// function for checking if entered value is a number
bool isNumber(const char value[]){
	int length, i;
	
	length = strlen(value);
	for(i = 0; i < length; i++){
		if(!isdigit(value[i])){		
			return false;
		}		
	}
	return true;
}

// function inserts into subject[] at position pos
void append(char subject[], const char insert[], int pos) {
    char buf[256] = {};

    strncpy(buf, subject, pos); // copy at most first pos characters
    int len = strlen(buf);
    strcpy(buf+len, insert); // copy all of insert[] at the end
    len += strlen(insert);  // increase the length by length of insert[]
    strcpy(buf+len, subject+pos); // copy the rest

    strcpy(subject, buf);   // copy it back to subject
    // deallocate buf[] here, if used malloc()
}

int main(int argc, char *argv[]) {     
    sqlite3 *db;
    char *err_msg = 0;
    int closeDb = 0;
    
    char ppkNumber[256];
    
    printf("Enter ppk number: ");
	gets(ppkNumber); 
	
	   // Check if value is a number
    if(isNumber(ppkNumber) == false){
    	printf("\nError! Entered value is not a number! \n\n");
    	
		system("pause"); 
		       
        return 1;
	}   
	
    
    int rc = sqlite3_open("data.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open CASL Cloud database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        system("pause");
        
        return 1;
    } 
	   
    // delete events by device number
    char sqlDelDev[256] = "DELETE FROM event WHERE device_id = (SELECT device_id FROM device WHERE number = )";       
	append(sqlDelDev, ppkNumber, 81);  
    //printf(sqlDelDev);  
    rc = sqlite3_exec(db, sqlDelDev, 0, 0, &err_msg);    
	
	if (rc != SQLITE_OK ) {        
        fprintf(stderr, "SQL error: %s\n", err_msg);  
		printf("\n");       
        sqlite3_free(err_msg);        
        sqlite3_close(db);        
        system("pause"); 
		return 1;       
    }        

    printf("\nDeleted all events for ppk %s \n", ppkNumber);
    sqlite3_close(db);
    printf("\n");    
    system("pause");      
	return 0;
}

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <vector>
#include <stdio.h>

using namespace std;

void Parse(char* cmnd, char* cmd[], char input[]);
void Clear(char* cmd[]);
void Execute(char* cmd[]);



int main() {

    char* cmnd = 0;
    char* cmd[40];
    char input[50];
    

    while(cmd[0] != NULL) {
        Clear(cmd);
        Parse(cmnd, cmd, input);
        if(strcmp(cmd[0], "exit") == 0) {
            break;
        }    
        else {
            Execute(cmd);
                      
        }    
    }    
}

void Parse(char* cmnd, char* cmd[], char input[]) {
    char* username;
    char hostname[40];

    username = getlogin();
    gethostname(hostname, sizeof hostname);

    cout << username << "@" << hostname << "$ ";
    cin.getline(input, 50);
    cmnd = strtok(input, " ");
    int i = 0;

    while (cmnd != NULL) {
        cmd[i] = cmnd;
        i++;
        cmnd = strtok(NULL, " ");
    }
}    

void Clear(char* cmd[]) {
    for (int i = 0; i < 40; i++) {
        cmd[i] = NULL;
    }
} 

void Execute(char* cmd[]) {
    int i = 0, j = 0;

   	while(cmd[i] != NULL) {
   		if(strcmp(cmd[i], "test") == 0 || cmd[i] == "[" )
		  {
        struct stat info;
			  switch(cmd[i+1][0])
			  {
          case '/':
    			  	{
    			  		if(stat(cmd[i+1], &info) == 0)
    			  			cout<<"(True)"<<endl;
    			  		else
    						  cout<<"(False)"<<endl;
    					i++;
              j = i;   
    					break;
    				  }
    			case '-':
          {
      			switch(cmd[i+1][1])
      			{
      			  	case 'e':
      			  	{
      			  		if(stat(cmd[i+2], &info) == 0)
      			  			cout<<"(True)"<<endl;
      			  		else
      						  cout<<"(False)"<<endl;
                i+= 2;
      					j = i;
      					break;
      				}
      
      				case 'f':
      				{
      			  		if(stat(cmd[i+2], &info) == 0 && S_ISREG(info.st_mode))
      			  			cout<<"(True)"<<endl;
      			  		else
      						  cout<<"(False)"<<endl;
   					    i+= 2;
                j = i;
      					break;
      				}
      
      				case 'd':
      				{
      			  		if(stat(cmd[i+2], &info) == 0 && S_ISDIR(info.st_mode))
      			  			cout<<"(True)"<<endl;
      			  		else
      						  cout<<"(False)"<<endl;
   					    i+= 2;
                j = i;      
      				break;
      				}
              default:
 					      cout<<"invalid command!"<<endl;
			      }
			    }
		    }
		  }
		i++;
	}

    pid_t pid;
    pid = fork();
/*    switch(pid) {
        case -1:
            cout << "Fork Failure" << endl;
            exit(-1);
        case 0:
            execvp(cmd[0], cmd);

            if (execvp(cmd[0], cmd) == -1) {
                cout << "Invalid command" << endl;
                exit(0);
            }    
        default: 
            wait(NULL);
            cout << "Child Finished" << endl;
    }
*/
    if (pid < 0) {
        perror("fork() error)");
        exit(-1);
    }    
    if (pid != 0) {
//        printf("I'm the parent %d, my child is %d\n", getpid(), pid);
        wait(NULL);
    } 
    else {
//        printf ("I'm the parent %d, my child is %d\n", getpid(), getppid());
        execvp(cmd[0], cmd);  
        
        if (execvp(cmd[0], cmd) == -1) {
            cout << "Invalid command" << endl;
            exit(0);
        }
        
           
    }              
                            
}




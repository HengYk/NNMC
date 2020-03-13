frame(in_file, main_res) and (
struct _iobuf {
char *_ptr and 
int _cnt and 
char *_base and 
int _flag and 
int _file and 
int _charbuf and 
int _bufsiz and 
char *_tmpfname 
};
FILE *in_file and skip;
float main_res[10] and skip;
 function main ( int  RValue )
 {
     frame(main_buffer,main_index,main_2_temp$_1,main_2_token,main_2_i,main_i,return,break$) and (
     int break$<==0 and skip;
     int return<==0 and skip;
     output ("the program is running!\n") and skip;
     in_file:=fopen("iterative_param.txt","r");
     if(!in_file) then 
     {
         fprintf(stderr,"Cannot open %s!",in_file) and skip
         
     }
     else 
     {
          skip 
     };
     char main_buffer[256] and skip;
     int main_index<==0 and skip;
     break$<==0 and skip;
     char* main_2_temp$_1 and skip;
     main_2_temp$_1:=fgets(main_buffer,256,in_file);
     while( break$=0 AND   (main_2_temp$_1!=NULL) )
     {
         char* main_2_token and skip;
         main_2_token:=strtok(main_buffer," ",RValue);
         int main_2_i<==0 and skip;
         
         while( (main_2_i<27) )
         {
             if(main_2_i=26) then 
             {
                 main_res[main_index]:=strtod(main_2_token,NULL,RValue);
                 main_2_token:=strtok(NULL," ",RValue)
             }
             else 
             { 
			      strtod(main_2_token,NULL,RValue) and skip;
                  main_2_token:=strtok(NULL," ",RValue);
                  skip 
             };
             main_2_i:=main_2_i+1
         };
         main_index:=main_index+1;
         if(main_index=10) then 
         {
             break$<==1 and skip
             
         }
         else 
         {
		      main_2_temp$_1:=fgets(main_buffer,256,in_file);
              skip 
         }
     };
     break$<==0 and skip;
     int main_i<==0 and skip;
     
     while( (main_i<10) )
     {
         output (main_i, " ", main_res[main_i],"\n") and skip;
         main_i:=main_i+1
         
     };
     fclose(in_file) and skip;
     return<==1 and RValue:=0;
     skip
     )
 };
  main(RValue)
 )

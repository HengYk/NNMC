frame(v,w,r,o,g,e,f,x,b,y,yc,Ek,aveEk) and (
float v[3,5] and skip;
float w[5,1] and skip;
float r[5] and skip;
float o[1] and skip;
float g[1] and skip;
float e[5] and skip;
float f[3] and skip;
float x[3] and skip;
float b[5] and skip;
float y[1] and skip;
float yc[1] and skip;
float Ek and skip;
float aveEk and skip;
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
 function read_parameter ( int  RValue )
 {
     frame(read_parameter_in,read_parameter_buffer,read_parameter_i,read_parameter_h,read_parameter_h_1,read_parameter_j,read_parameter_h_3,read_parameter_j_1,return) and ( 
     int return<==0 and skip;
     FILE *read_parameter_in<==NULL and skip;
     read_parameter_in:=fopen("bpnn_param.txt","r");
     if(read_parameter_in=NULL) then 
     {
         fprintf(stderr,"Cannot open %s\n","bpnn_param.txt") and skip;
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         char read_parameter_buffer[256] and skip;
         int read_parameter_i<==0 and skip;
         
         while( (read_parameter_i<3) )
         {
             int read_parameter_h<==0 and skip;
             
             while( (read_parameter_h<5) )
             {
                 fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
                 v[read_parameter_i,read_parameter_h]:=strtod(read_parameter_buffer,NULL,RValue);
                 read_parameter_h:=read_parameter_h+1
                 
             };
             read_parameter_i:=read_parameter_i+1
             
         };
         int read_parameter_h_1<==0 and skip;
         
         while( (read_parameter_h_1<5) )
         {
             int read_parameter_j<==0 and skip;
             
             while( (read_parameter_j<1) )
             {
                 fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
                 w[read_parameter_h_1,read_parameter_j]:=strtod(read_parameter_buffer,NULL,RValue);
                 read_parameter_j:=read_parameter_j+1
                 
             };
             read_parameter_h_1:=read_parameter_h_1+1
             
         };
         int read_parameter_h_3<==0 and skip;
         
         while( (read_parameter_h_3<5) )
         {
             fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
             r[read_parameter_h_3]:=strtod(read_parameter_buffer,NULL,RValue);
             read_parameter_h_3:=read_parameter_h_3+1
             
         };
         int read_parameter_j_1<==0 and skip;
         
         while( (read_parameter_j_1<1) )
         {
             fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
             o[read_parameter_j_1]:=strtod(read_parameter_buffer,NULL,RValue);
             read_parameter_j_1:=read_parameter_j_1+1
             
         };
         fclose(read_parameter_in) and skip;
         return<==1 and RValue:=1;
         skip
     }
     else
     {
         skip
     }
     )
     }; 
  function bpnn_check_single (  )
 {
     frame(bpnn_check_single_ax,bpnn_check_single_by,bpnn_check_single_h,bpnn_check_single_alpha_h,bpnn_check_single_i,bpnn_check_single_j,bpnn_check_single_beta_j,bpnn_check_single_h_1,bpnn_check_single_j_1,bpnn_check_single_check_flag) and ( 
     float bpnn_check_single_ax[3]<=={0.991998,0.919734,0.859287} and skip;
     float bpnn_check_single_by[1]<=={0.923673} and skip;
	 // float bpnn_check_single_ax[3]<=={0.712532,0.451378,0.920685} and skip;
	 // float bpnn_check_single_by[1]<=={0.694865} and skip;
     int bpnn_check_single_h<==0 and skip;
     
     while( (bpnn_check_single_h<5) )
     {
         float bpnn_check_single_alpha_h<==0 and skip;
         int bpnn_check_single_i<==0 and skip;
         
         while( (bpnn_check_single_i<3) )
         {
             bpnn_check_single_alpha_h:=bpnn_check_single_alpha_h+v[bpnn_check_single_i,bpnn_check_single_h]*bpnn_check_single_ax[bpnn_check_single_i];
             bpnn_check_single_i:=bpnn_check_single_i+1
             
         };
         b[bpnn_check_single_h]:=(1/ (1+exp(-(bpnn_check_single_alpha_h-r[bpnn_check_single_h]))));
         bpnn_check_single_h:=bpnn_check_single_h+1
         
     };
     int bpnn_check_single_j<==0 and skip;
     
     while( (bpnn_check_single_j<1) )
     {
         float bpnn_check_single_beta_j<==0 and skip;
         int bpnn_check_single_h_1<==0 and skip;
         
         while( (bpnn_check_single_h_1<5) )
         {
             bpnn_check_single_beta_j:=bpnn_check_single_beta_j+w[bpnn_check_single_h_1,bpnn_check_single_j]*b[bpnn_check_single_h_1];
             bpnn_check_single_h_1:=bpnn_check_single_h_1+1
             
         };
         yc[bpnn_check_single_j]:=(1/ (1+exp(-(bpnn_check_single_beta_j-o[bpnn_check_single_j]))));
         bpnn_check_single_j:=bpnn_check_single_j+1
         
     };
     Ek:=0;
     int bpnn_check_single_j_1<==0 and skip;
     
     while( (bpnn_check_single_j_1<1) )
     {
         Ek:=Ek+(yc[bpnn_check_single_j_1]-bpnn_check_single_by[bpnn_check_single_j_1])*(yc[bpnn_check_single_j_1]-bpnn_check_single_by[bpnn_check_single_j_1]);
         bpnn_check_single_j_1:=bpnn_check_single_j_1+1
         
     };
     Ek:=0.5*Ek;
     int bpnn_check_single_check_flag<==0 and skip;
	 aveEk <==0.00000215 and skip;
     if(Ek<=aveEk) then 
     {
         bpnn_check_single_check_flag:=1
         
     }
     else 
     {
          skip 
     };
     if(bpnn_check_single_check_flag) then 
     {
         output ("Ek <= aveEk : ",Ek," <= ",aveEk," --> #success#","\n") and skip
     }
     else
     {
         output ("Ek > aveEk : ",Ek," > ",aveEk,"  -->  #failure#","\n") and skip
     }
     )
     }; 
  function main ( int  RValue )
 {
     frame(main_1_temp$_1,return) and (
     int return<==0 and skip;
     int main_1_temp$_1 and skip;
     main_1_temp$_1:=read_parameter(RValue);
     if(!main_1_temp$_1) then 
     {
         output ("Read param is failed in ","bpnn_param.txt","!\n") and skip;
         return<==1 and RValue:=0;
         skip
         
     }
     else 
     {
          skip 
     };
     if(return=0)   then 
     {
         bpnn_check_single();
         return<==1 and RValue:=0;
         skip
     }
     else
     {
         skip
     }
     )
 };
  main(RValue)
 )

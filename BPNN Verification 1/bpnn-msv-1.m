frame(v,w,r,o,g,e,f,x,b,y,yc,Ek,maxEk,minEk,aveEk,in_file,out_file,bpnn_sim_percent) and (
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
float maxEk and skip;
float minEk and skip;
float aveEk and skip;
float bpnn_sim_percent and skip;
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
FILE *in_file<==NULL and skip;
FILE *out_file<==NULL and skip;
 function read_data ( float *in,float *out,int RValue )
 {
     frame(read_data_buffer,read_data_1_2_temp$_1,read_data_1_2_token,read_data_1_2_i,read_data_1_5_temp$_2,return) and ( 
     int return<==0 and skip;
     char read_data_buffer[256] and skip;
     if(in_file AND out_file) then 
     {
         char* read_data_1_2_temp$_1 and skip;
         read_data_1_2_temp$_1:=fgets(read_data_buffer,256,in_file);
         if(read_data_1_2_temp$_1!=NULL) then 
         {
             char* read_data_1_2_token and skip;
             read_data_1_2_token:=strtok(read_data_buffer,",",RValue);
             int read_data_1_2_i<==0 and skip;
             
             while( return=0 AND   return=0 AND   (read_data_1_2_i<3) )
             {
                 if(read_data_1_2_token=NULL) then 
                 {
                     fprintf(stderr,"The format of input is not correct!\n") and skip;
                     return<==1 and RValue:=0;
                     skip
                     
                 }
                 else 
                 {
                      skip 
                 };
                 if(return=0)   then 
                 {
                     in[read_data_1_2_i]:=strtod(read_data_1_2_token,NULL,RValue);
                     read_data_1_2_token:=strtok(NULL,",",RValue);
                     read_data_1_2_i:=read_data_1_2_i+1
                 }
                 else
                 {
                     skip
                 }
                 
             }
             
         }
         else
         {
             return<==1 and RValue:=0;
             skip
         };
         if(return=0)  then
         {
             if(return=0)  then
             {
                 char* read_data_1_5_temp$_2 and skip;
                 read_data_1_5_temp$_2:=fgets(read_data_buffer,256,out_file);
                 if(read_data_1_5_temp$_2!=NULL) then 
                 {
                     out[0]:=strtod(read_data_buffer,NULL,RValue)
                     
                 }
                 else
                 {
                     return<==1 and RValue:=0;
                     skip
                 };
                 if(return=0)  then
                 {
                     return<==1 and RValue:=1;
                     skip
                 }
                 else
                 {
                     skip
                 }
             }
             else
             {
                 skip
             }
         }
         else
         {
             skip
         }
         
     }
     else 
     {
          skip 
     };
     if(return=0)  then
     {
         if(return=0)   then 
         {
             return<==1 and RValue:=0;
             skip
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
     }; 
  function read_parameter ( int  RValue )
 {
     frame(read_parameter_in,read_parameter_buffer,read_parameter_i,read_parameter_h,read_parameter_h_1,read_parameter_j,read_parameter_h_2,read_parameter_j_1,return) and ( 
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
         int read_parameter_h_2<==0 and skip;
         
         while( (read_parameter_h_2<5) )
         {
             fscanf(read_parameter_in,"%s",read_parameter_buffer) and skip;
             r[read_parameter_h_2]:=strtod(read_parameter_buffer,NULL,RValue);
             read_parameter_h_2:=read_parameter_h_2+1
             
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
  function bpnn_sim (  )
 {
     frame(bpnn_sim_count,bpnn_sim_co,bpnn_sim_1_temp$_1,bpnn_sim_1_h,bpnn_sim_1_alpha_h,bpnn_sim_1_i,bpnn_sim_1_j,bpnn_sim_1_beta_j,bpnn_sim_1_h_1,bpnn_sim_1_i,bpnn_sim_1_j_1,bpnn_sim_check_model) and ( 
     maxEk:=0; 
	 minEk:=1;
	 aveEk:=0;
	 int bpnn_sim_count<==0 and skip;
     int bpnn_sim_co<==0 and skip;
     bpnn_sim_percent<==0.0 and skip;
     int bpnn_sim_1_temp$_1 and skip;
     bpnn_sim_1_temp$_1:=read_data(x,y,RValue);
     while( (bpnn_sim_1_temp$_1) )
     {
         bpnn_sim_count:=bpnn_sim_count+1;
         int bpnn_sim_1_h<==0 and skip;
         
         while( (bpnn_sim_1_h<5) )
         {
             float bpnn_sim_1_alpha_h<==0 and skip;
             int bpnn_sim_1_i<==0 and skip;
             
             while( (bpnn_sim_1_i<3) )
             {
                 bpnn_sim_1_alpha_h:=bpnn_sim_1_alpha_h+v[bpnn_sim_1_i,bpnn_sim_1_h]*x[bpnn_sim_1_i];
                 bpnn_sim_1_i:=bpnn_sim_1_i+1
                 
             };
             b[bpnn_sim_1_h]:=(1/ (1+exp(-(bpnn_sim_1_alpha_h-r[bpnn_sim_1_h]))));
             bpnn_sim_1_h:=bpnn_sim_1_h+1
             
         };
         Ek:=0;
         int bpnn_sim_1_j<==0 and skip;
         
         while( (bpnn_sim_1_j<1) )
         {
             float bpnn_sim_1_beta_j<==0 and skip;
             int bpnn_sim_1_h_1<==0 and skip;
             
             while( (bpnn_sim_1_h_1<5) )
             {
                 bpnn_sim_1_beta_j:=bpnn_sim_1_beta_j+w[bpnn_sim_1_h_1,bpnn_sim_1_j]*b[bpnn_sim_1_h_1];
                 bpnn_sim_1_h_1:=bpnn_sim_1_h_1+1
                 
             };
             yc[bpnn_sim_1_j]:=(1/ (1+exp(-(bpnn_sim_1_beta_j-o[bpnn_sim_1_j]))));
             Ek:=Ek+(yc[bpnn_sim_1_j]-y[bpnn_sim_1_j])*(yc[bpnn_sim_1_j]-y[bpnn_sim_1_j]);
             bpnn_sim_1_j:=bpnn_sim_1_j+1
             
         };
         Ek:=0.5*Ek;
         if(Ek<0.000001) then 
         {
             bpnn_sim_co:=bpnn_sim_co+1
             
         }
         else 
         {
              skip 
         };
         output ("Index: ",bpnn_sim_count,"   Cost: ",Ek," ==> ") and skip;
         output ("Input: ") and skip;
         bpnn_sim_1_i<==0 and skip;
         
         while( (bpnn_sim_1_i<3) )
         {
             output (x[bpnn_sim_1_i]," "," ") and skip;
             bpnn_sim_1_i:=bpnn_sim_1_i+1
             
         };
         output ("Output:") and skip;
         int bpnn_sim_1_j_1<==0 and skip;
         
         while( (bpnn_sim_1_j_1<1) )
         {
             output (y[bpnn_sim_1_j_1],"[",yc[bpnn_sim_1_j_1],"] ","] ") and skip;
             bpnn_sim_1_j_1:=bpnn_sim_1_j_1+1
             
         };
         output ("\n") and skip;
         maxEk:=( if((Ek>maxEk)) then Ek else maxEk);
         minEk:=( if((Ek<minEk)) then Ek else minEk);
         aveEk:=aveEk+Ek;
         bpnn_sim_1_temp$_1:=read_data(x,y,RValue)
     };
     aveEk:=aveEk/ bpnn_sim_count;
     bpnn_sim_percent:=bpnn_sim_co/ (float)bpnn_sim_count;
     output ("MaxCost: ",maxEk,"  MinCost: ",minEk,"  AveCost: ",aveEk,"\n") and skip;
     output ("Percent: ",bpnn_sim_percent*100,"\n") and skip;
     int bpnn_sim_check_model<==0 and skip;
     if(bpnn_sim_percent>0.9) then 
     {
         bpnn_sim_check_model:=1
         
     }
     else 
     {
          skip 
     };
     output (bpnn_sim_check_model,"\n","\n") and skip
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
         in_file:=fopen("in_reduced.txt","r");
         if(in_file=NULL) then 
         {
             fprintf(stderr,"Cannot open %s.\n","in_reduced.txt") and skip;
             return<==1 and RValue:=0;
             skip
             
         }
         else 
         {
              skip 
         };
         if(return=0)   then 
         {
             out_file:=fopen("out_reduced.txt","r");
             if(out_file=NULL) then 
             {
                 fprintf(stderr,"Cannot open %s.\n","out_reduced.txt") and skip;
                 return<==1 and RValue:=0;
                 skip
                 
             }
             else 
             {
                  skip 
             };
             if(return=0)   then 
             {
                 bpnn_sim();
                 fclose(in_file) and skip;
                 fclose(out_file) and skip;
                 return<==1 and RValue:=0;
                 skip
             }
             else
             {
                 skip
             }
         }
         else
         {
             skip
         }
     }
     else
     {
         skip
     }
     )
 };
  main(RValue)
 )
